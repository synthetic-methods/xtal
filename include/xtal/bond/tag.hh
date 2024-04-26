#pragma once
#include "./any.hh"
#include "./tab.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <class ...> class Y             > XTAL_TYP tag        : tab<tag<Y>> {};

template <class T, template <class ...> class ...Ys> XTAL_TYP tag_rest   :          tab_rest<T, tag<Ys>...>     {};
template <class T, template <class ...> class ...Ys> XTAL_USE tag_rest_t = typename tab_rest<T, tag<Ys>...>:: type;
template <class T, template <class ...> class ...Ys> XTAL_ASK tag_rest_q =          tab_rest<T, tag<Ys>...>::value;

template <class T, template <class ...> class ...Ys> XTAL_ASK tag_q      = _std::conjunction_v<tag_rest<based_t<T >, Ys>...>;
template <template <class ...> class Y, class ...Ts> XTAL_ASK tag_p      = _std::conjunction_v<tag_rest<based_t<Ts>, Y >...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
