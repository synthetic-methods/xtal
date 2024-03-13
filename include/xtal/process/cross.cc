#pragma once
#include "./any.cc"
#include "./cross.ii"// testing...

#include "../flux/indent.ii"
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

		using U_model = atom::solid::linear_t<int[2][3]>;
		using U_remix = process::cross_t<U_model, mix_t>;
		using U_mixer = processor::monomer_t<U_remix, resource::stored<>>;

		auto io = U_remix();
		io <<= U_model {{1, 2}, {3, 4}, {5, 6}};
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

		using U_model = atom::solid::linear_t<int[2][3]>;
		using U_remix = process::cross_t<U_model, mix_t>;
		using U_mixer = processor::monomer_t<U_remix, resource::stored<>>;

		auto _1 = processor::let_f(1);
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = U_mixer::bind_f(_1, _n);
		io <<= U_model {{1, 2}, {3, 4}, {5, 6}};
		io <<= message::resize_t<>(3);
		io >>= message::scope_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));
	//	(1*1 + 2*0) + (3*1 + 4*0) + (5*1 + 6*0)
	//	(1*1 + 2*1) + (3*1 + 4*1) + (5*1 + 6*1)
	//	(1*1 + 2*2) + (3*1 + 4*2) + (5*1 + 6*2)

	}
	TRY_("shape with matrix indent")
	{
		using namespace _v3::views;

		using U_model = atom::solid::linear_t<int[2][3]>;
		using U_remix = process::cross_t<U_model, mix_t>;
		using U_mixer = processor::monomer_t<U_remix, resource::stored<>>;

		auto _1 = processor::let_f(1);
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = U_mixer::bind_f(_1, _n);
		io <<= flux::indent_s<U_model>({{1, 2}, {3, 4}, {5, 6}});
		io <<= message::resize_t<>(3);
		io >>= message::scope_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));

	}
	TRY_("shape with column indent")
	{
		using namespace _v3::views;

		using U_model = atom::solid::linear_t<int[2][3]>;
		using U_remix = process::cross_t<U_model, mix_t>;
		using U_mixer = processor::monomer_t<U_remix, resource::stored<>>;

		auto _1 = processor::let_f(1);
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = U_mixer::bind_f(_1, _n);
		io <<= flux::indent_s<U_model, 0>({1, 2});
		io <<= flux::indent_s<U_model, 1>({3, 4});
		io <<= flux::indent_s<U_model, 2>({5, 6});
		io <<= message::resize_t<>(3);
		io >>= message::scope_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));

	}
	TRY_("shape with cell indent")
	{
		using namespace _v3::views;

		using U_model = atom::solid::linear_t<int[2][3]>;
		using U_remix = process::cross_t<U_model, mix_t>;
		using U_mixer = processor::monomer_t<U_remix, resource::stored<>>;

		auto _1 = processor::let_f(1);
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = U_mixer::bind_f(_1, _n);
		io <<= flux::indent_s<U_model, 0, 0>(1);
		io <<= flux::indent_s<U_model, 0, 1>(2);
		io <<= flux::indent_s<U_model, 1, 0>(3);
		io <<= flux::indent_s<U_model, 1, 1>(4);
		io <<= flux::indent_s<U_model, 2, 0>(5);
		io <<= flux::indent_s<U_model, 2, 1>(6);
		io <<= message::resize_t<>(3);
		io >>= message::scope_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));

	}
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
