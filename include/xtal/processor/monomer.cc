#pragma once
#include "./any.cc"
#include "./monomer.hh"// testing...

#include "./all.hh"
#include "../provision/all.hh"
#include "../occur/all.hh"

XTAL_ENV_(push)
namespace xtal::processor::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
void monomer_zipping()
{
	using _fit = bond::fit<>;
	using T_sigma = _fit::sigma_type;
	using T_alpha = _fit::alpha_type;

	using U_data = T_alpha;
	unsigned constexpr U_size = 2;

	//\
	using U_block  =  atom::block_t<U_data[U_size]>;
	using U_block  =  _std::complex<U_data>;
//	using U_resize = occur::resize_t<>;
//	using U_cursor = occur::cursor_t<>;

	U_data xs[] {0, 0, 0, 0};
	U_data ys[] {0, 0, 0, 0};
	auto zs = _xtd::ranges::views::zip(xs, ys);
//	zs[0] = U_block{1, 2};
	zs[0] = bond::repack_f(U_block{1, 2});

	TRUE_(xs[0] == 1);
	TRUE_(ys[0] == 2);
	
}
TAG_("monomer", "zipping")
{
	TRY_("pure (actual)") {monomer_zipping<provision::stored<>>();}
	TRY_("pure (virtual)")  {monomer_zipping();}

}


////////////////////////////////////////////////////////////////////////////////
/**/
template <typename ...As>
void monomer_lifting()
{
	using T_sigma = typename bond::fit<>::sigma_type;
	using T_alpha = typename bond::fit<>::alpha_type;

	T_sigma constexpr N_size = 5;
	using U_block  = atom::block_t<T_alpha[N_size]>;
	using U_resize = occur::resize_t<>;
	using U_cursor = occur::cursor_t<>;

	auto x = U_block{ 0,  1,  2,  3,  4};
	auto y = U_block{00, 10, 20, 30, 40};
	auto z = U_block{00, 11, 22, 33, 44};
	auto a = U_block{99, 99, 99, 99, 99};
//	auto f = processor::monomer_f<As...>([] (auto &&...xs) XTAL_0FN_(to) (XTAL_REF_(xs) +...+ 0));
//	auto b = f.bind(processor::let_f(x), processor::let_f(y));
	auto b = processor::monomer_f<As...>([] (auto &&...xs) XTAL_0FN_(to) (XTAL_REF_(xs) +...+ 0)).bind(processor::let_f(x), processor::let_f(y));

	b <<= U_resize(N_size);
	b >>= U_cursor(N_size);
	_xtd::ranges::move(b, a.begin());
	TRUE_(a == z);
	
}
TAG_("monomer", "lifting")
{
	TRY_("pure (actual)") {monomer_lifting<provision::stored<>>();}
	TRY_("pure (virtual)")  {monomer_lifting();}

}
/***/

///////////////////////////////////////////////////////////////////////////////
/**/
TAG_("monomer", "irritating")
{
	using T_sigma = typename bond::fit<>::sigma_type;
	using T_alpha = typename bond::fit<>::alpha_type;

	using U_cursor = occur::cursor_t<>;
	using U_mixer = processor::monomer_t<Px_irritator_mix, Ox_onset::dispatch<>>;

	auto _01 = _xtd::ranges::views::iota(0, 10)|_xtd::ranges::views::transform(bond::operate<T_alpha>{});
	auto _10 = _01|_xtd::ranges::views::transform([] (auto n) {return T_alpha(n*10);});
	auto _11 = _01|_xtd::ranges::views::transform([] (auto n) {return T_alpha(n*11);});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	auto xhs = U_mixer::bind_f(lhs, rhs);

	auto seq = U_cursor(3); TRUE_(0 == xhs.size());// uninitialized...
	TRUE_(3 == seq.size());

	xhs >>=   seq; TRUE_(3 == xhs.size());// TRUE_(33*0 == xhs.front()); // initialize via efflux!
	xhs >>= ++seq; TRUE_(3 == xhs.size());// TRUE_(33*1 == xhs.front()); // advance then efflux...
	xhs >>= ++seq; TRUE_(3 == xhs.size());// TRUE_(33*2 == xhs.front()); // advance then efflux...

}
/***/

///////////////////////////////////////////////////////////////////////////////

template <class Px_mix>
void monomer_provision__advancing()
{
	using T_sigma = typename bond::fit<>::sigma_type;
	using T_alpha = typename bond::fit<>::alpha_type;

	using U_cursor = occur::cursor_t<>;
	using U_mixer = processor::monomer_t<Px_mix>;

	auto _01 = _xtd::ranges::views::iota(0, 10)|_xtd::ranges::views::transform(bond::operate<T_alpha>{});
	auto _10 = _01|_xtd::ranges::views::transform([] (auto n) {return T_alpha(n*10);});
	auto _11 = _01|_xtd::ranges::views::transform([] (auto n) {return T_alpha(n*11);});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	auto xhs = U_mixer::bind_f(lhs, rhs);

	auto seq = U_cursor(3); TRUE_(0 == xhs.size());// uninitialized...
	TRUE_(3 == seq.size());

//	xhs <<=   seq; TRUE_(0 == xhs.size());//                             // initialize via influx?
	xhs >>=   seq; TRUE_(3 == xhs.size());// TRUE_(33*0 == xhs.front()); // initialize via efflux!
	xhs >>= ++seq; TRUE_(3 == xhs.size());// TRUE_(33*1 == xhs.front()); // advance then efflux...
	xhs >>= ++seq; TRUE_(3 == xhs.size());// TRUE_(33*2 == xhs.front()); // advance then efflux...

//	xhs >>= ++seq; // NOTE: Can't skip ahead (`cursor` assertion fails)!

	seq += 6;      TRUE_(3 == xhs.size());//                                  // prepare to advance and resize
	xhs >>= seq++; TRUE_(6 == xhs.size());// TRUE_(99 + 66*0 == xhs.front()); // efflux then advance
	xhs >>= seq++; TRUE_(6 == xhs.size());// TRUE_(99 + 66*1 == xhs.front()); // efflux then advance

//	NOTE: The adjustment below doesn't work for dispatched attributes like `static_bias` without reinvokation!

//	xhs <<= Ox_onset((T_alpha) - (99 + 66));
	auto const yhs = _11
	|	_xtd::ranges::views::take_exactly(xhs.size())
	|	_xtd::ranges::views::transform([] (auto n) {return n + 66 + 99;})
	;
	TRUE_(equal_f(xhs, yhs));

}
template <class U_add>
void monomer_provision__provisioning()
{
	using T_sigma = typename bond::fit<>::sigma_type;
	using T_alpha = typename bond::fit<>::alpha_type;

	using provide = provision::stored<extent_constant_t<0x20>>;

	using U_store = typename confined_t<provide>::template store_t<T_alpha>;
	using U_state  = reiterated_t<U_store>;
	using U_review = occur::review_t<U_state>;
	using U_resize = occur::resize_t<>;
	using U_cursor = occur::cursor_t<>;

	auto _01 = _xtd::ranges::views::iota(0, 10)|_xtd::ranges::views::transform(bond::operate<T_alpha>{});
	auto _10 = _01|_xtd::ranges::views::transform([] (T_alpha n) {return n*10;});
	auto _11 = _01|_xtd::ranges::views::transform([] (T_alpha n) {return n*11;});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	auto xhs = monomer_t<U_add, provide>::bind_f(lhs, rhs);

	auto u_vector = U_store{0, 0, 0};
	auto u_review = U_review(u_vector);
	auto u_cursor = U_cursor(3);

	TRUE_(0 == xhs.size());

	xhs >>= u_cursor++ >> u_review; TRUE_(equal_f(u_vector, _std::vector{00, 11, 22}));// initialize via efflux!
	xhs >>= u_cursor++ >> u_review; TRUE_(equal_f(u_vector, _std::vector{33, 44, 55}));// advance then efflux...
	xhs >>= u_cursor++ >> u_review; TRUE_(equal_f(u_vector, _std::vector{66, 77, 88}));// advance then efflux...
	xhs <<= Ox_onset((T_alpha) (11 + 1));
	xhs >>= u_cursor++ >> u_review; TRUE_(equal_f(u_vector, _std::vector{111, 122, 133}));// advance then efflux...

}
TAG_("monomer", "provision")
{
	TRY_("advancing (dynamic)") {monomer_provision__advancing<Px_dynamic_onset_mix>();}
	TRY_("advancing (static)")  {monomer_provision__advancing< Px_static_onset_mix>();}

	TRY_("provisioning (dynamic)") {monomer_provision__provisioning<Px_dynamic_onset_mix>();}
	TRY_("provisioning (static)")  {monomer_provision__provisioning< Px_static_onset_mix>();}

}


///////////////////////////////////////////////////////////////////////////////

template <class U_add, typename U_mul=Px_dynamic_term>
void monomer_chaining__rvalue()
{
	using T_sigma = typename bond::fit<>::sigma_type;
	using T_alpha = typename bond::fit<>::alpha_type;

	unsigned constexpr N = 4;
	
	using namespace _xtd::ranges;
	auto _01 =  views::iota(0, 10)|views::transform(bond::operate<T_alpha>{});
	auto _10 = _01|views::transform([] (auto n) {return n*10;});
	auto _11 = _01|views::transform([] (auto n) {return n*11;});
	
	using mix_op = monomer_t<U_add, provision::stored<>>;
	using mul_op = monomer_t<U_mul, provision::stored<>>;
	auto yhs = mul_op::bind_f(mix_op::bind_f(processor::let_f(_01), processor::let_f(_10)));

	yhs <<= occur::resize_f(N);
	yhs <<= Ox_scale((T_alpha) 100);
	yhs <<= Ox_onset((T_alpha) 000);
	TRUE_(0 == yhs.size());

	auto seq = occur::cursor_f(N);
	yhs >>= seq  ; TRUE_(N == yhs.size());// automorphism!
	yhs >>= seq++; TRUE_(equal_f(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >>= seq++; TRUE_(equal_f(yhs, _std::vector{4400, 5500, 6600, 7700}));

	TRUE_(yhs.template argument<0>().store().empty());

}
template <class U_add, typename U_mul=Px_dynamic_term>
void monomer_chaining__lvalue()
{
	using T_sigma = typename bond::fit<>::sigma_type;
	using T_alpha = typename bond::fit<>::alpha_type;

	unsigned constexpr N = 4;

	using namespace _xtd::ranges;
	auto _01 = views::iota(0, 10)|views::transform(bond::operate<T_alpha>{});
	auto _10 = _01|views::transform([] (T_alpha n) {return n*10;});
	auto _11 = _01|views::transform([] (T_alpha n) {return n*11;});
	
	using mix_op = monomer_t<U_add, provision::stored<>>;
	using mul_op = monomer_t<U_mul, provision::stored<>>;
	auto  lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto  rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	auto  xhs = mix_op::bind_f(lhs, rhs);
	auto  yhs = mul_op::bind_f(xhs);

	yhs <<= occur::resize_f(N);
	yhs <<= Ox_scale((T_alpha) 100);
	xhs <<= Ox_onset((T_alpha) 000);

	auto seq = occur::cursor_f(N);
	yhs >>= seq  ;// automorphism!
	yhs >>= seq++; TRUE_(equal_f(yhs, _std::vector{0000, 1100, 2200, 3300}));
	yhs >>= seq++; TRUE_(equal_f(yhs, _std::vector{4400, 5500, 6600, 7700}));

	TRUE_(yhs.template argument<0>().store().size() == 4);

}
template <class U_add, typename U_mul=Px_dynamic_term>
void monomer_chaining__shared()
{
	using T_sigma = typename bond::fit<>::sigma_type;
	using T_alpha = typename bond::fit<>::alpha_type;

	unsigned constexpr N = 4;

	using namespace _xtd::ranges;
	auto _01 =  views::iota(0, 10)|views::transform(bond::operate<T_alpha>{});
	auto _10 = _01|views::transform([] (auto n) {return n*10;});
	auto _11 = _01|views::transform([] (auto n) {return n*11;});

	using mix_op = monomer_t<U_add, provision::stored<>>;
	using mix_fn = monomer_t<U_add>;
	using idx_fn = monomer_t<Px_dynamic_count>;

	auto _xx = idx_fn::bind_f();
	auto xhs = mix_op::bind_f(_xx);
	auto lhs = mix_fn::bind_f(xhs, processor::let_f(_01));
	auto rhs = mix_fn::bind_f(xhs, processor::let_f(_10));
	auto yhs = mix_fn::bind_f(lhs, rhs);

	//\
	yhs <<= occur::restep_f(50U);
	yhs <<= occur::restep_f((size_type) 50);
	yhs <<= occur::resize_f(N);

	yhs >>= occur::cursor_f(N)*0; TRUE_(equal_f(yhs, _std::vector{000, 111, 222, 333}));
	yhs >>= occur::cursor_f(N)*1; TRUE_(equal_f(yhs, _std::vector{444, 555, 666, 777}));

}
TAG_("monomer", "chaining")
{
	TRY_("rvalue (dynamic)") {monomer_chaining__rvalue<Px_dynamic_onset_mix>();}
	TRY_("rvalue (static)")  {monomer_chaining__rvalue< Px_static_onset_mix>();}

	TRY_("lvalue (dynamic)") {monomer_chaining__lvalue<Px_dynamic_onset_mix>();}
	TRY_("lvalue (static)")  {monomer_chaining__lvalue< Px_static_onset_mix>();}

	TRY_("shared (dynamic)") {monomer_chaining__shared<Px_dynamic_onset_mix>();}
	TRY_("shared (static)")  {monomer_chaining__shared< Px_static_onset_mix>();}

}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
