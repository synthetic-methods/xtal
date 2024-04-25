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
	using M_phi = algebra::differential::linear_t  <T_alpha[2]>;
	using W_phi = algebra::differential::modular_t <T_alpha[2]>;
	using Y_phi = process::differential::phasor_t  <T_alpha[2]>;
	using Z_phi = processor::monomer_t<Y_phi, resource::restore<constant_t<-1>>>;

	TRY_("trial")
	{
		T_sigma constexpr bazook_n = 0x1000;
		T_alpha bazook_s[2][bazook_n]{};
	//	auto bazook_o = _std::array<M_phi, 8>{};
		auto bazook_o = bond::pact_bind_f<2>(bazook_n, bazook_s);
		auto bazook_w = W_phi        {}; bazook_w <<=                          {re::ratio_f(7)};
		auto bazook_y = Y_phi        {}; bazook_y <<= occur::indent_s<W_phi, 1>(re::ratio_f(7)); bazook_y <<= occur::resize_t<>(bazook_n);
		auto bazook_z = Z_phi::bind_f(); bazook_z <<= occur::indent_s<W_phi, 1>(re::ratio_f(7)); bazook_z <<= occur::resize_t<>(bazook_n);
		auto bazook_a = bazook_z.store();

		EST_("procession (process)")
		{
			bazook_y <<= occur::indent_s<W_phi, 1>(re::ratio_f(7));

			for (T_sigma i = 0; i < bazook_n; ++i) {
				bazook_o[i] = pact_make_f(bazook_y() ());
			}

		};
		EST_("procession (praxis)")
		{
			bazook_w <<= {re::ratio_f(7)};

			for (T_sigma i = 0; i < bazook_n; ++i) {
				bazook_o[i] = pact_make_f(bazook_w());
			}

		};
		EST_("procession (processor: `ranges::transform(z...)`)")
		{
			T_alpha constexpr x_dt = re::ratio_f(7);

		//	auto bazook_o = _std::array<M_phi, bazook_n>{};

			occur::resize_t<> z_req(bazook_n);
			occur::render_t<> z_seq(bazook_n);

			bazook_z <<= occur::indent_s<W_phi, 1>(re::ratio_f(7));
			bazook_z <<= z_req;
			bazook_z >>= z_seq++;
			//\
			_std::transform(bazook_z.begin(), bazook_z.end(), bazook_o.begin(), [] (auto &&o) XTAL_0FN_(bond::pact_make_f(XTAL_REF_(o) ())));
			_v3::ranges::transform(bazook_z, bazook_o.begin(), [] (auto &&o) XTAL_0FN_(bond::pact_make_f(XTAL_REF_(o) ())));

		};
		EST_("procession (processor: `ranges::for`)")
		{
			T_alpha constexpr x_dt = re::ratio_f(7);

		//	auto bazook_o = _std::array<M_phi, bazook_n>{};

			occur::resize_t<> z_req(bazook_n);
			occur::render_t<> z_seq(bazook_n);

			bazook_z <<= occur::indent_s<W_phi, 1>(re::ratio_f(7));
			bazook_z <<= z_req;
			bazook_z >>= z_seq++;

			for (T_sigma i = 0; i < bazook_n; ++i) {bazook_o[i] = pact_make_f(bazook_z.store()[i] ());}

		};
		EST_("procession (processor: `ranges::for_each`)")
		{
			T_alpha constexpr x_dt = re::ratio_f(7);

		//	auto bazook_o = _std::array<M_phi, bazook_n>{};

			occur::resize_t<> z_req(bazook_n);
			occur::render_t<> z_seq(bazook_n);

			bazook_z <<= occur::indent_s<W_phi, 1>(re::ratio_f(7));
			bazook_z <<= z_req;
			bazook_z >>= z_seq++;

			_v3::ranges::for_each(bazook_z, [&] (size_t i) noexcept {bazook_o[i] = pact_make_f(bazook_z.store()[i] ());});

		};
		EST_("procession (processor: `ranges::move(z|...)`)")
		{
			T_alpha constexpr x_dt = re::ratio_f(7);

		//	auto bazook_o = _std::array<M_phi, bazook_n>{};

			occur::resize_t<> z_req(bazook_n);
			occur::render_t<> z_seq(bazook_n);

			bazook_z <<= occur::indent_s<W_phi, 1>(re::ratio_f(7));
			bazook_z <<= z_req;
			bazook_z >>= z_seq++;
			//\
			_v3::ranges::move(bazook_z|argue_f()|bond::pact_make_f, bazook_o.begin());
			_v3::ranges::move(bazook_z|[] (auto &&o) XTAL_0FN_(bond::pact_make_f(XTAL_REF_(o) ())), bazook_o.begin());

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
		T_alpha z_outs[2][8]{};
		auto z_out = bond::pact_bind_f<2>(8, z_outs);
	//	auto z_out = _std::array<M_phi, 8>{};

		auto z_phi = Z_phi::bind_f();
		static_assert(is_q<W_phi, decltype(z_phi.store().front())>);

		occur::resize_t<> z_req(8);
		occur::render_t<> z_seq(8);

		z_phi <<= occur::indent_s<W_phi, 1>(x_d4);
		z_phi <<= z_req;
		z_phi >>= z_seq++;
		//\
		_v3::ranges::copy(z_phi|argue_f(), z_out.begin());
		_v3::ranges::copy(z_phi|argue_f(), z_out.begin());

		TRUE_(z_out[0] == _std::pair{ 1*x_d4, x_d4});
		TRUE_(z_out[1] == _std::pair{ 2*x_d4, x_d4});
		TRUE_(z_out[2] == _std::pair{ 3*x_d4, x_d4});
		TRUE_(z_out[3] == _std::pair{ 4*x_d4, x_d4});
		TRUE_(z_out[4] == _std::pair{ 5*x_d4, x_d4});
		TRUE_(z_out[5] == _std::pair{ 6*x_d4, x_d4});
		TRUE_(z_out[6] == _std::pair{ 7*x_d4, x_d4});
		TRUE_(z_out[7] == _std::pair{-8*x_d4, x_d4});
		
		z_phi <<= occur::indent_s<W_phi, 1>(x_d3);
		z_phi >>= z_seq++;
		//\
		_v3::ranges::copy(z_phi|argue_f(), z_out.begin());
		_v3::ranges::copy(z_phi|argue_f()|bond::pact_make_f, z_out.begin());
		
		TRUE_(z_out[0] == _std::pair{-3*x_d3, x_d3});
		TRUE_(z_out[1] == _std::pair{-2*x_d3, x_d3});
		TRUE_(z_out[2] == _std::pair{-1*x_d3, x_d3});
		TRUE_(z_out[3] == _std::pair{-0*x_d3, x_d3});
		TRUE_(z_out[4] == _std::pair{ 1*x_d3, x_d3});
		TRUE_(z_out[5] == _std::pair{ 2*x_d3, x_d3});
		TRUE_(z_out[6] == _std::pair{ 3*x_d3, x_d3});
		TRUE_(z_out[7] == _std::pair{-4*x_d3, x_d3});

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
