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

template <typename ...As>
void monomer_lifting()
{
	using sigma_t = typename computer::sigma_t;
	using alpha_t = typename computer::alpha_t;

	sigma_t constexpr N_size = 5;
	using group_u = solid::strata_t<alpha_t[N_size]>;
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
	TRUE_(a == z);
}
TAG_("monomer", "lifting")
{
	TRY_("pure (material)") {monomer_lifting<restore<>>();}
	TRY_("pure (virtual)")  {monomer_lifting();}

}


///////////////////////////////////////////////////////////////////////////////

template <class mix_t>
void monomer_control__advancing()
{
	using sigma_t = typename computer::sigma_t;
	using alpha_t = typename computer::alpha_t;

	using sequel_n = control::sequel_t<>;
	using mixer_t = processor::monomer_t<mix_t>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([] (auto n) {return alpha_t(n*10);});
	auto _11 = _01|_v3::views::transform([] (auto n) {return alpha_t(n*11);});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	auto xhs = mixer_t::bond_f(lhs, rhs);

	auto seq = sequel_n(3); TRUE_(0 == xhs.size());// uninitialized...
	TRUE_(3 == seq.size());

//	xhs <<   seq; TRUE_(0 == xhs.size());//                             // initialize via influx?
	xhs >>   seq; TRUE_(3 == xhs.size());// TRUE_(33*0 == xhs.front()); // initialize via efflux!
	xhs >> ++seq; TRUE_(3 == xhs.size());// TRUE_(33*1 == xhs.front()); // advance then efflux...
	xhs >> ++seq; TRUE_(3 == xhs.size());// TRUE_(33*2 == xhs.front()); // advance then efflux...
	/**/

//	xhs >> ++seq; // NOTE: Can't skip ahead (`sequel` assertion fails)!

	seq += 6;     TRUE_(3 == xhs.size());//                                  // prepare to advance and resize
	xhs >> seq++; TRUE_(6 == xhs.size());// TRUE_(99 + 66*0 == xhs.front()); // efflux then advance
	xhs >> seq++; TRUE_(6 == xhs.size());// TRUE_(99 + 66*1 == xhs.front()); // efflux then advance

//	NOTE: The adjustment below doesn't work for dispatched attributes like `static_bias` without reinvokation. \

//	xhs << onset_t((computer::alpha_t) - (99 + 66));
	auto const yhs = _11
	|	_v3::views::take(xhs.size())
	|	_v3::views::transform([] (auto n) {return n + 66 + 99;})
	;
	TRUE_(equal_f(xhs, yhs));

}
template <class add_t>
void monomer_control__provisioning()
{
	using sigma_t = typename computer::sigma_t;
	using alpha_t = typename computer::alpha_t;

	using provide = restore<(1<<5)>;

	using store_u = typename confined_t<provide>::template store<alpha_t>::type;
	using serve_u = deranged_t<store_u>;
	using respan_u = control::respan_t<serve_u>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

	auto lhs = let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	auto xhs = monomer_t<add_t, provide>::bond_f(lhs, rhs);

	auto slush_m = store_u {0, 0, 0};
	auto respan_m = respan_u(slush_m);
	auto sequel_m = sequel_n(3);

	TRUE_(0 == xhs.size());

	xhs >> pack_f(respan_m, sequel_m++); TRUE_(equal_f(slush_m, _std::vector{00, 11, 22}));// initialize via efflux!
	xhs >> pack_f(respan_m, sequel_m++); TRUE_(equal_f(slush_m, _std::vector{33, 44, 55}));// advance then efflux...
	xhs >> pack_f(respan_m, sequel_m++); TRUE_(equal_f(slush_m, _std::vector{66, 77, 88}));// advance then efflux...
	xhs << onset_t((alpha_t) (11 + 1));
	xhs >> pack_f(respan_m, sequel_m++); TRUE_(equal_f(slush_m, _std::vector{111, 122, 133}));// advance then efflux...

}
TAG_("monomer", "control")
{
	TRY_("advancing (dynamic)") {monomer_control__advancing<dynamic_onset_mix_t>();}
	TRY_("advancing (static)")  {monomer_control__advancing< static_onset_mix_t>();}

	TRY_("provisioning (dynamic)") {monomer_control__provisioning<dynamic_onset_mix_t>();}
	TRY_("provisioning (static)")  {monomer_control__provisioning< static_onset_mix_t>();}

}


///////////////////////////////////////////////////////////////////////////////

template <class add_t, typename mul_t=dynamic_term_t>
void monomer_chaining__rvalue()
{
	using sigma_t = typename computer::sigma_t;
	using alpha_t = typename computer::alpha_t;

	size_t constexpr N = 4;
	
	using namespace _v3;
	auto _01 =  views::iota(0, 10)|views::transform(to_f<alpha_t>);
	auto _10 = _01|views::transform([] (auto n) {return n*10;});
	auto _11 = _01|views::transform([] (auto n) {return n*11;});
	
	using mix_op = monomer_t<add_t, restore<>>;
	using mul_op = monomer_t<mul_t, restore<>>;
	auto yhs = mul_op::bond_f(mix_op::bond_f(let_f(_01), let_f(_10)));

	yhs << control::resize_f(N);
	yhs << scale_t((alpha_t) 100);
	yhs << onset_t((alpha_t) 000);
	TRUE_(0 == yhs.size());

	auto seq = control::sequel_f(N);
	yhs >> seq  ; TRUE_(N == yhs.size());// idempotent!
	yhs >> seq++; TRUE_(equal_f(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >> seq++; TRUE_(equal_f(yhs, _std::vector{4400, 5500, 6600, 7700}));

	TRUE_(yhs.template slot<0>().store().empty());

}
template <class add_t, typename mul_t=dynamic_term_t>
void monomer_chaining__lvalue()
{
	using sigma_t = typename computer::sigma_t;
	using alpha_t = typename computer::alpha_t;

	size_t constexpr N = 4;

	using namespace _v3;
	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});
	
	using mix_op = monomer_t<add_t, restore<>>;
	using mul_op = monomer_t<mul_t, restore<>>;
	auto  lhs = let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto  rhs = let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	auto  xhs = mix_op::bond_f(lhs, rhs);
	auto  yhs = mul_op::bond_f(xhs);

	yhs << control::resize_f(N);
	yhs << scale_t((alpha_t) 100);
	xhs << onset_t((alpha_t) 000);

	auto seq = control::sequel_f(N);
	yhs >> seq  ;// idempotent!
	yhs >> seq++; TRUE_(equal_f(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >> seq++; TRUE_(equal_f(yhs, _std::vector{4400, 5500, 6600, 7700}));

	TRUE_(yhs.template slot<0>().store().size() == 4);

}
template <class add_t, typename mul_t=dynamic_term_t>
void monomer_chaining__shared()
{
	using sigma_t = typename computer::sigma_t;
	using alpha_t = typename computer::alpha_t;

	size_t constexpr N = 4;

	using namespace _v3;
	auto _01 =  views::iota(0, 10)|views::transform(to_f<alpha_t>);
	auto _10 = _01|views::transform([] (auto n) {return n*10;});
	auto _11 = _01|views::transform([] (auto n) {return n*11;});

	using mix_op = monomer_t<add_t, restore<>>;
	using mix_fn = monomer_t<add_t>;
	using ndfn = monomer_t<dynamic_count_t>;

	auto _xx = ndfn::bond_f();
	auto xhs = mix_op::bond_f(_xx);
	auto lhs = mix_fn::bond_f(xhs, let_f(_01));
	auto rhs = mix_fn::bond_f(xhs, let_f(_10));
	auto yhs = mix_fn::bond_f(lhs, rhs);

	yhs << control::restep_f((size_t) 50);
	yhs << control::resize_f(N);

	yhs >> control::sequel_f(N)*0; TRUE_(equal_f(yhs, _std::vector{000, 111, 222, 333}));
	yhs >> control::sequel_f(N)*1; TRUE_(equal_f(yhs, _std::vector{444, 555, 666, 777}));

}
TAG_("monomer", "chaining")
{
	TRY_("rvalue (dynamic)") {monomer_chaining__rvalue<dynamic_onset_mix_t>();}
	TRY_("rvalue (static)")  {monomer_chaining__rvalue< static_onset_mix_t>();}

	TRY_("lvalue (dynamic)") {monomer_chaining__lvalue<dynamic_onset_mix_t>();}
	TRY_("lvalue (static)")  {monomer_chaining__lvalue< static_onset_mix_t>();}

	TRY_("shared (dynamic)") {monomer_chaining__shared<dynamic_onset_mix_t>();}
	TRY_("shared (static)")  {monomer_chaining__shared< static_onset_mix_t>();}

}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
