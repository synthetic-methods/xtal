#pragma once
#include "./any.c++"
#include "./etc.hpp"// testing...

#include "./all.hpp"




XTAL_ENV_(push)
namespace xtal::common::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__test;


////////////////////////////////////////////////////////////////////////////////
/*/
TEST_CASE("xtal/common/any.hpp: true")
{
	REQUIRE(true);
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
