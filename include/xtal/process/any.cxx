#pragma once
#include "./any.hpp"
#include "../message/numinal.hpp"
#include "../message/start.hpp"


#include <catch2/catch_all.hpp>

XTAL_ENV_(push)
namespace xtal::process::_test::any
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using bias_t = message::numinal_t<alpha_t, struct bias>;

struct static_bias_mix_t
:	process::confine_t<static_bias_mix_t
	,	bias_t::template dispatch<4>
	>
{
	template <auto bias>
	XTAL_FN2 method(XTAL_DEF... xs)
	{
		return (XTAL_REF_(xs) + ... + bias);
	}
};
struct dynamic_bias_mix_t
:	process::confine_t<dynamic_bias_mix_t
	,	bias_t::attach
	>
{
	template <auto...>
	XTAL_FN2 method(XTAL_DEF... xs)
	{
		return (XTAL_REF_(xs) + ... + this->template get<bias_t>());
	}
};

////////////////////////////////////////////////////////////////////////////////

void attribute_initialization__test(auto z)
{
	REQUIRE(00.0 == (float) z.template get<bias_t>());
	REQUIRE(10.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute initialization")
{
	attribute_initialization__test(dynamic_bias_mix_t());
	attribute_initialization__test(static_bias_mix_t());
}


void attribute_influx_operator__test(auto z)
{
	z <<= bias_t(0.0); REQUIRE(0.0 == (float) z.template get<bias_t>());
	z <<= bias_t(1.0); REQUIRE(1.0 == (float) z.template get<bias_t>());
	z <<= bias_t(2.0); REQUIRE(2.0 == (float) z.template get<bias_t>());
	z <<= bias_t(3.0); REQUIRE(3.0 == (float) z.template get<bias_t>());
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute influx operator")
{
	attribute_influx_operator__test(dynamic_bias_mix_t());
	attribute_influx_operator__test(static_bias_mix_t());
}


void attribute_efflux_operator__test(auto z)
{
	z >>= bias_t(0.0); REQUIRE(0.0 == (float) z.template get<bias_t>());
	z >>= bias_t(1.0); REQUIRE(1.0 == (float) z.template get<bias_t>());
	z >>= bias_t(2.0); REQUIRE(2.0 == (float) z.template get<bias_t>());
	z >>= bias_t(3.0); REQUIRE(3.0 == (float) z.template get<bias_t>());
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute efflux operator")
{
	attribute_efflux_operator__test(dynamic_bias_mix_t());
	attribute_efflux_operator__test(static_bias_mix_t());
}


void attribute_influx_method__test(auto z)
{
	REQUIRE(-1 == (float) z.influx(message::start_t()));                                           // unrecognized
	REQUIRE( 0 == (float) z.influx(bias_t(0.0))); REQUIRE(0.0 == (float) z.template get<bias_t>());// unchanged
	REQUIRE( 1 == (float) z.influx(bias_t(1.0))); REQUIRE(1.0 == (float) z.template get<bias_t>());// changed
	REQUIRE( 1 == (float) z.influx(bias_t(2.0))); REQUIRE(2.0 == (float) z.template get<bias_t>());// changed
	REQUIRE( 1 == (float) z.influx(bias_t(3.0))); REQUIRE(3.0 == (float) z.template get<bias_t>());// changed
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/any.hpp: attribute influx method")
{
	attribute_influx_method__test(dynamic_bias_mix_t());
	attribute_influx_method__test(static_bias_mix_t());
}


void attribute_efflux_method__test(auto z)
{
	REQUIRE(-1 == (float) z.efflux(message::start_t()));                                           // unrecognized
	REQUIRE( 0 == (float) z.efflux(bias_t(0.0))); REQUIRE(0.0 == (float) z.template get<bias_t>());// unchanged
	REQUIRE( 1 == (float) z.efflux(bias_t(1.0))); REQUIRE(1.0 == (float) z.template get<bias_t>());// changed
	REQUIRE( 1 == (float) z.efflux(bias_t(2.0))); REQUIRE(2.0 == (float) z.template get<bias_t>());// changed
	REQUIRE( 1 == (float) z.efflux(bias_t(3.0))); REQUIRE(3.0 == (float) z.template get<bias_t>());// changed
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
