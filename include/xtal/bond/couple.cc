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
	using _op = bond::operate<>;
	using T_delta = typename _op::delta_type;
	using T_sigma = typename _op::sigma_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;

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

		TRUE_(check_f<19>(x, 1.25));
		TRUE_(check_f<19>(y, 0.75));
		TRUE_(check_f<19>(get<0>(baz), get<0>(bar)));
		TRUE_(check_f<19>(get<1>(baz), get<1>(bar)));

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
