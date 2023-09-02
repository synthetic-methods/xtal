#pragma once
#include "../any.cc"
#include "./any.ii"// testing...

#include "../message/all.ii"
#include "../process/all.ii"
#include "../processor/all.ii"

XTAL_ENV_(push)
namespace xtal::message::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__test;


////////////////////////////////////////////////////////////////////////////////

TAG_("message", "hold", "process")
{
	TRY_("drive")
	{
		size_t constexpr N_size = 1<<3;

		using sequel_u = message::sequel_t<>;
		using gate_t   = message::label_t<typename common::computer::alpha_t, struct T_gate>;
		using gated_t  = process::confined_t<typename gate_t::template hold<(1<<7)>>;

		gated_t o_gated;
		
		using cue_t = context::cue_s<>;
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
		o_gated >>= sequel_u(N_size);
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
void control_hold_processor()
{
	using namespace processor;
	size_t constexpr N_size = 1<<3;

	using gate_t = message::label_t<typename common::computer::alpha_t, struct T_gate>;

	using gated_t = process::confined_t<typename gate_t::template hold<(1<<7)>>;
	using array_t = _std::array<typename common::computer::alpha_t, N_size>;
	using cue_t = context::cue_s<>;

	using resize_u = message::resize_t<>;
	using sequel_u = message::sequel_t<>;

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

	o_gated >>= sequel_u(N_size)*0; _v3::ranges::copy(o_gated, o_array.begin());
	TRUE_(o_array == array_t {  7,  1,  1, -1,  1, -1, -1, 77});

	o_gated <<= (cue_t) 4 << (gate_t) 11;
	o_gated >>= sequel_u(N_size)*1; _v3::ranges::copy(o_gated, o_array.begin());
	TRUE_(o_array == array_t { 77, 77, 77, 77, 11, 11, 11, 11});

}
TAG_("message", "hold", "processor")
{
	using namespace processor;
	TRY_("drive material") {control_hold_processor<restore<>>();}
//	TRY_("drive virtual")  {control_hold_processor<>();}// TODO?

}


////////////////////////////////////////////////////////////////////////////////

template <class mix_t>
void control_intermit_processor()
{
	using namespace processor;
	using alpha_t = typename common::computer::alpha_t;

	using    mix_z = processor::monomer_t<mix_t, restore<>, typename onset_t::template intermit<(1<<4)>>;
	using resize_u = message::resize_t<>;
	using sequel_n = message::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

	auto lhs = processor::let_f(_01); TRUE_(&lhs.valve() == &processor::let_f(lhs).valve());
	auto rhs = processor::let_f(_10); TRUE_(&rhs.valve() == &processor::let_f(rhs).valve());
	
	auto xhs = mix_z::bond_f(lhs, rhs);
	auto seq = sequel_n(4);

	xhs <<= resize_u(4);
	TRUE_(0 == xhs.size());//NOTE: Only changes after `sequel`.

	xhs <<= context::cue_s<onset_t>(0, (alpha_t) 100);
	xhs <<= context::cue_s<onset_t>(1, (alpha_t) 200);
	xhs <<= context::cue_s<onset_t>(2, (alpha_t) 300);
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{100, 211, 322, 333}));

	xhs <<= context::cue_s<onset_t>(2, (alpha_t) 400);// relative timing!
	xhs >>= seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{344, 355, 466, 477}));

}
TAG_("message", "intermit", "processor")
{
	using namespace processor;
	TRY_("drive dynamic") {control_intermit_processor<dynamic_onset_mix_t>();}
//	TRY_("drive  static") {control_intermit_processor< static_onset_mix_t>();}// TODO?

}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
