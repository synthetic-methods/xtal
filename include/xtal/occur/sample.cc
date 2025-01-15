#pragma once
#include "./any.cc"
#include "./sample.hh"// testing...





XTAL_ENV_(push)
namespace xtal::occur::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("sample")
{
	TRY_("construction")
	{
		using U = double; using U_op = bond::operate<U>;
		using V =  float; using V_op = bond::operate<V>;

		sample_t<V> o;
		TRUE_(V_op::diplo_f(00) == o.  rate());
		TRUE_(V_op::haplo_f(00) == o.period());

		o   = sample_t<V>{(unsigned short) 16};
		TRUE_(V_op::diplo_f(4) == o.  rate());
		TRUE_(V_op::haplo_f(4) == o.period());

		o <<= sample_t<U>{(unsigned  long) 32};
		TRUE_(V_op::diplo_f(5) == o.  rate());
		TRUE_(V_op::haplo_f(5) == o.period());

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
