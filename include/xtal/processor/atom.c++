#pragma once
#include "./all.hpp"
#include "../control/all.hpp"



#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::processor::__atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/processor/atom.hpp: lifting")
{
	sigma_t constexpr N_size = 5;
	using scalar_t = block::scalar_t<N_size, alpha_t>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

//	auto f = processor::atom_f([](XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
	auto x = scalar_t { 0,  1,  2,  3,  4};
	auto y = scalar_t {00, 10, 20, 30, 40};
	auto z = scalar_t {00, 11, 22, 33, 44};
	auto a = scalar_t {99, 99, 99, 99, 99};
//	auto b = f.bind_(x, y);
	auto b = processor::atom_f([](XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0)).bind_to(processor::let_f(x), processor::let_f(y));

	b <<= resize_u(N_size);
	b >>= sequel_n(N_size);
	_v3::ranges::copy(b, a.begin());
	REQUIRE(a == z);
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename mix_t>
void respan_external__test()
{
	using collector  = block::collector<(1<<5)>;
	using collected  = block::collected<alpha_t>;
	using collection = common::compose_s<unit_t, collector, collected>;

	using buffer_u = typename collection::buffer::type;
	using debuff_u = deranged_t<buffer_u>;
	using respan_u = control::respan_t<debuff_u>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([](alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([](alpha_t n) {return n*11;});

	auto lhs = processor::let_f(_01); REQUIRE(pointer_eq(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = processor::let_f(_10); REQUIRE(pointer_eq(rhs.head(), processor::let_f(rhs).head()));
	auto xhs = processor::atom_t<mix_t, collector>::bind_f(lhs, rhs);

	auto vector_m = buffer_u {0, 0, 0};
	auto respan_m = respan_u(vector_m);
	auto sequel_m = sequel_n(3);

	REQUIRE(0 == xhs.size());

	xhs >>= common::pack_f(sequel_m++, respan_m); REQUIRE(_v3::ranges::equal(vector_m, _std::vector{00, 11, 22}));// initialize via efflux!
	xhs >>= common::pack_f(sequel_m++, respan_m); REQUIRE(_v3::ranges::equal(vector_m, _std::vector{33, 44, 55}));// advance then efflux...
	xhs >>= common::pack_f(sequel_m++, respan_m); REQUIRE(_v3::ranges::equal(vector_m, _std::vector{66, 77, 88}));// advance then efflux...
	xhs <<= bias_t((alpha_t) (11 + 1));
	xhs >>= common::pack_f(sequel_m++, respan_m); REQUIRE(_v3::ranges::equal(vector_m, _std::vector{111, 122, 133}));// advance then efflux...

//	_std::cout << '\n'; for (auto _: xhs) _std::cout << '\t' << _; _std::cout << '\n'; REQUIRE(true);
}
TEST_CASE("xtal/processor/atom.hpp: respan external")
{
	respan_external__test<dynamic_bias_mix_t>();
	respan_external__test<static_bias_mix_t>();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename mix_t>
void respan_internal__test()
{
	using    mix_z = processor::atom_t<mix_t>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([](alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([](alpha_t n) {return n*11;});

	auto lhs = processor::let_f(_01); REQUIRE(pointer_eq(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = processor::let_f(_10); REQUIRE(pointer_eq(rhs.head(), processor::let_f(rhs).head()));
	
	auto xhs = mix_z::bind_f(lhs, rhs);
	auto seq = sequel_n(3);

	REQUIRE(0 == xhs.size());
	xhs <<= resize_u(3);
	xhs <<= resize_u(3);// idempotent!
//	REQUIRE(3 == xhs.size());

	xhs >>= seq++; REQUIRE(_v3::ranges::equal(xhs, _std::vector{00, 11, 22}));// initialize via efflux!
	xhs >>= seq++; REQUIRE(_v3::ranges::equal(xhs, _std::vector{33, 44, 55}));// advance then efflux...
	xhs >>= seq++; REQUIRE(_v3::ranges::equal(xhs, _std::vector{66, 77, 88}));// advance then efflux...

//	_std::cout << '\n'; for (auto _: xhs) _std::cout << '\t' << _; _std::cout << '\n'; REQUIRE(true);
}
TEST_CASE("xtal/processor/atom.hpp: respan internal")
{
	respan_internal__test<dynamic_bias_mix_t>();
	respan_internal__test<static_bias_mix_t>();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename mix_t, typename term_t=dynamic_term_t>
void respan_internal_chain_rvalue__test()
{
	using    mix_z = processor::atom_t< mix_t>;
	using   term_z = processor::atom_t<term_t>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([](alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([](alpha_t n) {return n*11;});
	
	auto lhs = processor::let_f(_01); REQUIRE(pointer_eq(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = processor::let_f(_10); REQUIRE(pointer_eq(rhs.head(), processor::let_f(rhs).head()));

//	auto xhs = mix_z::bind_f(_01, _10);
//	auto xhs = mix_z::bind_f(lhs, rhs);
	auto xhs = mix_z::bind_f(processor::let_f(_01), processor::let_f(_10));

//	auto yhs = term_z::bind_f(xhs);
	auto yhs = term_z::bind_f(mix_z::bind_f(lhs, rhs));

	auto seq = sequel_n(4); REQUIRE(0 == yhs.size());
	yhs <<= resize_u(4);
	yhs <<= coefficient_t((alpha_t) 100);
	xhs <<= bias_t((alpha_t) 0);

//	if constexpr (is_q<control::sequel_t<counted_t<>>, sequel_t>)
	yhs >>= seq; // idempotent!
	yhs >>= seq++; REQUIRE(_v3::ranges::equal(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >>= seq++; REQUIRE(_v3::ranges::equal(yhs, _std::vector{4400, 5500, 6600, 7700}));

//	_std::cout << '\n'; for (auto _: yhs) _std::cout << '\t' << _; _std::cout << '\n'; REQUIRE(true);
}
TEST_CASE("xtal/processor/atom.hpp: respan internal chain rvalue")
{
	respan_internal_chain_rvalue__test<dynamic_bias_mix_t>();
	respan_internal_chain_rvalue__test<static_bias_mix_t>();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename mix_t, typename term_t=dynamic_term_t>
void respan_internal_chain_lvalue__test()
{
	using    mix_z = processor::atom_t< mix_t>;
	using   term_z = processor::atom_t<term_t>;
	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([](alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([](alpha_t n) {return n*11;});
	
	auto lhs = processor::let_f(_01); REQUIRE(pointer_eq(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = processor::let_f(_10); REQUIRE(pointer_eq(rhs.head(), processor::let_f(rhs).head()));

//	auto xhs = mix_z::bind_f(_01, _10);
	auto xhs = mix_z::bind_f(lhs, rhs);
//	auto xhs = mix_z::bind_f(processor::let_f(_01), processor::let_f(_10));

	auto yhs = term_z::bind_f(xhs);
//	auto yhs = term_z::bind_f(mix_z::bind_f(lhs, rhs));

	auto seq = sequel_u(4); REQUIRE(0 == yhs.size());
	yhs <<= resize_u(4);
	yhs <<= coefficient_t((alpha_t) 100);
	xhs <<= bias_t((alpha_t) 0);

//	if constexpr (is_q<control::sequel_u<counted_t<>>, sequel_u>)
	yhs >>= seq  ;// idempotent!
	yhs >>= seq++; REQUIRE(_v3::ranges::equal(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >>= seq++; REQUIRE(_v3::ranges::equal(yhs, _std::vector{4400, 5500, 6600, 7700}));

//	_std::cout << '\n'; for (auto _: yhs) _std::cout << '\t' << _; _std::cout << '\n'; REQUIRE(true);
}
TEST_CASE("xtal/processor/atom.hpp: respan internal chain lvalue")
{
	respan_internal_chain_lvalue__test<dynamic_bias_mix_t>();
	respan_internal_chain_lvalue__test<static_bias_mix_t>();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/processor/atom.hpp: respan internal chain lvalue shared")
{
	using mixer_z  = processor::atom_t<dynamic_bias_mix_t>;
	using mixer_y  = processor::bond_t<dynamic_bias_mix_t>;
	using count_y  = processor::bond_t<dynamic_count_t>;
	using restep_u = control::restep_t<>;
	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;

	auto _xx = count_y::bind_f();
	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([](alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([](alpha_t n) {return n*11;});

	auto xhs = mixer_z::bind_f(_xx);
	auto lhs = mixer_y::bind_f(xhs, processor::let_f(_01));
	auto rhs = mixer_y::bind_f(xhs, processor::let_f(_10));
	auto yhs = mixer_y::bind_f(lhs, rhs);

	yhs <<= restep_u(50);
	yhs <<= resize_u(4);

	yhs >>= sequel_u(4)*0; REQUIRE(_v3::ranges::equal(yhs, _std::vector{000, 111, 222, 333}));
	yhs >>= sequel_u(4)*1; REQUIRE(_v3::ranges::equal(yhs, _std::vector{444, 555, 666, 777}));

//	_std::cout << '\n'; for (auto _: yhs) _std::cout << '\t' << _; _std::cout << '\n'; REQUIRE(true);
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
