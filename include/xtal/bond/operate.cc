#pragma once
#include "./any.cc"
#include "./operate.hh"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

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
			TRUE_(check_f<16>(_op::fraction_f(u), u - _std::round(u)));
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
