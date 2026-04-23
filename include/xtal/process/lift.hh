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
	class subtype : public bond::compose_s<S>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S>;
		using X_ = S_;
		using Y_ = U ;

		XTAL_DEF_(return,inline,set)
		y_(auto &&...oo)
		noexcept -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF_(to) (Y_{}(XTAL_REF_(oo)...))
			XTAL_0IF_(to) (Y_  {XTAL_REF_(oo)...})
			XTAL_0IF_(to) (Y_  (XTAL_REF_(oo)...))
		}

	public:
		using S_::S_;

		template <auto ...Ns>
		XTAL_DEF_(return,inline,let)
		method(auto &&...oo) const
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to_if) (XTAL_ANY_(X_ const &).template method<Ns...>(XTAL_REF_(oo)...))
		{	return                         y_(X_       :: template method<Ns...>(XTAL_REF_(oo)...));
		}
		template <auto ...Ns>
		XTAL_DEF_(return,inline,let)
		method(auto &&...oo)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to_if) (XTAL_ANY_(X_       &).template method<Ns...>(XTAL_REF_(oo)...))
		{	return                         y_(X_       :: template method<Ns...>(XTAL_REF_(oo)...));
		}

	};
};
template <class U>
struct lifted : lifter<U>
{
};

template <bond::compose_q A>
struct lifter<A> : lifter<confined_t<A>>
{
};
template <bond::compose_q A>
struct lifted<A> : A
{
};


}///////////////////////////////////////////////////////////////////////////////

template <                class ...As> struct lift;
template <                           > struct lift<        > : bond::compose<                               > {};
template <class        A, class ...As> struct lift<A, As...> : bond::compose<_detail::lifter<A>, lift<As...>> {};
template <incomplete_q A, class ...As> struct lift<A, As...> :                                   lift<As...>  {};
template <class        A             > struct lift<A       > :               _detail::lifted<A>               {};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
