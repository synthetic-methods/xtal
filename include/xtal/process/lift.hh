#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP lift;
template <typename ..._s> XTAL_USE lift_t = confined_t<lift<_s...>>;
template <typename ..._s> XTAL_REQ lift_q = bond::any_tag_p<lift, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides pure `head`-less mapping of `functor` and `function` (in contrast to `link`), \
in addition to allowing constructor mapping via `invoke_f`. \

template <typename     ...As> struct lift    : bond::compose<lift<As>...> {};
template <   incomplete_q A > struct lift<A> : bond::compose<           > {};
template <bond::compose_q A > struct lift<A> :                          A {};
template <class           F >
struct lift<F>
{
	using subkind = bond::tag<lift>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		using T_ = typename S_::self_type;
		
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET functor (auto &&...xs),
		->	decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF XTAL_TRY_TO_(invoke_f<F>(S_::template functor <Is...>(XTAL_REF_(xs)...)))
			XTAL_0IF XTAL_TRY_TO_(            T_::template function<Is...>(XTAL_REF_(xs)...) )
		})
		template <auto ...Is>
		XTAL_DEF_(return,inline,static)
		XTAL_LET function(auto &&...xs)
		XTAL_0EX
		->	decltype(auto)
			requires XTAL_TRY_TO_(invoke_f<F>(S_::template function<Is...>(XTAL_REF_(xs)...)))

	};
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
