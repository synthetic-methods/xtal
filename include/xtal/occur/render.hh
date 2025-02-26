#pragma once
#include "./any.hh"

#include "./cursor.hh"
#include "./review.hh"



XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s>	struct   render;
template <class ..._s>	using    render_t = confined_t<render<_s...>>;
template <class ..._s>	concept  render_q = bond::tagged_with_p<render, _s...>;


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) render_f = []<class ...Us> (Us &&...us)
XTAL_0FN_(to) (render_t<based_t<Us>...>(XTAL_REF_(us)...));


//////////////////////////////////////////////////////////////////////////////////

template <review_q U_review, cursor_q U_cursor>
struct render<U_review, U_cursor>
{
	using superkind = bond::compose<flow::tag<render>
	,	defer<U_review>
	,	defer<U_cursor>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

	public:// CONSTRUCT
		using S_::S_;
		
	public:// OPERATE

		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) cursor(), get<0>(S_::head()))
		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) review(), get<1>(S_::head()))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
