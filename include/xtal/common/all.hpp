#pragma once
#include "./any.hpp"
#include "./collate.hpp"
#include "./collect.hpp"
#include "./compose.hpp"
#include "./bundle.hpp"
#include "./realize.hpp"
#include "./seek.hpp"

XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//\
TODO: Split these into separate modules. \

template <typename V, int N> using collection = compose_s<unit_t, collect<N>, collate<V>>;

template <typename V, int N> using fluid_t  = typename collection<V, N>::fluid::type;
template <typename V, int N> using sluice_t = typename collection<V, N>::sluice::type;
template <typename V, int N> using siphon_t = typename collection<V, N>::siphon::type;

template <typename V, int N> using fixed_t  = typename collection<V, N>::fixed::type;
template <typename V, int N> using scalar_t = typename collection<V, N>::scalar::type;
template <typename V, int N> using serial_t = typename collection<V, N>::serial::type;
template <typename V, int N> using series_t = typename collection<V, N>::series::type;
template <typename V, int N> using couple_t = typename collection<V, N>::couple::type;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
