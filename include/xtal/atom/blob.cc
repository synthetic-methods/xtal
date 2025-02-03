#pragma once
#include "./any.cc"
#include "./blob.hh"// testing...


XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("blob")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	TRY_("blob: formation") {
		blob_t<T_alpha[2]> blob;

		auto [a0, b0] = blob.form<T_alpha, T_alpha>();
		a0 = 0.125;
		b0 = 0.875;

		auto [a1, b1] = blob.form<T_alpha, T_alpha>();
		TRUE_(a0 == a1);
		TRUE_(b0 == b1);

		auto [a2, b2] = blob.form(T_alpha{-0.25}, T_alpha{-0.75});
		TRUE_(a0 == -0.25 and a1 == -0.25 and a2 == 0.125);
		TRUE_(b0 == -0.75 and b1 == -0.75 and b2 == 0.875);

	}
	TRY_("blob: preallocation") {
		TRUE_(_detail::aligned<T_aphex[2]>::size() == blob_t<T_aphex[2]>::size());
		TRUE_(_detail::aligned<T_aphex[4]>::size() == blob_t<T_aphex[3]>::size());
		TRUE_(_detail::aligned<T_aphex[4]>::size() == blob_t<T_aphex[2], T_aphex[1]>::size());
		TRUE_(_detail::aligned<T_aphex[8]>::size() == blob_t<T_aphex[6]>::size());

	}
	TRY_("blob: allocation stepping") {
		size_type i{};
		TRUE_(_detail::aligned<_std::byte   >::static_bump(i) == 0x0);
		TRUE_(_detail::aligned<_std::int16_t>::static_bump(i) == 0x2);
		TRUE_(_detail::aligned<_std::byte   >::static_bump(i) == 0x4);
		TRUE_(_detail::aligned<_std::byte   >::static_bump(i) == 0x5);
		TRUE_(_detail::aligned<_std::int16_t>::static_bump(i) == 0x6);
		TRUE_(_detail::aligned<_std::byte   >::static_bump(i) == 0x8);
		TRUE_(_detail::aligned<_std::int16_t>::static_bump(i) == 0xA);

		TRUE_(0x10 == blob_t<_std::byte, _std::int16_t, _std::byte, _std::byte, _std::int16_t, _std::byte, _std::int16_t>::size());
	}
}
/***/

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)





