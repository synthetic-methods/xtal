#include "./any.hh"
#include "./compose.hh"
#include "./depose.hh"
#include "./derive.hh"
#include "./devoid.hh"
#include "./fit.hh"
#include "./operate.hh"
#include "./pack.hh"
#include "./seek.hh"
#include "./tab.hh"
#include "./tag.hh"
#include "./word.hh"

#ifndef XTAL_bond
#define XTAL_bond
XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

XTAL_VAL_(let)  half = bond::operate{[] XTAL_1FN_(to) (bond::fit<>::haplo_1)};
XTAL_VAL_(let)  zero = bond::operate{[] XTAL_1FN_(to) (0)};
XTAL_VAL_(let)   one = bond::operate{[] XTAL_1FN_(to) (1)};
XTAL_VAL_(let)   two = bond::operate{[] XTAL_1FN_(to) (2)};
XTAL_VAL_(let)   pie = bond::operate{[] XTAL_1FN_(to) (bond::fit<>::patio_1)};

static_assert((one >> 1.F) == half);
static_assert((one << 1.F) ==  two);

static_assert(constant_q<decltype( half)>);
static_assert(constant_q<decltype(+half)>);
static_assert(constant_q<decltype(-half)>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
#endif//XTAL_bond
