#pragma once
#include "./any.cc"
#include "./slicer.hh"// testing...

#include "../provision/all.hh"
#include "../processor/monomer.hh"


XTAL_ENV_(push)
namespace xtal::schedule::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class Px_mix>
void slicer_processor_x1()
{
	using namespace _xtd::ranges::views;
	using namespace provision;
//	using namespace schedule;


	using _fit = bond::fit<>;
	using T_alpha  = typename _fit::alpha_type;
	using T_sigma  = typename _fit::sigma_type;
	using T_delta  = typename _fit::delta_type;

	using U0_cue   = flow::cue_s<>;
//	using U1_cue   = flow::cue_s<U0_cue>;

	using U0_event = Ox_onset;
//	using U1_event = flow::cue_s<U0_event>;

	using mix_z = processor::monomer_t<Px_mix
	,	stored<>
	,	typename slicer_t<spooled<extent_constant_t<0x10>>>::template inqueue<U0_event>
	>;
	using U_resize = occur::resize_t<>;
	using U_cursor = occur::cursor_t<>;

	auto _01 = iota(0, 10)|transform(bond::operate<T_alpha>{});
	auto _10 = _01|transform([] (T_alpha n) {return n*10;});
	auto _11 = _01|transform([] (T_alpha n) {return n*11;});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	
	auto xhs = mix_z::bind_f(lhs, rhs);
	auto seq = U_cursor(4);

	xhs <<= U_resize(4);
	TRUE_(0 == xhs.size());//NOTE: Only changes after `cursor`.

	xhs <<= U0_cue{0}.then(U0_event{100});
	xhs <<= U0_cue{1}.then(U0_event{200});
	xhs <<= U0_cue{2}.then(U0_event{300});
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{100, 211, 322, 333}));

	xhs <<= U0_cue{2}.then(U0_event{400});// relative timing!
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{344, 355, 466, 477}));

}
TAG_("slicer", "processor")
{
	using namespace processor;
	TRY_("drive dynamic") {slicer_processor_x1<Px_dynamic_onset_mix>();}
//	TRY_("drive  static") {slicer_processor_x1< Px_static_onset_mix>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
