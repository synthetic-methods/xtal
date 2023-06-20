#pragma once
#include "./any.hpp"
#include "./collected.hpp"
#include "./collector.hpp"


#include "../common/compose.hpp"

XTAL_ENV_(push)
namespace xtal::block
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
template <typename V, int N> using collection = compose_s<unit_t, collector<N>, collected<V>>;
template <typename V, int N> using solid_t  = typename collection<V, N>::solid::type;
template <typename V, int N> using fluid_t  = typename collection<V, N>::fluid::type;
template <typename V, int N> using buffer_t = typename collection<V, N>::buffer::type;
template <typename V, int N> using sluice_t = typename collection<V, N>::sluice::type;
template <typename V, int N> using siphon_t = typename collection<V, N>::siphon::type;
template <typename V, int N> using scalar_t = typename collection<V, N>::scalar::type;
template <typename V, int N> using serial_t = typename collection<V, N>::serial::type;
template <typename V, int N> using series_t = typename collection<V, N>::series::type;
template <typename V, int N> using couple_t = typename collection<V, N>::couple::type;
//\
TODO: Split these into separate modules. \

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
