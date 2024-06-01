#pragma once
#include "./any.cc"
#include "./serial.hh"// testing...





XTAL_ENV_(push)
namespace xtal::algebra::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("solid", "serial")
{
	using Op = bond::operating;
	using T_delta = typename Op::delta_t;
	using T_sigma = typename Op::sigma_t;
	using T_alpha = typename Op::alpha_t;
	using T_aphex = typename Op::aphex_t;

	using D1 = serial_t<int[1]>;
	using D2 = serial_t<int[2]>;
	using D3 = serial_t<int[3]>;
	using D4 = serial_t<int[4]>;
	
	TRY_("partial construction")
	{
		D4 d4{1000};

		TRUE_(d4 == D4{1000, 0, 0, 0});

	}
	TRY_("multiplication")
	{
		TRUE_(D2 {           10, 1} * D2 {           20, 2} == D2 {                   200,   40});
		TRUE_(D3 {      100, 10, 1} * D3 {      200, 20, 2} == D3 {          20000,  4000,  600});
		TRUE_(D4{1000, 100, 10, 1} * D4{2000, 200, 20, 2} == D4{2000000, 400000, 60000, 8000});

		TRUE_(D2{1, 2} < D2{3, 4});

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
