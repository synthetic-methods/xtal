#pragma once
#include "./any.cc"
#include "./scalar.ii"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("scalar")
{
	using re = atom::realized;
	using T_sigma = typename re::sigma_t;
	using T_alpha = typename re::alpha_t;
	using W_alpha = scalar_t<T_alpha[2]>;

	TRY_("construction")
	{
		auto foo = W_alpha {2.0, 0.5};
		auto bar = forge_f<W_alpha>(re::template root_2f<2>((T_alpha) 2));
		bar.transmorph([] XTAL_1FN_(re::square_f), atom::computrim_f<1>);
		TRUE_(foo == bar);

		foo *= {(T_alpha) 0.0, (T_alpha) 0.0};

	}
	TRY_("transformation")
	{
		auto bar = W_alpha {2.0, 0.5};
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