#pragma once
#include "./realize.hpp"




#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::common::__realize
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/common/realize.hpp#bit_reverse 32:03")
{
	using _realized = realize<uint32_t>;
	using sigma_t = typename _realized::sigma_t;

	sigma_t question = 0b011;
	sigma_t answer   = 0b110;

	REQUIRE(answer == _realized::bit_reverse_y<3>(question));

}
TEST_CASE("xtal/common/realize.hpp#bit_reverse 16:16")
{
	using _realized = realize<uint16_t>;
	using sigma_t = typename _realized::sigma_t;

	sigma_t question = 0b0100100011100101;
	sigma_t answer   = 0b1010011100010010;

	REQUIRE(answer == _realized::bit_reverse_y<16>(question));

}
TEST_CASE("xtal/common/realize.hpp#bit_reverse 16:12")
{
	using _realized = realize<uint16_t>;
	using sigma_t = typename _realized::sigma_t;

	sigma_t question = 0b010010001110;
	sigma_t answer   = 0b011100010010;

	REQUIRE(answer == _realized::bit_reverse_y<12>(question));

}
TEST_CASE("xtal/common/realize.hpp#bit_reverse 8:8")
{
	using _realized = realize<uint8_t>;
	using sigma_t = typename _realized::sigma_t;

	sigma_t question = 0b01001101;
	sigma_t answer   = 0b10110010;

	REQUIRE(answer == _realized::bit_reverse_y<8>(question));

}
TEST_CASE("xtal/common/realize.hpp#bit_reverse 8:6")
{
	using _realized = realize<uint8_t>;
	using sigma_t = typename _realized::sigma_t;

	sigma_t question = 0b010011;
	sigma_t answer   = 0b110010;

	REQUIRE(answer == _realized::bit_reverse_y<6>(question));

}
/***/
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/common/realize.hpp: ratio")
{
	REQUIRE(realized::ratio_y<1>(4) == 0.25);
	REQUIRE(realized::ratio_y<2>(4) == 0.50);
	REQUIRE(realized::ratio_y<3>(4) == 0.75);
	REQUIRE(realized::ratio_y<4>(4) == 1.00);

}

////////////////////////////////////////////////////////////////////////////////

template <int N_sgn=1, int N_rho=0>
void realize_truncate__test()
{
	auto const up0 = realized::upsilon_y(0), dn0 = realized::dnsilon_y(0);
	auto const up1 = realized::upsilon_y(1), dn1 = realized::dnsilon_y(1);
	auto const up2 = realized::upsilon_y(2), dn2 = realized::dnsilon_y(2);
	auto const up3 = realized::upsilon_y(3), dn3 = realized::dnsilon_y(3);

	realized::alpha_t x, co = N_sgn*_std::pow(2, N_rho);
	x = co*up2; REQUIRE(realized::truncate_y<0>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn0);
	x = co*up1; REQUIRE(realized::truncate_y<0>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn0);
//	x = co*up0; REQUIRE(realized::truncate_y<0>(x, N_rho) ==     0); REQUIRE(x ==  co*dn0);
	x = co*dn0; REQUIRE(realized::truncate_y<0>(x, N_rho) ==     0); REQUIRE(x ==  co*dn0);
	x = co*dn1; REQUIRE(realized::truncate_y<0>(x, N_rho) ==     0); REQUIRE(x ==  co*dn1);
	x = co*dn2; REQUIRE(realized::truncate_y<0>(x, N_rho) ==     0); REQUIRE(x ==  co*dn2);
	
	x = co*up2; REQUIRE(realized::truncate_y<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*up1; REQUIRE(realized::truncate_y<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*up0; REQUIRE(realized::truncate_y<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*dn0; REQUIRE(realized::truncate_y<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*dn1; REQUIRE(realized::truncate_y<1>(x, N_rho) ==     0); REQUIRE(x ==  co*dn1);
	x = co*dn2; REQUIRE(realized::truncate_y<1>(x, N_rho) ==     0); REQUIRE(x ==  co*dn2);
	
	x = co*up2; REQUIRE(realized::truncate_y<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*up1; REQUIRE(realized::truncate_y<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*up0; REQUIRE(realized::truncate_y<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*dn0; REQUIRE(realized::truncate_y<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*dn1; REQUIRE(realized::truncate_y<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*dn2; REQUIRE(realized::truncate_y<2>(x, N_rho) ==     0); REQUIRE(x ==  co*dn2);

}
TEST_CASE("xtal/common/realize.hpp: truncate")
{
	realize_truncate__test< 1,  2>(); realize_truncate__test<-1,  2>();
	realize_truncate__test< 1,  1>(); realize_truncate__test<-1,  1>();
	realize_truncate__test< 1,  0>(); realize_truncate__test<-1,  0>();
	realize_truncate__test< 1, -1>(); realize_truncate__test<-1, -1>();
	realize_truncate__test< 1, -2>(); realize_truncate__test<-1, -2>();

	auto const up0 = realized::upsilon_y(0), dn0 = realized::dnsilon_y(0);
	auto const up1 = realized::upsilon_y(1), dn1 = realized::dnsilon_y(1);
	auto const up2 = realized::upsilon_y(2), dn2 = realized::dnsilon_y(2);
	auto const up3 = realized::upsilon_y(3), dn3 = realized::dnsilon_y(3);

	realized::alpha_t x;

	x = 3.142; REQUIRE(realized::truncate_y<1>(x, 1) == 1); REQUIRE(x == 2*dn1);
	x = 3.142; REQUIRE(realized::truncate_y<1>(x, 2) == 0); REQUIRE(x == 3.142);

}

////////////////////////////////////////////////////////////////////////////////

template <int N_sgn=1>
void realize_puncture_real__test()
{
	auto const oo0 = realized::minimal_y(0);
	auto const oo1 = realized::minimal_y(1);
	auto const oo2 = realized::minimal_y(2);
	auto const oo3 = realized::minimal_y(3);

	realized::alpha_t w, x, y, co = N_sgn;

	w = x = co*oo2; y = realized::puncture_y<0>(x); REQUIRE(y ==     0); REQUIRE(x == co*oo2);
	w = x = co*oo1; y = realized::puncture_y<0>(x); REQUIRE(y ==     0); REQUIRE(x == co*oo1);
	w = x = co*oo0; y = realized::puncture_y<0>(x); REQUIRE(y ==     0); REQUIRE(x == co*oo0);
//	w = x =      0; y = realized::puncture_y<0>(x); REQUIRE(y == N_sgn); REQUIRE(x == co*oo0);

	w = x = co*oo2; y = realized::puncture_y<1>(x); REQUIRE(y ==     0); REQUIRE(x == co*oo2);
	w = x = co*oo1; y = realized::puncture_y<1>(x); REQUIRE(y ==     0); REQUIRE(x == co*oo1);
	w = x = co*oo0; y = realized::puncture_y<1>(x); REQUIRE(y == N_sgn); REQUIRE(x == co*oo1);
//	w = x =      0; y = realized::puncture_y<1>(x); REQUIRE(y == N_sgn); REQUIRE(x == co*oo1);

	w = x = co*oo2; y = realized::puncture_y<2>(x); REQUIRE(y ==     0); REQUIRE(x == co*oo2);
	w = x = co*oo1; y = realized::puncture_y<2>(x); REQUIRE(y == N_sgn); REQUIRE(x == co*oo2);
	w = x = co*oo0; y = realized::puncture_y<2>(x); REQUIRE(y == N_sgn); REQUIRE(x == co*oo2);
//	w = x =      0; y = realized::puncture_y<2>(x); REQUIRE(y == N_sgn); REQUIRE(x == co*oo2);

}
TEST_CASE("xtal/common/realize.hpp: puncture real")
{
	realize_puncture_real__test< 1>();
	realize_puncture_real__test<-1>();

	auto const up0 = realized::upsilon_y(0), dn0 = realized::dnsilon_y(0);
	auto const up1 = realized::upsilon_y(1), dn1 = realized::dnsilon_y(1);
	auto const up2 = realized::upsilon_y(2), dn2 = realized::dnsilon_y(2);
	auto const up3 = realized::upsilon_y(3), dn3 = realized::dnsilon_y(3);

	realized::alpha_t x;

	x = 3.142; REQUIRE(realized::puncture_y<1>(x, 1) == 0); REQUIRE(x == 3.142);
	x = 3.142; REQUIRE(realized::puncture_y<1>(x, 2) == 1); REQUIRE(x == 4*up1);

}

template <int N_sgn=1, int N_rho=0>
void realize_puncture_real_zone__test()
{
	auto const up0 = realized::upsilon_y(0), dn0 = realized::dnsilon_y(0);
	auto const up1 = realized::upsilon_y(1), dn1 = realized::dnsilon_y(1);
	auto const up2 = realized::upsilon_y(2), dn2 = realized::dnsilon_y(2);
	auto const up3 = realized::upsilon_y(3), dn3 = realized::dnsilon_y(3);

	realized::alpha_t x, co = N_sgn*_std::pow(2, N_rho);
	
	x = co*up2; REQUIRE(realized::puncture_y<0>(x, N_rho) ==     0); REQUIRE(x ==  co*up2);
	x = co*up1; REQUIRE(realized::puncture_y<0>(x, N_rho) ==     0); REQUIRE(x ==  co*up1);
	x = co*up0; REQUIRE(realized::puncture_y<0>(x, N_rho) ==     0); REQUIRE(x ==  co*up0);
//	x = co*dn0; REQUIRE(realized::puncture_y<0>(x, N_rho) ==     0); REQUIRE(x ==  co*up0);
	x = co*dn1; REQUIRE(realized::puncture_y<0>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up0);
	x = co*dn2; REQUIRE(realized::puncture_y<0>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up0);
	
	x = co*up2; REQUIRE(realized::puncture_y<1>(x, N_rho) ==     0); REQUIRE(x ==  co*up2);
	x = co*up1; REQUIRE(realized::puncture_y<1>(x, N_rho) ==     0); REQUIRE(x ==  co*up1);
	x = co*up0; REQUIRE(realized::puncture_y<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up1);
	x = co*dn0; REQUIRE(realized::puncture_y<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up1);
	x = co*dn1; REQUIRE(realized::puncture_y<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up1);
	x = co*dn2; REQUIRE(realized::puncture_y<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up1);
	
	x = co*up2; REQUIRE(realized::puncture_y<2>(x, N_rho) ==     0); REQUIRE(x ==  co*up2);
	x = co*up1; REQUIRE(realized::puncture_y<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*up0; REQUIRE(realized::puncture_y<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*dn0; REQUIRE(realized::puncture_y<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*dn1; REQUIRE(realized::puncture_y<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*dn2; REQUIRE(realized::puncture_y<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up2);

}
TEST_CASE("xtal/common/realize.hpp: puncture real zone")
{
	realize_puncture_real_zone__test< 1,  2>(); realize_puncture_real_zone__test<-1,  2>();
	realize_puncture_real_zone__test< 1,  1>(); realize_puncture_real_zone__test<-1,  1>();
	realize_puncture_real_zone__test< 1,  0>(); realize_puncture_real_zone__test<-1,  0>();
	realize_puncture_real_zone__test< 1, -1>(); realize_puncture_real_zone__test<-1, -1>();
	realize_puncture_real_zone__test< 1, -2>(); realize_puncture_real_zone__test<-1, -2>();

}

TEST_CASE("xtal/common/realize.hpp: fracture complex")
{
	using sigma_t = typename realized::sigma_t;
	using delta_t = typename realized::delta_t;
	using alpha_t = typename realized::alpha_t;
	using aphex_t = typename realized::aphex_t;

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

	REQUIRE(realized::truncated_y<N_zoom>(square_2) == square_2);
	REQUIRE(realized::punctured_y<N_zoom>(square_2) == square_2);

	REQUIRE(trim_y<0>(realized::truncated_y<N_zoom>(square_F)) == trim_y<0>(square_1*realized::maximal_y(N_zoom)));
	REQUIRE(trim_y<0>(realized::punctured_y<N_zoom>(square_0)) == trim_y<0>(square_1*realized::minimal_y(N_zoom)));

	REQUIRE(trim_y<0>(realized::truncated_y<N_zoom>(square_F, 0)) == trim_y<0>(circle_1*realized::dnsilon_y(N_zoom)));
	REQUIRE(trim_y<0>(realized::truncated_y<N_zoom>(square_2, 0)) == trim_y<0>(circle_1*realized::dnsilon_y(N_zoom)));
	REQUIRE(trim_y<0>(realized::punctured_y<N_zoom>(square_H, 0)) == trim_y<0>(circle_1*realized::upsilon_y(N_zoom)));

	auto mt19937_m = typename realized::mt19937_t();
	mt19937_m.seed(Catch::rngSeed());

	BENCHMARK("fracture")
	{
		alpha_t constexpr two = 2;
		aphex_t z {};
		for (sigma_t i = 192000/100; ~--i;)
		{	auto x = realized::mantissa_y(mt19937_m); x = _std::pow(two, x);
			auto y = realized::mantissa_y(mt19937_m); y = _std::pow(two, y);
			z *= realized::truncated_y<0>(realized::punctured_y<0>(aphex_t {x, y}), 0);
		}
		return z;
	};

}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
