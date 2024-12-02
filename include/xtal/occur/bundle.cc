#pragma once
#include "./any.cc"
#include "./bundle.hh"// testing...





XTAL_ENV_(push)
namespace xtal::occur::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("bundle")
{
	TRY_("usage")
	{
		using W = bundle_t<int, int, int>;
		W w{1, 2, 3};
		auto m = bundle_f(1, 2, 3);
		using M = XTAL_ALL_(m);
		TRUE_(is_q<W, M>);

		w += m;
		m *= 2;
		TRUE_(w == m);

		w += w;
		m  = 2*m;
		TRUE_(w == m);

		w += w;
		TRUE_(w == m + m);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
