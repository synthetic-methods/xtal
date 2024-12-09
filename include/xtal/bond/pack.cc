#pragma once
#include "./any.cc"
#include "./pack.hh"// testing...






XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("pack")
{
	TRY_("bind")
	{
		double table[2][2] = {{0, 0}, {0, 0}};
		auto column_0 = transpack_f<void_type[2]>(0, 2) (table);
		auto column_1 = transpack_f<void_type[2]>(1, 2) (table);
		column_0[0] = pack_f(1.0, 2.0);
		column_1[0] = pack_f(3.0, 4.0);
		TRUE_(1 == table[0][0]);
		TRUE_(2 == table[1][0]);
		TRUE_(3 == table[0][1]);
		TRUE_(4 == table[1][1]);

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
