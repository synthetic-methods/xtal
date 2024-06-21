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

template <class Px_mix>
void chunk_processor_x1()
{
	using namespace resource;
//	using namespace schedule;

	using _op = bond::operating;
	using T_alpha  = typename _op::alpha_type;
	using T_sigma  = typename _op::sigma_type;
	using T_delta  = typename _op::delta_type;

	using U_chunk = chunk_t<spooled<nominal_t<0x10>>>;
	using U_value = flux::packet_t<Ox_onset>;
	using U_event = flux::cue_s<U_value>;

	using mix_z = processor::monomer_t<Px_mix
	,	stored<>
	,	U_chunk::template inqueue<Ox_onset>
	>;
	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;

	auto _01 = _xtd::ranges::views::iota(0, 10)|_xtd::ranges::views::transform(invoke_f<T_alpha>);
	auto _10 = _01|_xtd::ranges::views::transform([] (T_alpha n) {return n*10;});
	auto _11 = _01|_xtd::ranges::views::transform([] (T_alpha n) {return n*11;});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	
	auto xhs = mix_z::binds_f(lhs, rhs);
	auto seq = U_render(4);

	xhs <<= U_resize(4);
	TRUE_(0 == xhs.size());//NOTE: Only changes after `render`.

	xhs <<= U_event(0, (Ox_onset) (T_alpha) 100);
	xhs <<= U_event(1, (Ox_onset) (T_alpha) 200);
	xhs <<= U_event(2, (Ox_onset) (T_alpha) 300);
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{100, 211, 322, 333}));

	xhs <<= U_event(2, (T_alpha) 400);// relative timing!
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{344, 355, 466, 477}));

}
TAG_("chunk", "processor")
{
	using namespace processor;
	TRY_("drive dynamic") {chunk_processor_x1<Px_dynamic_onset_mix>();}
//	TRY_("drive  static") {chunk_processor_x1< Px_static_onset_mix>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
