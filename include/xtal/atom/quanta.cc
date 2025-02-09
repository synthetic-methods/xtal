#pragma once
#include "./any.cc"
#include "./quanta.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//atic_assert(atomic_q<quanta_t<float[2]>>);

static_assert(not counted_q<quanta_t<        int[2]>>);
static_assert(not counted_q<quanta_t<counter_t<>[2]>>);
static_assert(not counted_q<quanta_t<  size_type[2]>>);


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("quanta")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	using W_alpha = quanta_t<T_alpha[2]>; using U_alpha_ = quanta_t<T_alpha(&)[1]>;
	using W_aphex = quanta_t<T_aphex[2]>; using U_aphex_ = quanta_t<T_aphex(&)[1]>;

	TRY_("block equality")
	{
		W_alpha w_alpha{ 1 ,  2 };
		W_aphex w_aphex{{1}, {2}};

		TRUE_(W_alpha{ 1 ,  2 } == w_alpha);
		TRUE_(W_aphex{{1}, {2}} == w_aphex);

	}
	TRY_("quanta checking")
	{
		W_alpha w_0{0, 0};
		W_alpha w_1{1, 1};

		  TRUE_(w_0.blanked());
		UNTRUE_(w_1.blanked());

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("pack")
{
	TRY_("pack_item_f({...std::complex{...}})")
	{
		using U_nested = quanta_t<quanta_t<_std::complex<float>[2]>[2]>;
		U_nested etc{{{00, 01}, {02, 03}}, {{04, 05}, {06, 07}}};
		TRUE_(pack_item_f<1, 1, 1>(etc) == etc[1][1].imag());

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
