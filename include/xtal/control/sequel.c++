#pragma once
#include "./sequel.hpp"




#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::control::__sequel
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/control/sequel.hpp: interconversion")
{
	using sequel_n = sequel_t<countee_t<>>;
	using sequel_u = sequel_t<counted_t<>>;

	auto seq_n = sequel_n(3);
	auto seq_u = sequel_u(3);

	++seq_n; seq_u += seq_n.size(); REQUIRE(3 == seq_u.front()); REQUIRE(3 + (3 - 1) == seq_u.back());
	++seq_n; seq_u += seq_n.size(); REQUIRE(6 == seq_u.front()); REQUIRE(6 + (3 - 1) == seq_u.back());
	++seq_n; seq_u += seq_n.size(); REQUIRE(9 == seq_u.front()); REQUIRE(9 + (3 - 1) == seq_u.back());

	seq_n += 4; seq_u += seq_n.size(); REQUIRE(12 == seq_u.front()); REQUIRE(12 + (4 - 1) == seq_u.back());
	seq_n += 5; seq_u += seq_n.size(); REQUIRE(16 == seq_u.front()); REQUIRE(16 + (5 - 1) == seq_u.back());
	seq_n += 6; seq_u += seq_n.size(); REQUIRE(21 == seq_u.front()); REQUIRE(21 + (6 - 1) == seq_u.back());

	REQUIRE((int) seq_n.size() == (int) seq_u.size());
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/control/sequel.hpp: synchronization")
{
	using sequel_n = sequel_t<countee_t<>>;
	using sequel_u = sequel_t<counted_t<>>;

	auto seq_n = sequel_n(3);
	auto seq_u = sequel_u(3);
	REQUIRE(seq_u.size() == seq_n.size());
	REQUIRE(seq_u.step() == seq_n.step());
	REQUIRE(seq_u == sequel_u(counted_t<>(0, 3), 0));
	
	REQUIRE((seq_n.step() == 0 and seq_u.front() == 0 and seq_u.back() == 2));

	++seq_n;
	++seq_u;
	REQUIRE(seq_u.size() == seq_n.size());
	REQUIRE(seq_u.step() == seq_n.step());
	REQUIRE(seq_u == sequel_u(counted_t<>(3, 6), 1));

	seq_n++;
	seq_u++;
	REQUIRE(seq_u.size() == seq_n.size());
	REQUIRE(seq_u.step() == seq_n.step());
	REQUIRE(seq_u == sequel_u(counted_t<>(6, 9), 2));

	seq_n += 5;
	seq_u += 5;
	REQUIRE(seq_u.size() == seq_n.size());
	REQUIRE(seq_u.step() == seq_n.step());
	REQUIRE(seq_u == sequel_u(counted_t<>(9, 14), 3));
	REQUIRE(seq_u.null() == sequel_u(counted_t<>(14, 14), 4));
	REQUIRE(seq_u.next() == sequel_u(counted_t<>(14, 19), 4));
	
	seq_u = sequel_u(11) *= (7);
	REQUIRE(seq_u == sequel_u(counted_t<>(77, 88), 7));

	seq_n = sequel_n(11) *= (7);
	REQUIRE(seq_n == sequel_n(11, 7));

	REQUIRE(seq_n.trip(0, 0, 11) == sequel_n(11, 7));
	REQUIRE(seq_n.trip(0, 0, 01) == sequel_n(01, 7));
	REQUIRE(seq_n.trip(1, 1, 11) == sequel_n(10, 8));

	REQUIRE(seq_u.trip(0, 0, 11) == sequel_u(counted_t<>(77, 88), 7));
	REQUIRE(seq_u.trip(0, 0, 01) == sequel_u(counted_t<>(77, 78), 7));
	REQUIRE(seq_u.trip(1, 1, 11) == sequel_u(counted_t<>(78, 88), 8));

	seq_n = sequel_n(4, 1);
	seq_n = seq_n.null(); REQUIRE(seq_n == sequel_n(0, 2));

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
