#pragma once
#include "./any.hpp"
#include "../message/numinal.hpp"
#include "../message/serial.hpp"


#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::process::__any
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/process/any.hpp: lambda lifting")
{
	auto const f = let_f([] (XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) + ... + 0));
	REQUIRE(10 == f.template method<>(1, 2, 3, 4));
	REQUIRE(10 == f(1, 2, 3, 4));
	REQUIRE(10 == f.reify()(1, 2, 3, 4));
}

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

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/process/any.hpp: state")
{
	using serial_t = message::serial_t<countee_t<>>;
   using biased_t = process::confined_t<bias_t::template hold<(1 << 7)>>;

  biased_t biased;

  auto step = serial_t(1 << 3);
	
	biased <<= step;
	biased <<= common::bundle_f(0, (bias_t) (alpha_t)  7);
	biased <<= common::bundle_f(1, (bias_t) (alpha_t)  1);
	biased <<= common::bundle_f(3, (bias_t) (alpha_t) -1);
	biased <<= common::bundle_f(4, (bias_t) (alpha_t)  1);
	biased <<= common::bundle_f(5, (bias_t) (alpha_t) -1);
	biased <<= common::bundle_f(7, (bias_t) (alpha_t)  7);
	
	REQUIRE((alpha_t) biased()  ==  (alpha_t)  7);
	REQUIRE((alpha_t) biased()  ==  (alpha_t)  1);
	REQUIRE((alpha_t) biased()  ==  (alpha_t)  1);
	REQUIRE((alpha_t) biased()  ==  (alpha_t) -1);
	REQUIRE((alpha_t) biased()  ==  (alpha_t)  1);
	REQUIRE((alpha_t) biased()  ==  (alpha_t) -1);
	REQUIRE((alpha_t) biased()  ==  (alpha_t) -1);
	REQUIRE((alpha_t) biased()  ==  (alpha_t)  7);
	REQUIRE((alpha_t) biased()  ==  (alpha_t)  7);
	REQUIRE((alpha_t) biased()  ==  (alpha_t)  7);
//	...
	biased <<= step;
	REQUIRE((alpha_t) biased()  ==  (alpha_t)  7);
	REQUIRE((alpha_t) biased()  ==  (alpha_t)  7);
	REQUIRE((alpha_t) biased()  ==  (alpha_t)  7);

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)