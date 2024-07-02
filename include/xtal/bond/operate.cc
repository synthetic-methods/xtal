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
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());

	TRY_("trial")
	{
		EST_("real root<-1,~0>")
		{
			T_alpha constexpr two = 2;
			T_alpha w{};
			for (T_sigma i = 0x100; ~--i;) {
				auto x = _op::mantissa_f(mt19937_f); x = _std::pow(two, x);
				w *= _op::root_f<-1,~0>(x)/0x100;
			}
			return w;
		};
		EST_("real root<-1, 1>")
		{
			T_alpha constexpr two = 2;
			T_alpha w{};
			for (T_sigma i = 0x100; ~--i;) {
				auto x = _op::mantissa_f(mt19937_f); x = _std::pow(two, x);
				w *= _op::root_f<-1, 1>(x)/0x100;
			}
			return w;
		};
	};
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "bit_reverse")
{
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


	TRY_("32:03")
	{
		using _op = operate<uint32_t>;
		T_sigma question = 0b011;
		T_sigma answer   = 0b110;

		TRUE_(answer == _op::bit_reverse_f<3>(question));

	}
	TRY_("16:16")
	{
		using _op = operate<uint16_t>;
		T_sigma question = 0b0100100011100101;
		T_sigma answer   = 0b1010011100010010;

		TRUE_(answer == _op::bit_reverse_f<16>(question));

	}
	TRY_("16:12")
	{
		using _op = operate<uint16_t>;
		T_sigma question = 0b010010001110;
		T_sigma answer   = 0b011100010010;

		TRUE_(answer == _op::bit_reverse_f<12>(question));

	}
	TRY_("8:8")
	{
		using _op = operate<uint8_t>;
		T_sigma question = 0b01001101;
		T_sigma answer   = 0b10110010;

		TRUE_(answer == _op::bit_reverse_f<8>(question));

	}
	TRY_("8:6")
	{
		using _op = operate<uint8_t>;
		T_sigma question = 0b010011;
		T_sigma answer   = 0b110010;

		TRUE_(answer == _op::bit_reverse_f<6>(question));

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "bit_reverse")
{
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


	TRY_("4")
	{
		TRUE_(_op::ratio_f(1, 4) == 0.25);
		TRUE_(_op::ratio_f(2, 4) == 0.50);
		TRUE_(_op::ratio_f(3, 4) == 0.75);
		TRUE_(_op::ratio_f(4, 4) == 1.00);
	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "semifractional")
{
	using _op = operating;
	using T_iota  = typename _op:: iota_type;
	using T_delta = typename _op::delta_type;
	using T_sigma = typename _op::sigma_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());

	TRY_("trial")
	{
		using _qp = bond::operate<T_iota>;
		
		TRUE_(check_f<- 6>(0.2220, _op::haplo_f()*T_alpha(_op::    fractional_f(222.2220))));
		TRUE_(check_f<-24>(0.2220, _qp::haplo_f()*T_alpha(_op::semifractional_f(222.2220))));
		TRUE_(check_f<-24>(0.2220, _qp::haplo_f()*T_alpha(_op::semifractional_f( 22.2220))));
		TRUE_(check_f<-24>(0.2220, _qp::haplo_f()*T_alpha(_op::semifractional_f(  2.2220))));
		TRUE_(check_f<-24>(0.2220, _qp::haplo_f()*T_alpha(_op::semifractional_f(  0.2220))));
		TRUE_(check_f<-21>(0.0222, _qp::haplo_f()*T_alpha(_op::semifractional_f(  0.0222))));
	};
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "fraction")
{
	using _op = operating;
	using T_iota  = typename _op:: iota_type;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


	static constexpr T_alpha two =  2;
	static constexpr T_alpha ten = 10;


	TRY_("comparing implementations")
	{
		for (T_sigma i = 0x100; ~--i;) {
			T_alpha const u = ten*_op::mantissa_f(mt19937_f);
			TRUE_(computrim_f<16>(_op::fraction_f(u)) == computrim_f<16>(u - _std::round(u)));
		}
	};
	EST_("wrap via semintegral arithmetic")
	{
		T_iota w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto const u = ten*_op::mantissa_f(mt19937_f);
			w ^= _op::semifractional_f(u);
		}
		return w;
	};
	EST_("wrap via integral arithmetic")
	{
		T_delta w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto const u = ten*_op::mantissa_f(mt19937_f);
			w ^= _op::fractional_f(u);
		}
		return w;
	};
	EST_("wrap via floating-point arithmetic")
	{
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto const u = ten*_op::mantissa_f(mt19937_f);
			w *= u - _std::round(u);
		}
		return w;
	};
}


////////////////////////////////////////////////////////////////////////////////

template <int N_sgn=1, int N_rho=0>
void compute_truncate__zoned()
{
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


	auto const up0 = _op::upsilon_f(0), dn0 = _op::dnsilon_f(0);
	auto const up1 = _op::upsilon_f(1), dn1 = _op::dnsilon_f(1);
	auto const up2 = _op::upsilon_f(2), dn2 = _op::dnsilon_f(2);
	auto const up3 = _op::upsilon_f(3), dn3 = _op::dnsilon_f(3);

	_op::alpha_type x{}, a = N_sgn*_std::pow(2, N_rho);
	x = a*up2; TRUE_(_op::truncate_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn0);
	x = a*up1; TRUE_(_op::truncate_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn0);
//	x = a*up0; TRUE_(_op::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*dn0);
	x = a*dn0; TRUE_(_op::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*dn0);
	x = a*dn1; TRUE_(_op::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*dn1);
	x = a*dn2; TRUE_(_op::truncate_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*dn2);
	
	x = a*up2; TRUE_(_op::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn1);
	x = a*up1; TRUE_(_op::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn1);
	x = a*up0; TRUE_(_op::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn1);
	x = a*dn0; TRUE_(_op::truncate_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn1);
	x = a*dn1; TRUE_(_op::truncate_f<1>(x, N_rho) ==     0); TRUE_(x ==  a*dn1);
	x = a*dn2; TRUE_(_op::truncate_f<1>(x, N_rho) ==     0); TRUE_(x ==  a*dn2);
	
	x = a*up2; TRUE_(_op::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn2);
	x = a*up1; TRUE_(_op::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn2);
	x = a*up0; TRUE_(_op::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn2);
	x = a*dn0; TRUE_(_op::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn2);
	x = a*dn1; TRUE_(_op::truncate_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*dn2);
	x = a*dn2; TRUE_(_op::truncate_f<2>(x, N_rho) ==     0); TRUE_(x ==  a*dn2);

}
TAG_("operate", "truncate")
{
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


	TRY_("zoned") {
		compute_truncate__zoned< 1,  2>(); compute_truncate__zoned<-1,  2>();
		compute_truncate__zoned< 1,  1>(); compute_truncate__zoned<-1,  1>();
		compute_truncate__zoned< 1,  0>(); compute_truncate__zoned<-1,  0>();
		compute_truncate__zoned< 1, -1>(); compute_truncate__zoned<-1, -1>();
		compute_truncate__zoned< 1, -2>(); compute_truncate__zoned<-1, -2>();

		auto const up0 = _op::upsilon_f(0), dn0 = _op::dnsilon_f(0);
		auto const up1 = _op::upsilon_f(1), dn1 = _op::dnsilon_f(1);
		auto const up2 = _op::upsilon_f(2), dn2 = _op::dnsilon_f(2);
		auto const up3 = _op::upsilon_f(3), dn3 = _op::dnsilon_f(3);

		_op::alpha_type x{};

		x = 3.142; TRUE_(_op::truncate_f<1>(x, 1) == 1); TRUE_(x == 2*dn1);
		x = 3.142; TRUE_(_op::truncate_f<1>(x, 2) == 0); TRUE_(x == 3.142);

	}
}


////////////////////////////////////////////////////////////////////////////////

template <int N_sgn=1, int N_rho=0>
void compute_puncture__real_zoned()
{
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


	auto const up0 = _op::upsilon_f(0), dn0 = _op::dnsilon_f(0);
	auto const up1 = _op::upsilon_f(1), dn1 = _op::dnsilon_f(1);
	auto const up2 = _op::upsilon_f(2), dn2 = _op::dnsilon_f(2);
	auto const up3 = _op::upsilon_f(3), dn3 = _op::dnsilon_f(3);

	_op::alpha_type x{}, a = N_sgn*_std::pow(2, N_rho);
	
	x = a*up2; TRUE_(_op::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*up2);
	x = a*up1; TRUE_(_op::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*up1);
	x = a*up0; TRUE_(_op::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*up0);
//	x = a*dn0; TRUE_(_op::puncture_f<0>(x, N_rho) ==     0); TRUE_(x ==  a*up0);
	x = a*dn1; TRUE_(_op::puncture_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  a*up0);
	x = a*dn2; TRUE_(_op::puncture_f<0>(x, N_rho) == N_sgn); TRUE_(x ==  a*up0);
	
	x = a*up2; TRUE_(_op::puncture_f<1>(x, N_rho) ==     0); TRUE_(x ==  a*up2);
	x = a*up1; TRUE_(_op::puncture_f<1>(x, N_rho) ==     0); TRUE_(x ==  a*up1);
	x = a*up0; TRUE_(_op::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*up1);
	x = a*dn0; TRUE_(_op::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*up1);
	x = a*dn1; TRUE_(_op::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*up1);
	x = a*dn2; TRUE_(_op::puncture_f<1>(x, N_rho) == N_sgn); TRUE_(x ==  a*up1);
	
	x = a*up2; TRUE_(_op::puncture_f<2>(x, N_rho) ==     0); TRUE_(x ==  a*up2);
	x = a*up1; TRUE_(_op::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*up2);
	x = a*up0; TRUE_(_op::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*up2);
	x = a*dn0; TRUE_(_op::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*up2);
	x = a*dn1; TRUE_(_op::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*up2);
	x = a*dn2; TRUE_(_op::puncture_f<2>(x, N_rho) == N_sgn); TRUE_(x ==  a*up2);

}
template <int N_sgn=1>
void compute_puncture__real_unzoned()
{
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


	auto const oo0 = _op::minimal_f(0);
	auto const oo1 = _op::minimal_f(1);
	auto const oo2 = _op::minimal_f(2);
	auto const oo3 = _op::minimal_f(3);

	_op::alpha_type w{}, x{}, y{}, a = N_sgn;

	w = x = a*oo2; y = _op::puncture_f<0>(x); TRUE_(y ==     0); TRUE_(x == a*oo2);
	w = x = a*oo1; y = _op::puncture_f<0>(x); TRUE_(y ==     0); TRUE_(x == a*oo1);
	w = x = a*oo0; y = _op::puncture_f<0>(x); TRUE_(y ==     0); TRUE_(x == a*oo0);
//	w = x =      0; y = _op::puncture_f<0>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo0);

	w = x = a*oo2; y = _op::puncture_f<1>(x); TRUE_(y ==     0); TRUE_(x == a*oo2);
	w = x = a*oo1; y = _op::puncture_f<1>(x); TRUE_(y ==     0); TRUE_(x == a*oo1);
	w = x = a*oo0; y = _op::puncture_f<1>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo1);
//	w = x =      0; y = _op::puncture_f<1>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo1);

	w = x = a*oo2; y = _op::puncture_f<2>(x); TRUE_(y ==     0); TRUE_(x == a*oo2);
	w = x = a*oo1; y = _op::puncture_f<2>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo2);
	w = x = a*oo0; y = _op::puncture_f<2>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo2);
//	w = x =      0; y = _op::puncture_f<2>(x); TRUE_(y == N_sgn); TRUE_(x == a*oo2);

}
TAG_("operate", "puncture")
{
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


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

		auto const up0 = _op::upsilon_f(0), dn0 = _op::dnsilon_f(0);
		auto const up1 = _op::upsilon_f(1), dn1 = _op::dnsilon_f(1);
		auto const up2 = _op::upsilon_f(2), dn2 = _op::dnsilon_f(2);
		auto const up3 = _op::upsilon_f(3), dn3 = _op::dnsilon_f(3);

		_op::alpha_type x{};

		x = 3.142; TRUE_(_op::puncture_f<1>(x, 1) == 0); TRUE_(x == 3.142);
		x = 3.142; TRUE_(_op::puncture_f<1>(x, 2) == 1); TRUE_(x == 4*up1);

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "puncture", "truncate")
{
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


	TRY_("trial")
	{
		EST_("complex fracture")
		{
			T_alpha constexpr two = 2;
			T_aphex z{};
			for (T_sigma i = 0x100; ~--i;) {
				auto x = _op::mantissa_f(mt19937_f); x = _std::pow(two, x);
				auto y = _op::mantissa_f(mt19937_f); y = _std::pow(two, y);
				z *= _op::truncated_f<0>(_op::punctured_f<0>(T_aphex{x, y}), 0);
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

		TRUE_(_op::truncated_f<N_zoom>(square_2) == square_2);
		TRUE_(_op::punctured_f<N_zoom>(square_2) == square_2);

		TRUE_(computrim_f<0>(_op::truncated_f<N_zoom>(square_F)) == computrim_f<0>(square_1*_op::maximal_f(N_zoom)));
		TRUE_(computrim_f<0>(_op::punctured_f<N_zoom>(square_0)) == computrim_f<0>(square_1*_op::minimal_f(N_zoom)));

		TRUE_(computrim_f<0>(_op::truncated_f<N_zoom>(square_F, 0)) == computrim_f<0>(circle_1*_op::dnsilon_f(N_zoom)));
		TRUE_(computrim_f<0>(_op::truncated_f<N_zoom>(square_2, 0)) == computrim_f<0>(circle_1*_op::dnsilon_f(N_zoom)));
		TRUE_(computrim_f<0>(_op::punctured_f<N_zoom>(square_H, 0)) == computrim_f<0>(circle_1*_op::upsilon_f(N_zoom)));

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
