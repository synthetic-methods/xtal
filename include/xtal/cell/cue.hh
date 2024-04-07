#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Wrapper used to schedule an existing type.\

///\see e.g. [../occur/any#hold] or [../occur/any#intermit]`. \

template <         class ...Ts> XTAL_NEW cue;
template <         class ...Ts> XTAL_ASK cue_q = bond::tag_p<cue, Ts...>;
template <class Y, class ...Ts> XTAL_ASK cue_p = cue_q<Ts...> and made_p<Y, Ts...>;

template <class U> struct cue<U> : conferred<U, bond::tag<cue>> {};
template <       > struct cue< > : cue<size_s> {};

template <class S=void, typename ...As>
using cue_s = bond::compose_s<complete_t<S, confined_t<>>, cue<As...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
