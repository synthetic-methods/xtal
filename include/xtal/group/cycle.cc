#pragma once
#include "./any.cc"
#include "./cycle.ii"// testing...





XTAL_ENV_(push)
namespace xtal::group::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("cycle")
{
	using re = bond::realized;
	using T_sigma = unsigned int;
	using T_delta =   signed int;
	using T_alpha =        float;
	using U_phi = cycle_t<T_alpha[2]>;

	using D1 = cycle_t<int[1]>;
	using D2 = cycle_t<int[2]>;
	using D3 = cycle_t<int[3]>;
	using D4 = cycle_t<int[4]>;
	
	TRY_("construction")
	{
		D2 a_d2 {0.250, 0.250};
		D2 b_d2 {0.125, 0.125};

		TRUE_(a_d2 == D2 {0.250, 0.250});

		a_d2 = b_d2;
		TRUE_(a_d2 == D2 {0.125, 0.125});
	//	TRUE_(a_d2 == D2 {0x40000000, 0x40000000});

	}
	TRY_("multiplication")
	{
		T_alpha x =  0.33, x_dt = re::haplo_f(4);
		T_alpha y =  5.55;
		T_alpha z =  x*y;

		U_phi phi {x, x_dt};

		phi *= y;
	//	TRUE_(bond::computrim_f<8>(phi[0]) == bond::computrim_f<8>(z - _std::round(z)));
		TRUE_(bond::computrim_f<8>(phi(0)) == bond::computrim_f<8>(z - _std::round(z)));

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
