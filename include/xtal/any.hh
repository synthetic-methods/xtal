#pragma once

#include <range/v3/all.hpp>
#if __has_include(<execution>)
#include <execution>
#endif
#include <complex>
#include <numbers>
#include <limits>
#include <cmath>
#include <array>
#include <tuple>
#include <queue>
#include <new>
#include <bit>


#include "./etc.hh"


XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _std = ::std;
namespace _xtd
{
//using namespace _std::experimental;

#if XTAL_VER_(ranges != 3)
namespace ranges        {using namespace ::std::ranges;}
namespace ranges::views {using namespace ::std::ranges::views;}
#else
namespace ranges        {using namespace      ::ranges;}
namespace ranges::views {using namespace      ::ranges::views;}
namespace ranges::views
{
	XTAL_DEF_(inline,let)
	zip_transform(auto &&...oo)
	noexcept -> decltype(auto)
	{
		return zip_with(XTAL_REF_(oo)...);
	};
}
#endif

//\
template <class T> concept trivially_moveable      = _std::             is_trivially_moveable_v<T>;
template <class T> concept trivially_moveable      = _std::   is_trivially_move_constructible_v<T>;
//\
template <class T> concept trivially_copyable      = _std::             is_trivially_copyable_v<T>;
template <class T> concept trivially_copyable      = _std::   is_trivially_copy_constructible_v<T>;
//\
template <class T> concept trivially_initializable = _std::             default_initializable  <T>;
template <class T> concept trivially_initializable = _std::is_trivially_default_constructible_v<T>;

template <class T> concept trivially_constructible = trivially_copyable<T> and trivially_moveable<T>;
template <class T> concept trivially_destructible  = _std::is_trivially_destructible_v<T>;

template <class T> concept semitrivial = _std::semiregular<T> and     _std::destructible<T>;
template <class T> concept     trivial =       semitrivial<T> and trivially_destructible<T> and trivially_constructible<T>;

#if __cpp_lib_bit_cast
using _std::bit_cast;
#else
template <trivial T, trivial S> requires in_n<sizeof(T), sizeof(S)>
XTAL_DEF_(return,inline,let)
bit_cast(S s)
noexcept -> T
{
	return __builtin_bit_cast(T, s);
}
#endif

#if XTAL_VER_(STD < 2300) or XTAL_VER_(MSVC < 1700)
template <trivial T>
XTAL_DEF_(return,inline,let)
copysign(T t, T s)
noexcept -> T
{
	return __builtin_copysign(t, s);
}
#else
using _std::copysign;
#endif



////////////////////////////////////////////////////////////////////////////////

template <class F, class ...Xs> concept          invocable = requires {XTAL_ANY_(F)  (XTAL_ANY_(Xs)...);};
template <class F, class ...Xs> concept constant_invocable = requires {          F{} (XTAL_ANY_(Xs)...);};


template <class T> using       make_signed_t = _std::  make_signed_t<T>;
XTAL_DEF_(return,inline,let)   make_signed_f  (_std::       signed_integral auto i) noexcept -> auto {return i;}
XTAL_DEF_(return,inline,let)   make_signed_f  (_std::     unsigned_integral auto i) noexcept -> auto {return bit_cast<  make_signed_t<decltype(i)>>(i);}
XTAL_DEF_(return,inline,let)   make_signed_f  (          constant_invocable auto f) noexcept -> auto {return   make_signed_f(f());}

template <class T>     using make_unsigned_t = _std::make_unsigned_t<T>;
XTAL_DEF_(return,inline,let) make_unsigned_f  (_std::       signed_integral auto i) noexcept -> auto {return bit_cast<make_unsigned_t<decltype(i)>>(i);}
XTAL_DEF_(return,inline,let) make_unsigned_f  (_std::     unsigned_integral auto i) noexcept -> auto {return i;}
XTAL_DEF_(return,inline,let) make_unsigned_f  (          constant_invocable auto f) noexcept -> auto {return make_unsigned_f(f());}


template <class T> using        remove_reference_t =                                                     _std::remove_reference_t<T>;
template <class T> using remove_rvalue_reference_t = _std::conditional_t<_std::is_rvalue_reference_v<T>, _std::remove_reference_t<T>, T>;
template <class T> using remove_lvalue_reference_t = _std::conditional_t<_std::is_lvalue_reference_v<T>, _std::remove_reference_t<T>, T>;


}//namespace _xtd


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./_retail.ii"
#include "./_entail.ii"
#include "./_detail.ii"

///\returns the result of evaluating the result `y`. \

///\note\
To be implemented by the host to transparently reduce `y` when vectorized. \

template <class T>
XTAL_DEF_(return,inline,let)
objective_f(T &&t)
noexcept -> auto
{
	return XTAL_REF_(t);
}
template <constant_q T>
XTAL_DEF_(return,inline,let)
objective_f(T &&t)
noexcept -> auto
{
	return XTAL_REF_(t)();
}

template <class    T > struct   objective {using type = XTAL_ALL_(objective_f(XTAL_ANY_(T)));};
template <class ...Ts> using    objective_t = common_t<typename objective<Ts>::type...>;


/*/
///\returns the result of applying `f` to `...xs`. \

///\note\
To be implemented by the host to transparently lift `f` when `xs...` are vectorized. \

template <class F, class ...Xs> XTAL_DEF_(inline,let) operative_f(F &&f, Xs &&...xs) noexcept -> decltype(auto) {return            XTAL_REF_(f) (XTAL_REF_(xs)...);}
template <class F, class ...Xs> XTAL_DEF_(inline,let) operative_f(       Xs &&...xs) noexcept -> decltype(auto) {return operative_f(invoke_n<F>, XTAL_REF_(xs)...);}
template <class F             > XTAL_DEF_(inline,let) operative_f(F &&f            ) noexcept -> decltype(auto) {return         [] XTAL_0FN_(alias)  (operative_f);}

template <template <class> class Y, class ...Xs>
XTAL_DEF_(return,inline,let)
construxion_f(Xs &&...xs)
noexcept -> decltype(auto)
{
	using W = common_t<Xs...>;
	return operative_f<Y<W>>(XTAL_REF_(xs)...);
}
XTAL_DEF_(return,inline,let)
complexion_f(auto &&...xs)
noexcept -> decltype(auto)
{
	return construxion_f<_std::complex>(XTAL_REF_(xs)...);
}
/***/


////////////////////////////////////////////////////////////////////////////////

#if XTAL_LOG
class
{
	XTAL_DEF_(let)
	print_list(auto &&x) const
	noexcept -> void
	{
		for (auto &&w: XTAL_REF_(x)) ::std::cout << XTAL_REF_(w) << '\t';
	}
	XTAL_DEF_(let)
	print_item(auto &&x) const
	noexcept -> void
	{
		using W = XTAL_ALL_(x);
		if constexpr (continuous_field_q<W>) {
			::std::cout.precision(17);
		}
		if constexpr (::std::is_arithmetic_v<W>) {
			if (::std::copysign(1.0, x) == 1.0) {
				 ::std::cout << ' ';
			}
		}
		::std::cout << XTAL_REF_(x) << '\t';
	}
	XTAL_DEF_(let)
	put(auto &&x) const
	noexcept -> decltype(auto)
	{
		using W = XTAL_ALL_(x);
		if constexpr (_xtd::ranges::range<W> and requires {::std::is_arithmetic_v<typename W::value_type>;}) {
			print_list(XTAL_REF_(x));
		}
		else {
			print_item(XTAL_REF_(x));
		}
		return XTAL_REF_(x);
	}

public:
	XTAL_DEF_(let)
	operator() (auto &&...xs) const
	noexcept -> decltype(auto)
	{
		if constexpr (0 < sizeof...(xs)) {
			::std::cout << '\t'; auto const x = (put(XTAL_REF_(xs)), ...);
			::std::cout << '\n';
			return x;
		}
		else {
			::std::cout << '\n';
		}
	}

}
#else
class
{
public:
	XTAL_DEF_(inline,let)
	operator() (auto &&...xs) -> decltype(auto)
	{
		if constexpr (0 < sizeof...(xs)) {
			return (XTAL_REF_(xs), ...);
		}
	}

}
#endif
const echo;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
