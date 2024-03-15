#pragma once
#include "./any.cc"
#include "./realize.ii"// testing...





XTAL_ENV_(push)
namespace xtal::bond::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("realize", "logarithm")
{
	using T_sigma = typename realized::sigma_t;
	using T_delta = typename realized::delta_t;
	using T_alpha = typename realized::alpha_t;
	using T_aphex = typename realized::aphex_t;

	auto mt19937_f = typename realized::mt19937_t();
	mt19937_f.seed(Catch::rngSeed());

	EST_("real std::log")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = realized::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w += realized::logarithm_f(x);
		//	w += log(x);
		}
		return w;
	};
	EST_("real logarithm_f<+4>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = realized::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w += realized::logarithm_f<+4>(x);
		}
		return w;
	};
	EST_("real logarithm_f<+2>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = realized::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w += realized::logarithm_f<+2>(x);
		}
		return w;
	};
	EST_("real logarithm_f< 0>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = realized::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w += realized::logarithm_f< 0>(x);
		}
		return w;
	};

	TRY_("real logarithm")
	{
		T_alpha const x = 2;
		T_alpha const y = _std::log(x);
		TRUE_(computrim_f<52+0>(y) == computrim_f<52+0>(realized::logarithm_f<-1>(x)));

		TRUE_(computrim_f<50+1>(y) == computrim_f<50+1>(realized::logarithm_f<+4>(x)));
		TRUE_(computrim_f<40+0>(y) == computrim_f<40+0>(realized::logarithm_f<+3>(x)));
		TRUE_(computrim_f<30+0>(y) == computrim_f<30+0>(realized::logarithm_f<+2>(x)));
		TRUE_(computrim_f<20+0>(y) == computrim_f<20+0>(realized::logarithm_f<+1>(x)));
		TRUE_(computrim_f<10-2>(y) == computrim_f<10-2>(realized::logarithm_f<+0>(x)));
		
	}
}
TAG_("realize", "exponential")
{
	using T_sigma = typename realized::sigma_t;
	using T_delta = typename realized::delta_t;
	using T_alpha = typename realized::alpha_t;
	using T_aphex = typename realized::aphex_t;

	auto mt19937_f = typename realized::mt19937_t();
	mt19937_f.seed(Catch::rngSeed());

	EST_("real std::exp")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = realized::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w += _std::exp(x);
		}
		return w;
	};

	EST_("real antilogarithm_f<2, 0>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = realized::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w *= realized::antilogarithm_f<2, 0>(x);
		}
		return w;
	};
	EST_("real antilogarithm_f<1, 0>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = realized::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w *= realized::antilogarithm_f<1, 0>(x);
		}
		return w;
	};

	EST_("real antilogarithmic_f<2, 0>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = realized::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w *= realized::antilogarithmic_f<2, 0>(x);
		}
		return w;
	};
	EST_("real antilogarithmic_f<1, 0>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = realized::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w *= realized::antilogarithmic_f<1, 0>(x);
		}
		return w;
	};

	TRY_("real exponential")
	{
		T_alpha const x = 5.5;
		T_alpha const y = _std::exp(x);
	//	TRUE_(computrim_f<52+0>(y) == computrim_f<52+0>(realized::antilogarithm_f<-1>(x)));

		TRUE_(computrim_f<40+1>(y) == computrim_f<40+1>(realized::antilogarithm_f<+2, 0>(x)));
		TRUE_(computrim_f<40+1>(y) == computrim_f<40+1>(realized::antilogarithm_f<+1, 1>(x)));
		TRUE_(computrim_f<40+0>(y) == computrim_f<40+0>(realized::antilogarithm_f<+1, 0>(x)));
		TRUE_(computrim_f<10+5>(y) == computrim_f<10+5>(realized::antilogarithm_f<+0, 1>(x)));

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("realize", "bit_reverse")
{
	TRY_("32:03")
	{
		using __realized = realize<uint32_t>;
		using T_sigma = typename __realized::sigma_t;

		T_sigma question = 0b011;
		T_sigma answer   = 0b110;

		TRUE_(answer == __realized::bit_reverse_f<3>(question));

	}
	TRY_("16:16")
	{
		using __realized = realize<uint16_t>;
		using T_sigma = typename __realized::sigma_t;

		T_sigma question = 0b0100100011100101;
		T_sigma answer   = 0b1010011100010010;

		TRUE_(answer == __realized::bit_reverse_f<16>(question));

	}
	TRY_("16:12")
	{
		using __realized = realize<uint16_t>;
		using T_sigma = typename __realized::sigma_t;

		T_sigma question = 0b010010001110;
		T_sigma answer   = 0b011100010010;

		TRUE_(answer == __realized::bit_reverse_f<12>(question));

	}
	TRY_("8:8")
	{
		using __realized = realize<uint8_t>;
		using T_sigma = typename __realized::sigma_t;

		T_sigma question = 0b01001101;
		T_sigma answer   = 0b10110010;

		TRUE_(answer == __realized::bit_reverse_f<8>(question));

	}
	TRY_("8:6")
	{
		using __realized = realize<uint8_t>;
		using T_sigma = typename __realized::sigma_t;

		T_sigma question = 0b010011;
		T_sigma answer   = 0b110010;

		TRUE_(answer == __realized::bit_reverse_f<6>(question));

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("realize", "bit_reverse")
{
	TRY_("4")
	{
		TRUE_(realized::ratio_f<1>(4) == 0.25);
		TRUE_(realized::ratio_f<2>(4) == 0.50);
		TRUE_(realized::ratio_f<3>(4) == 0.75);
		TRUE_(realized::ratio_f<4>(4) == 1.00);
	}
}


////////////////////////////////////////////////////////////////////////////////

template <int N_sgn=1, int N_rho=0>
void compute_truncate__zoned()
{
	auto const up0 = realized::upsilon_f(0), dn0 = realized::dnsilon_f(0);
	auto const up1 = realized::upsilon_f(1), dn1 = realized::dnsilon_f(1);
	auto const up2 = realized::upsilon_f(2), dn2 = realized::dnsilon_f(2);
	auto const up3 = realized::upsilon_f(3), dn3 = realized::dnsilon_f(3);

	realized::alpha_t x, co = N_sgn*_std::pow(2, N_rho);
	x = co*up2; TRUE_(realized::truncate_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  co*dn0);
	x = co*up1; TRUE_(realized::truncate_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  co*dn0);
//	x = co*up0; TRUE_(realized::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  co*dn0);
	x = co*dn0; TRUE_(realized::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  co*dn0);
	x = co*dn1; TRUE_(realized::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  co*dn1);
	x = co*dn2; TRUE_(realized::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  co*dn2);
	
	x = co*up2; TRUE_(realized::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  co*dn1);
	x = co*up1; TRUE_(realized::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  co*dn1);
	x = co*up0; TRUE_(realized::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  co*dn1);
	x = co*dn0; TRUE_(realized::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  co*dn1);
	x = co*dn1; TRUE_(realized::truncate_f<1>(x, N_rho) ==     0); TRUE_(x ==  co*dn1);
	x = co*dn2; TRUE_(realized::truncate_f<1>(x, N_rho) ==     0); TRUE_(x ==  co*dn2);
	
	x = co*up2; TRUE_(realized::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  co*dn2);
	x = co*up1; TRUE_(realized::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  co*dn2);
	x = co*up0; TRUE_(realized::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  co*dn2);
	x = co*dn0; TRUE_(realized::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  co*dn2);
	x = co*dn1; TRUE_(realized::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  co*dn2);
	x = co*dn2; TRUE_(realized::truncate_f<2>(x, N_rho) ==     0); TRUE_(x ==  co*dn2);

}
TAG_("realize", "truncate")
{
	TRY_("zoned") {
		compute_truncate__zoned< 1,  2>(); compute_truncate__zoned<-1,  2>();
		compute_truncate__zoned< 1,  1>(); compute_truncate__zoned<-1,  1>();
		compute_truncate__zoned< 1,  0>(); compute_truncate__zoned<-1,  0>();
		compute_truncate__zoned< 1, -1>(); compute_truncate__zoned<-1, -1>();
		compute_truncate__zoned< 1, -2>(); compute_truncate__zoned<-1, -2>();

		auto const up0 = realized::upsilon_f(0), dn0 = realized::dnsilon_f(0);
		auto const up1 = realized::upsilon_f(1), dn1 = realized::dnsilon_f(1);
		auto const up2 = realized::upsilon_f(2), dn2 = realized::dnsilon_f(2);
		auto const up3 = realized::upsilon_f(3), dn3 = realized::dnsilon_f(3);

		realized::alpha_t x;

		x = 3.142; TRUE_(realized::truncate_f<1>(x, 1) == 1); TRUE_(x == 2*dn1);
		x = 3.142; TRUE_(realized::truncate_f<1>(x, 2) == 0); TRUE_(x == 3.142);

	}
}


////////////////////////////////////////////////////////////////////////////////

template <int N_sgn=1, int N_rho=0>
void compute_puncture__real_zoned()
{
	auto const up0 = realized::upsilon_f(0), dn0 = realized::dnsilon_f(0);
	auto const up1 = realized::upsilon_f(1), dn1 = realized::dnsilon_f(1);
	auto const up2 = realized::upsilon_f(2), dn2 = realized::dnsilon_f(2);
	auto const up3 = realized::upsilon_f(3), dn3 = realized::dnsilon_f(3);

	realized::alpha_t x, co = N_sgn*_std::pow(2, N_rho);
	
	x = co*up2; TRUE_(realized::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  co*up2);
	x = co*up1; TRUE_(realized::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  co*up1);
	x = co*up0; TRUE_(realized::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  co*up0);
//	x = co*dn0; TRUE_(realized::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  co*up0);
	x = co*dn1; TRUE_(realized::puncture_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  co*up0);
	x = co*dn2; TRUE_(realized::puncture_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  co*up0);
	
	x = co*up2; TRUE_(realized::puncture_f<1>(x, N_rho) ==     0); TRUE_(x ==  co*up2);
	x = co*up1; TRUE_(realized::puncture_f<1>(x, N_rho) ==     0); TRUE_(x ==  co*up1);
	x = co*up0; TRUE_(realized::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  co*up1);
	x = co*dn0; TRUE_(realized::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  co*up1);
	x = co*dn1; TRUE_(realized::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  co*up1);
	x = co*dn2; TRUE_(realized::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  co*up1);
	
	x = co*up2; TRUE_(realized::puncture_f<2>(x, N_rho) ==     0); TRUE_(x ==  co*up2);
	x = co*up1; TRUE_(realized::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  co*up2);
	x = co*up0; TRUE_(realized::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  co*up2);
	x = co*dn0; TRUE_(realized::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  co*up2);
	x = co*dn1; TRUE_(realized::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  co*up2);
	x = co*dn2; TRUE_(realized::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  co*up2);

}
template <int N_sgn=1>
void compute_puncture__real_unzoned()
{
	auto const oo0 = realized::minimal_f(0);
	auto const oo1 = realized::minimal_f(1);
	auto const oo2 = realized::minimal_f(2);
	auto const oo3 = realized::minimal_f(3);

	realized::alpha_t w, x, y, co = N_sgn;

	w = x = co*oo2; y = realized::puncture_f<0>(x); TRUE_(y ==     0); TRUE_(x == co*oo2);
	w = x = co*oo1; y = realized::puncture_f<0>(x); TRUE_(y ==     0); TRUE_(x == co*oo1);
	w = x = co*oo0; y = realized::puncture_f<0>(x); TRUE_(y ==     0); TRUE_(x == co*oo0);
//	w = x =      0; y = realized::puncture_f<0>(x); TRUE_(y == N_sgn); TRUE_(x == co*oo0);

	w = x = co*oo2; y = realized::puncture_f<1>(x); TRUE_(y ==     0); TRUE_(x == co*oo2);
	w = x = co*oo1; y = realized::puncture_f<1>(x); TRUE_(y ==     0); TRUE_(x == co*oo1);
	w = x = co*oo0; y = realized::puncture_f<1>(x); TRUE_(y == N_sgn); TRUE_(x == co*oo1);
//	w = x =      0; y = realized::puncture_f<1>(x); TRUE_(y == N_sgn); TRUE_(x == co*oo1);

	w = x = co*oo2; y = realized::puncture_f<2>(x); TRUE_(y ==     0); TRUE_(x == co*oo2);
	w = x = co*oo1; y = realized::puncture_f<2>(x); TRUE_(y == N_sgn); TRUE_(x == co*oo2);
	w = x = co*oo0; y = realized::puncture_f<2>(x); TRUE_(y == N_sgn); TRUE_(x == co*oo2);
//	w = x =      0; y = realized::puncture_f<2>(x); TRUE_(y == N_sgn); TRUE_(x == co*oo2);

}
TAG_("realize", "puncture")
{
	TRY_("real zoned")
	{
		compute_puncture__real_zoned< 1,  2>(); compute_puncture__real_zoned<-1,  2>();
		compute_puncture__real_zoned< 1,  1>(); compute_puncture__real_zoned<-1,  1>();
		compute_puncture__real_zoned< 1,  0>(); compute_puncture__real_zoned<-1,  0>();
		compute_puncture__real_zoned< 1, -1>(); compute_puncture__real_zoned<-1, -1>();
		compute_puncture__real_zoned< 1, -2>(); compute_puncture__real_zoned<-1, -2>();

	}
	TRY_("real unzoned")
	{
		compute_puncture__real_unzoned< 1>();
		compute_puncture__real_unzoned<-1>();

		auto const up0 = realized::upsilon_f(0), dn0 = realized::dnsilon_f(0);
		auto const up1 = realized::upsilon_f(1), dn1 = realized::dnsilon_f(1);
		auto const up2 = realized::upsilon_f(2), dn2 = realized::dnsilon_f(2);
		auto const up3 = realized::upsilon_f(3), dn3 = realized::dnsilon_f(3);

		realized::alpha_t x;

		x = 3.142; TRUE_(realized::puncture_f<1>(x, 1) == 0); TRUE_(x == 3.142);
		x = 3.142; TRUE_(realized::puncture_f<1>(x, 2) == 1); TRUE_(x == 4*up1);

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("realize", "puncture", "truncate")
{
	using T_sigma = typename realized::sigma_t;
	using T_delta = typename realized::delta_t;
	using T_alpha = typename realized::alpha_t;
	using T_aphex = typename realized::aphex_t;

	auto mt19937_f = typename realized::mt19937_t();
	mt19937_f.seed(Catch::rngSeed());

	EST_("complex fracture")
	{
		T_alpha constexpr two = 2;
		T_aphex z{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = realized::mantissa_f(mt19937_f); x = _std::pow(two, x);
			auto y = realized::mantissa_f(mt19937_f); y = _std::pow(two, y);
			z *= realized::truncated_f<0>(realized::punctured_f<0>(T_aphex {x, y}), 0);
		}
		return z;
	};
	TRY_("complex fracture")
	{
		T_delta constexpr N_zoom = 4;
		T_alpha constexpr F = _std::numeric_limits<T_alpha>::infinity();
		T_alpha constexpr E = _std::numeric_limits<T_alpha>::max();

		auto const square_0 = T_aphex {0, 0};
		auto const square_H = T_aphex {1, 1}*(0.5);
		auto const square_1 = T_aphex {1, 1};
		auto const square_2 = T_aphex {2, 2};
		auto const square_F = T_aphex {F, F};
		auto const square_E = T_aphex {E, E};
		auto const circle_1 = T_aphex {1, 1}*_std::sqrt(0.5);

		TRUE_(realized::truncated_f<N_zoom>(square_2) == square_2);
		TRUE_(realized::punctured_f<N_zoom>(square_2) == square_2);

		TRUE_(computrim_f<0>(realized::truncated_f<N_zoom>(square_F)) == computrim_f<0>(square_1*realized::maximal_f(N_zoom)));
		TRUE_(computrim_f<0>(realized::punctured_f<N_zoom>(square_0)) == computrim_f<0>(square_1*realized::minimal_f(N_zoom)));

		TRUE_(computrim_f<0>(realized::truncated_f<N_zoom>(square_F, 0)) == computrim_f<0>(circle_1*realized::dnsilon_f(N_zoom)));
		TRUE_(computrim_f<0>(realized::truncated_f<N_zoom>(square_2, 0)) == computrim_f<0>(circle_1*realized::dnsilon_f(N_zoom)));
		TRUE_(computrim_f<0>(realized::punctured_f<N_zoom>(square_H, 0)) == computrim_f<0>(circle_1*realized::upsilon_f(N_zoom)));

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
