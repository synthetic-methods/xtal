#pragma once
#include "./any.cc"
#include "./slider.hh"// testing...

#include "../scheme/all.hh"
#include "../processor/monomer.hh"


XTAL_ENV_(push)
namespace xtal::schedule::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("slider", "process")
{
	using U_fit = bond::fit<>;
	using U_sigma = typename U_fit::sigma_type;
	using U_delta = typename U_fit::delta_type;
	using U_alpha = typename U_fit::alpha_type;

	/**/
	TRY_("continuous")
	{
		using flow::cue_f;
		using namespace scheme;
	//	using namespace schedule;

		int constexpr N_store = (1<<3);
		int constexpr N_spool = (1<<7);

		using Par_cursor = occur::cursor_t<>;
		using Sxd_slider = slider_t<spooled<extent_constant_t<N_spool>>>;

		using Par_ramp = occur::reinferred_t<class RAMP, U_alpha>;
		using Prx_ramp = process::confined_t<
			typename Sxd_slider::template suspend<flow::cue_s<Par_ramp>>
		>;
		using Pxr_ramp = processor::monomer_t<Prx_ramp
		,	scheme::stored <null_type[0x100]>
		,	scheme::spooled<null_type[0x100]>
		>;

		auto z_cursor = occur::cursor_t<>(0x020);
		auto z_resize = occur::resize_t<>(0x020);
		auto z_sample = occur::quartz_t<>(44100);

		//\
		Pxr_ramp::template bind_t<> z;
		auto z = Pxr_ramp::bind_f();
		
		z <<=                        Par_ramp{ 0.00};
		z <<= cue_f(0x08, 0x10) <<   Par_ramp{ 0.99};
		z <<= cue_f(0x10, 0x28) <<   Par_ramp{-0.99};
	//	z <<= cue_f(0x08, 0x10).then(Par_ramp{ 0.99});
	//	z <<= cue_f(0x10, 0x28).then(Par_ramp{-0.99});

		z <<= z_sample;
		z <<= z_resize;

		echo_rule_<28>();

		TRUE_(0 == z.efflux(z_cursor++));
		{
			echo_plot_<28>(z.store(), 0x10, 0x18);

		//	TRUE_(2 >= z.ensemble().size());// Still decaying...
		}
		z <<= cue_f(0x10, 0x20).then(Par_ramp{ 0.00});
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
		using flow::cue_f;
		using namespace scheme;
	//	using namespace schedule;

		int constexpr N_store = (1<<3);
		int constexpr N_spool = (1<<7);

		using Sxd_slider = slider_t<spooled<extent_constant_t<N_spool>>>;
		using Par_cursor = occur::cursor_t<>;


		using Par_ramp = occur::reinferred_t<class RAMP, U_alpha>;
		using Dif_ramp = atom::differential_t<std::plus<Par_ramp>[2]>;
		using Prx_ramp = process::confined_t<void
		,	typename Sxd_slider::template suspend<flow::cue_s<Par_ramp>>
		>;
		Prx_ramp u_gate;
		
		u_gate <<=                 (Par_ramp{2.0});
		u_gate <<= cue_f(2, 6).then(Par_ramp{4.0});
		u_gate <<= cue_f(7, 9).then(Par_ramp{5.0});

		TRUE_((U_alpha) u_gate() == 2.0);//  0
		TRUE_((U_alpha) u_gate() == 2.0);//  1
		TRUE_((U_alpha) u_gate() == 2.0);//  2 <<
		TRUE_((U_alpha) u_gate() == 2.5);//  3
		TRUE_((U_alpha) u_gate() == 3.0);//  4
		TRUE_((U_alpha) u_gate() == 3.5);//  5
//		
		u_gate >>= Par_cursor(N_store);
		u_gate <<= cue_f(4) << (Par_ramp) 9.0;
//		
		TRUE_((U_alpha) u_gate() == 4.0);//  6 >>
		TRUE_((U_alpha) u_gate() == 4.0);//  7 <<
		TRUE_((U_alpha) u_gate() == 4.5);//  8
		TRUE_((U_alpha) u_gate() == 5.0);//  9 >>
		TRUE_((U_alpha) u_gate() == 9.0);// 10
		TRUE_((U_alpha) u_gate() == 9.0);// 11
		
		u_gate <<= cue_f(1) << (Par_ramp) 1.0;
		
		TRUE_((U_alpha) u_gate() == 9.0);// 12
		TRUE_((U_alpha) u_gate() == 1.0);// 13

	//	TODO: Test that the queue is being culled. \

	}
	/***/
	/**/
	TRY_("discrete")
	{
		using flow::cue_f;
		using namespace scheme;
	//	using namespace schedule;

		int constexpr N_store = (1<<3);
		int constexpr N_spool = (1<<7);

		using Sxd_slider = slider_t<spooled<extent_constant_t<N_spool>>>;
		using Par_cursor = occur::cursor_t<>;

		using Par_step = occur::reinferred_t<class STEP, U_alpha>;
		using Prx_step = process::confined_t<typename Sxd_slider::template suspend<Par_step>>;

		using U_event = flow::cue_s<Par_step>;
		
		Prx_step u_gate;
		
		u_gate <<=              (Par_step)  7;
	//	u_gate <<= cue_f( 0) << (Par_step)  7;
		u_gate <<= cue_f( 1) << (Par_step)  1;
		u_gate <<= cue_f( 3) << (Par_step) -1;
		u_gate <<= cue_f( 4) << (Par_step)  1;
		u_gate <<= cue_f( 5) << (Par_step) -1;
		u_gate <<= cue_f( 7) << (Par_step)  7;
		u_gate <<= cue_f( 7) << (Par_step) 77;
		u_gate <<= cue_f(10) << (Par_step) 99;
		
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
		u_gate >>= Par_cursor(N_store);
		u_gate <<= cue_f(4) << (Par_step) 11;

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
		using flow::cue_f;
		using namespace scheme;
	//	using namespace schedule;

		int constexpr N_store = (1<<3);
		int constexpr N_spool = (1<<7);

		using Sxd_slider = slider_t<spooled<extent_constant_t<N_spool>>>;
		using Par_cursor = occur::cursor_t<>;
		
		using Par_step   = occur::reinferred_t<class STEP, U_alpha>;
		using Prx_step   = process::confined_t<typename Sxd_slider::template suspend<Par_step>>;

		Prx_step u_gate;
		
	//	u_gate <<= cue_f(0) << (Par_step)  7;
		u_gate <<=             (Par_step)  7;
		TRUE_(u_gate() ==  7);
	//	...
		u_gate >>= Par_cursor(N_store);
	//	u_gate <<= cue_f(0) << (Par_step) 11;
		u_gate <<=             (Par_step) 11;
		TRUE_(u_gate() == 11);

	}
	/***/
}

////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
void slider_processor()
{
	using U_fit = bond::fit<>;
	using U_sigma = typename U_fit::sigma_type;
	using U_delta = typename U_fit::delta_type;
	using U_alpha = typename U_fit::alpha_type;

	using flow::cue_f;
	using namespace scheme;
//	using namespace schedule;

	int constexpr N_store = (1<<3);
	int constexpr N_spool = (1<<7);
	
	using Sxd_slider = slider_t<spooled<extent_constant_t<N_spool>>>;

	using Par_resize = occur::resize_t<>;
	using Par_cursor = occur::cursor_t<>;
	using Arr_store  = std::array<U_alpha, N_store>;
	Arr_store u_store{};

	using Par_step  = occur::reinferred_t<union STEP, U_alpha>;
	using Prx_step  = process::confined_t<typename Sxd_slider::template suspend<Par_step>>;
	using Pxr_step  = processor::monomer_t<Prx_step, As...>;
	auto  pxr_step  = Pxr_step::bind_f();
	
	using U_event  = flow::cue_s<Par_step>;

	pxr_step <<= Par_resize(N_store);
	/*/
	pxr_step <<= cue_f(0) << (Par_step)  7;
	pxr_step <<= cue_f(1) << (Par_step)  1;
	pxr_step <<= cue_f(3) << (Par_step) -1;
	pxr_step <<= cue_f(4) << (Par_step)  1;
	pxr_step <<= cue_f(5) << (Par_step) -1;
	pxr_step <<= cue_f(7) << (Par_step)  7;
	pxr_step <<= cue_f(7) << (Par_step) 77;
	/*/
	pxr_step <<= U_event(0,  7);
	pxr_step <<= U_event(1,  1);
	pxr_step <<= U_event(3, -1);
	pxr_step <<= U_event(4,  1);
	pxr_step <<= U_event(5, -1);
	pxr_step <<= U_event(7,  7);
	pxr_step <<= U_event(7, 77);
	/***/

	pxr_step >>= Par_cursor(N_store)*0; xtd::ranges::copy(pxr_step, u_store.begin());
	TRUE_(u_store == Arr_store {  7,  1,  1, -1,  1, -1, -1, 77});

	/**/
//	pxr_step <<= cue_f(0) << (Par_step) 77;
	pxr_step <<= cue_f(4) << (Par_step) 11;
	/*/
//	pxr_step <<= U_event(0, 77);
	pxr_step <<= U_event(4, 11);
	/***/

	pxr_step >>= Par_cursor(N_store)*1; xtd::ranges::copy(pxr_step, u_store.begin());
	TRUE_(u_store == Arr_store { 77, 77, 77, 77, 11, 11, 11, 11});

}
TAG_("slider", "processor")
{
	using namespace processor;
	TRY_("drive actual") {slider_processor<scheme::stored<>>();}
//	TRY_("drive virtual")  {slider_processor<>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
