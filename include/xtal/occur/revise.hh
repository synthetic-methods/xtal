#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP revise;
template <typename ..._s> XTAL_ASK revise_q = bond::tag_p<revise, _s...>;
template <iterable_q  U > XTAL_USE revise_t = confined_t<revise<U>, bond::tag<revise>>;
template <iterable_q  U > XTAL_FN2 revise_f(U &&u) XTAL_0EX {return revise_t<U>(XTAL_REF_(u));};

template <class S, iterated_q U>
using revise_s = bond::compose_s<S, confined<revise<U>, bond::tag<revise>>>;

template <materialized_q U>
struct revise<U>
:	revise<reiterated_t<U>>
{
};
template <class U>
struct revise<U>
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
		
		XTAL_TO4_(XTAL_TN2 span(auto &&...oo), S_::head(XTAL_REF_(oo)...))

		XTAL_TN2 slice(counted_q auto &&w)
		XTAL_0FX
		{
			using _xtd::ranges::views::slice;

			auto i = w.front(), j = w.back() + 1;
			return revise_f(span()|slice(i, j));
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
