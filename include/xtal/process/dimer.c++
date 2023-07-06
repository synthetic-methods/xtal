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
	using namespace _v3::views;

	using alpha_t = realized::alpha_t;
	using aphex_t = realized::aphex_t;
	using matrix_t = typename collage_t<alpha_t, 3, 2>::matrix_t;
	
	using remix_t = process::dimer_t<mix_t, control::redial<matrix_t>>;
	using mixer_t = processor::monomer_t<mix_t, collect<>>;

//	auto n01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
//	auto n10 = n01|_v3::views::transform([] (alpha_t n) {return n*10;});
//	auto n11 = n01|_v3::views::transform([] (alpha_t n) {return n*11;});
//
////	auto _1 = processor::lift_f((alpha_t) 1);
//	auto _1 = processor::let_f(iota(0, 10)|transform(to_f<alpha_t>));
//	auto _n = processor::let_f(iota(0, 10)|transform(to_f<alpha_t>));
//
//	auto io = mixer_t::binding_f(_1, _n);
//	io <<= matrix_t {{1, 2, 3}, {1, 2, 3}};


//	TODO: Implement `matrix` slices somehow: \

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
