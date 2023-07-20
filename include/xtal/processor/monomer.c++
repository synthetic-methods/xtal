#pragma once
#include "./any.c++"
#include "./monomer.hpp"// testing...

#include "./all.hpp"
#include "../control/all.hpp"


XTAL_ENV_(push)
namespace xtal::processor::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
template <typename ...As>
void test__invocable()
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	sigma_t constexpr N_size = 5;
	using group_u = typename collate_t<N_size>::template group_t<alpha_t>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

	auto x = group_u { 0,  1,  2,  3,  4};
	auto y = group_u {00, 10, 20, 30, 40};
	auto z = group_u {00, 11, 22, 33, 44};
	auto a = group_u {99, 99, 99, 99, 99};
//	auto f = processor::monomer_f<As...>([] (XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
//	auto b = f.bind(processor::let_f(x), processor::let_f(y));
	auto b = processor::monomer_f<As...>([] (XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0)).bind(processor::let_f(x), processor::let_f(y));

	b << resize_u(N_size);
	b >> sequel_n(N_size);
	_v3::ranges::move(b, a.begin());
	REQUIRE(a == z);
}
TEST_CASE("xtal/processor/monomer.hpp: invocable")
{
	test__invocable<collect<-1>>();
	test__invocable();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename mix_t>
void test__sequel()
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	using sequel_n = control::sequel_t<>;
	using mixer_t = processor::monomer_t<mix_t>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([] (auto n) {return alpha_t(n*10);});
	auto _11 = _01|_v3::views::transform([] (auto n) {return alpha_t(n*11);});

	auto lhs = processor::let_f(_01); REQUIRE(identical_f(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = processor::let_f(_10); REQUIRE(identical_f(rhs.head(), processor::let_f(rhs).head()));
	auto xhs = mixer_t::bond_f(lhs, rhs);

	auto seq = sequel_n(3); REQUIRE(0 == xhs.size());// uninitialized...
	REQUIRE(3 == seq.size());

//	xhs <<   seq; REQUIRE(0 == xhs.size());//                               // initialize via influx?
	xhs >>   seq; REQUIRE(3 == xhs.size());// REQUIRE(33*0 == xhs.front()); // initialize via efflux!
	xhs >> ++seq; REQUIRE(3 == xhs.size());// REQUIRE(33*1 == xhs.front()); // advance then efflux...
	xhs >> ++seq; REQUIRE(3 == xhs.size());// REQUIRE(33*2 == xhs.front()); // advance then efflux...
	/**/

//	xhs >> ++seq; // NOTE: Can't skip ahead (`sequel` assertion fails)!

	seq += 6;      REQUIRE(3 == xhs.size());//                                    // prepare to advance and resize
	xhs >> seq++; REQUIRE(6 == xhs.size());// REQUIRE(99 + 66*0 == xhs.front()); // efflux then advance
	xhs >> seq++; REQUIRE(6 == xhs.size());// REQUIRE(99 + 66*1 == xhs.front()); // efflux then advance

//	NOTE: The adjustment below doesn't work for dispatched attributes like `static_bias` without reinvokation. \

//	xhs << bias_t((realized::alpha_t) - (99 + 66));
	auto const yhs = _11
	|	_v3::views::take(xhs.size())
	|	_v3::views::transform([] (auto n) {return n + 66 + 99;})
	;
	REQUIRE(_v3::ranges::equal(xhs, yhs));
	/***/
}

TEST_CASE("xtal/processor/monomer.hpp: sequel")
{
	test__sequel<dynamic_bias_mix_t>();
	test__sequel<static_bias_mix_t>();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename add_t>
void test__respan_provision()
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	using provide = collect<(1<<5)>;

	using buffer_u = typename provide::type::template fluid<alpha_t>::type;
	using debuff_u = deranged_t<buffer_u>;
	using respan_u = control::respan_t<debuff_u>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

	auto lhs = let_f(_01); REQUIRE(identical_f(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = let_f(_10); REQUIRE(identical_f(rhs.head(), processor::let_f(rhs).head()));
	auto xhs = monomer_t<add_t, provide>::bond_f(lhs, rhs);

	auto buffer_m = buffer_u {0, 0, 0};
	auto respan_m = respan_u(buffer_m);
	auto sequel_m = sequel_n(3);

	REQUIRE(0 == xhs.size());

	xhs >> bundle_f(respan_m, sequel_m++); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{00, 11, 22}));// initialize via efflux!
	xhs >> bundle_f(respan_m, sequel_m++); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{33, 44, 55}));// advance then efflux...
	xhs >> bundle_f(respan_m, sequel_m++); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{66, 77, 88}));// advance then efflux...
	xhs << bias_t((alpha_t) (11 + 1));
	xhs >> bundle_f(respan_m, sequel_m++); REQUIRE(_v3::ranges::equal(buffer_m, _std::vector{111, 122, 133}));// advance then efflux...

}
TEST_CASE("xtal/processor/monomer.hpp: respan provision")
{
	test__respan_provision<dynamic_bias_mix_t>();
	test__respan_provision<static_bias_mix_t>();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename add_t, typename mul_t=dynamic_term_t>
void test__respan_chain_rvalue()
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	size_t constexpr N = 4;
	
	using namespace _v3;
	auto _01 =  views::iota(0, 10)|views::transform(to_f<alpha_t>);
	auto _10 = _01|views::transform([] (auto n) {return n*10;});
	auto _11 = _01|views::transform([] (auto n) {return n*11;});
	
	using mix_op = monomer_t<add_t, collect<-1>>;
	using mul_op = monomer_t<mul_t, collect<-1>>;
	auto yhs = mul_op::bond_f(mix_op::bond_f(lift_f(_01), lift_f(_10)));

	yhs << control::resize_f(N);
	yhs << coef_t((alpha_t) 100);
	yhs << bias_t((alpha_t) 000);
	REQUIRE(0 == yhs.size());

	auto seq = control::sequel_f(N);
	yhs >> seq  ; REQUIRE(N == yhs.size());// idempotent!
	yhs >> seq++; REQUIRE(ranges::equal(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >> seq++; REQUIRE(ranges::equal(yhs, _std::vector{4400, 5500, 6600, 7700}));

	REQUIRE(yhs.template slot<0>().store().empty());

}
TEST_CASE("xtal/processor/monomer.hpp: respan internal chain rvalue")
{
	test__respan_chain_rvalue<dynamic_bias_mix_t>();
	test__respan_chain_rvalue<static_bias_mix_t>();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename add_t, typename mul_t=dynamic_term_t>
void test__respan_chain_lvalue()
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	size_t constexpr N = 4;

	using namespace _v3;
	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});
	
	using mix_op = monomer_t<add_t, collect<-1>>;
	using mul_op = monomer_t<mul_t, collect<-1>>;
	auto  lhs = let_f(_01); REQUIRE(identical_f(lhs.head(), processor::let_f(lhs).head()));
	auto  rhs = let_f(_10); REQUIRE(identical_f(rhs.head(), processor::let_f(rhs).head()));
	auto  xhs = mix_op::bond_f(lhs, rhs);
	auto  yhs = mul_op::bond_f(xhs);

	yhs << control::resize_f(N);
	yhs << coef_t((alpha_t) 100);
	xhs << bias_t((alpha_t) 000);

	auto seq = control::sequel_f(N);
	yhs >> seq  ;// idempotent!
	yhs >> seq++; REQUIRE(_v3::ranges::equal(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >> seq++; REQUIRE(_v3::ranges::equal(yhs, _std::vector{4400, 5500, 6600, 7700}));

	REQUIRE(yhs.template slot<0>().store().size() == 4);

}
TEST_CASE("xtal/processor/monomer.hpp: respan internal chain lvalue")
{
	test__respan_chain_lvalue<dynamic_bias_mix_t>();
	test__respan_chain_lvalue<static_bias_mix_t>();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/processor/monomer.hpp: respan internal chain lvalue shared")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	size_t constexpr N = 4;

	using namespace _v3;
	auto _01 =  views::iota(0, 10)|views::transform(to_f<alpha_t>);
	auto _10 = _01|views::transform([] (auto n) {return n*10;});
	auto _11 = _01|views::transform([] (auto n) {return n*11;});

	using mix_op = monomer_t<dynamic_bias_mix_t, collect<-1>>;
	using mix_fn = monomer_t<dynamic_bias_mix_t>;
	using nat_fn = monomer_t<dynamic_count_t>;

	auto _xx = nat_fn::bond_f();
	auto xhs = mix_op::bond_f(_xx);
	auto lhs = mix_fn::bond_f(xhs, let_f(_01));
	auto rhs = mix_fn::bond_f(xhs, let_f(_10));
	auto yhs = mix_fn::bond_f(lhs, rhs);

	yhs << control::restep_f((size_t) 50);
	yhs << control::resize_f(N);

	yhs >> control::sequel_f(N)*0; REQUIRE(ranges::equal(yhs, _std::vector{000, 111, 222, 333}));
	yhs >> control::sequel_f(N)*1; REQUIRE(ranges::equal(yhs, _std::vector{444, 555, 666, 777}));

}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
