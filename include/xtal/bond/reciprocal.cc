#pragma once
#include "./any.cc"
#include "./reciprocal.ii"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("solid", "reciprocal")
{
	TRY_("construction")
	{
		using T_sigma = typename atom::realized::sigma_t;
		using T_alpha = typename atom::realized::alpha_t;
		using W_alpha = reciprocal_t<T_alpha[2]>;

		auto foo = W_alpha {2.0, 0.5};
		auto bar = W_alpha::fudge_f(atom::realized::template unsquare_f<0>((T_alpha) 2));
		bar.transmute([] XTAL_1FN_(atom::realized::square_f), atom::computrim_f<1>);
		TRUE_(foo == bar);

		foo *= {(T_alpha) 0.0, (T_alpha) 0.0};

	}
	TRY_("transformation")
	{
		using T_sigma = typename atom::realized::sigma_t;
		using T_alpha = typename atom::realized::alpha_t;
		using W_alpha = reciprocal_t<T_alpha[2]>;

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
