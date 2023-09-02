#pragma once
#include "./any.cc"
#include "./series.ii"// testing...





XTAL_ENV_(push)
namespace xtal::compound::solid::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("solid", "series")
{
	TRY_("initialization")
	{
		using sigma_t = typename common::computer::sigma_t;
		using alpha_t = typename common::computer::alpha_t;

		sigma_t constexpr N = 1 << 3;
		using series_w = solid::series_t<alpha_t[N]>;
		using series_u = solid::series_t<alpha_t[N]>;

		series_u baz(2.0);
		series_w bar = force_f<series_w &>(baz);
		series_w foo = {1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7};
		TRUE_(equal_f(foo, bar));
		
	}
	TRY_("transformation")
	{
		using sigma_t = typename common::computer::sigma_t;
		using alpha_t = typename common::computer::alpha_t;
		using aphex_t = typename common::computer::aphex_t;

		auto    constexpr iffy = [] XTAL_1FN_(common::computrim_f<16>);
		sigma_t constexpr O = 1 << 5;
		sigma_t constexpr N = 1 << 3;
		sigma_t constexpr M = N  - 1;

		using series_s = solid::series_t<aphex_t[O]>;
		using series_u = solid::series_t<aphex_t[N]>;
		series_s basis(ordinal_t<-1>{});

		series_u source;
		source[0] = source[M - 0] = aphex_t(0.0, 0.0);
		source[1] = source[M - 1] = aphex_t(1.0, 1.0);
		source[2] = source[M - 2] = aphex_t(3.0, 3.0);
		source[3] = source[M - 3] = aphex_t(4.0, 4.0);

		auto target = basis.transformation(source).transmute(iffy);
		TRUE_(target[0] == iffy(aphex_t( 0.1600000000000000e+2,  0.1600000000000000e+2)));
		TRUE_(target[1] == iffy(aphex_t(-0.4828427124746192e+1, -0.1165685424949238e+2)));
		TRUE_(target[2] == iffy(aphex_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
		TRUE_(target[3] == iffy(aphex_t(-0.3431457505076203e+0,  0.8284271247461885e+0)));
		TRUE_(target[4] == iffy(aphex_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
		TRUE_(target[5] == iffy(aphex_t( 0.8284271247461912e+0, -0.3431457505076203e+0)));
		TRUE_(target[6] == iffy(aphex_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
		TRUE_(target[7] == iffy(aphex_t(-0.1165685424949238e+2, -0.4828427124746188e+1)));

	}
	TRY_("convolution")
	{
		using sigma_t = typename common::computer::sigma_t;
		using alpha_t = typename common::computer::alpha_t;
		using aphex_t = typename common::computer::aphex_t;

		auto    constexpr iffy = [] XTAL_1FN_(common::computrim_f<16>);
		sigma_t constexpr N = 1 << 3;
		sigma_t constexpr M = N  - 1;

		using series_u = solid::series_t<aphex_t[N]>;
		series_u basis(ordinal_t<-1>{});

		series_u lhs = {0, 1, 2, 0, 0, 0, 0, 0};
		series_u rhs = {1, 0, 1, 0, 0, 0, 0, 0};
		series_u xhs = {0, 1, 2, 1, 2, 0, 0, 0};
		series_u yhs = basis.convolution(lhs, rhs).transmute(iffy);
		TRUE_(xhs == yhs);

	}
	TRY_("multiplication")
	{
		using sigma_t = typename common::computer::sigma_t;
		using alpha_t = typename common::computer::alpha_t;
		using aphex_t = typename common::computer::aphex_t;

		using C4 = solid::series_t<aphex_t[4]>;
		using D4 = solid::series_t<aphex_t[4]>;
		
		TRUE_(C4 {1000, 100, 10, 1} * C4 {2000, 200, 20, 2} == C4 {2000600, 400040, 60002, 8000});
		TRUE_(D4 {1000, 100, 10, 1} * D4 {2000, 200, 20, 2} == D4 {2000600, 400040, 60002, 8000});

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
