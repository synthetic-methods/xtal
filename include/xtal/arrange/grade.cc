#pragma once
#include "./any.cc"
#include "./grade.hh"// testing...





XTAL_ENV_(push)
namespace xtal::arrange::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("arrange", "grade")
{
	using _fix = bond::fixture<>;
	using T_delta = typename _fix::delta_type;
	using T_sigma = typename _fix::sigma_type;
	using T_alpha = typename _fix::alpha_type;
	using T_aphex = typename _fix::aphex_type;

	using D1 = grade_t<int[1]>;
	using D2 = grade_t<int[2]>;
	using D3 = grade_t<int[3]>;
	using D4 = grade_t<int[4]>;
	
	TRY_("partial construction")
	{
		D4 d4{1000};

		TRUE_(d4 == D4{1000, 0, 0, 0});

	}
	TRY_("integration")
	{
		D4 d4{1000, 100, 10, 1};

		TRUE_(++d4 == D4{1100, 110, 11, 1});
		TRUE_(++d4 == D4{1210, 121, 12, 1});
		TRUE_(++d4 == D4{1331, 133, 13, 1});
		TRUE_(--d4 == D4{1210, 121, 12, 1});
		TRUE_(--d4 == D4{1100, 110, 11, 1});

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
