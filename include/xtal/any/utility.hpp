#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <typename...> typename> struct tag {};
template <auto     ...Ns > concept       true_p =     (bool(Ns)  or...);///< Any `Ns... == 1`.
template <auto     ...Ns > concept      false_p = not (bool(Ns) and...);///< Any `Ns... == 0`.
template <auto     ...Ns > concept     untrue_p = not (bool(Ns)  or...);///< All `Ns... == 0`.
template <auto     ...Ns > concept    unfalse_p =     (bool(Ns) and...);///< All `Ns... == 1`.

template <typename    T  > using         type_t = typename _std::remove_reference_t<T>::type;
template <typename    T  > using        value_t = typename _std::remove_reference_t<T>::value_type;
template <typename    T  > XTAL_LET     value_v =          _std::remove_reference_t<T>::value;

                           using      nothing_t = _std::nullptr_t;
template <typename    X  > using      bracket_t = _std::initializer_list<X>;
template <typename    T  > concept    pointer_b = _std::is_pointer_v<_std::decay_t<T>>;
template <typename ...Ts > concept    pointer_q = unfalse_p<pointer_b<Ts>...>;

template <auto        N  > using     constant   = _std::integral_constant<XTAL_TYP_(N), N>;
template <typename    T  > concept   constant_b = _std::is_base_of_v<_std::integral_constant<value_t<T>, value_v<T>>, T>;
template <typename ...Ts > concept   constant_q = unfalse_p<constant_b<Ts>...>;

template <typename ...Ts > struct   construct    {using type = _std::variant<Ts...>;};
template <               > struct   construct< > {using type = _std::monostate     ;};
template <typename    T  > struct   construct<T> {using type = T                   ;};
template <typename ...Ts > using    construct_t = type_t<construct<Ts...>>;
template <typename ...Ts > XTAL_LET construct_f = [] (XTAL_DEF ...oo) XTAL_0FN_(construct_t<Ts...> (XTAL_REF_(oo)...));


template <typename    T  > using        based_t = _std::decay_t<T>;
template <typename    T  > concept      based_b = _std::same_as<T, based_t<T>> and _std::is_trivially_copy_constructible_v<T>;
template <typename ...Ts > concept      based_q = unfalse_p<based_b<Ts>...>;

template <typename    T  > concept    unbased_b = not based_b<T>;
template <typename ...Ts > concept    unbased_q = unfalse_p<unbased_b<Ts>...>;

template <typename    T  > struct     rebased            : constant<false> {using type = T;};
template <typename    T  > struct     rebased<T const &&>: constant<true>  {using type = T;};
template <typename    T  > struct     rebased<T       &&>: constant<true>  {using type = T;};
template <typename    T  > using      rebased_t =    type_t<rebased<T>>;
template <typename    T  > concept    rebased_b =   value_v<rebased<T>>;
template <typename ...Ts > concept    rebased_q = unfalse_p<rebased_b<Ts>...>;

template <typename    T  > struct     debased           : constant<false> {using type = based_t<T>;};
template <typename    T  > struct     debased<T const &>: constant<false> {using type = based_t<T>;};
template <unbased_b   T  > struct     debased<T       &>: constant<true>  {using type =         T*;};
template <typename    T  > using      debased_t =    type_t<debased<T>>;
template <typename    T  > concept    debased_b =   value_v<debased<T>>;
template <typename ...Ts > concept    debased_q = unfalse_p<debased_b<Ts>...>;


template <_std::size_t ...Ns > using    seek_t  = _std::     index_sequence<Ns...>;
template <_std::size_t    N  > XTAL_LET seek_v  = _std::make_index_sequence<N>{};
template <auto N=0>
XTAL_FZ1 seek_f(auto f)
XTAL_0EX
{
	return [&] <auto ...Ns> (seek_t<Ns...>)
		XTAL_0FN_(..., f(Ns)) (seek_v<N>);
}
template <auto N=0>
XTAL_FZ1 seek_f(XTAL_DEF w, auto f)
XTAL_0EX
{
	return [&] <auto ...Ns> (seek_t<Ns...>)
		XTAL_0FN_(XTAL_REF_(w), ..., f(Ns)) (seek_v<N>);
}

template <_std::size_t I, bool ...Ns> struct   truth_seeker;
template <_std::size_t I, bool ...Ns> struct   truth_seeker<I,  true, Ns...>: constant<I> {};
template <_std::size_t I, bool ...Ns> struct   truth_seeker<I, false, Ns...>: truth_seeker<I + 1, Ns...> {};
template <                bool ...Ns> using    truth_index_t  = truth_seeker<0, Ns..., true>;
template <                bool ...Ns> XTAL_LET truth_index_v  = value_v<truth_index_t<Ns...>>;


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename    T > concept complex_b = requires (T t)
{
	{t.real()} -> _std::same_as<value_t<T>>;
	{t.real()} -> _std::same_as<value_t<T>>;
};
template <typename    T > concept boolean_b = _std::is_same_v<bool, _std::remove_reference_t<T>>;
template <typename ...Ts> concept complex_q = unfalse_p<complex_b<Ts>...>;
template <typename ...Ts> concept boolean_q = unfalse_p<boolean_b<Ts>...>;

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
