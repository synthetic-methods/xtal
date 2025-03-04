#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Provides `method` composition by linking `head`s.

\details
Besides handling composition,
most of the work is done via `processor::defer`.
*/
template <typename ..._s> struct   link;
template <typename ..._s> using    link_t = confined_t<link<_s...>>;
template <typename ..._s> concept  link_q = bond::tag_in_p<link, _s...>;


////////////////////////////////////////////////////////////////////////////////

template <typename     ...As> struct link    : bond::compose<link<As>...                          > {};
template <   incomplete_q A > struct link<A> : bond::compose<                                     > {};
template <bond::compose_q A > struct link<A> : bond::compose<defer<confined_t<A>>, bond::tag<link>> {};
template <class           U > struct link<U> : bond::compose<defer<           U >, bond::tag<link>> {};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
