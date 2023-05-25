#pragma once
#include "./any.hpp"
#include "../message/numinal.hpp"
#include "../message/start.hpp"


#include "../any.cxx"

XTAL_ENV_(push)
namespace xtal::processor::__any
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/processor/any.hpp: lambda lifting")
{
	auto g = processor::let_f([] (XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) + ... + 0));
	auto       w = _std::vector { 0,  0,  0,  0,  0};
	auto const x = _std::vector { 0,  1,  2,  3,  4};
	auto const y = _std::vector {00, 10, 20, 30, 40};
	auto       z = g(x, y);
	_v3::ranges::copy(z, w.begin());
	REQUIRE(w[0] == 00);
	REQUIRE(w[1] == 11);
	REQUIRE(w[2] == 22);
	REQUIRE(w[3] == 33);
	REQUIRE(w[4] == 44);
}

////////////////////////////////////////////////////////////////////////////////

template <typename mix_t>
void contrivance__test()
{
	auto const _01 = _v3::views::iota(0, 3)|_v3::views::transform(construct_f<alpha_t>);
	auto const _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto const _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

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
}

TEST_CASE("xtal/processor/any.hpp: contrivance.")
{
	contrivance__test<dynamic_bias_mix_t>();
	contrivance__test<static_bias_mix_t>();
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
