#pragma once
#include "./any.c++"
#include "./sluice.ipp"// testing...





XTAL_ENV_(push)
namespace xtal::compound::fluid::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("sluice")
{
	TRY_("assignment")
	{
		using sigma_t = typename computer::sigma_t;
		using alpha_t = typename computer::alpha_t;

		using sluice_u = sluice_t<alpha_t[128]>;
		using vector_u = _std::vector<alpha_t>;

		auto const zhs = sluice_u {7, 8, 9};
		auto       yhs = sluice_u {4, 5, 6};
		auto       xhs = sluice_u {1, 2, 3};
		TRUE_(equal_f(xhs, vector_u {1, 2, 3}));
		
		xhs = yhs;// copy
		TRUE_(equal_f(xhs, vector_u {4, 5, 6}));

		xhs = zhs;// copy
		TRUE_(equal_f(xhs, vector_u {7, 8, 9}));

		xhs = sluice_u {3, 5, 7};// move
		TRUE_(equal_f(xhs, vector_u {3, 5, 7}));

	}
	TRY_("mutation")
	{
		using sigma_t = typename computer::sigma_t;
		using alpha_t = typename computer::alpha_t;

		using sluice_u = sluice_t<alpha_t[128]>;
		using vector_u = _std::vector<alpha_t>;

		auto xs = sluice_u {0, 1, 2, 3, 4};
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
