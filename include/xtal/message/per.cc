#pragma once
#include "./any.cc"
#include "./per.ii"// testing...





XTAL_ENV_(push)
namespace xtal::message::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("per")
{
	TRY_("construction")
	{
		using T_sigma = typename atom::realized::sigma_t;
		using T_alpha = typename atom::realized::alpha_t;

		T_sigma b = atom::realized::diplo_f(16);
		T_alpha p = atom::realized::haplo_f(16);

		auto d = per_t(b);
		auto q = per_t(p);

		TRUE_(b == d.rate());
		TRUE_(b == q.rate());

		TRUE_(p == d.period());
		TRUE_(p == q.period());

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
