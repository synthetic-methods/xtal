#pragma once
#include "./any.hh"
#include "./tab.hh"
//nclude "./tag.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

///\
Provides `typename compose<Ts_...>::template subtype<S, _Ts...>`, \
first applying `_Ts` to `S`        from left-to-right, \
then  applying `Ts_` to the result from right-to-left. \

template <typename ...Ts_>	using    compose   =         _detail::excompose<Ts_...> ;
template <typename ...Ts_>	concept  compose_q = (...and _detail::compose_q<Ts_   >);

template <template <class, class...> class ...Ts_> using compose_t = _detail::excompose_t<   Ts_...>;///< Composes `Ts_`                 from right-to-left.
template <class S,                typename ..._Ts> using compose_s = _detail::incompose_s<S, _Ts...>;///< Applies  `_Ts::subtype` to `S` from left-to-right.


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
