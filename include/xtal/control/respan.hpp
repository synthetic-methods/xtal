#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <iterated_q U>
struct respan
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
	
	public:
	//	using co::co;
		using co::self;

		XTAL_CO2_(subtype);
		XTAL_CO4_(subtype);

		template <iterated_q W>
		XTAL_NEW_(explicit) subtype(W &&w, XTAL_DEF ...ws)
		XTAL_0EX
		:	co(deranged_t<W>(XTAL_FWD_(W) (w)), XTAL_REF_(ws)...)
		{
		}

		XTAL_RE4_(XTAL_FN1 span(XTAL_DEF... oo), co::head(XTAL_REF_(oo)...))
		XTAL_RE4_(XTAL_FN2 size(), co::head().size())

		XTAL_FN2 slice(iota_t i, iota_t j)
		XTAL_0EX
		{
			auto t = self(); t.span(t.span()|_v3::views::slice(i, j)); return t;
		}

	};
};
template <iterated_q U>
using respan_t = confined_t<respan<U>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
