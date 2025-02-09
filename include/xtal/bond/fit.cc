#pragma once
#include "./any.cc"
#include "./fit.hh"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("fit")
{
	TRY_("`fit` evaluation")
	{
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
		TRUE_(fit<>::template epsilon_n<0> != 0);
		TRUE_(fit<>::template epsilon_n<0> <  fit<>::template epsilon_n<1>);
		TRUE_(fit<>::template epsilon_n<1> <  fit<>::template epsilon_n<2>);
		TRUE_(fit<>::template epsilon_n<1> == _std::numeric_limits<double>::epsilon());
		TRUE_(one <  one + fit<>::template epsilon_n< 1>);
		TRUE_(one == one + fit<>::template epsilon_n< 0>);
		TRUE_(one == one - fit<>::template epsilon_n<-1>);
		TRUE_(one  > one - fit<>::template epsilon_n< 1>);
		TRUE_(                             one == fit<>::template upsilon_n<0>);
		TRUE_(fit<>::template upsilon_n<0> <  fit<>::template upsilon_n<1>);
		TRUE_(fit<>::template upsilon_n<1> <  fit<>::template upsilon_n<2>);
		TRUE_(                             one == fit<>::template dnsilon_n<0>);
		TRUE_(fit<>::template dnsilon_n<1> <  fit<>::template dnsilon_n<0>);
		TRUE_(fit<>::template dnsilon_n<2> <  fit<>::template dnsilon_n<1>);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
