#pragma once
#include "./any.c++"
#include "./polymer.hpp"// testing...

#include "./monomer.hpp"



XTAL_ENV_(push)
namespace xtal::processor::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <size_t N_window=8, int N_collect=-1, int N_collate=-1>
void polymer_control_spine__locamotion()
{
	using alpha_t = typename realized::alpha_t;
	using sigma_t = typename realized::sigma_t;
	using delta_t = typename realized::delta_t;
	using  iota_t = typename realized:: iota_t;

	using stage_t = control::stasis_t<>;
	using event_t = context::voice_s<stage_t>;
	using empty_t = control::confined_t<>;

	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;
	
	using gate_t = process::confined_t<typename level_t::poll, typename stage_t::gauge>;

	using vox_t = polymer_t<gate_t
	,	collect<N_collect>
	,	collate<N_collate>
	,	typename empty_t::rend
	>;
	auto  vox_o = vox_t::bond_f();

// Resize, and set the default `level: 1` and `stage: final`:
	vox_o << resize_u(N_window);
	vox_o << level_t(1) << stage_t(-1);
	vox_o << bundle_f(event_t(62, 0)); TRUE_(1 == vox_o.spool().size());
	vox_o << bundle_f(event_t(65, 0)); TRUE_(2 == vox_o.spool().size());
	vox_o << bundle_f(event_t(69, 0)); TRUE_(3 == vox_o.spool().size());
	vox_o << bundle_f(event_t(65, 0)); TRUE_(4 == vox_o.spool().size());

//	Render:
//	vox_o << resize_u(N_window);
	vox_o >> sequel_u(N_window);
	
	TRUE_(3 == vox_o.spool().size());
	TRUE_(3 == vox_o.front());
	
	auto vox_oo_ = vox_o.spool().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

}
TAG_("polymer", "control", "spine")
{
	TRY_("voice allocation/deallocation")
	{
		polymer_control_spine__locamotion<8, -1, -1>();
		polymer_control_spine__locamotion<8, -1, 64>();
		polymer_control_spine__locamotion<8, 64, -1>();
		polymer_control_spine__locamotion<8, 64, 64>();

	}
}


////////////////////////////////////////////////////////////////////////////////

template <size_t N_window=8, int N_collect=-1, int N_collate=-1>
void polymer_control_spool__compound()
{
	using alpha_t = typename realized::alpha_t;
	using sigma_t = typename realized::sigma_t;
	using delta_t = typename realized::delta_t;
	using  iota_t = typename realized:: iota_t;

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
	,	collect<N_collect>
	,	collate<N_collate>
	>;
	auto  vox_o = vox_t::bond_f();

// Set the default `stage: final`:
	vox_o << stage_t(-1);
	vox_o << bundle_f(event_t(62, 0), level_t(1)); TRUE_(1 == vox_o.spool().size());
	vox_o << bundle_f(event_t(65, 0), level_t(2)); TRUE_(2 == vox_o.spool().size());
	vox_o << bundle_f(event_t(69, 0), level_t(3)); TRUE_(3 == vox_o.spool().size());
	vox_o << bundle_f(event_t(65, 0), level_t(4)); TRUE_(4 == vox_o.spool().size());

//	Re(?:size|nder):
	vox_o << resize_u(N_window) >> sequel_u(N_window);
	
	TRUE_(3 == vox_o.spool().size());
	TRUE_(8 == vox_o.front());
	
	auto vox_oo_ = vox_o.spool().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

}
template <size_t N_window=8, int N_collect=-1, int N_collate=-1>
void polymer_control_spool__composited()
{
	using alpha_t = typename realized::alpha_t;
	using sigma_t = typename realized::sigma_t;
	using delta_t = typename realized::delta_t;
	using  iota_t = typename realized:: iota_t;

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
	,	collect<N_collect>
	,	collate<N_collate>
	>;
	auto  vox_o = vox_t::bond_f();

// Set the default `stage: final`:
	vox_o << stage_t(-1);
	vox_o << bundle_f(context::voice_s<>(62), stage_t(0), level_t(1)); TRUE_(1 == vox_o.spool().size());
	vox_o << bundle_f(context::voice_s<>(65), stage_t(0), level_t(2)); TRUE_(2 == vox_o.spool().size());
	vox_o << bundle_f(context::voice_s<>(69), stage_t(0), level_t(3)); TRUE_(3 == vox_o.spool().size());
	vox_o << bundle_f(context::voice_s<>(65), stage_t(0), level_t(4)); TRUE_(4 == vox_o.spool().size());

//	Re(?:size|nder):
	vox_o << resize_u(N_window) >> sequel_u(N_window);
	
	TRUE_(3 == vox_o.spool().size());
	TRUE_(8 == vox_o.front());
	
	auto vox_oo_ = vox_o.spool().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

}
TAG_("polymer", "control", "spool")
{
	TRY_("with compound events")
	{
		polymer_control_spool__compound<8, -1, -1>();
		polymer_control_spool__compound<8, -1, 64>();
		polymer_control_spool__compound<8, 64, -1>();
		polymer_control_spool__compound<8, 64, 64>();

	}
	TRY_("with composited events")
	{
		polymer_control_spool__composited<8, -1, -1>();
		polymer_control_spool__composited<8, -1, 64>();
		polymer_control_spool__composited<8, 64, -1>();
		polymer_control_spool__composited<8, 64, 64>();

	}
}
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
