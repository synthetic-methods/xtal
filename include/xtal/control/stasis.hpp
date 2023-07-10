#pragma once
#include "./any.hpp"
#include "./flux.hpp"





XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Tracks the stage/state e.g. of `context::grain`. \
Represents the dual of, and observes the same value-semantics as `flux`, \
with `{initialize,on}`, `{finalize,off}`, and `{terminate,cut}` respectively corresponding to `0`, `1`, and `-1`. \

template <typename ...As>
struct stasis;

template <typename ...As>
using stasis_t = confined_t<flux<As..., tag<stasis>>>;

template <typename ...As>
XTAL_CN2 stasis_f(XTAL_DEF... oo) {return stasis_t<As...>(XTAL_REF_(oo)...);}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
