#pragma once
#include "./any.cc"
#include "./store.ii"// testing...





XTAL_ENV_(push)
namespace xtal::common::fluid::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("store")
{
	TRY_("assignment")
	{
		using sigma_t = typename common::computer::sigma_t;
		using alpha_t = typename common::computer::alpha_t;

		using store_u = store_t<alpha_t[128]>;
		using vector_u = _std::vector<alpha_t>;

		auto const zhs = store_u {7, 8, 9};
		auto       yhs = store_u {4, 5, 6};
		auto       xhs = store_u {1, 2, 3};
		TRUE_(equal_f(xhs, vector_u {1, 2, 3}));
		
		xhs = yhs;// copy
		TRUE_(equal_f(xhs, vector_u {4, 5, 6}));

		xhs = zhs;// copy
		TRUE_(equal_f(xhs, vector_u {7, 8, 9}));

		xhs = store_u {3, 5, 7};// move
		TRUE_(equal_f(xhs, vector_u {3, 5, 7}));

	}
	TRY_("mutation")
	{
		using sigma_t = typename common::computer::sigma_t;
		using alpha_t = typename common::computer::alpha_t;

		using store_u = store_t<alpha_t[128]>;
		using vector_u = _std::vector<alpha_t>;

		auto xs = store_u {0, 1, 2, 3, 4};
		auto x_ = xs.begin();

		xs.erase(x_ + 2);
		TRUE_(equal_f(xs, vector_u {0, 1, 3, 4}));

		xs.erase(x_ + 1, x_ + 3);
		TRUE_(equal_f(xs, vector_u {0, 4}));

		xs.insert(x_ + 1, {1, 2, 3});
		TRUE_(equal_f(xs, vector_u {0, 1, 2, 3, 4}));

		xs.insert(x_ + 4, x_ + 1, x_ + 4);
		TRUE_(equal_f(xs, vector_u {0, 1, 2, 3, 1, 2, 3, 4}));

	}
}



///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
