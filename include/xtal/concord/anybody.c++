#pragma once
#include "./any.c++"
#include "./anybody.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::concord::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("concord", "traversal")
{
	TRY_("path access")
	{
		using qux = confined<void
		,	any<struct foo>, defer<int>
		,	any<struct bar>, defer<int>
		,	any<struct baz>, defer<int>
		>;
		using qux_t = typename qux::type;
		qux_t qux_o(0, 1, 2);

		TRUE_(0 == qux_o.template head<0>());
		TRUE_(1 == qux_o.template head<1>());
		TRUE_(2 == qux_o.template head<2>());

		TRUE_(0 == qux_o.template get<struct foo>());
		TRUE_(1 == qux_o.template get<struct bar>());
		TRUE_(2 == qux_o.template get<struct baz>());

		TRUE_(1 == qux_o.template get<struct foo, struct bar>());
		TRUE_(2 == qux_o.template get<struct foo, struct baz>());
		TRUE_(2 == qux_o.template get<struct bar, struct baz>());

	}
	TRY_("path mutation")
	{
		using foo_t = confined_t<defer<bool>, defer<int>, defer<float>>;
		auto foo = foo_t(1, 2, 3);

		(void) foo.self(0);
		TRUE_(_std::get<0>(foo) == 0);
		TRUE_(_std::get<1>(foo) == 2);
		TRUE_(_std::get<2>(foo) == 3);

		(void) foo.self(1, 3);
		TRUE_(_std::get<0>(foo) == 1);
		TRUE_(_std::get<1>(foo) == 3);
		TRUE_(_std::get<2>(foo) == 3);

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("concord", "conversion")
{
	TRY_("tuple")
	{
		using namespace common;

		using foo_t = confined_t<defer<bool>, defer<int>, defer<float>>;
		auto const foo = foo_t(1, 2, 3);
		auto const bar = foo.tuple();
		using bar_t = XTAL_TYP_(bar);

		auto baz = (bar_t) foo;
		TRUE_(_std::get<0>(baz) == _std::get<0>(bar));
		TRUE_(_std::get<1>(baz) == _std::get<1>(bar));
		TRUE_(_std::get<2>(baz) == _std::get<2>(bar));

	//	TRUE_(6 == _std::apply([] (XTAL_DEF ...oo) XTAL_0FN_(XTAL_REF_(oo) +...+ 0), foo));// nope...
		TRUE_(6 ==   foo.apply([] (XTAL_DEF ...oo) XTAL_0FN_(XTAL_REF_(oo) +...+ 0)));
		TRUE_(3 == _std::tuple_size_v<foo_t>);
		TRUE_(3 == _std::tuple_size_v<bar_t>);

		auto [_1, _2, _3] = foo;
		TRUE_(_1 == 1);
		TRUE_(_2 == 2);
		TRUE_(_3 == 3);
		TRUE_(_std::get<0>(foo) == 1);
		TRUE_(_std::get<1>(foo) == 2);
		TRUE_(_std::get<2>(foo) == 3);
		TRUE_(_std::get<0>(foo) == _std::get<0>(bar));
		TRUE_(_std::get<1>(foo) == _std::get<1>(bar));
		TRUE_(_std::get<2>(foo) == _std::get<2>(bar));

		TRUE_(is_q<_std::tuple_element_t<0, foo_t>,  bool>);
		TRUE_(is_q<_std::tuple_element_t<1, foo_t>,   int>);
		TRUE_(is_q<_std::tuple_element_t<2, foo_t>, float>);
		TRUE_(is_q<_std::tuple_element_t<0, foo_t>, _std::tuple_element_t<0, bar_t>>);
		TRUE_(is_q<_std::tuple_element_t<1, foo_t>, _std::tuple_element_t<1, bar_t>>);
		TRUE_(is_q<_std::tuple_element_t<2, foo_t>, _std::tuple_element_t<2, bar_t>>);

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
