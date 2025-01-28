#pragma once
#include "./any.cc"
#include "./block.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert( fixed_sized_q<block_t<int(&)[1]>>);
static_assert(fixed_valued_q<block_t<int(&)[1]>>);


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("block")
{
	using _fix = bond::fixture<>;
	using T_delta = typename _fix::delta_type;
	using T_sigma = typename _fix::sigma_type;
	using T_alpha = typename _fix::alpha_type;
	using T_aphex = typename _fix::aphex_type;

	using W_alpha = block_t<T_alpha[2]>; using U_alpha_ = block_t<T_alpha(&)[1]>;
	using W_aphex = block_t<T_aphex[2]>; using U_aphex_ = block_t<T_aphex(&)[1]>;

	TRY_("block slicing")
	{
		W_alpha w_alpha{1, 2};

		auto  u_alpha_ = w_alpha.self(one);
		TRUE_(w_alpha == W_alpha{1, 2});
		u_alpha_[0] = 3;
		TRUE_(w_alpha == W_alpha{3, 2});

	}
	TRY_("block checking")
	{
		W_alpha w_0{0, 0};
		W_alpha w_1{1, 1};

		  TRUE_(w_0.blanked());
		UNTRUE_(w_1.blanked());

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
