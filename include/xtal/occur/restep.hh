#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <integral_p U=typename bond::realized::iota_t>
struct restep
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using U_step = U;

		XTAL_TO4_(XTAL_TN2 step(auto &&...oo), S_::head(XTAL_REF_(oo)...))

	};
};
template <integral_p U=typename bond::realized::iota_t>
using restep_t = confined_t<restep<U>>;

XTAL_FN2 restep_f(auto &&w)
XTAL_0EX
{
	using re = bond::realize<XTAL_TYP_(w)>;
	return restep_t<typename re::iota_t>(XTAL_REF_(w));
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
