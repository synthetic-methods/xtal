#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Composes the supplied `Outer::subtype`s to define `::subtype<S, Inner...>`. \

///\note\
The `Outer...::subtype`s are applied to `::subtype<S, Inner...>` from right-to-left, \
while the `Inner...::subtype`s are applied to `S` from left-to-right. \

template <typename ...Outer>
struct compose;

template <>
struct compose<>
{
private:
	template <class S, typename ...Inner                > struct compact {using type = S;};
	template <class S, typename    Inner, typename ..._s>
	struct compact<S, Inner, _s...>
	:	compact<typename Inner::template subtype<S>, _s...>
	{};

public:
	template <class S, typename ...Inner>
	using subtype = typename compact<S, Inner...>::type;

};
template <typename Outer, typename ..._s>
struct compose<Outer, _s...>
{
	template <class S, typename ...Inner>
	using subtype = typename Outer::template subtype<
		typename compose<_s...>::template subtype<S, Inner...>
	>;

};
template <typename ...Outer>
struct compose<void, Outer...>
:	compose<Outer...>
{
};

///\
Applys the `Inner::subtype`s to `S` from left-to-right. \

template <class S, typename ...Inner>
using   compose_s = typename compose<>::template subtype<S, Inner...>;

template <typename ...Subtyped>
concept compose_q = (...and _detail::compose_q<Subtyped>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
