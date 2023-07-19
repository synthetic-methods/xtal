#pragma once
#include "./any.c++"
#include "./matrix.hpp"// testing...

#include "../processor/monomer.hpp"



XTAL_ENV_(push)
namespace xtal::process::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/process/matrix.hpp: process matrix")
{
	using namespace _v3::views;

	using group_t = typename collate_t<2, 3>::template group_t<int>;

	using remix_t = process::matrix_t<group_t, mix_t>;
	using mixer_t = processor::monomer_t<remix_t, collect<-1>>;

	auto io = remix_t();
	io << group_t {{1, 2}, {3, 4}, {5, 6}};
	REQUIRE(io(10, 100) == 1290);
//	(1*10 + 2*100) + (3*10 + 4*100) + (5*10 + 6*100)

}
/**/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/process/matrix.hpp: processor matrix")
{
	using namespace _v3::views;

	using group_t = typename collate_t<2, 3>::template group_t<int>;
	using remix_t = process::matrix_t<group_t, mix_t>;
	using mixer_t = processor::monomer_t<remix_t, collect<-1>>;

	auto _1 = processor::lift_f(1);
	auto _n = processor::lift_f(iota(0, 10));
//
	auto io = mixer_t::bond_f(_1, _n);
	io << group_t {{1, 2}, {3, 4}, {5, 6}};
	io << control::resize_t<>(3);
	io >> control::sequel_t<>(3);

	REQUIRE(_v3::ranges::equal(io, _std::vector { 9, 21, 33}));
//	(1*1 + 2*0) + (3*1 + 4*0) + (5*1 + 6*0)
//	(1*1 + 2*1) + (3*1 + 4*1) + (5*1 + 6*1)
//	(1*1 + 2*2) + (3*1 + 4*2) + (5*1 + 6*2)

}
/**/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/process/matrix.hpp: processor shard matrix")
{
	using namespace _v3::views;

	using group_t = typename collate_t<2, 3>::template group_t<int>;
	using remix_t = process::matrix_t<group_t, mix_t>;
	using mixer_t = processor::monomer_t<remix_t, collect<-1>>;

	auto _1 = processor::lift_f(1);
	auto _n = processor::lift_f(iota(0, 10));
//
	auto io = mixer_t::bond_f(_1, _n);
	io << context::shard_s<group_t>({{1, 2}, {3, 4}, {5, 6}});
	io << control::resize_t<>(3);
	io >> control::sequel_t<>(3);

	REQUIRE(_v3::ranges::equal(io, _std::vector { 9, 21, 33}));

}
/**/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/process/matrix.hpp: processor shard column")
{
	using namespace _v3::views;

	using group_t = typename collate_t<2, 3>::template group_t<int>;
	using remix_t = process::matrix_t<group_t, mix_t>;
	using mixer_t = processor::monomer_t<remix_t, collect<-1>>;

	auto _1 = processor::lift_f(1);
	auto _n = processor::lift_f(iota(0, 10));
//
	auto io = mixer_t::bond_f(_1, _n);
	io << context::shard_s<group_t, 0>({1, 2});
	io << context::shard_s<group_t, 1>({3, 4});
	io << context::shard_s<group_t, 2>({5, 6});
	io << control::resize_t<>(3);
	io >> control::sequel_t<>(3);

	REQUIRE(_v3::ranges::equal(io, _std::vector { 9, 21, 33}));

}
/**/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/process/matrix.hpp: processor shard cell")
{
	using namespace _v3::views;

	using group_t = typename collate_t<2, 3>::template group_t<int>;
	using remix_t = process::matrix_t<group_t, mix_t>;
	using mixer_t = processor::monomer_t<remix_t, collect<-1>>;

	auto _1 = processor::lift_f(1);
	auto _n = processor::lift_f(iota(0, 10));
//
	auto io = mixer_t::bond_f(_1, _n);
	io << context::shard_s<group_t, 0, 0>(1);
	io << context::shard_s<group_t, 0, 1>(2);
	io << context::shard_s<group_t, 1, 0>(3);
	io << context::shard_s<group_t, 1, 1>(4);
	io << context::shard_s<group_t, 2, 0>(5);
	io << context::shard_s<group_t, 2, 1>(6);
	io << control::resize_t<>(3);
	io >> control::sequel_t<>(3);

	REQUIRE(_v3::ranges::equal(io, _std::vector { 9, 21, 33}));

}
/**/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
