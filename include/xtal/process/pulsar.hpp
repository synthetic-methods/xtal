#pragma once
#include "./anybody.hpp"
#include "./star.hpp"
#include "../content/pulse.hpp"




XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <                     typename ..._s> XTAL_NYM pulsar;
template <                     typename ..._s> XTAL_ASK pulsar_q = tag_p<pulsar, _s...>;
template <array_q W=size_t[2], typename ...As> XTAL_USE pulsar_t = confined_t<pulsar<W, As...>>;


////////////////////////////////////////////////////////////////////////////////
///\

template <array_q W, typename ...As>
struct pulsar<W, As...>
{
	XTAL_LET N_ = _std::       extent_v<W>;
	XTAL_USE U_ = _std::remove_extent_t<W>;
	
	using scope_u = content::pulse_t<U_>[N_];
	using subkind = compose<tag<pulsar>, As..., star<scope_u>>;

	template <class S>
	using subtype = compose_s<S, subkind>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
