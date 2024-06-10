#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP review;
template <typename ..._s> XTAL_ASK review_q = bond::head_tag_p<review, _s...>;
template <iterable_q  U > XTAL_USE review_t = confined_t<review<U>, bond::tag<review>>;
template <iterable_q  U >
XTAL_DEF_(return,inline)
XTAL_LET review_f(U &&u)
XTAL_0EX
{
	return review_t<U>(XTAL_REF_(u));
};

template <class U>
struct review<U>
{
	using subkind = confer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::twin;
		using S_::head;
		
		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_REF    view(auto &&...oo),         (S_::   head(XTAL_REF_(oo)...)))
		XTAL_TO2_(XTAL_DEF_(return,inline) XTAL_REF subview(auto &&...oo), review_f(S_::subhead(XTAL_REF_(oo)...)))

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
