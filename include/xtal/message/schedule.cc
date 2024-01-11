#pragma once
#include "./any.cc"
#include "./schedule.ii"// testing...

#include "../prepare/all.ii"
#include "../processor/monomer.ii"


XTAL_ENV_(push)
namespace xtal::message::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("message", "schedule", "hold", "process")
{
	TRY_("drive")
	{
		size_t constexpr N_size = 1<<3;

		using scope_u = message::scope_t<>;
		using gate_t  = message::label_t<typename common::computer::alpha_t, struct T_gate>;
		using gated_t = process::confined_t<typename schedule_t<gate_t>::template hold<(1<<7)>>;

		gated_t o_gated;
		
		using cue_t = conduct::cue_s<>;
		o_gated <<= (cue_t) 0 << (gate_t)  7;
		o_gated <<= (cue_t) 1 << (gate_t)  1;
		o_gated <<= (cue_t) 3 << (gate_t) -1;
		o_gated <<= (cue_t) 4 << (gate_t)  1;
		o_gated <<= (cue_t) 5 << (gate_t) -1;
		o_gated <<= (cue_t) 7 << (gate_t)  7;
		o_gated <<= (cue_t) 7 << (gate_t) 77;
		
		TRUE_(o_gated() ==  7);
		TRUE_(o_gated() ==  1);
		TRUE_(o_gated() ==  1);
		TRUE_(o_gated() == -1);
		TRUE_(o_gated() ==  1);
		TRUE_(o_gated() == -1);
		TRUE_(o_gated() == -1);
		TRUE_(o_gated() == 77);
		TRUE_(o_gated() == 77);
		TRUE_(o_gated() == 77);
	//	...
		o_gated >>= scope_u(N_size);
		o_gated <<= (cue_t) 4 << (gate_t) 11;
		TRUE_(o_gated() == 77);
		TRUE_(o_gated() == 77);
		TRUE_(o_gated() == 77);
		TRUE_(o_gated() == 77);
		TRUE_(o_gated() == 11);
		TRUE_(o_gated() == 11);
		TRUE_(o_gated() == 11);
		TRUE_(o_gated() == 11);

	}
}


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
void message_schedule_hold_processor()
{
	using namespace processor;
	size_t constexpr N_size = 1<<3;

	using gate_t = message::label_t<typename common::computer::alpha_t, struct T_gate>;

	using gated_t = process::confined_t<typename schedule_t<gate_t>::template hold<(1<<7)>>;
	using array_t = _std::array<typename common::computer::alpha_t, N_size>;
	using cue_t = conduct::cue_s<>;

	using resize_u = message::resize_t<>;
	using scope_u = message::scope_t<>;

	auto o_gated = processor::monomer_t<gated_t, As...>::bond_f();
	auto o_array = array_t();
	
	o_gated <<= resize_u(N_size);
	o_gated <<= (cue_t) 0 << (gate_t)  7;
	o_gated <<= (cue_t) 1 << (gate_t)  1;
	o_gated <<= (cue_t) 3 << (gate_t) -1;
	o_gated <<= (cue_t) 4 << (gate_t)  1;
	o_gated <<= (cue_t) 5 << (gate_t) -1;
	o_gated <<= (cue_t) 7 << (gate_t)  7;
	o_gated <<= (cue_t) 7 << (gate_t) 77;

	o_gated >>= scope_u(N_size)*0; _v3::ranges::copy(o_gated, o_array.begin());
	TRUE_(o_array == array_t {  7,  1,  1, -1,  1, -1, -1, 77});

	o_gated <<= (cue_t) 4 << (gate_t) 11;
	o_gated >>= scope_u(N_size)*1; _v3::ranges::copy(o_gated, o_array.begin());
	TRUE_(o_array == array_t { 77, 77, 77, 77, 11, 11, 11, 11});

}
TAG_("message", "schedule", "hold", "processor")
{
	using namespace processor;
	TRY_("drive material") {message_schedule_hold_processor<prepare::restore<>>();}
//	TRY_("drive virtual")  {message_schedule_hold_processor<>();}// TODO?

}


////////////////////////////////////////////////////////////////////////////////

template <class mix_t>
void message_schedule_intermit_x1()
{
	using namespace processor;
	using alpha_t = typename common::computer::alpha_t;

	using onset_s = schedule_t<onset_t>;

	using mix_z = processor::monomer_t<mix_t
	,	prepare::restore<>
	,	onset_s::template intermit<(1<<4)>
	>;
	using resize_u = message::resize_t<>;
	using scope_n  = message::scope_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.head() == &processor::let_f(lhs).head());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.head() == &processor::let_f(rhs).head());
	
	auto xhs = mix_z::bond_f(lhs, rhs);
	auto seq = scope_n(4);

	xhs <<= resize_u(4);
	TRUE_(0 == xhs.size());//NOTE: Only changes after `scope`.

	xhs <<= conduct::cue_s<onset_s>(0, (onset_t) (alpha_t) 100);
	xhs <<= conduct::cue_s<onset_s>(1, (onset_t) (alpha_t) 200);
	xhs <<= conduct::cue_s<onset_s>(2, (onset_t) (alpha_t) 300);
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{100, 211, 322, 333}));

	xhs <<= conduct::cue_s<onset_s>(2, (alpha_t) 400);// relative timing!
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{344, 355, 466, 477}));

}
TAG_("message", "schedule", "intermit")
{
	using namespace processor;
	TRY_("drive dynamic") {message_schedule_intermit_x1<dynamic_onset_mix_t>();}
//	TRY_("drive  static") {message_schedule_intermit_x1< static_onset_mix_t>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
