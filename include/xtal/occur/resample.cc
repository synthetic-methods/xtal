#pragma once
#include "./any.cc"
#include "./resample.hh"// testing...





XTAL_ENV_(push)
namespace xtal::occur::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("resample")
{
	TRY_("construction")
	{
		using U = double; using U_fit = bond::fit<U>;
		using V =  float; using V_fit = bond::fit<V>;

		resample_t<V> o;
		TRUE_(V_fit::diplo_f(0) == o.sample().  rate());
		TRUE_(V_fit::haplo_f(0) == o.sample().period());

		o   = resample_t<V>{(unsigned short) 16};
		TRUE_(V_fit::diplo_f(4) == o.sample().  rate());
		TRUE_(V_fit::haplo_f(4) == o.sample().period());

		o <<= resample_t<U>{(unsigned  long) 32};
		TRUE_(V_fit::diplo_f(5) == o.sample().  rate());
		TRUE_(V_fit::haplo_f(5) == o.sample().period());

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
