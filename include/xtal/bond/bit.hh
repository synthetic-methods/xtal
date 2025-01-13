#pragma once
#include "./any.hh"

#include "./operate.hh"
#include "./couple.hh"



XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//\todo\
Move to `xtal::process::math::boole`?


////////////////////////////////////////////////////////////////////////////////

template <class V>
XTAL_DEF_(short)
XTAL_SET bit_depth_f()
noexcept -> auto
{
	return static_cast<int>(sizeof(V) << 3);
}
XTAL_DEF_(short)
XTAL_SET bit_depth_f(variable_q auto v)
noexcept -> int
{
	return static_cast<int>(sizeof(v) << 3);
}
XTAL_DEF_(short)
XTAL_SET bit_depth_f(constant_q auto w)
noexcept -> int
{
	return constant_t<bit_depth_f(w())>{};
}


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(short)
XTAL_SET bit_sign_f(integral_variable_q auto o)
noexcept -> int
{
	return static_cast<int>(ordinal_f(o) >> bit_depth_f<decltype(o)>() - one);
}
XTAL_DEF_(short)
XTAL_SET bit_sign_f(real_variable_q auto o)
noexcept -> int
{
	using _op = bond::operate<decltype(o)>;
	return bit_sign_f(_xtd::bit_cast<typename _op::delta_type>(o));
}
XTAL_DEF_(short)
XTAL_SET bit_sign_f(constant_q auto w)
noexcept -> auto
{
	return constant_t<bit_sign_f(w())>{};
}


///\returns the number of bits set in `u`. \

XTAL_DEF_(short)
XTAL_SET bit_count_f(cardinal_variable_q auto u)
noexcept -> int
{
	return _std::popcount(u);
}
XTAL_DEF_(short)
XTAL_SET bit_count_f(ordinal_variable_q auto v)
noexcept -> int
{
	int  x = bit_sign_f(v);
	v ^= x;
	v -= x;
	int  y = bit_count_f(cardinal_f(v));
	y ^= x;
	y -= x;
	return y;
}

XTAL_DEF_(short)
XTAL_SET bit_count_f(constant_q auto w)
noexcept -> auto
{
	return constant_t<bit_count_f(w())>{};
}


template <int N_zero=-1> requires (N_zero == -1)
XTAL_DEF_(short)
XTAL_SET bit_floor_f(cardinal_variable_q auto u)
noexcept -> int
{
	/*/
	U const  z =      one == u;
	U const _z = bond::operate<decltype(u)>::unit.depth&-z;
	return _std::bit_width(u) - (one << _z) + z;// 0 -> -1023
	/*/
	return _std::bit_width(u) - one;// 0 -> -1
	/***/
}
template <int N_zero=-1> requires (N_zero != -1)
XTAL_DEF_(short)
XTAL_SET bit_floor_f(cardinal_variable_q auto u)
noexcept -> int
{
	int constexpr N = N_zero + one;
	int y = bit_floor_f(u); y += (N&bit_sign_f(y));
	return y;
}
template <int N_zero=-1>
XTAL_DEF_(short)
XTAL_SET bit_floor_f(ordinal_variable_q auto v)
noexcept -> int
{
	int  x = bit_sign_f(v);
	v ^= x;
	v -= x;
	int  y = bit_floor_f<N_zero>(cardinal_f(v));
	y ^= x;
	y -= x;
	return y;
}

template <int N_zero>
XTAL_DEF_(short)
XTAL_SET bit_floor_f(real_variable_q auto &&x)
noexcept -> int
{
	using X_op =  bond::operate<decltype(x)>;
	using U = typename X_op::sigma_type;
	using V = typename X_op::delta_type;

	XTAL_LET Z = -X_op::unit.mark;
	XTAL_LET N = N_zero - Z << X_op::unit.shift;

	auto n = _xtd::bit_cast<U>(XTAL_REF_(x));
	n &= ~X_op::sign.mask;
	n -=  X_op::unit.mask;
	n +=  N&bit_sign_f(n);
	return   _xtd::bit_cast<V>(n) >> X_op::unit.shift;
}
template <int N_zero>
XTAL_DEF_(short)
XTAL_SET bit_floor_f(complex_variable_q auto &&x)
noexcept -> int
{
	return bit_floor_f<N_zero>(norm(XTAL_REF_(x))) >> one;
}
XTAL_DEF_(short)
XTAL_SET bit_floor_f(auto &&x)
noexcept -> int
requires real_variable_q<absolve_u<decltype(x)>>
{
	XTAL_LET N_zero = -static_cast<int>(bond::operate<decltype(x)>::unit.mark);
	return bit_floor_f<N_zero>(XTAL_REF_(x));
}

template <int N_zero=-1>
XTAL_DEF_(short)
XTAL_SET bit_floor_f(constant_q auto w)
noexcept -> auto
{
	return constant_t<bit_floor_f<N_zero>(w())>{};
}


template <int N_zero=-1> requires (N_zero == -1)
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(cardinal_variable_q auto u)
noexcept -> int
{
	int const z = u == zero;
	//\
	return _std::bit_width(u - !z) - (z << unit.depth) + z;// 0 -> -1023
	return _std::bit_width(u - !z)                     - z;// 0 -> -1
}
template <int N_zero=-1> requires (N_zero != -1)
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(cardinal_variable_q auto u)
noexcept -> int
{
	int constexpr N = N_zero + one;
	int y = bit_ceiling_f(u); y += N&bit_sign_f(y);
	return y;
}
template <int N_zero=-1>
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(ordinal_variable_q auto v)
noexcept -> int
{
	int  x = bit_sign_f(v);
	v ^= x;
	v -= x;
	int  y = bit_ceiling_f<N_zero>(cardinal_f(v));
	y ^= x;
	y -= x;
	return y;
}

template <int N_zero=+1>
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(real_variable_q auto &&x)
noexcept -> int
{
	using X_op = bond::operate<decltype(x)>;
	return bit_floor_f<N_zero>(X_op::diplo_1*X_op::dnsilon_1*XTAL_REF_(x));
}
template <int N_zero=+1>
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(complex_variable_q auto &&x)
noexcept -> int
{
	return bit_ceiling_f<N_zero>(norm(XTAL_REF_(x))) >> 1;
}

template <int N_zero=-1>
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(constant_q auto w)
noexcept -> auto
{
	return constant_t<bit_ceiling_f<N_zero>(w())>{};
}


///\returns the bitwise-reversal of `u`, \
restricted to `N_subdepth` when `0 < N_subdepth < sizeof(u) << 3U`. \

///\note Requires `log2(sizeof(u) << 3U)` iterations. \

XTAL_DEF_(long)
XTAL_SET bit_reverse_f(cardinal_variable_q auto u, int const &n_subdepth)
noexcept -> auto
{
	using    U =      decltype(u);
	XTAL_LET N = bit_depth_f<U>();

	#pragma inline
	for (U m = -1, i = N; i >>= 1;) {
		m ^= m<<i;
		u = (u&m)<<i | (u&~m)>>i;
	}
	u >>= N - n_subdepth; assert(0 < n_subdepth and n_subdepth <= N);
	return u;
}
XTAL_DEF_(long)
XTAL_SET bit_reverse_f(ordinal_variable_q auto v, int const &n_subdepth)
noexcept -> auto
{
	decltype(v) x = bit_sign_f(v);
	v ^= x;
	v -= x;
	v  = ordinal_f(bit_reverse_f(cardinal_f(v), n_subdepth));
	v ^= x;
	v -= x;
	return v;
}

XTAL_DEF_(short)
XTAL_SET bit_reverse_f(constant_q auto w, int const &n_subdepth)
noexcept -> auto
{
	return constant_t<bit_reverse_f(w(), n_subdepth)>{};
}
template <int N_subdepth>
XTAL_DEF_(short)
XTAL_SET bit_reverse_f(auto &&x)
noexcept -> auto
{
	XTAL_LET N_depth = bond::operate<decltype(x)>::full.depth;
	//\
	int constexpr n_subdepth = below_m<N_depth, (unsigned) N_subdepth>;
	int constexpr n_subdepth = 0 < N_subdepth? N_subdepth: N_depth;
	return bit_reverse_f(XTAL_REF_(x), n_subdepth);
}

///////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(short)
XTAL_SET bit_representation_f(real_variable_q auto x)
noexcept -> auto
{
	using X_op =  bond::operate<decltype(x)>;
	using U = typename X_op::sigma_type;
	using V = typename X_op::delta_type;

	U constexpr N = X_op::unit.mark + X_op::fraction.depth;
	U constexpr M =            one << X_op::fraction.depth;
	
	auto const o = _xtd::bit_cast<U>(x);
	V const z = static_cast<V>(o) >> X_op::positive.depth;
	V const n = N - (o << X_op::sign.depth >> X_op::sign.depth + X_op::exponent.shift);
	V       m = M | (o&X_op::fraction.mask);
	m  ^= z;
	m  -= z;
	return couple_t<V[2]>{m, n};
}
XTAL_DEF_(short)
XTAL_SET bit_presentation_f(couple_q auto const &mn)
noexcept -> auto
{
	auto const &[m, n] = mn;
	using MN_op = bond::operate<decltype(m), decltype(n)>;
	return static_cast<typename MN_op::alpha_type>(m)*MN_op::haplo_f(n);
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
