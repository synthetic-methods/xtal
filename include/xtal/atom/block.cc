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

	TRY_("block nesting")
	{
		using Z_alpha = block_t<T_alpha[2][4][6]>;

		TRUE_(2 == fluid_shaped<         Z_alpha                                    >::extent());
		TRUE_(4 == fluid_shaped<typename Z_alpha::value_type                        >::extent());
		TRUE_(6 == fluid_shaped<typename Z_alpha::value_type::value_type            >::extent());
		TRUE_(0 == fluid_shaped<typename Z_alpha::value_type::value_type::value_type>::extent());

	}
	TRY_("block slicing (array)")
	{
		using W = block_t<T_alpha[2]>;

		W w{1, 2};

		auto  u = w.self(-one);
		TRUE_(w == W{1, 2});
		u[0] = 3;
		TRUE_(w == W{3, 2});

		TRUE_(w.size() == 2);
		TRUE_(u.size() == 1);

	}
//	TRY_("block slicing (tuple)")
//	{
//		using W = block_t<T_alpha, T_sigma>;
//		W w{1, 2};
//
//		auto  u = w.self(-one);
//		TRUE_(w == W{1, 2});
//		u[0] = 3;
//		TRUE_(w == W{3, 2});
//
//		TRUE_(w.size() == 2);
//		TRUE_(u.size() == 1);
//
//	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
