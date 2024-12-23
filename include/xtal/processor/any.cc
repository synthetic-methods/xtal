#pragma once
#include "../any.cc"
#include "./any.hh"// testing...

#include "../algebra/all.hh"



XTAL_ENV_(push)
namespace xtal::processor::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::_test;


////////////////////////////////////////////////////////////////////////////////

struct irritator_mix
{
	class type : public process::confine_t<type
//	,	Ox_onset::dispatch<>
	>
	{
	public:

		template <auto onset=0>
		XTAL_DEF_(short,static)
		XTAL_LET function(auto &&...xs)
		noexcept -> auto
		{
			return (XTAL_REF_(xs) +...+ onset);
		}

	};
};
using Px_irritator_mix = typename irritator_mix::type;


////////////////////////////////////////////////////////////////////////////////

template <class U_mix>
void processor_provision__messaging()
{
	using T_alpha = typename bond::operating::alpha_type;

	auto const _01 = _xtd::ranges::views::iota(0, 3)|_xtd::ranges::views::transform(invoke_f<T_alpha>);
	auto const _10 = _01|_xtd::ranges::views::transform([] (T_alpha n) {return n*10;});
	auto const _11 = _01|_xtd::ranges::views::transform([] (T_alpha n) {return n*11;});

	using U_mixer = processor::conferred_t<U_mix>;
	U_mixer mixer_f;
	auto o_mixed = mixer_f(_01, _10);

	TRUE_(equal_f(o_mixed, _11));
	TRUE_(equal_f(o_mixed, _std::vector{00.0, 11.0, 22.0}));

	mixer_f <<= Ox_onset(33.0);

	/*/
	if constexpr (same_q<U_mix, Px_static_onset_mix>) {
		//	NOTE: Parameters take effect when the `processor` is invoked, \
		so the function is only resolved once for each collection to which it is applied. \

		TRUE_(equal_f(o_mixed, _std::vector{00.0, 11.0, 22.0}));
	}
	if constexpr (same_q<U_mix, Px_dynamic_onset_mix>) {
		//	NOTE: Parameters take effect when the underlying `process` is invoked, \
		so the function is resolved for each sample. \

		TRUE_(equal_f(o_mixed, _std::vector{33.0, 44.0, 55.0}));
	}
	/*/
	TRUE_(equal_f(o_mixed, _std::vector{33.0, 44.0, 55.0}));
	/***/

}
TAG_("processor", "occur")
{
	TRY_("messaging (dynamic)") {processor_provision__messaging<Px_dynamic_onset_mix>();}
	TRY_("messaging (static)")  {processor_provision__messaging< Px_static_onset_mix>();}

}
TAG_("processor", "construct")
{
//	TRY_("letting")
//	{
//		size_type constexpr N_size = 5;
//		using U_group = algebra::lattice_t<int[N_size]>;
//		auto z = U_group{00, 11, 22, 33, 44};
//		auto a = processor::let_f(z);
//		
//	}
	TRY_("lifting")
	{
		using T_alpha = typename bond::operating::alpha_type;

		size_type constexpr N_size = 5;
		using U_group = algebra::lattice_t<T_alpha[N_size]>;
		
		auto f = processor::let_f([] (auto &&...xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
		auto x = U_group { 0,  1,  2,  3,  4};
		auto y = U_group{00, 10, 20, 30, 40};
		auto z = U_group{00, 11, 22, 33, 44};
		auto a = U_group{00, 00, 00, 00, 00};
		auto b = f(x, y);
		
		_xtd::ranges::move(b, a.begin());
		TRUE_(a == z);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
