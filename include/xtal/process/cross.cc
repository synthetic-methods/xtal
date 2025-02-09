#pragma once
#include "./any.cc"
#include "./cross.hh"// testing...

#include "../atom/all.hh"
#include "../flow/indent.hh"
#include "../processor/monomer.hh"

XTAL_ENV_(push)
namespace xtal::process::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("cross", "process")
{
	TRY_("shape with matrix")
	{
		using namespace _xtd::ranges::views;

		using U_model = atom::quanta_t<int[3][2]>;
		using U_remix = process::cross_t<U_model, Px_mix>;

		auto io = U_remix();
		io <<= U_model {{1, 2}, {3, 4}, {5, 6}};
		TRUE_(io(10, 100) == 1290);
	//	(1*10 + 2*100) + (3*10 + 4*100) + (5*10 + 6*100)

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("cross", "processor")
{
	/**/
	TRY_("shape with matrix")
	{
		using namespace _xtd::ranges::views;

		using U_model = atom::quanta_t<int[3][2]>;// 3-outputs, 2-inputs
		using U_remix = process::cross_t<U_model, Px_mix>;
		using U_mixer = processor::monomer_t<U_remix, provision::stored<>>;

		//\
		auto _1 = processor::let_f(1);
		auto _1 = processor::let_f(_xtd::ranges::views::repeat(1));
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = U_mixer::bind_f(_1, _n);
		io <<= U_model {{1, 2}, {3, 4}, {5, 6}};
		io <<= occur::resize_t<>(3);
		io >>= occur::cursor_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));
	//	(1*1 + 2*0) + (3*1 + 4*0) + (5*1 + 6*0)
	//	(1*1 + 2*1) + (3*1 + 4*1) + (5*1 + 6*1)
	//	(1*1 + 2*2) + (3*1 + 4*2) + (5*1 + 6*2)

	//	{{1,2}, {3,4}, {5,6}}.{1,0} // Total
	//	{{1,2}, {3,4}, {5,6}}.{1,1} // Total
	//	{{1,2}, {3,4}, {5,6}}.{1,2} // Total

	}
	/***/
	/**/
	TRY_("shape with matrix indent")
	{
		using namespace _xtd::ranges::views;

		using U_model = atom::quanta_t<int[3][2]>;
		using U_remix = process::cross_t<U_model, Px_mix>;
		using U_mixer = processor::monomer_t<U_remix, provision::stored<>>;

		auto _1 = processor::let_f(1);
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = U_mixer::bind_f(_1, _n);
		io <<=  flow::indent_s<U_model>{{1, 2}, {3, 4}, {5, 6}};
		io <<= occur::resize_t<>(3);
		io >>= occur::cursor_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));

	}
	/***/
	/**/
	TRY_("shape with column indent")
	{
		using namespace _xtd::ranges::views;

		using U_model = atom::quanta_t<int[3][2]>;
		using U_remix = process::cross_t<U_model, Px_mix>;
		using U_mixer = processor::monomer_t<U_remix, provision::stored<>>;

		auto _1 = processor::let_f(1);
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = U_mixer::bind_f(_1, _n);
		io <<=  flow::indent_s<U_model, 0>{1, 2};
		io <<=  flow::indent_s<U_model, 1>{3, 4};
		io <<=  flow::indent_s<U_model, 2>{5, 6};
		io <<= occur::resize_t<>(3);
		io >>= occur::cursor_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));

	}
	/***/
	/**/
	TRY_("shape with vector indent")
	{
		using namespace _xtd::ranges::views;

		using U_model = atom::quanta_t<int[3][2]>;
		using U_remix = process::cross_t<U_model, Px_mix>;
		using U_mixer = processor::monomer_t<U_remix, provision::stored<>>;

		auto _1 = processor::let_f(1);
		auto _n = processor::let_f(iota(0, 10));
	//
		auto io = U_mixer::bind_f(_1, _n);
		io <<=  flow::indent_s<U_model, 0, 0>{1};
		io <<=  flow::indent_s<U_model, 0, 1>{2};
		io <<=  flow::indent_s<U_model, 1, 0>{3};
		io <<=  flow::indent_s<U_model, 1, 1>{4};
		io <<=  flow::indent_s<U_model, 2, 0>{5};
		io <<=  flow::indent_s<U_model, 2, 1>{6};
		io <<= occur::resize_t<>(3);
		io >>= occur::cursor_t<>(3);

		TRUE_(equal_f(io, _std::vector { 9, 21, 33}));

	}
	/***/
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
