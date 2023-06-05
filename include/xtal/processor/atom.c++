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
	sigma_t constexpr N = 5;
	using scalar_t = block::scalar_t<N, alpha_t>;

	auto x = scalar_t { 0,  1,  2,  3,  4};
	auto y = scalar_t {00, 10, 20, 30, 40};
	auto z = scalar_t {00, 11, 22, 33, 44};
	auto a = scalar_t {99, 99, 99, 99, 99};
//	auto f = processor::atom_f([](XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
//	auto b = f.bind_(x, y);
	auto b = processor::atom_f([](XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0)).bind_to(processor::let_f(x), processor::let_f(y));

	b <<= control::resize_f(N);
	b >>= control::sequel_f(N);
	_v3::ranges::copy(b, a.begin());
	REQUIRE(a == z);
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename add_t>
void respan_external__test()
{
	using collector  = block::collector<(1<<5)>;
	using collected  = block::collected<alpha_t>;
	using collection = compose_s<unit_t, collector, collected>;

	using buffer_u = typename collection::buffer::type;
	using debuff_u = deranged_t<buffer_u>;
	using respan_u = control::respan_t<debuff_u>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([](alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([](alpha_t n) {return n*11;});

	auto lhs = let_f(_01); REQUIRE(pointer_eq(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = let_f(_10); REQUIRE(pointer_eq(rhs.head(), processor::let_f(rhs).head()));
	auto xhs = atom_t<add_t, collector>::bind_f(lhs, rhs);

	auto vector_m = buffer_u {0, 0, 0};
	auto respan_m = respan_u(vector_m);
	auto sequel_m = sequel_n(3);

	REQUIRE(0 == xhs.size());

	xhs >>= pack_f(sequel_m++, respan_m); REQUIRE(_v3::ranges::equal(vector_m, _std::vector{00, 11, 22}));// initialize via efflux!
	xhs >>= pack_f(sequel_m++, respan_m); REQUIRE(_v3::ranges::equal(vector_m, _std::vector{33, 44, 55}));// advance then efflux...
	xhs >>= pack_f(sequel_m++, respan_m); REQUIRE(_v3::ranges::equal(vector_m, _std::vector{66, 77, 88}));// advance then efflux...
	xhs <<= bias_t((alpha_t) (11 + 1));
	xhs >>= pack_f(sequel_m++, respan_m); REQUIRE(_v3::ranges::equal(vector_m, _std::vector{111, 122, 133}));// advance then efflux...

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
template <typename add_t>
void respan_internal__test()
{
	size_t constexpr N = 3;

	using namespace _v3;
	auto _01 =  views::iota(0, 10)|views::transform(to_f<alpha_t>);
	auto _10 = _01|views::transform([](auto n) {return n*10;});
	auto _11 = _01|views::transform([](auto n) {return n*11;});

	using mix_op = atom_t<add_t>;
	auto  lhs = processor::let_f(_01); REQUIRE(pointer_eq(lhs.head(), processor::let_f(lhs).head()));
	auto  rhs = processor::let_f(_10); REQUIRE(pointer_eq(rhs.head(), processor::let_f(rhs).head()));
	auto  xhs = mix_op::bind_f(lhs, rhs);

	xhs <<= control::resize_f(N);
	xhs <<= control::resize_f(N);// idempotent!
	REQUIRE(0 == xhs.size());

	auto seq = control::sequel_f(N);
	xhs >>= seq  ; REQUIRE(N == xhs.size());// idempotent!
	xhs >>= seq++; REQUIRE(ranges::equal(xhs, _std::vector{00, 11, 22}));// initialize via efflux!
	xhs >>= seq++; REQUIRE(ranges::equal(xhs, _std::vector{33, 44, 55}));// advance then efflux...
	xhs >>= seq++; REQUIRE(ranges::equal(xhs, _std::vector{66, 77, 88}));// advance then efflux...

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
template <typename add_t, typename mul_t=dynamic_term_t>
void respan_internal_chain_rvalue__test()
{
	size_t constexpr N = 4;
	
	using namespace _v3;
	auto _01 =  views::iota(0, 10)|views::transform(to_f<alpha_t>);
	auto _10 = _01|views::transform([](auto n) {return n*10;});
	auto _11 = _01|views::transform([](auto n) {return n*11;});
	
	using mix_op = atom_t<add_t>;
	using mul_op = atom_t<mul_t>;
	auto yhs = mul_op::bind_f(mix_op::bind_f(lift_f(_01), lift_f(_10)));

	yhs <<= control::resize_f(N);
	yhs <<= coef_t((alpha_t) 100);
	yhs <<= bias_t((alpha_t) 000);
	REQUIRE(0 == yhs.size());

	auto seq = control::sequel_f(N);
	yhs >>= seq  ; REQUIRE(N == yhs.size());// idempotent!
	yhs >>= seq++; REQUIRE(ranges::equal(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >>= seq++; REQUIRE(ranges::equal(yhs, _std::vector{4400, 5500, 6600, 7700}));

	REQUIRE(yhs.template argument<0>().store().empty());

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
template <typename add_t, typename mul_t=dynamic_term_t>
void respan_internal_chain_lvalue__test()
{
	size_t constexpr N = 4;

	using namespace _v3;
	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([](alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([](alpha_t n) {return n*11;});
	
	using mix_op = atom_t<add_t>;
	using mul_op = atom_t<mul_t>;
	auto  lhs = let_f(_01); REQUIRE(pointer_eq(lhs.head(), processor::let_f(lhs).head()));
	auto  rhs = let_f(_10); REQUIRE(pointer_eq(rhs.head(), processor::let_f(rhs).head()));
	auto  xhs = mix_op::bind_f(lhs, rhs);
	auto  yhs = mul_op::bind_f(xhs);

	yhs <<= control::resize_f(N);
	yhs <<= coef_t((alpha_t) 100);
	xhs <<= bias_t((alpha_t) 000);

	auto seq = control::sequel_f(N);
	yhs >>= seq  ;// idempotent!
	yhs >>= seq++; REQUIRE(_v3::ranges::equal(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >>= seq++; REQUIRE(_v3::ranges::equal(yhs, _std::vector{4400, 5500, 6600, 7700}));

	REQUIRE(yhs.template argument<0>().store().size() == 4);

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
	size_t constexpr N = 4;

	using namespace _v3;
	auto _01 =  views::iota(0, 10)|views::transform(to_f<alpha_t>);
	auto _10 = _01|views::transform([](auto n) {return n*10;});
	auto _11 = _01|views::transform([](auto n) {return n*11;});

	using mix_op = atom_t<dynamic_bias_mix_t>;
	using mix_fn = bond_t<dynamic_bias_mix_t>;
	using nat_fn = bond_t<dynamic_count_t>;

	auto _xx = nat_fn::bind_f();
	auto xhs = mix_op::bind_f(_xx);
	auto lhs = mix_fn::bind_f(xhs, let_f(_01));
	auto rhs = mix_fn::bind_f(xhs, let_f(_10));
	auto yhs = mix_fn::bind_f(lhs, rhs);

	yhs <<= control::restep_f((size_t) 50);
	yhs <<= control::resize_f(N);

	yhs >>= control::sequel_f(N)*0; REQUIRE(ranges::equal(yhs, _std::vector{000, 111, 222, 333}));
	yhs >>= control::sequel_f(N)*1; REQUIRE(ranges::equal(yhs, _std::vector{444, 555, 666, 777}));

//	_std::cout << '\n'; for (auto _: yhs) _std::cout << '\t' << _; _std::cout << '\n'; REQUIRE(true);
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
