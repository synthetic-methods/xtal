#pragma once
#include "../any.c++"
#include "./any.hpp"// testing...

#include "../message/all.hpp"
#include "../process/all.hpp"
#include "../processor/all.hpp"

XTAL_ENV_(push)
namespace xtal::context::__any
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__any;

using gate_t = control::label_t<typename realized::alpha_t, struct gate>;


////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/control/any.hpp: hold process")
{
	size_t constexpr N_size = 1<<3;

	using gated_t = process::confined_t<gate_t::template hold<(1<<7)>>;
	using delay_t = context::delay_s<>;
	using sequel_u   = message::sequel_t<>;

	gated_t gated_o;
	
	gated_o <<= bundle_f((delay_t) 0, (gate_t)  7);
	gated_o <<= bundle_f((delay_t) 1, (gate_t)  1);
	gated_o <<= bundle_f((delay_t) 3, (gate_t) -1);
	gated_o <<= bundle_f((delay_t) 4, (gate_t)  1);
	gated_o <<= bundle_f((delay_t) 5, (gate_t) -1);
	gated_o <<= bundle_f((delay_t) 7, (gate_t)  7);
	gated_o <<= bundle_f((delay_t) 7, (gate_t) 77);
	
	REQUIRE(gated_o() ==  7);
	REQUIRE(gated_o() ==  1);
	REQUIRE(gated_o() ==  1);
	REQUIRE(gated_o() == -1);
	REQUIRE(gated_o() ==  1);
	REQUIRE(gated_o() == -1);
	REQUIRE(gated_o() == -1);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
//	...
	gated_o >>= sequel_u(N_size);
	gated_o <<= bundle_f((delay_t) 4, (gate_t)  11);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 11);
	REQUIRE(gated_o() == 11);
	REQUIRE(gated_o() == 11);
	REQUIRE(gated_o() == 11);

//	REQUIRE(true);
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <template <typename, typename...> typename P_>
void hold_processor__test()
{
	size_t constexpr N_size = 1<<3;

	using gated_t = process::confined_t<gate_t::template hold<(1<<7)>>;
	using array_t = _std::array<typename realized::alpha_t, N_size>;
	using delay_t = context::delay_s<>;

	using resize_u = message::resize_t<>;
	using sequel_u = message::sequel_t<>;

	auto gated_o = P_<gated_t>::bind_f();
	auto array_o = array_t();
	
	gated_o <<= resize_u(N_size);
	gated_o <<= bundle_f((delay_t) 0, (gate_t)  7);
	gated_o <<= bundle_f((delay_t) 1, (gate_t)  1);
	gated_o <<= bundle_f((delay_t) 3, (gate_t) -1);
	gated_o <<= bundle_f((delay_t) 4, (gate_t)  1);
	gated_o <<= bundle_f((delay_t) 5, (gate_t) -1);
	gated_o <<= bundle_f((delay_t) 7, (gate_t)  7);
	gated_o <<= bundle_f((delay_t) 7, (gate_t) 77);

	gated_o >>= sequel_u(N_size)*0; _v3::ranges::copy(gated_o, array_o.begin());
	REQUIRE(array_o == array_t {  7,  1,  1, -1,  1, -1, -1, 77});

	gated_o <<= bundle_f((delay_t) 4, (gate_t)  11);
	gated_o >>= sequel_u(N_size)*1; _v3::ranges::copy(gated_o, array_o.begin());
	REQUIRE(array_o == array_t { 77, 77, 77, 77, 11, 11, 11, 11});

//	echo(gated_o); REQUIRE(true);
}
TEST_CASE("xtal/control/any.hpp: hold processor")
{
	hold_processor__test<processor::molecule_t>();
//	hold_processor__test<processor::monomer_t>();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename mix_t>
void respan_internal_interrupt__test()
{
	using alpha_t = typename realized::alpha_t;

	using    mix_z = processor::molecule_t<mix_t, typename bias_t::template interrupt<(1 << 4)>>;
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
TEST_CASE("xtal/control/any.hpp: respan internal interrupt")
{
	respan_internal_interrupt__test<dynamic_bias_mix_t>();
//	respan_internal_interrupt__test<static_bias_mix_t>();
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
