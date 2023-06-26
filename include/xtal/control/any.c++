#pragma once
#include "../any.c++"
#include "./any.hpp"// testing...

#include "../message/all.hpp"
#include "../process/all.hpp"
#include "../processor/all.hpp"

XTAL_ENV_(push)
namespace xtal::context::__any
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__any;

using gate_t = control::label_t<typename realized::alpha_t, struct gate>;


////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/control/any.hpp: hold process")
{
	size_t constexpr N_size = 1<<3;

   using gated_t = process::confined_t<gate_t::template hold<(1<<7)>>;
	using delay_t = context::delay_s<>;
	using sequel_u   = message::sequel_t<>;

	gated_t gated_o;
	
	gated_o <<= bundle_f((delay_t) 0, (gate_t)  7);
	gated_o <<= bundle_f((delay_t) 1, (gate_t)  1);
	gated_o <<= bundle_f((delay_t) 3, (gate_t) -1);
	gated_o <<= bundle_f((delay_t) 4, (gate_t)  1);
	gated_o <<= bundle_f((delay_t) 5, (gate_t) -1);
	gated_o <<= bundle_f((delay_t) 7, (gate_t)  7);
	gated_o <<= bundle_f((delay_t) 7, (gate_t) 77);
	
	REQUIRE(gated_o() ==  7);
	REQUIRE(gated_o() ==  1);
	REQUIRE(gated_o() ==  1);
	REQUIRE(gated_o() == -1);
	REQUIRE(gated_o() ==  1);
	REQUIRE(gated_o() == -1);
	REQUIRE(gated_o() == -1);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
//	...
	gated_o >>= sequel_u(N_size);
	gated_o <<= bundle_f((delay_t) 4, (gate_t)  11);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 11);
	REQUIRE(gated_o() == 11);
	REQUIRE(gated_o() == 11);
	REQUIRE(gated_o() == 11);

//	REQUIRE(true);
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <template <typename, typename...> typename P_>
void hold_processor__test()
{
	size_t constexpr N_size = 1<<3;

   using gated_t = process::confined_t<gate_t::template hold<(1<<7)>>;
	using array_t = _std::array<typename realized::alpha_t, N_size>;
	using delay_t = context::delay_s<>;

	using resize_u = message::resize_t<>;
	using sequel_u = message::sequel_t<>;

	auto gated_o = P_<gated_t>::bind_f();
	auto array_o = array_t();
	
	gated_o <<= resize_u(N_size);
	gated_o <<= bundle_f((delay_t) 0, (gate_t)  7);
	gated_o <<= bundle_f((delay_t) 1, (gate_t)  1);
	gated_o <<= bundle_f((delay_t) 3, (gate_t) -1);
	gated_o <<= bundle_f((delay_t) 4, (gate_t)  1);
	gated_o <<= bundle_f((delay_t) 5, (gate_t) -1);
	gated_o <<= bundle_f((delay_t) 7, (gate_t)  7);
	gated_o <<= bundle_f((delay_t) 7, (gate_t) 77);

	gated_o >>= sequel_u(N_size)*0; _v3::ranges::copy(gated_o, array_o.begin());
	REQUIRE(array_o == array_t {  7,  1,  1, -1,  1, -1, -1, 77});

	gated_o <<= bundle_f((delay_t) 4, (gate_t)  11);
	gated_o >>= sequel_u(N_size)*1; _v3::ranges::copy(gated_o, array_o.begin());
	REQUIRE(array_o == array_t { 77, 77, 77, 77, 11, 11, 11, 11});

//	echo(gated_o); REQUIRE(true);
}
TEST_CASE("xtal/control/any.hpp: hold processor")
{
	hold_processor__test<processor::node_t>();
//	hold_processor__test<processor::edge_t>();
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
