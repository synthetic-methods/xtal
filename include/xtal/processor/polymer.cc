#pragma once
#include "./any.cc"
#include "./polymer.hh"// testing...

#include "./monomer.hh"
#include "../resource/all.hh"
#include "../schedule/all.hh"








XTAL_ENV_(push)
namespace xtal::processor::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <size_t N_window=8, int N_buffer=-1, int N_spool=-1>
void polymer_provision_spine__locamotion()
{
	using re = bond::realized;
	using U_alpha  = typename re::alpha_t;
	using U_sigma  = typename re::sigma_t;
	using U_delta  = typename re::delta_t;

	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;
	using U_stage  = occur::stage_t<>;
	using U_event  = cell::key_s<U_stage>;
	using U_thunk  = schedule::thunk_t<resource::spool<(1<<5)>>;
	using U_cue    = cell::cue_s<>;

	//\
	using W_gate   = typename level_t::poll<>;
	using W_gate   = typename U_thunk::template inqueue<level_t>;
	using U_gate   = process::confined_t<W_gate, typename U_stage::expect<>>;

	using U_vox = polymer_t<U_gate
	,	resource::buffer<N_buffer>
	,	resource::spool<N_spool>
	>;
	auto u_vox = U_vox::bind_f();

// Resize, and set the default `level: 1` and `stage: final`:
	u_vox <<= U_resize(N_window);
	u_vox <<= level_t(1) <<= U_stage(-1);
	u_vox <<= U_event(62, 0); TRUE_(1 == u_vox.ensemble().size());
	u_vox <<= U_event(65, 0); TRUE_(2 == u_vox.ensemble().size());
	u_vox <<= U_event(69, 0); TRUE_(3 == u_vox.ensemble().size());
	u_vox <<= U_event(65, 0); TRUE_(4 == u_vox.ensemble().size());
	u_vox <<= U_event(62, 0); TRUE_(5 == u_vox.ensemble().size());

//	Render:
//	u_vox <<= U_resize(N_window);
	u_vox >>= U_render(N_window);
	
	TRUE_(3 == u_vox.ensemble().size());
	TRUE_(3 == u_vox.front());
	
	auto vox_oo_ = u_vox.ensemble().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

}
TAG_("polymer", "occur", "spine")
{
	TRY_("voice allocation/deallocation")
	{
		polymer_provision_spine__locamotion<8, -1, -1>();
		polymer_provision_spine__locamotion<8, -1, 64>();
		polymer_provision_spine__locamotion<8, 64, -1>();
		polymer_provision_spine__locamotion<8, 64, 64>();

	}
}


////////////////////////////////////////////////////////////////////////////////

template <size_t N_window=8, int N_buffer=0, int N_spool=0>
void polymer_provision_spool__combined()
{
	using U_alpha = typename bond::realized::alpha_t;
	using U_sigma = typename bond::realized::sigma_t;
	using U_delta = typename bond::realized::delta_t;

	using U_stage = occur::stage_t<>;
	using U_event = cell::key_s<U_stage>;

	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;
	
	using U_gate = process::confined_t<void
	,	typename U_stage::expect<>
	,	typename level_t::poll<>
	>;

	using U_vox = polymer_t<U_gate
	,	resource::buffer<N_buffer>
	,	resource::spool<N_spool>
	>;
	auto u_vox = U_vox::bind_f();

// Set the default `stage: final`:
	u_vox <<= U_stage(-1);
	u_vox <<= U_event(62, 0) << level_t(1); TRUE_(1 == u_vox.ensemble().size());
	u_vox <<= U_event(65, 0) << level_t(2); TRUE_(2 == u_vox.ensemble().size());
	u_vox <<= U_event(69, 0) << level_t(3); TRUE_(3 == u_vox.ensemble().size());
	u_vox <<= U_event(65, 0) << level_t(4); TRUE_(4 == u_vox.ensemble().size());

//	Re(?:size|nder):
	u_vox <<= U_resize(N_window);
	u_vox >>= U_render(N_window);
	
	TRUE_(3 == u_vox.ensemble().size());
	TRUE_(8 == u_vox.front());
	
	auto vox_oo_ = u_vox.ensemble().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

}
template <size_t N_window=8, int N_buffer=0, int N_spool=0>
void polymer_provision_spool__composited()
{
	using U_alpha = typename bond::realized::alpha_t;
	using U_sigma = typename bond::realized::sigma_t;
	using U_delta = typename bond::realized::delta_t;

	using U_stage = occur::stage_t<>;
	using U_event = cell::key_s<U_stage>;

	using U_resize = occur::resize_t<>;
	using U_render = occur::render_t<>;
	
	using U_gate = process::confined_t<void
	,	typename U_stage::expect<>
	,	typename level_t::poll<>
	>;

	using U_vox = polymer_t<U_gate
	,	resource::buffer<N_buffer>
	,	resource::spool<N_spool>
	>;
	auto u_vox = U_vox::bind_f();

// Set the default `stage: final`:
	u_vox <<= U_stage(-1);
	u_vox <<= cell::key_s<>(62) << U_stage(0) << level_t(1); TRUE_(1 == u_vox.ensemble().size());
	u_vox <<= cell::key_s<>(65) << U_stage(0) << level_t(2); TRUE_(2 == u_vox.ensemble().size());
	u_vox <<= cell::key_s<>(69) << U_stage(0) << level_t(3); TRUE_(3 == u_vox.ensemble().size());
	u_vox <<= cell::key_s<>(65) << U_stage(0) << level_t(4); TRUE_(4 == u_vox.ensemble().size());

//	Re(?:size|nder):
	u_vox <<= U_resize(N_window);
	u_vox >>= U_render(N_window);
	
	TRUE_(3 == u_vox.ensemble().size());
	TRUE_(8 == u_vox.front());
	
	auto vox_oo_ = u_vox.ensemble().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

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
		polymer_provision_spool__composited<8, -1, -1>();
		polymer_provision_spool__composited<8, -1, 64>();
		polymer_provision_spool__composited<8, 64, -1>();
		polymer_provision_spool__composited<8, 64, 64>();

	}
}
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
