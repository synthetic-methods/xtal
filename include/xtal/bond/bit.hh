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

template <class ...Ts>	using   bit_iota_t = typename operate<Ts...>:: iota_type;
template <class ...Ts>	using  bit_delta_t = typename operate<Ts...>::delta_type;
template <class ...Ts>	using  bit_sigma_t = typename operate<Ts...>::sigma_type;
template <class ...Ts>	using  bit_alpha_t = typename operate<Ts...>::alpha_type;
template <class ...Ts>	using  bit_aphex_t = typename operate<Ts...>::aphex_type;


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(short)
XTAL_SET bit_depth_f(variable_q auto v)
noexcept -> auto
{
	return sizeof(v) << 3;
}

XTAL_DEF_(short)
XTAL_SET bit_depth_f(constant_q auto w)
noexcept -> auto
{
	return constant_t<bit_depth_f(w.value)>{};
}
template <int N_diff>
XTAL_DEF_(short)
XTAL_SET bit_depth_f(auto x)
noexcept -> auto
{
	return bit_depth_f(x) + N_diff;
}


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(short)
XTAL_SET bit_sign_f(cardinal_variable_q auto u)
noexcept -> auto
{
	using U = bit_sigma_t<decltype(u)>;
	using V = bit_delta_t<decltype(u)>;
	return _xtd::bit_cast<U>(_xtd::bit_cast<V>(u) >> bit_depth_f<-1>(u));
}
XTAL_DEF_(short)
XTAL_SET bit_sign_f(ordinal_variable_q auto v)
noexcept -> auto
{
	return v >> operate<decltype(v)>::positive.depth;
}

XTAL_DEF_(short)
XTAL_SET bit_sign_f(constant_q auto w)
noexcept -> auto
{
	return constant_t<bit_sign_f(w.value)>{};
}


///\returns the number of bits set in `u`. \

XTAL_DEF_(short)
XTAL_SET bit_count_f(cardinal_variable_q auto u)
noexcept -> auto
{
	return _std::popcount(u);
}
XTAL_DEF_(short)
XTAL_SET bit_count_f(ordinal_variable_q auto v)
noexcept -> auto
{
	using U = bit_sigma_t<decltype(v)>;
	using V = bit_delta_t<decltype(v)>;
	auto  x = bit_sign_f(v);
	v ^= x;
	v -= x;
	v  = _xtd::bit_cast<V>(bit_count_f(_xtd::bit_cast<U>(v)));
	v ^= x;
	v -= x;
	return v;
}

XTAL_DEF_(short)
XTAL_SET bit_count_f(constant_q auto w)
noexcept -> auto
{
	return constant_t<bit_count_f(w.value)>{};
}


template <int N_zero=-1> requires (N_zero == -1)
XTAL_DEF_(short)
XTAL_SET bit_floor_f(cardinal_variable_q auto u)
noexcept -> bit_delta_t<decltype(u)>
{
	/*/
	U const  z =      one == u;
	U const _z = operate<decltype(u)>::unit.depth&-z;
	return _std::bit_width(u) - (one << _z) + z;// 0 -> -1023
	/*/
	return _std::bit_width(u) - one;// 0 -> -1
	/***/
}
template <int N_zero=-1> requires (N_zero != -1)
XTAL_DEF_(short)
XTAL_SET bit_floor_f(cardinal_variable_q auto u)
noexcept -> bit_delta_t<decltype(u)>
{
	XTAL_LET Z =         -1;
	XTAL_LET N = N_zero - Z;
	u  =  bit_floor_f(u);
	u += N&bit_sign_f(u);
	return u;
}
template <int N_zero=-1>
XTAL_DEF_(short)
XTAL_SET bit_floor_f(ordinal_variable_q auto v)
noexcept -> bit_delta_t<decltype(v)>
{
	using U = bit_sigma_t<decltype(v)>;
	using V = bit_delta_t<decltype(v)>;
	auto  x = bit_sign_f(v);
	v ^= x;
	v -= x;
	v  = _xtd::bit_cast<V>(bit_floor_f<N_zero>(_xtd::bit_cast<U>(v)));
	v ^= x;
	v -= x;
	return v;
}

template <int N_zero>
XTAL_DEF_(short)
XTAL_SET bit_floor_f(real_variable_q auto &&x)
noexcept -> bit_delta_t<decltype(x)>
{
	using X_op =  operate<decltype(x)>;
	using U = bit_sigma_t<decltype(x)>;
	using V = bit_delta_t<decltype(x)>;

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
noexcept -> bit_delta_t<decltype(x)>
{
	return bit_floor_f<N_zero>(norm(XTAL_REF_(x))) >> one;
}
XTAL_DEF_(short)
XTAL_SET bit_floor_f(auto &&x)
noexcept -> bit_delta_t<decltype(x)>
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
	return constant_t<bit_floor_f<N_zero>(w.value)>{};
}


template <int N_zero=-1> requires (N_zero == -1)
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(cardinal_variable_q auto u)
noexcept -> bit_delta_t<decltype(u)>
{
	auto const z = u == zero;
	//\
	return _std::bit_width(u - !z) - (z << unit.depth) + z;// 0 -> -1023
	return _std::bit_width(u - !z)                     - z;// 0 -> -1
}
template <int N_zero=-1> requires (N_zero != -1)
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(cardinal_variable_q auto u)
noexcept -> bit_delta_t<decltype(u)>
{
	XTAL_LET Z =         -1;
	XTAL_LET N = N_zero - Z;
	u  =   bit_ceiling_f(u);
	u +=    N&bit_sign_f(u);
	return u;
}
template <int N_zero=-1>
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(ordinal_variable_q auto v)
noexcept -> bit_delta_t<decltype(v)>
{
	using U = bit_sigma_t<decltype(v)>;
	using V = bit_delta_t<decltype(v)>;
	V x = bit_sign_f(v);
	v ^= x;
	v -= x;
	v  = _xtd::bit_cast<V>(bit_ceiling_f(_xtd::bit_cast<U>(v)));
	v ^= x;
	v -= x;
	return v;
}

template <int N_zero=+1>
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(real_variable_q auto &&x)
noexcept -> bit_delta_t<decltype(x)>
{
	using X_op = bond::operate<decltype(x)>;
	return bit_floor_f<N_zero>(XTAL_REF_(x)*X_op::diplo_1*X_op::dnsilon_1);
}
template <int N_zero=+1>
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(complex_variable_q auto &&x)
noexcept -> bit_delta_t<decltype(x)>
{
	return bit_ceiling_f<N_zero>(norm(XTAL_REF_(x))) >> 1;
}

template <int N_zero=-1>
XTAL_DEF_(short)
XTAL_SET bit_ceiling_f(constant_q auto w)
noexcept -> auto
{
	return constant_t<bit_ceiling_f<N_zero>(w.value)>{};
}


///\returns the bitwise-reversal of `u`, \
restricted to `N_subdepth` when `0 < N_subdepth < sizeof(u) << 3U`. \

///\note Requires `log2(sizeof(u) << 3U)` iterations. \

XTAL_DEF_(long)
XTAL_SET bit_reverse_f(cardinal_variable_q auto u, int const &n_subdepth)
noexcept -> auto
{
	using U = XTAL_ALL_(u);
	using U_op = bond::operate<U>;

	#pragma inline
	for (U m = -1, i = U_op::full.depth; i >>= 1;) {
		m ^= m<<i;
		u = (u&m)<<i | (u&~m)>>i;
	}
	u >>= U_op::full.depth - n_subdepth; assert(0 < n_subdepth and n_subdepth <= U_op::full.depth);
	return u;
}
XTAL_DEF_(long)
XTAL_SET bit_reverse_f(ordinal_variable_q auto v, int const &n_subdepth)
noexcept -> auto
{
	using U = bit_sigma_t<decltype(v)>;
	using V = bit_delta_t<decltype(v)>;
	V x = bit_sign_f(v);
	v ^= x;
	v -= x;
	v  = _xtd::bit_cast<V>(bit_reverse_f(_xtd::bit_cast<U>(v), n_subdepth));
	v ^= x;
	v -= x;
	return v;
}

XTAL_DEF_(short)
XTAL_SET bit_reverse_f(constant_q auto w, int const &n_subdepth)
noexcept -> auto
{
	return constant_t<bit_reverse_f(w.value, n_subdepth)>{};
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
noexcept -> couple_t<bit_delta_t<decltype(x)>[2]>
{
	using X_op =  operate<decltype(x)>;
	using U = bit_sigma_t<decltype(x)>;
	using V = bit_delta_t<decltype(x)>;

	U constexpr N = X_op::unit.mark + X_op::fraction.depth;
	U constexpr M =            one << X_op::fraction.depth;
	
	auto const o = _xtd::bit_cast<U>(x);
	V const z = static_cast<V>(o) >> X_op::positive.depth;
	V const n = N - (o << X_op::sign.depth >> X_op::sign.depth + X_op::exponent.shift);
	V       m = M | (o&X_op::fraction.mask);
	m  ^= z;
	m  -= z;
	return {m, n};
}
XTAL_DEF_(short)
XTAL_SET bit_presentation_f(couple_q auto const &mn)
noexcept -> auto
{
	auto const &[m, n] = mn;
	using MN_op = operate<decltype(m), decltype(n)>;
	return static_cast<typename MN_op::alpha_type>(m)*MN_op::haplo_f(n);
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
