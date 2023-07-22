#pragma once
#include "./any.c++"
#include "./anybody.hpp"// testing...

#include "../control/all.hpp"



XTAL_ENV_(push)
namespace xtal::process::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__test;


////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/process/anybody.hpp: lifting")
{
	auto const f = let_f([] (XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
	REQUIRE(10 == f.method(1, 2, 3, 4));
	REQUIRE(10 == f(1, 2, 3, 4));
	REQUIRE(10 == f.reify() (1, 2, 3, 4));
}

////////////////////////////////////////////////////////////////////////////////
/**/
void test__attribute_initialization(auto z)
{
	auto &o = z.template get<onset_t>();
	REQUIRE(00.0 == (float) o);
	REQUIRE(10.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/anybody.hpp: attribute initialization")
{
	test__attribute_initialization(dynamic_onset_mix_t());
	test__attribute_initialization(static_onset_mix_t());
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void test__attribute_influx_operator(auto z)
{
	auto &o = z.template get<onset_t>();
	z << onset_t(0.0); REQUIRE(0.0 == (float) o);
	z << onset_t(1.0); REQUIRE(1.0 == (float) o);
	z << onset_t(2.0); REQUIRE(2.0 == (float) o);
	z << onset_t(3.0); REQUIRE(3.0 == (float) o);
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/anybody.hpp: attribute influx operator")
{
	test__attribute_influx_operator(dynamic_onset_mix_t());
	test__attribute_influx_operator(static_onset_mix_t());
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void test__attribute_efflux_operator(auto z)
{
	auto &o = z.template get<onset_t>();
	z >> onset_t(0.0); REQUIRE(0.0 == (float) o);
	z >> onset_t(1.0); REQUIRE(1.0 == (float) o);
	z >> onset_t(2.0); REQUIRE(2.0 == (float) o);
	z >> onset_t(3.0); REQUIRE(3.0 == (float) o);
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/anybody.hpp: attribute efflux operator")
{
	test__attribute_efflux_operator(dynamic_onset_mix_t());
	test__attribute_efflux_operator(static_onset_mix_t());
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void test__attribute_influx_method(auto z)
{
	using start_t = control::nominal_t<0, struct T_start>;

	auto &o = z.template get<onset_t>();
	REQUIRE(-1 == (int) z.influx(start_t()));                                    // unrecognized
	REQUIRE( 1 == (int) z.influx(onset_t(0.0))); REQUIRE(0.0 == (float) o);// unchanged
	REQUIRE( 0 == (int) z.influx(onset_t(1.0))); REQUIRE(1.0 == (float) o);// changed
	REQUIRE( 0 == (int) z.influx(onset_t(2.0))); REQUIRE(2.0 == (float) o);// changed
	REQUIRE( 0 == (int) z.influx(onset_t(3.0))); REQUIRE(3.0 == (float) o);// changed
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/anybody.hpp: attribute influx method")
{
	test__attribute_influx_method(dynamic_onset_mix_t());
	test__attribute_influx_method(static_onset_mix_t());
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void test__attribute_efflux_method(auto z)
{
	using start_t = control::nominal_t<0, struct T_start>;

	auto &o = z.template get<onset_t>();
	REQUIRE(-1 == (int) z.efflux(start_t()));                                    // unrecognized
	REQUIRE( 1 == (int) z.efflux(onset_t(0.0))); REQUIRE(0.0 == (float) o);// unchanged
	REQUIRE( 0 == (int) z.efflux(onset_t(1.0))); REQUIRE(1.0 == (float) o);// changed
	REQUIRE( 0 == (int) z.efflux(onset_t(2.0))); REQUIRE(2.0 == (float) o);// changed
	REQUIRE( 0 == (int) z.efflux(onset_t(3.0))); REQUIRE(3.0 == (float) o);// changed
	REQUIRE(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TEST_CASE("xtal/process/anybody.hpp: attribute efflux method")
{
	test__attribute_efflux_method(dynamic_onset_mix_t());
	test__attribute_efflux_method(static_onset_mix_t());
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
