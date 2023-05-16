#pragma once
#include "./realize.hpp"




#include <catch2/catch_all.hpp>

XTAL_ENV_(push)
namespace xtal::any::_realize
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

unsigned int bitReverse(unsigned int x, int O)
{
	int n = 0;
	int mask = 0x1;
	for (int i = 0; i < O; i++)
	{
		n <<= 1;
		n |= (x & 1);
		x >>= 1;
	}
	return n;
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/any/realize.hpp: reverse 32:03")
{
	using realized = realize<uint32_t>;
	using sigma_t = typename realized::sigma_t;

	sigma_t question = 0b011;
	sigma_t answer   = 0b110;

//	REQUIRE(answer == bitReverse(question, 3));
	REQUIRE(answer == bit_reverse_x<3>(question));

}
TEST_CASE("xtal/any/realize.hpp: reverse 16:16")
{
	using realized = realize<uint16_t>;
	using sigma_t = typename realized::sigma_t;

	sigma_t question = 0b0100100011100101;
	sigma_t answer   = 0b1010011100010010;

	REQUIRE(answer == bit_reverse_x<16>(question));

}
TEST_CASE("xtal/any/realize.hpp: reverse 16:12")
{
	using realized = realize<uint16_t>;
	using sigma_t = typename realized::sigma_t;

	sigma_t question = 0b010010001110;
	sigma_t answer   = 0b011100010010;

	REQUIRE(answer == bit_reverse_x<12>(question));

}
TEST_CASE("xtal/any/realize.hpp: reverse 8:8")
{
	using realized = realize<uint8_t>;
	using sigma_t = typename realized::sigma_t;

	sigma_t question = 0b01001101;
	sigma_t answer   = 0b10110010;

	REQUIRE(answer == bit_reverse_x<8>(question));

}
TEST_CASE("xtal/any/realize.hpp: reverse 8:6")
{
	using realized = realize<uint8_t>;
	using sigma_t = typename realized::sigma_t;

	sigma_t question = 0b010011;
	sigma_t answer   = 0b110010;

	REQUIRE(answer == bit_reverse_x<6>(question));

}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/any/realize.hpp: ratio")
{
	REQUIRE(realized::ratio_x<1>(4) == 0.25);
	REQUIRE(realized::ratio_x<2>(4) == 0.50);
	REQUIRE(realized::ratio_x<3>(4) == 0.75);
	REQUIRE(realized::ratio_x<4>(4) == 1.00);

}

////////////////////////////////////////////////////////////////////////////////

template <iota_t N_sgn=1, iota_t N_rho=0>
void realize_expunge__test()
{
	auto const up0 = realized::upsilon_y(0), dn0 = realized::dnsilon_y(0);
	auto const up1 = realized::upsilon_y(1), dn1 = realized::dnsilon_y(1);
	auto const up2 = realized::upsilon_y(2), dn2 = realized::dnsilon_y(2);
	auto const up3 = realized::upsilon_y(3), dn3 = realized::dnsilon_y(3);

	realized::alpha_t x, co = N_sgn*_std::pow(2, N_rho);
	
	x = co*up3; REQUIRE(realized::puncture_z<0>(x, N_rho) ==     0); REQUIRE(x ==  co*up3);
	x = co*up2; REQUIRE(realized::puncture_z<0>(x, N_rho) ==     0); REQUIRE(x ==  co*up2);
	x = co*up1; REQUIRE(realized::puncture_z<0>(x, N_rho) ==     0); REQUIRE(x ==  co*up1);
	x = co*up0; REQUIRE(realized::puncture_z<0>(x, N_rho) ==     0); REQUIRE(x ==  co*up0);
	x = co*dn0; REQUIRE(realized::puncture_z<0>(x, N_rho) ==     0); REQUIRE(x ==  co*up0);
	x = co*dn1; REQUIRE(realized::puncture_z<0>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up0);
	x = co*dn2; REQUIRE(realized::puncture_z<0>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up0);
	x = co*dn3; REQUIRE(realized::puncture_z<0>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up0);
	
	x = co*up3; REQUIRE(realized::puncture_z<1>(x, N_rho) ==     0); REQUIRE(x ==  co*up3);
	x = co*up2; REQUIRE(realized::puncture_z<1>(x, N_rho) ==     0); REQUIRE(x ==  co*up2);
	x = co*up1; REQUIRE(realized::puncture_z<1>(x, N_rho) ==     0); REQUIRE(x ==  co*up1);
	x = co*up0; REQUIRE(realized::puncture_z<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up1);
	x = co*dn0; REQUIRE(realized::puncture_z<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up1);
	x = co*dn1; REQUIRE(realized::puncture_z<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up1);
	x = co*dn2; REQUIRE(realized::puncture_z<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up1);
	x = co*dn3; REQUIRE(realized::puncture_z<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up1);
	
	x = co*up3; REQUIRE(realized::puncture_z<2>(x, N_rho) ==     0); REQUIRE(x ==  co*up3);
	x = co*up2; REQUIRE(realized::puncture_z<2>(x, N_rho) ==     0); REQUIRE(x ==  co*up2);
	x = co*up1; REQUIRE(realized::puncture_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*up0; REQUIRE(realized::puncture_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*dn0; REQUIRE(realized::puncture_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*dn1; REQUIRE(realized::puncture_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*dn2; REQUIRE(realized::puncture_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*dn3; REQUIRE(realized::puncture_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*up2);

}
TEST_CASE("xtal/any/realize.hpp: expunge")
{
	realize_expunge__test< 1,  2>(); realize_expunge__test<-1,  2>();
	realize_expunge__test< 1,  1>(); realize_expunge__test<-1,  1>();
	realize_expunge__test< 1,  0>(); realize_expunge__test<-1,  0>();
	realize_expunge__test< 1, -1>(); realize_expunge__test<-1, -1>();
	realize_expunge__test< 1, -2>(); realize_expunge__test<-1, -2>();

}

////////////////////////////////////////////////////////////////////////////////

template <iota_t N_sgn=1, iota_t N_rho=0>
void realize_truncate__test()
{
	auto const up0 = realized::upsilon_y(0), dn0 = realized::dnsilon_y(0);
	auto const up1 = realized::upsilon_y(1), dn1 = realized::dnsilon_y(1);
	auto const up2 = realized::upsilon_y(2), dn2 = realized::dnsilon_y(2);
	auto const up3 = realized::upsilon_y(3), dn3 = realized::dnsilon_y(3);

	realized::alpha_t x, co = N_sgn*_std::pow(2, N_rho);
//	x = co*up3; REQUIRE(realized::truncate_z<0>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn0);
//	x = co*up2; REQUIRE(realized::truncate_z<0>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn0);
//	x = co*up1; REQUIRE(realized::truncate_z<0>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn0);
//	x = co*up0; REQUIRE(realized::truncate_z<0>(x, N_rho) ==     0); REQUIRE(x ==  co*dn0);
//	x = co*dn0; REQUIRE(realized::truncate_z<0>(x, N_rho) ==     0); REQUIRE(x ==  co*dn0);
//	x = co*dn1; REQUIRE(realized::truncate_z<0>(x, N_rho) ==     0); REQUIRE(x ==  co*dn1);
//	x = co*dn2; REQUIRE(realized::truncate_z<0>(x, N_rho) ==     0); REQUIRE(x ==  co*dn2);
//	x = co*dn3; REQUIRE(realized::truncate_z<0>(x, N_rho) ==     0); REQUIRE(x ==  co*dn3);
	
	x = co*up3; REQUIRE(realized::truncate_z<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*up2; REQUIRE(realized::truncate_z<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*up1; REQUIRE(realized::truncate_z<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*up0; REQUIRE(realized::truncate_z<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*dn0; REQUIRE(realized::truncate_z<1>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*dn1; REQUIRE(realized::truncate_z<1>(x, N_rho) ==     0); REQUIRE(x ==  co*dn1);
	x = co*dn2; REQUIRE(realized::truncate_z<1>(x, N_rho) ==     0); REQUIRE(x ==  co*dn2);
	x = co*dn3; REQUIRE(realized::truncate_z<1>(x, N_rho) ==     0); REQUIRE(x ==  co*dn3);
	
	x = co*up3; REQUIRE(realized::truncate_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*up2; REQUIRE(realized::truncate_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*up1; REQUIRE(realized::truncate_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*up0; REQUIRE(realized::truncate_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*dn0; REQUIRE(realized::truncate_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*dn1; REQUIRE(realized::truncate_z<2>(x, N_rho) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*dn2; REQUIRE(realized::truncate_z<2>(x, N_rho) ==     0); REQUIRE(x ==  co*dn2);
	x = co*dn3; REQUIRE(realized::truncate_z<2>(x, N_rho) ==     0); REQUIRE(x ==  co*dn3);

}
TEST_CASE("xtal/any/realize.hpp: truncate")
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

	x = 3.142; REQUIRE(realized::truncate_z<1>(x, 1) == 1); REQUIRE(x == 2*dn1);
	x = 3.142; REQUIRE(realized::truncate_z<1>(x, 2) == 0); REQUIRE(x == 3.142);

}

////////////////////////////////////////////////////////////////////////////////

template <iota_t N_sgn=1>
void realize_puncture__test()
{
	auto const oo0 = realized::minimal_y(0);
	auto const oo1 = realized::minimal_y(1);
	auto const oo2 = realized::minimal_y(2);
	auto const oo3 = realized::minimal_y(3);

	realized::alpha_t w, x, y, co = N_sgn;
	/**/
	w = x = co*oo3; y = realized::puncture_z<0>(x); REQUIRE(y ==     0); REQUIRE(x ==  co*oo3);
	w = x = co*oo2; y = realized::puncture_z<0>(x); REQUIRE(y ==     0); REQUIRE(x ==  co*oo2);
	w = x = co*oo1; y = realized::puncture_z<0>(x); REQUIRE(y ==     0); REQUIRE(x ==  co*oo1);
	w = x = co*oo0; y = realized::puncture_z<0>(x); REQUIRE(y ==     0); REQUIRE(x ==  co*oo0);
//	w = x =    0.0; y = realized::puncture_z<0>(x); REQUIRE(y ==     0); REQUIRE(x ==  co*0.0);

	w = x = co*oo3; y = realized::puncture_z<1>(x); REQUIRE(y ==     0); REQUIRE(x ==  co*oo3);
	w = x = co*oo2; y = realized::puncture_z<1>(x); REQUIRE(y ==     0); REQUIRE(x ==  co*oo2);
	w = x = co*oo1; y = realized::puncture_z<1>(x); REQUIRE(y ==     0); REQUIRE(x ==  co*oo1);
	w = x = co*oo0; y = realized::puncture_z<1>(x); REQUIRE(y == N_sgn); REQUIRE(x ==  co*oo1);
//	w = x =    0.0; y = realized::puncture_z<1>(x); REQUIRE(y == N_sgn); REQUIRE(x ==  co*oo1);

	w = x = co*oo3; y = realized::puncture_z<2>(x); REQUIRE(y ==     0); REQUIRE(x ==  co*oo3);
	w = x = co*oo2; y = realized::puncture_z<2>(x); REQUIRE(y ==     0); REQUIRE(x ==  co*oo2);
	w = x = co*oo1; y = realized::puncture_z<2>(x); REQUIRE(y == N_sgn); REQUIRE(x ==  co*oo2);
	w = x = co*oo0; y = realized::puncture_z<2>(x); REQUIRE(y == N_sgn); REQUIRE(x ==  co*oo2);
//	w = x =    0.0; y = realized::puncture_z<2>(x); REQUIRE(y == N_sgn); REQUIRE(x ==  co*oo2);

	w = x = co*oo3; y = realized::puncture_z<3>(x); REQUIRE(y ==     0); REQUIRE(x ==  co*oo3);
	w = x = co*oo2; y = realized::puncture_z<3>(x); REQUIRE(y == N_sgn); REQUIRE(x ==  co*oo3);
	w = x = co*oo1; y = realized::puncture_z<3>(x); REQUIRE(y == N_sgn); REQUIRE(x ==  co*oo3);
	w = x = co*oo0; y = realized::puncture_z<3>(x); REQUIRE(y == N_sgn); REQUIRE(x ==  co*oo3);
//	w = x =    0.0; y = realized::puncture_z<3>(x); REQUIRE(y == N_sgn); REQUIRE(x ==  co*oo3);
	/*/
	w = x = co*oo3; y = realized::puncture_z<2>(x); ouch(w, x, y, w != x);
	w = x = co*oo2; y = realized::puncture_z<2>(x); ouch(w, x, y, w != x);
	w = x = co*oo1; y = realized::puncture_z<2>(x); ouch(w, x, y, w != x);
	w = x = co*0.0; y = realized::puncture_z<2>(x); ouch(w, x, y, w != x);
	
	ouch();
	/***/

}
TEST_CASE("xtal/any/realize.hpp: puncture")
{
	realize_puncture__test< 1>();
	realize_puncture__test<-1>();

	auto const up0 = realized::upsilon_y(0), dn0 = realized::dnsilon_y(0);
	auto const up1 = realized::upsilon_y(1), dn1 = realized::dnsilon_y(1);
	auto const up2 = realized::upsilon_y(2), dn2 = realized::dnsilon_y(2);
	auto const up3 = realized::upsilon_y(3), dn3 = realized::dnsilon_y(3);

	realized::alpha_t x;

	x = 3.142; REQUIRE(realized::puncture_z<1>(x, 1) == 0); REQUIRE(x == 3.142);
	x = 3.142; REQUIRE(realized::puncture_z<1>(x, 2) == 1); REQUIRE(x == 4*up1);

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
