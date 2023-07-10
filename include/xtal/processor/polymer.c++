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
template <int M_polymer=-1, int N_polymer=-1, int N_monomer=-1>
void test_polymer__control_spindle()
{
	using alpha_t = typename realized::alpha_t;
	using sigma_t = typename realized::sigma_t;
	using delta_t = typename realized::delta_t;
	using  iota_t = typename realized:: iota_t;

	using stage_t = control::stasis_t<>;
	using event_t = context::grain_s<stage_t>;

	size_t constexpr N = 1<<3;

	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;
	
//	using gate_t = process::confined_t<typename bias_t::template hold<(1<<7)>, typename stage_t::gauge>;
	using gate_t = process::confined_t<typename bias_t::poll, typename stage_t::gauge>;
	using fate_t = processor::monomer_t<gate_t, collect<N_monomer>>;
	using fate_u = typename fate_t::template bond_t<>;
	auto  fate_o =          fate_t::         bond_f();

	using vox_t = polymer_t<M_polymer, collect<N_polymer>>;
	using vox_u = typename vox_t::template bond_t<fate_u>;
	
//	auto  vox_o = vox_t::bond_f(XTAL_MOV_(fate_o));
//	auto  vox_o = vox_u(XTAL_MOV_(fate_o));
	auto  vox_o = vox_u();

	vox_o <<= bias_t(1);
	vox_o <<= resize_u(N);
	vox_o <<= bundle_f(event_t(62, 0)); REQUIRE(1 == vox_o.spool().size());
	vox_o <<= bundle_f(event_t(65, 0)); REQUIRE(2 == vox_o.spool().size());
	vox_o <<= bundle_f(event_t(69, 0)); REQUIRE(3 == vox_o.spool().size());
	vox_o <<= bundle_f(event_t(65, 0)); REQUIRE(4 == vox_o.spool().size());
//	vox_o <<= bias_t(2);
//	vox_o <<= resize_u(N);
	vox_o >>= sequel_u(N);
	
	REQUIRE(3 == vox_o.spool().size());
	REQUIRE(3 == vox_o.front());
	
	auto vox_oo_ = vox_o.spool().begin();
	REQUIRE(62 == vox_oo_++->head());
	REQUIRE(65 == vox_oo_++->head());
	REQUIRE(69 == vox_oo_++->head());

}
TEST_CASE("xtal/processor/polymer.hpp: control spindle")
{
//	test_polymer__control_spindle<-1, -1, -1>();
	test_polymer__control_spindle<64, -1, -1>();
//	test_polymer__control_spindle<-1, 64, -1>();
	test_polymer__control_spindle<64, 64, -1>();
//	test_polymer__control_spindle<-1, -1, 64>();
	test_polymer__control_spindle<64, -1, 64>();
//	test_polymer__control_spindle<-1, 64, 64>();
	test_polymer__control_spindle<64, 64, 64>();
	
}
/**/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
