#pragma once
#include "./any.cc"
#include "./render.hh"// testing...





XTAL_ENV_(push)
namespace xtal::occur::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("render")
{
	TRY_("construction")
	{
		using U = double; using U_fit = bond::fit<U>;
		using V =  float; using V_fit = bond::fit<V>;

		render_t<V> o;
		TRUE_(V_fit::diplo_f(00) == o.  rate());
		TRUE_(V_fit::haplo_f(00) == o.period());

		o   = render_t<V>{(unsigned short) 16};
		TRUE_(V_fit::diplo_f(4) == o.  rate());
		TRUE_(V_fit::haplo_f(4) == o.period());

		o <<= render_t<U>{(unsigned  long) 32};
		TRUE_(V_fit::diplo_f(5) == o.  rate());
		TRUE_(V_fit::haplo_f(5) == o.period());

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
