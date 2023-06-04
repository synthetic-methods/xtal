#pragma once
#include "./any.hpp"
#include "../control/all.hpp"
#include "../process/any.hpp"
#include "../processor/atom.hpp"

#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::control::__any
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/control/any.hpp: hold")
{
	using sequel_t = control::sequel_t<countee_t<>>;
   using biased_t = process::confined_t<bias_t::template hold<(1 << 7)>>;

  biased_t biased;

  auto step = sequel_t(1 << 3);
	
	biased <<= step;
	biased <<= common::pack_f(content::delay_s<>(0), (bias_t) (alpha_t)  7);
	biased <<= common::pack_f(content::delay_s<>(1), (bias_t) (alpha_t)  1);
	biased <<= common::pack_f(content::delay_s<>(3), (bias_t) (alpha_t) -1);
	biased <<= common::pack_f(content::delay_s<>(4), (bias_t) (alpha_t)  1);
	biased <<= common::pack_f(content::delay_s<>(5), (bias_t) (alpha_t) -1);
	biased <<= common::pack_f(content::delay_s<>(7), (bias_t) (alpha_t)  7);
	
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
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename mix_t>
void respan_internal_interrupt__test()
{
	using    mix_z = processor::atom_t<mix_t, typename bias_t::template interrupt<(1 << 4)>>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([](alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([](alpha_t n) {return n*11;});

	auto lhs = processor::let_f(_01); REQUIRE(pointer_eq(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = processor::let_f(_10); REQUIRE(pointer_eq(rhs.head(), processor::let_f(rhs).head()));
	
	auto xhs = mix_z::bind_f(lhs, rhs);
	auto seq = sequel_n(4);

	xhs <<= resize_u(4);
	REQUIRE(0 == xhs.size());//NOTE: Only changes after `sequel`.

	xhs <<= content::delay_s<bias_t>(0, (alpha_t) 100);
	xhs <<= content::delay_s<bias_t>(1, (alpha_t) 200);
	xhs <<= content::delay_s<bias_t>(2, (alpha_t) 300);
	xhs >>= seq++;
	REQUIRE(4 == xhs.size());
	REQUIRE(_v3::ranges::equal(xhs, _std::vector{100, 211, 322, 333}));

	xhs <<= content::delay_s<bias_t>(2, (alpha_t) 400);// relative timing!
	xhs >>= seq++;
	REQUIRE(4 == xhs.size());
	REQUIRE(_v3::ranges::equal(xhs, _std::vector{344, 355, 466, 477}));

//	_std::cout << '\n'; for (auto _: xhs) _std::cout << '\t' << _; _std::cout << '\n'; REQUIRE(true);
}
TEST_CASE("xtal/processor/atom.hpp: respan internal interrupt")
{
	respan_internal_interrupt__test<dynamic_bias_mix_t>();
//	respan_internal_interrupt__test<static_bias_mix_t>();
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
