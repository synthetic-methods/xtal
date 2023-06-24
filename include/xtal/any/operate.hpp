#pragma once
#include "./any.hpp"
#include "./utilize.hpp"





XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename T>
concept comparators_p = _std::integral<T> or _std::floating_point<T> or requires (T t, T u)
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
concept bit_operators_p = _std::integral<T> or requires (T t, T u)
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
concept field_operators_p = _std::floating_point<T> or not bit_operators_p<T, N_arity> and requires (T t, T u)
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

template <typename ...Ts > concept   bit_operators_q = every_q<  bit_operators_p<based_t<Ts>>...>;
template <typename ...Ts > concept field_operators_q = every_q<field_operators_p<based_t<Ts>>...>;

static_assert(field_operators_q<_std::complex<float>>);

template <typename T>
concept complex_p = requires (T t)
{
	{t.real()} -> _std::same_as<value_t<T>>;
	{t.imag()} -> _std::same_as<value_t<T>>;
} and field_operators_p<T, 2>;

template <typename ...Ts>
concept complex_q = every_q<complex_p<Ts>...>;

template <complex_q T>
XTAL_FZ2 simple_f(T &t)
XTAL_0EX
{
	return reinterpret_cast<value_t<T>(&)[2]>(t);
}
template <complex_q T>
XTAL_FZ2 re_f(T &t)
XTAL_0EX
{
	return simple_f(t)[0];
}
template <complex_q T>
XTAL_FZ2 im_f(T &t)
XTAL_0EX
{
	return simple_f(t)[1];
}


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

template <sigma_q U>
XTAL_FZ2 bit_count_y(U u)
XTAL_0EX
{
	U n = 0;
	while (u)
	{	n  += 1&u;
		u >>= 1;
	}
	return n;
}
template <delta_q V>
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


template <sigma_q U>
XTAL_FZ2_(U) bit_floor_y(U u)
XTAL_0EX
{
	U n = 0;
	while (u >>= 1)
	{	++n;
	}
	return n;
}
template <delta_q V>
XTAL_FZ2_(V) bit_floor_y(V v)
XTAL_0EX
{
	using U = _std::make_unsigned_t<V>;
	V const v_sgn = (0 < v) - (v < 0);
	V const v_abs = v*v_sgn;
	V const y_abs = bit_floor_y((U) v_abs);
	return  y_abs*v_sgn;
}
template <size_t N, size_t M=0>
concept bit_floor_q = N == 1 << (bit_floor_y(N >> M) + M);


template <sigma_q U>
XTAL_FZ2_(U) bit_ceiling_y(U const &u)
XTAL_0EX
{
	U n = bit_floor_y<U>(u);
	n += 1 << n != u;
	return n;
}
template <delta_q V>
XTAL_FZ2_(V) bit_ceiling_y(V v)
XTAL_0EX
{
	using U = _std::make_unsigned_t<V>;
	U const u = bit_ceiling_y<U>(v);
	return 0 < v? V(u): -V(u);
}
template <size_t N, size_t M=0>
concept bit_ceiling_q = N == 1 << (bit_ceiling_y(N >> M) + M);


///\returns the bitwise-reversal of `that`, \
	restricted to `N_subdepth` when `0 < N_subdepth < sizeof(that) << 3`. \

///\note Requires `log2(sizeof(that) << 3)` iterations. \

template <iota_q T>
XTAL_FZ2 bit_reverse_y(T that, T const &subdepth)
XTAL_0EX
{
	using U = _std::make_unsigned_t<T>;
	U constexpr depth = bit_depth_v<U>;
	U u = that;
	for (U m = -1, i = depth; i >>= 1;)
	{	m ^= m<<i;
		u = (u&m)<<i | (u&~m)>>i;
	}
	u >>= depth - subdepth; assert(0 < subdepth and subdepth <= depth);
	return u;
}
template <size_t N_subdepth=0>
XTAL_FZ2 bit_reverse_y(XTAL_DEF_(iota_q) that)
XTAL_0EX
{
	using T = XTAL_TYP_(that);
	using U = _std::make_unsigned_t<T>;
	U constexpr depth = bit_depth_v<U>;
	U constexpr subdepth = 0 < N_subdepth? N_subdepth: depth;
	return bit_reverse_y(XTAL_REF_(that), subdepth);
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
