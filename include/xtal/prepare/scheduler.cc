#pragma once
#include "./any.cc"
#include "./scheduler.ii"// testing...

#include "../prepare/all.ii"
#include "../processor/monomer.ii"


XTAL_ENV_(push)
namespace xtal::prepare::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("prepare", "scheduler", "hold", "process")
{
	TRY_("drive")
	{
		size_t constexpr N_store = (1<<3);
		size_t constexpr N_spool = (1<<7);

		using scope_u = message::scope_t<>;
		using sched_u = scheduler_t<respool<N_spool>>;
		
		using cue_t = conduct::cue_s<>;
		
		using gate_t = message::label_t<typename common::computer::alpha_t, struct __gate__>;
		using gate_u = process::confined_t<typename sched_u::template hold<gate_t>>;

		gate_u o_gate;
		
		o_gate <<= (cue_t) 0 << (gate_t)  7;
		o_gate <<= (cue_t) 1 << (gate_t)  1;
		o_gate <<= (cue_t) 3 << (gate_t) -1;
		o_gate <<= (cue_t) 4 << (gate_t)  1;
		o_gate <<= (cue_t) 5 << (gate_t) -1;
		o_gate <<= (cue_t) 7 << (gate_t)  7;
		o_gate <<= (cue_t) 7 << (gate_t) 77;
		
		TRUE_(o_gate() ==  7);
		TRUE_(o_gate() ==  1);
		TRUE_(o_gate() ==  1);
		TRUE_(o_gate() == -1);
		TRUE_(o_gate() ==  1);
		TRUE_(o_gate() == -1);
		TRUE_(o_gate() == -1);
		TRUE_(o_gate() == 77);
		TRUE_(o_gate() == 77);
		TRUE_(o_gate() == 77);
	//	...
		o_gate >>= scope_u(N_store);
		o_gate <<= (cue_t) 4 << (gate_t) 11;
		TRUE_(o_gate() == 77);
		TRUE_(o_gate() == 77);
		TRUE_(o_gate() == 77);
		TRUE_(o_gate() == 77);
		TRUE_(o_gate() == 11);
		TRUE_(o_gate() == 11);
		TRUE_(o_gate() == 11);
		TRUE_(o_gate() == 11);

	}
}


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
void prepare_schedule_hold_processor()
{
	size_t constexpr N_store = (1<<3);
	size_t constexpr N_spool = (1<<7);
	
	using namespace processor;
	using sched_u = scheduler_t<respool<N_spool>>;
	using resize_u = message::resize_t<>;
	using scope_u = message::scope_t<>;
	using cue_t = conduct::cue_s<>;

	using gate_t = message::label_t<typename common::computer::alpha_t, struct __gate__>;
	using gate_u = process::confined_t<typename sched_u::template hold<gate_t>>;
	
	using array_t = _std::array<typename common::computer::alpha_t, N_store>;

	auto o_gate = processor::monomer_t<gate_u, As...>::bond_f();
	auto o_array = array_t();
	
	o_gate <<= resize_u(N_store);
	o_gate <<= (cue_t) 0 << (gate_t)  7;
	o_gate <<= (cue_t) 1 << (gate_t)  1;
	o_gate <<= (cue_t) 3 << (gate_t) -1;
	o_gate <<= (cue_t) 4 << (gate_t)  1;
	o_gate <<= (cue_t) 5 << (gate_t) -1;
	o_gate <<= (cue_t) 7 << (gate_t)  7;
	o_gate <<= (cue_t) 7 << (gate_t) 77;

	o_gate >>= scope_u(N_store)*0; _v3::ranges::copy(o_gate, o_array.begin());
	TRUE_(o_array == array_t {  7,  1,  1, -1,  1, -1, -1, 77});

	o_gate <<= (cue_t) 4 << (gate_t) 11;
	o_gate >>= scope_u(N_store)*1; _v3::ranges::copy(o_gate, o_array.begin());
	TRUE_(o_array == array_t { 77, 77, 77, 77, 11, 11, 11, 11});

}
TAG_("prepare", "scheduler", "hold", "processor")
{
	using namespace processor;
	TRY_("drive material") {prepare_schedule_hold_processor<prepare::restore<>>();}
//	TRY_("drive virtual")  {prepare_schedule_hold_processor<>();}// TODO?

}


////////////////////////////////////////////////////////////////////////////////

template <class mix_t>
void prepare_schedule_intermit_x1()
{
	using namespace processor;
	using sched_u = scheduler_t<respool<(1<<4)>>;

	using alpha_u = typename common::computer::alpha_t;
	using event_u = message::packet_t<onset_t>;

	using mix_z = processor::monomer_t<mix_t
	,	prepare::restore<>
	,	sched_u::template intermit<onset_t>
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

	xhs <<= conduct::cue_s<event_u>(0, (onset_t) (alpha_u) 100);
	xhs <<= conduct::cue_s<event_u>(1, (onset_t) (alpha_u) 200);
	xhs <<= conduct::cue_s<event_u>(2, (onset_t) (alpha_u) 300);
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{100, 211, 322, 333}));

	xhs <<= conduct::cue_s<event_u>(2, (alpha_u) 400);// relative timing!
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{344, 355, 466, 477}));

}
TAG_("context", "scheduler", "intermit")
{
	using namespace processor;
	TRY_("drive dynamic") {prepare_schedule_intermit_x1<dynamic_onset_mix_t>();}
//	TRY_("drive  static") {prepare_schedule_intermit_x1< static_onset_mix_t>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
