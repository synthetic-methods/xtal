#pragma once
#include "./any.c++"
#include "./realize.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::common::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("realize", "bit_reverse")
{
	TRY_("32:03")
	{
		using _realized = realize<uint32_t>;
		using sigma_t = typename _realized::sigma_t;

		sigma_t question = 0b011;
		sigma_t answer   = 0b110;

		TRUE_(answer == _realized::bit_reverse_f<3>(question));

	}
	TRY_("16:16")
	{
		using _realized = realize<uint16_t>;
		using sigma_t = typename _realized::sigma_t;

		sigma_t question = 0b0100100011100101;
		sigma_t answer   = 0b1010011100010010;

		TRUE_(answer == _realized::bit_reverse_f<16>(question));

	}
	TRY_("16:12")
	{
		using _realized = realize<uint16_t>;
		using sigma_t = typename _realized::sigma_t;

		sigma_t question = 0b010010001110;
		sigma_t answer   = 0b011100010010;

		TRUE_(answer == _realized::bit_reverse_f<12>(question));

	}
	TRY_("8:8")
	{
		using _realized = realize<uint8_t>;
		using sigma_t = typename _realized::sigma_t;

		sigma_t question = 0b01001101;
		sigma_t answer   = 0b10110010;

		TRUE_(answer == _realized::bit_reverse_f<8>(question));

	}
	TRY_("8:6")
	{
		using _realized = realize<uint8_t>;
		using sigma_t = typename _realized::sigma_t;

		sigma_t question = 0b010011;
		sigma_t answer   = 0b110010;

		TRUE_(answer == _realized::bit_reverse_f<6>(question));

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
void realize_truncate__zoned()
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
		realize_truncate__zoned< 1,  2>(); realize_truncate__zoned<-1,  2>();
		realize_truncate__zoned< 1,  1>(); realize_truncate__zoned<-1,  1>();
		realize_truncate__zoned< 1,  0>(); realize_truncate__zoned<-1,  0>();
		realize_truncate__zoned< 1, -1>(); realize_truncate__zoned<-1, -1>();
		realize_truncate__zoned< 1, -2>(); realize_truncate__zoned<-1, -2>();

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
void realize_puncture__real_zoned()
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
void realize_puncture__real_unzoned()
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
		realize_puncture__real_zoned< 1,  2>(); realize_puncture__real_zoned<-1,  2>();
		realize_puncture__real_zoned< 1,  1>(); realize_puncture__real_zoned<-1,  1>();
		realize_puncture__real_zoned< 1,  0>(); realize_puncture__real_zoned<-1,  0>();
		realize_puncture__real_zoned< 1, -1>(); realize_puncture__real_zoned<-1, -1>();
		realize_puncture__real_zoned< 1, -2>(); realize_puncture__real_zoned<-1, -2>();

	}
	TRY_("real unzoned")
	{
		realize_puncture__real_unzoned< 1>();
		realize_puncture__real_unzoned<-1>();

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
	using sigma_t = typename realized::sigma_t;
	using delta_t = typename realized::delta_t;
	using alpha_t = typename realized::alpha_t;
	using aphex_t = typename realized::aphex_t;

	auto mt19937_m = typename realized::mt19937_t();
	mt19937_m.seed(Catch::rngSeed());

	EST_("complex fracture")
	{
		alpha_t constexpr two = 2;
		aphex_t z{};
		for (sigma_t i = 192000/100; ~--i;) {
			auto x = realized::mantissa_f(mt19937_m); x = _std::pow(two, x);
			auto y = realized::mantissa_f(mt19937_m); y = _std::pow(two, y);
			z *= realized::truncated_f<0>(realized::punctured_f<0>(aphex_t {x, y}), 0);
		}
		return z;
	};
	TRY_("complex fracture")
	{
		delta_t constexpr N_zoom = 4;
		alpha_t constexpr F = _std::numeric_limits<alpha_t>::infinity();
		alpha_t constexpr E = _std::numeric_limits<alpha_t>::max();

		auto const square_0 = aphex_t {0, 0};
		auto const square_H = aphex_t {1, 1}*(0.5);
		auto const square_1 = aphex_t {1, 1};
		auto const square_2 = aphex_t {2, 2};
		auto const square_F = aphex_t {F, F};
		auto const square_E = aphex_t {E, E};
		auto const circle_1 = aphex_t {1, 1}*_std::sqrt(0.5);

		TRUE_(realized::truncated_f<N_zoom>(square_2) == square_2);
		TRUE_(realized::punctured_f<N_zoom>(square_2) == square_2);

		TRUE_(trim_f<0>(realized::truncated_f<N_zoom>(square_F)) == trim_f<0>(square_1*realized::maximal_f(N_zoom)));
		TRUE_(trim_f<0>(realized::punctured_f<N_zoom>(square_0)) == trim_f<0>(square_1*realized::minimal_f(N_zoom)));

		TRUE_(trim_f<0>(realized::truncated_f<N_zoom>(square_F, 0)) == trim_f<0>(circle_1*realized::dnsilon_f(N_zoom)));
		TRUE_(trim_f<0>(realized::truncated_f<N_zoom>(square_2, 0)) == trim_f<0>(circle_1*realized::dnsilon_f(N_zoom)));
		TRUE_(trim_f<0>(realized::punctured_f<N_zoom>(square_H, 0)) == trim_f<0>(circle_1*realized::upsilon_f(N_zoom)));

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
