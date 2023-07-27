#pragma once
#include "./anybody.hpp"
#include "./group.hpp"





XTAL_ENV_(push)
namespace xtal::content
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <                typename ..._s> XTAL_NYM pulse;
template <                typename ..._s> XTAL_ASK pulse_q = tag_p<pulse, _s...>;
template <class U=size_t, typename ...As> XTAL_USE pulse_t = confined_t<pulse<U>, As...>;


////////////////////////////////////////////////////////////////////////////////
///\
Represents a local `{store,serve}` pair, \
used as e.g. a buffer and its abstract/copyable `std::span`. \

template <class U>
struct pulse<U>
{
	using _realized = realize<U>;
	using delta_t = typename _realized::delta_t;
	using subkind = compose<tag<pulse>, group<delta_t>>;

	template <class S>
	using subtype = compose_s<S, subkind>;
	
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
