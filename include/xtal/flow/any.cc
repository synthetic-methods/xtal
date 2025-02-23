#pragma once
#include "../any.cc"
#include "./any.hh"// testing...





XTAL_ENV_(push)
namespace xtal::flow::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::_test;


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("flow", "any")
{
	TRY_("task")
	{
		auto const bar = flow::packed_f(0, 1);
		auto const baz = flow::packed_f(2, 3);
		auto const foo = (bar, baz);
		using Foo = XTAL_ALL_(foo);

	//	TRUE_(same_q<Foo, flow::packet_t<int, int, int, int>>);
		
		TRUE_(     flow::packed_q      <Foo>);
		TRUE_(0 == bond::pack_item_f<0>(foo));
		TRUE_(1 == bond::pack_item_f<1>(foo));
		TRUE_(2 == bond::pack_item_f<2>(foo));
		TRUE_(3 == bond::pack_item_f<3>(foo));
		TRUE_(4 == bond::pack_size_f   (foo));

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
