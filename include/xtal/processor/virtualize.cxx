#pragma once
#include "./virtualize.hpp"
#include "../message/numinal.hpp"
#include "../message/start.hpp"


#include "../any.cxx"

XTAL_ENV_(push)
namespace xtal::processor::__virtualize
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename mix_t>
void render_virtual__test()
{
	using serial_o = message::serial_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(craft_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([] (auto n) {return alpha_t(n*10);});
	auto _11 = _01|_v3::views::transform([] (auto n) {return alpha_t(n*11);});

	auto lhs = processor::let_f(_01); REQUIRE(id_y(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = processor::let_f(_10); REQUIRE(id_y(rhs.head(), processor::let_f(rhs).head()));
	
	using xhs_t = processor::virtualize_t<mix_t>;
	auto  xhs = xhs_t::bind_f(lhs, rhs);

	auto walk = serial_o(3); REQUIRE(0 == xhs.size());//                               // uninitialized...
	xhs <<=   walk;          REQUIRE(0 == xhs.size());//                               // initialize via influx?
	xhs >>=   walk;          REQUIRE(3 == xhs.size());// REQUIRE(33*0 == xhs.front()); // initialize via efflux!
	xhs >>= ++walk;          REQUIRE(3 == xhs.size());// REQUIRE(33*1 == xhs.front()); // advance then efflux...
	xhs >>= ++walk;          REQUIRE(3 == xhs.size());// REQUIRE(33*2 == xhs.front()); // advance then efflux...

//	xhs >>= ++walk; // NOTE: Can't skip ahead (`serial` assertion fails)!

	walk += 6;      REQUIRE(3 == xhs.size());//                                    // prepare to advance and resize
	xhs >>= walk++; REQUIRE(6 == xhs.size());// REQUIRE(99 + 66*0 == xhs.front()); // efflux then advance
	xhs >>= walk++; REQUIRE(6 == xhs.size());// REQUIRE(99 + 66*1 == xhs.front()); // efflux then advance

//\
	NOTE: The adjustment below doesn't work for dispatched attributes like `static_bias` without reinvokation. \

//	xhs <<= bias_t((realized::alpha_t) - (99 + 66));
	auto const yhs = _11
	|	_v3::views::take(xhs.size())
	|	_v3::views::transform([] (auto n) {return n + 66 + 99;})
	;
	REQUIRE(_v3::ranges::equal(xhs, yhs));
}

TEST_CASE("xtal/processor/virtualize.hpp: render virtual")
{
	render_virtual__test<dynamic_bias_mix_t>();
	render_virtual__test<static_bias_mix_t>();
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
