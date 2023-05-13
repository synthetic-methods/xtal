#pragma once
#include "./realize.hpp"




#include <catch2/catch_all.hpp>

XTAL_ENV_(push)
namespace xtal::any::_test::realize
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <iota_t N_sgn=1, iota_t N_rho=0>
void realize_expunge__test()
{
	auto const up0 = realized::upsilon_y(0), dn0 = realized::dnsilon_y(0);
	auto const up1 = realized::upsilon_y(1), dn1 = realized::dnsilon_y(1);
	auto const up2 = realized::upsilon_y(2), dn2 = realized::dnsilon_y(2);
	auto const up3 = realized::upsilon_y(3), dn3 = realized::dnsilon_y(3);

	realized::alpha_t x, co = N_sgn*_std::pow(2, N_rho);
	
	x = co*up3; REQUIRE(realized::expunge_z<0, N_rho>(x) ==     0); REQUIRE(x ==  co*up3);
	x = co*up2; REQUIRE(realized::expunge_z<0, N_rho>(x) ==     0); REQUIRE(x ==  co*up2);
	x = co*up1; REQUIRE(realized::expunge_z<0, N_rho>(x) ==     0); REQUIRE(x ==  co*up1);
	x = co*up0; REQUIRE(realized::expunge_z<0, N_rho>(x) ==     0); REQUIRE(x ==  co*up0);
	x = co*dn0; REQUIRE(realized::expunge_z<0, N_rho>(x) ==     0); REQUIRE(x ==  co*up0);
	x = co*dn1; REQUIRE(realized::expunge_z<0, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up0);
	x = co*dn2; REQUIRE(realized::expunge_z<0, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up0);
	x = co*dn3; REQUIRE(realized::expunge_z<0, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up0);
	
	x = co*up3; REQUIRE(realized::expunge_z<1, N_rho>(x) ==     0); REQUIRE(x ==  co*up3);
	x = co*up2; REQUIRE(realized::expunge_z<1, N_rho>(x) ==     0); REQUIRE(x ==  co*up2);
	x = co*up1; REQUIRE(realized::expunge_z<1, N_rho>(x) ==     0); REQUIRE(x ==  co*up1);
	x = co*up0; REQUIRE(realized::expunge_z<1, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up1);
	x = co*dn0; REQUIRE(realized::expunge_z<1, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up1);
	x = co*dn1; REQUIRE(realized::expunge_z<1, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up1);
	x = co*dn2; REQUIRE(realized::expunge_z<1, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up1);
	x = co*dn3; REQUIRE(realized::expunge_z<1, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up1);
	
	x = co*up3; REQUIRE(realized::expunge_z<2, N_rho>(x) ==     0); REQUIRE(x ==  co*up3);
	x = co*up2; REQUIRE(realized::expunge_z<2, N_rho>(x) ==     0); REQUIRE(x ==  co*up2);
	x = co*up1; REQUIRE(realized::expunge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*up0; REQUIRE(realized::expunge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*dn0; REQUIRE(realized::expunge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*dn1; REQUIRE(realized::expunge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*dn2; REQUIRE(realized::expunge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up2);
	x = co*dn3; REQUIRE(realized::expunge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*up2);
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
void realize_expurge__test()
{
	auto const up0 = realized::upsilon_y(0), dn0 = realized::dnsilon_y(0);
	auto const up1 = realized::upsilon_y(1), dn1 = realized::dnsilon_y(1);
	auto const up2 = realized::upsilon_y(2), dn2 = realized::dnsilon_y(2);
	auto const up3 = realized::upsilon_y(3), dn3 = realized::dnsilon_y(3);

	realized::alpha_t x, co = N_sgn*_std::pow(2, N_rho);
//	x = co*up3; REQUIRE(realized::expurge_z<0, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn0);
//	x = co*up2; REQUIRE(realized::expurge_z<0, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn0);
//	x = co*up1; REQUIRE(realized::expurge_z<0, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn0);
//	x = co*up0; REQUIRE(realized::expurge_z<0, N_rho>(x) ==     0); REQUIRE(x ==  co*dn0);
//	x = co*dn0; REQUIRE(realized::expurge_z<0, N_rho>(x) ==     0); REQUIRE(x ==  co*dn0);
//	x = co*dn1; REQUIRE(realized::expurge_z<0, N_rho>(x) ==     0); REQUIRE(x ==  co*dn1);
//	x = co*dn2; REQUIRE(realized::expurge_z<0, N_rho>(x) ==     0); REQUIRE(x ==  co*dn2);
//	x = co*dn3; REQUIRE(realized::expurge_z<0, N_rho>(x) ==     0); REQUIRE(x ==  co*dn3);
	
	x = co*up3; REQUIRE(realized::expurge_z<1, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*up2; REQUIRE(realized::expurge_z<1, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*up1; REQUIRE(realized::expurge_z<1, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*up0; REQUIRE(realized::expurge_z<1, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*dn0; REQUIRE(realized::expurge_z<1, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn1);
	x = co*dn1; REQUIRE(realized::expurge_z<1, N_rho>(x) ==     0); REQUIRE(x ==  co*dn1);
	x = co*dn2; REQUIRE(realized::expurge_z<1, N_rho>(x) ==     0); REQUIRE(x ==  co*dn2);
	x = co*dn3; REQUIRE(realized::expurge_z<1, N_rho>(x) ==     0); REQUIRE(x ==  co*dn3);
	
	x = co*up3; REQUIRE(realized::expurge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*up2; REQUIRE(realized::expurge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*up1; REQUIRE(realized::expurge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*up0; REQUIRE(realized::expurge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*dn0; REQUIRE(realized::expurge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*dn1; REQUIRE(realized::expurge_z<2, N_rho>(x) == N_sgn); REQUIRE(x ==  co*dn2);
	x = co*dn2; REQUIRE(realized::expurge_z<2, N_rho>(x) ==     0); REQUIRE(x ==  co*dn2);
	x = co*dn3; REQUIRE(realized::expurge_z<2, N_rho>(x) ==     0); REQUIRE(x ==  co*dn3);
}
TEST_CASE("xtal/any/realize.hpp: expurge")
{
	realize_expurge__test< 1,  2>(); realize_expurge__test<-1,  2>();
	realize_expurge__test< 1,  1>(); realize_expurge__test<-1,  1>();
	realize_expurge__test< 1,  0>(); realize_expurge__test<-1,  0>();
	realize_expurge__test< 1, -1>(); realize_expurge__test<-1, -1>();
	realize_expurge__test< 1, -2>(); realize_expurge__test<-1, -2>();
}

////////////////////////////////////////////////////////////////////////////////

template <iota_t N_sgn=1>
void realize_impurge__test()
{
	auto const oo0 = _std::numeric_limits<realized::alpha_t>::min()*(1 << 0);//realized::epsilon_y(0);
	auto const oo1 = _std::numeric_limits<realized::alpha_t>::min()*(1 << 1);//realized::epsilon_y(1);
	auto const oo2 = _std::numeric_limits<realized::alpha_t>::min()*(1 << 2);//realized::epsilon_y(2);
	auto const oo3 = _std::numeric_limits<realized::alpha_t>::min()*(1 << 3);//realized::epsilon_y(3);

	realized::alpha_t x, co = N_sgn;
	
	x = co*oo3; REQUIRE(realized::impurge_z<0>(x) ==     0); REQUIRE(x ==  co*oo3);
	x = co*oo2; REQUIRE(realized::impurge_z<0>(x) ==     0); REQUIRE(x ==  co*oo2);
	x = co*oo1; REQUIRE(realized::impurge_z<0>(x) ==     0); REQUIRE(x ==  co*oo1);
	x = co*oo0; REQUIRE(realized::impurge_z<0>(x) ==     0); REQUIRE(x ==  co*oo0);
//	x =    0.0; REQUIRE(realized::impurge_z<0>(x) ==     0); REQUIRE(x ==  co*0.0);

	x = co*oo3; REQUIRE(realized::impurge_z<1>(x) ==     0); REQUIRE(x ==  co*oo3);
	x = co*oo2; REQUIRE(realized::impurge_z<1>(x) ==     0); REQUIRE(x ==  co*oo2);
	x = co*oo1; REQUIRE(realized::impurge_z<1>(x) ==     0); REQUIRE(x ==  co*oo1);
	x = co*oo0; REQUIRE(realized::impurge_z<1>(x) == N_sgn); REQUIRE(x ==  co*oo0);
//	x =    0.0; REQUIRE(realized::impurge_z<1>(x) == N_sgn); REQUIRE(x ==  co*oo0);

	x = co*oo3; REQUIRE(realized::impurge_z<2>(x) ==     0); REQUIRE(x ==  co*oo3);
	x = co*oo2; REQUIRE(realized::impurge_z<2>(x) ==     0); REQUIRE(x ==  co*oo2);
	x = co*oo1; REQUIRE(realized::impurge_z<2>(x) == N_sgn); REQUIRE(x ==  co*oo1);
	x = co*oo0; REQUIRE(realized::impurge_z<2>(x) == N_sgn); REQUIRE(x ==  co*oo1);
//	x =    0.0; REQUIRE(realized::impurge_z<2>(x) == N_sgn); REQUIRE(x ==  co*oo1);

	x = co*oo3; REQUIRE(realized::impurge_z<3>(x) ==     0); REQUIRE(x ==  co*oo3);
	x = co*oo2; REQUIRE(realized::impurge_z<3>(x) == N_sgn); REQUIRE(x ==  co*oo2);
	x = co*oo1; REQUIRE(realized::impurge_z<3>(x) == N_sgn); REQUIRE(x ==  co*oo2);
	x = co*oo0; REQUIRE(realized::impurge_z<3>(x) == N_sgn); REQUIRE(x ==  co*oo2);
//	x =    0.0; REQUIRE(realized::impurge_z<3>(x) == N_sgn); REQUIRE(x ==  co*oo2);
}
TEST_CASE("xtal/any/realize.hpp: impurge")
{
	realize_impurge__test< 1>();
	realize_impurge__test<-1>();
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
