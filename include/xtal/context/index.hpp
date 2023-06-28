#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using index_t = typename realized::iota_t;

template <typename S=confined_t<>, typename T=index_t>
using index_s = compose_s<S, confer<T, any<struct index>>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
