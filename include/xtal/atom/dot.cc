#pragma once
#include "./any.cc"
#include "./dot.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("dot")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	TRY_("dot (multiplicative)")
	{
		using U_couple =  couple_t<T_alpha[2]>;
		using U_dot    =     dot_t<T_alpha[2]>;
		U_couple u_couple{2, 3};
		U_dot    u_dot   {4, 9};
		TRUE_(u_dot*u_couple == 35.);
		TRUE_(u_couple*u_dot == 35.);

		TRUE_(    bond::subtabbed_q<dot_t<float[2]>, couple_t<float[2]>>);
		TRUE_(not bond::subtabbed_q<couple_t<float[2]>, dot_t<float[2]>>);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
