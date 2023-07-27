#pragma once
#include "./any.c++"
#include "./collate.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::common::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <int N>
void spool__operation()
{
	using event_u = compose_s<onset_t, concord::conferred<int>>;
	using queue_u = typename collate_t<N>::template spool_t<event_u>;
	queue_u q {(event_u) _std::numeric_limits<int>::max()};

	auto e1 = event_u(1, onset_t(-1.0));
	auto e2 = event_u(2, onset_t(-2.0));
	TRUE_(e1 < e2);
	TRUE_(2 == e2.head());
	TRUE_(1 == e1.head());
	
	TRUE_(0 == q.size());
	q.push(e1); TRUE_(1 == q.size());
	q.push(e2); TRUE_(2 == q.size());
	TRUE_(-1.0 == q.peek().core()); q.advance(1); TRUE_(1 == q.size());
	TRUE_(-2.0 == q.peek().core()); q.advance(1); TRUE_(0 == q.size());

}
TAG_("collate", "spool")
{
	TRY_("operation fluid") {spool__operation<-1>();}
	TRY_("operation fixed") {spool__operation<64>();}

}


////////////////////////////////////////////////////////////////////////////////

TAG_("collate", "scalar")
{
	TRY_("construction")
	{
		using sigma_t = typename realized::sigma_t;
		using alpha_t = typename realized::alpha_t;

		auto foo = typename collate_t<2>::template scalar_t<alpha_t> {2.0, 0.5};
		auto bar = realized::template unsquare_f<0>((alpha_t) 2);
		bar.transmute([] XTAL_1FN_(realized::square_f), trim_f<1>);
		TRUE_(foo == bar);

	}
	TRY_("transformation")
	{
		using sigma_t = typename realized::sigma_t;
		using alpha_t = typename realized::alpha_t;

		auto bar = typename collate_t<2>::template scalar_t<alpha_t> {2.0, 0.5};
		auto foo = bar.reflected(-1);
		auto baz = foo.reflected(+1);
		
		TRUE_(trim_f<19>(foo[0]) == 1.25);
		TRUE_(trim_f<19>(foo[1]) == 0.75);
		TRUE_(trim_f<19>(baz[0]) == bar[0]);
		TRUE_(trim_f<19>(baz[1]) == bar[1]);

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("collate", "series")
{
	TRY_("initialization")
	{
		using sigma_t = typename realized::sigma_t;
		using alpha_t = typename realized::alpha_t;

		sigma_t constexpr N = 1 << 3;
		using group_u = typename collate_t<N>::template group_t<alpha_t>;
		using series_u = typename collate_t<N>::template series_t<alpha_t>;

		series_u baz(2.0);
		group_u bar = force_f<group_u &>(baz);
		group_u foo = {1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7};
		TRUE_(equal_f(foo, bar));
		
	}
	TRY_("transformation")
	{
		using sigma_t = typename realized::sigma_t;
		using alpha_t = typename realized::alpha_t;
		using aphex_t = typename realized::aphex_t;

		auto    constexpr iffy = [] XTAL_1FN_(trim_f<16>);
		sigma_t constexpr O = 1 << 5;
		sigma_t constexpr N = 1 << 3;
		sigma_t constexpr M = N  - 1;

		using series_s = typename collate_t<O>::template series_t<aphex_t>;
		using series_u = typename collate_t<N>::template series_t<aphex_t>;
		series_s basis(integer_t<-1>{});

		series_u source;
		source[0] = source[M - 0] = aphex_t(0.0, 0.0);
		source[1] = source[M - 1] = aphex_t(1.0, 1.0);
		source[2] = source[M - 2] = aphex_t(3.0, 3.0);
		source[3] = source[M - 3] = aphex_t(4.0, 4.0);

		auto target = basis.transformation(source).transmute(iffy);
		TRUE_(target[0] == iffy(aphex_t( 0.1600000000000000e+2,  0.1600000000000000e+2)));
		TRUE_(target[1] == iffy(aphex_t(-0.4828427124746192e+1, -0.1165685424949238e+2)));
		TRUE_(target[2] == iffy(aphex_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
		TRUE_(target[3] == iffy(aphex_t(-0.3431457505076203e+0,  0.8284271247461885e+0)));
		TRUE_(target[4] == iffy(aphex_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
		TRUE_(target[5] == iffy(aphex_t( 0.8284271247461912e+0, -0.3431457505076203e+0)));
		TRUE_(target[6] == iffy(aphex_t( 0.0000000000000000e+0,  0.0000000000000000e+0)));
		TRUE_(target[7] == iffy(aphex_t(-0.1165685424949238e+2, -0.4828427124746188e+1)));

	}
	TRY_("convolution")
	{
		using sigma_t = typename realized::sigma_t;
		using alpha_t = typename realized::alpha_t;
		using aphex_t = typename realized::aphex_t;

		auto    constexpr iffy = [] XTAL_1FN_(trim_f<16>);
		sigma_t constexpr N = 1 << 3;
		sigma_t constexpr M = N  - 1;

		using series_u = typename collate_t<N>::template series_t<aphex_t>;
		series_u basis(integer_t<-1>{});

		series_u lhs = {0, 1, 2, 0, 0, 0, 0, 0};
		series_u rhs = {1, 0, 1, 0, 0, 0, 0, 0};
		series_u xhs = {0, 1, 2, 1, 2, 0, 0, 0};
		series_u yhs = basis.convolution(lhs, rhs).transmute(iffy);
		TRUE_(xhs == yhs);

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("collate", "serial")
{
	TRY_("multiplication")
	{
		using D2 = typename collate_t<2>::template serial_t<int>;
		using D3 = typename collate_t<3>::template serial_t<int>;
		using D4 = typename collate_t<4>::template serial_t<int>;
		
		TRUE_(D2 {           10, 1} * D2 {           20, 2} == D2 {                   200,   40});
		TRUE_(D3 {      100, 10, 1} * D3 {      200, 20, 2} == D3 {          20000,  4000,  600});
		TRUE_(D4 {1000, 100, 10, 1} * D4 {2000, 200, 20, 2} == D4 {2000000, 400000, 60000, 8000});

		TRUE_(D2 {1, 2} < D2 {3, 4});

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("collate", "series")
{
	TRY_("multiplication")
	{
		using sigma_t = typename realized::sigma_t;
		using alpha_t = typename realized::alpha_t;
		using aphex_t = typename realized::aphex_t;

		using C4 = typename collate_t<4>::template series_t<aphex_t>;
		using D4 = typename collate_t<4>::template series_t<aphex_t>;
		
		TRUE_(C4 {1000, 100, 10, 1} * C4 {2000, 200, 20, 2} == C4 {2000600, 400040, 60002, 8000});
		TRUE_(D4 {1000, 100, 10, 1} * D4 {2000, 200, 20, 2} == D4 {2000600, 400040, 60002, 8000});

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("collate", "serial")
{
	TRY_("integration")
	{
		using D = typename collate_t<4>::template serial_t<int>;

		D d {1000, 100, 10, 1};

		TRUE_(++d == D {1100, 110, 11, 1});
		TRUE_(++d == D {1210, 121, 12, 1});
		TRUE_(++d == D {1331, 133, 13, 1});

	}
}


////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("collate", "phasor")
{
	TRY_("operation")
	{
		using P = typename collate_t<2>::template phasor_t<float>;
		P p {0.125, 0.250};

		TRUE_(p++ == P {+0.125, 0.250});
		TRUE_(p++ == P {+0.375, 0.250});
		TRUE_(p++ == P {-0.375, 0.250});
		TRUE_(p++ == P {-0.125, 0.250});

	}
	TRY_("iteration")
	{
		using namespace _v3;
		using P  = typename collate_t<2>::template phasor_t<float>;
		using Ps = ranges::iota_view<P>;
		using Qs = _std::vector<float>;

		Ps ps(P {0.125, 0.250});
		Qs qs;
		for (auto p: ps|views::take(4)) qs.push_back(p[0]);
		
		TRUE_(qs == Qs {+0.125, +0.375, -0.375, -0.125});

	//	TODO: Find a way to reset/change the phase/frequency by mutation (or otherwise)? \
		If not, just need to wrap as a `process`. \

	}
}

/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
