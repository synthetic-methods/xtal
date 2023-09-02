#pragma once
#include "./any.cc"
#include "./scalar.ii"// testing...





XTAL_ENV_(push)
namespace xtal::compound::solid::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("solid", "scalar")
{
	TRY_("construction")
	{
		using sigma_t = typename common::computer::sigma_t;
		using alpha_t = typename common::computer::alpha_t;

		auto foo = solid::scalar_t<alpha_t[2]> {2.0, 0.5};
		auto bar = common::computer::template unsquare_f<0>((alpha_t) 2);
		bar.transmute([] XTAL_1FN_(common::computer::square_f), common::computrim_f<1>);
		TRUE_(foo == bar);

	}
	TRY_("transformation")
	{
		using sigma_t = typename common::computer::sigma_t;
		using alpha_t = typename common::computer::alpha_t;

		auto bar = solid::scalar_t<alpha_t[2]> {2.0, 0.5};
		auto foo = bar.reflected(-1);
		auto baz = foo.reflected(+1);
		
		TRUE_(common::computrim_f<19>(foo[0]) == 1.25);
		TRUE_(common::computrim_f<19>(foo[1]) == 0.75);
		TRUE_(common::computrim_f<19>(baz[0]) == bar[0]);
		TRUE_(common::computrim_f<19>(baz[1]) == bar[1]);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
