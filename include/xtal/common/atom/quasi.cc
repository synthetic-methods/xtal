#pragma once
#include "./any.cc"
#include "./quasi.ii"// testing...





XTAL_ENV_(push)
namespace xtal::common::atom::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("quasi")
{
	TRY_("task")
	{
		using quasied = quasi_t<int>;
	
		TRUE_(true);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)