#pragma once
#include "./any.cc"
#include "./phasor.ii"// testing...





XTAL_ENV_(push)
namespace xtal::process::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("phasor")
{
	using T_alpha = typename common::computer::alpha_t;
	using T_sigma = typename common::computer::sigma_t;
	using T_delta = typename common::computer::delta_t;
	using U_phi = phasor_t<size_t[2]>;
	
	TRY_("initialize")
	{
		U_phi u_phi{1.0};

		TRUE_(u_phi[0] == 1);
		TRUE_(u_phi[1] == 0);

	}
	TRY_("advance")
	{
		U_phi u_phi{0.0, 0.4};
		TRUE_(u_phi.subscript(0) ==  0.0);
		TRUE_(u_phi.subscript(1) ==  0.4);

		(void) u_phi.method();
		TRUE_(u_phi.subscript(0) ==  0.4);
		TRUE_(u_phi.subscript(1) ==  0.4);

		(void) u_phi.method();
		TRUE_(common::computer::template trim_f<12>((T_alpha) u_phi.subscript(0)/-0.2) == 1);
		TRUE_(common::computer::template trim_f<12>((T_alpha) u_phi.subscript(1)/ 0.4) == 1);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
