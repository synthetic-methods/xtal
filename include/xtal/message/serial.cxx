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

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/message/serial.hpp: synchronization")
{
	using serial_n = serial_t<countee_t<>>;
	using serial_u = serial_t<counted_t<>>;

	auto cereal_n = serial_n(3);
	auto cereal_u = serial_u(3);
	REQUIRE(cereal_u.size() == cereal_n.size());
	REQUIRE(cereal_u.step() == cereal_n.step());
	REQUIRE(cereal_u == serial_u(counted_t<>(0, 3), 0));
	
	REQUIRE((cereal_n.step() == 0 and cereal_u.front() == 0 and cereal_u.back() == 2));

	++cereal_n;
	++cereal_u;
	REQUIRE(cereal_u.size() == cereal_n.size());
	REQUIRE(cereal_u.step() == cereal_n.step());
	REQUIRE(cereal_u == serial_u(counted_t<>(3, 6), 1));

	cereal_n++;
	cereal_u++;
	REQUIRE(cereal_u.size() == cereal_n.size());
	REQUIRE(cereal_u.step() == cereal_n.step());
	REQUIRE(cereal_u == serial_u(counted_t<>(6, 9), 2));

	cereal_n += 5;
	cereal_u += 5;
	REQUIRE(cereal_u.size() == cereal_n.size());
	REQUIRE(cereal_u.step() == cereal_n.step());
	REQUIRE(cereal_u == serial_u(counted_t<>(9, 14), 3));
	REQUIRE(cereal_u.null() == serial_u(counted_t<>(14, 14), 4));
	REQUIRE(cereal_u.next() == serial_u(counted_t<>(14, 19), 4));
	
	cereal_u = serial_u(11) *= (7);
	REQUIRE(cereal_u == serial_u(counted_t<>(77, 88), 7));

	cereal_n = serial_n(11) *= (7);
	REQUIRE(cereal_n == serial_n(11, 7));

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
