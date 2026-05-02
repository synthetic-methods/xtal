#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*!
\brief 	Extracts the underlying `value_type` as `type`,
         exposing an alternate-value-constructor via the `template subtype`.
*/
template <class ...Ts>
struct depose
{
	template <class V>
	using subtype = V;
	using    type = void;

};
/*!
\brief  	Replaces the underlying `value_type` with the provided `template <class>`, via the member-`subtype`.
*/
template <template <class> class T_, class U>
struct depose<T_<U>> : depose<U>
{
	template <class V>
	using subtype = T_<V>;
	using    type = U;

};
template <template <class> class T_, vector_q W>
struct depose<T_<W>> : depose<_xtd::remove_extent_t<W>>
{
	template <class V>
	using subtype = T_<V>[_xtd::extent_v<W>];
	using    type = _xtd::remove_extent_t<W>;

};
/*!
\brief  	Replaces the underlying `value_type` with the provided `template <class, class ...>`, via the member-`subtype`.
*/
template <template <class, class ...> class T_, class U, class ..._s> requires some_q<_s...>
struct depose<T_<U, _s...>> : depose<U>
{
	template <class V>
	using subtype = T_<V, _s...>;
	using    type = U;

};
/*!
\brief  	Replaces the underlying `value_type` with the provided `template <class, auto  ...>`, via the member-`subtype`.
*/
template <template <class, auto  ...> class T_, class U, auto  ..._s> requires some_v<_s...>
struct depose<T_<U, _s...>> : depose<U>
{
	template <class V>
	using subtype = T_<V, _s...>;
	using    type = U;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
