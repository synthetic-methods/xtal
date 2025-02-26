#pragma once
#include "./any.hh"

#include "./tab.hh"




XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class T, template <class ...> class ...Ks_> concept       tagged_q      = bond::       tagged_q     <T, Ks_...>;
template <class T, template <class ...> class ...Ks_> concept fixed_tagged_q      = bond:: fixed_tagged_q     <T, Ks_...>;
template <class T, template <class ...> class ...Ks_> concept       tagged_with_q = bond::       tagged_with_q<T, Ks_...>;
template <class T, template <class ...> class ...Ks_> concept fixed_tagged_with_q = bond:: fixed_tagged_with_q<T, Ks_...>;

template <template <class ...> class K_, class ...Ts> concept       tagged_p      = bond::       tagged_p     <K_, Ts...>;
template <template <class ...> class K_, class ...Ts> concept fixed_tagged_p      = bond:: fixed_tagged_p     <K_, Ts...>;
template <template <class ...> class K_, class ...Ts> concept       tagged_with_p = bond::       tagged_with_p<K_, Ts...>;
template <template <class ...> class K_, class ...Ts> concept fixed_tagged_with_p = bond:: fixed_tagged_with_p<K_, Ts...>;


//////////////////////////////////////////////////////////////////////////////////
///\
A `tag`ged variant of `tab`. \

template <template <class ...> class ..._s>
struct tag
:	tab<bond::tag<_s...>>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
