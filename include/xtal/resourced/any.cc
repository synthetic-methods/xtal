#pragma once
#include "../any.cc"
#include "./any.ii"// testing...





XTAL_ENV_(push)
namespace xtal::resourced::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::_test;


////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("prepare", "any")
{
	TRY_("task")
	{
		TRUE_(true);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
