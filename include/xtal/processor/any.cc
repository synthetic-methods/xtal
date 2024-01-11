#pragma once
#include "../any.cc"
#include "./any.ii"// testing...





XTAL_ENV_(push)
namespace xtal::processor::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__test;


////////////////////////////////////////////////////////////////////////////////

template <class mix_t>
void processor_prepare__messaging()
{
	using alpha_t = typename common::computer::alpha_t;

	auto const _01 = _v3::views::iota(0, 3)|_v3::views::transform(to_f<alpha_t>);
	auto const _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto const _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

	using mixer_t = processor::conferred_t<mix_t>;
	mixer_t mixer_f;
	auto o_mixed = mixer_f(_01, _10);

	TRUE_(equal_f(o_mixed, _11));
	TRUE_(equal_f(o_mixed, _std::vector {00.0, 11.0, 22.0}));

	mixer_f <<= onset_t(33.0);

	if constexpr (is_q<mix_t, static_onset_mix_t>) {
		//	NOTE: Parameters take effect when the `processor` is invoked, \
		so the function is only resolved once for each collection to which it is applied. \

		TRUE_(equal_f(o_mixed, _std::vector {00.0, 11.0, 22.0}));
	}
	if constexpr (is_q<mix_t, dynamic_onset_mix_t>) {
		//	NOTE: Parameters take effect when the underlying `process` is invoked, \
		so the function is resolved for each sample. \

		TRUE_(equal_f(o_mixed, _std::vector {33.0, 44.0, 55.0}));
	}

}
TAG_("processor", "message")
{
	TRY_("messaging (dynamic)") {processor_prepare__messaging<dynamic_onset_mix_t>();}
	TRY_("messaging (static)")  {processor_prepare__messaging< static_onset_mix_t>();}

}
TAG_("processor", "construct")
{
	TRY_("letting")
	{
		size_t constexpr N_size = 5;
		using group_u = common::solid::linear_t<int[N_size]>;
		auto z = group_u {00, 11, 22, 33, 44};
		auto a = processor::let_f(z);
		
	}
	TRY_("lifting")
	{
		using alpha_t = typename common::computer::alpha_t;

		size_t constexpr N_size = 5;
		using group_u = common::solid::linear_t<alpha_t[N_size]>;
		
		auto f = processor::let_f([] (XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
		auto x = group_u { 0,  1,  2,  3,  4};
		auto y = group_u {00, 10, 20, 30, 40};
		auto z = group_u {00, 11, 22, 33, 44};
		auto a = group_u {00, 00, 00, 00, 00};
		auto b = f(x, y);
		
		_v3::ranges::move(b, a.begin());
		TRUE_(a == z);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
