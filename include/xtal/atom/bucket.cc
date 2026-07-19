#pragma once
#include "./any.cc"
#include "./bucket.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//atic_assert(xtd::trivially_initializable<bucket_t<float[2]>>);
static_assert(xtd::trivially_destructible<bucket_t<float[2]>>);
static_assert(xtd::trivially_copyable<bucket_t<float[2]>>);
static_assert(xtd::trivially_movable<bucket_t<float[2]>>);
//atic_assert(atomic_q<bucket_t<float[2]>>);

static_assert(bond::pack_size_q<bucket_t<double[2]>>);

static_assert(fixed_shaped_q<bucket_t<int(&)[1]>>);
static_assert(fixed_valued_q<bucket_t<int(&)[1]>>);

static_assert( objective_q<bucket_t<int   [1]>>);
static_assert(subjective_q<bucket_t<int(&)[1]>>);


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("bucket")
{
	using _fit = bond::fit<>;
	using T_delta = typename _fit::delta_type;
	using T_sigma = typename _fit::sigma_type;
	using T_alpha = typename _fit::alpha_type;
	using T_aphex = typename _fit::aphex_type;

	using W_alpha = bucket_t<T_alpha[2]>; using U_alpha_ = bucket_t<T_alpha(&)[1]>;
	using W_aphex = bucket_t<T_aphex[2]>; using U_aphex_ = bucket_t<T_aphex(&)[1]>;

	TRY_("bucket nesting")
	{
		using Z_alpha = bucket_t<T_alpha[2][4][6]>;

		TRUE_(2 == fluid_shaped<         Z_alpha                                    >::extent());
		TRUE_(4 == fluid_shaped<typename Z_alpha::value_type                        >::extent());
		TRUE_(6 == fluid_shaped<typename Z_alpha::value_type::value_type            >::extent());
		TRUE_(0 == fluid_shaped<typename Z_alpha::value_type::value_type::value_type>::extent());

	}
	TRY_("bucket expansion")
	{
		using W2 = bucket_t<T_alpha[2]>;
		using W3 = bucket_t<T_alpha[3]>;

		auto w2 = W2{1, 2}; auto _w3 = w2.twin(cardinal_constant_t<3>{});
		auto w3 = W3{1, 2};

		TRUE_(w3[0] == _w3[0]);
		TRUE_(w3[1] == _w3[1]);
	//	TRUE_(w3[2] == _w3[2]);
	//	TRUE_(w3    == _w3   );
	//	TODO: Make this work with CLang/RELEASE...

	}
	TRY_("bucket slicing (array)")
	{
		using W = bucket_t<T_alpha[2]>;

		W w{1, 2};

		auto  u = w.self(-one);
		TRUE_(w == W{1, 2});
		u[0] = 3;
		TRUE_(w == W{3, 2});

		TRUE_(w.size() == 2);
		TRUE_(u.size() == 1);

	}
//	TRY_("bucket slicing (tuple)")
//	{
//		using W = bucket_t<T_alpha, T_sigma>;
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
