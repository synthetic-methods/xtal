#pragma once
#include "./any.c++"
#include "./collate.hpp"// testing...

#include "./collage.hpp"



XTAL_ENV_(push)
namespace xtal::common::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
template <int N>
void test__spool_operation()
{
	using event_u = compose_s<bias_t, concord::lift<int>>;
	using queue_u = typename collage_t<event_u, N>::spool_t;
	queue_u q {(event_u) _std::numeric_limits<int>::max()};

	auto e1 = event_u(1, bias_t(-1.0));
	auto e2 = event_u(2, bias_t(-2.0));
	REQUIRE(e1 < e2);
	REQUIRE(2 == e2.head());
	REQUIRE(1 == e1.head());
	
	REQUIRE(0 == q.size());
	q.push(e1); REQUIRE(1 == q.size());
	q.push(e2); REQUIRE(2 == q.size());
	REQUIRE(-1.0 == q.peek().core()); q.advance(1); REQUIRE(1 == q.size());
	REQUIRE(-2.0 == q.peek().core()); q.advance(1); REQUIRE(0 == q.size());

}
TEST_CASE("xtal/common/collate.hpp: spool operation")
{
//	test__spool_operation<-1>();
	test__spool_operation<64>();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/common/collate.hpp: scalar construction")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	auto foo = typename collage_t<alpha_t, 2>::scalar_t {2.0, 0.5};
	auto bar = realized::template unsquare_y<0>((alpha_t) 2);
	bar.transmute([] XTAL_1FN_(realized::square_y), trim_y<1>);
	REQUIRE(foo == bar);

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/common/collate.hpp: scalar transformation")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	auto bar = typename collage_t<alpha_t, 2>::scalar_t {2.0, 0.5};
	auto foo = bar.reflected(-1);
	auto baz = foo.reflected(+1);
	
	REQUIRE(trim_y<19>(foo[0]) == 1.25);
	REQUIRE(trim_y<19>(foo[1]) == 0.75);
	REQUIRE(trim_y<19>(baz[0]) == bar[0]);
	REQUIRE(trim_y<19>(baz[1]) == bar[1]);

}
/***/
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("xtal/common/collate.hpp: series initialization")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	sigma_t constexpr N = 1 << 3;
	using group_u = typename collage_t<alpha_t, N>::group_t;
	using series_u = typename collage_t<alpha_t, N>::series_t;

	series_u baz(2.0);
	group_u bar = reinterpret_cast<group_u &>(baz);
	group_u foo = {1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7};
	REQUIRE(_v3::ranges::equal(foo, bar));
	
//	foo += bar;
//	foo -= 1;
//	foo -= {0, 1, 3, 7, 15, 31, 63, 127};
//	REQUIRE(foo == bar);

}
TEST_CASE("xtal/common/collate.hpp: series transformation")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;
	using aphex_t = typename realized::aphex_t;

	auto    constexpr iffy = [] XTAL_1FN_(trim_y<16>);
	sigma_t constexpr O = 1 << 5;
	sigma_t constexpr N = 1 << 3;
	sigma_t constexpr M = N  - 1;

	using series_s = typename collage_t<aphex_t, O>::series_t;
	using series_u = typename collage_t<aphex_t, N>::series_t;
	series_s basis(constant_t<-1>{});

	series_u source;
	source[0] = source[M - 0] = aphex_t(0.0, 0.0);
	source[1] = source[M - 1] = aphex_t(1.0, 1.0);
	source[2] = source[M - 2] = aphex_t(3.0, 3.0);
	source[3] = source[M - 3] = aphex_t(4.0, 4.0);

	auto target = basis.transformation(source).transmute(iffy);
	REQUIRE(target[0] == iffy(aphex_t( 0.1600000000000000e+2,  0.1600000000000000e+2)));
	REQUIRE(target[1] == iffy(aphex_t(-0.4828427124746192e+1, -0.1165685424949238e+2)));
	REQUIRE(target[2] == iffy(aphex_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
	REQUIRE(target[3] == iffy(aphex_t(-0.3431457505076203e+0,  0.8284271247461885e+0)));
	REQUIRE(target[4] == iffy(aphex_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
	REQUIRE(target[5] == iffy(aphex_t( 0.8284271247461912e+0, -0.3431457505076203e+0)));
	REQUIRE(target[6] == iffy(aphex_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
	REQUIRE(target[7] == iffy(aphex_t(-0.1165685424949238e+2, -0.4828427124746188e+1)));

}
/**/
TEST_CASE("xtal/common/collate.hpp: series convolution")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;
	using aphex_t = typename realized::aphex_t;

	auto    constexpr iffy = [] XTAL_1FN_(trim_y<16>);
	sigma_t constexpr N = 1 << 3;
	sigma_t constexpr M = N  - 1;

	using series_u = typename collage_t<aphex_t, N>::series_t;
	series_u basis(constant_t<-1>{});

	series_u lhs = {0, 1, 2, 0, 0, 0, 0, 0};
	series_u rhs = {1, 0, 1, 0, 0, 0, 0, 0};
	series_u xhs = {0, 1, 2, 1, 2, 0, 0, 0};
	series_u yhs = basis.convolution(lhs, rhs).transmute(iffy);
	REQUIRE(xhs == yhs);

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void test__serial_multiplication()
{
	using D2 = typename collage_t<int, 2>::serial_t;
	using D3 = typename collage_t<int, 3>::serial_t;
	using D4 = typename collage_t<int, 4>::serial_t;
	
	REQUIRE(D2 {           10, 1} * D2 {           20, 2} == D2 {                   200,   40});
	REQUIRE(D3 {      100, 10, 1} * D3 {      200, 20, 2} == D3 {          20000,  4000,  600});
	REQUIRE(D4 {1000, 100, 10, 1} * D4 {2000, 200, 20, 2} == D4 {2000000, 400000, 60000, 8000});

	REQUIRE(D2 {1, 2} < D2 {3, 4});

}
TEST_CASE("xtal/common/collate.hpp: serial multiplication")
{
	test__serial_multiplication();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void test__series_multiplication()
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;
	using aphex_t = typename realized::aphex_t;

	using C4 = typename collage_t<aphex_t, 4>::series_t;
	using D4 = typename collage_t<aphex_t, 4>::series_t;
	
	REQUIRE(C4 {1000, 100, 10, 1} * C4 {2000, 200, 20, 2} == C4 {2000600, 400040, 60002, 8000});
	REQUIRE(D4 {1000, 100, 10, 1} * D4 {2000, 200, 20, 2} == D4 {2000600, 400040, 60002, 8000});
		
}
TEST_CASE("xtal/common/collate.hpp: series multiplication")
{
	test__series_multiplication();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void test__pulsar_operation()
{
	using D = typename collage_t<int, 4>::pulsar_t;

	D d {1000, 100, 10, 1};

	REQUIRE(++d == D {1100, 110, 11, 1});
	REQUIRE(++d == D {1210, 121, 12, 1});
	REQUIRE(++d == D {1331, 133, 13, 1});

}
TEST_CASE("xtal/common/collate.hpp: pulsar operation")
{
	test__pulsar_operation();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void test__phasor_operation()
{
	using P = typename collage_t<float, 2>::phasor_t;
	P p {0.125, 0.250};

	REQUIRE(p++ == P {+0.125, 0.250});
	REQUIRE(p++ == P {+0.375, 0.250});
	REQUIRE(p++ == P {-0.375, 0.250});
	REQUIRE(p++ == P {-0.125, 0.250});

}
TEST_CASE("xtal/common/collate.hpp: phasor operation")
{
	test__phasor_operation();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void test__phasor_iteration()
{
	using namespace _v3;
	using P  = typename collage_t<float, 2>::phasor_t;
	using Ps = ranges::iota_view<P>;
	using Qs = _std::vector<float>;

	Ps ps(P {0.125, 0.250});
	Qs qs;
	for (auto p: ps|views::take(4)) qs.push_back(p[0]);
	
	REQUIRE(qs == Qs {+0.125, +0.375, -0.375, -0.125});

//	TODO: Find a way to reset/change the phase/frequency by mutation (or otherwise)? \
	If not, just need to wrap as a `process`. \

}
TEST_CASE("xtal/common/collate.hpp: phasor iteration")
{
	test__phasor_iteration();

}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
