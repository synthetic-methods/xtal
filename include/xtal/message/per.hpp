#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U, typename V=alpha_t>
struct per
{
	using subkind = compose<defer<U>, defer<V>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;

		XTAL_FZ2 invert_f(XTAL_DEF o)
		{
			return alpha_t(1)/alpha_t(XTAL_REF_(o));
		}

	public:
//	using co::co;
		
		XTAL_CO2_(subtype);
		XTAL_CO4_(subtype);

		XTAL_NEW_(explicit) subtype(XTAL_DEF n, XTAL_DEF ...ws)
		XTAL_0EX
		:	co(n, invert_f(XTAL_REF_(n)), XTAL_REF_(ws)...)
		{
		}

		XTAL_RE4_(XTAL_FN2   rate(), co::template head<0>())
		XTAL_RE4_(XTAL_FN2 period(), co::template head<1>())

	};
};
template <typename U, typename V=alpha_t>
using per_t = confined_t<per<U, V>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
