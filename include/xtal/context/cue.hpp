#pragma once
#include "./anybody.hpp"






XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Wrapper used to schedule an existing type.\

///\see e.g. [../control/anybody#hold] or [../control/anybody#intermit]`. \

template <typename ..._s> XTAL_NYM cue;
template <class       U > XTAL_NYM cue<U>: conferred<U, tag<cue>> {};
template <class    ...Ts> XTAL_ASK cue_q = tag_p<cue, Ts...>;

template <class S=confined_t<>, class U=size_s>
using cue_s = compose_s<S, cue<U>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)