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
template <class ..._s>	concept cue_q = bond::tag_outer_p<cue_s, _s...>;
template <           >	struct  cue<> : cell::header<signed, bond::tag<cue_s>> {};


////////////////////////////////////////////////////////////////////////////////

XTAL_VAL_(let) cue_f = [] (auto &&...oo)
XTAL_0FN {
	XTAL_IF0
	XTAL_0IF (1 == sizeof...(oo)) {return       cue_s<> (XTAL_REF_(oo)...);}
	XTAL_0IF (2 == sizeof...(oo)) {return cue_s<cue_s<>>(XTAL_REF_(oo)...);}
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
