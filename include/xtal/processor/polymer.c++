#pragma once
#include "./any.c++"
#include "./polymer.ipp"// testing...

#include "./monomer.ipp"



XTAL_ENV_(push)
namespace xtal::processor::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <size_t N_window=8, int N_store=-1, int N_stash=-1>
void polymer_control_spine__locamotion()
{
	using alpha_t = typename computer::alpha_t;
	using sigma_t = typename computer::sigma_t;
	using delta_t = typename computer::delta_t;

	using stage_t = control::stasis_t<>;
	using event_t = context::voice_s<stage_t>;
	using empty_t = control::confined_t<>;

	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;
	
	using gate_t = process::confined_t<typename level_t::poll, typename stage_t::gauge>;

	using vox_t = polymer_t<gate_t
	,	restore<N_store>
	,	restash<N_stash>
	,	typename empty_t::rend
	>;
	auto  vox_o = vox_t::bond_f();

// Resize, and set the default `level: 1` and `stage: final`:
	vox_o << resize_u(N_window);
	vox_o << level_t(1) << stage_t(-1);
	vox_o << pack_f(event_t(62, 0)); TRUE_(1 == vox_o.stash().size());
	vox_o << pack_f(event_t(65, 0)); TRUE_(2 == vox_o.stash().size());
	vox_o << pack_f(event_t(69, 0)); TRUE_(3 == vox_o.stash().size());
	vox_o << pack_f(event_t(65, 0)); TRUE_(4 == vox_o.stash().size());

//	Render:
//	vox_o << resize_u(N_window);
	vox_o >> sequel_u(N_window);
	
	TRUE_(3 == vox_o.stash().size());
	TRUE_(3 == vox_o.front());
	
	auto vox_oo_ = vox_o.stash().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

}
TAG_("polymer", "control", "spine")
{
	TRY_("voice allocation/deallocation")
	{
		polymer_control_spine__locamotion<8,  0,  0>();
		polymer_control_spine__locamotion<8,  0, 64>();
		polymer_control_spine__locamotion<8, 64,  0>();
		polymer_control_spine__locamotion<8, 64, 64>();

	}
}


////////////////////////////////////////////////////////////////////////////////

template <size_t N_window=8, int N_store=0, int N_stash=0>
void polymer_control_stash__compound()
{
	using alpha_t = typename computer::alpha_t;
	using sigma_t = typename computer::sigma_t;
	using delta_t = typename computer::delta_t;

	using stage_t = control::stasis_t<>;
	using event_t = context::voice_s<stage_t>;
	using empty_t = control::confined_t<>;

	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;
	
	using gate_t = process::confined_t<void
	,	typename stage_t::gauge
	,	typename level_t::poll
	>;

	using vox_t = polymer_t<gate_t
	,	restore<N_store>
	,	restash<N_stash>
	>;
	auto  vox_o = vox_t::bond_f();

// Set the default `stage: final`:
	vox_o << stage_t(-1);
	vox_o << pack_f(event_t(62, 0), level_t(1)); TRUE_(1 == vox_o.stash().size());
	vox_o << pack_f(event_t(65, 0), level_t(2)); TRUE_(2 == vox_o.stash().size());
	vox_o << pack_f(event_t(69, 0), level_t(3)); TRUE_(3 == vox_o.stash().size());
	vox_o << pack_f(event_t(65, 0), level_t(4)); TRUE_(4 == vox_o.stash().size());

//	Re(?:size|nder):
	vox_o << resize_u(N_window) >> sequel_u(N_window);
	
	TRUE_(3 == vox_o.stash().size());
	TRUE_(8 == vox_o.front());
	
	auto vox_oo_ = vox_o.stash().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

}
template <size_t N_window=8, int N_store=0, int N_stash=0>
void polymer_control_stash__composited()
{
	using alpha_t = typename computer::alpha_t;
	using sigma_t = typename computer::sigma_t;
	using delta_t = typename computer::delta_t;

	using stage_t = control::stasis_t<>;
	using event_t = context::voice_s<stage_t>;
	using empty_t = control::confined_t<>;

	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;
	
	using gate_t = process::confined_t<void
	,	typename stage_t::gauge
	,	typename level_t::poll
	>;

	using vox_t = polymer_t<gate_t
	,	restore<N_store>
	,	restash<N_stash>
	>;
	auto  vox_o = vox_t::bond_f();

// Set the default `stage: final`:
	vox_o << stage_t(-1);
	vox_o << pack_f(context::voice_s<>(62), stage_t(0), level_t(1)); TRUE_(1 == vox_o.stash().size());
	vox_o << pack_f(context::voice_s<>(65), stage_t(0), level_t(2)); TRUE_(2 == vox_o.stash().size());
	vox_o << pack_f(context::voice_s<>(69), stage_t(0), level_t(3)); TRUE_(3 == vox_o.stash().size());
	vox_o << pack_f(context::voice_s<>(65), stage_t(0), level_t(4)); TRUE_(4 == vox_o.stash().size());

//	Re(?:size|nder):
	vox_o << resize_u(N_window) >> sequel_u(N_window);
	
	TRUE_(3 == vox_o.stash().size());
	TRUE_(8 == vox_o.front());
	
	auto vox_oo_ = vox_o.stash().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

}
TAG_("polymer", "control", "stash")
{
	TRY_("with compound events")
	{
		polymer_control_stash__compound<8,  0,  0>();
		polymer_control_stash__compound<8,  0, 64>();
		polymer_control_stash__compound<8, 64,  0>();
		polymer_control_stash__compound<8, 64, 64>();

	}
	TRY_("with composited events")
	{
		polymer_control_stash__composited<8,  0,  0>();
		polymer_control_stash__composited<8,  0, 64>();
		polymer_control_stash__composited<8, 64,  0>();
		polymer_control_stash__composited<8, 64, 64>();

	}
}
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
