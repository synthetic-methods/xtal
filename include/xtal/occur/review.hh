#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct   review;
template <class ..._s> using    review_t = confined_t<review<_s...>, bond::tag<review>>;
template <class ..._s> concept  review_q = bond::tagged_with_p<review, _s...>;


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) review_f = []<class ...Us> (Us &&...us)
XTAL_0FN_(to) (review_t<based_t<Us>...>(XTAL_REF_(us)...));


////////////////////////////////////////////////////////////////////////////////

template <class W>
struct review<W>
{
	using superkind = confer<W>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::head;
		
		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) view_(auto &&...oo), (void) head(XTAL_REF_(oo)...), self())
		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) view (auto &&...oo),        head(XTAL_REF_(oo)...)        )

		XTAL_FX2_(to) (XTAL_DEF_(return,inline,get)
		subview(auto &&...oo),
		review_f(S_::subhead(XTAL_REF_(oo)...)))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
