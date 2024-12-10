#pragma once
#include "./any.cc"
#include "./operate.hh"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("operate", "root")
{
	using _op = operating;
	using T_sigma = typename _op::sigma_type;
	using T_delta = typename _op::delta_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;
	auto mt19937_f = typename _op::mt19937_t(Catch::rngSeed());

	TRY_("trial")
	{
		EST_("real root<-1,~0>")
		{
			T_alpha constexpr two = 2;
			T_alpha w{};
			for (T_sigma i = 0x100; ~--i;) {
				auto x = _op::mantissa_f(mt19937_f); x = _std::pow(two, x);
				w *= _op::root_f<-1,~0>(x)/0x100;
			}
			return w;
		};
		EST_("real root<-1, 1>")
		{
			T_alpha constexpr two = 2;
			T_alpha w{};
			for (T_sigma i = 0x100; ~--i;) {
				auto x = _op::mantissa_f(mt19937_f); x = _std::pow(two, x);
				w *= _op::root_f<-1, 1>(x)/0x100;
			}
			return w;
		};
	};
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

TAG_("operate", "exponential")
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
		TRUE_(_op::exponential_f(0.1) == -4);
		TRUE_(_op::exponential_f(0.2) == -3);
		TRUE_(_op::exponential_f(0.3) == -2);
		TRUE_(_op::exponential_f(0.4) == -2);
		TRUE_(_op::exponential_f(0.5) == -1);
		TRUE_(_op::exponential_f(0.6) == -1);
		TRUE_(_op::exponential_f(0.7) == -1);
		TRUE_(_op::exponential_f(0.8) == -1);
		TRUE_(_op::exponential_f(0.9) == -1);
		TRUE_(_op::exponential_f(1.0) ==  0);
		TRUE_(_op::exponential_f(2.0) ==  1);
		TRUE_(_op::exponential_f(3.0) ==  1);
		TRUE_(_op::exponential_f(4.0) ==  2);
		TRUE_(_op::exponential_f(5.0) ==  2);
		TRUE_(_op::exponential_f(6.0) ==  2);
		TRUE_(_op::exponential_f(7.0) ==  2);
		TRUE_(_op::exponential_f(8.0) ==  3);
		TRUE_(_op::exponential_f(9.0) ==  3);

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
		
		TRUE_(check_f<- 6>(0.2220, _op::haplo_f()*T_alpha(_op::fractional_f(222.2220))));
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
			w ^= _op::fractional_f(u);
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
