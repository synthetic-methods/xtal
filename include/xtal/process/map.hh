#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP map;
template <typename ..._s> XTAL_USE map_t = confined_t<map<_s...>>;
template <typename ..._s> XTAL_ASK map_q = bond::head_tag_p<map, _s...>;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <typename     ...As> struct map_link    : bond::compose<map_link<As>...> {};
template <   incomplete_q A > struct map_link<A> : bond::compose<               > {};
template <bond::compose_q A > struct map_link<A> :                              A {};
template <class           F >
struct map_link<F>
{
	template <any_q S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;
		
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_TN1 functor (auto &&...xs),
		{
			return invoke_f<F>(S_::template functor <Is...>(XTAL_REF_(xs)...));
		})
		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_FN1 function(auto &&...xs)
		XTAL_0EX
		{
			return invoke_f<F>(S_::template function<Is...>(XTAL_REF_(xs)...));
		}

	};
};


}///////////////////////////////////////////////////////////////////////////////

template <typename     ...As> struct map    : bond::compose<_detail::map_link<As...>, bond::tag<map>> {};
template <bond::compose_q A > struct map<A> : bond::compose<                  A     , bond::tag<map>> {};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
