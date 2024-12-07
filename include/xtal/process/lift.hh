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

template <class F>
struct lifter
{
	using superkind = invoke_body<>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

	public:
		using S_::S_;

		template <auto ...Is>
		XTAL_DEF_(short,static)
		XTAL_LET function(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(S_::template function<Is...>(XTAL_REF_(xs)...))
		{
			return target_f<Is...>(S_::template function<Is...>(XTAL_REF_(xs)...));
		}
		template <auto ...Is>
		XTAL_DEF_(short)
		XTAL_LET method(auto &&...xs) const
		noexcept -> decltype(auto)
		requires XTAL_TRY_(XTAL_ANY_(S_ const &).template method<Is...>(XTAL_REF_(xs)...))
		{
			return target_f<Is...>(S_::template method<Is...>(XTAL_REF_(xs)...));
		}
		template <auto ...Is>
		XTAL_DEF_(short)
		XTAL_LET method(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(XTAL_ANY_(S_       &).template method<Is...>(XTAL_REF_(xs)...))
		{
			return target_f<Is...>(S_::template method<Is...>(XTAL_REF_(xs)...));
		}

	private:
		template <auto ...Is>
		XTAL_DEF_(short,static)
		XTAL_LET target_f(auto &&...xs)
		noexcept -> decltype(auto)
		{
			if constexpr (bond::compose_q<F>) {
				return confined_t<superkind, F>::template function<Is...>(XTAL_REF_(xs)...);
			}
			else {
				return invoke_f<F>(XTAL_REF_(xs)...);
			}
		}

	};
};


}///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Provides pure `head`-less mapping of `method` and `function` (in contrast to `link`), \
in addition to allowing constructor mapping via `invoke_f`. \

template <                   typename ...As> struct lift;
template <bond::compose_q A                > struct lift<A       > :                                              A {};
template <                                 > struct lift<        > : bond::compose<                               > {};
template <     typename   A, typename ...As> struct lift<A, As...> : bond::compose<_detail::lifter<A>, lift<As...>> {};
template <   incomplete_q A, typename ...As> struct lift<A, As...> :                                   lift<As...>  {};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
