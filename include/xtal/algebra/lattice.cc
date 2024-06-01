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
	using Op = bond::operating;
	using T_delta = typename Op::delta_t;
	using T_sigma = typename Op::sigma_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;

	auto constexpr iffy = [] XTAL_1FN_(bond::computrim_f<16>);

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

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
