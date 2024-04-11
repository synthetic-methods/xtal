#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

struct per
{
private:
	using U = _std::make_unsigned_t<typename bond::realized::iota_t>;
	using V = typename bond::realized::alpha_t;

public:
	using subkind = bond::compose<defer<U>, defer<V>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	public:
	//	using S_::S_;
		
		XTAL_CO0_(subtype);
		XTAL_CO1_(subtype);
		XTAL_CO4_(subtype);

		XTAL_CXN subtype(integral_p auto n, auto &&...oo)
		XTAL_0EX
		:	S_(n, (V) 1/V(n), XTAL_REF_(oo)...)
		{}
		XTAL_CXN subtype(_std::floating_point auto u, auto &&...oo)
		XTAL_0EX
		:	S_((U) 1/V(u), u, XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(XTAL_TN2   rate(), S_::template head<0>())
		XTAL_TO4_(XTAL_TN2 period(), S_::template head<1>())

	};
};
using per_t = confined_t<per>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
