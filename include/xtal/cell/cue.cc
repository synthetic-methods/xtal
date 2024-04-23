#pragma once
#include "./any.cc"
#include "./cue.hh"// testing...





XTAL_ENV_(push)
namespace xtal::cell::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("cue")
{
	TRY_("construct")
	{
		using U_source = cell::conferred_t<counted_t<>>;
		using U_target = cue_s<U_source>;
		using V_target = cue_s<>;

		V_target t0(99);
		U_target t1(99, U_source(counted_t<>(11, 22)));

		TRUE_(99 == t0.template head<0>());
		TRUE_(99 == t1.template head<0>());
		TRUE_(equal_f(counted_t<>(11, 22), t1.then()));

		TRUE_(is_q<XTAL_TYP_(XTAL_ANY_(U_target).head()), typename V_target::template head_t<>>);
		TRUE_(is_q<XTAL_TYP_(XTAL_ANY_(U_target).then()), U_source>);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
