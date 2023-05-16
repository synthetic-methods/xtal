#pragma once
#include "./vectorize.hpp"
#include "../message/numinal.hpp"
#include "../message/start.hpp"


#include <catch2/catch_all.hpp>

XTAL_ENV_(push)
namespace xtal::processor::_test::vectorize
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using bias_t = message::ordinal_t<struct bias>;

struct static_bias_mix_t
:	process::confine_t<static_bias_mix_t
	,	bias_t::template dispatch<(1<<7)>
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
/**/
template <typename mix_t>
void render_external__test()
{
	using resize_o = message::resize_t<>;
	using serial_o = message::serial_t<>;

	auto  _01   = _v3::views::iota(0, 10)|_v3::views::transform(realized::iota_x);
	auto  _10   = _01|_v3::views::transform([] (auto n) {return realized::iota_x(n*10);});
	auto  _11   = _01|_v3::views::transform([] (auto n) {return realized::iota_x(n*11);});

	auto  lhs   = processor::let_f(_01); REQUIRE(id_y(lhs.head(), processor::let_f(lhs).head()));
	auto  rhs   = processor::let_f(_10); REQUIRE(id_y(rhs.head(), processor::let_f(rhs).head()));

	auto  xhs   = processor::vectorize_t<mix_t, buffer<(1<<5)>>::bind_f(lhs, rhs);
	using xhs_t = XTAL_TYP_(xhs);
	
	auto buffer_m = typename xhs_t::buffer_t {0, 0, 0};
	auto render_m = typename xhs_t::render_t(buffer_m);
	auto serial_m = serial_o(3);

	REQUIRE(0 == xhs.size());

	xhs <<= _std::make_tuple(  serial_m, render_m);                                                                 // initialize via influx?
	xhs >>= _std::make_tuple(  serial_m, render_m); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{00, 11, 22}));// initialize via efflux!
	xhs >>= _std::make_tuple(++serial_m, render_m); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{33, 44, 55}));// advance then efflux...
	xhs >>= _std::make_tuple(++serial_m, render_m); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{66, 77, 88}));// advance then efflux...
	xhs <<= bias_t(11 + 1);
	xhs >>= _std::make_tuple(++serial_m, render_m); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{111, 122, 133}));// advance then efflux...
}

TEST_CASE("xtal/processor/vectorize.hpp: render external")
{
	render_external__test<dynamic_bias_mix_t>();
	render_external__test<static_bias_mix_t>();
}

/**/
////////////////////////////////////////////////////////////////////////////////

template <typename mix_t>
void render_internal__test()
{
	using resize_o = message::resize_t<>;
	using serial_o = message::serial_t<>;

	auto  _01   = _v3::views::iota(0, 10)|_v3::views::transform(realized::iota_x);
	auto  _10   = _01|_v3::views::transform([] (auto n) {return realized::iota_x(n*10);});
	auto  _11   = _01|_v3::views::transform([] (auto n) {return realized::iota_x(n*11);});

	auto  lhs   = processor::let_f(_01); REQUIRE(id_y(lhs.head(), processor::let_f(lhs).head()));
	auto  rhs   = processor::let_f(_10); REQUIRE(id_y(rhs.head(), processor::let_f(rhs).head()));
	
	using xhs_t = processor::vectorize_t<mix_t>;
	auto  xhs   = xhs_t::bind_f(lhs, rhs);
	auto  seq   = serial_o(3);

	REQUIRE(0 == xhs.size());
	xhs <<= resize_o(3);
//	REQUIRE(3 == xhs.size());

	xhs <<=   seq;                                                            // initialize via influx?
	xhs >>=   seq; REQUIRE(_v3::ranges::equal(xhs, _std::vector{00, 11, 22}));// initialize via efflux!
	xhs >>= ++seq; REQUIRE(_v3::ranges::equal(xhs, _std::vector{33, 44, 55}));// advance then efflux...
	xhs >>= ++seq; REQUIRE(_v3::ranges::equal(xhs, _std::vector{66, 77, 88}));// advance then efflux...
//	ouch <<= xhs[0] << xhs[1] << xhs[2];
}

TEST_CASE("xtal/processor/vectorize.hpp: render internal")
{
	render_internal__test<dynamic_bias_mix_t>();
	render_internal__test<static_bias_mix_t>();
}

////////////////////////////////////////////////////////////////////////////////

template <typename mix_t>
void render_internal_suspension__test()
{
	using resize_o = message::resize_t<>;
	using serial_o = message::serial_t<>;

	auto  _01   = _v3::views::iota(0, 10)|_v3::views::transform(realized::iota_x);
	auto  _10   = _01|_v3::views::transform([] (auto n) {return realized::iota_x(n*10);});
	auto  _11   = _01|_v3::views::transform([] (auto n) {return realized::iota_x(n*11);});

	auto  lhs   = processor::let_f(_01); REQUIRE(id_y(lhs.head(), processor::let_f(lhs).head()));
	auto  rhs   = processor::let_f(_10); REQUIRE(id_y(rhs.head(), processor::let_f(rhs).head()));
	
	using xhs_t = processor::vectorize_t<mix_t, typename bias_t::template suspend<(1 << 4)>>;
	auto  xhs   = xhs_t::bind_f(lhs, rhs);
	auto  seq   = serial_o(4);

	xhs <<= resize_o(4);
	REQUIRE(0 == xhs.size());//NOTE: Only changes after `serial`?

	xhs <<= _std::make_tuple(0, bias_t(00));
	xhs <<= _std::make_tuple(1, bias_t(11));
	xhs <<= _std::make_tuple(2, bias_t(22));
	xhs >>=  seq;
	REQUIRE(4 == xhs.size());
	REQUIRE(_v3::ranges::equal(xhs, _std::vector{00, 22, 44, 55}));

	xhs <<= _std::make_tuple(2, bias_t(00));
	xhs >>=  seq;
	REQUIRE(4 == xhs.size());
	REQUIRE(_v3::ranges::equal(xhs, _std::vector{66, 77, 66, 77}));
//	ouch <<= xhs[0] << xhs[1] << xhs[2] << xhs[3];
}

TEST_CASE("xtal/processor/vectorize.hpp: render internal suspension")
{
	render_internal_suspension__test<dynamic_bias_mix_t>();
	render_internal_suspension__test<static_bias_mix_t>();
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
