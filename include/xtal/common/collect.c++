#pragma once
#include "./any.c++"
#include "./collect.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::common::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("collect", "fluid")
{
	TRY_("assignment")
	{
		using sigma_t = typename realized::sigma_t;
		using alpha_t = typename realized::alpha_t;

		using buffer_u = typename collect_t<128>::template fluid_t<alpha_t>;
		using vector_u = _std::vector<alpha_t>;

		auto const zhs = buffer_u {7, 8, 9};
		auto       yhs = buffer_u {4, 5, 6};
		auto       xhs = buffer_u {1, 2, 3};
		TRUE_(equal_f(xhs, vector_u {1, 2, 3}));
		
		xhs = yhs;// copy
		TRUE_(equal_f(xhs, vector_u {4, 5, 6}));

		xhs = zhs;// copy
		TRUE_(equal_f(xhs, vector_u {7, 8, 9}));

		xhs = buffer_u {3, 5, 7};// move
		TRUE_(equal_f(xhs, vector_u {3, 5, 7}));

	}
	TRY_("mutation")
	{
		using sigma_t = typename realized::sigma_t;
		using alpha_t = typename realized::alpha_t;

		using buffer_u = typename collect_t<128>::template fluid_t<alpha_t>;
		using vector_u = _std::vector<alpha_t>;

		auto xs = buffer_u {0, 1, 2, 3, 4};
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
