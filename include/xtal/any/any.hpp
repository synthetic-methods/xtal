#pragma once
#include <concepts>
#include <cassert>
#include <cstdint>
#include <complex>
#include <numbers>
#include <variant>
#include <cstring>
#include <cmath>
#include <tuple>
#include <array>
#include <queue>



#if __has_include(<execution>)
#include <execution>
#endif



#include <bit>
#if not __cpp_lib_bit_cast
namespace std
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename To, typename Fro>
requires (sizeof(To) == sizeof(Fro) and is_trivially_copyable_v<To> and is_trivially_copyable_v<Fro>)
static constexpr To bit_cast(Fro const& fro)
noexcept
{
	return __builtin_bit_cast(To, fro);
//	To to; memcpy(&to, &fro, sizeof(fro)); return to;
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
#endif



#include <range/v3/all.hpp>
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _std = ::std;
namespace _v3
{
namespace ranges = ::ranges;
namespace views  = ::ranges::views;
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////



#include "../_.hpp"

#if XTAL_LOG
#include <iostream>
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
struct
{
	template <typename X>
	void put(X&& x)
	{
		if constexpr (std::is_floating_point_v<std::decay_t<X>>)
		{
			std::cout.precision(17);
			if (std::copysign(1.0, x) == 1.0) std::cout << ' ';
		}
		std::cout << static_cast<X&&>(x);
	}
	template <typename... Xs>
	void put(Xs&&...xs)
	{
		(put(static_cast<Xs &&>(xs)), ...);
	}

	template <typename X>
	decltype(auto) operator<< (X&& x)
	{
		put(static_cast<X&&>(x));
		return *this;
	}
	template <typename... Xs>
	decltype(auto) operator() (Xs&&... xs)
	{
		(put('\t', static_cast<Xs&&>(xs)), ...);
		std::cout << '\n';
		return *this;
	}

} ouch;
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
#else
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
struct
{
	void operator() (auto&&... etc)
	{
	}
	decltype(auto) operator<< (auto&& etc)
	{
	}
	decltype(auto) operator<<= (auto&& etc)
	{
	}

} ouch;
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
#endif

