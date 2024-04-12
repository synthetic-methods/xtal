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
	TRY_("drive")
	{
		using namespace resource;
	//	using namespace schedule;

		size_t constexpr N_store = (1<<3);
		size_t constexpr N_spool = (1<<7);

		using U_thunk = thunk_t<respool<constant_t<N_spool>>>;
		using U_render = occur::render_t<>;
		using U_cue = cell::cue_s<>;
		
		using V_gate = occur::inferred_t<class gate_a, typename bond::realized::alpha_t>;
		using U_gate = process::confined_t<typename U_thunk::template inqueue<V_gate>>;

		U_gate u_gate;
		
		u_gate <<=              (V_gate)  7;
	//	u_gate <<= (U_cue) 0 << (V_gate)  7;
		u_gate <<= (U_cue) 1 << (V_gate)  1;
		u_gate <<= (U_cue) 3 << (V_gate) -1;
		u_gate <<= (U_cue) 4 << (V_gate)  1;
		u_gate <<= (U_cue) 5 << (V_gate) -1;
		u_gate <<= (U_cue) 7 << (V_gate)  7;
		u_gate <<= (U_cue) 7 << (V_gate) 77;
		
		TRUE_(u_gate() ==  7);
		TRUE_(u_gate() ==  1);
		TRUE_(u_gate() ==  1);
		TRUE_(u_gate() == -1);
		TRUE_(u_gate() ==  1);
		TRUE_(u_gate() == -1);
		TRUE_(u_gate() == -1);
		TRUE_(u_gate() == 77);
		TRUE_(u_gate() == 77);
		TRUE_(u_gate() == 77);
	//	...
		u_gate >>= U_render(N_store);
		u_gate <<= (U_cue) 4 << (V_gate) 11;
		TRUE_(u_gate() == 77);
		TRUE_(u_gate() == 77);
		TRUE_(u_gate() == 77);
		TRUE_(u_gate() == 77);
		TRUE_(u_gate() == 11);
		TRUE_(u_gate() == 11);
		TRUE_(u_gate() == 11);
		TRUE_(u_gate() == 11);

	}
	TRY_("through")
	{

		using namespace resource;
	//	using namespace schedule;

		size_t constexpr N_store = (1<<3);
		size_t constexpr N_spool = (1<<7);

		using U_thunk = thunk_t<respool<constant_t<N_spool>>>;
		using U_render = occur::render_t<>;
		using U_cue = cell::cue_s<>;
		
		using V_gate = occur::inferred_t<class gate_a, typename bond::realized::alpha_t>;
		using U_gate = process::confined_t<typename U_thunk::template inqueue<V_gate>>;

		U_gate u_gate;
		
	//	u_gate <<= (U_cue) 0 << (V_gate)  7;
		u_gate <<=              (V_gate)  7;
		TRUE_(u_gate() ==  7);
	//	...
		u_gate >>= U_render(N_store);
	//	u_gate <<= (U_cue) 0 << (V_gate) 11;
		u_gate <<=              (V_gate) 11;
		TRUE_(u_gate() == 11);

	}
}


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
void thunk_processor()
{
	using namespace resource;
//	using namespace schedule;

	using alpha_t = typename bond::realized::alpha_t;

	class L_gate;

	size_t constexpr N_store = (1<<3);
	size_t constexpr N_spool = (1<<7);
	
	using U_thunk = thunk_t<respool<constant_t<N_spool>>>;
	using U_cue = cell::cue_s<>;

	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;
	using U_store = _std::array<alpha_t, N_store>;
	U_store u_store{};

	using V_gate  = occur::inferred_t<L_gate, alpha_t>;
	using Fn_gate = process::confined_t<typename U_thunk::template inqueue<V_gate>>;
	using Fx_gate = processor::monomer_t<Fn_gate, As...>;
	auto  fx_gate = Fx_gate::bind_f();
	
	fx_gate <<= U_resize(N_store);
	fx_gate <<= (U_cue) 0 << (V_gate)  7;
	fx_gate <<= (U_cue) 1 << (V_gate)  1;
	fx_gate <<= (U_cue) 3 << (V_gate) -1;
	fx_gate <<= (U_cue) 4 << (V_gate)  1;
	fx_gate <<= (U_cue) 5 << (V_gate) -1;
	fx_gate <<= (U_cue) 7 << (V_gate)  7;
	fx_gate <<= (U_cue) 7 << (V_gate) 77;

	fx_gate >>= U_render(N_store)*0; _v3::ranges::copy(fx_gate, u_store.begin());
	TRUE_(u_store == U_store {  7,  1,  1, -1,  1, -1, -1, 77});

	fx_gate <<= (U_cue) 4 << (V_gate) 11;
	
	fx_gate >>= U_render(N_store)*1; _v3::ranges::copy(fx_gate, u_store.begin());
	TRUE_(u_store == U_store { 77, 77, 77, 77, 11, 11, 11, 11});

}
TAG_("thunk", "processor")
{
	using namespace processor;
	TRY_("drive actual") {thunk_processor<resource::restore<>>();}
//	TRY_("drive virtual")  {thunk_processor<>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
