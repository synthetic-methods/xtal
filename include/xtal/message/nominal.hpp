#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//\
TODO: Maybe revise this to allow `enum`. \


////////////////////////////////////////////////////////////////////////////////

template <int N, typename ...As>
using nominal = label<constant_t<N>, As...>;

template <int N, typename ...As>
using nominal_t = compose_s<any_t<>, nominal<N, As...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
