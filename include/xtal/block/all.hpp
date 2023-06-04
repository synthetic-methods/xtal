#pragma once
#include "./any.hpp"
#include "./collected.hpp"
#include "./collector.hpp"


#include "../common/compose.hpp"

XTAL_ENV_(push)
namespace xtal::block
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
template <int N,   typename V> using collection = compose_s<unit_t, collector<N>, collected<V>>;
template <int N,   typename V> using   buffer_t = typename collection<N, V>::   buffer::type;
template <int N,   typename V> using   scalar_t = typename collection<N, V>::   scalar::type;
template <int N,   typename V> using   serial_t = typename collection<N, V>::   serial::type;
template <int N,   typename V> using   series_t = typename collection<N, V>::   series::type;
template <int N,   typename V> using parallel_t = typename collection<N, V>:: parallel::type;
template <typename V, int M=0> using converse_t = typename collection<2, V>::template converse<M>::type;

template <int N, typename V, size_t M=0> using siphon_t = typename collection<N, V>::template siphon<M>::type;
template <int N, typename V, size_t M=0> using sluice_t = typename collection<N, V>::template sluice<M>::type;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
