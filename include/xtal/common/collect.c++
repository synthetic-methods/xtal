#pragma once
#include "./etc.c++"
#include "./collect.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::common::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/common/collect.hpp: fluid assigment")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	using buffer_u = typename collect_t<128>::template fluid_t<alpha_t>;
	using vector_u = _std::vector<alpha_t>;

	auto const zhs = buffer_u {7, 8, 9};
	auto       yhs = buffer_u {4, 5, 6};
	auto       xhs = buffer_u {1, 2, 3};
	REQUIRE(_v3::ranges::equal(xhs, vector_u {1, 2, 3}));
	
	xhs = yhs;// copy
	REQUIRE(_v3::ranges::equal(xhs, vector_u {4, 5, 6}));

	xhs = zhs;// copy
	REQUIRE(_v3::ranges::equal(xhs, vector_u {7, 8, 9}));

	xhs = buffer_u {3, 5, 7};// move
	REQUIRE(_v3::ranges::equal(xhs, vector_u {3, 5, 7}));
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/common/collect.hpp: fluid mutation")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	using buffer_u = typename collect_t<128>::template fluid_t<alpha_t>;
	using vector_u = _std::vector<alpha_t>;

	auto xs = buffer_u {0, 1, 2, 3, 4};
	auto x_ = xs.begin();

	xs.erase(x_ + 2);
	REQUIRE(_v3::ranges::equal(xs, vector_u {0, 1, 3, 4}));

	xs.erase(x_ + 1, x_ + 3);
	REQUIRE(_v3::ranges::equal(xs, vector_u {0, 4}));

	xs.insert(x_ + 1, {1, 2, 3});
	REQUIRE(_v3::ranges::equal(xs, vector_u {0, 1, 2, 3, 4}));

	xs.insert(x_ + 4, x_ + 1, x_ + 4);
	REQUIRE(_v3::ranges::equal(xs, vector_u {0, 1, 2, 3, 1, 2, 3, 4}));
}
/**/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
