#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
using ordinal = label<typename realized::iota_t, As...>;

template <typename ...As>
using ordinal_t = compose_s<any_t<>, ordinal<As...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
