#pragma once
#include "./any.cc"
#include "./couple.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(bond::array_tag_p<couple_t, couple_t<int[2]>, int[2]>);
static_assert(couple_q<couple_t<int[2]>>);
static_assert(couple_q<couple_t<int[2]>, int[2]>);

static_assert(complete_q<couple_t<float, double>>);

static_assert(atomic_q<couple_t<float[2]>>);

static_assert(fungible_q<_std::array<float, 2>,
	XTAL_ALL_(XTAL_ANY_(couple_t<float(&)[2]>)*XTAL_ANY_(couple_t<float(&)[2]>))>
);


////////////////////////////////////////////////////////////////////////////////

TAG_("couple")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	EST_("couple reinitialization")
	{
		couple_t<T_aphex[4]> foo{};

		for (int i{0}; i < 0x100; ++i) {
			foo *= T_alpha{};
			foo.blanket();
		}
		return foo;
	};
	TRY_("couple reinitialization")
	{
		using W_aphex = couple_t<T_aphex[2]>;

		auto constexpr N_size = 2;
		W_aphex foo{};

		foo *= T_alpha{};
		TRUE_(foo == W_aphex{{0}, {0}}); TRUE_(foo.blanket() == 1);
		TRUE_(foo == W_aphex{{1}, {1}}); TRUE_(foo.blanket() == 0);

	}
	TRY_("couple production (multiplicative)")
	{
		using W =  couple_t<T_aphex, T_alpha>;
		auto  x =  W{2, 3};
		auto  y =  W{4, 9};
		auto  z =  y*x;
		TRUE_(z == W{8, 27});

	}
	TRY_("couple production (divisive)")
	{
		using W =  couple_t<T_aphex, T_alpha>;
		auto  x =  W{2, 3};
		auto  y =  W{4, 9};
		auto  z =  y/x;

		TRUE_(z == W{2, 3});
	//	TRUE_(x == x/T_alpha{1});
	}
	TRY_("couple summation")
	{
		auto constexpr N_size = 3;
		using W = couple_t<T_alpha[N_size]>;
		auto  w = W{2.0, 1.0, 0.5};

		TRUE_(3.5 == w.sum());
		TRUE_(1.5 == w.template sum<-1>());

	}
	TRY_("couple reflection")
	{
		auto constexpr N_size = 2;
		using W = couple_t<T_alpha[N_size]>;

		auto bar = W{2.0, 0.5};
		auto foo = bar.template reflected<-1>();
		auto baz = foo.template reflected<+1>();
		
		TRUE_(check_f<19>(foo[0], 1.25));
		TRUE_(check_f<19>(foo[1], 0.75));
		TRUE_(check_f<19>(baz[0], bar[0]));
		TRUE_(check_f<19>(baz[1], bar[1]));

	}
	TRY_("couple refactoring")
	{
		using U0 = T_sigma;
		using U1 = couple_t<U0[1]>;
		using U2 = couple_t<U0[2]>;
		using U3 = couple_t<U0[3]>;
		using U4 = couple_t<U0[4]>;

	//	TRUE_(U4{2, 12, 6, 2}.extremal() == U2{2, 12});


		U4 const xs_expected { 1,  2,  1,  2};
		U4 const xs_provided { 2, 12,  6,  2};
		
		auto const xs_extents = xs_provided/xs_expected;
		auto const ys_extent  = xs_extents.maximum();
		
		U3 const ys_expected { 2,  1,  2};
		U3 const ys_provided = ys_expected*ys_extent;

		TRUE_(xs_extents == U4{2, 6, 6, 1});
		TRUE_(ys_extent   == 6);
		
		TRUE_(xs_provided.sum() == 22);
		TRUE_(ys_provided.sum() == 30);

	}
	/*/
	TRY_("referencing")
	{
		auto constexpr N = (size_type) 4;
		float foo[2][N] {{1, 2, 3, 4}, {5, 6, 7, 8}};

		using simplex_val = couple_t<float   [N]>;
		using simplex_ref = couple_t<float(&)[N]>;
		
		using complex_val = _std::complex<simplex_val>;
		using complex_ref = _std::complex<simplex_ref>;
		
		simplex_ref bar_re{_std::span(foo[0], 4)};
		simplex_ref bar_im{_std::span(foo[1], 4)};
		complex_ref bar{bar_re, bar_im};
	//	complex_ref bar{_std::span(foo[0], 4), _std::span(foo[1], 4)};// NOPE!

		simplex_val &baz_re = reinterpret_cast<simplex_val &>(foo[0]);
		simplex_val &baz_im = reinterpret_cast<simplex_val &>(foo[1]);
		complex_val &baz    = reinterpret_cast<complex_val &>(foo   );

	}
	/***/
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
