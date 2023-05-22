#pragma once
#include "./vectorize.hpp"
#include "./virtualize.hpp"
#include "../message/numinal.hpp"
#include "../message/start.hpp"

#include "../any.cxx"

XTAL_ENV_(push)
namespace xtal::processor::__vectorize
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*/
template <typename mix_t>
void render_external__test()
{
	using resize_t = message::resize_t<>;
	using serial_n = message::serial_t<>;

	auto  _01 = _v3::views::iota(0, 10)|_v3::views::transform(craft_f<alpha_t>);
	auto  _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto  _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

	auto  lhs = processor::let_f(_01); REQUIRE(id_y(lhs.head(), processor::let_f(lhs).head()));
	auto  rhs = processor::let_f(_10); REQUIRE(id_y(rhs.head(), processor::let_f(rhs).head()));

	auto  xhs = processor::vectorize_t<mix_t, buffer<(1<<5)>>::bind_f(lhs, rhs);
	using XHS = XTAL_TYP_(xhs);
	
	auto buffer_m = typename XHS::buffer_t {0, 0, 0};
	auto render_m = typename XHS::render_t(buffer_m);
	auto serial_m = serial_n(3);

	REQUIRE(0 == xhs.size());

	xhs <<= bundle_f(  serial_m, render_m);                                                                 // initialize via influx?
	xhs >>= bundle_f(  serial_m, render_m); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{00, 11, 22}));// initialize via efflux!
	xhs >>= bundle_f(++serial_m, render_m); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{33, 44, 55}));// advance then efflux...
	xhs >>= bundle_f(++serial_m, render_m); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{66, 77, 88}));// advance then efflux...
	xhs <<= bias_t((alpha_t) (11 + 1));
	xhs >>= bundle_f(++serial_m, render_m); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{111, 122, 133}));// advance then efflux...

}
TEST_CASE("xtal/processor/vectorize.hpp: render external")
{
	render_external__test<dynamic_bias_mix_t>();
	render_external__test<static_bias_mix_t>();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/*/
template <typename mix_t>
void render_internal__test()
{
	using resize_t = message::resize_t<>;
	using serial_n = message::serial_t<>;

	auto  _01 = _v3::views::iota(0, 10)|_v3::views::transform(craft_f<alpha_t>);
	auto  _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto  _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

	auto  lhs = processor::let_f(_01); REQUIRE(id_y(lhs.head(), processor::let_f(lhs).head()));
	auto  rhs = processor::let_f(_10); REQUIRE(id_y(rhs.head(), processor::let_f(rhs).head()));
	
	using XHS = processor::vectorize_t<mix_t>;
	auto  xhs = XHS::bind_f(lhs, rhs);
	auto  seq = serial_n(3);

	REQUIRE(0 == xhs.size());
	xhs <<= resize_t(3);
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
/***/
////////////////////////////////////////////////////////////////////////////////
/*/
template <typename mix_t>
void render_internal_interrupt__test()
{
	using resize_t = message::resize_t<>;
	using serial_n = message::serial_t<>;

	auto  _01 = _v3::views::iota(0, 10)|_v3::views::transform(craft_f<alpha_t>);
	auto  _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto  _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

	auto  lhs = processor::let_f(_01); REQUIRE(id_y(lhs.head(), processor::let_f(lhs).head()));
	auto  rhs = processor::let_f(_10); REQUIRE(id_y(rhs.head(), processor::let_f(rhs).head()));
	
	using XHS = processor::vectorize_t<mix_t, typename bias_t::template interrupt<(1 << 4)>>;
	auto  xhs = XHS::bind_f(lhs, rhs);
	auto  seq = serial_n(4);

	xhs <<= resize_t(4);
	REQUIRE(0 == xhs.size());//NOTE: Only changes after `serial`?

	xhs <<= bundle_f(0, (bias_t) (alpha_t) (00));
	xhs <<= bundle_f(1, (bias_t) (alpha_t) (11));
	xhs <<= bundle_f(2, (bias_t) (alpha_t) (22));
	xhs >>=  seq;
	REQUIRE(4 == xhs.size());
	REQUIRE(_v3::ranges::equal(xhs, _std::vector{00, 22, 44, 55}));

	xhs <<= bundle_f(2, (bias_t) (alpha_t) (00));
	xhs >>=  seq;
	REQUIRE(4 == xhs.size());
	REQUIRE(_v3::ranges::equal(xhs, _std::vector{66, 77, 66, 77}));
//	ouch <<= xhs[0] << xhs[1] << xhs[2] << xhs[3];
}
TEST_CASE("xtal/processor/vectorize.hpp: render internal interrupt")
{
	render_internal_interrupt__test<dynamic_bias_mix_t>();
	render_internal_interrupt__test<static_bias_mix_t>();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename mix_t>
void render_internal_chain__test()
{
	using resize_t = message::resize_t<>;
	using serial_t = message::serial_t<>;

	auto  _01 = _v3::views::iota(0, 10)|_v3::views::transform(craft_f<alpha_t>);
	auto  _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto  _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});
	
	using XHS = processor::vectorize_t<mix_t>;//, buffer<(1<<5)>
	using YHS = processor::vectorize_t<dynamic_term_t>;

	auto  lhs = processor::let_f(_01); REQUIRE(id_y(lhs.head(), processor::let_f(lhs).head()));
	auto  rhs = processor::let_f(_10); REQUIRE(id_y(rhs.head(), processor::let_f(rhs).head()));

//	auto  xhs = XHS::bind_f(_01, _10);// wrapped lvalue (OK)
//	auto  xhs = XHS::bind_f(lhs, rhs);// lvalue (OK)
	auto  xhs = XHS::bind_f(processor::let_f(_01), processor::let_f(_10));// rvalue (OKish, but offset by 11*100...)

	auto  yhs = YHS::bind_f(xhs);// lvalue (OK)
//	auto  yhs = YHS::bind_f(XHS::bind_f(lhs, rhs));// rvalue (definitely not OK)

	auto  seq = serial_t(4); REQUIRE(0 == yhs.size());
	yhs <<= resize_t(4);
	yhs <<= coefficient_t((alpha_t) 100);
	xhs <<= bias_t((alpha_t) 0);

	yhs >>= seq++;// REQUIRE(_v3::ranges::equal(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >>= seq++;// REQUIRE(_v3::ranges::equal(yhs, _std::vector{4400, 5500, 6600, 7700}));

//	std::cout << "+>" << "\t" << seq.size() << "\t" << seq.step() << "\n";
	std::cout << "=>"; for (auto y: yhs) std::cout << "\t" << y; std::cout << "\n";
	
}
TEST_CASE("xtal/processor/vectorize.hpp: render internal chain")
{
//	render_internal_chain__test<dynamic_bias_mix_t>();
	render_internal_chain__test<static_bias_mix_t>();
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
