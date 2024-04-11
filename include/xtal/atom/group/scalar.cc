#pragma once
#include "./any.cc"
#include "./scalar.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::group::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("scalar")
{
	using re = bond::realized;
	using T_delta = typename re::delta_t;
	using T_sigma = typename re::sigma_t;
	using T_alpha = typename re::alpha_t;
	using T_aphex = typename re::aphex_t;

	TRY_("construction")
	{
		auto constexpr N_size = 2;
		using W = scalar_t<T_alpha[N_size]>;

		auto foo = W{2.0, 0.5};
		auto bar = static_cast<W>(re::template root_2f<2>((T_alpha) 2));
		bar.transmorph([] XTAL_1FN_(re::square_f), bond::computrim_f<1>);
		TRUE_(foo == bar);

		foo *= {(T_alpha) 0.0, (T_alpha) 0.0};

	}
	TRY_("inflection")
	{
		auto constexpr N_size = 2;
		using W = scalar_t<T_alpha[N_size]>;

		auto bar = W{2.0, 0.5};
		auto foo = bar.inflected(-1);
		auto baz = foo.inflected(+1);
		
		TRUE_(bond::computrim_f<19>(foo[0]) == 1.25);
		TRUE_(bond::computrim_f<19>(foo[1]) == 0.75);
		TRUE_(bond::computrim_f<19>(baz[0]) == bar[0]);
		TRUE_(bond::computrim_f<19>(baz[1]) == bar[1]);

	}
	TRY_("7th characterization (integer)")
	{
		auto constexpr N_size = 7;
		auto constexpr M_size = N_size  - 1;
		auto constexpr K      = N_size >> 1;

		using W = scalar_t<T_delta[N_size]>;
		W w; w.characterize();

		TRUE_(w == W{ 0, 0, 2, 1,-2,-1, 3});

	}
	TRY_("7th characterization (complex)")
	{
		auto constexpr N_size = 7;
		auto constexpr M_size = N_size  - 1;
		auto constexpr K      = N_size >> 1;

		using W = scalar_t<T_aphex[N_size]>;
		W w; w.characterize();
		TRUE_(re::explo_f(w, K).transmorph(bond::computrim_f<8>) == W{0, 1, 1,-1, 1,-1,-1});

		w.transmorph([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*M_size/re::patio_f(2, 1)));
		w.transmorph(bond::computrim_f<16>);
		TRUE_(w == W{w[0], 0, 2, 1,-2,-1, w[M_size]});

	}
	TRY_("5th characterization (complex)")
	{
		auto constexpr N_size = 5;
		auto constexpr M_size = N_size  - 1;
		auto constexpr K      = N_size >> 1;

		using W = scalar_t<T_aphex[N_size]>;
		W w; w.characterize();
		TRUE_(re::explo_f(w, K).transmorph(bond::computrim_f<8>) == W{0, 1,-1,-1, 1});

		w.transmorph([] (auto &&z) XTAL_0FN_(_std::arg(XTAL_REF_(z))*M_size/re::patio_f(2, 1)));
		w.transmorph(bond::computrim_f<16>);
		TRUE_(w == W{w[0], 0, 1,-1, w[M_size]});

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
