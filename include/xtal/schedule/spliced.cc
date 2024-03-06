#pragma once
#include "./any.cc"
#include "./spliced.ii"// testing...

#include "../resource/all.ii"
#include "../processor/monomer.ii"


XTAL_ENV_(push)
namespace xtal::schedule::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class mix_t>
void spliced_processor_x1()
{
	using namespace resource;
//	using namespace schedule;

	using spliced_u = spliced_t<respool<(1<<4)>>;

	using alpha_u = typename common::computer::alpha_t;
	using event_u = message::packet_t<onset_t>;

	using mix_z = processor::monomer_t<mix_t
	,	restore<>
	,	spliced_u::template inqueue<onset_t>
	>;
	using resize_u = message::resize_t<>;
	using scope_n  = message::scope_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_u>);
	auto _10 = _01|_v3::views::transform([] (alpha_u n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (alpha_u n) {return n*11;});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	
	auto xhs = mix_z::bond_f(lhs, rhs);
	auto seq = scope_n(4);

	xhs <<= resize_u(4);
	TRUE_(0 == xhs.size());//NOTE: Only changes after `scope`.

	xhs <<= compound::cue_s<event_u>(0, (onset_t) (alpha_u) 100);
	xhs <<= compound::cue_s<event_u>(1, (onset_t) (alpha_u) 200);
	xhs <<= compound::cue_s<event_u>(2, (onset_t) (alpha_u) 300);
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{100, 211, 322, 333}));

	xhs <<= compound::cue_s<event_u>(2, (alpha_u) 400);// relative timing!
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{344, 355, 466, 477}));

}
TAG_("spliced", "processor")
{
	using namespace processor;
	TRY_("drive dynamic") {spliced_processor_x1<dynamic_onset_mix_t>();}
//	TRY_("drive  static") {spliced_processor_x1< static_onset_mix_t>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
