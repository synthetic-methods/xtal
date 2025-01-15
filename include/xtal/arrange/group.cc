#pragma once
#include "./any.cc"
#include "./group.hh"// testing...





XTAL_ENV_(push)
namespace xtal::arrange::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("arrange", "group")
{
	using F = _std::plus<void>;

	using _op = bond::operate<>;
	using T_delta = typename _op::delta_type;
	using T_sigma = typename _op::sigma_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;

	using D1 = group_t<int[1]>;
	using D2 = group_t<int[2]>;
	using D3 = group_t<int[3]>;
	using D4 = group_t<int[4]>;
	
	TRY_("partial construction")
	{
		D4 d4{1000};

		TRUE_(d4 == D4{1000, 0, 0, 0});

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
