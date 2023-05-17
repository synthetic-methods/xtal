#pragma once
#include "./any.hpp"
#include "../message/numinal.hpp"
#include "../message/start.hpp"




XTAL_ENV_(push)
namespace xtal::processor::_test::any
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using bias_t = message::numinal_t<alpha_t, struct bias>;

struct static_bias_mix_t
:	process::confine_t<static_bias_mix_t
	,	bias_t::template dispatch<4>
	>
{
	template <auto bias>
	XTAL_FN2 method(XTAL_DEF... xs)
	{
		return (XTAL_REF_(xs) + ... + bias);
	}
};
struct dynamic_bias_mix_t
:	process::confine_t<dynamic_bias_mix_t
	,	bias_t::attach
	>
{
	template <auto...>
	XTAL_FN2 method(XTAL_DEF... xs)
	{
		return (XTAL_REF_(xs) + ... + this->template get<bias_t>());
	}
};

////////////////////////////////////////////////////////////////////////////////

template <typename mix_t>
void contrivance__test()
{
	auto const _01 = _v3::views::iota(0, 3)|_v3::views::transform(craft_f<alpha_t>);
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
