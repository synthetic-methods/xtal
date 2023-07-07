#pragma once
#include "./any.c++"
#include "./dimer.hpp"// testing...

#include "../processor/monomer.hpp"



XTAL_ENV_(push)
namespace xtal::process::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/process/dimer.hpp: interlude")
{
	using namespace _v3::views;

	using matrix_t = typename collage_t<int, 2, 3>::matrix_t;
	using column_t = typename matrix_t::value_type;
	
	using remix_t = process::dimer_t<mix_t, control::redial<matrix_t>>;
	using mixer_t = processor::monomer_t<remix_t, collect<>>;

	auto oo = remix_t(); oo <<= matrix_t {{1, 2}, {3, 4}, {5, 6}};
	REQUIRE(oo(10, 100) == 1290);// (1*10 + 2*100) + (3*10 + 4*100) + (5*10 + 6*100)

	auto _1 = processor::lift_f(1);
	auto _n = processor::lift_f(iota(0, 10));
//
	auto io = mixer_t::bond_f(_1, _n);
	io <<= matrix_t {{1, 2}, {3, 4}, {5, 6}};
	io <<= control::resize_t<>(3);
	io >>= control::sequel_t<>(3);

	REQUIRE(_v3::ranges::equal(io, _std::vector { 9, 21, 33}));
//	(1*1 + 2*0) + (3*1 + 4*0) + (5*1 + 6*0)
//	(1*1 + 2*1) + (3*1 + 4*1) + (5*1 + 6*1)
//	(1*1 + 2*2) + (3*1 + 4*2) + (5*1 + 6*2)

//	TODO: Implement `matrix` slices somehow... \
	...probably just by prefacing with e.g. `context::subscript_s`. \

//	io <<= bundle_f(control::matrix_t<2> {1.0, 2.0, 3.0, 4.0});
//	io <<= bundle_f(control::matrix_t<2, 3> {4.0});
//
//	io <<= bundle_f(control::dot_f<2>(3), 0.5);
//	io <<= bundle_f(control::dot_f<2>(), 1.0, 2.0, 3.0, 4.0);
//	io <<= bundle_f(control::dot_f<>(3), 0.5, 0.5, 0.5);

}
/**/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
