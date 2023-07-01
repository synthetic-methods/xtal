#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename U=_std::ptrdiff_t>
struct delay
:	lift<U, only<delay>>
{
};
template <typename S=confined_t<>, typename U=_std::ptrdiff_t>
using delay_s = compose_s<S, delay<U>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
