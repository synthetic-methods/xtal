#pragma once
#include "./any.hh"

#include "../cell/header.hh"




XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Insulated header for a `flow::let_t<_s...>` `tail()`.

\details
Creates an inherited wrapper for `flow::any_q` based on `cell::header`.

Used for scheduling any type by prefixing with an integral delay.
May be stacked in order to described gradients.
*/
template <class ..._s>	struct  cue;
template <class ..._s>	using   cue_s = bond::compose_s<let_t< _s...>, cue<>>;
template <class ..._s>	concept cue_q = bond::tag_as_p<cue_s, _s...>;
template <           >	struct  cue<> : cell::header<signed, bond::tag<cue_s>> {};


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) cue_f = [] XTAL_1FN_(call) (cue_s<>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
