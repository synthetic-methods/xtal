#pragma once
#include "../any.cc"
#include "./any.ii"// testing...

#include "../message/all.ii"



XTAL_ENV_(push)
namespace xtal::scheduled::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::_test;


////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("any")
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
