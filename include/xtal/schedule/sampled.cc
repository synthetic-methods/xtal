#pragma once
#include "./any.cc"
#include "./sampled.ii"// testing...

#include "../resource/all.ii"
#include "../processor/monomer.ii"


XTAL_ENV_(push)
namespace xtal::schedule::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("sampled", "process")
{
	TRY_("drive")
	{
		using namespace resource;
	//	using namespace schedule;

		size_t constexpr N_store = (1<<3);
		size_t constexpr N_spool = (1<<7);

		using sampled_u = sampled_t<respool<N_spool>>;
		using scope_u = message::scope_t<>;
		using cue_t = conduct::cue_s<>;
		
		using gate_t = message::label_t<typename common::computer::alpha_t, struct __gate__>;
		using gate_y = process::confined_t<typename sampled_u::template inqueue<gate_t>>;

		gate_y o_gate;
		
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
void sampled_processor()
{
	using namespace resource;
//	using namespace schedule;

	size_t constexpr N_store = (1<<3);
	size_t constexpr N_spool = (1<<7);
	
	using sampled_u = sampled_t<respool<N_spool>>;
	using cue_t = conduct::cue_s<>;

	using resize_u = message::resize_t<>;
	using scope_u  = message::scope_t<>;
	using store_u  = _std::array<typename common::computer::alpha_t, N_store>;
	store_u o_store {};

	using gate_t = message::label_t<typename common::computer::alpha_t, struct __gate__>;
	using gate_y = process::confined_t<typename sampled_u::template inqueue<gate_t>>;
	using gate_z = processor::monomer_t<gate_y, As...>;
	auto  o_gate = gate_z::bond_f();
	
	o_gate <<= resize_u(N_store);
	o_gate <<= (cue_t) 0 << (gate_t)  7;
	o_gate <<= (cue_t) 1 << (gate_t)  1;
	o_gate <<= (cue_t) 3 << (gate_t) -1;
	o_gate <<= (cue_t) 4 << (gate_t)  1;
	o_gate <<= (cue_t) 5 << (gate_t) -1;
	o_gate <<= (cue_t) 7 << (gate_t)  7;
	o_gate <<= (cue_t) 7 << (gate_t) 77;

	o_gate >>= scope_u(N_store)*0; _v3::ranges::copy(o_gate, o_store.begin());
	TRUE_(o_store == store_u {  7,  1,  1, -1,  1, -1, -1, 77});

	o_gate <<= (cue_t) 4 << (gate_t) 11;
	o_gate >>= scope_u(N_store)*1; _v3::ranges::copy(o_gate, o_store.begin());
	TRUE_(o_store == store_u { 77, 77, 77, 77, 11, 11, 11, 11});

}
TAG_("sampled", "processor")
{
	using namespace processor;
	TRY_("drive material") {sampled_processor<resource::restore<>>();}
//	TRY_("drive virtual")  {sampled_processor<>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
