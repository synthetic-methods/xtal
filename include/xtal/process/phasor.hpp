#pragma once
#include "./anybody.hpp"
#include "./star.hpp"
#include "../content/phase.hpp"




XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <                     typename ..._s> XTAL_NYM phasor;
template <                     typename ..._s> XTAL_ASK phasor_q = tag_p<phasor, _s...>;
template <array_q W=size_t[2], typename ...As> XTAL_USE phasor_t = confined_t<phasor<W, As...>>;


////////////////////////////////////////////////////////////////////////////////
///\

template <array_q W, typename ...As>
struct phasor<W, As...>
{
	XTAL_LET N_ = _std::extent_v<W>;
	XTAL_USE U_ = _std::remove_all_extents_t<W>;
	
	using scope_u = content::phase_t<U_>[N_];
	using subkind = compose<tag<phasor>, As..., star<scope_u>>;

	template <class S>
	using subtype = compose_s<S, subkind>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
