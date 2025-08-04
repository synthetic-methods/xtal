#pragma once
#include "./any.cc"
#include "./glider.hh"// testing...

#include "../provision/all.hh"
#include "../processor/monomer.hh"


XTAL_ENV_(push)
namespace xtal::schedule::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("glider", "process")
{
	using _fit = bond::fit<>;
	using T_sigma = typename _fit::sigma_type;
	using T_delta = typename _fit::delta_type;
	using T_alpha = typename _fit::alpha_type;

	/**/
	TRY_("continuous")
	{
		using namespace provision;
	//	using namespace schedule;

		int constexpr N_store = (1<<3);
		int constexpr N_spool = (1<<7);

		using U_glider = glider_t<spooled<extent_constant_t<N_spool>>>;
		using U_cursor = occur::cursor_t<>;

		using U0_cue   = flow::cue_s<>;
		using U1_cue   = flow::cue_s<U0_cue>;
		using U0_event = occur::reinferred_t<class A_gate, T_alpha>;
		using U1_event = flow::cue_s<U0_event>;
		
		using W0_event = atom::differential_t<U0_event[2]>;
		using V_event = flow::cue_s<>;
		
		using Z_process = process::confined_t<
			typename U_glider::template accept<U1_event>
		>;
		using U_processor = processor::monomer_t<Z_process
		,	provision::stored <null_type[0x100]>
		,	provision::spooled<null_type[0x100]>
		>;

		auto z_cursor = occur::  cursor_t<>(0x020);
		auto z_resize = occur::  resize_t<>(0x020);
		auto z_sample = occur::resample_t<>(44100);

		//\
		U_processor::template bind_t<> z;
		auto z = U_processor::bind_f();
		
		U0_event u0(0);
		U1_event u1(2, u0);

		U0_event v0(2);
		U1_event v1(2, u0);

		u0 += v0;
//		u1 += v1;

		z <<= u0;
		z <<= u1;

		W0_event w0{u0};

		z <<=                         U0_event{ 0.00} ;
		z <<= U1_cue(0x08, 0x10).then(U0_event{ 0.50});
		z <<= U1_cue(0x18, 0x28).then(U0_event{-0.50});
	//	z <<= U1_cue(0x30, 0x40).then(U0_event{ 0.00});

		z <<= z_sample;
		z <<= z_resize;

		echo_rule_<28>();

		TRUE_(0 == z.efflux(z_cursor++));
		{
			echo_plot_<28>(z.store(), 0x10, 0x18);

		//	TRUE_(2 >= z.ensemble().size());// Still decaying...
		}
		z <<= U1_cue(0x10, 0x20).then(U0_event{ 0.00});
		TRUE_(0 == z.efflux(z_cursor++));
		{
			echo_plot_<28>(z.store(), 0x08, 0x10);

		//	TRUE_(2 >= z.ensemble().size());// Still decaying...
		}

		echo_rule_<28>();
	}
	/***/
	/**/
	TRY_("continuous")
	{
		using namespace provision;
	//	using namespace schedule;

		int constexpr N_store = (1<<3);
		int constexpr N_spool = (1<<7);

		using U_glider = glider_t<spooled<extent_constant_t<N_spool>>>;
		using U_cursor = occur::cursor_t<>;

		using U0_cue   = flow::cue_s<>;
		using U1_cue   = flow::cue_s<U0_cue>;

		using U0_event = occur::reinferred_t<class A_gate, T_alpha>;
		using U1_event = flow::cue_s<U0_event>;
		
		using W0_event = atom::differential_t<U0_event[2]>;
		using V_event  = flow::cue_s<>;
		
		using U_accept = typename U_glider::template accept<U1_event>;
		using U_process = process::confined_t<U_accept>;

		U_process u_gate;
		
		U0_event u0(2);
		U1_event u1(2, u0);

		U0_event v0(2);
		U1_event v1(2, u0);

		u0 += v0;
//		u1 += v1;

		u_gate <<= u0;
		u_gate <<= u1;

		W0_event w0{u0};

		u_gate <<=                   U0_event{2.0} ;
		u_gate <<= U1_cue(2, 6).then(U0_event{4.0});
		u_gate <<= U1_cue(7, 9).then(U0_event{5.0});

		TRUE_((T_alpha) u_gate() == 2.0);//  0
		TRUE_((T_alpha) u_gate() == 2.0);//  1
		TRUE_((T_alpha) u_gate() == 2.0);//  2 <<
		TRUE_((T_alpha) u_gate() == 2.5);//  3
		TRUE_((T_alpha) u_gate() == 3.0);//  4
		TRUE_((T_alpha) u_gate() == 3.5);//  5
//		
		u_gate >>= U_cursor(N_store);
		u_gate <<= (V_event) 4 << (U0_event) 9.0;
//		
		TRUE_((T_alpha) u_gate() == 4.0);//  6 >>
		TRUE_((T_alpha) u_gate() == 4.0);//  7 <<
		TRUE_((T_alpha) u_gate() == 4.5);//  8
		TRUE_((T_alpha) u_gate() == 5.0);//  9 >>
		TRUE_((T_alpha) u_gate() == 9.0);// 10
		TRUE_((T_alpha) u_gate() == 9.0);// 11
		
		u_gate <<= (V_event) 1 << (U0_event) 1.0;
		
		TRUE_((T_alpha) u_gate() == 9.0);// 12
		TRUE_((T_alpha) u_gate() == 1.0);// 13

	//	TODO: Test that the queue is being culled. \

	}
	/***/
	/**/
	TRY_("discrete")
	{
		using namespace provision;
	//	using namespace schedule;

		int constexpr N_store = (1<<3);
		int constexpr N_spool = (1<<7);

		using U_glider = glider_t<spooled<extent_constant_t<N_spool>>>;
		using U_cursor = occur::cursor_t<>;

		using V_value = occur::reinferred_t<class A_gate, T_alpha>;
		using Z_value = process::confined_t<typename U_glider::template accept<V_value>>;

		using U_event = flow::cue_s<V_value>;
		using V_event = flow::cue_s<>;
		
		Z_value u_gate;
		
		u_gate <<=                 (V_value)  7;
	//	u_gate <<= (V_event)  0 << (V_value)  7;
		u_gate <<= (V_event)  1 << (V_value)  1;
		u_gate <<= (V_event)  3 << (V_value) -1;
		u_gate <<= (V_event)  4 << (V_value)  1;
		u_gate <<= (V_event)  5 << (V_value) -1;
		u_gate <<= (V_event)  7 << (V_value)  7;
		u_gate <<= (V_event)  7 << (V_value) 77;
		u_gate <<= (V_event) 10 << (V_value) 99;
		
		TRUE_(u_gate() ==  7);
		TRUE_(u_gate() ==  1);
		TRUE_(u_gate() ==  1);
		TRUE_(u_gate() == -1);
		TRUE_(u_gate() ==  1);
		TRUE_(u_gate() == -1);
		TRUE_(u_gate() == -1);
		TRUE_(u_gate() == 77);
		TRUE_(u_gate() == 77);
	//	TRUE_(u_gate() == 99);
	//	...
		u_gate >>= U_cursor(N_store);
		u_gate <<= (V_event) 4 << (V_value) 11;

		TRUE_(u_gate() == 77);
		TRUE_(u_gate() == 99);
		TRUE_(u_gate() == 99);
		TRUE_(u_gate() == 99);
		TRUE_(u_gate() == 11);
		TRUE_(u_gate() == 11);
		TRUE_(u_gate() == 11);
		TRUE_(u_gate() == 11);

	}
	/***/
	/**/
	TRY_("through")
	{

		using namespace provision;
	//	using namespace schedule;

		int constexpr N_store = (1<<3);
		int constexpr N_spool = (1<<7);

		using U_glider = glider_t<spooled<extent_constant_t<N_spool>>>;
		using U_cursor = occur::cursor_t<>;
		using V_event = flow::cue_s<>;
		
		using V_value = occur::reinferred_t<class A_gate, T_alpha>;
		using Z_value = process::confined_t<typename U_glider::template accept<V_value>>;

		Z_value u_gate;
		
	//	u_gate <<= (V_event) 0 << (V_value)  7;
		u_gate <<=                (V_value)  7;
		TRUE_(u_gate() ==  7);
	//	...
		u_gate >>= U_cursor(N_store);
	//	u_gate <<= (V_event) 0 << (V_value) 11;
		u_gate <<=                (V_value) 11;
		TRUE_(u_gate() == 11);

	}
	/***/
}

////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
void glider_processor()
{
	using _fit = bond::fit<>;
	using T_sigma = typename _fit::sigma_type;
	using T_delta = typename _fit::delta_type;
	using T_alpha = typename _fit::alpha_type;

	using namespace provision;
//	using namespace schedule;

	class L_gate;

	int constexpr N_store = (1<<3);
	int constexpr N_spool = (1<<7);
	
	using U_glider = glider_t<spooled<extent_constant_t<N_spool>>>;

	using U_resize = occur::resize_t<>;
	using U_cursor = occur::cursor_t<>;
	using U_store = _std::array<T_alpha, N_store>;
	U_store u_store{};

	using V_value  = occur::reinferred_t<L_gate, T_alpha>;
	using Fn_gate = process::confined_t<typename U_glider::template accept<V_value>>;
	using Fx_gate = processor::monomer_t<Fn_gate, As...>;
	auto  fx_gate = Fx_gate::bind_f();
	
	using U_event = flow::cue_s<V_value>;
	using V_event = flow::cue_s<>;

	fx_gate <<= U_resize(N_store);
	/*/
	fx_gate <<= (V_event) 0 << (V_value)  7;
	fx_gate <<= (V_event) 1 << (V_value)  1;
	fx_gate <<= (V_event) 3 << (V_value) -1;
	fx_gate <<= (V_event) 4 << (V_value)  1;
	fx_gate <<= (V_event) 5 << (V_value) -1;
	fx_gate <<= (V_event) 7 << (V_value)  7;
	fx_gate <<= (V_event) 7 << (V_value) 77;
	/*/
	fx_gate <<= U_event(0,  7);
	fx_gate <<= U_event(1,  1);
	fx_gate <<= U_event(3, -1);
	fx_gate <<= U_event(4,  1);
	fx_gate <<= U_event(5, -1);
	fx_gate <<= U_event(7,  7);
	fx_gate <<= U_event(7, 77);
	/***/

	fx_gate >>= U_cursor(N_store)*0; _xtd::ranges::copy(fx_gate, u_store.begin());
	TRUE_(u_store == U_store {  7,  1,  1, -1,  1, -1, -1, 77});

	/**/
//	fx_gate <<= (V_event) 0 << (V_value) 77;
	fx_gate <<= (V_event) 4 << (V_value) 11;
	/*/
//	fx_gate <<= U_event(0, 77);
	fx_gate <<= U_event(4, 11);
	/***/

	fx_gate >>= U_cursor(N_store)*1; _xtd::ranges::copy(fx_gate, u_store.begin());
	TRUE_(u_store == U_store { 77, 77, 77, 77, 11, 11, 11, 11});

}
TAG_("glider", "processor")
{
	using namespace processor;
	TRY_("drive actual") {glider_processor<provision::stored<>>();}
//	TRY_("drive virtual")  {glider_processor<>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
