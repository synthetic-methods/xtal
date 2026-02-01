#pragma once
#include "./any.cc"
#include "./couple.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(bond::tag_in_p<couple_t, couple_t<int[2]>>);
static_assert(bond::tag_infixed_p<couple_t, couple_t<int[2]>>);
static_assert(bond::tag_infixed_p<couple_t, couple_t<int[2]>, int[2]>);
static_assert(couple_q<couple_t<int[2]>, int[2]>);

static_assert(complete_q<couple_t<float, double>>);

//atic_assert(atomic_q<couple_t<float[2]>>);

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


	TRY_("couple typing")
	{
		using U = unsigned;
		using V =   signed;

		using U0 = couple_t<U[0] >; using _U0 = brace_t<U[0] >;
		using V0 = couple_t<V[0] >; using _V0 = brace_t<V[0] >;
		using U1 = couple_t<U[1] >; using _U1 = brace_t<U[1] >;
		using V1 = couple_t<V[1] >; using _V1 = brace_t<V[1] >;
		using U2 = couple_t<U[2] >; using _U2 = brace_t<U[2] >;
		using V2 = couple_t<V[2] >; using _V2 = brace_t<V[2] >;
		using UV = couple_t<U, V>; using _UV = brace_t<U, V>;
		using VU = couple_t<V, U>; using _VU = brace_t<V, U>;

		static_assert(    bond::tab_comparable_q< V1,  V1>);// `    ==` (shallow)
		static_assert(not bond::tab_comparable_q< V1, _V1>);// `not ==` (shallow)
		static_assert(    bond::tab_compatible_q< V1,  V1>);// `    ==`
		static_assert(not bond::tab_compatible_q< V1, _V1>);// `not ==`
		
		static_assert(    bond::tab_precedence_p< V1, _V1>);// `    <=`
		static_assert(not bond::tab_preference_p< V1,  V1>);// `    < `
		static_assert(not bond::tab_precedence_p<_V1,  V1>);// `not <=`
		static_assert(not bond::tab_preference_p<_V1,  V1>);// `not < `

		U0 u0{}; V0 v0{};
		U1 u1{}; V1 v1{};
		U2 u2{}; V2 v2{};
		UV uv{}; VU vu{};

		TRUE_(v1.size() == v1.twin().size());
		TRUE_(v1.size() == (1234*v1).size());
		TRUE_(v1.size() == (v1*1234).size());

	};
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
	TRY_("couple flipping")
	{
		using W_alpha = couple_t<T_alpha[2]>;

		auto constexpr N_size = 2;
		W_alpha foo{1, 2};
		W_alpha bar{2, 1};

		TRUE_(foo == foo.flipped(T_alpha{ 1}));
		TRUE_(bar == foo.flipped(T_alpha{-1}));

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
	TRY_("couple progressive sum/difference")
	{
		using W = couple_t<T_alpha[4]>;
		W const w{2, 3, 5, 7};

		TRUE_(++w == W{ 2,  5, 10, 17});
		TRUE_(w++ == W{ 0,  2,  5, 10});

		TRUE_(w == (--(++w)));
		TRUE_(w == ((w++)--));

	}
	TRY_("couple reflection")
	{
		auto constexpr N_size = 2;
		using W = couple_t<T_alpha[N_size]>;

		auto bar = W{2.0, 0.5};
		auto foo = bar.reflection();
		
		TRUE_(get<0>(foo) == bar.template reflection<+1>());
		TRUE_(get<1>(foo) == bar.template reflection<-1>());
		TRUE_(get<0>(foo) == 2.5);
		TRUE_(get<1>(foo) == 1.5);

	}
	TRY_("couple refactoring")
	{
		using U = T_sigma;
		using U1 = couple_t<U[1]>;
		using U2 = couple_t<U[2]>;
		using U3 = couple_t<U[3]>;
		using U4 = couple_t<U[4]>;

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
