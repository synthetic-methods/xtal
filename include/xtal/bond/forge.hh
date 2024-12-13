#pragma once
#include "./any.hh"
#include "./compose.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class U>
struct forge
{
	template <class V>
	using subtype = V;

};
template <template <class, class ...> class T_, class U>
struct forge<T_<U>>
{
	template <class V>
	using subtype = T_<V>;

};
template <template <class, class ...> class T_, class U, class ..._s> requires (1 <= sizeof...(_s))
struct forge<T_<U, _s...>>
{
	template <class V>
	using subtype = T_<V, _s...>;

};
template <template <class, auto  ...> class T_, class U, auto  ..._s> requires (1 <= sizeof...(_s))
struct forge<T_<U, _s...>>
{
	template <class V>
	using subtype = T_<V, _s...>;

};


////////////////////////////////////////////////////////////////////////////////

static_assert(is_q<_std::complex<int   >, compose_s<int, forge<_std::complex<double   >>>>);
static_assert(is_q<_std::array  <int, 2>, compose_s<int, forge<_std::array  <double, 2>>>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
