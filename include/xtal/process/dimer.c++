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
TEST_CASE("xtal/process/dimer.hpp: true")
{
	using alpha_t = realized::alpha_t;
	using aphex_t = realized::aphex_t;
	using matrix_t = typename collage_t<alpha_t, 3, 4>::matrix_t;
	
	using remix_t = process::dimer_t<mix_t, control::redial<matrix_t>>;
	using remixer_t = processor::monomer_t<remix_t, collect<-1>>;
//	TODO: Implement `matrix` slices somehow: \

//	auto io = remixer_t::binding_f(1, a, b, c);
//
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
