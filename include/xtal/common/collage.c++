#pragma once
#include "./any.c++"
#include "./collage.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::common::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("collage", "quasar")
{
	TRY_("construction by supervalue")
	{
		using alpha_t = typename realized::alpha_t;
		using delta_t = typename realized::delta_t;

		using quasar_u = typename collage_t<1>::template quasar_t<alpha_t>;
		using quasar_t = typename collage_t<2>::template quasar_t<alpha_t>;
		
		quasar_t q0(1.125);
		++q0;
		++q0;
		++q0;
		TRUE_(alpha_t(q0) == 0.125);
		TRUE_(q0.phase(0) == 0.125);
		TRUE_(q0.phase(1) == 0.0);
		TRUE_(q0.pulse(0) == 0.0);
		TRUE_(q0.pulse(1) == 0.0);

	}
	TRY_("construction by subsequence")
	{
		using alpha_t = typename realized::alpha_t;
		using delta_t = typename realized::delta_t;

		using quasar_u = typename collage_t<1>::template quasar_t<alpha_t>;
		using quasar_t = typename collage_t<2>::template quasar_t<alpha_t>;
		
		quasar_u q1{0.375};
		quasar_t q0(q1);
		++q0;
		++q0;
		++q0;
		TRUE_(alpha_t(q0) == 0.125);
		TRUE_(q0.phase(0) == 0.125);
		TRUE_(q0.phase(1) == 0.375);
		TRUE_(q0.pulse(0) == 0.0);
		TRUE_(q0.pulse(1) == 0.0);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
