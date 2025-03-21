#pragma once
#include "./any.cc"
#include "./buffer.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("buffer")
{
	TRY_("assignment")
	{
		using T_sigma = typename bond::fit<>::sigma_type;
		using T_alpha = typename bond::fit<>::alpha_type;

		using U_buffer = buffer_t<T_alpha[128]>;
		using U_vector = _std::vector<T_alpha>;

		auto const zhs = U_buffer{7, 8, 9};
		auto       yhs = U_buffer{4, 5, 6};
		auto       xhs = U_buffer{1, 2, 3};
		TRUE_(equal_f(xhs, U_vector{1, 2, 3}));
		
		xhs = yhs;// copy
		TRUE_(equal_f(xhs, U_vector{4, 5, 6}));

		xhs = zhs;// copy
		TRUE_(equal_f(xhs, U_vector{7, 8, 9}));

		xhs = U_buffer{3, 5, 7};// move
		TRUE_(equal_f(xhs, U_vector{3, 5, 7}));

	}
	TRY_("mutation")
	{
		using T_sigma = typename bond::fit<>::sigma_type;
		using T_alpha = typename bond::fit<>::alpha_type;

		using U_buffer = buffer_t<T_alpha[128]>;
		using U_vector = _std::vector<T_alpha>;

		auto xs = U_buffer{0, 1, 2, 3, 4};
		auto x_ = xs.begin();

		xs.erase(_std::next(x_, 2));
		TRUE_(equal_f(xs, U_vector{0, 1, 3, 4}));

		xs.erase(_std::next(x_, 1), _std::next(x_, 3));
		TRUE_(equal_f(xs, U_vector{0, 4}));

		xs.insert(_std::next(x_, 1), {1, 2, 3});
		TRUE_(equal_f(xs, U_vector{0, 1, 2, 3, 4}));

		xs.insert(_std::next(x_, 4), _std::next(x_, 1), _std::next(x_, 4));
		TRUE_(equal_f(xs, U_vector{0, 1, 2, 3, 1, 2, 3, 4}));

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
