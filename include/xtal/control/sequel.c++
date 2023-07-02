#pragma once
#include "./any.c++"
#include "./sequel.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::control::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/control/sequel.hpp: interconversion")
{
	using sequel_n = sequel_t<counter_t<>>;
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
	using sequel_n = sequel_t<counter_t<>>; auto seq_n = sequel_n(3);
	using sequel_u = sequel_t<counted_t<>>; auto seq_u = sequel_u(3);

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

	REQUIRE(seq_n.skip(0).slice(0, 11) == sequel_n(11, 7));
	REQUIRE(seq_n.skip(0).slice(0, 01) == sequel_n(01, 7));
	REQUIRE(seq_n.skip(1).slice(1, 11) == sequel_n(10, 8));

	REQUIRE(seq_u.skip(0).slice(0, 11) == sequel_u(counted_t<>(77, 88), 7));
	REQUIRE(seq_u.skip(0).slice(0, 01) == sequel_u(counted_t<>(77, 78), 7));
	REQUIRE(seq_u.skip(1).slice(1, 11) == sequel_u(counted_t<>(78, 88), 8));

	seq_n = sequel_n(4, 1);
	seq_n = seq_n.null(); REQUIRE(seq_n == sequel_n(0, 2));

}

////////////////////////////////////////////////////////////////////////////////

template <typename Y, typename X>
void test__initialization(auto n)
{
	X x; Y y;
	x = X(n); y = Y(0); REQUIRE(y.efflux(x) == 0); REQUIRE(y.step() == 0); REQUIRE(y.size() == n);
	x = X(n); y = Y(n); REQUIRE(y.efflux(x) == 1); REQUIRE(y.step() == 0); REQUIRE(y.size() == n);

}
TEST_CASE("xtal/control/sequel.hpp: initialization")
{
	using sequel_n = sequel_t<counter_t<>>;
	using sequel_u = sequel_t<counted_t<>>;
	using I = typename sequel_u::step_t;

	test__initialization<sequel_u, sequel_u>((I) 3);
	test__initialization<sequel_u, sequel_n>((I) 3);
	test__initialization<sequel_n, sequel_u>((I) 3);
	test__initialization<sequel_n, sequel_n>((I) 3);

}

////////////////////////////////////////////////////////////////////////////////

template <typename Y, typename X>
void test__finalization(auto n)
{
	X x; Y y;
	x = X(n); y = Y(n)       ; REQUIRE(y.influx(x) == 0); REQUIRE(y.step() == 1); REQUIRE(y.size() == 0);
//	x = X(n); y = Y(n).null(); REQUIRE(y.influx(x) == 1); REQUIRE(y.step() == 2); REQUIRE(y.size() == 0);

}
TEST_CASE("xtal/control/sequel.hpp: finalization")
{
	using sequel_n = sequel_t<counter_t<>>;
	using sequel_u = sequel_t<counted_t<>>;
	using I = typename sequel_u::step_t;
	
	test__initialization<sequel_u, sequel_u>((I) 3);
	test__initialization<sequel_u, sequel_n>((I) 3);
	test__initialization<sequel_n, sequel_u>((I) 3);
	test__initialization<sequel_n, sequel_n>((I) 3);

}

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/control/sequel.hpp: intrepidation")
{
	using V = counter_t<>;
	using U = counted_t<>;
	using sequel_n = sequel_t<V>; auto seq_n = sequel_n(3);
	using sequel_u = sequel_t<U>; auto seq_u = sequel_u(3), seq_w = seq_u;

	REQUIRE(seq_w.efflux(seq_u) == 1); REQUIRE(seq_w == sequel_u(U(0, 3), 0));
	seq_w >>= ++seq_u;                 REQUIRE(seq_w == sequel_u(U(3, 6), 1));
	seq_w >>= ++seq_u;                 REQUIRE(seq_w == sequel_u(U(6, 9), 2));

}
TEST_CASE("xtal/control/sequel.hpp: intrepidation from zero")
{
	using V = counter_t<>;
	using U = counted_t<>;
	using sequel_n = sequel_t<V>; auto seq_n = sequel_n(3);
	using sequel_u = sequel_t<U>; auto seq_u = sequel_u(3), seq_w = sequel_u(0);

	REQUIRE(seq_w.efflux(seq_u) == 0); REQUIRE(seq_w == sequel_u(U(0, 3), 0));
	seq_w >>= ++seq_u;                 REQUIRE(seq_w == sequel_u(U(3, 6), 1));
	seq_w >>= ++seq_u;                 REQUIRE(seq_w == sequel_u(U(6, 9), 2));

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename Y, typename X>
void test__interference(auto i)
{
	using V = counter_t<>;
	using U = counted_t<>;

	auto seq_n = X(4);
	auto seq_u = Y(4), seq_w = Y(4*i);

	seq_w >>= seq_n++; REQUIRE(seq_w == Y(U(0, 4), 0));
	
	seq_w >>= seq_n.skip(0).slice(0, 2); REQUIRE(seq_w == Y(U(4, 6), 1));
	seq_w >>= seq_n.skip(1).slice(2, 4); REQUIRE(seq_w == Y(U(6, 8), 2));
	seq_w <<= seq_n++;                   REQUIRE(seq_w == Y(U(4, 8), 1));
	
	seq_w >>= seq_n.skip(0).slice(0, 2); REQUIRE(seq_w == Y(U( 8, 10), 2));
	seq_w >>= seq_n.skip(1).slice(2, 4); REQUIRE(seq_w == Y(U(10, 12), 3));
	seq_w <<= seq_n++;                   REQUIRE(seq_w == Y(U( 8, 12), 2));

}
TEST_CASE("xtal/control/sequel.hpp: interruption")
{
	using V = counter_t<>; using sequel_n = sequel_t<V>;
	using U = counted_t<>; using sequel_u = sequel_t<U>;
	using I = typename sequel_u::step_t;

	for (I i = 0; i <= 1; ++i)
	{
		test__interference<sequel_u, sequel_u>(i);
		test__interference<sequel_u, sequel_n>(i);
		test__interference<sequel_n, sequel_u>(i);
		test__interference<sequel_n, sequel_n>(i);
	}

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/control/sequel.hpp: cycle")
{
	using V = counter_t<size_t>; using sequel_n = sequel_t<V>;
	using U = counted_t<size_t>; using sequel_u = sequel_t<U>;
	size_t constexpr N = 5;

	sequel_n seq_n(N); seq_n *= N;
	sequel_n seq_m = seq_n;

	seq_m += N;
	seq_m -= N;
	REQUIRE(seq_m == seq_n);

	seq_m += 0;
	seq_m -= N;
	REQUIRE(seq_m == seq_n);

	seq_m -= 0;
	seq_m += N;
	REQUIRE(seq_m == seq_n);

	seq_m += 0;
	seq_m -= 0;
	REQUIRE(seq_m == seq_n.null());

}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
