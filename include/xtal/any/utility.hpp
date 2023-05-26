#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

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

template <typename    T  > struct     rebased            : _std::false_type {using type = T;};
template <typename    T  > struct     rebased<T const &&>: _std:: true_type {using type = T;};
template <typename    T  > struct     rebased<T       &&>: _std:: true_type {using type = T;};
template <typename    T  > using      rebased_t =    type_t<rebased<T>>;
template <typename    T  > concept    rebased_b =   value_v<rebased<T>>;
template <typename ...Ts > concept    rebased_q = unfalse_p<rebased_b<Ts>...>;

template <typename    T  > struct     debased           : _std::false_type {using type = based_t<T>;};
template <typename    T  > struct     debased<T const &>: _std::false_type {using type = based_t<T>;};
template <unbased_b   T  > struct     debased<T       &>: _std:: true_type {using type =         T*;};
template <typename    T  > using      debased_t =    type_t<debased<T>>;
template <typename    T  > concept    debased_b =   value_v<debased<T>>;
template <typename ...Ts > concept    debased_q = unfalse_p<debased_b<Ts>...>;

///////////////////////////////////////////////////////////////////////////////

template <typename ...Ys>
struct identical
:	_std::false_type
{};

template <typename T, typename ...Ys>
struct identical<T, Ys...>
:	_std::disjunction<_std::is_same<T, Ys>...>
{};
template <typename ...Ys>
struct isomeric
:	identical<based_t<Ys>...>
{};
template <typename ...Ys>
struct isomorphic
:	isomeric<Ys...>
{};


XTAL_FZ2_(bool) id_y(XTAL_DEF s, XTAL_DEF t)
XTAL_0EX
{
	return _std::addressof(XTAL_REF_(s)) == _std::addressof(XTAL_REF_(t));
}
template <typename ...Ys>             concept  id_q = identical <Ys...>::value;
template <typename ...Ys>             concept  is_q = isomeric  <Ys...>::value;
template <typename ...Ys>             concept iso_q = isomorphic<Ys...>::value;


template <typename T, typename    Y > concept  to_b = requires (T t) {based_t<Y> (t);};//TODO: Remove `based_t`?
template <typename T, typename ...Ys> concept  to_q = unfalse_p<to_b<T, Ys>...>;

template <typename T, typename    Y > concept  of_b = _std::is_base_of_v<based_t<Y>, based_t<T>>;
template <typename T, typename ...Ys> concept  of_q = unfalse_p<of_b<T, Ys>...>;


///////////////////////////////////////////////////////////////////////////////

template <template <typename...> typename T_>
struct tag_t {};

template <typename T, template <typename...> typename T_>
concept tag_q = of_q<T, tag_t<T_>>;


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

template <typename T>
concept complex_b = requires (T t)
{
	{t.real()} -> _std::same_as<value_t<T>>;
	{t.real()} -> _std::same_as<value_t<T>>;
};
template <typename ...Ts>
concept complex_q = unfalse_p<complex_b<Ts>...>;

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
