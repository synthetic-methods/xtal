#pragma once
#include "./any.hpp"
#include "./ordinal.hpp"





XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Tracks the state of e.g. a `context::instance`, \
observing the same semantics as the values exchanged by `*flux`, \
with `{begin,on}`, `{end,off}`, and `{kill,cut}` respectively corresponding to `0`, `1`, and `-1`. \

template <typename ...As>
using stasis = label<XTAL_FLX, As..., struct T_stasis>;

template <typename ...As>
using stasis_t = typename stasis<As...>::type;

template <typename ...As>
XTAL_CN2 stasis_f(XTAL_DEF... oo) {return stasis_t<As...>(XTAL_REF_(oo)...);}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
