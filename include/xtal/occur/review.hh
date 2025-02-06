#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   review;
template <typename ..._s> concept  review_q = bond::tag_p<review, _s...>;
template <iterable_q  U > using    review_t = confined_t<review<U>, bond::tag<review>>;

template <iterable_q  U >
XTAL_DEF_(return,inline,let)
review_f(U &&u)
noexcept -> auto
{
	return review_t<U>(XTAL_REF_(u));
};

template <class U>
struct review<U>
{
	using superkind = confer<U>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::twin;
		using S_::head;
		
		XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)    view(auto &&...oo),          S_::   head(XTAL_REF_(oo)...) )
		XTAL_FX2_(to) (XTAL_DEF_(return,inline,get) subview(auto &&...oo), review_f(S_::subhead(XTAL_REF_(oo)...)))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
