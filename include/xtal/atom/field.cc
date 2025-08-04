#pragma once
#include "./any.cc"
#include "./field.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("atom", "field")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	using F1 = field_t<_xtd::plus_multiplies<int>[1]>;
	using F2 = field_t<_xtd::plus_multiplies<int>[2]>;
	using F3 = field_t<_xtd::plus_multiplies<int>[3]>;
	using F4 = field_t<_xtd::plus_multiplies<int>[4]>;
	
	TRY_("partial construction")
	{
		F4 d4{1000};

		TRUE_(d4 == F4{1000, 0, 0, 0});

	}
	TRY_("field addition")
	{
		F2 d2_0{2, 2};
		F2 d2_1{5, 7};

		TRUE_(d2_0+d2_1 == F2{ 7,  9});
		d2_0 += d2_1;
		TRUE_(d2_0      == F2{ 7,  9});

	}
	TRY_("field multiplication")
	{
		F2 d2_0{2, 2};
		F2 d2_1{5, 7};

		TRUE_(d2_0*d2_1 == F2{10, 14});
		d2_0 *= d2_1;
		TRUE_(d2_0      == F2{10, 14});

		using W =  field_arithmetic_t<T_aphex, T_alpha>;
		auto  x =  W{2, 3};
		auto  y =  W{4, 9};
		auto  z =  y*T_alpha{3};
		TRUE_(z == W{12, 27});

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
