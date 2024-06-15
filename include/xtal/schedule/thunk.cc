#pragma once
#include "./any.cc"
#include "./thunk.hh"// testing...

#include "../resource/all.hh"
#include "../processor/monomer.hh"


XTAL_ENV_(push)
namespace xtal::schedule::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("thunk", "process")
{
	using _op = bond::operating;
	using T_sigma = typename _op::sigma_t;
	using T_delta = typename _op::delta_t;
	using T_alpha = typename _op::alpha_t;

	/**/
	TRY_("continuous")
	{
		using namespace resource;
	//	using namespace schedule;

		int constexpr N_store = (1<<3);
		int constexpr N_spool = (1<<7);

		using U_thunk = thunk_t<spooled<nominal_t<N_spool>>>;
		using U_render = occur::render_t<>;

		using U0_event = occur::reinferred_t<class A_gate, T_alpha>;
		using U1_event = flux::cue_s<U0_event>;
		using U2_event = flux::cue_s<U1_event>;
		
		using W0_event = algebra::d_::linear_t<U0_event[2]>;
		using V_event = flux::cue_s<>;
		
		//\
		using U_inqueue = typename U_thunk::template inqueue<V_event, U0_event>;
		using U_inqueue = typename U_thunk::template inqueue<         U1_event>;
		using U_process = process::confined_t<U_inqueue>;

		U_process u_gate;
		
		U0_event u0(2);
		U1_event u1(2, u0);
		U2_event u2(2, u1);

		U0_event v0(2);
		U1_event v1(2, u0);
		U2_event v2(2, u1);

		u0 += v0;
//		u1 += v1;
	//	static_assert(is_q<U2_event, typename U_process::event_type>);
		static_assert(is_q<U0_event, typename U1_event::cue_type>);
		static_assert(is_q<U0_event, typename U2_event::cue_type>);
	//	static_assert(is_q<U0_event, typename U_process::event_type::cue_type>);

		u_gate <<= u0;
		u_gate <<= u1;
		u_gate <<= u2;

		W0_event w0{u0};

		u_gate <<=                (U0_event) 2.0;
		u_gate <<= U2_event(2, 6, (U0_event) 4.0);
		u_gate <<= U2_event(7, 9, (U0_event) 5.0);

		TRUE_((T_alpha) u_gate() == 2.0);//  0
		TRUE_((T_alpha) u_gate() == 2.0);//  1
		TRUE_((T_alpha) u_gate() == 2.0);//  2 <<
		TRUE_((T_alpha) u_gate() == 2.5);//  3
		TRUE_((T_alpha) u_gate() == 3.0);//  4
		TRUE_((T_alpha) u_gate() == 3.5);//  5
//		
		u_gate >>= U_render(N_store);
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
		using namespace resource;
	//	using namespace schedule;

		int constexpr N_store = (1<<3);
		int constexpr N_spool = (1<<7);

		using U_thunk = thunk_t<spooled<nominal_t<N_spool>>>;
		using U_render = occur::render_t<>;

		using V_value = occur::reinferred_t<class A_gate, T_alpha>;
		using Z_value = process::confined_t<typename U_thunk::template inqueue<V_value>>;

		using U_event = flux::cue_s<occur::packet_t<V_value>>;
		using V_event = flux::cue_s<>;
		
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
		u_gate >>= U_render(N_store);
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

		using namespace resource;
	//	using namespace schedule;

		int constexpr N_store = (1<<3);
		int constexpr N_spool = (1<<7);

		using U_thunk = thunk_t<spooled<nominal_t<N_spool>>>;
		using U_render = occur::render_t<>;
		using V_event = flux::cue_s<>;
		
		using V_value = occur::reinferred_t<class A_gate, T_alpha>;
		using Z_value = process::confined_t<typename U_thunk::template inqueue<V_value>>;

		Z_value u_gate;
		
	//	u_gate <<= (V_event) 0 << (V_value)  7;
		u_gate <<=              (V_value)  7;
		TRUE_(u_gate() ==  7);
	//	...
		u_gate >>= U_render(N_store);
	//	u_gate <<= (V_event) 0 << (V_value) 11;
		u_gate <<=              (V_value) 11;
		TRUE_(u_gate() == 11);

	}
	/***/
}

////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
void thunk_processor()
{
	using _op = bond::operating;
	using T_sigma = typename _op::sigma_t;
	using T_delta = typename _op::delta_t;
	using T_alpha = typename _op::alpha_t;

	using namespace resource;
//	using namespace schedule;

	class L_gate;

	int constexpr N_store = (1<<3);
	int constexpr N_spool = (1<<7);
	
	using U_thunk = thunk_t<spooled<nominal_t<N_spool>>>;

	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;
	using U_store = _std::array<T_alpha, N_store>;
	U_store u_store{};

	using V_value  = occur::reinferred_t<L_gate, T_alpha>;
	using Fn_gate = process::confined_t<typename U_thunk::template inqueue<V_value>>;
	using Fx_gate = processor::monomer_t<Fn_gate, As...>;
	auto  fx_gate = Fx_gate::binding_f();
	
	using U_event = flux::cue_s<occur::packet_t<V_value>>;
	using V_event = flux::cue_s<>;

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

	fx_gate >>= U_render(N_store)*0; _xtd::ranges::copy(fx_gate, u_store.begin());
//	echo(u_store);
	TRUE_(u_store == U_store {  7,  1,  1, -1,  1, -1, -1, 77});

	/**/
//	fx_gate <<= (V_event) 0 << (V_value) 77;
	fx_gate <<= (V_event) 4 << (V_value) 11;
	/*/
//	fx_gate <<= U_event(0, 77);
	fx_gate <<= U_event(4, 11);
	/***/

	fx_gate >>= U_render(N_store)*1; _xtd::ranges::copy(fx_gate, u_store.begin());
//	echo(u_store);
	TRUE_(u_store == U_store { 77, 77, 77, 77, 11, 11, 11, 11});

}
TAG_("thunk", "processor")
{
	using namespace processor;
	TRY_("drive actual") {thunk_processor<resource::stored<>>();}
//	TRY_("drive virtual")  {thunk_processor<>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
