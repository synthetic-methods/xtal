#pragma once
#include "./nominal.hpp"




#include <catch2/catch_all.hpp>

XTAL_ENV_(push)
namespace xtal::any::_test::nominal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*/
TEST_CASE("xtal/any/nominal.hpp: true")
{
	REQUIRE(true);
}
/**/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
