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
	using _op = bond::operating;
	using T_delta = typename _op::delta_type;
	using T_sigma = typename _op::sigma_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;

	TRY_("construction")
	{
		auto constexpr N_size = 2;
		using W = scalar_t<T_alpha[N_size]>;

		auto foo = W{2.0, 0.5};
		auto bar = _op::template roots_f<2>((T_alpha) 2);
		auto baz = bar*bar;
	//	bar.transact([] XTAL_1FN_(_op::square_f), bond::computrim_f<1>);
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
	TRY_("refactoring")
	{
		using U2 = scalar_t<T_sigma[2]>;
		using U4 = scalar_t<T_sigma[4]>;

		TRUE_(U2{2, 12} == U4{2, 12, 6, 2}.coordered());
		TRUE_(U2{0,  0} == U4{2, 12, 6, 3}.coordered());
		TRUE_(U2{0,  0} == U4{2, 12, 6, 4}.coordered());

		U4 u4{2, 12, 6, 2};
		TRUE_(U4{0, 0, 0, 0} == u4 % U4{1, 2, 1, 2});
		u4 /= {1, 2, 1, 2};
		TRUE_(U2{1, 6} == u4.coordered());

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
