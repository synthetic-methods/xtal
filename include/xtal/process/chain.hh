#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP chain;
template <typename ..._s> XTAL_USE chain_t = confined_t<chain<_s...>>;
template <typename ..._s> XTAL_ASK chain_q = bond::head_tag_p<chain, _s...>;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <typename     ...As> struct chain_link    : bond::compose<chain_link<As>...> {};
template <   incomplete_q A > struct chain_link<A> : bond::compose<                 > {};
template <bond::compose_q A > struct chain_link<A> :             defer<confined_t<A>> {};
template <class           U > struct chain_link<U> :             defer<           U > {};


}///////////////////////////////////////////////////////////////////////////////

template <typename     ...As> struct chain    : bond::compose<_detail::chain_link<As...>, bond::tag<chain>> {};
template <bond::compose_q A > struct chain<A> : bond::compose<                    A     , bond::tag<chain>> {};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
