#pragma once
#include "./any.cc"
#include "./couple.hh"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("couple")
{
	using re = bond::realized;
	using T_delta = typename re::delta_t;
	using T_sigma = typename re::sigma_t;
	using T_alpha = typename re::alpha_t;
	using T_aphex = typename re::aphex_t;

	TRY_("production (multiplicative)")
	{
		using W =  couple_t<T_aphex, T_alpha>;
		auto  x =  W{2, 3};
		auto  y =  W{4, 9};
		auto  z =  y*x;
		TRUE_(z == W{8, 27});

	}
	TRY_("production (divisive)")
	{
		using W =  couple_t<T_aphex, T_alpha>;
		auto  x =  W{2, 3};
		auto  y =  W{4, 9};
		auto  z =  y/x;
		TRUE_(z == W{2, 3});
	}
	TRY_("summation")
	{
		using W = couple_t<T_alpha, T_alpha>;
		auto  w = W{2.0, 1.0};

		TRUE_(3.0 == w.sum());
		TRUE_(1.0 == w.template sum<-1>());

	}
	TRY_("reflection")
	{
		using W = couple_t<T_alpha, T_alpha>;

		auto bar = W{2.0, 0.5};
		auto foo = bar.template reflected<-1>();
		auto baz = foo.template reflected<+1>();
		
		auto [x, y] = foo;

		TRUE_(bond::computrim_f<19>(x) == 1.25);
		TRUE_(bond::computrim_f<19>(y) == 0.75);
		TRUE_(bond::computrim_f<19>(baz.get<0>()) == bar.get<0>());
		TRUE_(bond::computrim_f<19>(baz.get<1>()) == bar.get<1>());

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
