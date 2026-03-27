#pragma once
#include "./any.hh"

#include "./tab.hh"




XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Duplicates the `concept`s from `bond::tag`.
*/
template <class T, template <class ...> class ...Ks_> concept       tag_outer_q = bond::       tag_outer_q<T, Ks_...>;
template <class T, template <class ...> class ...Ks_> concept tag_outer_fixed_q = bond:: tag_outer_fixed_q<T, Ks_...>;
template <class T, template <class ...> class ...Ks_> concept       tag_inner_q = bond::       tag_inner_q<T, Ks_...>;
template <class T, template <class ...> class ...Ks_> concept tag_inner_fixed_q = bond:: tag_inner_fixed_q<T, Ks_...>;

template <template <class ...> class K_, class ...Ts> concept       tag_outer_p = bond::       tag_outer_p<K_, Ts...>;
template <template <class ...> class K_, class ...Ts> concept tag_outer_fixed_p = bond:: tag_outer_fixed_p<K_, Ts...>;
template <template <class ...> class K_, class ...Ts> concept       tag_inner_p = bond::       tag_inner_p<K_, Ts...>;
template <template <class ...> class K_, class ...Ts> concept tag_inner_fixed_p = bond:: tag_inner_fixed_p<K_, Ts...>;


//////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Provides conversion from `bond::tab_compatible_q` types when `fuse`d.

\details
Adaptation of `flow::tab` to `class`-based templates.
*/
template <template <class ...> class ..._s>
struct tag
:	tab<bond::tag<_s...>>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
