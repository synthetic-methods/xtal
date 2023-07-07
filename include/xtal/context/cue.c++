#pragma once
#include "./any.c++"
#include "./cue.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::context::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/context/cue.hpp: true")
{
	using source_t = concord::lift_t<counted_t<>>;
	using target_t = cue_s<source_t>;
	using target_u = cue_s<>;

	target_u t0(99);
	target_t t1(99, source_t(counted_t<>(11, 22)));

	REQUIRE(99 == t0.template head<0>());
	REQUIRE(99 == t1.template head<0>());
	REQUIRE(_v3::ranges::equal(counted_t<>(11, 22), t1.template head<1>()));

	REQUIRE(is_q<XTAL_TYP_(XTAL_VAL_(target_t).head()), typename target_u::head_t>);
	REQUIRE(is_q<XTAL_TYP_(XTAL_VAL_(target_t).parent()), source_t>);
}
/**/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
