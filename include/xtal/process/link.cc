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
		XTAL_DEF_(inline,let)
		operator () (auto &&o) const
		{
			return XTAL_REF_(o) + 1;
		}

	};
};
using foo_t = typename foo::type;
using bar_t = process::confined_t<confer<foo_t>>;
using baz_t = process::link_t<decltype([] (auto &&o) XTAL_0FN_(to) (o*10)), confer<foo_t>>;


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
	TRY_("chaining")
	{
		using halve_square_root_t = link_t<halve_t, square_root_t>;
		using square_root_halve_t = link_t<square_root_t, halve_t>;
		
		TRUE_(2. == halve_square_root_t::method_f(16.));
		TRUE_(3. == square_root_halve_t::method_f(18.));

		TRUE_(2. == halve_square_root_t{}.method(16.));
		TRUE_(3. == square_root_halve_t{}.method(18.));

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
