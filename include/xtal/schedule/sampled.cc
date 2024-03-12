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

		using U_sampled = sampled_t<spooled<N_spool>>;
		using U_scope = message::scope_t<>;
		using U_cue = compound::cue_s<>;
		
		using V_gate = message::label_t<typename atom::computer::alpha_t, struct __gate__>;
		using U_gate = process::confined_t<typename U_sampled::template inqueue<V_gate>>;

		U_gate u_gate;
		
		u_gate <<= (U_cue) 0 << (V_gate)  7;
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
		u_gate >>= U_scope(N_store);
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
}


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
void sampled_processor()
{
	using namespace resource;
//	using namespace schedule;

	size_t constexpr N_store = (1<<3);
	size_t constexpr N_spool = (1<<7);
	
	using U_sampled = sampled_t<spooled<N_spool>>;
	using U_cue = compound::cue_s<>;

	using U_resize = message::resize_t<>;
	using U_scope  = message::scope_t<>;
	using U_store  = _std::array<typename atom::computer::alpha_t, N_store>;
	U_store u_store {};

	using V_gate = message::label_t<typename atom::computer::alpha_t, struct __gate__>;
	using U_gate = process::confined_t<typename U_sampled::template inqueue<V_gate>>;
	
	using Z_gate = processor::monomer_t<U_gate, As...>;
	auto  z_gate = Z_gate::bond_f();
	
	z_gate <<= U_resize(N_store);
	z_gate <<= (U_cue) 0 << (V_gate)  7;
	z_gate <<= (U_cue) 1 << (V_gate)  1;
	z_gate <<= (U_cue) 3 << (V_gate) -1;
	z_gate <<= (U_cue) 4 << (V_gate)  1;
	z_gate <<= (U_cue) 5 << (V_gate) -1;
	z_gate <<= (U_cue) 7 << (V_gate)  7;
	z_gate <<= (U_cue) 7 << (V_gate) 77;

	z_gate >>= U_scope(N_store)*0; _v3::ranges::copy(z_gate, u_store.begin());
	TRUE_(u_store == U_store {  7,  1,  1, -1,  1, -1, -1, 77});

	z_gate <<= (U_cue) 4 << (V_gate) 11;
	z_gate >>= U_scope(N_store)*1; _v3::ranges::copy(z_gate, u_store.begin());
	TRUE_(u_store == U_store { 77, 77, 77, 77, 11, 11, 11, 11});

}
TAG_("sampled", "processor")
{
	using namespace processor;
	TRY_("drive material") {sampled_processor<resource::stored<>>();}
//	TRY_("drive virtual")  {sampled_processor<>();}// TODO?

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
