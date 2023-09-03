#pragma once
#include "./any.cc"
#include "./opt.ii"// testing...





XTAL_ENV_(push)
namespace xtal::message::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("opt")
{
	using aim  = opt<cardinal_t<4>, class T_aim  >;
	using hype = opt<cardinal_t<2>, class T_hype >;
	
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

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
