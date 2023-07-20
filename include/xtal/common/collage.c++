#pragma once
#include "./any.c++"
#include "./collage.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::common::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/common/collage.hpp: construction supervalue")
{
	using alpha_t = typename realized::alpha_t;
	using delta_t = typename realized::delta_t;

	using quasar_u = typename collage_t<1>::template quasar_t<alpha_t>;
	using quasar_t = typename collage_t<2>::template quasar_t<alpha_t>;
	
	quasar_t q0(1.125);
	++q0;
	++q0;
	++q0;
	REQUIRE(alpha_t(q0) == 0.125);
	REQUIRE(q0.phase(0) == 0.125);
	REQUIRE(q0.phase(1) == 0.0);
	REQUIRE(q0.pulse(0) == 0.0);
	REQUIRE(q0.pulse(1) == 0.0);

}
/**/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/common/collage.hpp: construction subsequence")
{
	using alpha_t = typename realized::alpha_t;
	using delta_t = typename realized::delta_t;

	using quasar_u = typename collage_t<1>::template quasar_t<alpha_t>;
	using quasar_t = typename collage_t<2>::template quasar_t<alpha_t>;
	
	quasar_u q1{0.375};
	quasar_t q0(q1);
	++q0;
	++q0;
	++q0;
	REQUIRE(alpha_t(q0) == 0.125);
	REQUIRE(q0.phase(0) == 0.125);
	REQUIRE(q0.phase(1) == 0.375);
	REQUIRE(q0.pulse(0) == 0.0);
	REQUIRE(q0.pulse(1) == 0.0);

}
/**/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
