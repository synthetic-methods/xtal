#pragma once
#include "../common/any.hpp"//_detail






XTAL_ENV_(push)
namespace xtal::content
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail = xtal::common;
#include "../common/any.ipp"

////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct define
{
	template <any_q S>
	class subtype: public S
	{
		using co = S;

	protected:
		using self_t = T;

	public:
		using co::co;
		
		///\
		\returns `this` as a subtype of the derived-type `T`. \

		XTAL_FN2 self() XTAL_0FX_(&) {return static_cast<T const &>(*this);}
		XTAL_FN2 self() XTAL_0EX_(&) {return static_cast<T       &>(*this);}
		
		XTAL_FN2 twin() XTAL_0FX_(&) {auto t = self(); return t;}
		XTAL_FN2 twin() XTAL_0EX_(&) {auto t = self(); return t;}

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

	};
};
////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct refine
{
	template <any_q S>
	class subtype: public S
	{
		using co = S;
	public:
		using co::co;

	};

	template <any_q S>
	requires iterable_q<S>
	class subtype<S>: public S, public iterate_t<T>
	{
		using co = S;
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
		using V  = debased_t<U>;

	protected:
		XTAL_FZ2 member_f(XTAL_DEF ...ws) XTAL_0EX                       {return V(XTAL_REF_(ws)...);}
		XTAL_FZ2 member_f(XTAL_DEF    w ) XTAL_0EX requires debased_q<U> {return _std::addressof(XTAL_REF_(w));}

		XTAL_FZ2 member_x(XTAL_DEF    w ) XTAL_0EX                       {return  XTAL_REF_(w);}
		XTAL_FZ2 member_x(XTAL_DEF    w ) XTAL_0EX requires debased_q<U> {return *XTAL_REF_(w);}

		XTAL_FZ2 member_y(XTAL_DEF    w ) XTAL_0EX                       {return  _std::move(XTAL_REF_(w));}
		XTAL_FZ2 member_y(XTAL_DEF    w ) XTAL_0EX requires debased_q<U> {return *_std::move(XTAL_REF_(w));}

		using head_t = U;
		using body_t = V;
		body_t body_m;
	//	body_t body_m {};

	public:
//	using co::co;

		///\
		Resolves `this` as the super-type. \

		XTAL_FN2 tail() XTAL_0FX_( &) {return static_cast<co const  &>(*this);}
		XTAL_FN2 tail() XTAL_0EX_( &) {return static_cast<co        &>(*this);}
		XTAL_FN2 tail() XTAL_0FX_(&&) {return static_cast<co const &&>(*this);}
		XTAL_FN2 tail() XTAL_0EX_(&&) {return static_cast<co       &&>(*this);}

		///\
		\returns the kernel-value (prior to reconstruction using the given arguments, if provided). \

		template <sigma_t N_index=0> XTAL_FN1 head(XTAL_DEF... oo) XTAL_0EX_(&&) {return co::template head<N_index - 1>(XTAL_REF_(oo)...);}
		template <sigma_t N_index=0> XTAL_FN1 head(XTAL_DEF... oo) XTAL_0FX_(&&) {return co::template head<N_index - 1>(XTAL_REF_(oo)...);}
		template <sigma_t N_index=0> XTAL_FN1 head(XTAL_DEF... oo) XTAL_0EX_( &) {return co::template head<N_index - 1>(XTAL_REF_(oo)...);}
		template <sigma_t N_index=0> XTAL_FN1 head(XTAL_DEF... oo) XTAL_0FX_( &) {return co::template head<N_index - 1>(XTAL_REF_(oo)...);}
		
		template <sigma_t N_index=0> requires (0 == N_index) XTAL_FN2 head() XTAL_0EX_(&&) {return member_y(body_m);}
		template <sigma_t N_index=0> requires (0 == N_index) XTAL_FN2 head() XTAL_0FX_(&&) {return member_y(body_m);}
		template <sigma_t N_index=0> requires (0 == N_index) XTAL_FN2 head() XTAL_0EX_( &) {return member_x(body_m);}
		template <sigma_t N_index=0> requires (0 == N_index) XTAL_FN2 head() XTAL_0FX_( &) {return member_x(body_m);}
		
		template <sigma_t N_index=0>
		requires (0 == N_index)
		XTAL_FN1 head(XTAL_DEF o, XTAL_DEF... oo)
		XTAL_0EX
		{
			U u = head(); body_m = member_f(XTAL_REF_(o), XTAL_REF_(oo)...);
			return u;
		}

		///\
		Converts `this` to the kernel-type (explicit). \

		XTAL_RE4_(XTAL_NEW explicit operator U(), head())

		///\
		Default construction/destruction. \

		XTAL_CO4_(subtype);
		XTAL_CO2_(subtype);

		///\
		Deferred constructor: initializes `head` \
		then forwards the remaining arguments to the super-constructor. \

		XTAL_NEW subtype(XTAL_DEF ...ws)
		XTAL_0EX
		:	co(XTAL_REF_(ws)...)
		{
		}
		///\
		Deferred constructor: constructs `head` using the first argument \
		then forwards the remaining arguments to the super-constructor. \
		\
		NOTE: If the kernel-type is a reference, \
		the `head` is stored as the `std::addressof` the argument. \

		XTAL_NEW subtype(XTAL_DEF_(of_q<U>) head_w, XTAL_DEF ...ws)
		XTAL_0EX
		:	co(XTAL_REF_(ws)...)
		,	body_m(member_f(XTAL_REF_(head_w)))
		{
		}

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
		Setter: applied when the template parameter matches the kernel-type. \
		\returns the previous value.

		template <typename W=U>
		XTAL_FN1 set(XTAL_DEF ...ws)
		XTAL_0EX
		requires is_q<head_t, body_t>
		{
			if constexpr (is_q<W, U>)
			{
				auto const head_m = head();
				body_m = member_f(XTAL_REF_(ws)...);
				return head_m;
			}
			else
			{
				return co::template set<W>(XTAL_REF_(ws)...);
			}
		}
		///\
		Getter: applied when the template parameter matches the kernel-type. \
		\returns the current value.

		template <typename W=U>
		XTAL_FN2 get()
		XTAL_0FX
		{
			if constexpr (is_q<W, U>)
			{
				return head();
			}
			else
			{
				return co::template get<W>();
			}
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
		
	};
};
////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that lifts the operations of `U`. \

template <typename U>
struct refer
{
	template <any_q S>
	class subtype: public S
	{
		using co = S; using T = subtype<S>;//typename co::self_t;
	public:
		using co::co;

	};
	template <any_q S>
	requires alpha_q<U>
	class subtype<S>: public S
	{
		using co = S; using T = subtype<S>;//typename co::self_t;
	public:
		using co::co;
		using co::self;
		using co::head;
		using co::body_m;

	//	XTAL_OP2        <=>       (subtype const &t) XTAL_0FX {return   head() <=> t.head();}
		XTAL_OP2_(bool) ==        (subtype const &t) XTAL_0FX {return   head() ==  t.head();}
		XTAL_OP2_(bool) <=        (subtype const &t) XTAL_0FX {return   head() <=  t.head();}
		XTAL_OP2_(bool) >=        (subtype const &t) XTAL_0FX {return   head() >=  t.head();}
		XTAL_OP2_(bool) <         (subtype const &t) XTAL_0FX {return   head() <   t.head();}
		XTAL_OP2_(bool) >         (subtype const &t) XTAL_0FX {return   head() >   t.head();}

		XTAL_OP2_(T ) * (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m * U(XTAL_REF_(w)));}
		XTAL_OP2_(T ) / (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m / U(XTAL_REF_(w)));}
		XTAL_OP2_(T ) % (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m % U(XTAL_REF_(w)));}
		XTAL_OP2_(T ) + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m + U(XTAL_REF_(w)));}
		XTAL_OP2_(T ) - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m - U(XTAL_REF_(w)));}

		XTAL_OP1_(T&) *=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m *=U(XTAL_REF_(w)), self();}
		XTAL_OP1_(T&) /=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m /=U(XTAL_REF_(w)), self();}
		XTAL_OP1_(T&) %=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m %=U(XTAL_REF_(w)), self();}
		XTAL_OP1_(T&) +=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m +=U(XTAL_REF_(w)), self();}
		XTAL_OP1_(T&) -=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m -=U(XTAL_REF_(w)), self();}
		
	};
	template <any_q S>
	requires iota_q<U>
	class subtype<S>: public S
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

		XTAL_OP2>> (XTAL_DEF           i) XTAL_0FX {return T(body_m>>  (XTAL_REF_(i)));}
		XTAL_OP2<< (XTAL_DEF           i) XTAL_0FX {return T(body_m<<  (XTAL_REF_(i)));}
		XTAL_OP2 & (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m & U(XTAL_REF_(w)));}
		XTAL_OP2 | (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m | U(XTAL_REF_(w)));}
		XTAL_OP2 ^ (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m ^ U(XTAL_REF_(w)));}
		XTAL_OP2 + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m + U(XTAL_REF_(w)));}
		XTAL_OP2 - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T(body_m - U(XTAL_REF_(w)));}

		XTAL_OP1>>=(XTAL_DEF           i) XTAL_0EX {return   body_m>>= (XTAL_REF_(i)), self();}
		XTAL_OP1<<=(XTAL_DEF           i) XTAL_0EX {return   body_m<<= (XTAL_REF_(i)), self();}
		XTAL_OP1 &=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m &=U(XTAL_REF_(w)), self();}
		XTAL_OP1 |=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m |=U(XTAL_REF_(w)), self();}
		XTAL_OP1 ^=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m ^=U(XTAL_REF_(w)), self();}
		XTAL_OP1 +=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m +=U(XTAL_REF_(w)), self();}
		XTAL_OP1 -=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return   body_m -=U(XTAL_REF_(w)), self();}
		
		XTAL_OP1 ++(int)                  XTAL_0EX {auto r = self(); ++body_m; return r;}
		XTAL_OP1 --(int)                  XTAL_0EX {auto r = self(); --body_m; return r;}
		XTAL_OP1 ++()                     XTAL_0EX {auto&s = self(); ++body_m; return s;}
		XTAL_OP1 --()                     XTAL_0EX {auto&s = self(); --body_m; return s;}

		XTAL_OP2 ~ ()                     XTAL_0FX {return T(~body_m);}
		XTAL_OP2 - ()                     XTAL_0FX {return T(-body_m);}

	};
	template <any_q S>
	requires (iterated_q<U> and uniterated_q<S> and uniterable_q<S>)
	class subtype<S>: public S
	{
		using co = S; using T = subtype<S>;//typename co::self_t;
	public:
		using co::co;
		using co::self;
		using co::head;

		XTAL_FN2 begin() XTAL_0EX requires requires (U       &u) {u.begin();} {return head().begin();}
		XTAL_FN2 begin() XTAL_0FX requires requires (U const &u) {u.begin();} {return head().begin();}
		XTAL_FN2   end() XTAL_0EX requires requires (U       &u) {u.  end();} {return head().  end();}
		XTAL_FN2   end() XTAL_0FX requires requires (U const &u) {u.  end();} {return head().  end();}

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
