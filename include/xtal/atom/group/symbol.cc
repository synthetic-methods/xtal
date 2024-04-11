#pragma once
#include "./any.cc"
#include "./symbol.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::group::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("symbol")
{
	using re = bond::realized;
	using T_delta = typename re::delta_t;
	using T_sigma = typename re::sigma_t;
	using T_alpha = typename re::alpha_t;
	using T_aphex = typename re::aphex_t;

	TRY_("7th characterization (integer)")
	{
		auto constexpr N_size = 7;
		auto constexpr M_size = N_size  - 1;
		auto constexpr K      = M_size >> 1;

		using W = symbol_t<T_delta[N_size]>;
		W w; w.characterize();

		TRUE_(w == W{ 0, 0, 2, 1,-2,-1, 3});

	}
	TRY_("7th characterization (complex)")
	{
		auto constexpr N_size = 7;
		auto constexpr M_size = N_size  - 1;
		auto constexpr K      = M_size >> 1;

		using W = symbol_t<T_aphex[N_size]>;
		W w; w.characterize();
		TRUE_(re::explo_f(w, K).transmorph(bond::computrim_f<8>) == W{0, 1, 1,-1, 1,-1,-1});

		w.transmorph([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*M_size/re::patio_f(2, 1)));
		w.transmorph(bond::computrim_f<16>);
		TRUE_(w == W{w[0], 0, 2, 1,-2,-1, w[M_size]});

	}
	TRY_("7th characterization (real)")
	{
		auto constexpr N_size = 7;
		auto constexpr M_size = N_size  - 1;
		auto constexpr K      = M_size >> 1;

		using W = symbol_t<T_alpha[N_size]>;
		W w; w.characterize();
		w.transmorph(bond::computrim_f<16>);
		TRUE_(w == W{0, 1, 1,-1, 1,-1,-1});

	}

	TRY_("5th characterization (complex)")
	{
		auto constexpr N_size = 5;
		auto constexpr M_size = N_size  - 1;
		auto constexpr K      = M_size >> 1;

		using W = symbol_t<T_aphex[N_size]>;
		W w; w.characterize();
		TRUE_(re::explo_f(w, K).transmorph(bond::computrim_f<8>) == W{0, 1,-1,-1, 1});

		w.transmorph([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*M_size/re::patio_f(2, 1)));
		w.transmorph(bond::computrim_f<16>);
		TRUE_(w == W{w[0], 0, 1,-1, w[M_size]});

	}
	/*/
	TRY_("5th characterization (real)")
	{
		auto constexpr N_size = 5;
		auto constexpr M_size = N_size  - 1;
		auto constexpr K      = M_size >> 1;

		using W = symbol_t<T_alpha[N_size]>;
		W w; w.template characterize<2>();
		w.transmorph(bond::computrim_f<16>);
		echo(w);
	}
	/***/
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
