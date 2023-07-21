#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
NOTE: The decorators `Heads...` and `Tails...`, \
supplied as the outer- and inner- arguments respectively, \
are evaluated w.r.t. the corresponding right- or left- fold relative to `S`: \
`A[0]::subtype<...A[N]::subtype<T[N]::subtype<...T[0]::subtype<S>>>>`. \

template <typename ...>
struct compose;

template <>
struct compose<>
{
	template <typename S, typename T>
	using body = typename T::template subtype<S>;

	template <typename S, typename ...Ts>
	struct tail;

	template <typename S>
	struct tail<S>
	{
		using type = S;
	};
	template <typename S, typename T, typename ...Ts>
	struct tail<S, T, Ts...>
	:	tail<body<S, T>, Ts...>
	{};

	template <typename S, typename ...Tails>
	using subtype = typename tail<S, Tails...>::type;

};
template <typename Head, typename ...Heads>
struct compose<Head, Heads...>
{
	template <typename H, typename S>
	using head = typename H::template subtype<S>;

	template <typename S, typename ...Ts>
	using tail = typename compose<Heads...>::template subtype<S, Ts...>;

	template <typename S, typename ...Ts>
	using subtype = head<Head, tail<S, Ts...>>;

};
template <typename ...Heads>
struct compose<void, Heads...>
:	compose<Heads...>
{};

template <typename S, typename ...Tails>
using compose_s = typename compose<>::template subtype<S, Tails...>;


///\
Finalizes `compose` by providing a `type` based on `unit_t`. \

template <typename ...Heads>
struct composed
{
	using subkind = compose<Heads...>;
	
	template <typename S, typename ...Tails>
	using subtype = compose_s<S, Tails..., subkind>;
	using    type = subtype<unit_t>;

};
template <typename S, typename ...Tails>
using composed_s = typename composed<>::template subtype<S, Tails...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
