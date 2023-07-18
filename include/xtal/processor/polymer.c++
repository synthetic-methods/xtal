#pragma once
#include "./any.c++"
#include "./polymer.hpp"// testing...

#include "./monomer.hpp"



XTAL_ENV_(push)
namespace xtal::processor::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
template <size_t N_window=8, int N_collect=-1, int N_collate=-1>
void test_polymer__control_spine()
{
	using alpha_t = typename realized::alpha_t;
	using sigma_t = typename realized::sigma_t;
	using delta_t = typename realized::delta_t;
	using  iota_t = typename realized:: iota_t;

	using stage_t = control::stasis_t<>;
	using event_t = context::grain_s<stage_t>;

	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;
	
	using gate_t = process::confined_t<typename level_t::poll, typename stage_t::gauge>;

	using vox_t = polymer_t<gate_t, collect<N_collect>, collate<N_collate>>;
	auto  vox_o = vox_t::bond_f();

	vox_o <<= resize_u(N_window);
	vox_o <<= stage_t(-1);// Set the protovoice `stage` to `{terminate,cut}`.
	vox_o <<= level_t(1);// Set the `level` for the protovoice (and therefore all voices).
	vox_o <<= bundle_f(event_t(62, 0)); REQUIRE(1 == vox_o.spool().size());
	vox_o <<= bundle_f(event_t(65, 0)); REQUIRE(2 == vox_o.spool().size());
	vox_o <<= bundle_f(event_t(69, 0)); REQUIRE(3 == vox_o.spool().size());
	vox_o <<= bundle_f(event_t(65, 0)); REQUIRE(4 == vox_o.spool().size());
//	vox_o <<= level_t(2);
//	vox_o <<= resize_u(N_window);
	vox_o >>= sequel_u(N_window);
	
	REQUIRE(3 == vox_o.spool().size());
	REQUIRE(3 == vox_o.front());
	
	auto vox_oo_ = vox_o.spool().begin();
	REQUIRE(62 == vox_oo_++->head());
	REQUIRE(65 == vox_oo_++->head());
	REQUIRE(69 == vox_oo_++->head());

}
TEST_CASE("xtal/processor/polymer.hpp: control spine")
{
	test_polymer__control_spine<8, -1, -1>();
	test_polymer__control_spine<8, -1, 64>();
	test_polymer__control_spine<8, 64, -1>();
	test_polymer__control_spine<8, 64, 64>();

}
/**/
////////////////////////////////////////////////////////////////////////////////
/**/
template <size_t N_window=8, int N_collect=-1, int N_collate=-1>
void test_polymer__control_spool()
{
	using alpha_t = typename realized::alpha_t;
	using sigma_t = typename realized::sigma_t;
	using delta_t = typename realized::delta_t;
	using  iota_t = typename realized:: iota_t;

	using stage_t = control::stasis_t<>;
	using event_t = context::grain_s<stage_t>;

	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;
	
	using gate_t = process::confined_t<typename level_t::poll, typename stage_t::gauge>;

	using vox_t = polymer_t<gate_t, collect<N_collect>, collate<N_collate>>;
	auto  vox_o = vox_t::bond_f();

	vox_o <<= resize_u(N_window);
	vox_o <<= stage_t(-1);// Set the protovoice `stage` to `{terminate,cut}`.
	vox_o <<= bundle_f(event_t(62, 0), level_t(1)); REQUIRE(1 == vox_o.spool().size());
	vox_o <<= bundle_f(event_t(65, 0), level_t(2)); REQUIRE(2 == vox_o.spool().size());
	vox_o <<= bundle_f(event_t(69, 0), level_t(3)); REQUIRE(3 == vox_o.spool().size());
	vox_o <<= bundle_f(event_t(65, 0), level_t(4)); REQUIRE(4 == vox_o.spool().size());
//	vox_o <<= level_t(2);
//	vox_o <<= resize_u(N_window);
	vox_o >>= sequel_u(N_window);
	
	REQUIRE(3 == vox_o.spool().size());
	REQUIRE(8 == vox_o.front());
	
	auto vox_oo_ = vox_o.spool().begin();
	REQUIRE(62 == vox_oo_++->head());
	REQUIRE(65 == vox_oo_++->head());
	REQUIRE(69 == vox_oo_++->head());

}
TEST_CASE("xtal/processor/polymer.hpp: control spool")
{
	test_polymer__control_spool<8, -1, -1>();
	test_polymer__control_spool<8, -1, 64>();
	test_polymer__control_spool<8, 64, -1>();
	test_polymer__control_spool<8, 64, 64>();

}
/**/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
