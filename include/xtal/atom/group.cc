#pragma once
#include "./any.cc"
#include "./group.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("atom", "group")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	using A1 = group_addition_t<int[1]>;
	using A2 = group_addition_t<int[2]>;
	using A3 = group_addition_t<int[3]>;
	using A4 = group_addition_t<int[4]>;
	
	using M1 = group_multiplication_t<int[1]>;
	using M2 = group_multiplication_t<int[2]>;
	using M3 = group_multiplication_t<int[3]>;
	using M4 = group_multiplication_t<int[4]>;
	
	TRY_("partial construction")
	{
		A4 d4{1000};

		TRUE_(d4 == A4{1000, 0, 0, 0});

	}
	TRY_("group addition")
	{
		A2 d2_0{2, 2};
		A2 d2_1{5, 7};

		TRUE_(d2_0+d2_1 == A2{ 7,  9});
		d2_0 += d2_1;
		TRUE_(d2_0      == A2{ 7,  9});

	}
	TRY_("group multiplication")
	{
		M2 d2_0{2, 2};
		M2 d2_1{5, 7};

		TRUE_(d2_0*d2_1 == M2{10, 14});
		d2_0 *= d2_1;
		TRUE_(d2_0      == M2{10, 14});

		using W =  group_multiplication_t<T_aphex, T_alpha>;
		auto  x =  W{2, 3};
		auto  y =  W{4, 9};
		auto  z =  y*T_alpha{3};
		TRUE_(z == W{12, 27});

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
