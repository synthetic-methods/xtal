#pragma once
#include "./serial.hpp"




#include "../any.cxx"

XTAL_ENV_(push)
namespace xtal::message::__serial
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/message/serial.hpp: interconversion")
{
	using serial_n = serial_t<countee_t<>>;
	using serial_u = serial_t<counted_t<>>;

	auto cereal_n = serial_n(3);
	auto cereal_u = serial_u(3);

	++cereal_n; cereal_u += cereal_n.size(); REQUIRE(3 == cereal_u.front()); REQUIRE(3 + (3 - 1) == cereal_u.back());
	++cereal_n; cereal_u += cereal_n.size(); REQUIRE(6 == cereal_u.front()); REQUIRE(6 + (3 - 1) == cereal_u.back());
	++cereal_n; cereal_u += cereal_n.size(); REQUIRE(9 == cereal_u.front()); REQUIRE(9 + (3 - 1) == cereal_u.back());

	cereal_n += 4; cereal_u += cereal_n.size(); REQUIRE(12 == cereal_u.front()); REQUIRE(12 + (4 - 1) == cereal_u.back());
	cereal_n += 5; cereal_u += cereal_n.size(); REQUIRE(16 == cereal_u.front()); REQUIRE(16 + (5 - 1) == cereal_u.back());
	cereal_n += 6; cereal_u += cereal_n.size(); REQUIRE(21 == cereal_u.front()); REQUIRE(21 + (6 - 1) == cereal_u.back());

	REQUIRE((int) cereal_n.size() == (int) cereal_u.size());
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
