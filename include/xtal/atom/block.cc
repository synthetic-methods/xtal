#pragma once
#include "./any.cc"
#include "./block.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("block")
{
	using re = bond::realized;
	using T_delta = typename re::delta_t;
	using T_sigma = typename re::sigma_t;
	using T_alpha = typename re::alpha_t;
	using T_aphex = typename re::aphex_t;

	using W_alpha = block_t<T_alpha[2]>;
	using W_aphex = block_t<T_aphex[2]>;
	auto constexpr iffy = [] XTAL_1FN_(bond::computrim_f<16>);

	//\
	W_alpha constexpr w_alpha((size_t) 1);
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
