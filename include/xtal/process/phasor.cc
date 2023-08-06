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
	using alpha_t = typename computer::alpha_t;
	using sigma_t = typename computer::sigma_t;
	using delta_t = typename computer::delta_t;
	using phi_t = phasor_t<size_t[2]>;
	
	TRY_("initialize")
	{
		phi_t o_phi{1};

		TRUE_(o_phi[0] == 1);
		TRUE_(o_phi[1] == 0);

	}
	TRY_("advance")
	{
		phi_t o_phi{0.0, 0.4};
		TRUE_(o_phi.d(0) ==  0.0);
		TRUE_(o_phi.d(1) ==  0.4);

		(void) o_phi.method();
		TRUE_(o_phi.d(0) ==  0.4);
		TRUE_(o_phi.d(1) ==  0.4);

		(void) o_phi.method();
		TRUE_(computer::template trim_f<12>((alpha_t) o_phi.d(0)/-0.2) == 1);
		TRUE_(computer::template trim_f<12>((alpha_t) o_phi.d(1)/ 0.4) == 1);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
