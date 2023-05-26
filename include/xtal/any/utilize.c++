#pragma once
#include "./utilize.hpp"




#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::any::__utilize
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/any/utilize.hpp#bit_reverse 32:03")
{
	using realized = realize<uint32_t>;
	using sigma_t = typename realized::sigma_t;

	sigma_t question = 0b011;
	sigma_t answer   = 0b110;

	REQUIRE(answer == bit_reverse_x<3>(question));

}
TEST_CASE("xtal/any/utilize.hpp#bit_reverse 16:16")
{
	using realized = realize<uint16_t>;
	using sigma_t = typename realized::sigma_t;

	sigma_t question = 0b0100100011100101;
	sigma_t answer   = 0b1010011100010010;

	REQUIRE(answer == bit_reverse_x<16>(question));

}
TEST_CASE("xtal/any/utilize.hpp#bit_reverse 16:12")
{
	using realized = realize<uint16_t>;
	using sigma_t = typename realized::sigma_t;

	sigma_t question = 0b010010001110;
	sigma_t answer   = 0b011100010010;

	REQUIRE(answer == bit_reverse_x<12>(question));

}
TEST_CASE("xtal/any/utilize.hpp#bit_reverse 8:8")
{
	using realized = realize<uint8_t>;
	using sigma_t = typename realized::sigma_t;

	sigma_t question = 0b01001101;
	sigma_t answer   = 0b10110010;

	REQUIRE(answer == bit_reverse_x<8>(question));

}
TEST_CASE("xtal/any/utilize.hpp#bit_reverse 8:6")
{
	using realized = realize<uint8_t>;
	using sigma_t = typename realized::sigma_t;

	sigma_t question = 0b010011;
	sigma_t answer   = 0b110010;

	REQUIRE(answer == bit_reverse_x<6>(question));

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
