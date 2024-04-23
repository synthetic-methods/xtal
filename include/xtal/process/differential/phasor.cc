#pragma once
#include "./any.cc"
#include "./phasor.hh"// testing...

#include "../../processor/monomer.hh"
#include "../../resource/all.hh"


XTAL_ENV_(push)
namespace xtal::process::differential::_test
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
	using W_phi = algebra::differential::modular_t <size_t[2]>;
	using Y_phi = process::differential::phasor_t<size_t[2]>;
	using Z_phi = processor::monomer_t<Y_phi, resource::restore<constant_t<-1>>>;

	TRY_("trial")
	{
		EST_("progression")
		{
			T_alpha x = re::haplo_f(17), x_d8 = re::haplo_f(8);
			T_alpha y = re::haplo_f(64);
			Y_phi y_phi{x, x_d8};

			for (T_sigma i = 0x1000; ~--i;) {
				y *= (T_alpha) y_phi();
			}
			return y;

		};
	}
	TRY_("progression")
	{
		T_alpha x_d4 = re::haplo_f(4);
		T_alpha x_d3 = re::haplo_f(3);
		Y_phi y_phi{0, x_d4};

		TRUE_(y_phi() == W_phi{ 1*x_d4, x_d4});
		TRUE_(y_phi() == W_phi{ 2*x_d4, x_d4});
		TRUE_(y_phi() == W_phi{ 3*x_d4, x_d4});
		TRUE_(y_phi() == W_phi{ 4*x_d4, x_d4});
		TRUE_(y_phi() == W_phi{ 5*x_d4, x_d4});
		TRUE_(y_phi() == W_phi{ 6*x_d4, x_d4});
		TRUE_(y_phi() == W_phi{ 7*x_d4, x_d4});
		y_phi <<= occur::indent_s<W_phi, 1>(x_d3);
	//	TRUE_(y_phi() == W_phi{-8*x_d4, x_d4});
		TRUE_(y_phi() == W_phi{-7*x_d4, x_d3});
	//	TRUE_(y_phi() == W_phi{-6*x_d4, x_d4});
		TRUE_(y_phi() == W_phi{-5*x_d4, x_d3});
	//	TRUE_(y_phi() == W_phi{-4*x_d4, x_d4});
		TRUE_(y_phi() == W_phi{-3*x_d4, x_d3});
	//	TRUE_(y_phi() == W_phi{-2*x_d4, x_d4});
		TRUE_(y_phi() == W_phi{-1*x_d4, x_d3});

	}
	TRY_("procession")
	{
		T_alpha x_d4 = re::haplo_f(4);
		T_alpha x_d3 = re::haplo_f(3);
		auto z_out = _std::array<W_phi, 8>{};
		auto z_phi = Z_phi::bind_f();
		static_assert(is_q<W_phi, decltype(z_phi.store().front())>);

		occur::resize_t<> z_req(8);
		occur::render_t<> z_seq(8);

		z_phi <<= occur::indent_s<W_phi, 1>(x_d4);
		z_phi <<= z_req;
		z_phi >>= z_seq++;
		_v3::ranges::copy(z_phi, z_out.begin());

		TRUE_(z_out[0] == W_phi{ 1*x_d4, x_d4});
		TRUE_(z_out[1] == W_phi{ 2*x_d4, x_d4});
		TRUE_(z_out[2] == W_phi{ 3*x_d4, x_d4});
		TRUE_(z_out[3] == W_phi{ 4*x_d4, x_d4});
		TRUE_(z_out[4] == W_phi{ 5*x_d4, x_d4});
		TRUE_(z_out[5] == W_phi{ 6*x_d4, x_d4});
		TRUE_(z_out[6] == W_phi{ 7*x_d4, x_d4});
		TRUE_(z_out[7] == W_phi{-8*x_d4, x_d4});
		
		z_phi <<= occur::indent_s<W_phi, 1>(x_d3);
		z_phi >>= z_seq++;
		_v3::ranges::copy(z_phi, z_out.begin());
		
		TRUE_(z_out[0] == W_phi{-3*x_d3, x_d3});
		TRUE_(z_out[1] == W_phi{-2*x_d3, x_d3});
		TRUE_(z_out[2] == W_phi{-1*x_d3, x_d3});
		TRUE_(z_out[3] == W_phi{-0*x_d3, x_d3});
		TRUE_(z_out[4] == W_phi{ 1*x_d3, x_d3});
		TRUE_(z_out[5] == W_phi{ 2*x_d3, x_d3});
		TRUE_(z_out[6] == W_phi{ 3*x_d3, x_d3});
		TRUE_(z_out[7] == W_phi{-4*x_d3, x_d3});

	}
	TRY_("multiplication")
	{
		T_alpha x =  0.33, x_d4 = re::haplo_f(4);
		T_alpha y =  5.55;
		T_alpha z =  x*y;

		Y_phi y_phi{x, x_d4};

	//	TRUE_(Y_phi{x, x_d4} == y_phi);
		TRUE_(Y_phi{x, x_d4} == y_phi.head());
		TRUE_(W_phi{x, x_d4} == y_phi.head());
		TRUE_(x == y_phi.head() (0));

		y_phi *= y;
		TRUE_(bond::computrim_f<8>(y_phi.head() (0)) == bond::computrim_f<8>(z - _std::round(z)));

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
