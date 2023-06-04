#pragma once
#include "./collect.hpp"
#include "../control/numinal.hpp"



#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::common::__collect
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
template <int M_pow=1, int N_lim=-1>
XTAL_FZ2 unsquing_y(auto const &w)
XTAL_0EX
{
	using W = XTAL_TYP_(w);
	using realized = realize<W>;
	if constexpr (M_pow == 0 and _std::floating_point<W>)
	{	if (_std::is_constant_evaluated())
		{
			auto const n = realized::template unsquare_y<-1, N_lim>(w);
			auto const u = n*w;
			return collection_parallel_t<2, W>{u, n};
		}
		else
		{	auto const u = realized::template unsquare_y< 1, N_lim>(w);
			auto const n = u/w;
			return collection_parallel_t<2, W>{u, n};
		}
	}
	else
	{	return realized::template unsquare_y<M_pow, N_lim>(w);	
	}
}
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/common/collect.hpp: multiplicative construction")
{
	auto foo = collection_parallel_t<2, alpha_t>{2.0, 0.5};
	auto bar = unsquing_y<0>((alpha_t) 2);
	bar.transmute([&](XTAL_DEF u) XTAL_0FN_(realized::square_y(XTAL_REF_(u))), trim_y<1>);
	REQUIRE(foo == bar);

}
/***/
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/common/collect.hpp: converse")
{
	auto bar = collection_converse_t<alpha_t, 1>{2.0, 0.5};
	auto foo = ~bar;
	auto baz = ~foo;
	REQUIRE(foo[0] == 1.25);
	REQUIRE(foo[1] == 0.75);
	REQUIRE(bar[0] == bar[0]);
	REQUIRE(bar[1] == bar[1]);

}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/common/collect.hpp: series initialization")
{
	sigma_t constexpr N = 1 << 3;
	using scalar_t = collection_scalar_t<N, alpha_t>;
	using series_t = collection_series_t<N, alpha_t>;

	series_t baz(2.0);
	scalar_t bar; bar.refill(baz);
	scalar_t foo = {1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7};
	REQUIRE(_v3::ranges::equal(foo, bar));
	
//	foo += bar;
//	foo -= 1;
//	foo -= {0, 1, 3, 7, 15, 31, 63, 127};
//	REQUIRE(foo == bar);

}

TEST_CASE("xtal/common/collect.hpp: series transformation")
{
	auto    constexpr iffy = [](XTAL_DEF w) XTAL_0FN_(trim_y<16>(XTAL_REF_(w)));
	sigma_t constexpr O = 1 << 5;
	sigma_t constexpr N = 1 << 3;
	sigma_t constexpr M = N  - 1;

	using series_s = collection_series_t<O, aleph_t>;
	using series_t = collection_series_t<N, aleph_t>;
	series_s basis(true);

	series_t source;
	source[0] = source[M - 0] = aleph_t(0.0, 0.0);
	source[1] = source[M - 1] = aleph_t(1.0, 1.0);
	source[2] = source[M - 2] = aleph_t(3.0, 3.0);
	source[3] = source[M - 3] = aleph_t(4.0, 4.0);

	auto target = basis.transformation(source).transmute(iffy);
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

TEST_CASE("xtal/common/collect.hpp: series convolution")
{
	auto    constexpr iffy = [](XTAL_DEF w) XTAL_0FN_(trim_y<16>(XTAL_REF_(w)));
	sigma_t constexpr N = 1 << 3;
	sigma_t constexpr M = N  - 1;

	using series_t = collection_series_t<N, aleph_t>;
	series_t basis(true);

	series_t lhs = {0, 1, 2, 0, 0, 0, 0, 0};
	series_t rhs = {1, 0, 1, 0, 0, 0, 0, 0};
	series_t xhs = {0, 1, 2, 1, 2, 0, 0, 0};
	series_t yhs = basis.convolution(lhs, rhs).transmute(iffy);
	REQUIRE(xhs == yhs);

}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/common/collect.hpp: buffer assigment")
{
	using buffer_t = collection_buffer_t<(1<<7), realized::alpha_t>;
	using vector_t = _std::vector<realized::alpha_t>;

	auto const zhs = buffer_t {7, 8, 9};
	auto       yhs = buffer_t {4, 5, 6};
	auto       xhs = buffer_t {1, 2, 3};
	REQUIRE(_v3::ranges::equal(xhs, vector_t {1, 2, 3}));
	
	xhs = yhs;// copy
	REQUIRE(_v3::ranges::equal(xhs, vector_t {4, 5, 6}));

	xhs = zhs;// copy
	REQUIRE(_v3::ranges::equal(xhs, vector_t {7, 8, 9}));

	xhs = buffer_t {3, 5, 7};// move
	REQUIRE(_v3::ranges::equal(xhs, vector_t {3, 5, 7}));
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/common/collect.hpp: buffer mutation")
{
	using buffer_t = collection_buffer_t<(1<<7), realized::alpha_t>;
	using vector_t = _std::vector<realized::alpha_t>;

	auto xs = buffer_t {0, 1, 2, 3, 4};
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
/**/
template <int N>
void collection_siphon_operation__test()
{
	using event_t = compose_s<bias_t, content::confer<int>>;
	using queue_t = collection_siphon_t<N, event_t>;
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
TEST_CASE("xtal/common/collect.hpp: siphon operation")
{
	collection_siphon_operation__test<-1>();
	collection_siphon_operation__test< 4>();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/*/
template <int N>
void collection_sluice_operation__test()
{
	using event_t = compose_s<bias_t, content::confer<int>>;
	using queue_t = collection_sluice_t<N, event_t, 1>;
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
TEST_CASE("xtal/common/collect.hpp: sluice operation")
{
//	collection_sluice_operation__test<-1>();
	collection_sluice_operation__test<64>();

}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
