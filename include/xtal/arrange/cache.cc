#pragma once
#include "./any.cc"
#include "./cache.hh"// testing...


XTAL_ENV_(push)
namespace xtal::arrange::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("cache")
{
	using _fix = bond::fixture<>;
	using T_delta = typename _fix::delta_type;
	using T_sigma = typename _fix::sigma_type;
	using T_alpha = typename _fix::alpha_type;
	using T_aphex = typename _fix::aphex_type;

	TRY_("cache: formation") {
		cache_t<T_alpha[2]> cachet;

		auto [a0, b0] = cachet.form<T_alpha, T_alpha>();
		a0 = 0.125;
		b0 = 0.875;

		auto [a1, b1] = cachet.form<T_alpha, T_alpha>();
		TRUE_(a0 == a1);
		TRUE_(b0 == b1);

		auto [a2, b2] = cachet.form(T_alpha{-0.25}, T_alpha{-0.75});
		TRUE_(a0 == -0.25 and a1 == -0.25 and a2 == 0.125);
		TRUE_(b0 == -0.75 and b1 == -0.75 and b2 == 0.875);

	}
	TRY_("cache: preallocation") {
		TRUE_(_detail::aligned_n<T_aphex[2]> == cache_t<T_aphex[2]>::size());
		TRUE_(_detail::aligned_n<T_aphex[4]> == cache_t<T_aphex[3]>::size());
		TRUE_(_detail::aligned_n<T_aphex[4]> == cache_t<T_aphex[2], T_aphex[1]>::size());
		TRUE_(_detail::aligned_n<T_aphex[8]> == cache_t<T_aphex[6]>::size());

	}
	TRY_("cache: allocation stepping") {
		size_type i{};
		TRUE_(_detail::maligned_f<_std::byte   >(i) == 0x0);
		TRUE_(_detail::maligned_f<_std::int16_t>(i) == 0x2);
		TRUE_(_detail::maligned_f<_std::byte   >(i) == 0x4);
		TRUE_(_detail::maligned_f<_std::byte   >(i) == 0x5);
		TRUE_(_detail::maligned_f<_std::int16_t>(i) == 0x6);
		TRUE_(_detail::maligned_f<_std::byte   >(i) == 0x8);
		TRUE_(_detail::maligned_f<_std::int16_t>(i) == 0xA);

		TRUE_(0x10 == cache_t<_std::byte, _std::int16_t, _std::byte, _std::byte, _std::int16_t, _std::byte, _std::int16_t>::size());
	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)





