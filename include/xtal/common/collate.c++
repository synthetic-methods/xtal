#pragma once
#include "./collate.hpp"




#include "../any.c++"

XTAL_ENV_(push)
namespace xtal::common::__collate
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
template <int M_pow=1, int N_lim=-1>
XTAL_FZ2 unsquing_y(auto const &w)
XTAL_0EX
{
	using W = XTAL_TYP_(w);
	using _realized = realize<W>;
	if constexpr (M_pow == 0 and alpha_q<W>)
	{	if (_std::is_constant_evaluated())
		{
			auto const n = _realized::template unsquare_y<-1, N_lim>(w);
			auto const u = n*w;
			return couple_t<W, 2>{u, n};
		}
		else
		{	auto const u = _realized::template unsquare_y< 1, N_lim>(w);
			auto const n = u/w;
			return couple_t<W, 2>{u, n};
		}
	}
	else
	{	return _realized::template unsquare_y<M_pow, N_lim>(w);	
	}
}
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/common/collate.hpp: multiplicative construction")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	auto foo = couple_t<alpha_t, 2>{2.0, 0.5};
	auto bar = unsquing_y<0>((alpha_t) 2);
	bar.transmute([&](XTAL_DEF u) XTAL_0FN_(realized::square_y(XTAL_REF_(u))), trim_y<1>);
	REQUIRE(foo == bar);

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/common/collate.hpp: couple")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	auto bar = couple_t<alpha_t, 2>{2.0, 0.5};
	auto foo = bar.reflected<-1>();
	auto baz = foo.reflected<+1>();
	
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
	using scalar_u = scalar_t<alpha_t, N>;
	using series_u = series_t<alpha_t, N>;

	series_u baz(2.0);
	scalar_u bar = reinterpret_cast<scalar_u &>(baz);
	scalar_u foo = {1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7};
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

	auto    constexpr iffy = [](XTAL_DEF w) XTAL_0FN_(trim_y<16>(XTAL_REF_(w)));
	sigma_t constexpr O = 1 << 5;
	sigma_t constexpr N = 1 << 3;
	sigma_t constexpr M = N  - 1;

	using series_s = series_t<aphex_t, O>;
	using series_u = series_t<aphex_t, N>;
	series_s basis(constant_o<-1>);

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

	auto    constexpr iffy = [](XTAL_DEF w) XTAL_0FN_(trim_y<16>(XTAL_REF_(w)));
	sigma_t constexpr N = 1 << 3;
	sigma_t constexpr M = N  - 1;

	using series_u = series_t<aphex_t, N>;
	series_u basis(constant_o<-1>);

	series_u lhs = {0, 1, 2, 0, 0, 0, 0, 0};
	series_u rhs = {1, 0, 1, 0, 0, 0, 0, 0};
	series_u xhs = {0, 1, 2, 1, 2, 0, 0, 0};
	series_u yhs = basis.convolution(lhs, rhs).transmute(iffy);
	REQUIRE(xhs == yhs);

}
/***/
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("xtal/common/collate.hpp: buffer assigment")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	using buffer_u = fluid_t<alpha_t, (1<<7)>;
	using vector_u = _std::vector<alpha_t>;

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

TEST_CASE("xtal/common/collate.hpp: buffer mutation")
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;

	using buffer_u = fluid_t<alpha_t, (1<<7)>;
	using vector_u = _std::vector<alpha_t>;

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
void sluice_operation__test()
{
	using event_u = compose_s<bias_t, compound::confer<int>>;
	using queue_u = sluice_t<event_u, N>;
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
TEST_CASE("xtal/common/collate.hpp: sluice operation")
{
	sluice_operation__test<-1>();
	sluice_operation__test< 4>();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <int N>
void siphon_operation__test()
{
	using event_u = compose_s<bias_t, compound::confer<int>>;
	using queue_u = siphon_t<event_u, N>;
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
TEST_CASE("xtal/common/collate.hpp: siphon operation")
{
//	siphon_operation__test<-1>();
	siphon_operation__test<64>();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void serial_operation__test()
{
	using D = serial_t<int, 4>;

	D d {1000, 100, 10, 1};

	REQUIRE(++d == D {1100, 110, 11, 1});
	REQUIRE(++d == D {1210, 121, 12, 1});
	REQUIRE(++d == D {1331, 133, 13, 1});

}
TEST_CASE("xtal/common/collate.hpp: serial operation")
{
	serial_operation__test();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void serial_multiplication__test()
{
	using D2 = serial_t<int, 2>;
	using D3 = serial_t<int, 3>;
	using D4 = serial_t<int, 4>;
	
	REQUIRE(D2 {           10, 1} * D2 {           20, 2} == D2 {                   200,   40});
	REQUIRE(D3 {      100, 10, 1} * D3 {      200, 20, 2} == D3 {          20000,  4000,  600});
	REQUIRE(D4 {1000, 100, 10, 1} * D4 {2000, 200, 20, 2} == D4 {2000000, 400000, 60000, 8000});

}
TEST_CASE("xtal/common/collate.hpp: serial multiplication")
{
	serial_multiplication__test();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void series_multiplication__test()
{
	using sigma_t = typename realized::sigma_t;
	using alpha_t = typename realized::alpha_t;
	using aphex_t = typename realized::aphex_t;

	using C4 = series_t<aphex_t, 4>;
	using D4 = series_t<alpha_t, 4>;
	
	REQUIRE(C4 {1000, 100, 10, 1} * C4 {2000, 200, 20, 2} == C4 {2000600, 400040, 60002, 8000});
	REQUIRE(D4 {1000, 100, 10, 1} * D4 {2000, 200, 20, 2} == D4 {2000600, 400040, 60002, 8000});
		
}
TEST_CASE("xtal/common/collate.hpp: series multiplication")
{
	series_multiplication__test();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void phasor_operation__test()
{
	using P = serial_t<float, 2>;
	P p {0.125, 0.250};

	REQUIRE(p++ == P {+0.125, 0.250});
	REQUIRE(p++ == P {+0.375, 0.250});
	REQUIRE(p++ == P {-0.375, 0.250});
	REQUIRE(p++ == P {-0.125, 0.250});

}
TEST_CASE("xtal/common/collate.hpp: phasor operation")
{
	phasor_operation__test();

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void phasor_iteration__test()
{
	using namespace _v3;
	using P  = serial_t<float, 2>;
	using Ps = ranges::iota_view<P>;
	using Qs = _std::vector<float>;

	Ps ps(P {0.125, 0.250});
	Qs qs;
	for (auto p: ps|views::take(4)) qs.push_back(p[0]);
	
	REQUIRE(qs == Qs {+0.125, +0.375, -0.375, -0.125});

//	TODO: Is there a way to reset/change the phase/frequency by mutation (or otherwise)? \
	If not, just need to wrap as a `process`. \

}
TEST_CASE("xtal/common/collate.hpp: phasor iteration")
{
	phasor_iteration__test();

}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
