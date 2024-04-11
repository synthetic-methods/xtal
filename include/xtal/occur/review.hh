#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct  review;
template <iterated_q   U> using   review_t = confined_t<refer<U>, review<U>, bond::tag<review>>;
template <typename ..._s> concept review_q = bond::tag_p<review, _s...>;
/**/
template <class S, iterated_q U>
using review_s = bond::compose_s<S, confined<bond::tag<review>, refer<U>, review<U>>>;
/***/

template <iterated_q U>
struct review<U>
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
	//	using S_::S_;
		using S_::self;
		using S_::twin;
		using S_::head;
		
		using U_span = U;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);

		XTAL_CXN subtype(auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{}
		template <iterated_q W> requires is_q<reiterate_t<W>, U>
		XTAL_CXN subtype(W &&w, auto &&...oo)
		XTAL_0EX
		:	S_(reiterate_t<W>(XTAL_REF_(w)), XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(XTAL_TN2 span(auto &&...oo), S_::head(XTAL_REF_(oo)...))

		XTAL_TN2 slice(counted_q auto &&w)
		XTAL_0FX
		{
			auto i = w.front(), j = w.back() + 1;
			auto t = twin(); (void) t.span(t.span()|_v3::views::slice(i, j)); return t;
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)