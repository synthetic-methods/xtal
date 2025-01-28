#pragma once
#include "./any.cc"
#include "./group.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(atomic_q<group_t<_std::plus<float>[2]>>);
static_assert(atomic_q<group_t<_std::plus<void>, float[2]>>);


////////////////////////////////////////////////////////////////////////////////

TAG_("atom", "group")
{
	using F = _std::plus<void>;

	using _fix = bond::fixture<>;
	using T_delta = typename _fix::delta_type;
	using T_sigma = typename _fix::sigma_type;
	using T_alpha = typename _fix::alpha_type;
	using T_aphex = typename _fix::aphex_type;

	using A1 = group_t<_std::plus<int>[1]>;
	using A2 = group_t<_std::plus<int>[2]>;
	using A3 = group_t<_std::plus<int>[3]>;
	using A4 = group_t<_std::plus<int>[4]>;
	
	using M1 = group_t<_std::multiplies<int>[1]>;
	using M2 = group_t<_std::multiplies<int>[2]>;
	using M3 = group_t<_std::multiplies<int>[3]>;
	using M4 = group_t<_std::multiplies<int>[4]>;
	
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

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
