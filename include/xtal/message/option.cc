#pragma once
#include "./any.cc"
#include "./option.ii"// testing...





XTAL_ENV_(push)
namespace xtal::message::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("option")
{
	using aim  = option<cardinal_t<4>, class T_aim  >;
	using hype = option<cardinal_t<2>, class T_hype >;
	
	using Aim  = confined_t<aim  >;
	using Hype = confined_t<hype >;
	using AimHype = confined_t<aim, hype>;
	
	TRY_("task")
	{
		auto options = AimHype(0b1'10u);
		unsigned int value = options.value;
		TRUE_(0b10 == options.template get<aim  >());
		TRUE_(0b1  == options.template get<hype >());
		TRUE_(sizeof(Aim) == sizeof(AimHype));
		TRUE_(option_q<AimHype>);
		TRUE_(option_q<AimHype, cardinal_t<4>, class T_aim>);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
