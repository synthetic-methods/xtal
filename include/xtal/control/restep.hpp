#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U=iota_t>
struct restep
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
	public:
		using co::co;
		using step_t = U;

		XTAL_RE4_(XTAL_FN1 step(XTAL_DEF... oo), co::head(XTAL_REF_(oo)...))

	};
};
template <typename U=iota_t>
using restep_t = confined_t<restep<U>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
