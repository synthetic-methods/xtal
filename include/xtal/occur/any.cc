#pragma once
#include "../any.cc"
#include "./any.hh"// testing...





XTAL_ENV_(push)
namespace xtal::occur::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::_test;


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("occur", "any")
{
	TRY_("occur flux")
	{
		TRUE_(true);

		using damping_type = occur::inferred_t<struct DAMPING, float>;
		using balance_type = occur::inferred_t<struct BALANCE, float>;

		damping_type damping{0};
		
		TRUE_(-1 == damping.influx(balance_type{2}));
		TRUE_(-1 == damping.influx(balance_type{2}, damping_type{1}));
		TRUE_( 0 == damping.head());

		TRUE_( 0 == damping.influx(damping_type{1}));
		TRUE_( 1 == damping.head());

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
