#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::cell
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Wrapper used to index an existing type. \

///\see e.g. [../processor/polymer.ipp]. \

template <         class ..._s> struct  key;
template <         class ..._s> concept key_q = bond::head_tag_p<key, _s...>;
template <class Y, class ..._s> concept key_p = key_q<_s...> and fungible_q<Y, _s...>;

template <class U> struct key<U> : conferred<U, bond::tag<key>> {};
template <       > struct key< > : key<size_t> {};

template <class S=void, typename ..._s>
using key_s = bond::compose_s<complete_t<S, confined_t<>>, key<_s...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
