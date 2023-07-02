#pragma once
#include "../common/all.hpp"// referenced in `any.hxx`






XTAL_ENV_(push)
namespace xtal::concord
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail
{///////////////////////////////////////////////////////////////////////////////
///\
Creates a unique `subtype<S>` tagged by the given `As...`, \
such that e.g. `std::derives_from<any<struct x, struct xs...>, any<struct xs...>>`. \

template <typename ...As>
struct any
{
	using subkind = common::compose<any<As>...>;

	template <typename S>
	using subtype = typename subkind::template subtype<S>;

};
template <typename A>
struct any<A>
{
	template <typename S>
	class subtype: public S
	{
	public:
		using S::S;

	};
};


}///////////////////////////////////////////////////////////////////////////////

#include "./any.hxx"


////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct define
{
	template <any_p S>
	class subtype: public S
	{
	public:
		using S::S;
		
		XTAL_CXN subtype(XTAL_DEF... oo)
		:	S(XTAL_REF_(oo)...)
		{
		}

		XTAL_OP2_(bool) ==(subtype const &t) XTAL_0FX {return 1;}///<\returns `true`.
		XTAL_OP2_(bool) !=(subtype const &t) XTAL_0FX {return 0;}///<\returns `false`.

		XTAL_DO4_(XTAL_OP0 _std::tuple<>(), tuple())
		
		XTAL_FN2 tuple() XTAL_0FX {return bundle_f();}

		using tuple_size = constant_t<(size_t) 0>;

		
		///\returns `this` as the `define`d supertype.. \

		XTAL_DO4_(XTAL_FN2 parent(), S::self())

		///\returns `this` as a subtype of the derived-type `T`. \

		XTAL_DO4_(XTAL_FN2 self(), cast<T>())

		XTAL_FN2_(T) twin() XTAL_0FX_(&) {return self();}
		XTAL_FN2_(T) twin() XTAL_0EX_(&) {return self();}

	protected:
		template <typename Y> XTAL_FN2 cast() XTAL_0FX_(&&) {return static_cast<Y const &&>(XTAL_MOV_(*this));}
		template <typename Y> XTAL_FN2 cast() XTAL_0EX_(&&) {return static_cast<Y       &&>(XTAL_MOV_(*this));}
		template <typename Y> XTAL_FN2 cast() XTAL_0FX_(&)  {return static_cast<Y const  &>(*this);}
		template <typename Y> XTAL_FN2 cast() XTAL_0EX_(&)  {return static_cast<Y        &>(*this);}
		
		using self_t = T;

	};
};
////////////////////////////////////////////////////////////////////////////////
namespace _detail
{
struct refine_as_head
{
	template <any_p S>
	class subtype: public S
	{
	public:
		using S::S;

	};
	template <any_p S> requires (S::tuple_size::value == 1)
	class subtype<S>: public S
	{
		using U = typename S::head_t;

	public:
		using S::S;
		using S::head;

		///\
		Implicit conversion to the singleton kernel-type. \

		XTAL_DO4_(XTAL_OP0 U(), head())
		
	};
};
struct refine_as_tuple
{
	template <any_p S>
	class subtype: public S
	{
	public:
		using S::S;

		using tuple_type = XTAL_TYP_(XTAL_VAL_(S).tuple());
		XTAL_DO4_(XTAL_OP0 tuple_type(), S::tuple())

	};
};
}
template <typename T>
struct refine
{
	using subkind = compose<any<>
	,	_detail::refine_as_head
	,	_detail::refine_as_tuple
	>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

	};
	template <any_p S> requires iterable_q<S>
	class subtype<S>: public compose_s<S, subkind>, public iterate_t<T>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

	};
};


namespace _detail
{//////////////////////////////////////////////////////////////////////////////

template <typename T> concept dismember_p =     debased_q<T>;// determine whether `T` should be dereferenced
template <typename T> concept  remember_p = not debased_q<T>;
template <typename T> using      member_t =     debased_t<T>;// convert references to pointers

template <typename T>   XTAL_CN2 member_f(XTAL_DEF w)     XTAL_0EX XTAL_REQ dismember_p<T> {return &XTAL_REF_(w);}// obtain address
template <typename T>   XTAL_CN2 member_f(XTAL_DEF w)     XTAL_0EX {return to_f<T>(XTAL_REF_(w));}
template <typename T>   XTAL_CN2 member_f(XTAL_DEF ...ws) XTAL_0EX {return to_f<T>(XTAL_REF_(ws)...);}

XTAL_CN2 remember_y(XTAL_DEF w) XTAL_0EX XTAL_REQ_(*w) {return *XTAL_REF_(w);}// dereference address
XTAL_CN2 remember_y(XTAL_DEF w) XTAL_0EX               {return  XTAL_REF_(w);}

XTAL_CN2 remember_x(XTAL_DEF w) XTAL_0EX XTAL_REQ_(*w) {return *XTAL_MOV_(XTAL_REF_(w));}// dereference address
XTAL_CN2 remember_x(XTAL_DEF w) XTAL_0EX               {return  XTAL_MOV_(XTAL_REF_(w));}



}//////////////////////////////////////////////////////////////////////////////

template <typename U>
struct defer
{
	template <any_p S>
	class subtype: public compose_s<S>
	{
		using S_ = compose_s<S>;
		using T_ = typename S_::self_t;
		using V  = debased_t<U>;

	protected:
	//	NOTE: The redundant parameter `X` allows GCC to handle nested specialization... \
	
		template <typename X, typename Y> struct superself        {using type = typename S::template self_s<Y>;};
		template <typename X            > struct superself<X, T_> {using type = T_ ;};
		template <typename X            > struct superself<X, U > {using type = X  ;};

		template <typename X, size_t   N> struct superseek        {using type = typename S::template seek_s<N - 1>;};
		template <typename X            > struct superseek<X, 0 > {using type = X  ;};

		template <typename Y=T_> using self_s = typename superself<subtype<S>, Y>::type;
		template <size_t   N=0 > using seek_s = typename superseek<subtype<S>, N>::type;

		V body_m;
	//	V body_m {};

	public:
	//	using S_::S_;
		using body_t = V;
		using head_t = U;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);

		///\
		Chaining constructor: initializes `this` using the first argument, \
		and forwards the rest to super. \

		XTAL_CXN subtype(XTAL_DEF w, XTAL_DEF ...ws)
		XTAL_0EX
		:	S_(XTAL_REF_(ws)...)
		,	body_m(_detail::member_f<U>(XTAL_REF_(w)))
		{
		}

		XTAL_CON subtype()
		XTAL_0EX
		XTAL_REQ_(body_t{})
		:	subtype(body_t{})
		{
		}

		XTAL_DO4_(template <typename W=T_> XTAL_FN2 self(), S_::template cast<self_s<W>>())
		XTAL_DO4_(template <size_t   N=0 > XTAL_FN2 seek(), S_::template cast<seek_s<N>>())

		///\returns the kernel-value (prior to reconstruction using the given arguments, if provided). \

		XTAL_DO4_(template <size_t N_index=0>
		XTAL_FN1 head(XTAL_DEF... oo), seek<N_index>().head(XTAL_REF_(oo)...)
		)
		XTAL_FN2 head() XTAL_0FX_(&&) {return _detail::remember_x(body_m);}
		XTAL_FN2 head() XTAL_0EX_(&&) {return _detail::remember_x(body_m);}
		XTAL_FN2 head() XTAL_0FX_( &) {return _detail::remember_y(body_m);}
		XTAL_FN2 head() XTAL_0EX_( &) {return _detail::remember_y(body_m);}
		
		XTAL_FN1 head(XTAL_DEF o, XTAL_DEF... oo)
		XTAL_0EX
		{
			return heady(_detail::member_f<U>(XTAL_REF_(o), XTAL_REF_(oo)...));
		}
		XTAL_FN1 heady(body_t v)
		XTAL_0EX
		XTAL_REQ _detail::remember_p<U>
		{
			_std::swap(body_m, v); return _detail::remember_x(v);
		}

		///\
		Converts `this` to the kernel-type (explicit). \

		XTAL_DO4_(XTAL_OP1_(explicit) U(), head())

		XTAL_FN2 apply(XTAL_DEF_(_std::invocable) f)
		XTAL_0FX
		{
			return [this, g = XTAL_REF_(f)] <size_t ...I>(seek_t<I...>)
				XTAL_0FN_(g(head<I>()...)) (seek_v<tuple_size::value>);
		}
		
		XTAL_FN2 tuple()
		XTAL_0FX
		{
			return apply(bundle_f);
		}
		using tuple_size = constant_t<S_::tuple_size::value + 1>;
		
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
			if constexpr (requires {u.operator==(w);}) {
				return u.operator==(w);
			}
			else if constexpr (requires {u == w;}) {
				return u == w;
			}
			else if constexpr (iterated_q<U>) {
				return u.begin() == w.begin() and u.end() == w.end();
			}
		}
		
		///\
		Equality testing. \
		\returns `true` if the supplied value matches `this`, `false` otherwise. \

		XTAL_OP2_(bool) == (subtype const &t)
		XTAL_0FX
		{
			return has(t.head()) and S_::operator==(static_cast<S_ const &>(t));
		}

	};
};
////////////////////////////////////////////////////////////////////////////////
namespace _detail
{
template <typename U>
struct refer_to_comparators
:	compose<>
{
};
template <typename U> requires comparators_p<U>
struct refer_to_comparators<U>
{
	template <any_p S>
	class subtype: public S
	{
	public:
		using S::S;
		using S::head;

	//	XTAL_OP2        <=> (subtype const &t) XTAL_0FX {return head() <=> t.head();}
		XTAL_OP2_(bool) ==  (subtype const &t) XTAL_0FX {return head() ==  t.head();}
		XTAL_OP2_(bool) <=  (subtype const &t) XTAL_0FX {return head() <=  t.head();}
		XTAL_OP2_(bool) >=  (subtype const &t) XTAL_0FX {return head() >=  t.head();}
		XTAL_OP2_(bool) <   (subtype const &t) XTAL_0FX {return head() <   t.head();}
		XTAL_OP2_(bool) >   (subtype const &t) XTAL_0FX {return head() >   t.head();}

	};
};
template <typename U, int N_arity=0>
struct refer_to_logic_operators
:	compose<>
{
};
template <typename U>
struct refer_to_logic_operators<U, 0>
:	compose<refer_to_logic_operators<U, 1>, refer_to_logic_operators<U, 2>>
{
};
template <typename U> requires logic_operators_p<U, 1> and _detail::remember_p<U>
struct refer_to_logic_operators<U, 1>
{
	template <any_p S>
	class subtype: public S
	{
	protected:
		using S::body_m;

	public:
		using S::S;
		using S::self;
		using S::head;

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
template <typename U> requires logic_operators_p<U, 2>
struct refer_to_logic_operators<U, 2>
{
	template <any_p S>
	class subtype: public S
	{
		using T_ = typename S::self_t;

	public:
		using S::S;
		using S::head;

		XTAL_OP2>> (XTAL_DEF           i) XTAL_0FX {return T_(head() >>  (XTAL_REF_(i)));}
		XTAL_OP2<< (XTAL_DEF           i) XTAL_0FX {return T_(head() <<  (XTAL_REF_(i)));}
		XTAL_OP2 % (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(head()  % U(XTAL_REF_(w)));}
		XTAL_OP2 & (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(head()  & U(XTAL_REF_(w)));}
		XTAL_OP2 | (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(head()  | U(XTAL_REF_(w)));}
		XTAL_OP2 ^ (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(head()  ^ U(XTAL_REF_(w)));}
		XTAL_OP2 + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(head()  + U(XTAL_REF_(w)));}
		XTAL_OP2 - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(head()  - U(XTAL_REF_(w)));}

		XTAL_OP2 ~ () XTAL_0FX {return T_(~head());}
		XTAL_OP2 - () XTAL_0FX {return T_(-head());}

	};
};
template <typename U, int N_arity=0>
struct refer_to_arithmetic_operators
:	compose<>
{
};
template <typename U>
struct refer_to_arithmetic_operators<U, 0>
:	compose<refer_to_arithmetic_operators<U, 1>, refer_to_arithmetic_operators<U, 2>>
{
};
template <typename U> requires arithmetic_operators_p<U, 1> and _detail::remember_p<U>
struct refer_to_arithmetic_operators<U, 1>
{
	template <any_p S>
	class subtype: public S
	{
	protected:
		using S::body_m;

	public:
		using S::S;
		using S::self;
		using S::head;

		XTAL_OP1 *=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m *=U(XTAL_REF_(w)), self();}
		XTAL_OP1 /=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m /=U(XTAL_REF_(w)), self();}
		XTAL_OP1 +=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m +=U(XTAL_REF_(w)), self();}
		XTAL_OP1 -=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return body_m -=U(XTAL_REF_(w)), self();}

	};
};
template <typename U> requires arithmetic_operators_p<U, 2>
struct refer_to_arithmetic_operators<U, 2>
{
	template <any_p S>
	class subtype: public S
	{
		using T_ = typename S::self_t;
	
	public:
		using S::S;
		using S::head;

		XTAL_OP2 * (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(head() * U(XTAL_REF_(w)));}
		XTAL_OP2 / (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(head() / U(XTAL_REF_(w)));}
		XTAL_OP2 + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(head() + U(XTAL_REF_(w)));}
		XTAL_OP2 - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(head() - U(XTAL_REF_(w)));}

	};
};
template <typename U>
struct refer_to_range_operators
:	compose<>
{
};
template <typename U> requires iterated_q<U>
struct refer_to_range_operators<U>
{
	template <any_p S>
	class subtype: public S
	{
		using U_ = U const &;

	public:
		using S::S;
		using S::head;

		XTAL_FN2 begin() XTAL_0EX                                  {return head().begin();}
		XTAL_FN2   end() XTAL_0EX                                  {return head().  end();}
		XTAL_FN2 begin() XTAL_0FX XTAL_REQ_(XTAL_VAL_(U_).begin()) {return head().begin();}
		XTAL_FN2   end() XTAL_0FX XTAL_REQ_(XTAL_VAL_(U_).  end()) {return head().  end();}

	};
	template <any_p S> requires iterated_q<S> or iterable_q<S>
	class subtype<S>: public S
	{
	public:
		using S::S;

	};
};
}
template <typename U>
struct refer
:	compose<any<>
	,	_detail::refer_to_comparators<U>
	,	_detail::refer_to_logic_operators<U>
	,	_detail::refer_to_arithmetic_operators<U>
	,	_detail::refer_to_range_operators<U>
	>
{
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::concord::any_p T> requires (0 < T::tuple_size::value)
struct tuple_size<T>: xtal::constant_t<(size_t) T::tuple_size::value> {};

template <size_t N, xtal::concord::any_p T> requires (0 < T::tuple_size::value)
struct tuple_element<N, T> {using type = XTAL_TYP_(XTAL_VAL_(T).template head<N>());};

template <size_t N, xtal::concord::any_p T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T const &&t) {return std::move(t).template head<N>();};

template <size_t N, xtal::concord::any_p T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T       &&t) {return std::move(t).template head<N>();};

template <size_t N, xtal::concord::any_p T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T const  &t) {return t.template head<N>();};

template <size_t N, xtal::concord::any_p T> requires (0 < T::tuple_size::value)
XTAL_FN1 get(T        &t) {return t.template head<N>();};

}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
