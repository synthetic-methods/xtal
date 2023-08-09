#pragma once
#include "./any.cc"
#include "./polymer.ii"// testing...

#include "./monomer.ii"



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
	auto o_vox = vox_t::bond_f();

// Resize, and set the default `level: 1` and `stage: final`:
	o_vox <<= resize_u(N_window);
	o_vox <<= level_t(1) <<= stage_t(-1);
	o_vox <<= event_t(62, 0); TRUE_(1 == o_vox.stash().size());
	o_vox <<= event_t(65, 0); TRUE_(2 == o_vox.stash().size());
	o_vox <<= event_t(69, 0); TRUE_(3 == o_vox.stash().size());
	o_vox <<= event_t(65, 0); TRUE_(4 == o_vox.stash().size());

//	Render:
//	o_vox <<= resize_u(N_window);
	o_vox >>= sequel_u(N_window);
	
	TRUE_(3 == o_vox.stash().size());
	TRUE_(3 == o_vox.front());
	
	auto vox_oo_ = o_vox.stash().begin();
	TRUE_(62 == vox_oo_++->valve());
	TRUE_(65 == vox_oo_++->valve());
	TRUE_(69 == vox_oo_++->valve());

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
	auto o_vox = vox_t::bond_f();

// Set the default `stage: final`:
	o_vox <<= stage_t(-1);
	o_vox <<= event_t(62, 0) << level_t(1); TRUE_(1 == o_vox.stash().size());
	o_vox <<= event_t(65, 0) << level_t(2); TRUE_(2 == o_vox.stash().size());
	o_vox <<= event_t(69, 0) << level_t(3); TRUE_(3 == o_vox.stash().size());
	o_vox <<= event_t(65, 0) << level_t(4); TRUE_(4 == o_vox.stash().size());

//	Re(?:size|nder):
	o_vox <<= resize_u(N_window);
	o_vox >>= sequel_u(N_window);
	
	TRUE_(3 == o_vox.stash().size());
	TRUE_(8 == o_vox.front());
	
	auto vox_oo_ = o_vox.stash().begin();
	TRUE_(62 == vox_oo_++->valve());
	TRUE_(65 == vox_oo_++->valve());
	TRUE_(69 == vox_oo_++->valve());

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
	auto o_vox = vox_t::bond_f();

// Set the default `stage: final`:
	o_vox <<= stage_t(-1);
	o_vox <<= context::voice_s<>(62) << stage_t(0) << level_t(1); TRUE_(1 == o_vox.stash().size());
	o_vox <<= context::voice_s<>(65) << stage_t(0) << level_t(2); TRUE_(2 == o_vox.stash().size());
	o_vox <<= context::voice_s<>(69) << stage_t(0) << level_t(3); TRUE_(3 == o_vox.stash().size());
	o_vox <<= context::voice_s<>(65) << stage_t(0) << level_t(4); TRUE_(4 == o_vox.stash().size());

//	Re(?:size|nder):
	o_vox <<= resize_u(N_window);
	o_vox >>= sequel_u(N_window);
	
	TRUE_(3 == o_vox.stash().size());
	TRUE_(8 == o_vox.front());
	
	auto vox_oo_ = o_vox.stash().begin();
	TRUE_(62 == vox_oo_++->valve());
	TRUE_(65 == vox_oo_++->valve());
	TRUE_(69 == vox_oo_++->valve());

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
