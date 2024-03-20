#pragma once
#include "./any.cc"
#include "./cycle.ii"// testing...





XTAL_ENV_(push)
namespace xtal::process::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("cycle")
{
	using re = atom::realized;
	using T_sigma = typename re::sigma_t;
	using T_alpha = typename re::alpha_t;
	using U_phi = cycle_t<size_t[2]>;

	EST_("method")
	{
		T_alpha x = re::haplo_f(17), x_dt = re::haplo_f(16);
		T_alpha y = re::haplo_f(64);
		U_phi phi {x, x_dt};

		for (T_sigma i = 0x1000; ~--i;) {
			y *= (T_alpha) phi();
		}
		return y;

	};
	TRY_("method")
	{
		T_alpha x = 0, x_dt = re::haplo_f(4);

		U_phi phi {x, x_dt};

		TRUE_(phi() == U_phi { 1*x_dt, x_dt});
		TRUE_(phi() == U_phi { 2*x_dt, x_dt});
		TRUE_(phi() == U_phi { 3*x_dt, x_dt});
		TRUE_(phi() == U_phi { 4*x_dt, x_dt});
		TRUE_(phi() == U_phi { 5*x_dt, x_dt});
		TRUE_(phi() == U_phi { 6*x_dt, x_dt});
		TRUE_(phi() == U_phi { 7*x_dt, x_dt});
		TRUE_(phi() == U_phi {-8*x_dt, x_dt});
		TRUE_(phi() == U_phi {-7*x_dt, x_dt});
		TRUE_(phi() == U_phi {-6*x_dt, x_dt});
		TRUE_(phi() == U_phi {-5*x_dt, x_dt});
		TRUE_(phi() == U_phi {-4*x_dt, x_dt});
		TRUE_(phi() == U_phi {-3*x_dt, x_dt});
		TRUE_(phi() == U_phi {-2*x_dt, x_dt});
		TRUE_(phi() == U_phi {-1*x_dt, x_dt});

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
