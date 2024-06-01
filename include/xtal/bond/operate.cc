#pragma once
#include "./any.cc"
#include "./operate.hh"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "root")
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


	TRY_("trial")
	{
		EST_("real root<-1,~0>")
		{
			T_alpha constexpr two = 2;
			T_alpha w{};
			for (T_sigma i = 0x100; ~--i;) {
				auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
				w *= Op::root_f<-1,~0>(x)/0x100;
			}
			return w;
		};
		EST_("real root<-1, 1>")
		{
			T_alpha constexpr two = 2;
			T_alpha w{};
			for (T_sigma i = 0x100; ~--i;) {
				auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
				w *= Op::root_f<-1, 1>(x)/0x100;
			}
			return w;
		};
	};
}
TAG_("operate", "logarithm")
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


	EST_("real std::log")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
			//\
			w += Op::logarithm_f(x);
			w += _std::log(x);
		}
		return w;
	};
	EST_("real logarithm_f<+4>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w += Op::logarithm_f<+4>(x);
		}
		return w;
	};
	EST_("real logarithm_f<+2>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w += Op::logarithm_f<+2>(x);
		}
		return w;
	};
	EST_("real logarithm_f< 0>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w += Op::logarithm_f< 0>(x);
		}
		return w;
	};

	TRY_("real logarithm")
	{
		T_alpha const x = 2;
		T_alpha const y = _std::log(x);
		TRUE_(computrim_f<52+0>(y) == computrim_f<52+0>(Op::logarithm_f<-1>(x)));

		TRUE_(computrim_f<50+1>(y) == computrim_f<50+1>(Op::logarithm_f<+4>(x)));
		TRUE_(computrim_f<40+0>(y) == computrim_f<40+0>(Op::logarithm_f<+3>(x)));
		TRUE_(computrim_f<30+0>(y) == computrim_f<30+0>(Op::logarithm_f<+2>(x)));
		TRUE_(computrim_f<20+0>(y) == computrim_f<20+0>(Op::logarithm_f<+1>(x)));
		TRUE_(computrim_f<10-2>(y) == computrim_f<10-2>(Op::logarithm_f<+0>(x)));

	}
}
TAG_("operate", "exponential")
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


	EST_("real std::exp")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w += _std::exp(x);
		}
		return w;
	};

	EST_("real antilogarithm_f<2, 0>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w *= Op::antilogarithm_f<2, 0>(x);
		}
		return w;
	};
	EST_("real antilogarithm_f<1, 0>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w *= Op::antilogarithm_f<1, 0>(x);
		}
		return w;
	};

	EST_("real antilogarithmic_f<2, 0>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w *= Op::antilogarithmic_f<2, 0>(x);
		}
		return w;
	};
	EST_("real antilogarithmic_f<1, 0>")
	{
		T_alpha constexpr two = 2;
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
			w *= Op::antilogarithmic_f<1, 0>(x);
		}
		return w;
	};

	TRY_("real exponential")
	{
		T_alpha const x = 5.5;
		T_alpha const y = _std::exp(x);
	//	TRUE_(computrim_f<52+0>(y) == computrim_f<52+0>(Op::antilogarithm_f<-1>(x)));

		TRUE_(computrim_f<40+1>(y) == computrim_f<40+1>(Op::antilogarithm_f<+2, 0>(x)));
		TRUE_(computrim_f<40+1>(y) == computrim_f<40+1>(Op::antilogarithm_f<+1, 1>(x)));
		TRUE_(computrim_f<40+0>(y) == computrim_f<40+0>(Op::antilogarithm_f<+1, 0>(x)));
		TRUE_(computrim_f<10+5>(y) == computrim_f<10+5>(Op::antilogarithm_f<+0, 1>(x)));

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "bit_reverse")
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


	TRY_("32:03")
	{
		using Op = operate<uint32_t>;
		using T_sigma = typename Op::sigma_t;

		T_sigma question = 0b011;
		T_sigma answer   = 0b110;

		TRUE_(answer == Op::bit_reverse_f<3>(question));

	}
	TRY_("16:16")
	{
		using Op = operate<uint16_t>;
		using T_sigma = typename Op::sigma_t;

		T_sigma question = 0b0100100011100101;
		T_sigma answer   = 0b1010011100010010;

		TRUE_(answer == Op::bit_reverse_f<16>(question));

	}
	TRY_("16:12")
	{
		using Op = operate<uint16_t>;
		using T_sigma = typename Op::sigma_t;

		T_sigma question = 0b010010001110;
		T_sigma answer   = 0b011100010010;

		TRUE_(answer == Op::bit_reverse_f<12>(question));

	}
	TRY_("8:8")
	{
		using Op = operate<uint8_t>;
		using T_sigma = typename Op::sigma_t;

		T_sigma question = 0b01001101;
		T_sigma answer   = 0b10110010;

		TRUE_(answer == Op::bit_reverse_f<8>(question));

	}
	TRY_("8:6")
	{
		using Op = operate<uint8_t>;
		using T_sigma = typename Op::sigma_t;

		T_sigma question = 0b010011;
		T_sigma answer   = 0b110010;

		TRUE_(answer == Op::bit_reverse_f<6>(question));

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "bit_reverse")
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


	TRY_("4")
	{
		TRUE_(Op::ratio_f(1, 4) == 0.25);
		TRUE_(Op::ratio_f(2, 4) == 0.50);
		TRUE_(Op::ratio_f(3, 4) == 0.75);
		TRUE_(Op::ratio_f(4, 4) == 1.00);
	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "fraction")
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


	XTAL_LET_(T_alpha) two =  2;
	XTAL_LET_(T_alpha) ten = 10;


	TRY_("comparing implementations")
	{
		for (T_sigma i = 0x100; ~--i;) {
			T_alpha const u = ten*Op::mantissa_f(mt19937_f);
			TRUE_(computrim_f<16>(Op::fraction_f(u)) == computrim_f<16>(u - _std::round(u)));
		}
	};
	EST_("wrap via integral arithmetic")
	{
		T_delta w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto const u = ten*Op::mantissa_f(mt19937_f);
			w ^= Op::fractional_f(u);
		}
		return w;
	};
	EST_("wrap via floating-point arithmetic")
	{
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto const u = ten*Op::mantissa_f(mt19937_f);
			w *= u - _std::round(u);
		}
		return w;
	};
}


////////////////////////////////////////////////////////////////////////////////

template <int N_sgn=1, int N_rho=0>
void compute_truncate__zoned()
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


	auto const up0 = Op::upsilon_f(0), dn0 = Op::dnsilon_f(0);
	auto const up1 = Op::upsilon_f(1), dn1 = Op::dnsilon_f(1);
	auto const up2 = Op::upsilon_f(2), dn2 = Op::dnsilon_f(2);
	auto const up3 = Op::upsilon_f(3), dn3 = Op::dnsilon_f(3);

	Op::alpha_t x{}, a = N_sgn*_std::pow(2, N_rho);
	x = a*up2; TRUE_(Op::truncate_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn0);
	x = a*up1; TRUE_(Op::truncate_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn0);
//	x = a*up0; TRUE_(Op::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*dn0);
	x = a*dn0; TRUE_(Op::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*dn0);
	x = a*dn1; TRUE_(Op::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*dn1);
	x = a*dn2; TRUE_(Op::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*dn2);
	
	x = a*up2; TRUE_(Op::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn1);
	x = a*up1; TRUE_(Op::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn1);
	x = a*up0; TRUE_(Op::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn1);
	x = a*dn0; TRUE_(Op::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn1);
	x = a*dn1; TRUE_(Op::truncate_f<1>(x, N_rho) ==     0); TRUE_(x ==  a*dn1);
	x = a*dn2; TRUE_(Op::truncate_f<1>(x, N_rho) ==     0); TRUE_(x ==  a*dn2);
	
	x = a*up2; TRUE_(Op::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn2);
	x = a*up1; TRUE_(Op::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn2);
	x = a*up0; TRUE_(Op::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn2);
	x = a*dn0; TRUE_(Op::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn2);
	x = a*dn1; TRUE_(Op::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn2);
	x = a*dn2; TRUE_(Op::truncate_f<2>(x, N_rho) ==     0); TRUE_(x ==  a*dn2);

}
TAG_("operate", "truncate")
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


	TRY_("zoned") {
		compute_truncate__zoned< 1,  2>(); compute_truncate__zoned<-1,  2>();
		compute_truncate__zoned< 1,  1>(); compute_truncate__zoned<-1,  1>();
		compute_truncate__zoned< 1,  0>(); compute_truncate__zoned<-1,  0>();
		compute_truncate__zoned< 1, -1>(); compute_truncate__zoned<-1, -1>();
		compute_truncate__zoned< 1, -2>(); compute_truncate__zoned<-1, -2>();

		auto const up0 = Op::upsilon_f(0), dn0 = Op::dnsilon_f(0);
		auto const up1 = Op::upsilon_f(1), dn1 = Op::dnsilon_f(1);
		auto const up2 = Op::upsilon_f(2), dn2 = Op::dnsilon_f(2);
		auto const up3 = Op::upsilon_f(3), dn3 = Op::dnsilon_f(3);

		Op::alpha_t x{};

		x = 3.142; TRUE_(Op::truncate_f<1>(x, 1) == 1); TRUE_(x == 2*dn1);
		x = 3.142; TRUE_(Op::truncate_f<1>(x, 2) == 0); TRUE_(x == 3.142);

	}
}


////////////////////////////////////////////////////////////////////////////////

template <int N_sgn=1, int N_rho=0>
void compute_puncture__real_zoned()
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


	auto const up0 = Op::upsilon_f(0), dn0 = Op::dnsilon_f(0);
	auto const up1 = Op::upsilon_f(1), dn1 = Op::dnsilon_f(1);
	auto const up2 = Op::upsilon_f(2), dn2 = Op::dnsilon_f(2);
	auto const up3 = Op::upsilon_f(3), dn3 = Op::dnsilon_f(3);

	Op::alpha_t x{}, a = N_sgn*_std::pow(2, N_rho);
	
	x = a*up2; TRUE_(Op::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*up2);
	x = a*up1; TRUE_(Op::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*up1);
	x = a*up0; TRUE_(Op::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*up0);
//	x = a*dn0; TRUE_(Op::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*up0);
	x = a*dn1; TRUE_(Op::puncture_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  a*up0);
	x = a*dn2; TRUE_(Op::puncture_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  a*up0);
	
	x = a*up2; TRUE_(Op::puncture_f<1>(x, N_rho) ==     0); TRUE_(x ==  a*up2);
	x = a*up1; TRUE_(Op::puncture_f<1>(x, N_rho) ==     0); TRUE_(x ==  a*up1);
	x = a*up0; TRUE_(Op::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*up1);
	x = a*dn0; TRUE_(Op::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*up1);
	x = a*dn1; TRUE_(Op::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*up1);
	x = a*dn2; TRUE_(Op::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*up1);
	
	x = a*up2; TRUE_(Op::puncture_f<2>(x, N_rho) ==     0); TRUE_(x ==  a*up2);
	x = a*up1; TRUE_(Op::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*up2);
	x = a*up0; TRUE_(Op::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*up2);
	x = a*dn0; TRUE_(Op::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*up2);
	x = a*dn1; TRUE_(Op::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*up2);
	x = a*dn2; TRUE_(Op::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*up2);

}
template <int N_sgn=1>
void compute_puncture__real_unzoned()
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


	auto const oo0 = Op::minimal_f(0);
	auto const oo1 = Op::minimal_f(1);
	auto const oo2 = Op::minimal_f(2);
	auto const oo3 = Op::minimal_f(3);

	Op::alpha_t w{}, x{}, y{}, a = N_sgn;

	w = x = a*oo2; y = Op::puncture_f<0>(x); TRUE_(y ==     0); TRUE_(x == a*oo2);
	w = x = a*oo1; y = Op::puncture_f<0>(x); TRUE_(y ==     0); TRUE_(x == a*oo1);
	w = x = a*oo0; y = Op::puncture_f<0>(x); TRUE_(y ==     0); TRUE_(x == a*oo0);
//	w = x =      0; y = Op::puncture_f<0>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo0);

	w = x = a*oo2; y = Op::puncture_f<1>(x); TRUE_(y ==     0); TRUE_(x == a*oo2);
	w = x = a*oo1; y = Op::puncture_f<1>(x); TRUE_(y ==     0); TRUE_(x == a*oo1);
	w = x = a*oo0; y = Op::puncture_f<1>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo1);
//	w = x =      0; y = Op::puncture_f<1>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo1);

	w = x = a*oo2; y = Op::puncture_f<2>(x); TRUE_(y ==     0); TRUE_(x == a*oo2);
	w = x = a*oo1; y = Op::puncture_f<2>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo2);
	w = x = a*oo0; y = Op::puncture_f<2>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo2);
//	w = x =      0; y = Op::puncture_f<2>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo2);

}
TAG_("operate", "puncture")
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


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

		auto const up0 = Op::upsilon_f(0), dn0 = Op::dnsilon_f(0);
		auto const up1 = Op::upsilon_f(1), dn1 = Op::dnsilon_f(1);
		auto const up2 = Op::upsilon_f(2), dn2 = Op::dnsilon_f(2);
		auto const up3 = Op::upsilon_f(3), dn3 = Op::dnsilon_f(3);

		Op::alpha_t x{};

		x = 3.142; TRUE_(Op::puncture_f<1>(x, 1) == 0); TRUE_(x == 3.142);
		x = 3.142; TRUE_(Op::puncture_f<1>(x, 2) == 1); TRUE_(x == 4*up1);

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "puncture", "truncate")
{
	using Op = operating;
	using T_sigma = typename Op::sigma_t;
	using T_delta = typename Op::delta_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;
	auto mt19937_f = typename Op::mt19937_t(Catch::rngSeed());


	TRY_("trial")
	{
		EST_("complex fracture")
		{
			T_alpha constexpr two = 2;
			T_aphex z{};
			for (T_sigma i = 0x100; ~--i;) {
				auto x = Op::mantissa_f(mt19937_f); x = _std::pow(two, x);
				auto y = Op::mantissa_f(mt19937_f); y = _std::pow(two, y);
				z *= Op::truncated_f<0>(Op::punctured_f<0>(T_aphex{x, y}), 0);
			}
			return z;
		};
	}
	TRY_("complex fracture")
	{
		T_delta constexpr N_zoom = 4;
		T_alpha constexpr F = _std::numeric_limits<T_alpha>::infinity();
		T_alpha constexpr E = _std::numeric_limits<T_alpha>::max();

		auto const square_0 = T_aphex{0, 0};
		auto const square_H = T_aphex{1, 1}*(0.5);
		auto const square_1 = T_aphex{1, 1};
		auto const square_2 = T_aphex{2, 2};
		auto const square_F = T_aphex{F, F};
		auto const square_E = T_aphex{E, E};
		auto const circle_1 = T_aphex{1, 1}*_std::sqrt(0.5);

		TRUE_(Op::truncated_f<N_zoom>(square_2) == square_2);
		TRUE_(Op::punctured_f<N_zoom>(square_2) == square_2);

		TRUE_(computrim_f<0>(Op::truncated_f<N_zoom>(square_F)) == computrim_f<0>(square_1*Op::maximal_f(N_zoom)));
		TRUE_(computrim_f<0>(Op::punctured_f<N_zoom>(square_0)) == computrim_f<0>(square_1*Op::minimal_f(N_zoom)));

		TRUE_(computrim_f<0>(Op::truncated_f<N_zoom>(square_F, 0)) == computrim_f<0>(circle_1*Op::dnsilon_f(N_zoom)));
		TRUE_(computrim_f<0>(Op::truncated_f<N_zoom>(square_2, 0)) == computrim_f<0>(circle_1*Op::dnsilon_f(N_zoom)));
		TRUE_(computrim_f<0>(Op::punctured_f<N_zoom>(square_H, 0)) == computrim_f<0>(circle_1*Op::upsilon_f(N_zoom)));

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
