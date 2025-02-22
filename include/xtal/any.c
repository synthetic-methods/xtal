#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <catch2/catch_all.hpp>
#include "./any.h"


////////////////////////////////////////////////////////////////////////////////

#define   VOID_(...)        (void) (__VA_ARGS__);
#define UNTRUE_(...)   REQUIRE(not (__VA_ARGS__))
#define   TRUE_(...)   REQUIRE(    (__VA_ARGS__))
#define    TRY_(...)   SECTION(    (__VA_ARGS__))
#define    EST_(...) BENCHMARK(    (__VA_ARGS__))

#define TAG_(...) TEST_CASE(__FILE__ ":" XTAL_TXT_(__LINE__), TAG_N_(__VA_ARGS__))
#define TAG_N_(...)                           XTAL_APP_(map) (TAG_1_,__VA_ARGS__)
#define TAG_1_(...)                                              "[" __VA_ARGS__ "]"
