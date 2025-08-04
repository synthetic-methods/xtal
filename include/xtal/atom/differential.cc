#pragma once
#include "./any.cc"
#include "./differential.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//atic_assert(atomic_q<differential_t<float[2]>>);


////////////////////////////////////////////////////////////////////////////////

TAG_("atom", "differential")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	using D1 = differential_t<int[1]>;
	using D2 = differential_t<int[2]>;
	using D3 = differential_t<int[3]>;
	using D4 = differential_t<int[4]>;
	
	TRY_("differential construction")
	{
		D4 d4{1000};

		TRUE_(d4 == D4{1000, 0, 0, 0});

	}
	TRY_("differential integration")
	{
		D4 d4{1000, 100, 10, 1};

		TRUE_(++d4 == D4{1100, 110, 11, 1});
		TRUE_(++d4 == D4{1210, 121, 12, 1});
		TRUE_(++d4 == D4{1331, 133, 13, 1});
		TRUE_(--d4 == D4{1210, 121, 12, 1});
		TRUE_(--d4 == D4{1100, 110, 11, 1});

	}
	TRY_("differential addition")
	{
		D2 d2_0{2, 2};
		D2 d2_1{5, 7};

		TRUE_(d2_0+d2_1 == D2{ 7,  9});
		d2_0 += d2_1;
		TRUE_(d2_0      == D2{ 7,  9});

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
