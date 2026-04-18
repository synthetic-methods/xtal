#pragma once
#include "./any.cc"
#include "./pack.hh"// testing...






XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(pack_size_v<_std::tuple<            >> == 0);
static_assert(pack_size_v<_std::array<null_type, 0>> == 0);

static_assert(pack_size_q<_std::tuple<            >>);
static_assert(pack_size_q<_std::array<null_type, 0>>);


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("pack")
{
	TRY_("bind")
	{
		double xs[2][2] = {{0, 0}, {0, 0}};
		double ys[2][2] = {{1, 3}, {2, 4}};
		auto col_0 = transpack_f<void_type[2]>(0, 2) (xs);
		auto col_1 = transpack_f<void_type[2]>(1, 2) (xs);
		col_0[0] = pack_f(1.0, 2.0);
		col_1[0] = pack_f(3.0, 4.0);
		TRUE_(xs[0][0] == ys[0][0]);
		TRUE_(xs[1][0] == ys[1][0]);
		TRUE_(xs[0][1] == ys[0][1]);
		TRUE_(xs[1][1] == ys[1][1]);

	}
	TRY_("pack_item_f(std::complex{...})")
	{
		_std::complex x{0, 1};
		TRUE_(0 == pack_item_f<0>(x));
		TRUE_(1 == pack_item_f<1>(x));

		TRUE_(0 == pack_item_f<0>(_std::complex{0, 1}));
		TRUE_(1 == pack_item_f<1>(_std::complex{0, 1}));

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
