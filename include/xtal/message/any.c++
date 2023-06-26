#pragma once
#include "../any.c++"
#include "./any.hpp"// testing...

#include "../message/all.hpp"
#include "../processor/node.hpp"


XTAL_ENV_(push)
namespace xtal::message::__any
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__any;


////////////////////////////////////////////////////////////////////////////////
/**/
template <typename mix_t>
void respan_internal_interrupt__test()
{
	using alpha_t = typename realized::alpha_t;

	using    mix_z = processor::node_t<mix_t, typename bias_t::template interrupt<(1 << 4)>>;
	using resize_u = message::resize_t<>;
	using sequel_n = message::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([](alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([](alpha_t n) {return n*11;});

	auto lhs = processor::let_f(_01); REQUIRE(pointer_e(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = processor::let_f(_10); REQUIRE(pointer_e(rhs.head(), processor::let_f(rhs).head()));
	
	auto xhs = mix_z::bind_f(lhs, rhs);
	auto seq = sequel_n(4);

	xhs <<= resize_u(4);
	REQUIRE(0 == xhs.size());//NOTE: Only changes after `sequel`.

	xhs <<= context::delay_s<bias_t>(0, (alpha_t) 100);
	xhs <<= context::delay_s<bias_t>(1, (alpha_t) 200);
	xhs <<= context::delay_s<bias_t>(2, (alpha_t) 300);
	xhs >>= seq++;
	REQUIRE(4 == xhs.size());
	REQUIRE(_v3::ranges::equal(xhs, _std::vector{100, 211, 322, 333}));

	xhs <<= context::delay_s<bias_t>(2, (alpha_t) 400);// relative timing!
	xhs >>= seq++;
	REQUIRE(4 == xhs.size());
	REQUIRE(_v3::ranges::equal(xhs, _std::vector{344, 355, 466, 477}));

//	_std::cout << '\n'; for (auto _: xhs) _std::cout << '\t' << _; _std::cout << '\n'; REQUIRE(true);
}
TEST_CASE("xtal/message/any.hpp: respan internal interrupt")
{
	respan_internal_interrupt__test<dynamic_bias_mix_t>();
//	respan_internal_interrupt__test<static_bias_mix_t>();
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
