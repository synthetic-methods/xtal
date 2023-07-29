#pragma once
#include "./any.c++"
#include "./phasor.hpp"// testing...





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
	
	TRY_("initialize")
	{
		using phi_t = phasor_t<size_t[2]>;
		phi_t phi_o{1};

		TRUE_(phi_o[0] == 1);
		TRUE_(phi_o[1] == 0);

	}
	TRY_("advance")
	{
		using phi_t = phasor_t<size_t[2]>;

		phi_t phi_o{0.0, 0.4};
		TRUE_(phi_o.d(0) ==  0.0);
		TRUE_(phi_o.d(1) ==  0.4);

		(void) phi_o.method();
		TRUE_(phi_o.d(0) ==  0.4);
		TRUE_(phi_o.d(1) ==  0.4);

		(void) phi_o.method();
		TRUE_(computer::template trim_f<12>((alpha_t) phi_o.d(0)/-0.2) == 1);
		TRUE_(computer::template trim_f<12>((alpha_t) phi_o.d(1)/ 0.4) == 1);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
