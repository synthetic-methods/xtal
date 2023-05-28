#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U>
struct per
{
	using realized = realize<U>; using V = typename realized::alpha_t;
	using subkind = common::compose<defer<U>, defer<V>>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;

	public:
//	using co::co;
		
		XTAL_CO2_(subtype);
		XTAL_CO4_(subtype);

		XTAL_NEW_(explicit) subtype(XTAL_DEF n, XTAL_DEF ...ws)
		XTAL_0EX
		:	co(n, V(1)/V(XTAL_REF_(n)), XTAL_REF_(ws)...)
		{
		}

		XTAL_RE4_(XTAL_FN2   rate(), co::template head<0>())
		XTAL_RE4_(XTAL_FN2 period(), co::template head<1>())

	};
};
template <typename U>
using per_t = confined_t<per<U>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
