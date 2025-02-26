#pragma once
#include "./any.hh"

#include "../cell/header.hh"




XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Insulated header for a `flow::let_t<_s...>` `tail`. \
Opaque w.r.t. operations/comparators making it suitable candidate for labelling/ordering. \

///\
Used for scheduling any type by prefixing with an integral delay. \
May be stacked in order to described integral fades. \

template <class ..._s>	struct  cue;
template <class ..._s>	using   cue_s = bond::compose_s<let_t< _s...>, cue<>>;
template <class ..._s>	concept cue_q = bond::tagged_p<cue_s, _s...>;
template <           >	struct  cue<> : cell::header<signed, bond::tag<cue_s>> {};


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) cue_f = [] XTAL_1FN_(call) (cue_s<>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
