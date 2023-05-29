#pragma once
#include "./any.hpp"
#include "./atom.hpp"
#include "./bond.hpp"
//#include "../control/all.hpp"


#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::processor::__any
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/processor/any.hpp: letting")
{
	sigma_t constexpr N_size = 5;
	using scalar_t = common::collect_scalar_t<N_size, int>;
	auto z = scalar_t {00, 11, 22, 33, 44};
	auto a = processor::let_f(z);
	REQUIRE(true);
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/processor/any.hpp: lifting")
{
	sigma_t constexpr N_size = 5;
	using scalar_t = common::collect_scalar_t<N_size, alpha_t>;
	
	auto f = processor::let_f([](XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) + ... + 0));
	auto x = scalar_t { 0,  1,  2,  3,  4};
	auto y = scalar_t {00, 10, 20, 30, 40};
	auto z = scalar_t {00, 11, 22, 33, 44};
	auto a = scalar_t {00, 00, 00, 00, 00};
	auto b = f(x, y);
	
	_v3::ranges::copy(b, a.begin());
	REQUIRE(a == z);
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename mix_t>
void contrivance__test()
{
	auto const _01 = _v3::views::iota(0, 3)|_v3::views::transform(to_f<alpha_t>);
	auto const _10 = _01|_v3::views::transform([](alpha_t n) {return n*10;});
	auto const _11 = _01|_v3::views::transform([](alpha_t n) {return n*11;});

	using mixer_t = processor::contrive_t<mix_t>;
	mixer_t mixer_f;
	auto mixed_y = mixer_f(_01, _10);

	REQUIRE(_v3::ranges::equal(mixed_y, _11));
	REQUIRE(_v3::ranges::equal(mixed_y, _std::vector {00.0, 11.0, 22.0}));

	mixer_f <<= bias_t(33.0);

	if constexpr (is_q<mix_t, static_bias_mix_t>)
	{
	//	NOTE: Parameters take effect when the `processor` is invoked, \
		so the function is only resolved once for each collection to which it is applied. \

		REQUIRE(_v3::ranges::equal(mixed_y, _std::vector {00.0, 11.0, 22.0}));
	}
	if constexpr (is_q<mix_t, dynamic_bias_mix_t>)
	{
	//	NOTE: Parameters take effect when the underlying `process` is invoked, \
		so the function is resolved for each sample. \

		REQUIRE(_v3::ranges::equal(mixed_y, _std::vector {33.0, 44.0, 55.0}));
	}

//	_std::cout << '\n'; for (auto _: mixed_y) _std::cout << '\t' << _; _std::cout << '\n'; REQUIRE(true);
}

TEST_CASE("xtal/processor/any.hpp: contrivance.")
{
	contrivance__test<dynamic_bias_mix_t>();
	contrivance__test<static_bias_mix_t>();
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
