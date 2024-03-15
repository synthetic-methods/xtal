#pragma once
#include "./any.cc"
#include "./monomer.ii"// testing...

#include "./all.ii"
#include "../resourced/all.ii"
#include "../message/all.ii"

XTAL_ENV_(push)
namespace xtal::processor::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
void monomer_lifting()
{
	using T_sigma = typename bond::realized::sigma_t;
	using T_alpha = typename bond::realized::alpha_t;

	T_sigma constexpr N_size = 5;
	using U_group = atom::linear_t<T_alpha[N_size]>;
	using U_resize = message::resize_t<>;
	using U_scope = message::scope_t<>;

	auto x = U_group { 0,  1,  2,  3,  4};
	auto y = U_group {00, 10, 20, 30, 40};
	auto z = U_group {00, 11, 22, 33, 44};
	auto a = U_group {99, 99, 99, 99, 99};
//	auto f = processor::monomer_f<As...>([] (XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
//	auto b = f.bind(processor::let_f(x), processor::let_f(y));
	auto b = processor::monomer_f<As...>([] (XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0)).bind(processor::let_f(x), processor::let_f(y));

	b <<= U_resize(N_size);
	b >>= U_scope(N_size);
	_v3::ranges::move(b, a.begin());
	TRUE_(a == z);
	
}
TAG_("monomer", "lifting")
{
	TRY_("pure (material)") {monomer_lifting<resourced::stored<>>();}
	TRY_("pure (virtual)")  {monomer_lifting();}

}


///////////////////////////////////////////////////////////////////////////////

template <class mix_t>
void monomer_provision__advancing()
{
	using T_sigma = typename bond::realized::sigma_t;
	using T_alpha = typename bond::realized::alpha_t;

	using U_scope = message::scope_t<>;
	using U_mixer = processor::monomer_t<mix_t>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(as_f<T_alpha>);
	auto _10 = _01|_v3::views::transform([] (auto n) {return T_alpha(n*10);});
	auto _11 = _01|_v3::views::transform([] (auto n) {return T_alpha(n*11);});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	auto xhs = U_mixer::bind_f(lhs, rhs);

	auto seq = U_scope(3); TRUE_(0 == xhs.size());// uninitialized...
	TRUE_(3 == seq.size());

//	xhs <<=   seq; TRUE_(0 == xhs.size());//                             // initialize via influx?
	xhs >>=   seq; TRUE_(3 == xhs.size());// TRUE_(33*0 == xhs.front()); // initialize via efflux!
	xhs >>= ++seq; TRUE_(3 == xhs.size());// TRUE_(33*1 == xhs.front()); // advance then efflux...
	xhs >>= ++seq; TRUE_(3 == xhs.size());// TRUE_(33*2 == xhs.front()); // advance then efflux...
	/**/

//	xhs >>= ++seq; // NOTE: Can't skip ahead (`scope` assertion fails)!

	seq += 6;     TRUE_(3 == xhs.size());//                                  // prepare to advance and resize
	xhs >>= seq++; TRUE_(6 == xhs.size());// TRUE_(99 + 66*0 == xhs.front()); // efflux then advance
	xhs >>= seq++; TRUE_(6 == xhs.size());// TRUE_(99 + 66*1 == xhs.front()); // efflux then advance

//	NOTE: The adjustment below doesn't work for dispatched attributes like `static_bias` without reinvokation. \

//	xhs <<= onset_t((T_alpha) - (99 + 66));
	auto const yhs = _11
	|	_v3::views::take(xhs.size())
	|	_v3::views::transform([] (auto n) {return n + 66 + 99;})
	;
	TRUE_(equal_f(xhs, yhs));

}
template <class U_add>
void monomer_provision__provisioning()
{
	using T_sigma = typename bond::realized::sigma_t;
	using T_alpha = typename bond::realized::alpha_t;

	using provide = resourced::stored<(1<<5)>;

	using U_store = typename confined_t<provide>::template store_t<T_alpha>;
	using U_serve = visor_t<U_store>;
	using U_respan = message::respan_t<U_serve>;
	using U_resize = message::resize_t<>;
	using U_scope = message::scope_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(as_f<T_alpha>);
	auto _10 = _01|_v3::views::transform([] (T_alpha n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (T_alpha n) {return n*11;});

	auto lhs = let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	auto xhs = monomer_t<U_add, provide>::bind_f(lhs, rhs);

	auto m_slush = U_store {0, 0, 0};
	auto m_respan = U_respan(m_slush);
	auto m_scope = U_scope(3);

	TRUE_(0 == xhs.size());

	xhs >>= m_scope++ >> m_respan; TRUE_(equal_f(m_slush, _std::vector{00, 11, 22}));// initialize via efflux!
	xhs >>= m_scope++ >> m_respan; TRUE_(equal_f(m_slush, _std::vector{33, 44, 55}));// advance then efflux...
	xhs >>= m_scope++ >> m_respan; TRUE_(equal_f(m_slush, _std::vector{66, 77, 88}));// advance then efflux...
	xhs <<= onset_t((T_alpha) (11 + 1));
	xhs >>= m_scope++ >> m_respan; TRUE_(equal_f(m_slush, _std::vector{111, 122, 133}));// advance then efflux...

}
TAG_("monomer", "message")
{
	TRY_("advancing (dynamic)") {monomer_provision__advancing<dynamic_onset_mix_t>();}
	TRY_("advancing (static)")  {monomer_provision__advancing< static_onset_mix_t>();}

	TRY_("provisioning (dynamic)") {monomer_provision__provisioning<dynamic_onset_mix_t>();}
	TRY_("provisioning (static)")  {monomer_provision__provisioning< static_onset_mix_t>();}

}


///////////////////////////////////////////////////////////////////////////////

template <class U_add, typename U_mul=dynamic_term_t>
void monomer_chaining__rvalue()
{
	using T_sigma = typename bond::realized::sigma_t;
	using T_alpha = typename bond::realized::alpha_t;

	size_t constexpr N = 4;
	
	using namespace _v3;
	auto _01 =  views::iota(0, 10)|views::transform(as_f<T_alpha>);
	auto _10 = _01|views::transform([] (auto n) {return n*10;});
	auto _11 = _01|views::transform([] (auto n) {return n*11;});
	
	using mix_op = monomer_t<U_add, resourced::stored<>>;
	using mul_op = monomer_t<U_mul, resourced::stored<>>;
	auto yhs = mul_op::bind_f(mix_op::bind_f(let_f(_01), let_f(_10)));

	yhs <<= message::resize_f(N);
	yhs <<= scale_t((T_alpha) 100);
	yhs <<= onset_t((T_alpha) 000);
	TRUE_(0 == yhs.size());

	auto seq = message::scope_f(N);
	yhs >>= seq  ; TRUE_(N == yhs.size());// idempotent!
	yhs >>= seq++; TRUE_(equal_f(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >>= seq++; TRUE_(equal_f(yhs, _std::vector{4400, 5500, 6600, 7700}));

	TRUE_(yhs.template slot<0>().store().empty());

}
template <class U_add, typename U_mul=dynamic_term_t>
void monomer_chaining__lvalue()
{
	using T_sigma = typename bond::realized::sigma_t;
	using T_alpha = typename bond::realized::alpha_t;

	size_t constexpr N = 4;

	using namespace _v3;
	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(as_f<T_alpha>);
	auto _10 = _01|_v3::views::transform([] (T_alpha n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (T_alpha n) {return n*11;});
	
	using mix_op = monomer_t<U_add, resourced::stored<>>;
	using mul_op = monomer_t<U_mul, resourced::stored<>>;
	auto  lhs = let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto  rhs = let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	auto  xhs = mix_op::bind_f(lhs, rhs);
	auto  yhs = mul_op::bind_f(xhs);

	yhs <<= message::resize_f(N);
	yhs <<= scale_t((T_alpha) 100);
	xhs <<= onset_t((T_alpha) 000);

	auto seq = message::scope_f(N);
	yhs >>= seq  ;// idempotent!
	yhs >>= seq++; TRUE_(equal_f(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >>= seq++; TRUE_(equal_f(yhs, _std::vector{4400, 5500, 6600, 7700}));

	TRUE_(yhs.template slot<0>().store().size() == 4);

}
template <class U_add, typename U_mul=dynamic_term_t>
void monomer_chaining__shared()
{
	using T_sigma = typename bond::realized::sigma_t;
	using T_alpha = typename bond::realized::alpha_t;

	size_t constexpr N = 4;

	using namespace _v3;
	auto _01 =  views::iota(0, 10)|views::transform(as_f<T_alpha>);
	auto _10 = _01|views::transform([] (auto n) {return n*10;});
	auto _11 = _01|views::transform([] (auto n) {return n*11;});

	using mix_op = monomer_t<U_add, resourced::stored<>>;
	using mix_fn = monomer_t<U_add>;
	using ndfn = monomer_t<dynamic_count_t>;

	auto _xx = ndfn::bind_f();
	auto xhs = mix_op::bind_f(_xx);
	auto lhs = mix_fn::bind_f(xhs, let_f(_01));
	auto rhs = mix_fn::bind_f(xhs, let_f(_10));
	auto yhs = mix_fn::bind_f(lhs, rhs);

	yhs <<= message::restep_f((size_t) 50);
	yhs <<= message::resize_f(N);

	yhs >>= message::scope_f(N)*0; TRUE_(equal_f(yhs, _std::vector{000, 111, 222, 333}));
	yhs >>= message::scope_f(N)*1; TRUE_(equal_f(yhs, _std::vector{444, 555, 666, 777}));

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
