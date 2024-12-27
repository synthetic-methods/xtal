#pragma once
#include "./any.cc"
#include "./phason.hh"// testing...





XTAL_ENV_(push)
namespace xtal::algebra::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("phason")
{
	using U_op = bond::operate<int>;
	using T_op = bond::operate<double>;
	using T_iota  = typename T_op:: iota_type;
	using T_delta = typename T_op::delta_type;
	using T_sigma = typename T_op::sigma_type;
	using T_alpha = typename T_op::alpha_type;
	using T_aphex = typename T_op::aphex_type;
	static constexpr T_alpha two =  2;
	static constexpr T_alpha six =  6;
	static constexpr T_alpha ten = 10;

	auto mt19937_f = T_op::mt19937_t(Catch::rngSeed());

	using V_phi = T_alpha;
	using U_phi = phason_t<V_phi[2]>;
	using W_phi = _std::complex<phason_t<T_alpha[2]>>;
	using A_phi = _std::array<V_phi, 2>;

	using _qp = bond::template operate<typename U_phi::value_type>;

	using D1 = phason_t<T_alpha[1]>;
	using D2 = phason_t<T_alpha[2]>;
	using D3 = phason_t<T_alpha[3]>;
	using D4 = phason_t<T_alpha[4]>;
	
	/**/
	TRY_("phason of complex")
	{
		using M_phi = phason_t<_std::complex<T_alpha>[2]>;
		phason_t<_std::complex<T_alpha>[2]> a{{0.1, 0.2}, {0.3, 0.3}};
		phason_t<_std::complex<T_alpha>[2]> b{{0.1, 0.2}, {0.3, 0.3}};

		++a;
		++a;
		++a;
		TRUE_(check_f<12>(a(0), T_aphex{0.0, 0.1}));

	//	W_phi z = a;
	//	TRUE_(check_f<19>(z.real() (0), 0.0));
	//	TRUE_(check_f<19>(z.imag() (0), 0.1));
	//	TRUE_(check_f<19>(z.real() (1), 0.3));
	//	TRUE_(check_f<19>(z.imag() (1), 0.3));

	}
	/***/
	/**/
	TRY_("complex of phason")
	{
		W_phi a{{0.1, 0.0}, {0.2, 0.0}};
		W_phi b{{0.1, 0.0}, {0.2, 0.0}};
		//\
		W_phi c = 2.0 * a;
		W_phi c = b + a;

		TRUE_(check_f(c.real() (0), 0.2));
		TRUE_(check_f(c.imag() (0), 0.4));

	}
	/***/
	TRY_("construction")
	{
		D2 a_d2{0.250, 0.250};
		D2 b_d2{0.125, 0.125};
		D2 y_d2{0.000, 0.125};
		//\
		D2 z_d2(0.125);
		D2 z_d2{0.125};

		TRUE_(z_d2 == D2{0.125, 0.000});

		TRUE_(y_d2 == D2{0.000, 0.125}); y_d2 <<= {0.250};
		TRUE_(y_d2 == D2{0.000, 0.250}); y_d2 <<= _std::array<T_alpha, 1>{0.500};
		TRUE_(y_d2 == D2{0.000, 0.500}); y_d2 >>= _std::array<T_alpha, 1>{0.333};
		TRUE_(y_d2 == D2{0.333, 0.500});

		TRUE_(computrim_f<8>((2.0*y_d2)(0)) == computrim_f<8>(-0.334));
		TRUE_(computrim_f<8>((2.0*y_d2)(1)) == computrim_f<8>( 0.000));
		
		TRUE_(a_d2 == D2{0.250, 0.250});

		a_d2 = b_d2;
		TRUE_(a_d2 == b_d2); b_d2 = a_d2; ++a_d2[0];
		TRUE_(a_d2 != b_d2); b_d2 = a_d2; ++a_d2[0];
		TRUE_(a_d2 != b_d2); b_d2 = a_d2; ++a_d2[0];
		TRUE_(a_d2 != b_d2); b_d2 = a_d2; ++a_d2[0];
	//	TRUE_(a_d2 == D2{0x40000000, 0x40000000});

		TRUE_(check_f<4>(0.1, phason_t<T_alpha[2]>{0.1, 0.1}(0)));

	}
	TRY_("iteration")
	{
		U_phi   phi{0, T_op::haplo_f(4)};
		auto constexpr N_tip = _qp::sign.mask;
		auto           n_tip = N_tip;

		n_tip ^= N_tip;
		for (int i = 0; i < 0x8; ++i) {
			TRUE_((N_tip&phi[0]) == n_tip);
			++phi;
		}
		n_tip ^= N_tip;
		for (int i = 0; i < 0x8; ++i) {
			TRUE_((N_tip&phi[0]) == n_tip);
			++phi;
		}
		n_tip ^= N_tip;
		for (int i = 0; i < 0x8; ++i) {
			TRUE_((N_tip&phi[0]) == n_tip);
			++phi;
		}
		n_tip ^= N_tip;
		for (int i = 0; i < 0x8; ++i) {
			TRUE_((N_tip&phi[0]) == n_tip);
			++phi;
		}

	}
	TRY_("addition")
	{
		T_alpha x =  0.33, x_dt = T_op::haplo_f(4);
		T_alpha y =  5.55;
		T_alpha z =  x+y; z -= _std::round(z);

		U_phi phi{x, x_dt};

		phi += y;
	//	TRUE_(bond::computrim_f<8>(phi[0]) == bond::computrim_f<8>(z));
		TRUE_(bond::computrim_f<8>(phi(0)) == bond::computrim_f<8>(z));

	}
	TRY_("multiplication")
	{
		T_alpha x = 1/3.L, x_dt = T_op::haplo_f(4);
		U_phi phi{x, x_dt};
		V_phi foo{x};

		for (T_sigma i = 0; i < 0x4; ++i) {
			auto const v = static_cast<T_alpha>(i + 1);
			auto const u{exp(asinh(v*T_op::haplo_1))};
			phi *= u;
			foo *= u;
			foo -= _std::round(foo);
			TRUE_(check_f<8>(phi(0), foo));
		}

	}
	/**/
	TRY_("trial")
	{
		EST_("multiplication (fixed-point)")
		{
			T_alpha x = 0.33, x_dt = T_op::haplo_f(4);

			U_phi   phi{x, x_dt};
		//	T_alpha foo{x};

			for (T_sigma i = 0x100; ~--i;) {
				T_alpha const u = _std::pow(two, 1 + T_op::mantissa_f(mt19937_f));
				phi *= u;
			}
			return phi;
		};
		EST_("multiplication (floating-point)")
		{
			T_alpha x = 0.33, x_dt = T_op::haplo_f(4);

		//	U_phi   phi{x, x_dt};
			T_alpha foo{x};

			for (T_sigma i = 0x100; ~--i;) {
				T_alpha const u = _std::pow(two, 1 + T_op::mantissa_f(mt19937_f));
				foo *= u;
				foo -= _std::round(foo);
			}
			return foo;
		};
	}
	/***/
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
