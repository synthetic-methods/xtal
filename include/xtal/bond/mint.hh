#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Exchanges the value-type `U` of `T` with that supplied to `subtype<S>`. \
Used to change e.g. `float -> int`, \
`std::complex<float> -> std::complex<int>` \
`std::array<float, N> -> std::array<int, N>`, etc. \

template <class T>
struct mint;


////////////////////////////////////////////////////////////////////////////////

template <class T>
struct mint
{
	template <class V> using subtype = V;

};
template <template <class> class T_, class U>
struct mint<T_<U>>
{
	template <class V> using subtype = T_<V>;

};
template <template <class, class ...> class T_, class U, class ..._s> requires (1 <= sizeof...(_s))
struct mint<T_<U, _s...>>
{
	template <class V> using subtype = T_<V, _s...>;

};
template <template <class, auto  ...> class T_, class U, auto  ..._s> requires (1 <= sizeof...(_s))
struct mint<T_<U, _s...>>
{
	template <class V> using subtype = T_<V, _s...>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
