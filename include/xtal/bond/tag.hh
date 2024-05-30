#pragma once
#include "./any.hh"
#include "./tab.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <class ...> class Y             > XTAL_TYP tag        : tab<tag<Y>> {};

template <class T, template <class ...> class ...Ys> XTAL_TYP tag_tail   :          tab_tail<T, tag<Ys>...>     {};
template <class T, template <class ...> class ...Ys> XTAL_USE tag_tail_t = typename tab_tail<T, tag<Ys>...>:: type;
template <class T, template <class ...> class ...Ys> XTAL_ASK tag_tail_q =          tab_tail<T, tag<Ys>...>::value;

template <class T, template <class ...> class ...Ys> XTAL_ASK tag_head_q      = _std::conjunction_v<tag_tail<based_t<T >, Ys>...>;
template <template <class ...> class Y, class ...Ts> XTAL_ASK tag_head_p      = _std::conjunction_v<tag_tail<based_t<Ts>, Y >...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
