#pragma once
#include "./any.c++"
#include "./restore.ipp"// testing...





XTAL_ENV_(push)
namespace xtal::processor::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("restore")
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
