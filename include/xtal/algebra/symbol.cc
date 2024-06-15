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
	using _op = bond::operating;
	using T_delta = typename _op::delta_t;
	using T_sigma = typename _op::sigma_t;
	using T_alpha = typename _op::alpha_t;
	using T_aphex = typename _op::aphex_t;


	TRY_("11th characterization (integer)")
	{
		integral_type constexpr N = 11;
		integral_type constexpr M = N  - 1;
		integral_type constexpr K = M >> 1;

		using W = symbol_t<T_delta[N]>;
		W w; w.characterize();

		TRUE_(w == W{0, 0, -1, 2, 3, 1,-4,-2,-3, 4,-5});

	}
	TRY_("11th subcharacterization (integer)")
	{
		integral_type constexpr N = 11;
		integral_type constexpr M = N  - 1;
		integral_type constexpr K = M >> 1;

		using W = symbol_t<T_delta[K]>;
		W w; w.subcharacterize();

		TRUE_(w == W{0, -1, 2, 3, 1});

	}
	TRY_("11th characterization (complex)")
	{
		integral_type constexpr N = 11;
		integral_type constexpr M = N  - 1;
		integral_type constexpr K = M >> 1;

		using W = symbol_t<T_aphex[N]>;
		W w; w.characterize();
		TRUE_(_op::explo_f(w, K).transact(bond::computrim_f<8>) == W{0, 1,-1, 1,-1,-1, 1, 1,-1, 1,-1});

		w.transact([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*K/_op::patio_1));
		w.transact(bond::computrim_f<16>);
		TRUE_(w == W{0, 0, -1, 2, 3, 1,-4,-2,-3, 4,-5});

	}

	TRY_("7th characterization (integer)")
	{
		integral_type constexpr N = 7;
		integral_type constexpr M = N  - 1;
		integral_type constexpr K = M >> 1;

		using W = symbol_t<T_delta[N]>;
		W w; w.characterize();

		TRUE_(w == W{ 0, 0, 2, 1,-2,-1,-3});

	}
	TRY_("7th subcharacterization (integer)")
	{
		integral_type constexpr N = 7;
		integral_type constexpr M = N  - 1;
		integral_type constexpr K = M >> 1;

		using W = symbol_t<T_delta[K]>;
		W w; w.subcharacterize();

		TRUE_(w == W{ 0, 2, 1});

	}
	TRY_("7th characterization (complex)")
	{
		integral_type constexpr N = 7;
		integral_type constexpr M = N  - 1;
		integral_type constexpr K = M >> 1;

		using W = symbol_t<T_aphex[N]>;
		W w; w.characterize();
		TRUE_(_op::explo_f(w, K).transact(bond::computrim_f<8>) == W{0, 1, 1,-1, 1,-1,-1});

		w.transact([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*K/_op::patio_1));
		w.transact(bond::computrim_f<16>);
		TRUE_(w == W{0, 0, 2, 1,-2,-1, -3});

	}
	TRY_("7th subcharacterization (complex)")
	{
		integral_type constexpr N = 7;
		integral_type constexpr M = N  - 1;
		integral_type constexpr K = M >> 1;

		using W = symbol_t<T_aphex[K]>;
		W w; w.subcharacterize();
		TRUE_(_op::explo_f(w, K).transact(bond::computrim_f<8>) == W{1, 1,-1});

		w.transact([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*K/_op::patio_1));
		w.transact(bond::computrim_f<16>);
		TRUE_(w == W{0, 2, 1});

	}
	TRY_("7th characterization (real)")
	{
		integral_type constexpr N = 7;
		integral_type constexpr M = N  - 1;
		integral_type constexpr K = M >> 1;

		using W = symbol_t<T_alpha[N]>;
		W w; w.characterize();
		w.transact(bond::computrim_f<16>);
		TRUE_(w == W{0, 1, 1,-1, 1,-1,-1});

	}

	TRY_("5th characterization (complex)")
	{
		integral_type constexpr N = 5;
		integral_type constexpr M = N  - 1;
		integral_type constexpr K = M >> 1;

		using W = symbol_t<T_aphex[N]>;
		W w; w.characterize();
		TRUE_(_op::explo_f(w, K).transact(bond::computrim_f<8>) == W{0, 1,-1,-1, 1});

		w.transact([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*K/_op::patio_1));
		w.transact(bond::computrim_f<16>);
		TRUE_(w == W{w[0], 0, 1,-1, w[M]});
	}
	/*/
	TRY_("5th characterization (real)")
	{
		integral_type constexpr N = 5;
		integral_type constexpr M = N  - 1;
		integral_type constexpr K = M >> 1;

		using W = symbol_t<T_alpha[N]>;
		W w; w.template characterize<2>();
		w.transact(bond::computrim_f<16>);
	//	echo(w);
	}
	/***/
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
