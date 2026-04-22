#pragma once
#include "./any.cc"
#include "./stash.hh"// testing...


XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("stash")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	TRY_("stash: formation") {
		stash_t<T_alpha[2]> stash;

		auto [a0, b0] = stash.form<T_alpha, T_alpha>();
		a0 = 0.125;
		b0 = 0.875;

		auto [a1, b1] = stash.form<T_alpha, T_alpha>();
		TRUE_(a0 == a1);
		TRUE_(b0 == b1);

		auto [a2, b2] = stash.form(T_alpha{-0.25}, T_alpha{-0.75});
		TRUE_(a0 == -0.250);
		TRUE_(a1 == -0.250);
		TRUE_(a2 ==  0.125);
		TRUE_(b0 == -0.750);
		TRUE_(b1 == -0.750);
		TRUE_(b2 ==  0.875);

	}
	TRY_("stash: preallocation") {
		TRUE_(_detail::aligned<T_aphex[2]>::size() == stash_t<T_aphex[2]>::size());
		TRUE_(_detail::aligned<T_aphex[4]>::size() == stash_t<T_aphex[3]>::size());
		TRUE_(_detail::aligned<T_aphex[4]>::size() == stash_t<T_aphex[2], T_aphex[1]>::size());
		TRUE_(_detail::aligned<T_aphex[8]>::size() == stash_t<T_aphex[6]>::size());

	}
	TRY_("stash: allocation stepping") {
		size_type i{};
		TRUE_(_detail::aligned<_std::byte   >::advance(i) == 0x0);
		TRUE_(_detail::aligned<_std::int16_t>::advance(i) == 0x2);
		TRUE_(_detail::aligned<_std::byte   >::advance(i) == 0x4);
		TRUE_(_detail::aligned<_std::byte   >::advance(i) == 0x5);
		TRUE_(_detail::aligned<_std::int16_t>::advance(i) == 0x6);
		TRUE_(_detail::aligned<_std::byte   >::advance(i) == 0x8);
		TRUE_(_detail::aligned<_std::int16_t>::advance(i) == 0xA);

		TRUE_(0x10 == stash_t<_std::byte, _std::int16_t, _std::byte, _std::byte, _std::int16_t, _std::byte, _std::int16_t>::size());
	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)





