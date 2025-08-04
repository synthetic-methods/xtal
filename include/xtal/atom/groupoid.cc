#pragma once
#include "./any.cc"
#include "./groupoid.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//atic_assert(atomic_q<groupoid_t<float[2]>>);

static_assert(same_q<groupoid_t<int[1]>, decltype(groupoid_t<int[1]>{}*2)>);
static_assert(same_q<groupoid_t<int[1]>, decltype(2*groupoid_t<int[1]>{})>);

static_assert(1 == (groupoid_t<int[1]>{}*2).size());
static_assert(1 == (2*groupoid_t<int[1]>{}).size());

static_assert(not counted_q<groupoid_t<        int[2]>>);
static_assert(not counted_q<groupoid_t<counter_t<>[2]>>);
static_assert(not counted_q<groupoid_t<  size_type[2]>>);


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("groupoid")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	TRY_("groupoid map-from")
	{
		using U2_alpha = groupoid_t<T_alpha[2]>;
		using U2_aphex = groupoid_t<T_aphex[2]>;
		U2_alpha x{1, 2};
		U2_alpha y{2, 3};

		auto x_y = U2_alpha::template zip_from<[] (auto u, auto v) XTAL_0FN_(to) (u + v)>(x, y);
		TRUE_(x_y == U2_alpha{3, 5});

	}
	TRY_("groupoid scalar-division")
	{
		using U2_alpha = groupoid_t<T_alpha[2]>;
		using U2_aphex = groupoid_t<T_aphex[2]>;
		U2_alpha x{1, 2}, y = T_alpha{1.0}/x;
		TRUE_(y == U2_alpha{1.0, 0.5});
		y /= T_alpha{0.5};
		TRUE_(y == U2_alpha{2.0, 1.0});

	}
	TRY_("groupoid scalar-multiplication")
	{
		using U2_alpha = groupoid_t<T_alpha[2]>;
		using U2_aphex = groupoid_t<T_aphex[2]>;
		U2_alpha x{1, 2}; x *= (T_alpha) 10;
		U2_aphex y{1, 2}; y *= (T_alpha) 10;

		TRUE_(x <  U2_alpha{20, 40});
		TRUE_(x == U2_alpha{10, 20});
		TRUE_(y == U2_aphex{10, 20});

	}
	TRY_("groupoid comparison")
	{
		using U2_alpha = groupoid_t<T_alpha[2]>;

		TRUE_(U2_alpha{1, 1} == U2_alpha{1, 1});
		TRUE_(U2_alpha{0, 1} <  U2_alpha{1, 1});
		TRUE_(U2_alpha{1, 0} <  U2_alpha{1, 1});
		TRUE_(U2_alpha{1, 1} >  U2_alpha{0, 1});
		TRUE_(U2_alpha{1, 1} >  U2_alpha{1, 0});

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("pack")
{
	TRY_("pack_item_f({...std::complex{...}})")
	{
		using U_nested = groupoid_t<groupoid_t<_std::complex<float>[2]>[2]>;
		U_nested etc{{{00, 01}, {02, 03}}, {{04, 05}, {06, 07}}};
		TRUE_(pack_item_f<1, 1, 1>(etc) == etc[1][1].imag());

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
