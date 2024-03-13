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

	using U_spliced = spliced_t<spooled<(1<<4)>>;

	using U_alpha = typename atom::computer::alpha_t;
	using U_event = message::packet_t<onset_t>;

	using mix_z = processor::monomer_t<mix_t
	,	stored<>
	,	U_spliced::template inqueue<onset_t>
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

	xhs <<= bond::cue_s<U_event>(0, (onset_t) (U_alpha) 100);
	xhs <<= bond::cue_s<U_event>(1, (onset_t) (U_alpha) 200);
	xhs <<= bond::cue_s<U_event>(2, (onset_t) (U_alpha) 300);
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{100, 211, 322, 333}));

	xhs <<= bond::cue_s<U_event>(2, (U_alpha) 400);// relative timing!
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
