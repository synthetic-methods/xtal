#pragma once
#include "./any.c++"
#include "./anybody.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::processor::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__test;


////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/processor/anybody.hpp: letting")
{
	size_t constexpr N_size = 5;
	using group_u = typename collate_t<N_size>::template group_t<int>;
	auto z = group_u {00, 11, 22, 33, 44};
	auto a = processor::let_f(z);
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/processor/anybody.hpp: lifting")
{
	using alpha_t = typename realized::alpha_t;

	size_t constexpr N_size = 5;
	using group_u = typename collate_t<N_size>::template group_t<alpha_t>;
	
	auto f = processor::let_f([] (XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
	auto x = group_u { 0,  1,  2,  3,  4};
	auto y = group_u {00, 10, 20, 30, 40};
	auto z = group_u {00, 11, 22, 33, 44};
	auto a = group_u {00, 00, 00, 00, 00};
	auto b = f(x, y);
	
	_v3::ranges::move(b, a.begin());
	REQUIRE(a == z);
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <class mix_t>
void test__contrivance()
{
	using alpha_t = typename realized::alpha_t;

	auto const _01 = _v3::views::iota(0, 3)|_v3::views::transform(to_f<alpha_t>);
	auto const _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto const _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

	using mixer_t = processor::lift_t<mix_t>;
	mixer_t mixer_f;
	auto mixed_o = mixer_f(_01, _10);

	REQUIRE(_v3::ranges::equal(mixed_o, _11));
	REQUIRE(_v3::ranges::equal(mixed_o, _std::vector {00.0, 11.0, 22.0}));

	mixer_f << onset_t(33.0);

	if constexpr (is_q<mix_t, static_onset_mix_t>) {
		//	NOTE: Parameters take effect when the `processor` is invoked, \
		so the function is only resolved once for each collection to which it is applied. \

		REQUIRE(_v3::ranges::equal(mixed_o, _std::vector {00.0, 11.0, 22.0}));
	}
	if constexpr (is_q<mix_t, dynamic_onset_mix_t>) {
		//	NOTE: Parameters take effect when the underlying `process` is invoked, \
		so the function is resolved for each sample. \

		REQUIRE(_v3::ranges::equal(mixed_o, _std::vector {33.0, 44.0, 55.0}));
	}

}

TEST_CASE("xtal/processor/anybody.hpp: contrivance.")
{
	test__contrivance<dynamic_onset_mix_t>();
	test__contrivance<static_onset_mix_t>();
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)