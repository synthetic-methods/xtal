#pragma once
#include "./any.cc"
#include "./chunk.ii"// testing...

#include "../resourced/all.ii"
#include "../processor/monomer.ii"


XTAL_ENV_(push)
namespace xtal::scheduled::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////






template <class mix_t>
void chunk_processor_x1()
{
	using namespace resourced;
//	using namespace scheduled;

	using U_chunk = chunk_t<spool<(1<<4)>>;

	using U_alpha = typename bond::realized::alpha_t;
	using U_event = message::packet_t<onset_t>;

	using mix_z = processor::monomer_t<mix_t
	,	store<>
	,	U_chunk::template inqueue<onset_t>
	>;
	using U_resize = message::resize_t<>;
	using scope_n  = message::scope_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(as_f<U_alpha>);
	auto _10 = _01|_v3::views::transform([] (U_alpha n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (U_alpha n) {return n*11;});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	
	auto xhs = mix_z::bind_f(lhs, rhs);
	auto seq = scope_n(4);

	xhs <<= U_resize(4);
	TRUE_(0 == xhs.size());//NOTE: Only changes after `scope`.

	xhs <<= cell::cue_s<U_event>(0, (onset_t) (U_alpha) 100);
	xhs <<= cell::cue_s<U_event>(1, (onset_t) (U_alpha) 200);
	xhs <<= cell::cue_s<U_event>(2, (onset_t) (U_alpha) 300);
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{100, 211, 322, 333}));

	xhs <<= cell::cue_s<U_event>(2, (U_alpha) 400);// relative timing!
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{344, 355, 466, 477}));

}
TAG_("chunk", "processor")
{
	using namespace processor;
	TRY_("drive dynamic") {chunk_processor_x1<dynamic_onset_mix_t>();}
//	TRY_("drive  static") {chunk_processor_x1< static_onset_mix_t>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
