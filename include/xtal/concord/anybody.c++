#pragma once
#include "./any.c++"
#include "./anybody.hpp"// testing...





XTAL_ENV_(push)
namespace xtal::concord::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
using bar_baz = composed<void
,	confined<void
	,	infer<struct bar, int>
	,	infer<struct baz, int>
	>
,	any<As...>
>;
template <typename ...As>
using bar_baz_t = typename bar_baz<As...>::type;


////////////////////////////////////////////////////////////////////////////////

TAG_("concord", "matching")
{
	TRY_("any")
	{
		TRUE_(any_p<any_t<struct foo, struct goo>, struct foo, struct goo>);
		TRUE_(any_p<any_t<struct foo, struct goo>,             struct goo>);
		TRUE_(any_p<any_t<struct foo, struct goo>                        >);

	}
	TRY_("any root")
	{
		TRUE_(any_q<bar_baz_t<>>);
		TRUE_(any_q<bar_baz_t<struct foo>>);

		TRUE_(any_p<bar_baz_t<struct foo            >                        >);
		TRUE_(any_p<bar_baz_t<struct foo            >, struct foo            >);
		TRUE_(any_p<bar_baz_t<struct foo, struct goo>,             struct goo>);
		TRUE_(any_p<bar_baz_t<struct foo, struct goo>, struct foo, struct goo>);

		UNTRUE_(any_p<bar_baz_t<struct foo            >,             struct goo>);
		UNTRUE_(any_p<bar_baz_t<struct foo, struct goo>, struct foo            >);

	}
	TRY_("any inline")
	{
		TRUE_(any_p<bar_baz_t<>                        >);
		TRUE_(any_p<bar_baz_t<>,             struct baz>);
		TRUE_(any_p<bar_baz_t<>, struct bar, struct baz>);

	}
	TRY_("any combined")
	{
		TRUE_(any_p<bar_baz_t<struct foo>                                    >);
		TRUE_(any_p<bar_baz_t<struct foo>,                         struct foo>);
		TRUE_(any_p<bar_baz_t<struct foo>,             struct baz, struct foo>);
		TRUE_(any_p<bar_baz_t<struct foo>, struct bar, struct baz, struct foo>);

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("concord", "traversal")
{
	using qux = confined<void
	,	infer<struct foo, int>
	,	infer<struct bar, int>
	,	infer<struct baz, int>
	>;
	using qux_t = typename qux::type;
	
	TRY_("partial access")
	{
		qux_t qux_o(0, 1, 2);

		TRUE_(0 == qux_o.template head<0>());
		TRUE_(1 == qux_o.template head<1>());
		TRUE_(2 == qux_o.template head<2>());
	//	TRUE_(3 == qux_o.template head<3>());// Fails!

		TRUE_(0 == qux_o.template head<struct foo>());
		TRUE_(1 == qux_o.template head<struct bar>());
		TRUE_(2 == qux_o.template head<struct baz>());

		TRUE_(2 == qux_o.template head<struct bar, struct baz>());
	//	TRUE_(1 != qux_o.template head<struct baz, struct bar>());// Fails!
		
	//	TRUE_(    any_p<qux_t, sequent_t<1>>);
		TRUE_(    any_p<qux_t, struct bar, struct baz>);
		TRUE_(not any_p<qux_t, struct baz, struct bar>);
	//	UNTRUE_(requires {qux_o.template head<struct baz, struct bar>();});// Shouldn't fail?

	}
	/**/
	TRY_("partial reconstruction")
	{
		auto qux_o = qux_t(1, 2, 3);

		(void) qux_o.self(11);
		TRUE_(_std::get<0>(qux_o) == 11);
		TRUE_(_std::get<1>(qux_o) ==  2);
		TRUE_(_std::get<2>(qux_o) ==  3);

		(void) qux_o.self(111, 222);
		TRUE_(_std::get<0>(qux_o) == 111);
		TRUE_(_std::get<1>(qux_o) == 222);
		TRUE_(_std::get<2>(qux_o) ==   3);

		(void) qux_o.template self<1>(2222, 3333);
		TRUE_(_std::get<0>(qux_o) ==  111);//!
		TRUE_(_std::get<1>(qux_o) == 2222);
		TRUE_(_std::get<2>(qux_o) == 3333);

		(void) qux_o.template self<struct baz>(33333);
		TRUE_(_std::get<0>(qux_o) ==   111);
		TRUE_(_std::get<1>(qux_o) ==  2222);
		TRUE_(_std::get<2>(qux_o) == 33333);

	}
	/***/
}


////////////////////////////////////////////////////////////////////////////////

TAG_("concord", "conversion")
{
	TRY_("tuple")
	{
		using namespace compound;

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
