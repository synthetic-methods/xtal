#pragma once
#include "./any.cc"
#include "./identify.ii"// testing...





XTAL_ENV_(push)
namespace xtal::common::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("identify")
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