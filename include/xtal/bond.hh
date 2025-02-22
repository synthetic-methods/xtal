#pragma once
#include "./bond/all.hh"






XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) half = bond::operate{[] XTAL_1FN_(to) (0.5F)};
XTAL_DEF_(let) zero = bond::operate{[] XTAL_1FN_(to) (0)};
XTAL_DEF_(let)  one = bond::operate{[] XTAL_1FN_(to) (1)};
XTAL_DEF_(let)  two = bond::operate{[] XTAL_1FN_(to) (2)};

static_assert((one >> 1.F) == half);
static_assert((one << 1.F) ==  two);

static_assert(constant_q<decltype( half)>);
static_assert(constant_q<decltype(+half)>);
static_assert(constant_q<decltype(-half)>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
