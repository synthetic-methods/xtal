#pragma once
#include "./any.cc"
#include "./cue.ii"// testing...





XTAL_ENV_(push)
namespace xtal::conduct::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("cue")
{
	TRY_("construct")
	{
		using source_t = conduct::conferred_t<counted_t<>>;
		using target_t = cue_s<source_t>;
		using target_u = cue_s<>;

		target_u t0(99);
		target_t t1(99, source_t(counted_t<>(11, 22)));

		TRUE_(99 == t0.template head<0>());
		TRUE_(99 == t1.template head<0>());
		TRUE_(equal_f(counted_t<>(11, 22), t1.core()));

		TRUE_(is_q<XTAL_TYP_(XTAL_VAL_(target_t).head()), typename target_u::head_t>);
		TRUE_(is_q<XTAL_TYP_(XTAL_VAL_(target_t).core()), source_t>);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
