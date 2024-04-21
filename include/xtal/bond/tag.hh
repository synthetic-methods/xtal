#pragma once
#include "./any.hh"
#include "./tab.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <class ...> class Y             > struct  tag        : tab<tag<Y>> {};

template <class T, template <class ...> class ...Ys> struct  tag_rest   :          tab_rest<T, tag<Ys>...>     {};
template <class T, template <class ...> class ...Ys> using   tag_rest_t = typename tab_rest<T, tag<Ys>...>:: type;
template <class T, template <class ...> class ...Ys> concept tag_rest_q =          tab_rest<T, tag<Ys>...>::value;

template <class T, template <class ...> class ...Ys> concept tag_q      = _std::conjunction_v<tag_rest<based_t<T >, Ys>...>;
template <template <class ...> class Y, class ...Ts> concept tag_p      = _std::conjunction_v<tag_rest<based_t<Ts>, Y >...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
