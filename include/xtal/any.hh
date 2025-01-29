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
{///////////////////////////////////////////////////////////////////////////////
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
	}
}
#endif

template <class T> concept trivially_destructible  = _std::           is_trivially_destructible_v<T>;
//\
template <class T> concept trivially_moveable      = _std::               is_trivially_moveable_v<T>;
template <class T> concept trivially_moveable      = _std::     is_trivially_move_constructible_v<T>;
//\
template <class T> concept trivially_copyable      = _std::               is_trivially_copyable_v<T>;
template <class T> concept trivially_copyable      = _std::     is_trivially_copy_constructible_v<T>;
//\
template <class T> concept trivially_initializable = _std::               default_initializable  <T>;
template <class T> concept trivially_initializable = _std::  is_trivially_default_constructible_v<T>;

template <class T> concept trivially_constructible = trivially_copyable<T> and trivially_moveable<T>;

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


template <class T>	struct remove_rvalue_cvref : remove_rvalue_cvref<T &&> {};
template <class T>	struct remove_rvalue_cvref<T const &&> {using type = T         ;};
template <class T>	struct remove_rvalue_cvref<T       &&> {using type = T         ;};
template <class T>	struct remove_rvalue_cvref<T const  &> {using type = T const  &;};
template <class T>	struct remove_rvalue_cvref<T        &> {using type = T        &;};
template <class T>	using  remove_rvalue_cvref_t = typename remove_rvalue_cvref<T>::type;
XTAL_FX0_(alias) (template <class T>
XTAL_DEF_(return,inline,get)
remove_rvalue_cvref_f(T &&t), static_cast<remove_rvalue_cvref_t<T>>(t))

template <class T>	struct remove_lvalue_cvref : remove_lvalue_cvref<T &&> {};
template <class T>	struct remove_lvalue_cvref<T const &&> {using type = T const &&;};
template <class T>	struct remove_lvalue_cvref<T       &&> {using type = T       &&;};
template <class T>	struct remove_lvalue_cvref<T const  &> {using type = T         ;};
template <class T>	struct remove_lvalue_cvref<T        &> {using type = T         ;};
template <class T>	using  remove_lvalue_cvref_t = typename remove_lvalue_cvref<T>::type;
XTAL_FX0_(alias) (template <class T>
XTAL_DEF_(return,inline,get)
remove_lvalue_cvref_f(T &&t), static_cast<remove_lvalue_cvref_t<T>>(t))


}///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./_retail.ii"
#include "./_entail.ii"
#include "./_detail.ii"


template <auto f>
XTAL_DEF_(return,inline,let) objective_f(auto &&...) noexcept -> auto;///< Mapping    for expression-templates.
XTAL_DEF_(return,inline,let) operative_f(auto &&   ) noexcept -> auto;///< Resolution for expression-templates.

template <auto f>
XTAL_DEF_(return,inline,let)
operative_f(auto &&...xs)
noexcept -> auto
{
	return f(XTAL_REF_(xs)...);
}
XTAL_DEF_(return,inline,let)
objective_f(auto &&o)
noexcept -> auto
{
	XTAL_IF0
	//\
	XTAL_0IF (applicable_p<decltype(o)>) {return XTAL_REF_(o)();}
	XTAL_0IF (  constant_q<decltype(o)>) {return XTAL_REF_(o)();}
	XTAL_0IF (  variable_q<decltype(o)>) {return XTAL_REF_(o)  ;}
}
template <class ...Xs>
using objective_t = common_t<XTAL_ALL_(objective_f(XTAL_ANY_(Xs)))...>;
///< Obtains the common objective `type` for `Xs...`.

template <class ...Xs>
concept  objective_q = same_q<objective_t<Xs>..., Xs...>;

template <class ...Xs>
concept subjective_q = not objective_q<Xs...>;

template <class ...Ts> auto   surjective_f(            Ts... ) -> objective_t<valued_u<Ts>...>;
template <class ...Ts> auto   surjective_f(_std::tuple<Ts...>) -> objective_t<Ts...>;
template <class ...Ts> auto   surjective_f(_std::pair <Ts...>) -> objective_t<Ts...>;
template <class ...Ts> using  surjective_t = common_t<XTAL_ALL_(surjective_f(XTAL_ANY_(Ts)))...>;
///< Obtains the common objective `value_type` for `Xs...`.

//\todo\
Generalize `surjective_f` using `bond::pack`? \


///\returns an instance of the given template applied to either `Xs...` or `common_t<Xs...>`. \

template <template <class ...> class F, class ...Xs>
XTAL_DEF_(return,inline,let)
construxion_f(Xs &&...xs)
noexcept -> auto;

template <template <class ...> class F, class ...Xs>
XTAL_DEF_(return,inline,let)
construxion_f(Xs &&...xs)
noexcept -> auto
{
	XTAL_IF0
	XTAL_0IF (requires {typename F<based_t<Xs>...>;}) {return operative_f<evoke_t<F<based_t<Xs>...>>{}>(XTAL_REF_(xs)...);}
	XTAL_0IF (requires {typename F<cased_t<Xs...>>;}) {return operative_f<evoke_t<F<cased_t<Xs...>>>{}>(XTAL_REF_(xs)...);}
	XTAL_0IF_(abort)
}

///\returns an instance of `std::complex` applied to `common_t<Xs...>`. \

template <class ...Xs>
XTAL_DEF_(return,inline,let)
complexion_f(Xs &&...xs)
noexcept -> auto;

template <class ...Xs>
XTAL_DEF_(return,inline,let)
complexion_f(Xs &&...xs)
noexcept -> auto
{
	return construxion_f<_std::complex>(XTAL_REF_(xs)...);
}


////////////////////////////////////////////////////////////////////////////////

#if XTAL_LOG
class
{
	void print_list(auto const &x) const {
		for (auto const &w: x) {
			::std::cout << w << '\t';
		}
	}
	void print_item(auto const &x) const {
		using X = XTAL_ALL_(x); using namespace ::std;
		if constexpr (continuous_field_q<X>) {
			cout.precision(17);
		}
		if constexpr (is_arithmetic_v<X>) {
			if (1.0 == copysign(1.0, x)) {
				 cout << ' ';
			}
		}
		cout << x << '\t';
	}
	auto put(auto &&x) const noexcept -> decltype(auto) {
		using X = XTAL_ALL_(x);
		if constexpr (_xtd::ranges::range<X> and requires {::std::is_arithmetic_v<typename X::value_type>;}) {
			print_list(x);
		}
		else {
			print_item(x);
		}
		return XTAL_REF_(x);
	}

public:
	auto operator() (auto &&...xs) const noexcept -> decltype(auto) {
		if constexpr (1 <= sizeof...(xs)) {
			::std::cout << '\t'; auto const x = (put(XTAL_REF_(xs)), ...);
			::std::cout << '\n';
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
	auto operator() (auto &&...xs) -> decltype(auto) {
		if constexpr (1 <= sizeof...(xs)) {
			return (XTAL_REF_(xs), ...);
		}
	}

}
#endif
const echo;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
