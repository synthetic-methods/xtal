#pragma once
#include "./collected.hpp"




#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::block::__collected
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
			return parallel_t<2, W>{u, n};
		}
		else
		{	auto const u = realized::template unsquare_y< 1, N_lim>(w);
			auto const n = u/w;
			return parallel_t<2, W>{u, n};
		}
	}
	else
	{	return realized::template unsquare_y<M_pow, N_lim>(w);	
	}
}
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/block/collected.hpp: multiplicative construction")
{
	auto foo = parallel_t<2, alpha_t>{2.0, 0.5};
	auto bar = unsquing_y<0>((alpha_t) 2);
	bar.transmute([&](XTAL_DEF u) XTAL_0FN_(realized::square_y(XTAL_REF_(u))), trim_y<1>);
	REQUIRE(foo == bar);

}
/***/
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/block/collected.hpp: converse")
{
	auto bar = converse_t<alpha_t, 1>{2.0, 0.5};
	auto foo = ~bar;
	auto baz = ~foo;
	REQUIRE(foo[0] == 1.25);
	REQUIRE(foo[1] == 0.75);
	REQUIRE(bar[0] == bar[0]);
	REQUIRE(bar[1] == bar[1]);

}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("xtal/block/collected.hpp: series initialization")
{
	sigma_t constexpr N = 1 << 3;
	using scalar_u = scalar_t<N, alpha_t>;
	using series_u = series_t<N, alpha_t>;

	series_u baz(2.0);
	scalar_u bar = reinterpret_cast<scalar_u &>(baz);
	scalar_u foo = {1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7};
	REQUIRE(_v3::ranges::equal(foo, bar));
	
//	foo += bar;
//	foo -= 1;
//	foo -= {0, 1, 3, 7, 15, 31, 63, 127};
//	REQUIRE(foo == bar);

}
TEST_CASE("xtal/block/collected.hpp: series transformation")
{
	auto    constexpr iffy = [](XTAL_DEF w) XTAL_0FN_(trim_y<16>(XTAL_REF_(w)));
	sigma_t constexpr O = 1 << 5;
	sigma_t constexpr N = 1 << 3;
	sigma_t constexpr M = N  - 1;

	using series_s = series_t<O, aleph_t>;
	using series_u = series_t<N, aleph_t>;
	series_s basis(true);

	series_u source;
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
/**/
TEST_CASE("xtal/block/collected.hpp: series convolution")
{
	auto    constexpr iffy = [](XTAL_DEF w) XTAL_0FN_(trim_y<16>(XTAL_REF_(w)));
	sigma_t constexpr N = 1 << 3;
	sigma_t constexpr M = N  - 1;

	using series_u = series_t<N, aleph_t>;
	series_u basis(true);

	series_u lhs = {0, 1, 2, 0, 0, 0, 0, 0};
	series_u rhs = {1, 0, 1, 0, 0, 0, 0, 0};
	series_u xhs = {0, 1, 2, 1, 2, 0, 0, 0};
	series_u yhs = basis.convolution(lhs, rhs).transmute(iffy);
	REQUIRE(xhs == yhs);

}
/***/
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/block/collected.hpp: buffer assigment")
{
	using buffer_u = buffer_t<(1<<7), realized::alpha_t>;
	using vector_u = _std::vector<realized::alpha_t>;

	auto const zhs = buffer_u {7, 8, 9};
	auto       yhs = buffer_u {4, 5, 6};
	auto       xhs = buffer_u {1, 2, 3};
	REQUIRE(_v3::ranges::equal(xhs, vector_u {1, 2, 3}));
	
	xhs = yhs;// copy
	REQUIRE(_v3::ranges::equal(xhs, vector_u {4, 5, 6}));

	xhs = zhs;// copy
	REQUIRE(_v3::ranges::equal(xhs, vector_u {7, 8, 9}));

	xhs = buffer_u {3, 5, 7};// move
	REQUIRE(_v3::ranges::equal(xhs, vector_u {3, 5, 7}));
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/block/collected.hpp: buffer mutation")
{
	using buffer_u = buffer_t<(1<<7), realized::alpha_t>;
	using vector_u = _std::vector<realized::alpha_t>;

	auto xs = buffer_u {0, 1, 2, 3, 4};
	auto x_ = xs.begin();

	xs.erase(x_ + 2);
	REQUIRE(_v3::ranges::equal(xs, vector_u {0, 1, 3, 4}));

	xs.erase(x_ + 1, x_ + 3);
	REQUIRE(_v3::ranges::equal(xs, vector_u {0, 4}));

	xs.insert(x_ + 1, {1, 2, 3});
	REQUIRE(_v3::ranges::equal(xs, vector_u {0, 1, 2, 3, 4}));

	xs.insert(x_ + 4, x_ + 1, x_ + 4);
	REQUIRE(_v3::ranges::equal(xs, vector_u {0, 1, 2, 3, 1, 2, 3, 4}));
}

////////////////////////////////////////////////////////////////////////////////
/**/
template <int N>
void siphon_operation__test()
{
	using event_u = compose_s<bias_t, content::confer<int>>;
	using queue_u = siphon_t<N, event_u>;
	queue_u q;

	auto e1 = event_u(1, bias_t(-1.0));
	auto e2 = event_u(2, bias_t(-2.0));
	REQUIRE(e1 < e2);
	
	REQUIRE(0 == q.size());
	q.push(e1); REQUIRE(1 == q.size());
	q.push(e2); REQUIRE(2 == q.size());
	REQUIRE(-1.0 == q.top().tail()); q.pop(); REQUIRE(1 == q.size());
	REQUIRE(-2.0 == q.top().tail()); q.pop(); REQUIRE(0 == q.size());

}
TEST_CASE("xtal/block/collected.hpp: siphon operation")
{
	siphon_operation__test<-1>();
	siphon_operation__test< 4>();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <int N>
void sluice_operation__test()
{
	using event_u = compose_s<bias_t, content::confer<int>>;
	using queue_u = sluice_t<N, event_u>;
	queue_u q;

	auto e1 = event_u(1, bias_t(-1.0));
	auto e2 = event_u(2, bias_t(-2.0));
	REQUIRE(e1 < e2);
	REQUIRE(2 == e2.head());
	REQUIRE(1 == e1.head());
	
	REQUIRE(0 == q.remaining());
	q.push(e1); REQUIRE(1 == q.remaining());
	q.push(e2); REQUIRE(2 == q.remaining());
	REQUIRE(-1.0 == q.next(0).tail()); q.advance(); REQUIRE(1 == q.remaining());
	REQUIRE(-2.0 == q.next(0).tail()); q.advance(); REQUIRE(0 == q.remaining());

}
TEST_CASE("xtal/block/collected.hpp: sluice operation")
{
//	sluice_operation__test<-1>();
	sluice_operation__test<64>();

}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
