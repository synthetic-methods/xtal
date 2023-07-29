#pragma once
#include "./anybody.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <_std::integral U=typename computer::iota_t>
struct restep
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using step_t = U;

		XTAL_TO4_(XTAL_FN2 step(XTAL_DEF... oo), S_::head(XTAL_REF_(oo)...))

	};
};
template <_std::integral U=typename computer::iota_t>
using restep_t = confined_t<restep<U>>;

XTAL_CN2 restep_f(XTAL_DEF w)
{
	using _computer = compute<XTAL_TYP_(w)>;
	return restep_t<typename _computer::iota_t>(XTAL_REF_(w));
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
