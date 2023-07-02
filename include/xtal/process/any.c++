#pragma once
#include "../any.c++"
#include "./any.hpp"// testing...

#include "../control/all.hpp"



XTAL_ENV_(push)
namespace xtal::process::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__test;


////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/process/any.hpp: lifting")
{
	auto const f = let_f([] (XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
	REQUIRE(10 == f.template method<>(1, 2, 3, 4));
	REQUIRE(10 == f(1, 2, 3, 4));
	REQUIRE(10 == f.reify() (1, 2, 3, 4));
}

////////////////////////////////////////////////////////////////////////////////

void test__attribute_initialization(auto z)
{
	auto &o = z.template self<bias_t>();
	REQUIRE(00.0 == (float) o.head());
	REQUIRE(10.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute initialization")
{
	test__attribute_initialization(dynamic_bias_mix_t());
	test__attribute_initialization(static_bias_mix_t());
}


void test__attribute_influx_operator(auto z)
{
	auto &o = z.template self<bias_t>();
	z <<= bias_t(0.0); REQUIRE(0.0 == (float) o.head());
	z <<= bias_t(1.0); REQUIRE(1.0 == (float) o.head());
	z <<= bias_t(2.0); REQUIRE(2.0 == (float) o.head());
	z <<= bias_t(3.0); REQUIRE(3.0 == (float) o.head());
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute influx operator")
{
	test__attribute_influx_operator(dynamic_bias_mix_t());
	test__attribute_influx_operator(static_bias_mix_t());
}


void test__attribute_efflux_operator(auto z)
{
	auto &o = z.template self<bias_t>();
	z >>= bias_t(0.0); REQUIRE(0.0 == (float) o.head());
	z >>= bias_t(1.0); REQUIRE(1.0 == (float) o.head());
	z >>= bias_t(2.0); REQUIRE(2.0 == (float) o.head());
	z >>= bias_t(3.0); REQUIRE(3.0 == (float) o.head());
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute efflux operator")
{
	test__attribute_efflux_operator(dynamic_bias_mix_t());
	test__attribute_efflux_operator(static_bias_mix_t());
}


void test__attribute_influx_method(auto z)
{
	using start_t = control::nominal_t<0, struct start>;

	auto &o = z.template self<bias_t>();
	REQUIRE(-1 == (int) z.influx(start_t()));                                    // unrecognized
	REQUIRE( 1 == (int) z.influx(bias_t(0.0))); REQUIRE(0.0 == (float) o.head());// unchanged
	REQUIRE( 0 == (int) z.influx(bias_t(1.0))); REQUIRE(1.0 == (float) o.head());// changed
	REQUIRE( 0 == (int) z.influx(bias_t(2.0))); REQUIRE(2.0 == (float) o.head());// changed
	REQUIRE( 0 == (int) z.influx(bias_t(3.0))); REQUIRE(3.0 == (float) o.head());// changed
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute influx method")
{
	test__attribute_influx_method(dynamic_bias_mix_t());
	test__attribute_influx_method(static_bias_mix_t());
}


void test__attribute_efflux_method(auto z)
{
	using start_t = control::nominal_t<0, struct start>;

	auto &o = z.template self<bias_t>();
	REQUIRE(-1 == (int) z.efflux(start_t()));                                    // unrecognized
	REQUIRE( 1 == (int) z.efflux(bias_t(0.0))); REQUIRE(0.0 == (float) o.head());// unchanged
	REQUIRE( 0 == (int) z.efflux(bias_t(1.0))); REQUIRE(1.0 == (float) o.head());// changed
	REQUIRE( 0 == (int) z.efflux(bias_t(2.0))); REQUIRE(2.0 == (float) o.head());// changed
	REQUIRE( 0 == (int) z.efflux(bias_t(3.0))); REQUIRE(3.0 == (float) o.head());// changed
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute efflux method")
{
	test__attribute_efflux_method(dynamic_bias_mix_t());
	test__attribute_efflux_method(static_bias_mix_t());
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
