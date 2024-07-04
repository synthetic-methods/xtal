#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP lift;
template <typename ..._s> XTAL_USE lift_t = confined_t<lift<_s...>>;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class F>
struct lifter
{
	template <any_q S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;
		
	public:
		using S_::S_;

		template <auto ...Is> requires none_n<Is...>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		XTAL_0EX -> decltype(auto)
			requires XTAL_TRY_(XTAL_ANY_(S_ &).method(XTAL_REF_(xs)...))
		{
			return invoke_f<F>(S_::method(XTAL_REF_(xs)...));
		}
		template <auto ...Is> requires some_n<Is...>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		XTAL_0EX -> decltype(auto)
			requires XTAL_TRY_(XTAL_ANY_(S_ &).template method<Is...>(XTAL_REF_(xs)...))
		{
			return invoke_f<F>(S_::template method<Is...>(XTAL_REF_(xs)...));
		}
		
		template <auto ...Is> requires none_n<Is...>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		XTAL_0FX -> decltype(auto)
			requires XTAL_TRY_(XTAL_ANY_(S_ const &).method(XTAL_REF_(xs)...))
		{
			return invoke_f<F>(S_::method(XTAL_REF_(xs)...));
		}
		template <auto ...Is> requires some_n<Is...>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		XTAL_0FX -> decltype(auto)
			requires XTAL_TRY_(XTAL_ANY_(S_ const &).template method<Is...>(XTAL_REF_(xs)...))
		{
			return invoke_f<F>(S_::template method<Is...>(XTAL_REF_(xs)...));
		}

		template <auto ...Is>
		XTAL_DEF_(return,inline,static)
		XTAL_LET function(auto &&...xs)
		XTAL_0EX
		->	decltype(auto)
			requires XTAL_TRY_TO_(invoke_f<F>(S_::template function<Is...>(XTAL_REF_(xs)...)))

	};
};
template <bond::compose_q F>
struct lifter<F>
{
	template <any_q S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;
		using F_ = confined_t<F>;

	public:
		using S_::S_;

		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		XTAL_0EX -> decltype(auto)
		{
			return F_::template function<Is...>(S_::template method<Is...>(XTAL_REF_(xs)...));
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		XTAL_0FX -> decltype(auto)
			requires XTAL_TRY_(XTAL_ANY_(S_ const &).template method<Is...>(XTAL_REF_(xs)...))
		{
			return F_::template function<Is...>(S_::template method<Is...>(XTAL_REF_(xs)...));
		}
		
		template <auto ...Is>
		XTAL_DEF_(return,inline,static)
		XTAL_LET function(auto &&...xs)
		XTAL_0EX
		->	decltype(auto)
			requires XTAL_TRY_TO_(F_::template function<Is...>(S_::template function<Is...>(XTAL_REF_(xs)...)))

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
