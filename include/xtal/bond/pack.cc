#pragma once
#include "./any.cc"

#include "../atom/all.hh"




#include "./pack.hh"
XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert(pack_size_v<std::tuple<            >> == 0);
static_assert(pack_size_v<std::array<null_type, 0>> == 0);

static_assert(pack_size_q<std::tuple<            >>);
static_assert(pack_size_q<std::array<null_type, 0>>);


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

		using U0 = float;
		using W0 = std::complex<U0>;
		using U1 = atom::bucket_t<U0[1]>;
		using U2 = atom::bucket_t<U0[2]>;
		using U3 = atom::bucket_t<U0[3]>;
		using U4 = atom::bucket_t<U0[4]>;
		using U5 = atom::bucket_t<U0[5]>;

		using Y5 = XTAL_ALL_(transpack_f<U5>(1U, XTAL_ANY_(U0 **)));
		using Y4 = XTAL_ALL_(transpack_f<U4>(1U, XTAL_ANY_(initializer_t<U4> **)));
		using Y3 = bond::transpack_t<U3>;

	}
	TRY_("pack_item_f(std::complex{...})")
	{
		std::complex x{0, 1};
		TRUE_(0 == pack_item_f<0>(x));
		TRUE_(1 == pack_item_f<1>(x));

		TRUE_(0 == pack_item_f<0>(std::complex{0, 1}));
		TRUE_(1 == pack_item_f<1>(std::complex{0, 1}));

	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
