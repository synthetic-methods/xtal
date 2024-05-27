#pragma once
#include "./any.cc"
#include "./phasor.hh"// testing...

#include "../map.hh"
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
	namespace a_ = algebra::differential;
	namespace d_ = process::differential;
	
	using U_restore = resource::restore<constant_t<0x1000>>;
	using U_example = resource::example<>;

	using op = bond::operating;
	using T_sigma = typename op::sigma_t;
	using T_delta = typename op::delta_t;
	using T_alpha = typename op::alpha_t;
	
	using  _phi = T_alpha[2];
	using E_phi = Eigen::Array<T_alpha, 1, 2, Eigen::RowMajor>;
	using V_phi = bond::pack_row_t<_phi>;
	using W_phi = a_::    linear_t<_phi>;
	using X_phi = a_::  circular_t<_phi>;
	using Y_phi = d_::    phasor_t<_phi>;
	using Z_phi = processor::monomer_t<Y_phi, U_restore>;
	//\
	using Y_psi = process::confined_t<process::map<W_phi>, d_::phasor<_phi>>;
	using Y_psi = d_::phasor_t<_phi, U_example>;
	using Z_psi = processor::monomer_t<Y_psi, U_restore>;

	TRY_("trial")
	{
		using namespace Eigen;
		
		XTAL_LET x_delta  = op::ratio_f(7);
		
		T_sigma constexpr N_data = 0x1000;
		T_alpha z_data[2][N_data]{};

		auto  v_data  = bond::pack_table_f<2>(N_data, z_data);
		auto  e_data  = Map<Array<T_alpha, Dynamic, 2, ColMajor>>(*z_data, N_data, 2).rowwise();
		
		auto  x_phi = X_phi        {}; x_phi <<=                          {op::ratio_f(7)};
		auto  y_phi = Y_phi        {}; y_phi <<= occur::indent_s<X_phi, 1>{op::ratio_f(7)}; y_phi <<= occur::resize_t<>(N_data);
		auto  z_phi = Z_phi::bind_f(); z_phi <<= occur::indent_s<X_phi, 1>{op::ratio_f(7)}; z_phi <<= occur::resize_t<>(N_data);
		auto  z_psi = Z_psi::bind_f(); z_psi <<= occur::indent_s<X_phi, 1>{op::ratio_f(7)}; z_psi <<= occur::resize_t<>(N_data);

		occur::render_t<>         z_render(N_data);
		occur::indent_s<X_phi, 1> z_indent{x_delta};
		
		z_phi <<= z_indent;

//		TRY_("procession (Eigen)")
//		{
//			z_phi >>= z_render++ >> occur::revise_f(e_data_);
//
//			//\
//			TRUE_(z_phi[3].template got<W_phi>() == W_phi{z_data[0][3], z_data[1][3]});
//			echo(W_phi{z_data[0][3], z_data[1][3]});
//
//		};

		EST_("procession (process in-place)")
		{
			auto &z_d0 = z_data[0];
			auto &z_d1 = z_data[1];
		//	for (int i = 0; i < N_data; ++i) {v_data[i] = V_phi(y_phi());}
			for (int i = 0; i < N_data; ++i) {
				auto const &y = y_phi();
				z_d0[i] = y(0);
				z_d1[i] = y(1);
			}

		};
		EST_("procession (processor out-of-place)")
		{
			z_psi >>= z_render++;

		};
		EST_("procession (processor in-place: `ranges::copy...`)")
		{
			z_psi >>= z_render++ >> occur::revise_f(v_data);

		};
		EST_("procession (processor in-place: `Eigen...)")
		{
			z_phi >>= z_render++ >> occur::revise_f(e_data);

		};
		EST_("procession (processor re-place: `ranges::copy...`)")
		{
			z_psi >>= z_render++;
			_xtd::ranges::copy_n(z_psi.begin(), N_data, v_data.begin());//, [] XTAL_1FN_(V_phi));

		};
		EST_("procession (processor re-place: `for`)")
		{
			z_psi >>= z_render++;
			for (int i = 0; i < N_data; ++i) {v_data[i] = z_psi[i];}

		};
	}
	/**/
	TRY_("progression")
	{
		T_alpha x_d4 = op::haplo_f(4);
		T_alpha x_d3 = op::haplo_f(3);
		Y_phi y_phi{0, x_d4};

		TRUE_(y_phi() == X_phi{ 1*x_d4, x_d4});
		TRUE_(y_phi() == X_phi{ 2*x_d4, x_d4});
		TRUE_(y_phi() == X_phi{ 3*x_d4, x_d4});
		TRUE_(y_phi() == X_phi{ 4*x_d4, x_d4});
		TRUE_(y_phi() == X_phi{ 5*x_d4, x_d4});
		TRUE_(y_phi() == X_phi{ 6*x_d4, x_d4});
		TRUE_(y_phi() == X_phi{ 7*x_d4, x_d4});
		y_phi <<= occur::indent_s<X_phi, 1>{x_d3};
	//	TRUE_(y_phi() == X_phi{-8*x_d4, x_d4});
		TRUE_(y_phi() == X_phi{-7*x_d4, x_d3});
	//	TRUE_(y_phi() == X_phi{-6*x_d4, x_d4});
		TRUE_(y_phi() == X_phi{-5*x_d4, x_d3});
	//	TRUE_(y_phi() == X_phi{-4*x_d4, x_d4});
		TRUE_(y_phi() == X_phi{-3*x_d4, x_d3});
	//	TRUE_(y_phi() == X_phi{-2*x_d4, x_d4});
		TRUE_(y_phi() == X_phi{-1*x_d4, x_d3});

	}
	TRY_("procession in-place")
	{
		T_alpha x_d4 = op::haplo_f(4);
		T_alpha x_d3 = op::haplo_f(3);
		T_alpha z_outs[2][8]{};
		auto  z_out = bond::pack_table_f<2>(8, z_outs);
		using Z_out = reiterated_t<XTAL_TYP_(z_out)>;

		auto z_psi = Z_psi::bind_f();
	//	static_assert(is_q<X_phi, decltype(z_phi.store().front())>);

		occur::resize_t<> z_req(8);
		occur::render_t<> z_ren(8);
		occur::revise_t<Z_out> z_rev(z_out);

		z_psi <<= occur::indent_s<X_phi, 1>{x_d4};
		z_psi <<= z_req;
		
	//	static_assert(is_q<bond::pack_t<T_alpha, T_alpha>, iteratee_t<decltype(z_psi.store())>>);

		//\
		(void) z_psi.efflux(z_rev, z_ren++);
		z_psi >>= z_ren++ >> z_rev;
		//\
		TRUE_(z_out[0] == bond::pack_f( 1*x_d4, x_d4));
		TRUE_(z_out[0] == bond::pack_t<T_alpha, T_alpha>( 1*x_d4, x_d4));
		TRUE_(z_out[1] == bond::pack_f( 2*x_d4, x_d4));
		TRUE_(z_out[2] == bond::pack_f( 3*x_d4, x_d4));
		TRUE_(z_out[3] == bond::pack_f( 4*x_d4, x_d4));
		TRUE_(z_out[4] == bond::pack_f( 5*x_d4, x_d4));
		TRUE_(z_out[5] == bond::pack_f( 6*x_d4, x_d4));
		TRUE_(z_out[6] == bond::pack_f( 7*x_d4, x_d4));
		TRUE_(z_out[7] == bond::pack_f(-8*x_d4, x_d4));

		z_psi <<= occur::indent_s<X_phi, 1>{x_d3};

		//\
		(void) z_psi.efflux(z_rev, z_ren++);
		z_psi >>= z_ren++ >> z_rev;
		TRUE_(z_out[0] == bond::pack_f(-3*x_d3, x_d3));
		TRUE_(z_out[1] == bond::pack_f(-2*x_d3, x_d3));
		TRUE_(z_out[2] == bond::pack_f(-1*x_d3, x_d3));
		TRUE_(z_out[3] == bond::pack_f(-0*x_d3, x_d3));
		TRUE_(z_out[4] == bond::pack_f( 1*x_d3, x_d3));
		TRUE_(z_out[5] == bond::pack_f( 2*x_d3, x_d3));
		TRUE_(z_out[6] == bond::pack_f( 3*x_d3, x_d3));
		TRUE_(z_out[7] == bond::pack_f(-4*x_d3, x_d3));

	}
	TRY_("procession")
	{
		T_alpha x_d4 = op::haplo_f(4);
		T_alpha x_d3 = op::haplo_f(3);
		T_alpha z_outs[2][8]{};
		auto z_out = bond::pack_table_f<2>(8, z_outs);

		auto z_phi = Z_phi::bind_f();
		static_assert(is_q<X_phi, decltype(z_phi.store().front())>);

		occur::resize_t<> z_req(8);
		occur::render_t<> z_ren(8);


		z_phi <<= occur::indent_s<X_phi, 1>{x_d4};
		z_phi <<= z_req;
		z_phi >>= z_ren++;
		//\
		_xtd::ranges::move(z_phi|[] XTAL_1FN_(V_phi), z_out.begin());
		_xtd::ranges::copy(z_phi|[] XTAL_1FN_(V_phi), z_out.begin());

		TRUE_(z_out[0] == bond::pack_f( 1*x_d4, x_d4));
		TRUE_(z_out[1] == bond::pack_f( 2*x_d4, x_d4));
		TRUE_(z_out[2] == bond::pack_f( 3*x_d4, x_d4));
		TRUE_(z_out[3] == bond::pack_f( 4*x_d4, x_d4));
		TRUE_(z_out[4] == bond::pack_f( 5*x_d4, x_d4));
		TRUE_(z_out[5] == bond::pack_f( 6*x_d4, x_d4));
		TRUE_(z_out[6] == bond::pack_f( 7*x_d4, x_d4));
		TRUE_(z_out[7] == bond::pack_f(-8*x_d4, x_d4));
		
		z_phi <<= occur::indent_s<X_phi, 1>{x_d3};
		z_phi >>= z_ren++;
		//\
		_xtd::ranges::copy(z_phi|[] XTAL_1FN_(V_phi), z_out.begin());
		_xtd::ranges::copy(z_phi|[] XTAL_1FN_(V_phi), z_out.begin());
		
		TRUE_(z_out[0] == bond::pack_f(-3*x_d3, x_d3));
		TRUE_(z_out[1] == bond::pack_f(-2*x_d3, x_d3));
		TRUE_(z_out[2] == bond::pack_f(-1*x_d3, x_d3));
		TRUE_(z_out[3] == bond::pack_f(-0*x_d3, x_d3));
		TRUE_(z_out[4] == bond::pack_f( 1*x_d3, x_d3));
		TRUE_(z_out[5] == bond::pack_f( 2*x_d3, x_d3));
		TRUE_(z_out[6] == bond::pack_f( 3*x_d3, x_d3));
		TRUE_(z_out[7] == bond::pack_f(-4*x_d3, x_d3));

	}
	/***/
	TRY_("multiplication")
	{
		T_alpha x =  0.33, x_d4 = op::haplo_f(4);
		T_alpha y =  5.55;
		T_alpha z =  x*y;

		Y_phi y_phi{x, x_d4};

	//	TRUE_(Y_phi{x, x_d4} == y_phi);
		TRUE_(Y_phi{x, x_d4} == y_phi.head());
		TRUE_(X_phi{x, x_d4} == y_phi.head());
		TRUE_(x == y_phi.head() (0));

		y_phi *= y;
		TRUE_(bond::computrim_f<8>(y_phi.head() (0)) == bond::computrim_f<8>(z - _std::round(z)));

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
