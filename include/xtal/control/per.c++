#pragma once
#include "./any.c++"
#include "./per.ipp"// testing...





XTAL_ENV_(push)
namespace xtal::control::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("per")
{
	TRY_("construction")
	{
		using sigma_t = typename computer::sigma_t;
		using alpha_t = typename computer::alpha_t;

		sigma_t b = computer::diplo_f(16);
		alpha_t p = computer::haplo_f(16);

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
