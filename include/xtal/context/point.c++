#pragma once
#include "./any.c++"
#include "./point.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::context::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("point")
{
	TRY_("construct")
	{
		using source_t = concord::lift_t<counted_t<>>;
		using target_t = point_s<source_t>;
		using target_u = point_s<>;

		target_u t0(99);
		target_t t1(99, source_t(counted_t<>(11, 22)));

		TRUE_(99 == t0.template head<0>());
		TRUE_(99 == t1.template head<0>());
		TRUE_(equal_f(counted_t<>(11, 22), t1.template head<1>()));

		TRUE_(is_q<XTAL_TYP_(XTAL_VAL_(target_t).head()), typename target_u::head_t>);
		TRUE_(is_q<XTAL_TYP_(XTAL_VAL_(target_t).core()), source_t>);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
