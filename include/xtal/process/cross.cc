#pragma once
#include "./any.cc"
#include "./cross.ii"// testing...

#include "../context/shard.ii"
#include "../processor/monomer.ii"


XTAL_ENV_(push)
namespace xtal::process::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("cross", "process")
{
	TRY_("shape with matrix")
	{
		using namespace _v3::views;

		using model_u = compound::solid::point_t<int[2][3]>;
		using remix_u = process::cross_t<model_u, mix_t>;
		using mixer_u = processor::monomer_t<remix_u, processor::restore<>>;

		auto io = remix_u();
		io <<= model_u {{1, 2}, {3, 4}, {5, 6}};
		TRUE_(io(10, 100) == 1290);
	//	(1*10 + 2*100) + (3*10 + 4*100) + (5*10 + 6*100)

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("cross", "processor")
{
	TRY_("shape with matrix")
	{
		using namespace _v3::views;

		using model_u = compound::solid::point_t<int[2][3]>;
		using remix_u = process::cross_t<model_u, mix_t>;
		using mixer_u = processor::monomer_t<remix_u, processor::restore<>>;

		auto _1 = processor::let_f(1);
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = mixer_u::bond_f(_1, _n);
		io <<= model_u {{1, 2}, {3, 4}, {5, 6}};
		io <<= message::resize_t<>(3);
		io >>= message::sequel_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));
	//	(1*1 + 2*0) + (3*1 + 4*0) + (5*1 + 6*0)
	//	(1*1 + 2*1) + (3*1 + 4*1) + (5*1 + 6*1)
	//	(1*1 + 2*2) + (3*1 + 4*2) + (5*1 + 6*2)

	}
	TRY_("shape with matrix shard")
	{
		using namespace _v3::views;

		using model_u = compound::solid::point_t<int[2][3]>;
		using remix_u = process::cross_t<model_u, mix_t>;
		using mixer_u = processor::monomer_t<remix_u, processor::restore<>>;

		auto _1 = processor::let_f(1);
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = mixer_u::bond_f(_1, _n);
		io <<= context::shard_s<model_u>({{1, 2}, {3, 4}, {5, 6}});
		io <<= message::resize_t<>(3);
		io >>= message::sequel_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));

	}
	TRY_("shape with column shard")
	{
		using namespace _v3::views;

		using model_u = compound::solid::point_t<int[2][3]>;
		using remix_u = process::cross_t<model_u, mix_t>;
		using mixer_u = processor::monomer_t<remix_u, processor::restore<>>;

		auto _1 = processor::let_f(1);
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = mixer_u::bond_f(_1, _n);
		io <<= context::shard_s<model_u, 0>({1, 2});
		io <<= context::shard_s<model_u, 1>({3, 4});
		io <<= context::shard_s<model_u, 2>({5, 6});
		io <<= message::resize_t<>(3);
		io >>= message::sequel_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));

	}
	TRY_("shape with cell shard")
	{
		using namespace _v3::views;

		using model_u = compound::solid::point_t<int[2][3]>;
		using remix_u = process::cross_t<model_u, mix_t>;
		using mixer_u = processor::monomer_t<remix_u, processor::restore<>>;

		auto _1 = processor::let_f(1);
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = mixer_u::bond_f(_1, _n);
		io <<= context::shard_s<model_u, 0, 0>(1);
		io <<= context::shard_s<model_u, 0, 1>(2);
		io <<= context::shard_s<model_u, 1, 0>(3);
		io <<= context::shard_s<model_u, 1, 1>(4);
		io <<= context::shard_s<model_u, 2, 0>(5);
		io <<= context::shard_s<model_u, 2, 1>(6);
		io <<= message::resize_t<>(3);
		io >>= message::sequel_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));

	}
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
