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

template <         class ...Ts> XTAL_NEW key;
template <         class ...Ts> XTAL_ASK key_q = bond::tag_p<key, Ts...>;
template <class Y, class ...Ts> XTAL_ASK key_p = key_q<Ts...> and made_p<Y, Ts...>;

template <class U> struct key<U> : conferred<U, bond::tag<key>> {};
template <       > struct key< > : key<size_t> {};

template <class S=void, typename ...As>
using key_s = bond::compose_s<complete_t<S, confined_t<>>, key<As...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
