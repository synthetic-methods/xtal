#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

using null_t = XTAL_STD_NULL;
using size_t = XTAL_STD_SIZE;

template <auto     ...Ns > concept       true_p =     (bool(Ns)  or...);///< Any `Ns... == 1`.
template <auto     ...Ns > concept      false_p = not (bool(Ns) and...);///< Any `Ns... == 0`.
template <auto     ...Ns > concept     untrue_p = not (bool(Ns)  or...);///< All `Ns... == 0`.
template <auto     ...Ns > concept    unfalse_p =     (bool(Ns) and...);///< All `Ns... == 1`.

template <typename    T  > using         type_t = typename _std::remove_reference_t<T>::type;
template <typename    T  > using        value_t = typename _std::remove_reference_t<T>::value_type;
template <typename    T  > concept      value_b = requires {typename value_t<T>;};
template <typename ...Ts > concept      value_q = unfalse_p<value_b<Ts>...>;
template <typename    T  > XTAL_LET     value_v = _std::remove_reference_t<T>::value;

template <typename    X  > using      bracket_t = _std::initializer_list<X>;
template <typename    T  > concept    pointer_b = _std::is_pointer_v<_std::decay_t<T>>;
template <typename ...Ts > concept    pointer_q = unfalse_p<pointer_b<Ts>...>;

template <auto        N  > using     constant   = _std::integral_constant<XTAL_TYP_(N), N>;
template <typename    T  > concept   constant_b = _std::is_base_of_v<_std::integral_constant<value_t<T>, value_v<T>>, T>;
template <typename ...Ts > concept   constant_q = unfalse_p<constant_b<Ts>...>;

template <typename ...Ts > struct   construct   : _std::common_type<Ts...> {};
template <               > struct   construct< > {using type = _std::monostate     ;};
template <typename    T  > struct   construct<T> {using type = T                   ;};
template <typename ...Ts > using    construct_t = type_t<construct<Ts...>>;
template <typename ...Ts > XTAL_LET construct_f = [] (XTAL_DEF ...oo) XTAL_0FN_(construct_t<Ts...> (XTAL_REF_(oo)...));


template <typename    T  > using        based_t = _std::remove_cvref_t<T>;
template <typename    T  > concept      based_b = _std::is_trivially_copy_constructible_v<based_t<T>>;
template <typename ...Ts > concept      based_q = unfalse_p<based_b<Ts>...>;

template <typename    T  > concept    unbased_b = not based_b<T>;
template <typename ...Ts > concept    unbased_q = unfalse_p<unbased_b<Ts>...>;

template <typename    T  > struct     rebased            : _std:: true_type {using type = based_t<T>;};
template <unbased_b   T  > struct     rebased<T        &>: _std::false_type {using type =         T&;};
template <  based_b   T  > struct     rebased<T const  &>: _std:: true_type {using type =         T ;};
template <typename    T  > struct     rebased<T       &&>: _std:: true_type {using type =         T ;};
template <typename    T  > struct     rebased<T const &&>: _std:: true_type {using type =         T ;};
template <typename    T  > using      rebased_t =    type_t<rebased<T>>;
template <typename    T  > concept    rebased_b =   value_v<rebased<T>>;
template <typename ...Ts > concept    rebased_q = unfalse_p<rebased_b<Ts>...>;

template <typename    T  > struct     debased            : _std::false_type {using type = based_t<T>;};
template <unbased_b   T  > struct     debased<T        &>: _std:: true_type {using type =         T*;};
template <  based_b   T  > struct     debased<T const  &>: _std::false_type {using type =         T ;};
template <typename    T  > struct     debased<T       &&>: _std::false_type {using type =         T ;};
template <typename    T  > struct     debased<T const &&>: _std::false_type {using type =         T ;};
template <typename    T  > using      debased_t =    type_t<debased<T>>;
template <typename    T  > concept    debased_b =   value_v<debased<T>>;
template <typename ...Ts > concept    debased_q = unfalse_p<debased_b<Ts>...>;

template <typename T, auto Z=0>
concept integer_q = requires
{
	requires (0 == Z) or _std::         integral<based_t<T>>;
	requires (0 <= Z) or _std::  signed_integral<based_t<T>>;
	requires (Z <= 0) or _std::unsigned_integral<based_t<T>>;
};
template <typename  T, auto Z> struct integer;
template <integer_q T> struct integer<T,  0> {using type = T;};
template <integer_q T> struct integer<T, +1> {using type = _std::make_unsigned_t<T>;};
template <integer_q T> struct integer<T, -1> {using type = _std::  make_signed_t<T>;};

template <typename T, auto Z=0>
using integer_t = type_t<integer<T, Z>>;


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
///////////////////////////////////////////////////////////////////////////////

template <template <typename...> typename T_>
struct tag_t {};

template <typename T, template <typename...> typename T_>
concept tag_q = of_q<T, tag_t<T_>>;


template <size_t ...Ns > using    seek_t  = _std::     index_sequence<Ns...>;
template <size_t    N  > XTAL_LET seek_v  = _std::make_index_sequence<N>{};
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

template <size_t I, bool ...Ns> struct   truth_seeker;
template <size_t I, bool ...Ns> struct   truth_seeker<I,  true, Ns...>: constant<I> {};
template <size_t I, bool ...Ns> struct   truth_seeker<I, false, Ns...>: truth_seeker<I + 1, Ns...> {};
template <          bool ...Ns> using    truth_index_t  = truth_seeker<0, Ns..., true>;
template <          bool ...Ns> XTAL_LET truth_index_v  = value_v<truth_index_t<Ns...>>;


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename T>
concept comparators_b = _std::integral<T> or _std::floating_point<T> or requires (T t, T u)
{
	{t == u} -> is_q<bool>;
	{t <= u} -> is_q<bool>;
	{t <  u} -> is_q<bool>;
	{t >= u} -> is_q<bool>;
	{t >  u} -> is_q<bool>;
};

///\
\returns `true` if type `T` supports bit-operations, `false` otherwise.

///\
The optional parameter `N_arity` determines whether \
binary/immutable (+1) or unary/mutable (-1) operations are supported, or both (0, the default).

template <typename T, size_t N_arity=0>
concept bit_operators_b = _std::integral<T> or requires (T t, T u)
{
	requires N_arity == 1 or
	requires
	{
		{t <<  u} -> is_q<T>;
		{t >>  u} -> is_q<T>;
		{t  %  u} -> is_q<T>;
		{t  &  u} -> is_q<T>;
		{t  ^  u} -> is_q<T>;
		{t  |  u} -> is_q<T>;
		{t  +  u} -> is_q<T>;
		{t  -  u} -> is_q<T>;
	};
	requires N_arity == 2 or
	requires
	{
		{t <<= u} -> is_q<T>;
		{t >>= u} -> is_q<T>;
		{t  %  u} -> is_q<T>;
		{t  &= u} -> is_q<T>;
		{t  ^= u} -> is_q<T>;
		{t  |= u} -> is_q<T>;
		{t  += u} -> is_q<T>;
		{t  -= u} -> is_q<T>;
	};
};

///\
\returns `true` if type `T` supports field-operations (without supporting bit-operations), `false` otherwise.

///\
The optional parameter `N_arity` determines whether \
binary/immutable (+1) or unary/mutable (-1) operations are supported, or both (0, the default).

template <typename T, size_t N_arity=0>
concept field_operators_b = _std::floating_point<T> or not bit_operators_b<T, N_arity> and requires (T t, T u)
{
	requires N_arity == 1 or
	requires
	{
		{t  *  u} -> is_q<T>;
		{t  /  u} -> is_q<T>;
		{t  +  u} -> is_q<T>;
		{t  -  u} -> is_q<T>;
	};
	requires N_arity == 2 or
	requires
	{
		{t  *= u} -> is_q<T>;
		{t  /= u} -> is_q<T>;
		{t  += u} -> is_q<T>;
		{t  -= u} -> is_q<T>;
	};
};

template <typename ...Ts > concept          bit_operators_q = unfalse_p<  bit_operators_b<based_t<Ts>>...>;
template <typename ...Ts > concept        field_operators_q = unfalse_p<field_operators_b<based_t<Ts>>...>;
template <typename ...Ts > concept bit_or_field_operators_q = bit_operators_q<Ts...> or field_operators_q<Ts...>;

static_assert(field_operators_q<_std::complex<float>>);

template <typename T>
concept complex_b = requires (T t)
{
	{t.real()} -> _std::same_as<value_t<T>>;
	{t.imag()} -> _std::same_as<value_t<T>>;
} and field_operators_b<T, 2>;

template <typename ...Ts>
concept complex_q = unfalse_p<complex_b<Ts>...>;


///////////////////////////////////////////////////////////////////////////////

template <typename T>
XTAL_LET byte_depth_v = sizeof(based_t<T>);

template <typename T>
XTAL_FZ2 byte_depth_y(T &&t)
XTAL_0EX
{
	return byte_depth_v<T>;
}

template <typename T>
XTAL_LET bit_depth_v = byte_depth_v<T> << 3;

template <typename T>
XTAL_FZ2 bit_depth_y(T &&t)
XTAL_0EX
{
	return bit_depth_v<T>;
}


///\\returns the number of bits set in `u`. \

template <integer_q<+1> U>
XTAL_FZ2 bit_count_y(U u)
XTAL_0EX
{
	U n = 0;
	while (u)
	{
		n  += 1&u;
		u >>= 1;
	}
	return n;
}
template <integer_q<-1> V>
XTAL_FZ2 bit_count_y(V const &v)
XTAL_0EX
{
	using U = _std::make_unsigned_t<V>;
	V const v_sgn = (0 < v) - (v < 0);
	V const v_abs = v*v_sgn;
	V const y_abs = bit_count_y((U) v_abs);
	return  y_abs*v_sgn;
}
template <auto N_value=0>
XTAL_LET bit_count_v = bit_count_y(N_value);
///< Value expression of `bit_count_y`. \

static_assert(bit_count_y(0b10110100) == 4);


template <integer_q<+1> U>
XTAL_FZ2_(U) bit_floor_y(U u)
XTAL_0EX
{
	U n = 0;
	while (u >>= 1)
	{
		++n;
	}
	return n;
}
template <integer_q<-1> V>
XTAL_FZ2_(V) bit_floor_y(V v)
XTAL_0EX
{
	using U = integer_t<V, +1>;
	V const v_sgn = (0 < v) - (v < 0);
	V const v_abs = v*v_sgn;
	V const y_abs = bit_floor_y((U) v_abs);
	return  y_abs*v_sgn;
}
template <size_t N, size_t M=0>
concept bit_floor_q = N == 1 << (bit_floor_y(N >> M) + M);


template <integer_q<+1> U>
XTAL_FZ2_(U) bit_ceiling_y(U const &u)
XTAL_0EX
{
	U n = bit_floor_y<U>(u);
	n += 1 << n != u;
	return n;
}
template <integer_q<-1> V>
XTAL_FZ2_(V) bit_ceiling_y(V v)
XTAL_0EX
{
	using U = integer_t<V, +1>;
	U const u = bit_ceiling_y<U>(v);
	return 0 < v? V(u): -V(u);
}
template <size_t N, size_t M=0>
concept bit_ceiling_q = N == 1 << (bit_ceiling_y(N >> M) + M);


///\returns the bitwise-reversal of `that`, \
	restricted to `N_subdepth` when `0 < N_subdepth < sizeof(that) << 3`. \

///\note Requires `log2(sizeof(that) << 3)` iterations. \

template <integer_q T>
XTAL_FZ2 bit_reverse_y(T that, T const &subdepth)
XTAL_0EX
{
	using U = integer_t<T, +1>;
	U constexpr depth = bit_depth_v<U>;
	U u = that;
	for (U m = -1, i = depth; i >>= 1;)
	{
		m ^= m<<i;
		u = (u&m)<<i | (u&~m)>>i;
	}
	u >>= depth - subdepth; assert(0 < subdepth and subdepth <= depth);
	return u;
}
template <size_t N_subdepth=0>
XTAL_FZ2 bit_reverse_y(XTAL_DEF_(integer_q) that)
XTAL_0EX
{
	using T = XTAL_TYP_(that);
	using U = integer_t<T, +1>;
	U constexpr depth = bit_depth_v<U>;
	U constexpr subdepth = 0 < N_subdepth? N_subdepth: depth;
	return bit_reverse_y(XTAL_REF_(that), subdepth);
}
template <size_t N_subdepth=0>
XTAL_LET  bit_reverse_x = [] (XTAL_DEF that)
XTAL_0FN_(bit_reverse_y<N_subdepth> (XTAL_REF_(that)));
///<\
Function expression of `bit_reverse_y`. \


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
