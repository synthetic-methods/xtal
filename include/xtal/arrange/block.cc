#pragma once
#include "./any.cc"
#include "./block.hh"// testing...





XTAL_ENV_(push)
namespace xtal::arrange::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("block")
{
	using _op = bond::operating;
	using T_delta = typename _op::delta_type;
	using T_sigma = typename _op::sigma_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;

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

		  TRUE_(w_0.zeroed());
		UNTRUE_(w_1.zeroed());

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
