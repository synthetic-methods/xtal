#pragma once
#include "./any.cc"
#include "./bit.hh"// testing...





XTAL_ENV_(push)
namespace xtal::bond::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("bit", "bit_reverse")
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

		TRUE_(answer == bit_reverse_f<3>(question));

	}
	TRY_("16:16")
	{
		using _op = operate<uint16_t>;
		T_sigma question = 0b0100100011100101;
		T_sigma answer   = 0b1010011100010010;

		TRUE_(answer == bit_reverse_f<16>(question));

	}
	TRY_("16:12")
	{
		using _op = operate<uint16_t>;
		T_sigma question = 0b010010001110;
		T_sigma answer   = 0b011100010010;

		TRUE_(answer == bit_reverse_f<12>(question));

	}
	TRY_("8:8")
	{
		using _op = operate<uint8_t>;
		T_sigma question = 0b01001101;
		T_sigma answer   = 0b10110010;

		TRUE_(answer == bit_reverse_f<8>(question));

	}
	TRY_("8:6")
	{
		using _op = operate<uint8_t>;
		T_sigma question = 0b010011;
		T_sigma answer   = 0b110010;

		TRUE_(answer == bit_reverse_f<6>(question));

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("bit_floor_f")
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
		TRUE_(0 == bit_floor_f<0>(0));
		TRUE_(0 == bit_floor_f<0>(1));
		TRUE_(1 == bit_floor_f<0>(2));
		TRUE_(0 == bit_floor_f<0>(0.0));
		TRUE_(0 == bit_floor_f<0>(1.0));
		TRUE_(1 == bit_floor_f<0>(2.0));
	//	TRUE_(bit_floor_f(0.0) == bit_floor_f(0));
		TRUE_(bit_floor_f(1.0) == bit_floor_f(1));
		TRUE_(bit_floor_f(2.0) == bit_floor_f(2));
		TRUE_(bit_floor_f(3.0) == bit_floor_f(3));
		TRUE_(bit_floor_f(4.0) == bit_floor_f(4));
		TRUE_(bit_floor_f(5.0) == bit_floor_f(5));
		TRUE_(bit_floor_f(6.0) == bit_floor_f(6));
		TRUE_(bit_floor_f(7.0) == bit_floor_f(7));
		TRUE_(bit_floor_f(8.0) == bit_floor_f(8));
		TRUE_(bit_floor_f(9.0) == bit_floor_f(9));

	//	TRUE_(bit_floor_f(0.0*_op::diplo_1*_op::dnsilon_1) == bit_ceiling_f(0));
		TRUE_(bit_floor_f(1.0*_op::diplo_1*_op::dnsilon_1) == bit_ceiling_f(1));
		TRUE_(bit_floor_f(2.0*_op::diplo_1*_op::dnsilon_1) == bit_ceiling_f(2));
		TRUE_(bit_floor_f(3.0*_op::diplo_1*_op::dnsilon_1) == bit_ceiling_f(3));
		TRUE_(bit_floor_f(4.0*_op::diplo_1*_op::dnsilon_1) == bit_ceiling_f(4));
		TRUE_(bit_floor_f(5.0*_op::diplo_1*_op::dnsilon_1) == bit_ceiling_f(5));
		TRUE_(bit_floor_f(6.0*_op::diplo_1*_op::dnsilon_1) == bit_ceiling_f(6));
		TRUE_(bit_floor_f(7.0*_op::diplo_1*_op::dnsilon_1) == bit_ceiling_f(7));
		TRUE_(bit_floor_f(8.0*_op::diplo_1*_op::dnsilon_1) == bit_ceiling_f(8));
		TRUE_(bit_floor_f(9.0*_op::diplo_1*_op::dnsilon_1) == bit_ceiling_f(9));

	//	TRUE_(bit_ceiling_f(0) == _std::bit_width(0U - 1));
		TRUE_(bit_ceiling_f(1) == _std::bit_width(1U - 1));
		TRUE_(bit_ceiling_f(2) == _std::bit_width(2U - 1));
		TRUE_(bit_ceiling_f(3) == _std::bit_width(3U - 1));
		TRUE_(bit_ceiling_f(4) == _std::bit_width(4U - 1));
		TRUE_(bit_ceiling_f(5) == _std::bit_width(5U - 1));
		TRUE_(bit_ceiling_f(6) == _std::bit_width(6U - 1));
		TRUE_(bit_ceiling_f(7) == _std::bit_width(7U - 1));
		TRUE_(bit_ceiling_f(8) == _std::bit_width(8U - 1));
		TRUE_(bit_ceiling_f(9) == _std::bit_width(9U - 1));

		TRUE_(bit_floor_f(0.1) == -4);
		TRUE_(bit_floor_f(0.2) == -3);
		TRUE_(bit_floor_f(0.3) == -2);
		TRUE_(bit_floor_f(0.4) == -2);
		TRUE_(bit_floor_f(0.5) == -1);
		TRUE_(bit_floor_f(0.6) == -1);
		TRUE_(bit_floor_f(0.7) == -1);
		TRUE_(bit_floor_f(0.8) == -1);
		TRUE_(bit_floor_f(0.9) == -1);
		TRUE_(bit_floor_f(1.0) ==  0);
		TRUE_(bit_floor_f(2.0) ==  1);
		TRUE_(bit_floor_f(3.0) ==  1);
		TRUE_(bit_floor_f(4.0) ==  2);
		TRUE_(bit_floor_f(5.0) ==  2);
		TRUE_(bit_floor_f(6.0) ==  2);
		TRUE_(bit_floor_f(7.0) ==  2);
		TRUE_(bit_floor_f(8.0) ==  3);
		TRUE_(bit_floor_f(9.0) ==  3);

	};
}


////////////////////////////////////////////////////////////////////////////////

TAG_("bit_representation_f")
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
		TRUE_( 2.25 == bit_presentation_f(bit_representation_f( 2.25)));
		TRUE_( 1.25 == bit_presentation_f(bit_representation_f( 1.25)));
		TRUE_( 0.25 == bit_presentation_f(bit_representation_f( 0.25)));
		TRUE_( 0.75 == bit_presentation_f(bit_representation_f( 0.75)));
		TRUE_( 1.75 == bit_presentation_f(bit_representation_f( 1.75)));
		TRUE_( 2.75 == bit_presentation_f(bit_representation_f( 2.75)));

		TRUE_(-2.25 == bit_presentation_f(bit_representation_f(-2.25)));
		TRUE_(-1.25 == bit_presentation_f(bit_representation_f(-1.25)));
		TRUE_(-0.25 == bit_presentation_f(bit_representation_f(-0.25)));
		TRUE_(-0.75 == bit_presentation_f(bit_representation_f(-0.75)));
		TRUE_(-1.75 == bit_presentation_f(bit_representation_f(-1.75)));
		TRUE_(-2.75 == bit_presentation_f(bit_representation_f(-2.75)));

	};
}


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
