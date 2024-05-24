#pragma once
#include "./any.cc"
#include "./scalar.hh"// testing...





XTAL_ENV_(push)
namespace xtal::algebra::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("scalar")
{
	using re = bond::realized;
	using T_delta = typename re::delta_t;
	using T_sigma = typename re::sigma_t;
	using T_alpha = typename re::alpha_t;
	using T_aphex = typename re::aphex_t;

	TRY_("construction")
	{
		auto constexpr N_size = 2;
		using W = scalar_t<T_alpha[N_size]>;

		auto foo = W{2.0, 0.5};
		auto bar = re::template roots_f<2>((T_alpha) 2);
		auto baz = bar*bar;
	//	bar.transact([] XTAL_1FN_(re::square_f), bond::computrim_f<1>);
		TRUE_(get<0>(foo) == bond::computrim_f<19>(get<0>(baz)));
		TRUE_(get<1>(foo) == bond::computrim_f<19>(get<1>(baz)));

		foo *= {(T_alpha) 0.0, (T_alpha) 0.0};

	}
	TRY_("summation")
	{
		auto constexpr N_size = 3;
		using W = scalar_t<T_alpha[N_size]>;
		auto  w = W{2.0, 1.0, 0.5};

		TRUE_(3.5 == w.sum());
		TRUE_(1.5 == w.template sum<-1>());

	}
	TRY_("reflection")
	{
		auto constexpr N_size = 2;
		using W = scalar_t<T_alpha[N_size]>;

		auto bar = W{2.0, 0.5};
		auto foo = bar.template reflected<-1>();
		auto baz = foo.template reflected<+1>();
		
		TRUE_(bond::computrim_f<19>(foo[0]) == 1.25);
		TRUE_(bond::computrim_f<19>(foo[1]) == 0.75);
		TRUE_(bond::computrim_f<19>(baz[0]) == bar[0]);
		TRUE_(bond::computrim_f<19>(baz[1]) == bar[1]);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
