#pragma once
#include "./any.cc"
#include "./bracket.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//atic_assert(atomic_q<bracket_t<float[2]>>);

static_assert(not counted_q<bracket_t<        int[2]>>);
static_assert(not counted_q<bracket_t<counter_t<>[2]>>);
static_assert(not counted_q<bracket_t<  size_type[2]>>);


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("bracket")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	using W_alpha = bracket_t<T_alpha[2]>; using U_alpha_ = bracket_t<T_alpha(&)[1]>;
	using W_aphex = bracket_t<T_aphex[2]>; using U_aphex_ = bracket_t<T_aphex(&)[1]>;

	TRY_("bracket equality")
	{
		W_alpha w_alpha{ 1 ,  2 };
		W_aphex w_aphex{{1}, {2}};

		TRUE_(W_alpha{ 1 ,  2 } == w_alpha);
		TRUE_(W_aphex{{1}, {2}} == w_aphex);

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("pack")
{
	TRY_("pack_item_f({...std::complex{...}})")
	{
		using U_nested = bracket_t<bracket_t<std::complex<float>[2]>[2]>;
		U_nested mat{{{00, 01}, {02, 03}}, {{04, 05}, {06, 07}}};
		TRUE_(pack_item_f<1, 1, 1>(mat) == mat[1][1].imag());

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
