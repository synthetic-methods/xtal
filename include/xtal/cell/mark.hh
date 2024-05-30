#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Controls access to an `address`d `attach`ment.\

///\see e.g. [../occur/any#attach] or [../occur/any#dispatch]. \

template <         class ..._s> struct  mark;
template <         class ..._s> concept mark_q = bond::head_tag_p<mark, _s...>;
template <class Y, class ..._s> concept mark_p = mark_q<_s...> and fungible_q<Y, _s...>;

template <class U> struct mark<U> : conferred<U, bond::tag<mark>> {};
template <       > struct mark< > : mark<size_t> {};

template <class S=void, typename ..._s>
using mark_s = bond::compose_s<complete_t<S, confined_t<>>, mark<_s...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
