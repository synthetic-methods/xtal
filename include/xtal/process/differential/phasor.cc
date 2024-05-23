#pragma once
#include "./any.cc"
#include "./phasor.hh"// testing...

#include "../mop.hh"
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
	using W_phi = T_alpha[2];
	using X_phi = algebra::differential::modular_t <W_phi>;
	using Y_phi = process::differential::phasor_t  <W_phi>;
	using Z_phi = processor::monomer_t<Y_phi, resource::restore<constant_t<0x1000>>>;

	//\
	using Y_psi = process::confined_t<process::mop<enforce_f()>, process::differential::phasor<W_phi>>;
	using Y_psi = process::differential::phasor_t<W_phi, resource::example<>>;
	using Z_psi = processor::monomer_t<Y_psi, resource::restore<constant_t<0x1000>>>;

	TRY_("trial")
	{
		T_sigma constexpr result_n = 0x1000;
		T_alpha result_a[2][result_n]{};

		XTAL_VAR result_o = bond::pact_bind_f<2>(result_n, result_a);
		XTAL_USE result_t = reiterated_t<XTAL_TYP_(result_o)>;
		XTAL_LET x_delta  = re::ratio_f(7);
		XTAL_VAR x_phi = X_phi        {}; x_phi <<=                          {re::ratio_f(7)};
		XTAL_VAR y_phi = Y_phi        {}; y_phi <<= occur::indent_s<X_phi, 1>{re::ratio_f(7)}; y_phi <<= occur::resize_t<>(result_n);
		XTAL_VAR z_phi = Z_phi::bind_f(); z_phi <<= occur::indent_s<X_phi, 1>{re::ratio_f(7)}; z_phi <<= occur::resize_t<>(result_n);
		XTAL_VAR z_psi = Z_psi::bind_f(); z_psi <<= occur::indent_s<X_phi, 1>{re::ratio_f(7)}; z_psi <<= occur::resize_t<>(result_n);

		EST_("procession (process)")
		{
			y_phi <<= occur::indent_s<X_phi, 1>{x_delta};

			for (int i = 0; i < result_n; ++i) {
				result_o[i] = pact_make_f(y_phi().got());
			}

		};
		EST_("procession (processor: `ranges::transform(z|...)` in-place)")
		{
			occur::render_t<        > z_ren(result_n);
			occur::revise_t<result_t> z_rev(result_o);

			z_psi <<= occur::indent_s<X_phi, 1>{x_delta};
		//	z_psi >>= z_ren++;
			(void) z_psi.efflux_pull_apart(z_rev, z_ren++);
		//	(void) z_phi.efflux_pull_apart(z_rev, z_ren++);

		};
		EST_("procession (processor: `ranges::transform(z...)`)")
		{
			occur::render_t<> z_ren(result_n);

			z_phi <<= occur::indent_s<X_phi, 1>{x_delta};
			z_phi >>= z_ren++;
			//\
			_std::transform(z_phi.begin(), z_phi.end(), result_o.begin(), [] (auto &&o) XTAL_0FN_(bond::pact_make_f(XTAL_REF_(o) ())));
			_v3::ranges::transform(z_phi, result_o.begin(), [] (auto &&o) XTAL_0FN_(bond::pact_make_f(XTAL_REF_(o) ())));

		};
		EST_("procession (processor: `ranges::for`)")
		{
			occur::render_t<> z_ren(result_n);

			z_phi <<= occur::indent_s<X_phi, 1>{x_delta};
			z_phi >>= z_ren++;

			for (int i = 0; i < result_n; ++i) {result_o[i] = pact_make_f(z_phi.store()[i] ());}

		};
		EST_("procession (processor: `ranges::move(z|...)`)")
		{
			occur::render_t<> z_ren(result_n);

			z_phi <<= occur::indent_s<X_phi, 1>{x_delta};
			z_phi >>= z_ren++;
			//\
			_v3::ranges::move(z_phi|enforce_f()|bond::pact_make_f, result_o.begin());
			_v3::ranges::move(z_phi|[] (auto &&o) XTAL_0FN_(bond::pact_make_f(XTAL_REF_(o) ())), result_o.begin());

		};
	}
	/**/
	TRY_("progression")
	{
		T_alpha x_d4 = re::haplo_f(4);
		T_alpha x_d3 = re::haplo_f(3);
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
		T_alpha x_d4 = re::haplo_f(4);
		T_alpha x_d3 = re::haplo_f(3);
		T_alpha z_outs[2][8]{};
		auto  z_out = bond::pact_bind_f<2>(8, z_outs);
		using Z_out = reiterated_t<XTAL_TYP_(z_out)>;

		auto z_psi = Z_psi::bind_f();
	//	static_assert(is_q<X_phi, decltype(z_phi.store().front())>);

		occur::resize_t<> z_req(8);
		occur::render_t<> z_ren(8);
		occur::revise_t<Z_out> z_rev(z_out);

		z_psi <<= occur::indent_s<X_phi, 1>{x_d4};
		z_psi <<= z_req;
		
	//	static_assert(is_q<bond::pact_t<T_alpha, T_alpha>, iteratee_t<decltype(z_psi.store())>>);

		//\
		(void) z_psi.efflux(z_rev, z_ren++);
		z_psi >>= z_ren++ >> z_rev;
		//\
		TRUE_(z_out[0] == bond::pact_f( 1*x_d4, x_d4));
		TRUE_(z_out[0] == bond::pact_t<T_alpha, T_alpha>( 1*x_d4, x_d4));
		TRUE_(z_out[1] == bond::pact_f( 2*x_d4, x_d4));
		TRUE_(z_out[2] == bond::pact_f( 3*x_d4, x_d4));
		TRUE_(z_out[3] == bond::pact_f( 4*x_d4, x_d4));
		TRUE_(z_out[4] == bond::pact_f( 5*x_d4, x_d4));
		TRUE_(z_out[5] == bond::pact_f( 6*x_d4, x_d4));
		TRUE_(z_out[6] == bond::pact_f( 7*x_d4, x_d4));
		TRUE_(z_out[7] == bond::pact_f(-8*x_d4, x_d4));

		z_psi <<= occur::indent_s<X_phi, 1>{x_d3};

		//\
		(void) z_psi.efflux(z_rev, z_ren++);
		z_psi >>= z_ren++ >> z_rev;
		TRUE_(z_out[0] == bond::pact_f(-3*x_d3, x_d3));
		TRUE_(z_out[1] == bond::pact_f(-2*x_d3, x_d3));
		TRUE_(z_out[2] == bond::pact_f(-1*x_d3, x_d3));
		TRUE_(z_out[3] == bond::pact_f(-0*x_d3, x_d3));
		TRUE_(z_out[4] == bond::pact_f( 1*x_d3, x_d3));
		TRUE_(z_out[5] == bond::pact_f( 2*x_d3, x_d3));
		TRUE_(z_out[6] == bond::pact_f( 3*x_d3, x_d3));
		TRUE_(z_out[7] == bond::pact_f(-4*x_d3, x_d3));

	}
	TRY_("procession")
	{
		T_alpha x_d4 = re::haplo_f(4);
		T_alpha x_d3 = re::haplo_f(3);
		T_alpha z_outs[2][8]{};
		auto z_out = bond::pact_bind_f<2>(8, z_outs);

		auto z_phi = Z_phi::bind_f();
		static_assert(is_q<X_phi, decltype(z_phi.store().front())>);

		occur::resize_t<> z_req(8);
		occur::render_t<> z_ren(8);


		z_phi <<= occur::indent_s<X_phi, 1>{x_d4};
		z_phi <<= z_req;
		z_phi >>= z_ren++;
		//\
		_v3::ranges::copy(z_phi|enforce_f(), z_out.begin());
		_v3::ranges::move(z_phi|enforce_f(), z_out.begin());

		TRUE_(z_out[0] == bond::pact_f( 1*x_d4, x_d4));
		TRUE_(z_out[1] == bond::pact_f( 2*x_d4, x_d4));
		TRUE_(z_out[2] == bond::pact_f( 3*x_d4, x_d4));
		TRUE_(z_out[3] == bond::pact_f( 4*x_d4, x_d4));
		TRUE_(z_out[4] == bond::pact_f( 5*x_d4, x_d4));
		TRUE_(z_out[5] == bond::pact_f( 6*x_d4, x_d4));
		TRUE_(z_out[6] == bond::pact_f( 7*x_d4, x_d4));
		TRUE_(z_out[7] == bond::pact_f(-8*x_d4, x_d4));
		
		z_phi <<= occur::indent_s<X_phi, 1>{x_d3};
		z_phi >>= z_ren++;
		//\
		_v3::ranges::copy(z_phi|enforce_f(), z_out.begin());
		_v3::ranges::copy(z_phi|enforce_f()|bond::pact_make_f, z_out.begin());
		
		TRUE_(z_out[0] == bond::pact_f(-3*x_d3, x_d3));
		TRUE_(z_out[1] == bond::pact_f(-2*x_d3, x_d3));
		TRUE_(z_out[2] == bond::pact_f(-1*x_d3, x_d3));
		TRUE_(z_out[3] == bond::pact_f(-0*x_d3, x_d3));
		TRUE_(z_out[4] == bond::pact_f( 1*x_d3, x_d3));
		TRUE_(z_out[5] == bond::pact_f( 2*x_d3, x_d3));
		TRUE_(z_out[6] == bond::pact_f( 3*x_d3, x_d3));
		TRUE_(z_out[7] == bond::pact_f(-4*x_d3, x_d3));

	}
	/***/
	TRY_("multiplication")
	{
		T_alpha x =  0.33, x_d4 = re::haplo_f(4);
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
