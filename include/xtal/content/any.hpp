#pragma once
#include "../common/all.hpp"//_retail






XTAL_ENV_(push)
namespace xtal::content
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::common;
#include "../common/any.hxx"


////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct define
{
	template <any_q S>
	class subtype: public S
	{
		using co = S;

	public:
		using co::co;
		
		///\
		\returns `true`. \

		XTAL_OP2_(bool) ==(subtype const &t)
		XTAL_0FX
		{
			return true;
		}
		///\
		\returns `false`. \

		XTAL_OP2_(bool) !=(subtype const &t)
		XTAL_0FX
		{
			return false;
		}

		XTAL_FN2 tuple()
		XTAL_0FX
		{
			return pack_f();
		}
		using tuple_size = constant_t<(size_t) 0>;

	protected:
		template <typename Y> XTAL_FN2 cast() XTAL_0FX_(&&) {return static_cast<Y const &&>(*this);}
		template <typename Y> XTAL_FN2 cast() XTAL_0EX_(&&) {return static_cast<Y       &&>(*this);}
		template <typename Y> XTAL_FN2 cast() XTAL_0FX_(&)  {return static_cast<Y const  &>(*this);}
		template <typename Y> XTAL_FN2 cast() XTAL_0EX_(&)  {return static_cast<Y        &>(*this);}

		///\
		\returns `this` as a subtype of the derived-type `T`. \

		XTAL_RN4_(XTAL_FN2 self(), cast<T>())

		XTAL_FN2_(T) twin() XTAL_0FX_(&) {return self();}
		XTAL_FN2_(T) twin() XTAL_0EX_(&) {return self();}

		template <size_t N>
		using seek_s = void;

		template <typename Y=T>
		using self_s = _std::conditional_t<is_q<Y, T>, T, void>;
		using self_t = T;

	};
};
////////////////////////////////////////////////////////////////////////////////
namespace _detail
{
template <any_q S>
class refinement: public S
{
	using co = S;
public:
	using co::co;

};
template <any_q S> requires (S::tuple_size::value == 1)
class refinement<S>: public S
{
	using co = S; using U = typename co::head_t;

public:
	using co::co;
	using co::head;

	///\
	Implicit conversion to the singleton kernel-type. \

	XTAL_RN4_(XTAL_NEW operator U(), head())
	
};
}
template <typename T>
struct refine
{
	template <any_q S>
	class subtype: public _detail::refinement<S>
	{
		using co = _detail::refinement<S>;
	public:
		using co::co;

	};

	template <any_q S> requires iterable_q<S>
	class subtype<S>: public _detail::refinement<S>, public iterate_t<T>
	{
		using co = _detail::refinement<S>;
	public:
		using co::co;

	};
};


////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that proxies `U`. \

template <typename U>
struct defer
{
	template <any_q S>
	class subtype: public compose_s<S>
	{
		using co = compose_s<S>; using T = typename co::self_t;

	public:
		using head_t = U;
		using body_t = debased_t<U>;

	protected:
		template <typename Y=T> using self_s = _std::conditional_t<is_q<Y, U>, subtype, typename co::template self_s<Y>>;
		template <size_t   N=0> using seek_s = _std::conditional_t<N == 0,     subtype, typename co::template seek_s<N - 1>>;
		
		body_t body_m;
	//	body_t body_m {};

	public:
		///\
		Chaining constructor: initializes `this` using the first argument, \
		and forwards the rest to super. \

		XTAL_NEW_(explicit) subtype(XTAL_DEF w, XTAL_DEF ...ws)
		XTAL_0EX
		:	co(XTAL_REF_(ws)...)
		,	body_m(member_f<U>(XTAL_REF_(w)))
		{
		}

		XTAL_NEW subtype()
		XTAL_0EX
		XTAL_IF2  {body_t{};}
		:	subtype(body_t{})
		{
		}
		XTAL_CN4_(subtype);
		XTAL_CN2_(subtype);
	//	using co::co;


		XTAL_RN4_(template <typename W=T> XTAL_FN2 self(), co::template cast<self_s<W>>())
		XTAL_RN4_(template <size_t   N=0> XTAL_FN2 seek(), co::template cast<seek_s<N>>())

		XTAL_RN4_(XTAL_FN2 tail(), co::template cast<co>())

		///\
		\returns the kernel-value (prior to reconstruction using the given arguments, if provided). \

		XTAL_RN4_(template <size_t N_index=0>
		XTAL_FN1 head(XTAL_DEF... oo), seek<N_index>().head(XTAL_REF_(oo)...))
		
		XTAL_FN2 head() XTAL_0FX_(&&) {return remember_x(body_m);}
		XTAL_FN2 head() XTAL_0EX_(&&) {return remember_x(body_m);}
		XTAL_FN2 head() XTAL_0FX_( &) {return remember_y(body_m);}
		XTAL_FN2 head() XTAL_0EX_( &) {return remember_y(body_m);}
		
		XTAL_FN1 head(XTAL_DEF o, XTAL_DEF... oo)
		XTAL_0EX
		{
			return head_valve(member_f<U>(XTAL_REF_(o), XTAL_REF_(oo)...));
		}
		XTAL_FN1 head_valve(body_t v)
		XTAL_0EX
		{
			_std::swap(body_m, v); return remember_x(v);
		}
		XTAL_FN1 head_valve(XTAL_DEF w)
		XTAL_0EX
		{
			return co::head_valve(XTAL_REF_(w));
		}

		///\
		Converts `this` to the kernel-type (explicit). \

		XTAL_RN4_(XTAL_NEW explicit operator U(), head())

		XTAL_FN2 apply(XTAL_DEF_(_std::invocable) f)
		XTAL_0FX
		{
			return [f_ = XTAL_REF_(f), this] <size_t ...Ns>(seek_t<Ns...>)
				XTAL_0FN_(f_(head<Ns>()...)) (seek_v<tuple_size::value>);
		}
		
		XTAL_FN2 tuple()
		XTAL_0FX
		{
			return apply(pack_f);
		}
		using tuple_size = constant_t<co::tuple_size::value + 1>;

		///\
		Setter: applied when the template parameter matches the kernel-type. \
		\returns the previous value.

		template <typename W=U>
		XTAL_FN1 set(XTAL_DEF... ws)
		XTAL_0EX
		{
			return self<W>().head(XTAL_REF_(ws)...);
		}
		///\
		Getter: applied when the template parameter matches the kernel-type. \
		\returns the current value.

		template <typename W=U>
		XTAL_FN2 get()
		XTAL_0FX
		{
			return self<W>().head();
		}

		///\
		Membership testing. \
		\returns `true` if the supplied value matches `head`, `false` otherwise. \

		XTAL_FN2_(bool) has(U const &w)
		XTAL_0FX
		{
			U const &u = head();
			if constexpr (requires (U u, U w) {u.operator==(w);})
			{	return u.operator==(w);
			}
			else
			if constexpr (requires (U u, U w) {u == w;})
			{	return u == w;
			}
			else
			if constexpr (iterated_q<U>)
			{	return arranged_eq(u, w);
			}
		}
		
		///\
		Equality testing. \
		\returns `true` if the supplied value matches `this`, `false` otherwise. \

		XTAL_OP2_(bool) == (subtype const &t)
		XTAL_0FX
		{
			return has(t.head()) and co::operator==(static_cast<co const &>(t));
		}

	};
};
////////////////////////////////////////////////////////////////////////////////
namespace _detail
{
template <typename U>
struct comparators
:	compose<>
{
};
template <typename U> requires comparators_p<U>
struct comparators<U>
{
	template <any_q S>
	class subtype: public S
	{
		using co = S;
	public:
		using co::co;
		using co::head;

	//	XTAL_OP2        <=>  (subtype const &t) XTAL_0FX {return head() <=> t.head();}
		XTAL_OP2_(bool) ==   (subtype const &t) XTAL_0FX {return head() ==  t.head();}
		XTAL_OP2_(bool) <=   (subtype const &t) XTAL_0FX {return head() <=  t.head();}
		XTAL_OP2_(bool) >=   (subtype const &t) XTAL_0FX {return head() >=  t.head();}
		XTAL_OP2_(bool) <    (subtype const &t) XTAL_0FX {return head() <   t.head();}
		XTAL_OP2_(bool) >    (subtype const &t) XTAL_0FX {return head() >   t.head();}

	};
};
template <typename U, int N_arity=0>
struct bit_operators
:	compose<>
{
};
template <typename U>
struct bit_operators<U, 0>
:	compose<bit_operators<U, 1>, bit_operators<U, 2>>
{
};
template <typename U> requires bit_operators_p<U, 1> and remember_p<U>
struct bit_operators<U, 1>
{
	template <any_q S>
	class subtype: public S
	{
		using co = S;
	
	protected:
		using co::body_m;

	public:
		using co::co;
		using co::self;
		using co::head;

		XTAL_OP1>>=(XTAL_DEF           i) XTAL_0EX {return body_m>>= (XTAL_REF_(i)), self();}
		XTAL_OP1<<=(XTAL_DEF           i) XTAL_0EX {return body_m<<= (XTAL_REF_(i)), self();}
		XTAL_OP1 %=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m %=U(XTAL_REF_(w)), self();}
		XTAL_OP1 &=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m &=U(XTAL_REF_(w)), self();}
		XTAL_OP1 |=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m |=U(XTAL_REF_(w)), self();}
		XTAL_OP1 ^=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m ^=U(XTAL_REF_(w)), self();}
		XTAL_OP1 +=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m +=U(XTAL_REF_(w)), self();}
		XTAL_OP1 -=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m -=U(XTAL_REF_(w)), self();}

		XTAL_OP1 ++(int) XTAL_0EX {auto  t = self(); ++body_m; return t;}
		XTAL_OP1 --(int) XTAL_0EX {auto  t = self(); --body_m; return t;}
		XTAL_OP1 ++()    XTAL_0EX {auto &s = self(); ++body_m; return s;}
		XTAL_OP1 --()    XTAL_0EX {auto &s = self(); --body_m; return s;}

	};
};
template <typename U> requires bit_operators_p<U, 2>
struct bit_operators<U, 2>
{
	template <any_q S>
	class subtype: public S
	{
		using co = S; using T = typename co::self_t;

	public:
		using co::co;
		using co::head;

		XTAL_OP2>> (XTAL_DEF           i) XTAL_0FX {return T(head() >>  (XTAL_REF_(i)));}
		XTAL_OP2<< (XTAL_DEF           i) XTAL_0FX {return T(head() <<  (XTAL_REF_(i)));}
		XTAL_OP2 % (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(head()  % U(XTAL_REF_(w)));}
		XTAL_OP2 & (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(head()  & U(XTAL_REF_(w)));}
		XTAL_OP2 | (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(head()  | U(XTAL_REF_(w)));}
		XTAL_OP2 ^ (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(head()  ^ U(XTAL_REF_(w)));}
		XTAL_OP2 + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(head()  + U(XTAL_REF_(w)));}
		XTAL_OP2 - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(head()  - U(XTAL_REF_(w)));}

		XTAL_OP2 ~ () XTAL_0FX {return T(~head());}
		XTAL_OP2 - () XTAL_0FX {return T(-head());}

	};
};
template <typename U, int N_arity=0>
struct field_operators
:	compose<>
{
};
template <typename U>
struct field_operators<U, 0>
:	compose<field_operators<U, 1>, field_operators<U, 2>>
{
};
template <typename U> requires field_operators_p<U, 1> and remember_p<U>
struct field_operators<U, 1>
{
	template <any_q S>
	class subtype: public S
	{
		using co = S;

	protected:
		using co::body_m;

	public:
		using co::co;
		using co::self;
		using co::head;

		XTAL_OP1 *=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m *=U(XTAL_REF_(w)), self();}
		XTAL_OP1 /=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m /=U(XTAL_REF_(w)), self();}
		XTAL_OP1 +=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m +=U(XTAL_REF_(w)), self();}
		XTAL_OP1 -=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m -=U(XTAL_REF_(w)), self();}

	};
};
template <typename U> requires field_operators_p<U, 2>
struct field_operators<U, 2>
{
	template <any_q S>
	class subtype: public S
	{
		using co = S; using T = typename co::self_t;
	
	public:
		using co::co;
		using co::head;

		XTAL_OP2 * (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(head() * U(XTAL_REF_(w)));}
		XTAL_OP2 / (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(head() / U(XTAL_REF_(w)));}
		XTAL_OP2 + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(head() + U(XTAL_REF_(w)));}
		XTAL_OP2 - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(head() - U(XTAL_REF_(w)));}

	};
};
template <typename U>
struct range_operators
:	compose<>
{
};
template <typename U> requires iterated_q<U>
struct range_operators<U>
{
	template <any_q S>
	class subtype: public S
	{
		using co = S;

	public:
		using co::co;
		using co::head;

		XTAL_FN2 begin() XTAL_0EX                                    {return head().begin();}
		XTAL_FN2   end() XTAL_0EX                                    {return head().  end();}
		XTAL_FN2 begin() XTAL_0FX XTAL_IF2 (U const &u) {u.begin();} {return head().begin();}
		XTAL_FN2   end() XTAL_0FX XTAL_IF2 (U const &u) {u.  end();} {return head().  end();}

	};
	template <any_q S> requires iterated_q<S> or iterable_q<S>
	class subtype<S>: public S
	{
		using co = S;
	public:
		using co::co;

	};
};
}
///\
Produces a decorator `subtype<S>` that lifts the operations of `U`. \

template <typename U>
struct refer
:	compose<any<>
	,	_detail::     comparators<U>
	,	_detail::   bit_operators<U>
	,	_detail:: field_operators<U>
	,	_detail:: range_operators<U>
	>
{
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::content::any_q T> requires (0 < T::tuple_size::value)
struct tuple_size<T>: xtal::constant_t<(size_t) T::tuple_size::value> {};

template <size_t N, xtal::content::any_q T> requires (0 < T::tuple_size::value)
struct tuple_element<N, T> {using type = XTAL_TYP_(XTAL_VAL_(T).template head<N>());};

template <size_t N, xtal::content::any_q T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T const &&t) {return ::std::move(t).template head<N>();};

template <size_t N, xtal::content::any_q T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T       &&t) {return ::std::move(t).template head<N>();};

template <size_t N, xtal::content::any_q T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T const  &t) {return t.template head<N>();};

template <size_t N, xtal::content::any_q T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T        &t) {return t.template head<N>();};

}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
