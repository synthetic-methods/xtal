#pragma once
#include "./any.cc"
#include "./fit.hh"// testing...

#include "./compose.hh"



XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

static_assert( 1.0F == fit<float>::minimum_f( 1.0F,  1.5F));
static_assert( 1.0F == fit<float>::minimum_f( 1.5F,  1.0F));
static_assert(-1.5F == fit<float>::minimum_f(-1.0F, -1.5F));
static_assert(-1.5F == fit<float>::minimum_f(-1.5F, -1.0F));

static_assert( 1.5F == fit<float>::maximum_f( 1.0F,  1.5F));
static_assert( 1.5F == fit<float>::maximum_f( 1.5F,  1.0F));
static_assert(-1.0F == fit<float>::maximum_f(-1.0F, -1.5F));
static_assert(-1.0F == fit<float>::maximum_f(-1.5F, -1.0F));

static_assert(same_q<_std::complex<int   >, compose_s<int, fit<_std::complex<double   >>>>);
static_assert(same_q<_std::array  <int, 2>, compose_s<int, fit<_std::array  <double, 2>>>>);

////////////////////////////////////////////////////////////////////////////////

TAG_("fit")
{
	TRY_("`fit` evaluation")
	{
		auto constexpr M_sqrt2 = fit<>::diplo_f(0.5);
		auto constexpr N_sqrt2 = _std::numbers::sqrt2_v<typename fit<>::alpha_type>;
		TRUE_(N_sqrt2/M_sqrt2 - M_sqrt2/N_sqrt2 < fit<>::epsilon_f(8));

		TRUE_(fit<>::negative.depth == fit<>::full.depth);
		TRUE_(~fit<>::sign.mask == fit<>::positive.mask);
		TRUE_(0 != fit<>::template expound_f<2>( 1) and 0 != fit<>::template expound_f<3>( 1));
		TRUE_(0 == fit<>::template expound_f<2>( 2) and 0 != fit<>::template expound_f<3>( 2));
		TRUE_(0 != fit<>::template expound_f<2>( 3) and 0 == fit<>::template expound_f<3>( 3));
		TRUE_(0 == fit<>::template expound_f<2>( 4) and 0 != fit<>::template expound_f<3>( 4));
		TRUE_(0 == fit<>::template expound_f<2>( 8) and 0 != fit<>::template expound_f<3>( 8));
		TRUE_(0 != fit<>::template expound_f<2>( 9) and 0 == fit<>::template expound_f<3>( 9));
		TRUE_(0 == fit<>::template expound_f<2>(16) and 0 != fit<>::template expound_f<3>(16));
		TRUE_(0 != fit<>::template expound_f<2>(27) and 0 == fit<>::template expound_f<3>(27));
		TRUE_(fit<>::template diplo_n<+1> == 2.0);
		TRUE_(fit<>::template diplo_n< 0> == 1.0);
		TRUE_(fit<>::template diplo_n<-1> == 0.5);
		TRUE_(fit<>::template haplo_n<+1> == 0.5);
		TRUE_(fit<>::template haplo_n< 0> == 1.0);
		TRUE_(fit<>::template haplo_n<-1> == 2.0);
		TRUE_(fit<>::ratio_f(1, 2.0) == 0.5 && fit<>::template ratio_f<-1>(1, 2.0) == 2.0);
		TRUE_(fit<>::ratio_f(4, 2.0) == 2.0 && fit<>::template ratio_f<-1>(4, 2.0) == 0.5);
		TRUE_(fit<>::patio_f(1, 2) ==  double(1.570796326794896619231321691639751442L));
		TRUE_(fit<>::patio_f(1,-2) == -double(1.570796326794896619231321691639751442L));
		TRUE_(fit<>::patio_f(4, 2) ==  double(6.283185307179586476925286766559005768L));
		TRUE_(fit<>::patio_f(4,-2) == -double(6.283185307179586476925286766559005768L));
		TRUE_(fit<>::epsilon_f(0) != 0);
		TRUE_(fit<>::epsilon_f(0) <  fit<>::epsilon_f(1));
		TRUE_(fit<>::epsilon_f(1) <  fit<>::epsilon_f(2));
		TRUE_(fit<>::epsilon_f(1) == _std::numeric_limits<double>::epsilon());
		TRUE_(one <  one + fit<>::epsilon_f( 1));
		TRUE_(one == one + fit<>::epsilon_f( 0));
		TRUE_(one == one - fit<>::epsilon_f(-1));
		TRUE_(one  > one - fit<>::epsilon_f( 1));
		TRUE_(                one == fit<>::upsilon_f(0));
		TRUE_(fit<>::upsilon_f(0) <  fit<>::upsilon_f(1));
		TRUE_(fit<>::upsilon_f(1) <  fit<>::upsilon_f(2));
		TRUE_(                one == fit<>::dnsilon_f(0));
		TRUE_(fit<>::dnsilon_f(1) <  fit<>::dnsilon_f(0));
		TRUE_(fit<>::dnsilon_f(2) <  fit<>::dnsilon_f(1));

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
