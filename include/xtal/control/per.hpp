#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

struct per
{
private:
	using U = iota_t;
	using V = alpha_t;

public:
	using subkind = compose<defer<U>, defer<V>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;

	public:
//	using co::co;
		
		XTAL_CO2_(subtype);
		XTAL_CO4_(subtype);

		XTAL_NEW_(explicit) subtype(XTAL_DEF_(iota_q) n, XTAL_DEF ...ws)
		XTAL_0EX
		:	co(n, (V) 1./V(XTAL_REF_(n)), XTAL_REF_(ws)...)
		{
		}
		XTAL_NEW_(explicit) subtype(XTAL_DEF_(alpha_q) u, XTAL_DEF ...ws)
		XTAL_0EX
		:	co((U) 1./V(XTAL_REF_(u)), u, XTAL_REF_(ws)...)
		{
		}

		XTAL_RE4_(XTAL_FN2   rate(), co::template head<0>())
		XTAL_RE4_(XTAL_FN2 period(), co::template head<1>())

	};
};
using per_t = confined_t<per>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
