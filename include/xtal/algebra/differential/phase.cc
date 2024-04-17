#pragma once
#include "./any.cc"
#include "./phase.hh"// testing...





XTAL_ENV_(push)
namespace xtal::algebra::differential::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("phase")
{
	using re = bond::realize<size_t>;
	using T_sigma = typename re::sigma_t;
	using T_delta = typename re::delta_t;
	using T_alpha = typename re::alpha_t;
	XTAL_LET_(T_alpha) two =  2;
	XTAL_LET_(T_alpha) ten = 10;

	auto mt19937_f = typename realized::mt19937_t();
	mt19937_f.seed(Catch::rngSeed());

	using U_phi = phase_t<T_alpha[2]>;
	using W_phi = _std::complex<U_phi>;

	using D1 = phase_t<T_delta[1]>;
	using D2 = phase_t<T_delta[2]>;
	using D3 = phase_t<T_delta[3]>;
	using D4 = phase_t<T_delta[4]>;
	
	TRY_("complexion")
	{
		W_phi a{{0.1}, {0.2}};
		W_phi b{{0.1}, {0.2}};
		W_phi c = b + a;

		TRUE_(c.real());
		TRUE_(c == W_phi{0.2, 0.4});

	}
	TRY_("construction")
	{
		D2 a_d2{0.250, 0.250};
		D2 b_d2{0.125, 0.125};

		TRUE_(a_d2 == D2{0.250, 0.250});

		a_d2 = b_d2;
		TRUE_(a_d2 == D2{0.125, 0.125});
	//	TRUE_(a_d2 == D2{0x40000000, 0x40000000});

	}
	TRY_("multiplication")
	{
		T_alpha x =  0.33, x_dt = re::haplo_f(4);

		U_phi   phi{x, x_dt};
		T_alpha foo{x};

		for (T_sigma i = 0x2; ~--i;) {
			T_alpha const u = -_std::pow(two, 1 + re::mantissa_f(mt19937_f));
			phi *= u;
			foo *= u;
			foo -= _std::round(foo);
			TRUE_(computrim_f<4>(phi(0)) == computrim_f<4>(foo));
		}
	}
	TRY_("trial")
	{
		EST_("multiplication (fixed-point)")
		{
			T_alpha x = 0.33, x_dt = re::haplo_f(4);

			U_phi   phi{x, x_dt};
		//	T_alpha foo{x};

			for (T_sigma i = 0x100; ~--i;) {
				T_alpha const u = _std::pow(two, 1 + re::mantissa_f(mt19937_f));
				phi *= u;
			}
			return phi;
		};
		EST_("multiplication (floating-point)")
		{
			T_alpha x = 0.33, x_dt = re::haplo_f(4);

		//	U_phi   phi{x, x_dt};
			T_alpha foo{x};

			for (T_sigma i = 0x100; ~--i;) {
				T_alpha const u = _std::pow(two, 1 + re::mantissa_f(mt19937_f));
				foo *= u;
				foo -= _std::round(foo);
			}
			return foo;
		};
	}
	TRY_("addition")
	{
		T_alpha x =  0.33, x_dt = re::haplo_f(4);
		T_alpha y =  5.55;
		T_alpha z =  x+y; z -= _std::round(z);

		U_phi phi{x, x_dt};

		phi += y;
	//	TRUE_(bond::computrim_f<8>(phi[0]) == bond::computrim_f<8>(z));
		TRUE_(bond::computrim_f<8>(phi(0)) == bond::computrim_f<8>(z));

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
