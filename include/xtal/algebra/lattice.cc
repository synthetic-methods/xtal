#pragma once
#include "./any.cc"
#include "./lattice.hh"// testing...





XTAL_ENV_(push)
namespace xtal::algebra::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("lattice")
{
	using _op = bond::operating;
	using T_delta = typename _op::delta_type;
	using T_sigma = typename _op::sigma_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;

	auto constexpr iffy = XTAL_FUN_(bond::computrim_f<16>);

	TRY_("scalar multiplication")
	{
		using U2_alpha = lattice_t<T_alpha[2]>;
		using U2_aphex = lattice_t<T_aphex[2]>;
		U2_alpha x{1, 2}; x *= (T_alpha) 10;
		U2_aphex y{1, 2}; y *= (T_alpha) 10;

		TRUE_(x == U2_alpha{10, 20});
		TRUE_(y == U2_aphex{10, 20});

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("pack")
{
	TRY_("pack_item_f({...std::complex{...}})")
	{
		using U_nested = lattice_t<lattice_t<_std::complex<float>[2]>[2]>;
		U_nested etc{{{00, 01}, {02, 03}}, {{04, 05}, {06, 07}}};
		TRUE_(pack_item_f<1, 1, 1>(etc) == etc[1][1].imag());

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
