#pragma once
#include "./any.cc"
#include "./quantity.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("atom", "quantity")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	using A1 = quantity_plus_t<int[1]>;
	using A2 = quantity_plus_t<int[2]>;
	using A3 = quantity_plus_t<int[3]>;
	using A4 = quantity_plus_t<int[4]>;
	
	using M1 = quantity_multiplies_t<int[1]>;
	using M2 = quantity_multiplies_t<int[2]>;
	using M3 = quantity_multiplies_t<int[3]>;
	using M4 = quantity_multiplies_t<int[4]>;
	
	using Z1 = quantity_plus_multiplies_t<int[1]>;
	using Z2 = quantity_plus_multiplies_t<int[2]>;
	using Z3 = quantity_plus_multiplies_t<int[3]>;
	using Z4 = quantity_plus_multiplies_t<int[4]>;
	
	TRY_("partial construction")
	{
		A4 d4{1000};

		TRUE_(d4 == A4{1000, 0, 0, 0});

	}
	TRY_("quantity addition")
	{
		A2 d2_0{2, 2};
		A2 d2_1{5, 7};

		TRUE_(d2_0+d2_1 == A2{ 7,  9});
		d2_0 += d2_1;
		TRUE_(d2_0      == A2{ 7,  9});

	}
	TRY_("quantity multiplication")
	{
		M2 d2_0{2, 2};
		M2 d2_1{5, 7};

		TRUE_(d2_0*d2_1 == M2{10, 14});
		d2_0 *= d2_1;
		TRUE_(d2_0      == M2{10, 14});

		using W =  quantity_multiplies_t<T_aphex, T_alpha>;
		auto  x =  W{2, 3};
		auto  y =  W{4, 9};
		auto  z =  y*T_alpha{3};
		TRUE_(z == W{12, 27});

	}
	TRY_("quantity multiplication and addition")
	{
		Z2 d2_0{2, 2};
		Z2 d2_1{5, 7};

		TRUE_(d2_0*d2_1 == Z2{10, 14});
		d2_0 *= d2_1;
		TRUE_(d2_0      == Z2{10, 14});

		using W =  quantity_plus_multiplies_t<T_aphex, T_alpha>;
		auto  x =  W{2, 3};
		auto  y =  W{4, 9};
		auto  z =  y*T_alpha{3};
		TRUE_(z == W{12, 27});

		auto  zoo = d2_0.twin(+one);
		using Zoo = decltype(zoo);
		TRUE_(Zoo::size() == 3);
		TRUE_(quantity_plus_multiplies_q<Zoo>);
		TRUE_(same_q<Zoo, Z3>);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
