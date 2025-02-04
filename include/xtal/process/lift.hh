#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

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

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		S_method_f(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(return) (S::template method_f<Is...>(XTAL_REF_(xs)...))

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		U_method_f(auto &&...xs)
		noexcept -> decltype(auto)
		{
			if constexpr (bond::compose_q<U>) {
				return confined_t<U>::template method_f<Is...>(XTAL_REF_(xs)...);
			}
			else {
				return evoke_t<U>{}(XTAL_REF_(xs)...);
			}
		}

	public:
		using S::S;

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method_f(auto &&...xs)
		noexcept -> decltype(auto)
		requires requires {S_method_f<Is...>(XTAL_REF_(xs)...);}
		{
			return U_method_f<Is...>(S_method_f<Is...>(XTAL_REF_(xs)...));
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method  (auto &&...xs)
		noexcept -> decltype(auto)
		requires requires {S_method_f<Is...>(XTAL_REF_(xs)...);}
		{
			return U_method_f<Is...>(S_method_f<Is...>(XTAL_REF_(xs)...));
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		method  (auto &&...xs) const
		noexcept -> decltype(auto)
		requires XTAL_TRY_(unless)           (S_method_f<Is...>(XTAL_REF_(xs)...))
		and  requires (S const &s) {s .template method  <Is...>(XTAL_REF_(xs)...);}
		{
			return U_method_f<Is...>(S::template method  <Is...>(XTAL_REF_(xs)...));
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		method  (auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(unless)           (S_method_f<Is...>(XTAL_REF_(xs)...))
		and  requires (S       &s) {s .template method  <Is...>(XTAL_REF_(xs)...);}
		{
			return U_method_f<Is...>(S::template method  <Is...>(XTAL_REF_(xs)...));
		}

	};
};


}///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Provides pure `head`-less mapping of `method` (in contrast to `link`), \
in addition to allowing constructor mapping via `evoke_t`. \

template <                   typename ...As> struct lift;
template <bond::compose_q A                > struct lift<A       > :                                              A {};
template <                                 > struct lift<        > : bond::compose<                               > {};
template <     typename   A, typename ...As> struct lift<A, As...> : bond::compose<_detail::lifter<A>, lift<As...>> {};
template <   incomplete_q A, typename ...As> struct lift<A, As...> :                                   lift<As...>  {};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
