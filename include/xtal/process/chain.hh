#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct  chain;
template <typename ..._s> using   chain_t = confined_t<chain<_s...>>;
template <typename ..._s> concept chain_q = bond::tag_p<chain, _s...>;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct link : bond::compose<link<As>...>
{
};
template <incomplete_q A>
struct link<A>
:	bond::compose<>
{
};
template <bond::compose_q A>
struct link<A>
:	link<confined_t<A>>
{
};
template <class A>
struct link<A>
:	defer<A>
{
};

}///////////////////////////////////////////////////////////////////////////////

template <typename     ...As> struct chain    : bond::compose<_detail::link<As...>, bond::tag<chain>> {};
template <bond::compose_q A > struct chain<A> : bond::compose<              A     , bond::tag<chain>> {};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
