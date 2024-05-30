#pragma once
#include "./any.hh"
#include "./tab.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <class ...> class Y             > XTAL_TYP tag        : tab<tag<Y>> {};

template <class T, template <class ...> class ...Ys> XTAL_TYP tail_tag   :          tail_tab<T, tag<Ys>...>     {};
template <class T, template <class ...> class ...Ys> XTAL_USE tail_tag_t = typename tail_tab<T, tag<Ys>...>:: type;
template <class T, template <class ...> class ...Ys> XTAL_ASK tail_tag_q =          tail_tab<T, tag<Ys>...>::value;

template <class T, template <class ...> class ...Ys> XTAL_ASK head_tag_q      = _std::conjunction_v<tail_tag<based_t<T >, Ys>...>;
template <template <class ...> class Y, class ...Ts> XTAL_ASK head_tag_p      = _std::conjunction_v<tail_tag<based_t<Ts>, Y >...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
