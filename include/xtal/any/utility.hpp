#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <auto...          Ns >   concept       true_q  =     (bool(Ns)  or...);///< Matches if any `Ns... == 1`.
template <auto...          Ns >   concept      false_q  = not (bool(Ns) and...);///< Matches if any `Ns... == 0`.
template <auto...          Ns >   concept     untrue_q  = not (bool(Ns)  or...);///< Matches if all `Ns... == 0`.
template <auto...          Ns >   concept    unfalse_q  =     (bool(Ns) and...);///< Matches if all `Ns... == 1`.
template <auto             N=0>   concept   positive_q  = (0 < N);
template <auto             N=0>   concept   negative_q  = (N < 0);
template <typename T, auto N  >   concept    breadth_q  = (N == sizeof(T));
template <typename         X  >   using      bracket_t  = _std::initializer_list<X>;
template <typename         T  >   concept    pointer_b  = _std::is_pointer_v<_std::decay_t<T>>;
template <typename...      Ts >   concept    pointer_q  = unfalse_q<pointer_b<Ts>...>;
template <typename         T  >   using        value_t  = typename _std::decay_t<T>::value_type;
template <typename         T  >   XTAL_LET     value_v  =          _std::decay_t<T>::value;

template <typename...      Ts >   struct       craft    {using type = _std::variant<Ts...>;};
template <                    >   struct       craft< > {using type = _std::monostate     ;};
template <typename         T  >   struct       craft<T> {using type = T                   ;};
template <typename...      Ts >   using        craft_t  = typename craft<Ts...>::type;
template <typename...      Ts >   XTAL_LET     craft_f  = [] (XTAL_DEF... ws) XTAL_0FN_(craft_t<Ts...> (XTAL_REF_(ws)...));

template <auto             N  >   using        cased    = _std::integral_constant<XTAL_TYP_(N), N>;
template <typename         T  >   concept      cased_b  = _std::is_base_of_v<_std::integral_constant<value_t<T>, value_v<T>>, T>;
template <typename...      Ts >   concept      cased_q  = unfalse_q<cased_b<Ts>...>;

template <typename         T  >   using        based_t  = _std::decay_t<T>;
template <typename         T  >   concept      based_b  = _std::is_same_v<T, based_t<T>> and _std::is_trivially_copy_constructible_v<T>;
template <typename         T  >   concept    unbased_b  = not based_b<T>;

template <typename         T  >   struct     debased           : cased<false> {using type = based_t<T>;};
template <typename         T  >   struct     debased<T const &>: cased<false> {using type = based_t<T>;};
template <unbased_b        T  >   struct     debased<T       &>: cased<true>  {using type =         T*;};
template <typename         T  >   using      debased_t  = typename debased<T>::type;
template <typename         T  >   concept    debased_b  =          debased<T>::value;

template <typename...      Ts >   concept    debased_q  = unfalse_q<debased_b<Ts>...>;
template <typename...      Ts >   concept    unbased_q  = unfalse_q<unbased_b<Ts>...>;
template <typename...      Ts >   concept      based_q  = unfalse_q<  based_b<Ts>...>;

template <_std::size_t...  Ns >   using         seek_t  = _std::     index_sequence<Ns...>;
template <_std::size_t     N  >   XTAL_LET      seek_v  = _std::make_index_sequence<N>{};
template <auto N=0>
XTAL_FZ1 seek_f(auto f)
XTAL_0EX
{
	return [&] <auto... Ns> (seek_t<Ns...>)
		XTAL_0FN_(..., f(Ns)) (seek_v<N>);
}
template <auto N=0>
XTAL_FZ1 seek_f(XTAL_DEF w, auto f)
XTAL_0EX
{
	return [&] <auto... Ns> (seek_t<Ns...>)
		XTAL_0FN_(XTAL_REF_(w), ..., f(Ns)) (seek_v<N>);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename    T > concept complex_b = requires (T t)
{
	{t.real()} -> _std::same_as<value_t<T>>;
	{t.real()} -> _std::same_as<value_t<T>>;
};
template <typename    T > concept boolean_b = _std::is_same_v<bool, _std::remove_reference_t<T>>;
template <typename... Ts> concept complex_q = unfalse_q<complex_b<Ts>...>;
template <typename... Ts> concept boolean_q = unfalse_q<boolean_b<Ts>...>;

template <typename T>
XTAL_FZ2 square_y(T const &lhs)
XTAL_0EX
{
	return lhs*lhs;
}
template <complex_q T>
XTAL_FZ2 square_y(T const &lhs)
XTAL_0EX
{
	auto const x = lhs.real(), xx = square_y(x);
	auto const y = lhs.imag(), yy = square_y(y);
	return T(xx - yy, x*y*2.0);
}

template <complex_q T>
XTAL_FZ2 dot_y(T const &lhs)
XTAL_0EX
{
	auto const x = lhs.real(), xx = square_y(x);
	auto const y = lhs.imag(), yy = square_y(y);
	return xx + yy;
}

template <complex_q T>
XTAL_FZ2 arc_y(auto const &phi)
XTAL_0EX
{
	auto const x = _std::cos(phi);
	auto const y = _std::sin(phi);
	return T(x, y);
}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
