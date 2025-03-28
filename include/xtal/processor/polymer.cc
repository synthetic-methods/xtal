#pragma once
#include "./any.cc"
#include "./polymer.hh"// testing...

#include "./monomer.hh"
#include "../provision/all.hh"
#include "../schedule/all.hh"

XTAL_ENV_(push)
namespace xtal::processor::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

template <int N_window=8, int N_store=-1, int N_spool=-1>
void polymer_provision_spine__locamotion()
{
/**/
	using _fit = bond::fit<>;
	using T_alpha  = typename _fit::alpha_type;
	using T_sigma  = typename _fit::sigma_type;
	using T_delta  = typename _fit::delta_type;

	using U_resize = occur::resize_t<>;
	using U_cursor = occur::cursor_t<>;
	using U_stage  = occur::stage_t<>;
	using U_event  = flow::key_s<U_stage>;
	using U_glider = schedule::glider_t<provision::spooled<extent_constant_t<0x20>>>;
	using U_cue    = flow::cue_s<>;

	using A_stored  = provision::stored  <extent_constant_t<N_store>>;
	using A_spooled = provision::spooled <extent_constant_t<N_spool>>;

	using A_gate   = bond::compose<typename U_glider::template accept<Ox_level>, typename U_stage::inspect<>>;
	using U_gate   = process::confined_t<A_gate>;

	using U_vox = polymer_t<U_gate, A_stored, A_spooled
//	, provision::voiced<void
//		,	provision::stored<extent_constant_t<-1>>
//		>
	>;
	auto u_vox = U_vox::bind_f();

// Resize, and set the default `level: 1` and `stage: final`:
	u_vox <<= U_resize(N_window);

	u_vox <<= Ox_level(1);
	u_vox >>= U_stage(-1);
	u_vox >>= U_event(62, 0); TRUE_(1 == u_vox.ensemble().size());
	u_vox >>= U_event(65, 0); TRUE_(2 == u_vox.ensemble().size());
	u_vox >>= U_event(69, 0); TRUE_(3 == u_vox.ensemble().size());
	u_vox >>= U_event(65, 0); TRUE_(4 == u_vox.ensemble().size());
	u_vox >>= U_event(62, 0); TRUE_(5 == u_vox.ensemble().size());

//	Render:
//	u_vox <<= U_resize(N_window);
	u_vox >>= U_cursor(N_window);
	
	TRUE_(3 == u_vox.ensemble().size());
	TRUE_(3 == u_vox.front());
	
	auto vox_oo_ = u_vox.ensemble().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());
	TRUE_(true);
/***/
}

TAG_("polymer", "occur", "spine")
{
	using _fit = bond::fit<>;
	using T_alpha  = typename _fit::alpha_type;
	using T_sigma  = typename _fit::sigma_type;
	using T_delta  = typename _fit::delta_type;

	using U_resize = occur::resize_t<>;
	using U_cursor = occur::cursor_t<>;
	using U_stage  = occur::stage_t<>;
	using U_event  = flow::key_s<U_stage>;
	using U_glider = schedule::glider_t<provision::spooled<extent_constant_t<0x20>>>;
	using U_cue    = flow::cue_s<>;

	using A_stored  = provision::stored  <extent_constant_t<-1>>;
	using A_spooled = provision::spooled <extent_constant_t<64>>;

	using U_gate   = process::confined_t<void
	,	typename U_glider::template accept<Ox_level>
	,	typename U_stage::inspect<>
	>;

	using U_vox = polymer_t<U_gate, A_stored, A_spooled
//	, provision::voiced<void
//		,	provision::stored<extent_constant_t<-1>>
//		>
	>;
	auto u_vox = U_vox::bind_f();
/**/

// Resize, and set the default `level: 1` and `stage: final`:
	u_vox <<= U_resize(8);
	u_vox <<= Ox_level(1);
	u_vox >>= U_stage(-1);
	u_vox >>= U_event(62, 0); TRUE_(1 == u_vox.ensemble().size());
	u_vox >>= U_event(65, 0); TRUE_(2 == u_vox.ensemble().size());
	u_vox >>= U_event(69, 0); TRUE_(3 == u_vox.ensemble().size());
	u_vox >>= U_event(65, 0); TRUE_(4 == u_vox.ensemble().size());
	u_vox >>= U_event(62, 0); TRUE_(5 == u_vox.ensemble().size());

//	Render:
//	u_vox <<= U_resize(8);
	u_vox >>= U_cursor(8);
	
	TRUE_(3 == u_vox.ensemble().size());
	TRUE_(3 == u_vox.front());
	
	auto vox_oo_ = u_vox.ensemble().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());
	TRUE_(true);
/***/
	TRY_("voice allocation/deallocation")
	{
		polymer_provision_spine__locamotion<8, -1, -1>();
		polymer_provision_spine__locamotion<8, -1, 64>();
		polymer_provision_spine__locamotion<8, 64, -1>();
		polymer_provision_spine__locamotion<8, 64, 64>();

	}
}


////////////////////////////////////////////////////////////////////////////////

template <int N_window=8, int N_store=0, int N_spool=0>
void polymer_provision_spool__combined()
{
	using T_alpha = typename bond::fit<>::alpha_type;
	using T_sigma = typename bond::fit<>::sigma_type;
	using T_delta = typename bond::fit<>::delta_type;

	using U_stage = occur::stage_t<>;
	using U_event = flow::key_s<U_stage>;

	using U_resize = occur::resize_t<>;
	using U_cursor = occur::cursor_t<>;
	
	using Z_process = process::confined_t<void
	,	typename U_stage::inspect<>
	,	typename Ox_level::poll<>
	>;
	using Z_processor = polymer_t<Z_process
	,	provision::stored <extent_constant_t<N_store>>
	,	provision::spooled<extent_constant_t<N_spool>>
	>;
	using Y_processor = typename Z_processor::template bind_t<>;
	Y_processor u_vox{};

// Set the default `stage: final`:
	u_vox <<= U_stage(-1);
	(void) u_vox.efflux(U_event(62, 0), Ox_level(1)); TRUE_(1 == u_vox.ensemble().size());
	(void) u_vox.efflux(U_event(65, 0), Ox_level(2)); TRUE_(2 == u_vox.ensemble().size());
	(void) u_vox.efflux(U_event(69, 0), Ox_level(3)); TRUE_(3 == u_vox.ensemble().size());
	(void) u_vox.efflux(U_event(65, 0), Ox_level(4)); TRUE_(4 == u_vox.ensemble().size());

//	Re(?:size|nder):
	u_vox <<= U_resize(N_window);
	u_vox >>= U_cursor(N_window);
	
	TRUE_(3 == u_vox.ensemble().size());
//	TRUE_(8 == u_vox.front());
//
//	auto vox_oo_ = u_vox.ensemble().begin();
//	TRUE_(62 == vox_oo_++->head());
//	TRUE_(65 == vox_oo_++->head());
//	TRUE_(69 == vox_oo_++->head());

}
template <int N_window=8, int N_store=0, int N_spool=0>
void polymer_provision_spool_composited()
{
	using T_alpha = typename bond::fit<>::alpha_type;
	using T_sigma = typename bond::fit<>::sigma_type;
	using T_delta = typename bond::fit<>::delta_type;

	using U_stage = occur::stage_t<>;
	using U_event = flow::key_s<U_stage>;

	using U_resize = occur::resize_t<>;
	using U_cursor = occur::cursor_t<>;
	
	using U_gate = process::confined_t<void
	,	typename U_stage::inspect<>
	,	typename Ox_level::poll<>
	>;

	using U_vox = polymer_t<U_gate
	,	provision::stored <extent_constant_t<N_store>>
	,	provision::spooled<extent_constant_t<N_spool>>
	>;
	auto u_vox = U_vox::bind_f();

// Set the default `stage: final`:
	u_vox >>= U_stage(-1);
	u_vox >>= flow::key_s<>(62) << U_stage(0) << Ox_level(1); TRUE_(1 == u_vox.ensemble().size());
	u_vox >>= flow::key_s<>(65) << U_stage(0) << Ox_level(2); TRUE_(2 == u_vox.ensemble().size());
	u_vox >>= flow::key_s<>(69) << U_stage(0) << Ox_level(3); TRUE_(3 == u_vox.ensemble().size());
	u_vox >>= flow::key_s<>(65) << U_stage(0) << Ox_level(4); TRUE_(4 == u_vox.ensemble().size());

//	Re(?:size|nder):
	u_vox <<= U_resize(N_window);
	u_vox >>= U_cursor(N_window);
	
	TRUE_(3 == u_vox.ensemble().size());
//	TRUE_(8 == u_vox.front());
//
//	auto vox_oo_ = u_vox.ensemble().begin();
//	TRUE_(62 == vox_oo_++->head());
//	TRUE_(65 == vox_oo_++->head());
//	TRUE_(69 == vox_oo_++->head());

}
TAG_("polymer", "occur", "ensemble")
{
	TRY_("with combined events")
	{
		polymer_provision_spool__combined<8, -1, -1>();
		polymer_provision_spool__combined<8, -1, 64>();
		polymer_provision_spool__combined<8, 64, -1>();
		polymer_provision_spool__combined<8, 64, 64>();

	}
	TRY_("with composited events")
	{
		polymer_provision_spool_composited<8, -1, -1>();
		polymer_provision_spool_composited<8, -1, 64>();
		polymer_provision_spool_composited<8, 64, -1>();
		polymer_provision_spool_composited<8, 64, 64>();

	}
}


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
