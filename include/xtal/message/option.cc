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
	using aim = option<cardinal_t<4>, struct __aim__>;
	using hyp = option<cardinal_t<2>, struct __hyp__>;
	
	using Aim = confined_t<aim>;
	using Hyp = confined_t<hyp>;
	using AimHyp = confined_t<aim, hyp>;
	
	TRY_("task")
	{
		auto options = AimHyp(0b1'10u);
		unsigned int value = options.value;
		TRUE_(0b10 == options.template get<aim>());
		TRUE_(0b1  == options.template get<hyp>());
		TRUE_(sizeof(AimHyp) == sizeof(Aim));
		TRUE_(sizeof(AimHyp) == sizeof(Hyp));
		TRUE_(option_q<AimHyp>);
		TRUE_(option_q<AimHyp, cardinal_t<4>, struct __aim__>);
		TRUE_(6 == AimHyp::cardinality::value);
		TRUE_(4 == Aim   ::cardinality::value);
		TRUE_(2 ==    Hyp::cardinality::value);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
