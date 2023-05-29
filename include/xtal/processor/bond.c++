#pragma once
#include "./all.hpp"
#include "../control/all.hpp"



#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::processor::__bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/processor/bond.hpp: lifting")
{
	sigma_t constexpr N_size = 5;
	using scalar_t = common::collect_scalar_t<N_size, alpha_t>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

//	auto f = processor::bond_f([](XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) + ... + 0));
	auto x = scalar_t { 0,  1,  2,  3,  4};
	auto y = scalar_t {00, 10, 20, 30, 40};
	auto z = scalar_t {00, 11, 22, 33, 44};
	auto a = scalar_t {00, 00, 00, 00, 00};
//	auto b = f.bind_to(x, y);
	auto b = processor::bond_f([](XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) + ... + 0)).bind_to(processor::let_f(x), processor::let_f(y));

	b <<= resize_u(N_size);
	b >>= sequel_n(N_size);
	_v3::ranges::copy(b, a.begin());
	REQUIRE(a == z);
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename mix_t>
void respan_virtual__test()
{
	using sequel_n = control::sequel_t<>;

	auto  _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto  _10 = _01|_v3::views::transform([](auto n) {return alpha_t(n*10);});
	auto  _11 = _01|_v3::views::transform([](auto n) {return alpha_t(n*11);});

	auto  lhs = processor::let_f(_01); REQUIRE(pointer_eq(lhs.head(), processor::let_f(lhs).head()));
	auto  rhs = processor::let_f(_10); REQUIRE(pointer_eq(rhs.head(), processor::let_f(rhs).head()));
	
	using XHS = processor::bond_t<mix_t>;
	auto  xhs = XHS::bind_f(lhs, rhs);

	auto walk = sequel_n(3); REQUIRE(0 == xhs.size());//                               // uninitialized...
	REQUIRE(3 == walk.size());

//	xhs <<=   walk;          REQUIRE(0 == xhs.size());//                               // initialize via influx?
	xhs >>=   walk;          REQUIRE(3 == xhs.size());// REQUIRE(33*0 == xhs.front()); // initialize via efflux!
	xhs >>= ++walk;          REQUIRE(3 == xhs.size());// REQUIRE(33*1 == xhs.front()); // advance then efflux...
	xhs >>= ++walk;          REQUIRE(3 == xhs.size());// REQUIRE(33*2 == xhs.front()); // advance then efflux...

//	xhs >>= ++walk; // NOTE: Can't skip ahead (`sequel` assertion fails)!

	walk += 6;      REQUIRE(3 == xhs.size());//                                    // prepare to advance and resize
	xhs >>= walk++; REQUIRE(6 == xhs.size());// REQUIRE(99 + 66*0 == xhs.front()); // efflux then advance
	xhs >>= walk++; REQUIRE(6 == xhs.size());// REQUIRE(99 + 66*1 == xhs.front()); // efflux then advance

//\
	NOTE: The adjustment below doesn't work for dispatched attributes like `static_bias` without reinvokation. \

//	xhs <<= bias_t((realized::alpha_t) - (99 + 66));
	auto const yhs = _11
	|	_v3::views::take(xhs.size())
	|	_v3::views::transform([](auto n) {return n + 66 + 99;})
	;
	REQUIRE(_v3::ranges::equal(xhs, yhs));
	
}

TEST_CASE("xtal/processor/bond.hpp: respan virtual")
{
	respan_virtual__test<dynamic_bias_mix_t>();
	respan_virtual__test<static_bias_mix_t>();
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
