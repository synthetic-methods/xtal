#pragma once
#include "./buffer.hpp"
#include "../message/numinal.hpp"



#include <catch2/catch_all.hpp>

XTAL_ENV_(push)
namespace xtal::any::_test::buffer
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using bias_t = message::numinal_t<alpha_t, struct bias>;

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/any/buffer.hpp: vector assigment")
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

TEST_CASE("xtal/any/buffer.hpp: vector mutation")
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
	REQUIRE(-1.0 == q.top().tail().head()); q.pop(); REQUIRE(1 == q.size());
	REQUIRE(-2.0 == q.top().tail().head()); q.pop(); REQUIRE(0 == q.size());

	REQUIRE(0 == q.size());
	q.push(e2); REQUIRE(1 == q.size());
	q.push(e1); REQUIRE(2 == q.size());
	REQUIRE(-1.0 == q.top().tail().head()); q.pop(); REQUIRE(1 == q.size());
	REQUIRE(-2.0 == q.top().tail().head()); q.pop(); REQUIRE(0 == q.size());

}
TEST_CASE("xtal/any/buffer.hpp: queue operation")
{
	buffer_queue_operation__test<-1>();
	buffer_queue_operation__test<16>();

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
