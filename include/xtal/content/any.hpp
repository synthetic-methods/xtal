#pragma once
#include "../common/any.hpp"//_retail






XTAL_ENV_(push)
namespace xtal::content
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::common;
#include "../common/any.hxx"

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <any_q S>
class morphotype: public S
{
	using co = S;
public:
	using co::co;

};
template <any_q S> requires (S::cardinal::value == 1)
class morphotype<S>: public S
{
	using co = S;
public:
	using co::co;
	using co::head;
	using typename co::head_t;

	///\
	Implicit conversion to the singleton kernel-type. \

	XTAL_RE4_(XTAL_NEW operator head_t(), head())
	
};

}/////////////////////////////////////////////////////////////////////////////


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
		\returns `this` as a subtype of the derived-type `T`. \
&
		XTAL_FN2_(T const &&) self() XTAL_0FX_(&&) {return static_cast<T const &&>(*this);}
		XTAL_FN2_(T       &&) self() XTAL_0EX_(&&) {return static_cast<T       &&>(*this);}
		
		XTAL_FN2_(T const &) self() XTAL_0FX_(&) {return static_cast<T const &>(*this);}
		XTAL_FN2_(T       &) self() XTAL_0EX_(&) {return static_cast<T       &>(*this);}
		
		XTAL_FN2_(T) twin() XTAL_0FX_(&) {return self();}
		XTAL_FN2_(T) twin() XTAL_0EX_(&) {return self();}

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

		using cardinal = constant<(size_t) 0>;

	protected:
		using self_t = T;

	};
};

template <typename T>
struct refine
{
	template <any_q S>
	class subtype: public _detail::morphotype<S>
	{
		using co = _detail::morphotype<S>;
	public:
		using co::co;

	};

	template <any_q S> requires iterable_q<S>
	class subtype<S>: public _detail::morphotype<S>, public iterate_t<T>
	{
		using co = _detail::morphotype<S>;
	public:
		using co::co;

	};
};

////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that proxies `U`. \

template <typename T>
concept defer_q = requires (T t)
{
	t.head();
};
template <typename U>
struct defer
{
	template <any_q S>
	class subtype: public common::compose_s<S>
	{
		using co = common::compose_s<S>; using T = typename co::self_t;
		using V  = debased_t<U>;

	protected:
		XTAL_FZ2 lvalue(XTAL_DEF    w ) XTAL_0EX                       {return  XTAL_REF_(w);}
		XTAL_FZ2 lvalue(XTAL_DEF    w ) XTAL_0EX requires debased_q<U> {return *XTAL_REF_(w);}

		XTAL_FZ2 rvalue(XTAL_DEF    w ) XTAL_0EX                       {return  _std::move(XTAL_REF_(w));}
		XTAL_FZ2 rvalue(XTAL_DEF    w ) XTAL_0EX requires debased_q<U> {return *_std::move(XTAL_REF_(w));}

		XTAL_FZ2 mvalue(XTAL_DEF ...ws) XTAL_0EX                       {return V(XTAL_REF_(ws)...);}
		XTAL_FZ2 mvalue(XTAL_DEF    w ) XTAL_0EX requires debased_q<U> {return _std::addressof(XTAL_REF_(w));}

		using head_t = U;
		using body_t = V;
		body_t body_m;
	//	body_t body_m {};

	public:
//	using co::co;

		template <typename W=void>
		XTAL_FN2 node()
		XTAL_0EX_(&)
		{
			if constexpr (is_q<W, void>)
			{	return co::self();
			}
			else
			if constexpr (is_q<W, U>)
			{	return *this;
			}
			else
			{	return co::template node<W>();
			}
		}
		template <typename W=void>
		XTAL_FN2 node()
		XTAL_0FX_(&)
		{
			if constexpr (is_q<W, void>)
			{	return co::self();
			}
			else
			if constexpr (is_q<W, U>)
			{	return *this;
			}
			else
			{	return co::template node<W>();
			}
		}

		template <size_t N_index=0>
		XTAL_FN2 seek()
		XTAL_0EX_(&)
		{
			if constexpr (0 == N_index)
			{	return *this;
			}
			else
			if constexpr (1 <= N_index)
			{	return co::template seek<N_index - 1>();
			}
		}
		template <size_t N_index=0>
		XTAL_FN2 seek()
		XTAL_0FX_(&)
		{
			if constexpr (0 == N_index)
			{	return *this;
			}
			else
			if constexpr (1 <= N_index)
			{	return co::template seek<N_index - 1>();
			}
		}

		///\
		Resolves `this` as the super-type. \

		XTAL_FN2 tail() XTAL_0FX_( &) requires defer_q<co> {return static_cast<co const  &>(*this);}
		XTAL_FN2 tail() XTAL_0EX_( &) requires defer_q<co> {return static_cast<co        &>(*this);}
		XTAL_FN2 tail() XTAL_0FX_(&&) requires defer_q<co> {return static_cast<co const &&>(*this);}
		XTAL_FN2 tail() XTAL_0EX_(&&) requires defer_q<co> {return static_cast<co       &&>(*this);}

		///\
		\returns the kernel-value (prior to reconstruction using the given arguments, if provided). \

		template <size_t N_index=0> XTAL_FN1 head(XTAL_DEF... oo) XTAL_0EX_(&&) {return seek<N_index>().head(XTAL_REF_(oo)...);}
		template <size_t N_index=0> XTAL_FN1 head(XTAL_DEF... oo) XTAL_0FX_(&&) {return seek<N_index>().head(XTAL_REF_(oo)...);}
		template <size_t N_index=0> XTAL_FN1 head(XTAL_DEF... oo) XTAL_0EX_( &) {return seek<N_index>().head(XTAL_REF_(oo)...);}
		template <size_t N_index=0> XTAL_FN1 head(XTAL_DEF... oo) XTAL_0FX_( &) {return seek<N_index>().head(XTAL_REF_(oo)...);}
		
		XTAL_FN2 head() XTAL_0EX_(&&) {return rvalue(body_m);}
		XTAL_FN2 head() XTAL_0FX_(&&) {return rvalue(body_m);}
		XTAL_FN2 head() XTAL_0EX_( &) {return lvalue(body_m);}
		XTAL_FN2 head() XTAL_0FX_( &) {return lvalue(body_m);}
		XTAL_FN1 head(XTAL_DEF o, XTAL_DEF... oo)
		XTAL_0EX
		{
			auto m = mvalue(XTAL_REF_(o), XTAL_REF_(oo)...); _std::swap(body_m, m);
			return rvalue(_std::move(m));
		}

		///\
		Converts `this` to the kernel-type (explicit). \

		XTAL_RE4_(XTAL_NEW explicit operator U(), head())

		///\
		Default construction/destruction. \

		XTAL_CO4_(subtype);
		XTAL_CO2_(subtype);

		XTAL_NEW subtype()
		XTAL_0EX
		requires
		requires
		{
			body_t{};
		}
		:	subtype(body_t{})
		{
		}
		
		///\
		Deferred constructor: initializes `head` \
		then forwards the remaining arguments to the super-constructor. \

		XTAL_NEW_(explicit) subtype(XTAL_DEF w, XTAL_DEF ...ws)
		XTAL_0EX
		:	co(XTAL_REF_(ws)...)
		,	body_m(mvalue(XTAL_REF_(w)))
		{
		}

		///\
		Setter: applied when the template parameter matches the kernel-type. \
		\returns the previous value.

		template <typename W=U>
		XTAL_FN2 set(XTAL_DEF... ws)
		XTAL_0FX
		{
			return node<based_t<W>>().head(XTAL_REF_(ws)...);
		}
		///\
		Getter: applied when the template parameter matches the kernel-type. \
		\returns the current value.

		template <typename W=U>
		XTAL_FN2 get()
		XTAL_0FX
		{
			return node<based_t<W>>().head();
		}

		///\
		Membership testing. \
		\returns `true` if the supplied value matches `head`, `false` otherwise. \

		XTAL_FN2_(bool) has(U const &w)
		XTAL_0FX
		{
			U const &u = head();
			if constexpr (requires (U u, U w) {u.operator==(w);})
			{
				return u.operator==(w);
			}
			else
			if constexpr (requires (U u, U w) {u == w;})
			{
				return u == w;
			}
			else
			if constexpr (iterated_q<U>)
			{
				return u.begin() == w.begin() and u.end() == w.end();
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
		

		using cardinal = constant<co::cardinal::value + 1>;

	};
};
////////////////////////////////////////////////////////////////////////////////
namespace _detail
{
	template <typename U>
	struct comparators
	:	common::compose<>
	{
	};
	template <typename U>
	requires comparators_p<U>
	struct comparators<U>
	{
		template <any_q S>
		class subtype: public S
		{
			using co = S; using T = subtype<S>;//typename co::self_t;
		public:
			using co::co;
			using co::self;
			using co::head;
			using co::body_m;

		//	XTAL_OP2        <=>  (subtype const &t) XTAL_0FX {return   head() <=> t.head();}
			XTAL_OP2_(bool) ==   (subtype const &t) XTAL_0FX {return   head() ==  t.head();}
			XTAL_OP2_(bool) <=   (subtype const &t) XTAL_0FX {return   head() <=  t.head();}
			XTAL_OP2_(bool) >=   (subtype const &t) XTAL_0FX {return   head() >=  t.head();}
			XTAL_OP2_(bool) <    (subtype const &t) XTAL_0FX {return   head() <   t.head();}
			XTAL_OP2_(bool) >    (subtype const &t) XTAL_0FX {return   head() >   t.head();}

		};
	};

	template <typename U, int N_arity=0>
	struct bit_operators
	:	common::compose<>
	{
	};
	template <typename U>
	struct bit_operators<U, 0>
	:	common::compose<bit_operators<U, 1>, bit_operators<U, 2>>
	{
	};
	template <typename U>
	requires bit_operators_p<U, 1>
	struct bit_operators  <U, 1>
	{
		template <any_q S>
		class subtype: public S
		{
			using co = S; using T = subtype<S>;//typename co::self_t;
		public:
			using co::co;
			using co::self;
			using co::head;
			using co::body_m;

			XTAL_OP1>>=(XTAL_DEF           i) XTAL_0EX {return   body_m>>= (XTAL_REF_(i)), self();}
			XTAL_OP1<<=(XTAL_DEF           i) XTAL_0EX {return   body_m<<= (XTAL_REF_(i)), self();}
			XTAL_OP1 %=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m %=U(XTAL_REF_(w)), self();}
			XTAL_OP1 &=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m &=U(XTAL_REF_(w)), self();}
			XTAL_OP1 |=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m |=U(XTAL_REF_(w)), self();}
			XTAL_OP1 ^=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m ^=U(XTAL_REF_(w)), self();}
			XTAL_OP1 +=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m +=U(XTAL_REF_(w)), self();}
			XTAL_OP1 -=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m -=U(XTAL_REF_(w)), self();}

			XTAL_OP1 ++(int)                  XTAL_0EX {auto r = self(); ++body_m; return r;}
			XTAL_OP1 --(int)                  XTAL_0EX {auto r = self(); --body_m; return r;}
			XTAL_OP1 ++()                     XTAL_0EX {auto&s = self(); ++body_m; return s;}
			XTAL_OP1 --()                     XTAL_0EX {auto&s = self(); --body_m; return s;}

		};
	};
	template <typename U>
	requires bit_operators_p<U, 2>
	struct bit_operators  <U, 2>
	{
		template <any_q S>
		class subtype: public S
		{
			using co = S; using T = subtype<S>;//typename co::self_t;
		public:
			using co::co;
			using co::self;
			using co::head;
			using co::body_m;

			XTAL_OP2>> (XTAL_DEF           i) XTAL_0FX {return T(body_m>>  (XTAL_REF_(i)));}
			XTAL_OP2<< (XTAL_DEF           i) XTAL_0FX {return T(body_m<<  (XTAL_REF_(i)));}
			XTAL_OP2 % (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m % U(XTAL_REF_(w)));}
			XTAL_OP2 & (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m & U(XTAL_REF_(w)));}
			XTAL_OP2 | (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m | U(XTAL_REF_(w)));}
			XTAL_OP2 ^ (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m ^ U(XTAL_REF_(w)));}
			XTAL_OP2 + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m + U(XTAL_REF_(w)));}
			XTAL_OP2 - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m - U(XTAL_REF_(w)));}

			XTAL_OP2 ~ ()                     XTAL_0FX {return T(~body_m);}
			XTAL_OP2 - ()                     XTAL_0FX {return T(-body_m);}

		};
	};

	template <typename U, int N_arity=0>
	struct field_operators
	:	common::compose<>
	{
	};
	template <typename U>
	struct field_operators<U, 0>
	:	common::compose<field_operators<U, 1>, field_operators<U, 2>>
	{
	};
	template <typename U>
	requires field_operators_p<U, 1>
	struct field_operators  <U, 1>
	{
		template <any_q S>
		class subtype: public S
		{
			using co = S; using T = subtype<S>;//typename co::self_t;
		public:
			using co::co;
			using co::self;
			using co::head;
			using co::body_m;

			XTAL_OP1_(T&) *=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m *=U(XTAL_REF_(w)), self();}
			XTAL_OP1_(T&) /=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m /=U(XTAL_REF_(w)), self();}
			XTAL_OP1_(T&) +=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m +=U(XTAL_REF_(w)), self();}
			XTAL_OP1_(T&) -=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m -=U(XTAL_REF_(w)), self();}

		};
	};
	template <typename U>
	requires field_operators_p<U, 2>
	struct field_operators  <U, 2>
	{
		template <any_q S>
		class subtype: public S
		{
			using co = S; using T = subtype<S>;//typename co::self_t;
		public:
			using co::co;
			using co::self;
			using co::head;
			using co::body_m;

			XTAL_OP2_(T ) * (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m * U(XTAL_REF_(w)));}
			XTAL_OP2_(T ) / (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m / U(XTAL_REF_(w)));}
			XTAL_OP2_(T ) + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m + U(XTAL_REF_(w)));}
			XTAL_OP2_(T ) - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m - U(XTAL_REF_(w)));}

		};
	};

	template <typename U>
	struct range_operators
	:	common::compose<>
	{
	};
	template <typename U>
	requires iterated_q<U>
	struct range_operators<U>
	{
		template <any_q S>
		class subtype: public S
		{
			using co = S; using T = subtype<S>;//typename co::self_t;
		public:
			using co::co;
			using co::self;
			using co::head;
			using co::body_m;

			XTAL_FN2 begin() XTAL_0EX                                             {return head().begin();}
			XTAL_FN2   end() XTAL_0EX                                             {return head().  end();}
			XTAL_FN2 begin() XTAL_0FX requires requires (U const &u) {u.begin();} {return head().begin();}
			XTAL_FN2   end() XTAL_0FX requires requires (U const &u) {u.  end();} {return head().  end();}

		};
		template <any_q S>
		requires iterated_q<S> or iterable_q<S>
		class subtype<S>: public S
		{
			using co = S; using T = subtype<S>;//typename co::self_t;
		public:
			using co::co;

		};
	};
}

///\
Produces a decorator `subtype<S>` that lifts the operations of `U`. \

template <typename U>
struct refer
:	common::compose<any<>
	,	_detail::     comparators<U>
	,	_detail::   bit_operators<U>
	,	_detail:: field_operators<U>
	,	_detail:: range_operators<U>
	>
{
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/*/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::content::any_q T> requires (0 < T::cardinal::value)
struct tuple_size<T>: xtal::constant<(size_t) T::cardinal::value> {};

template <size_t N, xtal::content::any_q T> requires (0 < T::cardinal::value)
struct tuple_element<N, T> {using type = XTAL_TYP_(XTAL_VAL_(T).head());};

template <size_t N, xtal::content::any_q T> requires (0 < T::cardinal::value)
XTAL_FN1 get(T const &&t) {return move(t).template head<N>();};

template <size_t N, xtal::content::any_q T> requires (0 < T::cardinal::value)
XTAL_FN1 get(T       &&t) {return move(t).template head<N>();};

template <size_t N, xtal::content::any_q T> requires (0 < T::cardinal::value)
XTAL_FN1 get(T const  &t) {return t.template head<N>();};

template <size_t N, xtal::content::any_q T> requires (0 < T::cardinal::value)
XTAL_FN1 get(T        &t) {return t.template head<N>();};

}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
