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
	using Y_phi = process::phasor_t<size_t[2]>;
	using W_phi = algebra::differential::phase_t<size_t[2]>;

	TRY_("trial")
	{
		EST_("progression")
		{
			T_alpha x = re::haplo_f(17), x_d8 = re::haplo_f(8);
			T_alpha y = re::haplo_f(64);
			Y_phi phi{x, x_d8};

			for (T_sigma i = 0x1000; ~--i;) {
				y *= (T_alpha) phi();
			}
			return y;

		};
	}
	TRY_("progression")
	{
		T_alpha x_d4 = re::haplo_f(4);
		T_alpha x_d3 = re::haplo_f(3);
		Y_phi phi{0, x_d4};

		TRUE_(phi() == W_phi{ 1*x_d4, x_d4});
		TRUE_(phi() == W_phi{ 2*x_d4, x_d4});
		TRUE_(phi() == W_phi{ 3*x_d4, x_d4});
		TRUE_(phi() == W_phi{ 4*x_d4, x_d4});
		TRUE_(phi() == W_phi{ 5*x_d4, x_d4});
		TRUE_(phi() == W_phi{ 6*x_d4, x_d4});
		TRUE_(phi() == W_phi{ 7*x_d4, x_d4});
		phi <<= occur::indent_s<W_phi, 1>(x_d3);
	//	TRUE_(phi() == W_phi{-8*x_d4, x_d4});
		TRUE_(phi() == W_phi{-7*x_d4, x_d3});
	//	TRUE_(phi() == W_phi{-6*x_d4, x_d4});
		TRUE_(phi() == W_phi{-5*x_d4, x_d3});
	//	TRUE_(phi() == W_phi{-4*x_d4, x_d4});
		TRUE_(phi() == W_phi{-3*x_d4, x_d3});
	//	TRUE_(phi() == W_phi{-2*x_d4, x_d4});
		TRUE_(phi() == W_phi{-1*x_d4, x_d3});

	}
	TRY_("multiplication")
	{
		T_alpha x =  0.33, x_d4 = re::haplo_f(4);
		T_alpha y =  5.55;
		T_alpha z =  x*y;

		Y_phi phi{x, x_d4};

	//	TRUE_(Y_phi{x, x_d4} == phi);
		TRUE_(Y_phi{x, x_d4} == phi.head());
		TRUE_(W_phi{x, x_d4} == phi.head());
		TRUE_(x == phi.head() (0));

		phi *= y;
		TRUE_(bond::computrim_f<8>(phi.head() (0)) == bond::computrim_f<8>(z - _std::round(z)));

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
