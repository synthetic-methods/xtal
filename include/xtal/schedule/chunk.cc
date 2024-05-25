#pragma once
#include "./any.cc"
#include "./chunk.hh"// testing...

#include "../resource/all.hh"
#include "../processor/monomer.hh"


XTAL_ENV_(push)
namespace xtal::schedule::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////






template <class mix_t>
void chunk_processor_x1()
{
	using namespace resource;
//	using namespace schedule;

	using op = bond::operating;
	using T_alpha  = typename op::alpha_t;
	using T_sigma  = typename op::sigma_t;
	using T_delta  = typename op::delta_t;

	using U_chunk = chunk_t<respool<constant_t<0x10>>>;
	using U_event = occur::packed_t<onset_t>;

	using mix_z = processor::monomer_t<mix_t
	,	restore<>
	,	U_chunk::template inqueue<onset_t>
	>;
	using U_resize = occur::resize_t<>;
	using render_n  = occur::render_t<>;

	auto _01 = _xtd::ranges::views::iota(0, 10)|_xtd::ranges::views::transform(make_f<T_alpha>);
	auto _10 = _01|_xtd::ranges::views::transform([] (T_alpha n) {return n*10;});
	auto _11 = _01|_xtd::ranges::views::transform([] (T_alpha n) {return n*11;});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	
	auto xhs = mix_z::bind_f(lhs, rhs);
	auto seq = render_n(4);

	xhs <<= U_resize(4);
	TRUE_(0 == xhs.size());//NOTE: Only changes after `render`.

	xhs <<= cell::cue_s<U_event>(0, (onset_t) (T_alpha) 100);
	xhs <<= cell::cue_s<U_event>(1, (onset_t) (T_alpha) 200);
	xhs <<= cell::cue_s<U_event>(2, (onset_t) (T_alpha) 300);
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{100, 211, 322, 333}));

	xhs <<= cell::cue_s<U_event>(2, (T_alpha) 400);// relative timing!
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
