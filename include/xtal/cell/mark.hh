#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Controls access to an `address`d `attach`ment.\

///\see e.g. [../occur/any#attach] or [../occur/any#dispatch]. \

template <         class ...Ts> XTAL_NEW mark;
template <         class ...Ts> XTAL_ASK mark_q = bond::tag_p<mark, Ts...>;
template <class Y, class ...Ts> XTAL_ASK mark_p = mark_q<Ts...> and made_p<Y, Ts...>;

template <class U> struct mark<U> : conferred<U, bond::tag<mark>> {};
template <       > struct mark< > : mark<size_t> {};

template <class S=void, typename ...As>
using mark_s = bond::compose_s<complete_t<S, confined_t<>>, mark<As...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
