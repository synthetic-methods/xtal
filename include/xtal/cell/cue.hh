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

template <         class ..._s> struct  cue;
template <         class ..._s> concept cue_q = bond::head_tag_p<cue, _s...>;
template <class Y, class ..._s> concept cue_p = cue_q<_s...> and fungible_q<Y, _s...>;

template <class U> struct cue<U> : conferred<U, bond::tag<cue>> {};
template <       > struct cue< > : cue<size_s> {};

template <class S=void, typename ..._s>
using cue_s = bond::compose_s<complete_t<S, confined_t<>>, cue<_s...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
