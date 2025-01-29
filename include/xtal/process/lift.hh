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
	class subtype : public bond::compose_s<S>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S>;

		using S_var = S_       &;
		using S_val = S_ const &;

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		S_method(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(return) (S_::template static_method<Is...>(XTAL_REF_(xs)...))

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		U_method(auto &&...xs)
		noexcept -> decltype(auto)
		{
			if constexpr (bond::compose_q<U>) {
				return confined_t<U>::template static_method<Is...>(XTAL_REF_(xs)...);
			}
			else {
				return evoke_t<U>{}(XTAL_REF_(xs)...);
			}
		}

	public:
		using S_::S_;

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		static_method(auto &&...xs)
		noexcept -> decltype(auto)
		requires requires {S_method<Is...>(XTAL_REF_(xs)...);}
		{
			return U_method<Is...>(S_method<Is...>(XTAL_REF_(xs)...));
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method(auto &&...xs)
		noexcept -> decltype(auto)
		requires requires {S_method<Is...>(XTAL_REF_(xs)...);}
		{
			return U_method<Is...>(S_method<Is...>(XTAL_REF_(xs)...));
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		method(auto &&...xs) const
		noexcept -> decltype(auto)
		requires XTAL_TRY_(unless)          (S_method<Is...>(XTAL_REF_(xs)...))
		and  requires (S_val s_) {s_ .template method<Is...>(XTAL_REF_(xs)...);}
		{
			return U_method<Is...>(S_::template method<Is...>(XTAL_REF_(xs)...));
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		method(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(unless)          (S_method<Is...>(XTAL_REF_(xs)...))
		and  requires (S_var s_) {s_ .template method<Is...>(XTAL_REF_(xs)...);}
		{
			return U_method<Is...>(S_::template method<Is...>(XTAL_REF_(xs)...));
		}

	};
};


}///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Provides pure `head`-less mapping of `(?:static_)method` (in contrast to `link`), \
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
