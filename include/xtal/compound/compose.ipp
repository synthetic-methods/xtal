#pragma once
#include "./any.ipp"






XTAL_ENV_(push)
namespace xtal::compound
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
NOTE: The decorators `Heads...` and `Tails...`, \
supplied as the outer- and inner- arguments respectively, \
are evaluated w.r.t. the corresponding right- or left- fold relative to `S`: \
`Heads[0]::subtype<...Heads[N]::subtype<Tails[N]::subtype<...Tails[0]::subtype<S>>>>`. \

template <typename ...>
struct compose;

template <>
struct compose<>
{
	template <class S, typename ..._s>
	struct tail
	{
		using type = S;
	};
	template <class S, typename _, typename ..._s>
	struct tail<S, _, _s...>
	:	tail<typename _::template subtype<S>, _s...>
	{
	};
	template <class S, typename ..._s>
	using subtype = typename tail<S, _s...>::type;

};
template <typename A, typename ...As>
struct compose<A, As...>
{
	template <class S, typename ..._s>
	using subtype = typename A::template subtype<
		typename compose<As...>::template subtype<S, _s...>
	>;

};
template <typename ...As>
struct compose<void, As...>
:	compose<As...>
{
};

template <class S, typename ..._s>
using compose_s = typename compose<>::template subtype<S, _s...>;


///\
Finalizes `compose` by providing a `type` based on `unit_t`. \

template <typename ...As>
struct composed
{
	using subkind = compose<As...>;
	
	template <class S, typename ..._s>
	using subtype = compose_s<S, _s..., subkind>;
	using    type = subtype<unit_t>;

};
template <class S, typename ...Tails>
using composed_s = typename composed<>::template subtype<S, Tails...>;

template <typename ...Heads>
using composed_t = typename composed<Heads...>::type;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
