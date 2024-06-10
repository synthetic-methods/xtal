#pragma once
#include "./any.cc"
#include "./circular.hh"// testing...





XTAL_ENV_(push)
namespace xtal::algebra::differential::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("circular")
{
	using _op = bond::operating;
	using T_sigma = typename _op::sigma_t;
	using T_delta = typename _op::delta_t;
	using T_alpha = typename _op::alpha_t;
	static constexpr T_alpha two =  2;
	static constexpr T_alpha ten = 10;

	auto mt19937_f = typename operating::mt19937_t(Catch::rngSeed());

	using V_phi = T_alpha;
	using U_phi = circular_t<V_phi[2]>;
	using W_phi = _std::complex<U_phi>;

	using D1 = circular_t<T_delta[1]>;
	using D2 = circular_t<T_delta[2]>;
	using D3 = circular_t<T_delta[3]>;
	using D4 = circular_t<T_delta[4]>;
	
	TRY_("complexion")
	{
		W_phi a{{0.1, 0.0}, {0.2, 0.0}};
		W_phi b{{0.1, 0.0}, {0.2, 0.0}};
		//\
		W_phi c = 2.0 * a;
		W_phi c = b + a;

		TRUE_(c == W_phi{{0.2, 0.0}, {0.4, 0.0}});

	}
	TRY_("construction")
	{
		D2 a_d2{0.250, 0.250};
		D2 b_d2{0.125, 0.125};
		D2 y_d2{0.125};
		D2 z_d2(0.125);

		TRUE_(z_d2 == D2{0.125, 0.000});

		TRUE_(y_d2 == D2{0.000, 0.125}); y_d2 <<= {0.250};
		TRUE_(y_d2 == D2{0.000, 0.250}); y_d2 <<= _std::array<T_alpha, 1>{0.500};
		TRUE_(y_d2 == D2{0.000, 0.500}); y_d2 >>= _std::array<T_alpha, 1>{0.333};
		TRUE_(y_d2 == D2{0.333, 0.500});

		TRUE_(computrim_f<8>((2.0*y_d2)(0)) == computrim_f<8>(-0.334));
		TRUE_(computrim_f<8>((2.0*y_d2)(1)) == computrim_f<8>( 0.000));
		
		TRUE_(a_d2 == D2{0.250, 0.250});

		a_d2 = b_d2;
		TRUE_(a_d2 == D2{0.125, 0.125});
	//	TRUE_(a_d2 == D2{0x40000000, 0x40000000});

	}
	TRY_("multiplication")
	{
		T_alpha x = 1/3.L, x_dt = _op::haplo_f(4);
		U_phi phi{x, x_dt};
		V_phi foo{x};

		for (T_sigma i = 0; i < 0x08; ++i) {
			T_alpha const u = -_std::pow(two, 1 + _op::mantissa_f(mt19937_f));
			phi *= u;
			foo *= u;
			foo -= _std::round(foo);
		//	echo(i, _std::log(_std::abs(phi(0)/foo - foo/phi(0))));
			TRUE_(computrim_f<16>(phi(0)) == computrim_f<16>(foo));
		}
	}
	/**/
	TRY_("trial")
	{
		EST_("multiplication (fixed-point)")
		{
			T_alpha x = 0.33, x_dt = _op::haplo_f(4);

			U_phi   phi{x, x_dt};
		//	T_alpha foo{x};

			for (T_sigma i = 0x100; ~--i;) {
				T_alpha const u = _std::pow(two, 1 + _op::mantissa_f(mt19937_f));
				phi *= u;
			}
			return phi;
		};
		EST_("multiplication (floating-point)")
		{
			T_alpha x = 0.33, x_dt = _op::haplo_f(4);

		//	U_phi   phi{x, x_dt};
			T_alpha foo{x};

			for (T_sigma i = 0x100; ~--i;) {
				T_alpha const u = _std::pow(two, 1 + _op::mantissa_f(mt19937_f));
				foo *= u;
				foo -= _std::round(foo);
			}
			return foo;
		};
	}
	/***/
	TRY_("addition")
	{
		T_alpha x =  0.33, x_dt = _op::haplo_f(4);
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
