#pragma once
#include "./any.cc"
#include "./polymer.ii"// testing...

#include "./monomer.ii"
#include "../resourced/all.ii"


XTAL_ENV_(push)
namespace xtal::processor::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <size_t N_window=8, int N_store=-1, int N_spool=-1>
void polymer_provision_spine__locamotion()
{
	using alpha_t = typename common::computer::alpha_t;
	using sigma_t = typename common::computer::sigma_t;
	using delta_t = typename common::computer::delta_t;

	using stage_u = message::stage_t<>;
	using event_u = conduct::key_s<stage_u>;
	using empty_u = message::confined_t<>;

	using resize_u = message::resize_t<>;
	using scope_u = message::scope_t<>;
	
	using gate_t = process::confined_t<typename level_t::poll<>, typename stage_u::expect<>>;

	using vox_t = polymer_t<gate_t
	,	resourced::restore<N_store>
	,	resourced::respool<N_spool>
	>;
	auto o_vox = vox_t::bond_f();

// Resize, and set the default `level: 1` and `stage: final`:
	o_vox <<= resize_u(N_window);
	o_vox <<= level_t(1) <<= stage_u(-1);
	o_vox <<= event_u(62, 0); TRUE_(1 == o_vox.ensemble().size());
	o_vox <<= event_u(65, 0); TRUE_(2 == o_vox.ensemble().size());
	o_vox <<= event_u(69, 0); TRUE_(3 == o_vox.ensemble().size());
	o_vox <<= event_u(65, 0); TRUE_(4 == o_vox.ensemble().size());

//	Render:
//	o_vox <<= resize_u(N_window);
	o_vox >>= scope_u(N_window);
	
	TRUE_(3 == o_vox.ensemble().size());
	TRUE_(3 == o_vox.front());
	
	auto vox_oo_ = o_vox.ensemble().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

}
TAG_("polymer", "message", "spine")
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

template <size_t N_window=8, int N_store=0, int N_spool=0>
void polymer_provision_spool__compound()
{
	using alpha_t = typename common::computer::alpha_t;
	using sigma_t = typename common::computer::sigma_t;
	using delta_t = typename common::computer::delta_t;

	using stage_u = message::stage_t<>;
	using event_u = conduct::key_s<stage_u>;
	using empty_u = message::confined_t<>;

	using resize_u = message::resize_t<>;
	using scope_u = message::scope_t<>;
	
	using gate_t = process::confined_t<void
	,	typename stage_u::expect<>
	,	typename level_t::poll<>
	>;

	using vox_t = polymer_t<gate_t
	,	resourced::restore<N_store>
	,	resourced::respool<N_spool>
	>;
	auto o_vox = vox_t::bond_f();

// Set the default `stage: final`:
	o_vox <<= stage_u(-1);
	o_vox <<= event_u(62, 0) << level_t(1); TRUE_(1 == o_vox.ensemble().size());
	o_vox <<= event_u(65, 0) << level_t(2); TRUE_(2 == o_vox.ensemble().size());
	o_vox <<= event_u(69, 0) << level_t(3); TRUE_(3 == o_vox.ensemble().size());
	o_vox <<= event_u(65, 0) << level_t(4); TRUE_(4 == o_vox.ensemble().size());

//	Re(?:size|nder):
	o_vox <<= resize_u(N_window);
	o_vox >>= scope_u(N_window);
	
	TRUE_(3 == o_vox.ensemble().size());
	TRUE_(8 == o_vox.front());
	
	auto vox_oo_ = o_vox.ensemble().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

}
template <size_t N_window=8, int N_store=0, int N_spool=0>
void polymer_provision_spool__composited()
{
	using alpha_t = typename common::computer::alpha_t;
	using sigma_t = typename common::computer::sigma_t;
	using delta_t = typename common::computer::delta_t;

	using stage_u = message::stage_t<>;
	using event_u = conduct::key_s<stage_u>;
	using empty_u = message::confined_t<>;

	using resize_u = message::resize_t<>;
	using scope_u = message::scope_t<>;
	
	using gate_t = process::confined_t<void
	,	typename stage_u::expect<>
	,	typename level_t::poll<>
	>;

	using vox_t = polymer_t<gate_t
	,	resourced::restore<N_store>
	,	resourced::respool<N_spool>
	>;
	auto o_vox = vox_t::bond_f();

// Set the default `stage: final`:
	o_vox <<= stage_u(-1);
	o_vox <<= conduct::key_s<>(62) << stage_u(0) << level_t(1); TRUE_(1 == o_vox.ensemble().size());
	o_vox <<= conduct::key_s<>(65) << stage_u(0) << level_t(2); TRUE_(2 == o_vox.ensemble().size());
	o_vox <<= conduct::key_s<>(69) << stage_u(0) << level_t(3); TRUE_(3 == o_vox.ensemble().size());
	o_vox <<= conduct::key_s<>(65) << stage_u(0) << level_t(4); TRUE_(4 == o_vox.ensemble().size());

//	Re(?:size|nder):
	o_vox <<= resize_u(N_window);
	o_vox >>= scope_u(N_window);
	
	TRUE_(3 == o_vox.ensemble().size());
	TRUE_(8 == o_vox.front());
	
	auto vox_oo_ = o_vox.ensemble().begin();
	TRUE_(62 == vox_oo_++->head());
	TRUE_(65 == vox_oo_++->head());
	TRUE_(69 == vox_oo_++->head());

}
TAG_("polymer", "message", "ensemble")
{
	TRY_("with compound events")
	{
		polymer_provision_spool__compound<8, -1, -1>();
		polymer_provision_spool__compound<8, -1, 64>();
		polymer_provision_spool__compound<8, 64, -1>();
		polymer_provision_spool__compound<8, 64, 64>();

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
