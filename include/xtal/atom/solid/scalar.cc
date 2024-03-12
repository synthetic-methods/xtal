#pragma once
#include "./any.cc"
#include "./scalar.ii"// testing...





XTAL_ENV_(push)
namespace xtal::atom::solid::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("solid", "scalar")
{
	TRY_("construction")
	{
		using T_sigma = typename atom::computer::sigma_t;
		using T_alpha = typename atom::computer::alpha_t;

		auto foo = solid::scalar_t<T_alpha[2]> {2.0, 0.5};
		auto bar = atom::computer::template unsquare_f<0>((T_alpha) 2);
		bar.transmute([] XTAL_1FN_(atom::computer::square_f), atom::computrim_f<1>);
		TRUE_(foo == bar);

	}
	TRY_("transformation")
	{
		using T_sigma = typename atom::computer::sigma_t;
		using T_alpha = typename atom::computer::alpha_t;

		auto bar = solid::scalar_t<T_alpha[2]> {2.0, 0.5};
		auto foo = bar.reflected(-1);
		auto baz = foo.reflected(+1);
		
		TRUE_(atom::computrim_f<19>(foo[0]) == 1.25);
		TRUE_(atom::computrim_f<19>(foo[1]) == 0.75);
		TRUE_(atom::computrim_f<19>(baz[0]) == bar[0]);
		TRUE_(atom::computrim_f<19>(baz[1]) == bar[1]);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
