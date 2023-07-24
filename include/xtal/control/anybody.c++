#pragma once
#include "./any.c++"
#include "./anybody.hpp"// testing...

#include "../control/all.hpp"
#include "../process/all.hpp"
#include "../processor/all.hpp"

XTAL_ENV_(push)
namespace xtal::control::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__test;


////////////////////////////////////////////////////////////////////////////////

TAG_("control", "hold", "process")
{
	TRY_("drive")
	{
		size_t constexpr N_size = 1<<3;

		using sequel_u = control::sequel_t<>;
		using gate_t   = control::label_t<typename realized::alpha_t, struct T_gate>;
		using gated_t  = process::confined_t<typename gate_t::template hold<(1<<7)>>;

		gated_t gated_o;
		
		using point_t = context::point_s<>;
		gated_o << bundle_f((point_t) 0, (gate_t)  7);
		gated_o << bundle_f((point_t) 1, (gate_t)  1);
		gated_o << bundle_f((point_t) 3, (gate_t) -1);
		gated_o << bundle_f((point_t) 4, (gate_t)  1);
		gated_o << bundle_f((point_t) 5, (gate_t) -1);
		gated_o << bundle_f((point_t) 7, (gate_t)  7);
		gated_o << bundle_f((point_t) 7, (gate_t) 77);
		
		TRUE_(gated_o() ==  7);
		TRUE_(gated_o() ==  1);
		TRUE_(gated_o() ==  1);
		TRUE_(gated_o() == -1);
		TRUE_(gated_o() ==  1);
		TRUE_(gated_o() == -1);
		TRUE_(gated_o() == -1);
		TRUE_(gated_o() == 77);
		TRUE_(gated_o() == 77);
		TRUE_(gated_o() == 77);
	//	...
		gated_o >> sequel_u(N_size);
		gated_o << bundle_f((point_t) 4, (gate_t)  11);
		TRUE_(gated_o() == 77);
		TRUE_(gated_o() == 77);
		TRUE_(gated_o() == 77);
		TRUE_(gated_o() == 77);
		TRUE_(gated_o() == 11);
		TRUE_(gated_o() == 11);
		TRUE_(gated_o() == 11);
		TRUE_(gated_o() == 11);

	}
}


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
void control_hold_processor()
{
	size_t constexpr N_size = 1<<3;

	using gate_t = control::label_t<typename realized::alpha_t, struct T_gate>;

	using gated_t = process::confined_t<typename gate_t::template hold<(1<<7)>>;
	using array_t = _std::array<typename realized::alpha_t, N_size>;
	using point_t = context::point_s<>;

	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;

	auto gated_o = processor::monomer_t<gated_t, As...>::bond_f();
	auto array_o = array_t();
	
	gated_o << resize_u(N_size);
	gated_o << bundle_f((point_t) 0, (gate_t)  7);
	gated_o << bundle_f((point_t) 1, (gate_t)  1);
	gated_o << bundle_f((point_t) 3, (gate_t) -1);
	gated_o << bundle_f((point_t) 4, (gate_t)  1);
	gated_o << bundle_f((point_t) 5, (gate_t) -1);
	gated_o << bundle_f((point_t) 7, (gate_t)  7);
	gated_o << bundle_f((point_t) 7, (gate_t) 77);

	gated_o >> sequel_u(N_size)*0; _v3::ranges::copy(gated_o, array_o.begin());
	TRUE_(array_o == array_t {  7,  1,  1, -1,  1, -1, -1, 77});

	gated_o << bundle_f((point_t) 4, (gate_t)  11);
	gated_o >> sequel_u(N_size)*1; _v3::ranges::copy(gated_o, array_o.begin());
	TRUE_(array_o == array_t { 77, 77, 77, 77, 11, 11, 11, 11});

}
TAG_("control", "hold", "processor")
{
	TRY_("drive material") {control_hold_processor<collect<-1>>();}
//	TRY_("drive virtual")  {control_hold_processor<>();}// TODO?

}


////////////////////////////////////////////////////////////////////////////////

template <class mix_t>
void control_intermit_processor()
{
	using alpha_t = typename realized::alpha_t;

	using    mix_z = processor::monomer_t<mix_t, collect<-1>, typename onset_t::template intermit<(1<<4)>>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

	auto lhs = processor::let_f(_01); TRUE_(identical_f(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = processor::let_f(_10); TRUE_(identical_f(rhs.head(), processor::let_f(rhs).head()));
	
	auto xhs = mix_z::bond_f(lhs, rhs);
	auto seq = sequel_n(4);

	xhs << resize_u(4);
	TRUE_(0 == xhs.size());//NOTE: Only changes after `sequel`.

	xhs << context::point_s<onset_t>(0, (alpha_t) 100);
	xhs << context::point_s<onset_t>(1, (alpha_t) 200);
	xhs << context::point_s<onset_t>(2, (alpha_t) 300);
	xhs >> seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{100, 211, 322, 333}));

	xhs << context::point_s<onset_t>(2, (alpha_t) 400);// relative timing!
	xhs >> seq++;
	TRUE_(4 == xhs.size());
	TRUE_(equal_f(xhs, _std::vector{344, 355, 466, 477}));

}
TAG_("control", "intermit", "processor")
{
	TRY_("drive dynamic") {control_intermit_processor<dynamic_onset_mix_t>();}
//	TRY_("drive  static") {control_intermit_processor< static_onset_mix_t>();}// TODO?

}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
