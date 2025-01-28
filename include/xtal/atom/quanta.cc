#pragma once
#include "./any.cc"
#include "./quanta.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(atomic_q<quanta_t<float[2]>>);

static_assert(not counted_q<quanta_t<        int[2]>>);
static_assert(not counted_q<quanta_t<counter_t<>[2]>>);
static_assert(not counted_q<quanta_t<  size_type[2]>>);


////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("quanta")
{
	using _fix = bond::fixture<>;
	using T_delta = typename _fix::delta_type;
	using T_sigma = typename _fix::sigma_type;
	using T_alpha = typename _fix::alpha_type;
	using T_aphex = typename _fix::aphex_type;

	TRY_("scalar multiplication")
	{
		using U2_alpha = quanta_t<T_alpha[2]>;
		using U2_aphex = quanta_t<T_aphex[2]>;
		U2_alpha x{1, 2}; x *= (T_alpha) 10;
		U2_aphex y{1, 2}; y *= (T_alpha) 10;

		TRUE_(x == U2_alpha{10, 20});
		TRUE_(y == U2_aphex{10, 20});

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
