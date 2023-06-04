#pragma once
#include "./any.hpp"
#include "../control/all.hpp"



#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::process::__any
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/process/any.hpp: lifting")
{
	auto const f = let_f([](XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
	REQUIRE(10 == f.template method<>(1, 2, 3, 4));
	REQUIRE(10 == f(1, 2, 3, 4));
	REQUIRE(10 == f.reify() (1, 2, 3, 4));
}

////////////////////////////////////////////////////////////////////////////////

void attribute_initialization__test(auto z)
{
	auto &o = z.template self<bias_t>();
	REQUIRE(00.0 == (float) o.head());
	REQUIRE(10.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute initialization")
{
	attribute_initialization__test(dynamic_bias_mix_t());
	attribute_initialization__test(static_bias_mix_t());
}


void attribute_influx_operator__test(auto z)
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
	attribute_influx_operator__test(dynamic_bias_mix_t());
	attribute_influx_operator__test(static_bias_mix_t());
}


void attribute_efflux_operator__test(auto z)
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
	attribute_efflux_operator__test(dynamic_bias_mix_t());
	attribute_efflux_operator__test(static_bias_mix_t());
}


void attribute_influx_method__test(auto z)
{
	auto &o = z.template self<bias_t>();
	REQUIRE(-1 == (int) z.influx(control::start_t()));                           // unrecognized
	REQUIRE( 0 == (int) z.influx(bias_t(0.0))); REQUIRE(0.0 == (float) o.head());// unchanged
	REQUIRE( 1 == (int) z.influx(bias_t(1.0))); REQUIRE(1.0 == (float) o.head());// changed
	REQUIRE( 1 == (int) z.influx(bias_t(2.0))); REQUIRE(2.0 == (float) o.head());// changed
	REQUIRE( 1 == (int) z.influx(bias_t(3.0))); REQUIRE(3.0 == (float) o.head());// changed
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute influx method")
{
	attribute_influx_method__test(dynamic_bias_mix_t());
	attribute_influx_method__test(static_bias_mix_t());
}


void attribute_efflux_method__test(auto z)
{
	auto &o = z.template self<bias_t>();
	REQUIRE(-1 == (int) z.efflux(control::start_t()));                           // unrecognized
	REQUIRE( 0 == (int) z.efflux(bias_t(0.0))); REQUIRE(0.0 == (float) o.head());// unchanged
	REQUIRE( 1 == (int) z.efflux(bias_t(1.0))); REQUIRE(1.0 == (float) o.head());// changed
	REQUIRE( 1 == (int) z.efflux(bias_t(2.0))); REQUIRE(2.0 == (float) o.head());// changed
	REQUIRE( 1 == (int) z.efflux(bias_t(3.0))); REQUIRE(3.0 == (float) o.head());// changed
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute efflux method")
{
	attribute_efflux_method__test(dynamic_bias_mix_t());
	attribute_efflux_method__test(static_bias_mix_t());
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
