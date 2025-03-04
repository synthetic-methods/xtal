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
template <class T, template <class ...> class ...Ks_> concept       tag_as_q = bond::       tag_as_q<T, Ks_...>;
template <class T, template <class ...> class ...Ks_> concept tag_affixed_q = bond:: tag_affixed_q<T, Ks_...>;
template <class T, template <class ...> class ...Ks_> concept       tag_in_q = bond::       tag_in_q<T, Ks_...>;
template <class T, template <class ...> class ...Ks_> concept tag_infixed_q = bond:: tag_infixed_q<T, Ks_...>;

template <template <class ...> class K_, class ...Ts> concept       tag_as_p = bond::       tag_as_p<K_, Ts...>;
template <template <class ...> class K_, class ...Ts> concept tag_affixed_p = bond:: tag_affixed_p<K_, Ts...>;
template <template <class ...> class K_, class ...Ts> concept       tag_in_p = bond::       tag_in_p<K_, Ts...>;
template <template <class ...> class K_, class ...Ts> concept tag_infixed_p = bond:: tag_infixed_p<K_, Ts...>;


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
