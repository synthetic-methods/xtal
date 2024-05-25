#pragma once
#include "./any.cc"
#include "./series.hh"// testing...





XTAL_ENV_(push)
namespace xtal::algebra::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("solid", "series")
{
	using op = bond::operating;
	using T_delta = typename op::delta_t;
	using T_sigma = typename op::sigma_t;
	using T_alpha = typename op::alpha_t;
	using T_aphex = typename op::aphex_t;

	TRY_("initialization")
	{
		T_sigma constexpr N = 1 << 3;
		using V_series = series_t<T_alpha[N]>;
		using U_series = series_t<T_alpha[N]>;

		U_series baz(2.0);
		V_series bar = reinterpret_cast<V_series &>(baz);
		V_series foo = {1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7};
		TRUE_(equal_f(foo, bar));
		
	}
	TRY_("transformation")
	{
		auto    constexpr iffy = [] XTAL_1FN_(bond::computrim_f<16>);
		T_sigma constexpr O = 1 << 5;
		T_sigma constexpr N = 1 << 3;
		T_sigma constexpr M = N  - 1;

		using V_series = series_t<T_aphex[O]>;
		using U_series = series_t<T_aphex[N]>;
		V_series basis(ordinal_t<-1>{});

		U_series source;
		source[0] = source[M - 0] = T_aphex(0.0, 0.0);
		source[1] = source[M - 1] = T_aphex(1.0, 1.0);
		source[2] = source[M - 2] = T_aphex(3.0, 3.0);
		source[3] = source[M - 3] = T_aphex(4.0, 4.0);

		auto target = basis.transformation(source).transact(iffy);
		TRUE_(target[0] == iffy(T_aphex( 0.1600000000000000e+2,  0.1600000000000000e+2)));
		TRUE_(target[1] == iffy(T_aphex(-0.4828427124746192e+1, -0.1165685424949238e+2)));
		TRUE_(target[2] == iffy(T_aphex( 0.0000000000000000e+0,  0.0000000000000000e+0)));
		TRUE_(target[3] == iffy(T_aphex(-0.3431457505076203e+0,  0.8284271247461885e+0)));
		TRUE_(target[4] == iffy(T_aphex( 0.0000000000000000e+0,  0.0000000000000000e+0)));
		TRUE_(target[5] == iffy(T_aphex( 0.8284271247461912e+0, -0.3431457505076203e+0)));
		TRUE_(target[6] == iffy(T_aphex( 0.0000000000000000e+0,  0.0000000000000000e+0)));
		TRUE_(target[7] == iffy(T_aphex(-0.1165685424949238e+2, -0.4828427124746188e+1)));

	}
	TRY_("convolution")
	{
		auto    constexpr iffy = [] XTAL_1FN_(bond::computrim_f<16>);
		T_sigma constexpr N = 1 << 3;
		T_sigma constexpr M = N  - 1;

		using U_series = series_t<T_aphex[N]>;
		U_series basis(ordinal_t<-1>{});

		U_series lhs = {0, 1, 2, 0, 0, 0, 0, 0};
		U_series rhs = {1, 0, 1, 0, 0, 0, 0, 0};
		U_series xhs = {0, 1, 2, 1, 2, 0, 0, 0};
		U_series yhs = basis.convolution(lhs, rhs).transact(iffy);
		TRUE_(xhs == yhs);

	}
	TRY_("multiplication")
	{
		using C4 = series_t<T_aphex[4]>;
		using D4 = series_t<T_aphex[4]>;
		
		TRUE_(C4{1000, 100, 10, 1} * C4{2000, 200, 20, 2} == C4{2000600, 400040, 60002, 8000});
		TRUE_(D4{1000, 100, 10, 1} * D4{2000, 200, 20, 2} == D4{2000600, 400040, 60002, 8000});

	}
	TRY_("generation")
	{
		using U_alpha = scalar_t<T_alpha[1<<1]>;
		using U_aphex = scalar_t<T_aphex[1<<1]>;
		using W_aphex = series_t<U_aphex[1<<4]>;

		W_aphex w_aphex; w_aphex.generate(T_aphex{0, 1}, T_alpha{2.0});

		TRUE_(w_aphex.get(0) == U_aphex {{  1.00000,  0.00000}, {  1.00000,- 0.00000}});
		TRUE_(w_aphex.get(1) == U_aphex {{  0.00000,  2.00000}, {  0.00000,- 0.50000}});
		TRUE_(w_aphex.get(2) == U_aphex {{- 4.00000,  0.00000}, {- 0.25000,- 0.00000}});
		TRUE_(w_aphex.get(3) == U_aphex {{- 0.00000,- 8.00000}, {- 0.00000,  0.12500}});
		TRUE_(w_aphex.get(4) == U_aphex {{ 16.00000,- 0.00000}, {  0.06250,  0.00000}});
		TRUE_(w_aphex.get(5) == U_aphex {{  0.00000, 32.00000}, {  0.00000,- 0.03125}});

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
