#pragma once
#include "./any.cc"
#include "./operate.hh"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(constant_q<operate_t<[] XTAL_1FN_(to) (1)>>);
static_assert(constant_q<decltype(operate{[] XTAL_1FN_(to) (1)})>);

static_assert(same_q<operate<>, operate<>>);
static_assert(same_q<operate<>, decltype(operate<>{})>);


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("operate")
{
	using T_alpha = typename fit<>::alpha_type;
	using T_sigma = typename fit<>::sigma_type;
	using T_delta = typename fit<>::delta_type;

	TRY_("operate floating-point shift")
	{
		TRUE_(one == (one << 2.0)/4.0000000000000000);
		TRUE_(one == (one << 1.5)/2.8284271247461903);
		TRUE_(one == (one << 1.0)/2.0000000000000000);
		TRUE_(one == (one << 0.5)/1.4142135623730951);
		TRUE_(one == (one << 0.0)/1.0000000000000000);
		TRUE_(one == (one >> 0.0)/1.0000000000000000);
		TRUE_(one == (one >> 0.5)/0.7071067811865476);
		TRUE_(one == (one >> 1.0)/0.5000000000000000);
		TRUE_(one == (one >> 1.5)/0.3535533905932738);
		TRUE_(one == (one >> 2.0)/0.2500000000000000);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
