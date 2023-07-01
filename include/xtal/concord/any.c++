#pragma once
#include "../any.c++"
#include "./any.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::concord::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__test;


////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/concord/any.hpp: tuple mania")
{
	using namespace common;

	using foo_t = confined_t<defer<bool>, defer<int>, defer<float>>;
	auto const foo = foo_t(1, 2, 3);
	auto const bar = foo.tuple();
	using bar_t = XTAL_TYP_(bar);

	bar_t baz = foo;
	REQUIRE(_std::get<0>(baz) == _std::get<0>(bar));
	REQUIRE(_std::get<1>(baz) == _std::get<1>(bar));
	REQUIRE(_std::get<2>(baz) == _std::get<2>(bar));

//	REQUIRE(6 == _std::apply([](XTAL_DEF ...oo) XTAL_0FN_(XTAL_REF_(oo) +...+ 0), foo));// nope...
	REQUIRE(6 ==   foo.apply([](XTAL_DEF ...oo) XTAL_0FN_(XTAL_REF_(oo) +...+ 0)));
	REQUIRE(3 == _std::tuple_size_v<foo_t>);
	REQUIRE(3 == _std::tuple_size_v<bar_t>);

	auto [_1, _2, _3] = foo;
	REQUIRE(_1 == 1);
	REQUIRE(_2 == 2);
	REQUIRE(_3 == 3);
	REQUIRE(_std::get<0>(foo) == 1);
	REQUIRE(_std::get<1>(foo) == 2);
	REQUIRE(_std::get<2>(foo) == 3);
	REQUIRE(_std::get<0>(foo) == _std::get<0>(bar));
	REQUIRE(_std::get<1>(foo) == _std::get<1>(bar));
	REQUIRE(_std::get<2>(foo) == _std::get<2>(bar));

	REQUIRE(is_q<_std::tuple_element_t<0, foo_t>,  bool>);
	REQUIRE(is_q<_std::tuple_element_t<1, foo_t>,   int>);
	REQUIRE(is_q<_std::tuple_element_t<2, foo_t>, float>);
	REQUIRE(is_q<_std::tuple_element_t<0, foo_t>, _std::tuple_element_t<0, bar_t>>);
	REQUIRE(is_q<_std::tuple_element_t<1, foo_t>, _std::tuple_element_t<1, bar_t>>);
	REQUIRE(is_q<_std::tuple_element_t<2, foo_t>, _std::tuple_element_t<2, bar_t>>);

}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
