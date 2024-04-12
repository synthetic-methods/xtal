#pragma once
#include "./any.cc"
#include "./phasor.hh"// testing...





XTAL_ENV_(push)
namespace xtal::process::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("phasor")
{
	using re = bond::realized;
	using T_sigma = typename re::sigma_t;
	using T_delta = typename re::delta_t;
	using T_alpha = typename re::alpha_t;
	using U_phi = process::phasor_t<size_t[2]>;
	using W_phi = algebra::differential::phase_t<size_t[2]>;

	TRY_("trial")
	{
		EST_("progression")
		{
			T_alpha x = re::haplo_f(17), x_dt = re::haplo_f(16);
			T_alpha y = re::haplo_f(64);
			U_phi phi{x, x_dt};

			for (T_sigma i = 0x1000; ~--i;) {
				y *= (T_alpha) phi();
			}
			return y;

		};
	}
	TRY_("progression")
	{
		T_alpha x = 0, x_dt = re::haplo_f(4);

		U_phi phi{x, x_dt};

		TRUE_(phi() == U_phi{ 1*x_dt, x_dt});
		TRUE_(phi() == U_phi{ 2*x_dt, x_dt});
		TRUE_(phi() == U_phi{ 3*x_dt, x_dt});
		TRUE_(phi() == U_phi{ 4*x_dt, x_dt});
		TRUE_(phi() == U_phi{ 5*x_dt, x_dt});
		TRUE_(phi() == U_phi{ 6*x_dt, x_dt});
		TRUE_(phi() == U_phi{ 7*x_dt, x_dt});
		TRUE_(phi() == U_phi{-8*x_dt, x_dt});
		TRUE_(phi() == U_phi{-7*x_dt, x_dt});
		TRUE_(phi() == U_phi{-6*x_dt, x_dt});
		TRUE_(phi() == U_phi{-5*x_dt, x_dt});
		TRUE_(phi() == U_phi{-4*x_dt, x_dt});
		TRUE_(phi() == U_phi{-3*x_dt, x_dt});
		TRUE_(phi() == U_phi{-2*x_dt, x_dt});
		TRUE_(phi() == U_phi{-1*x_dt, x_dt});

	}
	TRY_("multiplication")
	{
		T_alpha x =  0.33, x_dt = re::haplo_f(4);
		T_alpha y =  5.55;
		T_alpha z =  x*y;

		U_phi phi{x, x_dt};

	//	TRUE_(U_phi{x, x_dt} == phi);
		TRUE_(U_phi{x, x_dt} == phi.head());
		TRUE_(W_phi{x, x_dt} == phi.head());
		TRUE_(x == phi.head() (0));

		phi *= y;
		TRUE_(bond::computrim_f<8>(phi.head() (0)) == bond::computrim_f<8>(z - _std::round(z)));

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
