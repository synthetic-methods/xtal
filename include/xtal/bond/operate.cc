#pragma once
#include "./any.cc"
#include "./operate.hh"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "bit_reverse")
{
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


	TRY_("32:03")
	{
		using _op = operate<uint32_t>;
		T_sigma question = 0b011;
		T_sigma answer   = 0b110;

		TRUE_(answer == _op::bit_reverse_f<3>(question));

	}
	TRY_("16:16")
	{
		using _op = operate<uint16_t>;
		T_sigma question = 0b0100100011100101;
		T_sigma answer   = 0b1010011100010010;

		TRUE_(answer == _op::bit_reverse_f<16>(question));

	}
	TRY_("16:12")
	{
		using _op = operate<uint16_t>;
		T_sigma question = 0b010010001110;
		T_sigma answer   = 0b011100010010;

		TRUE_(answer == _op::bit_reverse_f<12>(question));

	}
	TRY_("8:8")
	{
		using _op = operate<uint8_t>;
		T_sigma question = 0b01001101;
		T_sigma answer   = 0b10110010;

		TRUE_(answer == _op::bit_reverse_f<8>(question));

	}
	TRY_("8:6")
	{
		using _op = operate<uint8_t>;
		T_sigma question = 0b010011;
		T_sigma answer   = 0b110010;

		TRUE_(answer == _op::bit_reverse_f<6>(question));

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "bit_reverse")
{
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


	TRY_("4")
	{
		TRUE_(_op::ratio_f(1, 4) == 0.25);
		TRUE_(_op::ratio_f(2, 4) == 0.50);
		TRUE_(_op::ratio_f(3, 4) == 0.75);
		TRUE_(_op::ratio_f(4, 4) == 1.00);
	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "bit_floor_f")
{
	using _op = operating;
	using T_iota  = typename _op:: iota_type;
	using T_delta = typename _op::delta_type;
	using T_sigma = typename _op::sigma_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());

	TRY_("trial")
	{
		TRUE_(0 == _op::template bit_floor_f<0>(0));
		TRUE_(0 == _op::template bit_floor_f<0>(1));
		TRUE_(1 == _op::template bit_floor_f<0>(2));
		TRUE_(0 == _op::template bit_floor_f<0>(0.0));
		TRUE_(0 == _op::template bit_floor_f<0>(1.0));
		TRUE_(1 == _op::template bit_floor_f<0>(2.0));
	//	TRUE_(_op::bit_floor_f(0.0) == _op::bit_floor_f(0));
		TRUE_(_op::bit_floor_f(1.0) == _op::bit_floor_f(1));
		TRUE_(_op::bit_floor_f(2.0) == _op::bit_floor_f(2));
		TRUE_(_op::bit_floor_f(3.0) == _op::bit_floor_f(3));
		TRUE_(_op::bit_floor_f(4.0) == _op::bit_floor_f(4));
		TRUE_(_op::bit_floor_f(5.0) == _op::bit_floor_f(5));
		TRUE_(_op::bit_floor_f(6.0) == _op::bit_floor_f(6));
		TRUE_(_op::bit_floor_f(7.0) == _op::bit_floor_f(7));
		TRUE_(_op::bit_floor_f(8.0) == _op::bit_floor_f(8));
		TRUE_(_op::bit_floor_f(9.0) == _op::bit_floor_f(9));

	//	TRUE_(_op::bit_floor_f(0.0*_op::diplo_1*_op::dnsilon_1) == _op::bit_ceiling_f(0));
		TRUE_(_op::bit_floor_f(1.0*_op::diplo_1*_op::dnsilon_1) == _op::bit_ceiling_f(1));
		TRUE_(_op::bit_floor_f(2.0*_op::diplo_1*_op::dnsilon_1) == _op::bit_ceiling_f(2));
		TRUE_(_op::bit_floor_f(3.0*_op::diplo_1*_op::dnsilon_1) == _op::bit_ceiling_f(3));
		TRUE_(_op::bit_floor_f(4.0*_op::diplo_1*_op::dnsilon_1) == _op::bit_ceiling_f(4));
		TRUE_(_op::bit_floor_f(5.0*_op::diplo_1*_op::dnsilon_1) == _op::bit_ceiling_f(5));
		TRUE_(_op::bit_floor_f(6.0*_op::diplo_1*_op::dnsilon_1) == _op::bit_ceiling_f(6));
		TRUE_(_op::bit_floor_f(7.0*_op::diplo_1*_op::dnsilon_1) == _op::bit_ceiling_f(7));
		TRUE_(_op::bit_floor_f(8.0*_op::diplo_1*_op::dnsilon_1) == _op::bit_ceiling_f(8));
		TRUE_(_op::bit_floor_f(9.0*_op::diplo_1*_op::dnsilon_1) == _op::bit_ceiling_f(9));

		TRUE_(_op::bit_floor_f(0.1) == -4);
		TRUE_(_op::bit_floor_f(0.2) == -3);
		TRUE_(_op::bit_floor_f(0.3) == -2);
		TRUE_(_op::bit_floor_f(0.4) == -2);
		TRUE_(_op::bit_floor_f(0.5) == -1);
		TRUE_(_op::bit_floor_f(0.6) == -1);
		TRUE_(_op::bit_floor_f(0.7) == -1);
		TRUE_(_op::bit_floor_f(0.8) == -1);
		TRUE_(_op::bit_floor_f(0.9) == -1);
		TRUE_(_op::bit_floor_f(1.0) ==  0);
		TRUE_(_op::bit_floor_f(2.0) ==  1);
		TRUE_(_op::bit_floor_f(3.0) ==  1);
		TRUE_(_op::bit_floor_f(4.0) ==  2);
		TRUE_(_op::bit_floor_f(5.0) ==  2);
		TRUE_(_op::bit_floor_f(6.0) ==  2);
		TRUE_(_op::bit_floor_f(7.0) ==  2);
		TRUE_(_op::bit_floor_f(8.0) ==  3);
		TRUE_(_op::bit_floor_f(9.0) ==  3);

	};
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "assigned_f")
{
	using _op = operating;
	using T_iota  = typename _op:: iota_type;
	using T_delta = typename _op::delta_type;
	using T_sigma = typename _op::sigma_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());

	TRY_("assigned_f( 1)")
	{
		TRUE_( 1. == _op::assigned_f(T_sigma{ 1}));
		TRUE_( 1. == _op::assigned_f(T_delta{ 1}));
		TRUE_( 1. == _op::assigned_f(T_alpha{ 1}));
		TRUE_( 1. == _op::assigned_f(true));

	};
	TRY_("assigned_f( 0)")
	{
		TRUE_(-1. == _op::assigned_f(T_sigma{ 0}));
		TRUE_(-1. == _op::assigned_f(T_delta{ 0}));
	//	TRUE_(-1. == _op::assigned_f(T_alpha{-0}));
		TRUE_(-1. == _op::assigned_f(false));

	};
	TRY_("assigned_f(-1)")
	{
		TRUE_(-1. == _op::assigned_f(T_delta{-1}));
		TRUE_(-1. == _op::assigned_f(T_alpha{-1}));

	};
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "semifractional")
{
	using _op = operating;
	using T_iota  = typename _op:: iota_type;
	using T_delta = typename _op::delta_type;
	using T_sigma = typename _op::sigma_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());

	TRY_("trial")
	{
		using _qp = bond::operate<T_iota>;
		
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-00), (+123456789.0e-00) - round(+123456789.0e-00)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-01), (+123456789.0e-01) - round(+123456789.0e-01)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-02), (+123456789.0e-02) - round(+123456789.0e-02)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-03), (+123456789.0e-03) - round(+123456789.0e-03)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-04), (+123456789.0e-04) - round(+123456789.0e-04)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-05), (+123456789.0e-05) - round(+123456789.0e-05)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-06), (+123456789.0e-06) - round(+123456789.0e-06)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-07), (+123456789.0e-07) - round(+123456789.0e-07)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-08), (+123456789.0e-08) - round(+123456789.0e-08)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-09), (+123456789.0e-09) - round(+123456789.0e-09)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-10), (+123456789.0e-10) - round(+123456789.0e-10)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-11), (+123456789.0e-11) - round(+123456789.0e-11)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-12), (+123456789.0e-12) - round(+123456789.0e-12)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-13), (+123456789.0e-13) - round(+123456789.0e-13)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-14), (+123456789.0e-14) - round(+123456789.0e-14)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-15), (+123456789.0e-15) - round(+123456789.0e-15)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-16), (+123456789.0e-16) - round(+123456789.0e-16)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-17), (+123456789.0e-17) - round(+123456789.0e-17)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-18), (+123456789.0e-18) - round(+123456789.0e-18)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+123456789.0e-19), (+123456789.0e-19) - round(+123456789.0e-19)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(+000000000.0e-09), (+000000000.0e-09) - round(+000000000.0e-09)));
		echo();
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-00), (-123456789.0e-00) - round(-123456789.0e-00)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-01), (-123456789.0e-01) - round(-123456789.0e-01)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-02), (-123456789.0e-02) - round(-123456789.0e-02)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-03), (-123456789.0e-03) - round(-123456789.0e-03)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-04), (-123456789.0e-04) - round(-123456789.0e-04)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-05), (-123456789.0e-05) - round(-123456789.0e-05)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-06), (-123456789.0e-06) - round(-123456789.0e-06)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-07), (-123456789.0e-07) - round(-123456789.0e-07)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-08), (-123456789.0e-08) - round(-123456789.0e-08)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-09), (-123456789.0e-09) - round(-123456789.0e-09)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-10), (-123456789.0e-10) - round(-123456789.0e-10)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-11), (-123456789.0e-11) - round(-123456789.0e-11)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-12), (-123456789.0e-12) - round(-123456789.0e-12)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-13), (-123456789.0e-13) - round(-123456789.0e-13)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-14), (-123456789.0e-14) - round(-123456789.0e-14)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-15), (-123456789.0e-15) - round(-123456789.0e-15)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-16), (-123456789.0e-16) - round(-123456789.0e-16)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-17), (-123456789.0e-17) - round(-123456789.0e-17)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-18), (-123456789.0e-18) - round(-123456789.0e-18)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-123456789.0e-19), (-123456789.0e-19) - round(-123456789.0e-19)));
		TRUE_(check_f<-1>(_op::haplo_f()*_op::bit_fraction_f(-000000000.0e-09), (-000000000.0e-09) - round(-000000000.0e-09)));
		echo();

	};
}


////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "fraction")
{
	using _op = operating;
	using T_iota  = typename _op:: iota_type;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());


	static constexpr T_alpha two =  2;
	static constexpr T_alpha ten = 10;


	TRY_("comparing implementations")
	{
		for (T_sigma i = 0x100; ~--i;) {
			T_alpha const u = ten*_op::mantissa_f(mt19937_f);
			TRUE_(computrim_f<16>(_op::fraction_f(u)) == computrim_f<16>(u - _std::round(u)));
		}
	};
	EST_("wrap via integral arithmetic")
	{
		T_delta w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto const u = ten*_op::mantissa_f(mt19937_f);
			w ^= _op::bit_fraction_f(u);
		}
		return w;
	};
	EST_("wrap via floating-point arithmetic")
	{
		T_alpha w{};
		for (T_sigma i = 0x100; ~--i;) {
			auto const u = ten*_op::mantissa_f(mt19937_f);
			w *= u - _std::round(u);
		}
		return w;
	};
}


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
