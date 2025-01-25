#pragma once
#include "./any.hh"
#include "./tab.hh"
//nclude "./tag.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename ...Outers> concept   compose_q = (...and _detail::   compose_q<Outers>);

///\
Defines `typename compose<Outers...>::template subtype<S, Inners...>`, applying:

///-	`Inners::template subtype<S>` from left-to-right.
///-	`Outers::template subtype<S>` from right-to-left.

template <typename ...Outers>
using compose = _detail::excompose<Outers...>;

///\
Composes the `Subtypes`s right-to-left. \

template <template <class, class...> class ...Subtypes>
using compose_t = _detail::excompose_t<Subtypes...>;

///\
Applies the `Inners::subtype`s to `S` from left-to-right. \

template <class S, typename ...Inners>
using compose_s = _detail::excompose_s<S, Inners...>;


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
