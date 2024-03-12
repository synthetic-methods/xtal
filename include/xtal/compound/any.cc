#pragma once
#include "../any.cc"
#include "./any.ii"// testing...





XTAL_ENV_(push)
namespace xtal::compound::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__test;


////////////////////////////////////////////////////////////////////////////////

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


TAG_("compound", "matching")
{
	TRY_("any")
	{
		TRUE_(any_p<any_t<struct foo, struct goo>, struct foo, struct goo>);
		TRUE_(any_p<any_t<struct foo, struct goo>,             struct goo>);
	//	TRUE_(any_p<any_t<struct foo, struct goo>, struct foo            >);
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

TAG_("compound", "traversal")
{
	using qux = confined<void
	,	infer<struct foo, int>
	,	infer<struct bar, int>
	,	infer<struct baz, int>
	>;
	using U_qux = typename qux::type;
	
	TRY_("partial access")
	{
		U_qux u_qux(0, 1, 2);

		TRUE_(0 == u_qux.template head<0>());
		TRUE_(1 == u_qux.template head<1>());
		TRUE_(2 == u_qux.template head<2>());
	//	TRUE_(3 == u_qux.template head<3>());// Fails!

		TRUE_(0 == u_qux.template head<struct foo>());
		TRUE_(1 == u_qux.template head<struct bar>());
		TRUE_(2 == u_qux.template head<struct baz>());

		TRUE_(2 == u_qux.template head<struct bar, struct baz>());
	//	TRUE_(1 != u_qux.template head<struct baz, struct bar>());// Fails!
		
	//	TRUE_(    any_p<U_qux, cardinal_t<1>>);
		TRUE_(    any_p<U_qux, struct bar, struct baz>);
		TRUE_(not any_p<U_qux, struct baz, struct bar>);
	//	UNTRUE_(requires {u_qux.template head<struct baz, struct bar>();});// Shouldn't fail?

	}
	/**/
	TRY_("partial reconstruction")
	{
		auto u_qux = U_qux(1, 2, 3);

		(void) u_qux.self(11);
		TRUE_(_std::get<0>(u_qux) == 11);
		TRUE_(_std::get<1>(u_qux) ==  2);
		TRUE_(_std::get<2>(u_qux) ==  3);

		(void) u_qux.self(111, 222);
		TRUE_(_std::get<0>(u_qux) == 111);
		TRUE_(_std::get<1>(u_qux) == 222);
		TRUE_(_std::get<2>(u_qux) ==   3);

		(void) u_qux.template self<1>(2222, 3333);
		TRUE_(_std::get<0>(u_qux) ==  111);//!
		TRUE_(_std::get<1>(u_qux) == 2222);
		TRUE_(_std::get<2>(u_qux) == 3333);

		(void) u_qux.template self<struct baz>(33333);
		TRUE_(_std::get<0>(u_qux) ==   111);
		TRUE_(_std::get<1>(u_qux) ==  2222);
		TRUE_(_std::get<2>(u_qux) == 33333);

	}
	/***/
}


////////////////////////////////////////////////////////////////////////////////

TAG_("compound", "conversion")
{
	TRY_("tuple")
	{
		using namespace atom;

		using U_foo = confined_t<defer<bool>, defer<int>, defer<float>>;
		auto const foo = U_foo(1, 2, 3);
		auto const bar = foo.apple();
		using U_bar = XTAL_TYP_(bar);

		static_assert(_std::same_as<U_bar, _std::tuple<bool, int, float>>);

		auto baz = (U_bar) foo;
		TRUE_(_std::get<0>(baz) == _std::get<0>(bar));
		TRUE_(_std::get<1>(baz) == _std::get<1>(bar));
		TRUE_(_std::get<2>(baz) == _std::get<2>(bar));

	//	TRUE_(6 == _std::apply([] (XTAL_DEF ...oo) XTAL_0FN_(XTAL_REF_(oo) +...+ 0), foo));// nope...
		TRUE_(6 ==   foo.apply([] (XTAL_DEF ...oo) XTAL_0FN_(XTAL_REF_(oo) +...+ 0)));
		TRUE_(3 == _std::tuple_size_v<U_foo>);
		TRUE_(3 == _std::tuple_size_v<U_bar>);

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

		TRUE_(is_q<_std::tuple_element_t<0, U_foo>,  bool>);
		TRUE_(is_q<_std::tuple_element_t<1, U_foo>,   int>);
		TRUE_(is_q<_std::tuple_element_t<2, U_foo>, float>);
		TRUE_(is_q<_std::tuple_element_t<0, U_foo>, _std::tuple_element_t<0, U_bar>>);
		TRUE_(is_q<_std::tuple_element_t<1, U_foo>, _std::tuple_element_t<1, U_bar>>);
		TRUE_(is_q<_std::tuple_element_t<2, U_foo>, _std::tuple_element_t<2, U_bar>>);

	}
}


////////////////////////////////////////////////////////////////////////////////

TAG_("compound", "composition")
{
	class L_aim;
	class L_hyp;
	class L_etc;

	using T_aim = inferred_t<L_aim[4]>;
	using T_hyp = inferred_t<L_hyp[2]>;
	using T_opt = inferred_t<L_aim[4], L_hyp[2]>;
	
	TRY_("task")
	{
		auto t_opt = T_opt(0b1'10u);
		TRUE_(0b10 == t_opt.template head<L_aim>());
		TRUE_(0b1  == t_opt.template head<L_hyp>());
		TRUE_(sizeof(T_opt) == sizeof(T_aim));
		TRUE_(sizeof(T_opt) == sizeof(T_hyp));
	//	TRUE_(any_p<T_opt, L_aim>);
		TRUE_(any_p<T_opt, L_hyp>);
		TRUE_(complete_q<T_opt::self_t<L_aim>>);
		TRUE_(complete_q<T_opt::self_t<L_hyp>>);
		UNTRUE_(complete_q<T_opt::self_t<L_etc>>);
		TRUE_(8 == T_opt::enumerate());
		TRUE_(4 == T_aim::enumerate());
		TRUE_(2 == T_hyp::enumerate());

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)