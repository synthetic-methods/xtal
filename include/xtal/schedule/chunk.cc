#pragma once
#include "./any.cc"
#include "./chunk.hh"// testing...

#include "../provision/all.hh"
#include "../processor/monomer.hh"


XTAL_ENV_(push)
namespace xtal::schedule::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class Px_mix>
void chunk_processor_x1()
{
	using namespace provision;
//	using namespace schedule;

	using _fix = bond::fixture<>;
	using T_alpha  = typename _fix::alpha_type;
	using T_sigma  = typename _fix::sigma_type;
	using T_delta  = typename _fix::delta_type;

	using U_chunk = chunk_t<spooled<extent_constant_t<0x10>>>;
	using U_value = flow::packet_t<Ox_onset>;
	using U_event = flow::cue_s<U_value>;

	using mix_z = processor::monomer_t<Px_mix
	,	stored<>
	,	U_chunk::template inqueue<Ox_onset>
	>;
	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;

	auto _01 = _xtd::ranges::views::iota(0, 10)|_xtd::ranges::views::transform(evoke_t<T_alpha>{});
	auto _10 = _01|_xtd::ranges::views::transform([] (T_alpha n) {return n*10;});
	auto _11 = _01|_xtd::ranges::views::transform([] (T_alpha n) {return n*11;});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	
	auto xhs = mix_z::bind_f(lhs, rhs);
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
