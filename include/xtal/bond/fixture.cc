#pragma once
#include "./any.cc"
#include "./fixture.hh"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("fixture")
{
	TRY_("`fixture` evaluation")
	{
		TRUE_(fixture<>::negative.depth == fixture<>::full.depth);
		TRUE_(~fixture<>::sign.mask == fixture<>::positive.mask);
		TRUE_(0 != fixture<>::template expound_f<2>( 1) and 0 != fixture<>::template expound_f<3>( 1));
		TRUE_(0 == fixture<>::template expound_f<2>( 2) and 0 != fixture<>::template expound_f<3>( 2));
		TRUE_(0 != fixture<>::template expound_f<2>( 3) and 0 == fixture<>::template expound_f<3>( 3));
		TRUE_(0 == fixture<>::template expound_f<2>( 4) and 0 != fixture<>::template expound_f<3>( 4));
		TRUE_(0 == fixture<>::template expound_f<2>( 8) and 0 != fixture<>::template expound_f<3>( 8));
		TRUE_(0 != fixture<>::template expound_f<2>( 9) and 0 == fixture<>::template expound_f<3>( 9));
		TRUE_(0 == fixture<>::template expound_f<2>(16) and 0 != fixture<>::template expound_f<3>(16));
		TRUE_(0 != fixture<>::template expound_f<2>(27) and 0 == fixture<>::template expound_f<3>(27));
		TRUE_(fixture<>::template diplo_n<+1> == 2.0);
		TRUE_(fixture<>::template diplo_n< 0> == 1.0);
		TRUE_(fixture<>::template diplo_n<-1> == 0.5);
		TRUE_(fixture<>::template haplo_n<+1> == 0.5);
		TRUE_(fixture<>::template haplo_n< 0> == 1.0);
		TRUE_(fixture<>::template haplo_n<-1> == 2.0);
		TRUE_(fixture<>::ratio_f(1, 2.0) == 0.5 && fixture<>::template ratio_f<-1>(1, 2.0) == 2.0);
		TRUE_(fixture<>::ratio_f(4, 2.0) == 2.0 && fixture<>::template ratio_f<-1>(4, 2.0) == 0.5);
		TRUE_(fixture<>::patio_f(1, 2) ==  double(1.570796326794896619231321691639751442L));
		TRUE_(fixture<>::patio_f(1,-2) == -double(1.570796326794896619231321691639751442L));
		TRUE_(fixture<>::patio_f(4, 2) ==  double(6.283185307179586476925286766559005768L));
		TRUE_(fixture<>::patio_f(4,-2) == -double(6.283185307179586476925286766559005768L));
		TRUE_(fixture<>::template epsilon_n<0> != 0);
		TRUE_(fixture<>::template epsilon_n<0> <  fixture<>::template epsilon_n<1>);
		TRUE_(fixture<>::template epsilon_n<1> <  fixture<>::template epsilon_n<2>);
		TRUE_(fixture<>::template epsilon_n<1> == _std::numeric_limits<double>::epsilon());
		TRUE_(one <  one + fixture<>::template epsilon_n< 1>);
		TRUE_(one == one + fixture<>::template epsilon_n< 0>);
		TRUE_(one == one - fixture<>::template epsilon_n<-1>);
		TRUE_(one  > one - fixture<>::template epsilon_n< 1>);
		TRUE_(                             one == fixture<>::template upsilon_n<0>);
		TRUE_(fixture<>::template upsilon_n<0> <  fixture<>::template upsilon_n<1>);
		TRUE_(fixture<>::template upsilon_n<1> <  fixture<>::template upsilon_n<2>);
		TRUE_(                             one == fixture<>::template dnsilon_n<0>);
		TRUE_(fixture<>::template dnsilon_n<1> <  fixture<>::template dnsilon_n<0>);
		TRUE_(fixture<>::template dnsilon_n<2> <  fixture<>::template dnsilon_n<1>);
		TRUE_(fixture<>::template trim_f<2>(fixture<>::patio_f(2, 1)) == 6.25);
		TRUE_(fixture<>::template trim_f<3>(fixture<>::patio_f(1, 1)) == 3.125);
		TRUE_(fixture<>::template trim_f<4>(fixture<>::patio_f(1, 2)) == 1.5625);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
