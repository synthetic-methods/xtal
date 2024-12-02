#pragma once
#include "./any.cc"
#include "./link.hh"// testing...





XTAL_ENV_(push)
namespace xtal::process::_test_link
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::process::_test;


////////////////////////////////////////////////////////////////////////////////

struct foo
{
	class type
	{
	public:
		XTAL_DEF_(inline)
		XTAL_LET operator () (auto &&o) const
		{
			return XTAL_REF_(o) + 1;
		}

	};
};
using foo_t = typename foo::type;
using bar_t = process::confined_t<confer<foo_t>>;
using baz_t = process::link_t<decltype([] (auto &&o) XTAL_0FN_(o*10)), confer<foo_t>>;


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("link")
{
	TRY_("task")
	{
		bar_t bar_f;
		baz_t baz_f;

		TRUE_(bar_f(0) ==  1);
		TRUE_(baz_f(0) == 10);

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
