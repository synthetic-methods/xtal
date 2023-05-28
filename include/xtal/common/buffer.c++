#pragma once
#include "./buffer.hpp"
#include "../message/numinal.hpp"



#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::common::__buffer
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/common/buffer.hpp: series initialization")
{
	sigma_t constexpr N = 1 << 3;
	using scalar_t = buffer_scalar_t<N, alpha_t>;
	using series_t = buffer_series_t<N, alpha_t>;

	series_t baz(2.0);
	scalar_t bar; bar.refill(baz);
	scalar_t foo = {1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7};
	REQUIRE(_v3::ranges::equal(foo, bar));
	
	foo += bar;
	foo -= 1;
	foo -= {0, 1, 3, 7, 15, 31, 63, 127};
	REQUIRE(foo == bar);

}
/***/
TEST_CASE("xtal/common/buffer.hpp: series transformation")
{
	auto    constexpr iffy = [] (XTAL_DEF w) XTAL_0FN_(trim_y<16>(XTAL_REF_(w)));
	sigma_t constexpr O = 1 << 5;
	sigma_t constexpr N = 1 << 3;
	sigma_t constexpr M = N  - 1;

	using series_s = buffer_series_t<O, aleph_t>;
	using series_t = buffer_series_t<N, aleph_t>;
	series_s basis(true);

	series_t source;
	source[0] = source[M - 0] = aleph_t(0.0, 0.0);
	source[1] = source[M - 1] = aleph_t(1.0, 1.0);
	source[2] = source[M - 2] = aleph_t(3.0, 3.0);
	source[3] = source[M - 3] = aleph_t(4.0, 4.0);

	series_t target = basis.transformation(source).transmute(iffy);
	REQUIRE(target[0] == iffy(aleph_t( 0.1600000000000000e+2,  0.1600000000000000e+2)));
	REQUIRE(target[1] == iffy(aleph_t(-0.4828427124746192e+1, -0.1165685424949238e+2)));
	REQUIRE(target[2] == iffy(aleph_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
	REQUIRE(target[3] == iffy(aleph_t(-0.3431457505076203e+0,  0.8284271247461885e+0)));
	REQUIRE(target[4] == iffy(aleph_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
	REQUIRE(target[5] == iffy(aleph_t( 0.8284271247461912e+0, -0.3431457505076203e+0)));
	REQUIRE(target[6] == iffy(aleph_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
	REQUIRE(target[7] == iffy(aleph_t(-0.1165685424949238e+2, -0.4828427124746188e+1)));
	REQUIRE(true);
}

TEST_CASE("xtal/common/buffer.hpp: series convolution")
{
	auto    constexpr iffy = [] (XTAL_DEF w) XTAL_0FN_(trim_y<16>(XTAL_REF_(w)));
	sigma_t constexpr N = 1 << 3;
	sigma_t constexpr M = N  - 1;

	using series_t = buffer_series_t<N, aleph_t>;
	series_t basis(true);

	series_t lhs = {0, 1, 2, 0, 0, 0, 0, 0};
	series_t rhs = {1, 0, 1, 0, 0, 0, 0, 0};
	series_t xhs = {0, 1, 2, 1, 2, 0, 0, 0};
	series_t yhs = basis.convolution(lhs, rhs).transmute(iffy);
	REQUIRE(xhs == yhs);

}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/common/buffer.hpp: vector assigment")
{
	using static_vector_t = buffer_vector_t<(1<<7), realized::alpha_t>;
	using        vector_t = _std::vector<realized::alpha_t>;

	auto const zhs = static_vector_t {7, 8, 9};
	auto       yhs = static_vector_t {4, 5, 6};
	auto       xhs = static_vector_t {1, 2, 3};
	REQUIRE(_v3::ranges::equal(xhs, vector_t {1, 2, 3}));
	
	xhs = yhs;// copy
	REQUIRE(_v3::ranges::equal(xhs, vector_t {4, 5, 6}));

	xhs = zhs;// copy
	REQUIRE(_v3::ranges::equal(xhs, vector_t {7, 8, 9}));

	xhs = static_vector_t {3, 5, 7};// move
	REQUIRE(_v3::ranges::equal(xhs, vector_t {3, 5, 7}));
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/common/buffer.hpp: vector mutation")
{
	using static_vector_t = buffer_vector_t<(1<<7), realized::alpha_t>;
	using        vector_t = _std::vector<realized::alpha_t>;

	auto xs = static_vector_t {0, 1, 2, 3, 4};
	auto x_ = xs.begin();

	xs.erase(x_ + 2);
	REQUIRE(_v3::ranges::equal(xs, vector_t {0, 1, 3, 4}));

	xs.erase(x_ + 1, x_ + 3);
	REQUIRE(_v3::ranges::equal(xs, vector_t {0, 4}));

	xs.insert(x_ + 1, {1, 2, 3});
	REQUIRE(_v3::ranges::equal(xs, vector_t {0, 1, 2, 3, 4}));

	xs.insert(x_ + 4, x_ + 1, x_ + 4);
	REQUIRE(_v3::ranges::equal(xs, vector_t {0, 1, 2, 3, 1, 2, 3, 4}));
}

////////////////////////////////////////////////////////////////////////////////

template <iota_t N>
void buffer_queue_operation__test()
{
	using event_t = compose_s<bias_t, content::confer<iota_t>>;
	using stack_t = buffer_vector_t<N, event_t>;
	using queue_t = _std::priority_queue<event_t, stack_t, _std::greater<event_t>>;
	queue_t q;

	auto e1 = event_t(1, bias_t(-1.0));
	auto e2 = event_t(2, bias_t(-2.0));
	REQUIRE(e1 < e2);
	
	REQUIRE(0 == q.size());
	q.push(e1); REQUIRE(1 == q.size());
	q.push(e2); REQUIRE(2 == q.size());
	REQUIRE(-1.0 == q.top().template head<1>()); q.pop(); REQUIRE(1 == q.size());
	REQUIRE(-2.0 == q.top().template head<1>()); q.pop(); REQUIRE(0 == q.size());

	REQUIRE(0 == q.size());
	q.push(e2); REQUIRE(1 == q.size());
	q.push(e1); REQUIRE(2 == q.size());
	REQUIRE(-1.0 == q.top().template head<1>()); q.pop(); REQUIRE(1 == q.size());
	REQUIRE(-2.0 == q.top().template head<1>()); q.pop(); REQUIRE(0 == q.size());

}
TEST_CASE("xtal/common/buffer.hpp: queue operation")
{
	buffer_queue_operation__test<-1>();
	buffer_queue_operation__test<4>();

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
