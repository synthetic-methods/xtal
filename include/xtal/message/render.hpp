#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <iterated_q U>
struct render
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		XTAL_CO2_(subtype);
		XTAL_CO4_(subtype);

		template <iterated_q W>
		XTAL_NEW_(explicit) subtype(W &&w, XTAL_DEF... ws)
		XTAL_0EX
		:	co(rendered_t<W>(XTAL_FWD_(W) (w)), XTAL_REF_(ws)...)
		{
		}

		XTAL_RE4_(XTAL_FN2 span(), co::head())

	};
};
template <iterated_q U>
using render_t = confined_t<render<U>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
