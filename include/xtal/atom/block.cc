#pragma once
#include "./any.cc"
#include "./block.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//atic_assert(_xtd::trivially_initializable<block_t<float[2]>>);
static_assert(_xtd::trivially_destructible<block_t<float[2]>>);
static_assert(_xtd::trivially_copyable<block_t<float[2]>>);
static_assert(_xtd::trivially_movable<block_t<float[2]>>);
//atic_assert(atomic_q<block_t<float[2]>>);

static_assert(bond::pack_size_q<block_t<double[2]>>);

static_assert(fixed_shaped_q<block_t<int(&)[1]>>);
static_assert(fixed_valued_q<block_t<int(&)[1]>>);


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("block")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	using W_alpha = block_t<T_alpha[2]>; using U_alpha_ = block_t<T_alpha(&)[1]>;
	using W_aphex = block_t<T_aphex[2]>; using U_aphex_ = block_t<T_aphex(&)[1]>;

	TRY_("block slicing")
	{
		W_alpha w_alpha{1, 2};

		auto  u_alpha_ = w_alpha.self(one);
		TRUE_(w_alpha == W_alpha{1, 2});
		u_alpha_[0] = 3;
		TRUE_(w_alpha == W_alpha{3, 2});

		TRUE_(w_alpha.size() == 2);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
