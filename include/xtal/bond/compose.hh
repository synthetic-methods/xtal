#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <template <class, typename...> class Subtype>
struct compost
{
	template <class S, class ...Inners>                            struct pseudokind               {using type = Subtype<S, Inners...>;};
	template <class S, class ...Inners> requires none_q<Inners...> struct pseudokind<S, Inners...> {using type = Subtype<S           >;};
	template <class S, class ...Inners>
	//\
	using subtype = Subtype<S, Inners...>;
	using subtype = typename pseudokind<S, Inners...>::type;
	//\note\
	Even when `not sizeof...(Ts)`, `clang` can't instantiate unary alias-templates with `T, Ts...`. \

};
template <class S,                   typename ...Inners> struct compose {using type = S;};
template <class S, typename   Inner, typename ...Inners> struct compose<S, Inner, Inners...> : compose<                                 S , Inners...> {};
template <class S, complete_q Inner, typename ...Inners> struct compose<S, Inner, Inners...> : compose<typename Inner::template subtype<S>, Inners...> {};

template <typename Outer> concept   compose_q =     complete_q<compost<Outer::template subtype>>;
template <typename Outer> concept decompose_q = not complete_q<compost<Outer::template subtype>>;


}///////////////////////////////////////////////////////////////////////////////

template <typename ...Outers> concept   compose_q =     (...and _detail::   compose_q<Outers>);
template <typename ...Outers> concept decompose_q = not (...and _detail:: decompose_q<Outers>);


///\
Defines `typename compose<Outers...>::template subtype<S, Inners...>`, \
where `S` provides the kernel to which: \
-	`Inners::template subtype<S>` are applied from left-to-right. \
-	`Outers::template subtype<S>` are applied from right-to-left. \

template <                 typename ...Outers> struct compose;
template <typename  Outer, typename ...Outers> struct compose<Outer, Outers...> : compose<Outers...> {};
template <compose_q Outer, typename ...Outers> struct compose<Outer, Outers...>
{
	template <class S, typename ...Inners>
	using subtype = typename Outer::template subtype<
		typename compose<Outers...>::template subtype<S, Inners...>
	>;

};
template <>
struct compose<>
{
	template <class S, typename ...Inners>
	using subtype = typename _detail::compose<S, Inners...>::type;

};
///\
Composes the `Subtypes`s right-to-left. \

template <template <class, class...> class ...Subtypes>
XTAL_USE compose_t = compose<_detail::compost<Subtypes>...>;

///\
Applies the `Inners::subtype`s to `S` from left-to-right. \

template <class S, typename ...Inners>
using compose_s = typename compose<>::template subtype<S, Inners...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
