#pragma once
#include <concepts>
#include <cassert>
#include <complex>
#include <numbers>
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

namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
#if XTAL_LOG
#include <iostream>
class
{
	template <typename X>
	void put_list(X &&x)
	{
		for (auto &&_: x) ::std::cout << static_cast<decltype(_) &&>(_) << '\t';
	}
	template <typename X>
	void put_item(X &&x)
	{
		using W = ::std::decay_t<X>;
		if constexpr (::std::is_floating_point_v<W>)
		{	::std::cout.precision(17);
		}
		if constexpr (::std::is_arithmetic_v<W>)
		{	if (::std::copysign(1.0, x) == 1.0)
			{	 ::std::cout << ' ';

			}
		}
		::std::cout << x;
	}

public:
	template <typename X>
	decltype(auto) put(X &&x)
	{
		using W = ::std::remove_reference_t<X>;
		if constexpr (_v3::ranges::range<W> and requires {::std::is_arithmetic_v<typename W::value_type>;})
		{	put_list(static_cast<X &&>(x));
		}
		else
		{	put_item(static_cast<X &&>(x));
		}
		return static_cast<X &&>(x);
	}
	template <typename ...Xs>
	decltype(auto) operator() (Xs &&...xs)
	{
		::std::cout << '\t';
		auto const x = (put(static_cast<Xs &&>(xs)), ...);
		::std::cout << '\n';
		return x;
	}

} echo;
#else
class
{
public:
	template <typename ...Xs>
	decltype(auto) put(Xs &&...xs)
	{
	}
	template <typename ...Xs>
	decltype(auto) operator() (Xs &&...xs)
	{
	}

} echo;
#endif
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////

