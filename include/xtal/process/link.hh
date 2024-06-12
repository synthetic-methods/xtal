#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP link;
template <typename ..._s> XTAL_USE link_t = confined_t<link<_s...>>;
template <typename ..._s> XTAL_REQ link_q = bond::head_tag_p<link, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides (?:im)?pure mapping of `functor` and `function` by linking `head`s. \

template <typename     ...As> struct link    : bond::compose<link<As>...                          > {};
template <   incomplete_q A > struct link<A> : bond::compose<                                      > {};
template <bond::compose_q A > struct link<A> : bond::compose<defer<confined_t<A>>, bond::tag<link>> {};
template <class           U > struct link<U> : bond::compose<defer<           U >, bond::tag<link>> {};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
