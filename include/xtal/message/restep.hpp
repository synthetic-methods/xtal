#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <iota_q U=typename realized::iota_t>
struct restep
{
	using subkind = defer<U>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using step_t = U;

		XTAL_RN4_(XTAL_FN1 step(XTAL_DEF... oo), S_::head(XTAL_REF_(oo)...))

	};
};
template <iota_q U=typename realized::iota_t>
using restep_t = confined_t<restep<U>>;

XTAL_FZ2 restep_f(XTAL_DEF w)
{
	using _realized = realize<XTAL_TYP_(w)>;
	return restep_t<typename _realized::iota_t>(XTAL_REF_(w));
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
