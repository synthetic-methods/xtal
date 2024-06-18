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

	using W_alpha = block_t<T_alpha[2]>;
	using W_aphex = block_t<T_aphex[2]>;
	auto constexpr iffy = [] XTAL_1FN_(bond::computrim_f<16>);

	//\
	W_alpha constexpr w_alpha((size_type) 1);
	W_alpha constexpr w_alpha{0};

	TRY_("task")
	{
		TRUE_(true);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
