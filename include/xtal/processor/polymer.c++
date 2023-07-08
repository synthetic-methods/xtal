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
TEST_CASE("xtal/processor/polymer.hpp: true")
{
	using alpha_t = typename realized::alpha_t;
	using sigma_t = typename realized::sigma_t;
	using delta_t = typename realized::delta_t;
	using  iota_t = typename realized:: iota_t;

	using event_t = context::grain_s<control::stasis_t<>>;

	size_t constexpr N_size = 1<<3;

	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;
	
	using gate_t = process::confined_t<typename bias_t::template hold<(1<<7)>>;
	using fate_t = processor::monomer_t<gate_t, collect<>>;
	using fate_u = fate_t::bond_t<>;
	auto  fate_o = fate_t::bond_f();

	using vox_t = polymer_t<(1<<7), collect<128>>;
	using vox_u = typename vox_t::template bond_t<fate_u>;
	
//	auto  vox_o = vox_t::bond_f(fate_o);
//	auto  vox_o = vox_u();

//	vox_o <<= resize_u(N_size);
//	vox_o <<= bundle_f(event_t(62, 0), bias_t(1)); echo(1, '=', vox_o.spool().size());
//	vox_o <<= bundle_f(event_t(65, 0), bias_t(1)); echo(2, '=', vox_o.spool().size());
//	vox_o <<= bundle_f(event_t(69, 0), bias_t(1)); echo(3, '=', vox_o.spool().size());
//	vox_o <<= bundle_f(event_t(69, 0), bias_t(1)); echo(4, '=', vox_o.spool().size());
//	vox_o >>= sequel_u(N_size);                    echo(3, '=', vox_o.spool().size());


}
/**/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
