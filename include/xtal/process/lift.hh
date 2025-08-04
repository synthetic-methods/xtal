#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Provides `head`-less mapping of `method` (in contrast to `link`).

\details
Allows for constructor mapping via `bond::operate`.
*/
template <typename ..._s> struct   lift;
template <typename ..._s> using    lift_t = confined_t<lift<_s...>>;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class U>
struct lifter
{
	template <class S>
	class subtype : public S
	{
		static_assert(any_q<S>);

		using Outer = U;
		using Inner = S;
		using Inner_nu = const Inner &;
		using Inner_mu =       Inner &;

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		Outer_f(auto &&...xs)
		noexcept -> decltype(auto)
		{
		//	using outer = bond::operate<Outer>;
			XTAL_IF0
			XTAL_0IF (bond::compose_q<Outer>) {
				return confined_t<Outer>::template method_f<Is...>(XTAL_REF_(xs)...);
			}
			XTAL_0IF_(to) (Outer::template method_f<Is...>(XTAL_REF_(xs)...))
			XTAL_0IF_(to) (Outer                          {XTAL_REF_(xs)...})
			XTAL_0IF_(to) (Outer                          (XTAL_REF_(xs)...))
			XTAL_0IF_(to) (Outer{}                        (XTAL_REF_(xs)...))
		//	XTAL_0IF_(to) (outer{}                        (XTAL_REF_(xs)...))
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		Inner_f(auto &&...xs)
		noexcept -> decltype(auto)
			requires XTAL_TRY_(to)
				(Inner::template method_f<Is...>(XTAL_REF_(xs)...))

	public:
		using S::S;

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method_f(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to)
			(Outer_f<Is...>(Inner_f<Is...>(XTAL_REF_(xs)...)))

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to)
			(method_f<Is...>(XTAL_REF_(xs)...))

		template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		method  (auto &&...xs) const
		noexcept -> decltype(auto)
			requires XTAL_TRY_(to_unless)                          (method_f<Is...>(XTAL_REF_(xs)...))
			and      XTAL_TRY_(to_if) (XTAL_ANY_(Inner_nu).template method  <Is...>(XTAL_REF_(xs)...))
		{
			return                Outer_f<Is...>(Inner::   template method  <Is...>(XTAL_REF_(xs)...));
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		method  (auto &&...xs)
		noexcept -> decltype(auto)
			requires XTAL_TRY_(to_unless)                          (method_f<Is...>(XTAL_REF_(xs)...))
			and      XTAL_TRY_(to_if) (XTAL_ANY_(Inner_mu).template method  <Is...>(XTAL_REF_(xs)...))
		{
			return                Outer_f<Is...>(Inner::   template method  <Is...>(XTAL_REF_(xs)...));
		}

	};
};


}///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <                   typename ...As> struct lift;
template <bond::compose_q A                > struct lift<A       > :                                              A {};
template <                                 > struct lift<        > : bond::compose<                               > {};
template <     typename   A, typename ...As> struct lift<A, As...> : bond::compose<_detail::lifter<A>, lift<As...>> {};
template <   incomplete_q A, typename ...As> struct lift<A, As...> :                                   lift<As...>  {};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
