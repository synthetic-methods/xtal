#pragma once
#include "./any.cc"
#include "./symbol.hh"// testing...





XTAL_ENV_(push)
namespace xtal::algebra::_test
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


	TRY_("11th characterization (integer)")
	{
		size_s constexpr N = 11;
		size_s constexpr M = N  - 1;
		size_s constexpr K = M >> 1;

		using W = symbol_t<T_delta[N]>;
		W w; w.characterize();

		TRUE_(w == W{0, 0, -1, 2, 3, 1,-4,-2,-3, 4,-5});

	}
	TRY_("11th subcharacterization (integer)")
	{
		size_s constexpr N = 11;
		size_s constexpr M = N  - 1;
		size_s constexpr K = M >> 1;

		using W = symbol_t<T_delta[K]>;
		W w; w.subcharacterize();

		TRUE_(w == W{0, -1, 2, 3, 1});

	}
	TRY_("11th characterization (complex)")
	{
		size_s constexpr N = 11;
		size_s constexpr M = N  - 1;
		size_s constexpr K = M >> 1;

		using W = symbol_t<T_aphex[N]>;
		W w; w.characterize();
		TRUE_(re::explo_f(w, K).transmorph(bond::computrim_f<8>) == W{0, 1,-1, 1,-1,-1, 1, 1,-1, 1,-1});

		w.transmorph([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*K/re::patio_1));
		w.transmorph(bond::computrim_f<16>);
		TRUE_(w == W{0, 0, -1, 2, 3, 1,-4,-2,-3, 4,-5});

	}

	TRY_("7th characterization (integer)")
	{
		size_s constexpr N = 7;
		size_s constexpr M = N  - 1;
		size_s constexpr K = M >> 1;

		using W = symbol_t<T_delta[N]>;
		W w; w.characterize();

		TRUE_(w == W{ 0, 0, 2, 1,-2,-1,-3});

	}
	TRY_("7th subcharacterization (integer)")
	{
		size_s constexpr N = 7;
		size_s constexpr M = N  - 1;
		size_s constexpr K = M >> 1;

		using W = symbol_t<T_delta[K]>;
		W w; w.subcharacterize();

		TRUE_(w == W{ 0, 2, 1});

	}
	TRY_("7th characterization (complex)")
	{
		size_s constexpr N = 7;
		size_s constexpr M = N  - 1;
		size_s constexpr K = M >> 1;

		using W = symbol_t<T_aphex[N]>;
		W w; w.characterize();
		TRUE_(re::explo_f(w, K).transmorph(bond::computrim_f<8>) == W{0, 1, 1,-1, 1,-1,-1});

		w.transmorph([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*K/re::patio_1));
		w.transmorph(bond::computrim_f<16>);
		TRUE_(w == W{0, 0, 2, 1,-2,-1, -3});

	}
	TRY_("7th subcharacterization (complex)")
	{
		size_s constexpr N = 7;
		size_s constexpr M = N  - 1;
		size_s constexpr K = M >> 1;

		using W = symbol_t<T_aphex[K]>;
		W w; w.subcharacterize();
		TRUE_(re::explo_f(w, K).transmorph(bond::computrim_f<8>) == W{1, 1,-1});

		w.transmorph([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*K/re::patio_1));
		w.transmorph(bond::computrim_f<16>);
		TRUE_(w == W{0, 2, 1});

	}
	TRY_("7th characterization (real)")
	{
		size_s constexpr N = 7;
		size_s constexpr M = N  - 1;
		size_s constexpr K = M >> 1;

		using W = symbol_t<T_alpha[N]>;
		W w; w.characterize();
		w.transmorph(bond::computrim_f<16>);
		TRUE_(w == W{0, 1, 1,-1, 1,-1,-1});

	}

	TRY_("5th characterization (complex)")
	{
		size_s constexpr N = 5;
		size_s constexpr M = N  - 1;
		size_s constexpr K = M >> 1;

		using W = symbol_t<T_aphex[N]>;
		W w; w.characterize();
		TRUE_(re::explo_f(w, K).transmorph(bond::computrim_f<8>) == W{0, 1,-1,-1, 1});

		w.transmorph([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*K/re::patio_1));
		w.transmorph(bond::computrim_f<16>);
		TRUE_(w == W{w[0], 0, 1,-1, w[M]});
	}
	/*/
	TRY_("5th characterization (real)")
	{
		size_s constexpr N = 5;
		size_s constexpr M = N  - 1;
		size_s constexpr K = M >> 1;

		using W = symbol_t<T_alpha[N]>;
		W w; w.template characterize<2>();
		w.transmorph(bond::computrim_f<16>);
		echo(w);
	}
	/***/
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
