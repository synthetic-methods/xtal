#pragma once
#include "./bond/all.hh"






XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

auto constexpr zero = bond::operate{[] XTAL_1FN_(value) (0   )};
auto constexpr half = bond::operate{[] XTAL_1FN_(value) (0.5F)};
auto constexpr  one = bond::operate{[] XTAL_1FN_(value) (1   )};
auto constexpr  two = bond::operate{[] XTAL_1FN_(value) (2   )};

static_assert(constant_q<decltype( half)>);
static_assert(constant_q<decltype(+half)>);
static_assert(constant_q<decltype(-half)>);

template <auto  N> auto constexpr half_n = bond::operate{[] XTAL_1FN_(value) (1.F/(one << N))};
template <auto  N> auto constexpr  two_n = bond::operate{[] XTAL_1FN_(value) (1.F*(one << N))};



///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
