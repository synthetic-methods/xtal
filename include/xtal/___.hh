#pragma once

#if __has_include(<execution>)
#include <execution>
#endif
#include <concepts>
#include <cassert>
#include <cstring>
#include <complex>
#include <numbers>
#include <cmath>
#include <tuple>
#include <array>
#include <queue>
#include <new>
#include <bit>

//#if __has_include(<arm_neon.h>)
//#include <arm_neon.h>
//#endif

#include <simde/arm/neon.h>
#include <range/v3/all.hpp>



namespace std
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#if not __cpp_lib_bit_cast
template <class T, class S> requires (
	is_trivially_copyable_v<T> and
	is_trivially_copyable_v<S> and
	sizeof(T) == sizeof(S)
)
static constexpr T bit_cast(S const& s) noexcept {return __builtin_bit_cast(T, s);}
#endif


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
