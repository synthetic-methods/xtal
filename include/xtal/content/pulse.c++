#pragma once
#include "./any.c++"
#include "./pulse.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::content::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("pulse")
{
	TRY_("task")
	{
		using pulsed = pulse_t<int>;
	
		TRUE_(true);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)