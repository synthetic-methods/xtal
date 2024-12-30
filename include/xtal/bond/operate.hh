#pragma once
#include "./any.hh"
#include "./seek.hh"
#include "./couple.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////
///\
The translation-tables for the supplied `N_size` \
(which should be representative of the desired `sizeof`): \
\
-	`alpha_type` represents floating-point real numbers. \
-	`sigma_type` represents full-N_width `unsigned int`s like `std::size`. \
-	`delta_type` represents full-N_width   `signed int`s used for binary and integer arithmetic. \
-	`iota_type`  represents half-N_width   `signed int`s required for `ranges::difference_type`. \
\
The constants labelled `quake_*` are provided for `Q_rsqrt` (in lieu of `constexpr`). \

template <size_type N_size>
struct recognize : recognize<(N_size >> 1U)>
{
	using _zed = constant_t<false>;

};
template <>
struct recognize<(1U<<0U)>
{
	using       _zed =        constant_t<true>;
//	using  iota_type =           _std::int4_t;
	using delta_type =    signed XTAL_STD_(int,   0);
	using sigma_type =  unsigned XTAL_STD_(int,   0);
//	using alpha_type =           XTAL_STD_(float, 0);
//	using aphex_type = _std::complex<alpha_type>;

	XTAL_SET_(sigma_type) N_exponent = 3;
	XTAL_SET_(sigma_type) N_fraction = 4;

};
template <>
struct recognize<(1U<<1U)>
{
	using       _zed =        constant_t<true>;
	using  iota_type =    signed XTAL_STD_(int,   0);
	using delta_type =    signed XTAL_STD_(int,   1);
	using sigma_type =  unsigned XTAL_STD_(int,   1);
//	using alpha_type =           XTAL_STD_(float, 1);
//	using aphex_type = _std::complex<alpha_type>;

	XTAL_SET_(sigma_type) N_exponent =  5;
	XTAL_SET_(sigma_type) N_fraction = 10;

};
template <>
struct recognize<(1U<<2U)>
{
	using       _zed =        constant_t<true>;
	using  iota_type =    signed XTAL_STD_(int,   1);
	using delta_type =    signed XTAL_STD_(int,   2);
	using sigma_type =  unsigned XTAL_STD_(int,   2);
	using alpha_type =           XTAL_STD_(float, 2);
	using aphex_type = _std::complex<alpha_type>;

	XTAL_SET_(sigma_type) N_exponent =  8;
	XTAL_SET_(sigma_type) N_fraction = 23;

#ifdef FP_FAST_FMAF
	XTAL_SET_(sigma_type) N_fused = 0b1;
#else
	XTAL_SET_(sigma_type) N_fused = 0b0;
#endif

	using mt19937_t = _std::mersenne_twister_engine<sigma_type, 32, 624, 397, 31
	,	literal_f<sigma_type>(0x9908B0DF), 11
	,	literal_f<sigma_type>(0xFFFFFFFF),  7
	,	literal_f<sigma_type>(0x9D2C5680), 15
	,	literal_f<sigma_type>(0xEFC60000), 18
	,	literal_f<sigma_type>(0x6C078965)
	>;

	template <int _, int N_pow> struct   root;
	template <int _           > struct   root<_, -1> : constant_t<literal_f<sigma_type>(0x7EEEEEEE)> {};
	template <int _           > struct   root<_, -2> : constant_t<literal_f<sigma_type>(0x5F375A86)> {};

	template <int N_pow>
	XTAL_SET_(sigma_type) root_n = root<0, N_pow>::value;

	template <int N_pow=-1>
	XTAL_DEF_(short)
	XTAL_SET root_e(alpha_type const &w)
	noexcept -> alpha_type
	{
		static_assert(in_q<N_pow, -1, -2>);
		XTAL_IF0
#if XTAL_SYS_(Neon)
		XTAL_0IF_(consteval)
#endif
		{
			delta_type const v = _xtd::bit_cast<delta_type>(w) >> size_1;
			sigma_type const u = root_n<N_pow> - v;
			return _xtd::bit_cast<alpha_type>(u);
		}
#if XTAL_SYS_(Neon)
		XTAL_0IF_(else) {
			XTAL_IF0
			XTAL_0IF (N_pow == -1) {return  vrecpes_f32(w);}
			XTAL_0IF (N_pow == -2) {return vrsqrtes_f32(w);}
		}
#endif
	}
	template <int N_pow=-1>
	XTAL_DEF_(short)
	XTAL_SET root_e(alpha_type const &w, alpha_type const &n)
	noexcept -> alpha_type
	{
		static_assert(in_q<N_pow, -1, -2>);
		XTAL_IF0
#if XTAL_SYS_(Neon)
		XTAL_0IF_(consteval)
#endif
		{
			auto constexpr a0 = alpha_type{N_pow - 1}/alpha_type{N_pow};
			auto constexpr a1 = alpha_type{        1}/alpha_type{N_pow};
			XTAL_IF0
			XTAL_0IF (N_pow == -1) {return _xtd::accumulator(a0, a1*w, n)*w;}
			XTAL_0IF (N_pow == -2) {return _xtd::accumulator(a0, a1*w, n*n);}
		}
#if XTAL_SYS_(Neon)
		XTAL_0IF_(else) {
			XTAL_IF0
			XTAL_0IF (N_pow == -1) {return  vrecpss_f32(w,   n);}
			XTAL_0IF (N_pow == -2) {return vrsqrtss_f32(w, n*n);}
		}
#endif
	}

};
template <>
struct recognize<(1U<<3U)>
{
	using   _zed =           constant_t< true>;
	using  iota_type =    signed XTAL_STD_(int,   2);
	using delta_type =    signed XTAL_STD_(int,   3);
	using sigma_type =  unsigned XTAL_STD_(int,   3);
	using alpha_type =           XTAL_STD_(float, 3);
	using aphex_type = _std::complex<alpha_type>;

	XTAL_SET_(sigma_type) N_exponent = 11;
	XTAL_SET_(sigma_type) N_fraction = 52;

#ifdef FP_FAST_FMA
	XTAL_SET_(sigma_type) N_fused = 0b1;
#else
	XTAL_SET_(sigma_type) N_fused = 0b0;
#endif

	using mt19937_t = _std::mersenne_twister_engine<sigma_type, 64, 312, 156, 31
	,	literal_f<sigma_type>(0xB5026F5A, 0xA96619E9), 29
	,	literal_f<sigma_type>(0x55555555, 0x55555555), 17
	,	literal_f<sigma_type>(0x71D67FFF, 0xEDA60000), 37
	,	literal_f<sigma_type>(0xFFF7EEE0, 0x00000000), 43
	,	literal_f<sigma_type>(0x5851F42D, 0x4C958000)
	>;

	template <int _, int N_pow> struct   root;
	template <int _           > struct   root<_, -1> : constant_t<literal_f<sigma_type>(0x7EEEEEEE, 0xEEEEEEEE)> {};
	template <int _           > struct   root<_, -2> : constant_t<literal_f<sigma_type>(0x5FE6EB50, 0xC7B537A9)> {};
	
	template <int N_pow>
	XTAL_SET_(sigma_type) root_n = root<0, N_pow>::value;

	template <int N_pow=-1>
	XTAL_DEF_(short)
	XTAL_SET root_e(alpha_type const &w)
	noexcept -> alpha_type
	{
		static_assert(in_q<N_pow, -1, -2>);
		XTAL_IF0
#if XTAL_SYS_(Neon)
		XTAL_0IF_(consteval)
#endif
		{
			delta_type const v = _xtd::bit_cast<delta_type>(w) >> size_1;
			sigma_type const u = root_n<N_pow> - v;
			return _xtd::bit_cast<alpha_type>(u);
		}
#if XTAL_SYS_(Neon)
		XTAL_0IF_(else) {
			XTAL_IF0
			XTAL_0IF (N_pow == -1) {return  vrecped_f64(w);}
			XTAL_0IF (N_pow == -2) {return vrsqrted_f64(w);}
		}
#endif
	}
	template <int N_pow=-1>
	XTAL_DEF_(short)
	XTAL_SET root_e(alpha_type const &w, alpha_type const &n)
	noexcept -> alpha_type
	{
		static_assert(in_q<N_pow, -1, -2>);
		XTAL_IF0
#if XTAL_SYS_(Neon)
		XTAL_0IF_(consteval)
#endif
		{
			auto constexpr a0 = alpha_type{N_pow - 1}/alpha_type{N_pow};
			auto constexpr a1 = alpha_type{        1}/alpha_type{N_pow};
			XTAL_IF0
			XTAL_0IF (N_pow == -1) {return _xtd::accumulator(a0, a1*w, n)*w;}
			XTAL_0IF (N_pow == -2) {return _xtd::accumulator(a0, a1*w, n*n);}
		}
#if XTAL_SYS_(Neon)
		XTAL_0IF_(else) {
			XTAL_IF0
			XTAL_0IF (N_pow == -1) {return  vrecpsd_f64(w,   n);}
			XTAL_0IF (N_pow == -2) {return vrsqrtsd_f64(w, n*n);}
		}
#endif
	}

};

template <size_type N_size>
concept recognized_q = recognize<N_size>::_zed::value;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <size_type N_size>
struct rationalize : rationalize<(N_size >> 1U)>
{
	using _zed = constant_t<false>;

};
template <size_type N_size> requires recognized_q<N_size>
struct rationalize<N_size> : recognize<N_size>
{
private:
	using S_ = recognize<N_size>;

public:
//	using typename S_:: iota_type;
	using typename S_::delta_type;
	using typename S_::sigma_type;

//	XTAL_SET_( iota_type)  iota_0{0};
//	XTAL_SET_( iota_type)  iota_1{1};
//	XTAL_SET_( iota_type)  iota_2{2};

	XTAL_SET_(delta_type) delta_0{0};
	XTAL_SET_(delta_type) delta_1{1};
	XTAL_SET_(delta_type) delta_2{2};

	XTAL_SET_(sigma_type) sigma_0{0};
	XTAL_SET_(sigma_type) sigma_1{1};
	XTAL_SET_(sigma_type) sigma_2{2};

	XTAL_SET_(sigma_type) N_width = N_size;
	XTAL_SET_(sigma_type) N_depth = N_size << 3U;
	XTAL_SET_(sigma_type) M_depth = N_depth - 1U;

	XTAL_SET_(sigma_type) N_fraction =          S_::N_fraction;
	XTAL_SET_(sigma_type) N_exponent =          S_::N_exponent;
	XTAL_SET_(sigma_type) N_positive = N_fraction + N_exponent;
	XTAL_SET_(sigma_type) N_negative = N_positive + 1;
	XTAL_SET_(sigma_type) N_unit     = N_exponent - 1;
	XTAL_SET_(sigma_type) N_sign     =              1;
	static_assert(N_negative == N_depth);

	struct word
	{
		sigma_type const width;
		sigma_type const depth;
		sigma_type const shift;
		sigma_type const mark;
		sigma_type const mask;

		XTAL_DEF_(short,static) XTAL_LET flag_f(sigma_type const m=0)                       noexcept -> sigma_type {return sigma_1 << (m&M_depth);};
		XTAL_DEF_(short,static) XTAL_LET mark_f(sigma_type const m=0)                       noexcept -> sigma_type {return    ~-flag_f(m)        ;};
		XTAL_DEF_(short,static) XTAL_LET mask_f(sigma_type const m=0, sigma_type const n=0) noexcept -> sigma_type {return      mark_f(m) << n   ;};

		XTAL_NEW_(explicit) word(sigma_type m_depth, sigma_type n_shift=0)
		noexcept
		:	width (m_depth >> 3U)
		,	depth (m_depth)
		,	shift (n_shift)
		,	mark  (mark_f(m_depth))
		,	mask  (mask_f(m_depth, n_shift))
		{}

	};
	XTAL_SET_(word) negative {N_negative};
	XTAL_SET_(word) positive {N_positive};
	XTAL_SET_(word) fraction {N_fraction};
	XTAL_SET_(word) exponent {N_exponent, N_fraction};
	XTAL_SET_(word)     unit     {N_unit, N_fraction};
	XTAL_SET_(word)     sign     {N_sign, N_positive};
	XTAL_SET_(word)     half {N_depth >> 1U, N_depth >> 1U};
	XTAL_SET_(word)     full = negative;
	static_assert((sigma_type) ~sign.mask == positive.mask);

	using default_alignment = constant_t<(size_type) XTAL_SYS_(L1)/N_width>;

#ifdef __cpp_lib_hardware_interference_size
	using constructive_alignment = constant_t<(size_type) _std::hardware_constructive_interference_size/N_width>;
//	using  destructive_alignment = constant_t<(size_type) _std:: hardware_destructive_interference_size/N_width>;
#else
	using constructive_alignment = default_alignment;
//	using  destructive_alignment = default_alignment;
#endif
	using alignment = constructive_alignment;


	XTAL_DEF_(short) XTAL_SET internal_f(     delta_type const &i) noexcept -> auto {return i;}
	XTAL_DEF_(short) XTAL_SET internal_f(     sigma_type const &i) noexcept -> auto {return i;}
	XTAL_DEF_(short) XTAL_SET internal_f( ordinal_q auto const &i) noexcept -> auto {return static_cast<delta_type>(i);}
	XTAL_DEF_(short) XTAL_SET internal_f(cardinal_q auto const &i) noexcept -> auto {return static_cast<sigma_type>(i);}


///////////////////////////////////////////////////////////////////////////////

	template <int N_side=0> requires in_q<N_side, 1, 0, -1>
	XTAL_DEF_(short)
	XTAL_SET clamped_f(integral_q auto const &value)
	noexcept -> auto
	{
		XTAL_IF0
		XTAL_0IF (N_side == 0) {return                          (value);}
		XTAL_0IF (N_side != 0) {return N_side*designed_f<N_side>(value);}
	}

	///\returns the original sign of `target`, before applying the sign of `source`. \

	XTAL_DEF_(long)
	XTAL_SET resign_f(delta_type &target, delta_type const &source=0)
	noexcept -> delta_type
	{
		delta_type const t = target >> positive.depth;
		delta_type const s = source >> positive.depth;
		target ^= s;
		target -= s;
		return t;
	}
	///\returns the `target` magnitude with the sign of the `source`. \

	XTAL_DEF_(short)
	XTAL_SET resigned_f(delta_type target, delta_type const &source=0)
	noexcept -> delta_type
	{
		(void) resign_f(target, source); return target;
	}


	///\returns the original sign of `target`, after making it `abs`olute.

	template <int N_side=0> requires in_q<N_side, 1, 0, -1>
	XTAL_DEF_(long)
	XTAL_SET design_f(delta_type &target)
	noexcept -> delta_type
	{
		delta_type const signum = target >> positive.depth;
		XTAL_IF0
		XTAL_0IF (N_side == -1) {
			target &= signum;
			target += signum;
			target ^= signum;
		}
		XTAL_0IF (N_side ==  0) {
			target += signum;
			target ^= signum;
		}
		XTAL_0IF (N_side ==  1) {
			target &=~signum;
		}
		return signum;
	}
	///\returns the magnitude of `value` (in the direction of `N_side`, if provided). \
	
	template <int N_side=0> requires in_q<N_side, 1, 0, -1>
	XTAL_DEF_(short)
	XTAL_SET designed_f(delta_type value)
	noexcept -> auto
	{
		(void) design_f<N_side>(value); return value;
	}
	static_assert(designed_f< 1>((delta_type) +3) == (3));
	static_assert(designed_f< 1>((delta_type) +2) == (2));
	static_assert(designed_f< 1>((delta_type) +1) == (1));
	static_assert(designed_f< 1>((delta_type)  0) == (0));
	static_assert(designed_f< 1>((delta_type) -1) == (0));
	static_assert(designed_f< 1>((delta_type) -2) == (0));
	static_assert(designed_f< 1>((delta_type) -3) == (0));

	static_assert(designed_f< 0>((delta_type) +3) == (3));
	static_assert(designed_f< 0>((delta_type) +2) == (2));
	static_assert(designed_f< 0>((delta_type) +1) == (1));
	static_assert(designed_f< 0>((delta_type)  0) == (0));
	static_assert(designed_f< 0>((delta_type) -1) == (1));
	static_assert(designed_f< 0>((delta_type) -2) == (2));
	static_assert(designed_f< 0>((delta_type) -3) == (3));

	static_assert(designed_f<-1>((delta_type) +3) == (0));
	static_assert(designed_f<-1>((delta_type) +2) == (0));
	static_assert(designed_f<-1>((delta_type) +1) == (0));
	static_assert(designed_f<-1>((delta_type)  0) == (0));
	static_assert(designed_f<-1>((delta_type) -1) == (1));
	static_assert(designed_f<-1>((delta_type) -2) == (2));
	static_assert(designed_f<-1>((delta_type) -3) == (3));

	
///////////////////////////////////////////////////////////////////////////////

	XTAL_DEF_(short)
	XTAL_SET bit_sign_f(auto const &n)
	noexcept -> decltype(auto)
	{
		return bit_sign_f(internal_f(n));
	}
	XTAL_DEF_(short)
	XTAL_SET bit_sign_f(delta_type const n)
	noexcept -> delta_type
	{
		return n >> positive.depth;
	}
	XTAL_DEF_(short)
	XTAL_SET bit_sign_f(sigma_type const n)
	noexcept -> sigma_type
	{
		return _xtd::bit_cast<sigma_type>(_xtd::bit_cast<delta_type>(n) >> positive.depth);
	}


	///\returns the number of bits set in `u`. \

	XTAL_DEF_(short)
	XTAL_SET bit_count_f(integral_q auto i)
	noexcept -> auto
	requires (sizeof(i) < N_width)
	{
		return bit_count_f(internal_f(i));
	}
	XTAL_DEF_(short)
	XTAL_SET bit_count_f(sigma_type i)
	noexcept -> sigma_type
	{
		return _std::popcount(i);
	}
	XTAL_DEF_(short)
	XTAL_SET bit_count_f(delta_type i)
	noexcept -> delta_type
	{
		delta_type v = design_f(i);
		delta_type u = bit_count_f((sigma_type) i);
		u ^= v;
		u -= v;
		return u;
	}


	template <int N_zero=-1>
	XTAL_DEF_(short)
	XTAL_SET bit_floor_f(integral_q auto i)
	noexcept -> auto
	requires (sizeof(i) < N_width)
	{
		return bit_floor_f<N_zero>(internal_f(i));
	}
	template <int N_zero=-1>
	XTAL_DEF_(short)
	XTAL_SET bit_floor_f(sigma_type i)
	noexcept -> sigma_type
	{
		if constexpr (N_zero == -1) {
			/*/
			sigma_type const  z =  i == sigma_0;
			sigma_type const _z = unit.depth&-z;
			return _std::bit_width(i) - (sigma_1 << _z) + z;// 0 -> -1023
			/*/
			return _std::bit_width(i) - sigma_1;// 0 -> -1
			/***/
		}
		else {
			XTAL_LET Z =         -1;
			XTAL_LET N = N_zero - Z;
			i  =   bit_floor_f(i);
			i += N&bit_sign_f(i);
			return i;
		}
	}
	template <int N_zero=-1>
	XTAL_DEF_(short)
	XTAL_SET bit_floor_f(delta_type i)
	noexcept -> delta_type
	{
		delta_type v = design_f(i);
		delta_type u = bit_floor_f<N_zero>(_xtd::bit_cast<sigma_type>(i));
		u ^= v;
		u -= v;
		return _xtd::bit_cast<delta_type>(u);
	}

	template <int N_zero=-1>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(integral_q auto i)
	noexcept -> auto
	requires (sizeof(i) < N_width)
	{
		return bit_ceiling_f<N_zero>(internal_f(i));
	}
	template <int N_zero=-1>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(sigma_type i)
	noexcept -> sigma_type
	{
		if constexpr (N_zero == -1) {
			sigma_type const z = i == sigma_0;
			//\
			return _std::bit_width(i - !z) - (z << unit.depth) + z;// 0 -> -1023
			return _std::bit_width(i - !z)                     - z;// 0 -> -1
		}
		else {
			XTAL_LET Z =         -1;
			XTAL_LET N = N_zero - Z;
			i  =   bit_ceiling_f(i);
			i += N&bit_sign_f(i);
			return i;
		}
	}
	template <int N_zero=-1>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(delta_type i)
	noexcept -> delta_type
	{
		delta_type v = design_f(i);
		sigma_type u = bit_ceiling_f<N_zero>(_xtd::bit_cast<sigma_type>(i));
		u ^= v;
		u -= v;
		return _xtd::bit_cast<delta_type>(u);
	}

	///\returns the bitwise-reversal of `u`, \
	restricted to `N_subdepth` when `0 < N_subdepth < sizeof(u) << 3U`. \

	///\note Requires `log2(sizeof(u) << 3U)` iterations. \

	XTAL_DEF_(long)
	XTAL_SET bit_reverse_f(sigma_type u, sigma_type const &subdepth)
	noexcept -> sigma_type
	{
		for (sigma_type m = -1, i = N_depth; i >>= 1;) {
			m ^= m<<i;
			u = (u&m)<<i | (u&~m)>>i;
		}
		u >>= N_depth - subdepth; assert(0 < subdepth and subdepth <= N_depth);
		return u;
	}
	template <size_type N_subdepth=0>
	XTAL_DEF_(short)
	XTAL_SET bit_reverse_f(sigma_type const &u)
	noexcept -> sigma_type
	{
		sigma_type constexpr subdepth = 0 < N_subdepth? N_subdepth: N_depth;
		return bit_reverse_f(u, subdepth);
	}

	template <size_type N_subdepth=0>
	XTAL_DEF_(short)
	XTAL_SET bit_reverse_f(integral_q auto i)
	noexcept -> auto
	requires (sizeof(i) < N_width)
	{
		return bit_reverse_f<N_subdepth>(internal_f(i));
	}
	XTAL_DEF_(short)
	XTAL_SET bit_reverse_f(integral_q auto i, sigma_type const &subdepth)
	noexcept -> auto
	requires (sizeof(i) < N_width)
	{
		return bit_reverse_f(internal_f(i), subdepth);
	}


};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <size_type N_size>
struct realize : realize<(N_size >> 1U)>
{
	using _zed = constant_t<false>;

	template <int N_shift=0>
	using widen = realize<(N_shift < 0)? (N_size >> -N_shift): (N_size << N_shift)>;

};
template <size_type N_size> requires recognized_q<N_size>
struct realize<N_size> : rationalize<N_size>
{
	template <int N_shift=0>
	using widen = realize<(N_shift < 0)? (N_size >> -N_shift): (N_size << N_shift)>;

};
template <size_type N_size> requires recognized_q<N_size> and requires {typename recognize<N_size>::alpha_type;}
struct realize<N_size> : rationalize<N_size>
{
private:
	using S_ = rationalize<N_size>;

public:
	template <int N_shift=0>
	using widen = realize<(N_shift < 0)? (N_size >> -N_shift): (N_size << N_shift)>;
	
	using halved = realize<(N_size>>1)>;

	using S_:: negative;
	using S_:: positive;
	using S_:: fraction;
	using S_:: exponent;
	using S_::     unit;
	using S_::     sign;
	using S_::     half;
	using S_::     full;

//	using S_::   iota_0;
//	using S_::   iota_1;
//	using S_::   iota_2;
	
	using S_::  delta_0;
	using S_::  delta_1;
	using S_::  delta_2;

	using S_::  sigma_0;
	using S_::  sigma_1;
	using S_::  sigma_2;

	using typename S_::   iota_type;
	using typename S_::  delta_type;
	using typename S_::  sigma_type;
	using typename S_::  alpha_type;
	using typename S_::  aphex_type;
	using typename S_::mt19937_t;

	XTAL_SET_(alpha_type)  alpha_0{0};
	XTAL_SET_(alpha_type)  alpha_1{1};
	XTAL_SET_(alpha_type)  alpha_2{2};
	XTAL_SET_(alpha_type)  alpha_3{3};
	
	XTAL_SET_(aphex_type)  aphex_0{0, 0};
	XTAL_SET_(aphex_type)  aphex_1{1, 0};
	XTAL_SET_(aphex_type)  aphex_2{2, 0};
	XTAL_SET_(aphex_type)  aphex_3{3, 0};
	XTAL_SET_(aphex_type)  aphex_i{0, 1};

	XTAL_SET_(aphex_type) square_0{0, 0};
	XTAL_SET_(aphex_type) square_1{1, 1};
	XTAL_SET_(aphex_type) square_2{2, 2};
	XTAL_SET_(aphex_type) square_3{3, 3};
	
	XTAL_SET_(aphex_type) circle_0 = square_0*0.7071067811865475244008443621048490393L;
	XTAL_SET_(aphex_type) circle_1 = square_1*0.7071067811865475244008443621048490393L;
	XTAL_SET_(aphex_type) circle_2 = square_2*0.7071067811865475244008443621048490393L;
	XTAL_SET_(aphex_type) circle_3 = square_3*0.7071067811865475244008443621048490393L;

	XTAL_DEF_(short) XTAL_SET internal_f(     alpha_type const &i) noexcept -> auto {return i;}
	XTAL_DEF_(short) XTAL_SET internal_f(integral_q auto const &i) noexcept -> auto {return S_::internal_f(i);}


	XTAL_DEF_(short) XTAL_SET  iota_f(auto &&o) noexcept -> auto {return  iota_type(XTAL_REF_(o));}
//	XTAL_DEF_(short) XTAL_SET delta_f(auto &&o) noexcept -> auto {return delta_type(XTAL_REF_(o));}
//	XTAL_DEF_(short) XTAL_SET sigma_f(auto &&o) noexcept -> auto {return sigma_type(XTAL_REF_(o));}
//	XTAL_DEF_(short) XTAL_SET alpha_f(auto &&o) noexcept -> auto {return alpha_type(XTAL_REF_(o));}
	XTAL_DEF_(short) XTAL_SET aphex_f(auto &&o) noexcept -> auto {return aphex_type(XTAL_REF_(o));}

	XTAL_DEF_(short)
	XTAL_SET delta_f(auto &&o)
	noexcept -> delta_type
	{
		using Q = XTAL_ALL_(o);
		XTAL_IF0
		XTAL_0IF (       same_q<delta_type, Q>) {return                                 XTAL_REF_(o)  ;}
		XTAL_0IF (       same_q<sigma_type, Q>) {return      _std::bit_cast<delta_type>(XTAL_REF_(o)) ;}
		XTAL_0IF (       same_q<alpha_type, Q>) {return         static_cast<delta_type>(XTAL_REF_(o)) ;}
	//	XTAL_0IF (_std::  signed_integral<Q>) {return delta_f(static_cast<delta_type>(XTAL_REF_(o)));}
		XTAL_0IF (_std::unsigned_integral<Q>) {return delta_f(static_cast<sigma_type>(XTAL_REF_(o)));}
		XTAL_0IF (_std::   floating_point<Q>) {return delta_f(static_cast<alpha_type>(XTAL_REF_(o)));}
		XTAL_0IF_(else)                       {return         static_cast<delta_type>(XTAL_REF_(o)) ;}
	}
	XTAL_DEF_(short)
	XTAL_SET sigma_f(auto &&o)
	noexcept -> sigma_type
	{
		using Q = XTAL_ALL_(o);
		XTAL_IF0
		XTAL_0IF (       same_q<delta_type, Q>) {return      _std::bit_cast<sigma_type>(XTAL_REF_(o)) ;}
		XTAL_0IF (       same_q<sigma_type, Q>) {return                                 XTAL_REF_(o)  ;}
		XTAL_0IF (       same_q<alpha_type, Q>) {return                 sigma_f(delta_f(XTAL_REF_(o)));}
		XTAL_0IF (_std::  signed_integral<Q>) {return sigma_f(static_cast<delta_type>(XTAL_REF_(o)));}
	//	XTAL_0IF (_std::unsigned_integral<Q>) {return sigma_f(static_cast<sigma_type>(XTAL_REF_(o)));}
		XTAL_0IF (_std::   floating_point<Q>) {return sigma_f(static_cast<alpha_type>(XTAL_REF_(o)));}
		XTAL_0IF_(else)                       {return         static_cast<sigma_type>(XTAL_REF_(o)) ;}
	}
	XTAL_DEF_(short)
	XTAL_SET alpha_f(auto &&o)
	noexcept -> alpha_type
	{
		using Q = XTAL_ALL_(o);
		XTAL_IF0
		XTAL_0IF (       same_q<delta_type, Q>) {return         static_cast<alpha_type>(XTAL_REF_(o)) ;}
		XTAL_0IF (       same_q<sigma_type, Q>) {return                 alpha_f(delta_f(XTAL_REF_(o)));}
		XTAL_0IF (       same_q<alpha_type, Q>) {return                                 XTAL_REF_(o)  ;}
		XTAL_0IF (_std::  signed_integral<Q>) {return alpha_f(static_cast<delta_type>(XTAL_REF_(o)));}
		XTAL_0IF (_std::unsigned_integral<Q>) {return alpha_f(static_cast<sigma_type>(XTAL_REF_(o)));}
	//	XTAL_0IF (_std::   floating_point<Q>) {return         static_cast<alpha_type>(XTAL_REF_(o)) ;}
		XTAL_0IF_(else)                       {return         static_cast<alpha_type>(XTAL_REF_(o)) ;}
	}


	using S_::N_width;
	using S_::N_depth;
	using S_::N_fused;


	XTAL_SET_(sigma_type) IEC = _std::numeric_limits<alpha_type>::is_iec559? XTAL_SYS_(IEC)&60559: 0;

	XTAL_DEF_(short)
	XTAL_SET use_IEC()
	noexcept -> bool
	{
		return IEC&559;
	}
	XTAL_DEF_(short)
	XTAL_SET use_FMA()
	noexcept -> bool
	{
		return N_fused;
	}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	template <class Z>
	//\
	using couple_t = typename _std::array<Z, 2>;
	using couple_t = bond::couple_t<Z, Z>;


////////////////////////////////////////////////////////////////////////////////

	template <auto N_pow=1>
	XTAL_DEF_(short)
	XTAL_SET versus_f(auto &&u)
	noexcept -> auto
	{
		using U = XTAL_ALL_(u);
		XTAL_IF0
		XTAL_0IF (signum_n<N_pow> ==  0) {return couple_t<U>{u, one/XTAL_REF_(u)};}
		XTAL_0IF (signum_n<N_pow> == -1) {return                one/XTAL_REF_(u) ;}
		XTAL_0IF (signum_n<N_pow> == +1) {return                    XTAL_REF_(u) ;}
	}


////////////////////////////////////////////////////////////////////////////////

	///\
	Computes: `abs(u)**2`. \

	template <int N_pow=1> requires in_q<N_pow, 1, 0, -1>
	XTAL_DEF_(short)
	XTAL_SET dot_f(aphex_type const &u)
	noexcept -> alpha_type
	{
		alpha_type const x = u.real();
		alpha_type const y = u.imag();
		return versus_f<N_pow>(_xtd::accumulator(x*x, y, y));
	}


	///\
	Estimates: `w**(1/N_pow)`. \

	template <int N_pow>
	XTAL_DEF_(short)
	XTAL_SET root_e(alpha_type const &w)
	noexcept -> alpha_type
	{
		static_assert(N_pow < 0);
		if (_std::is_constant_evaluated()) {
			return _xtd::bit_cast<alpha_type>(S_::template root_n<N_pow> - (_xtd::bit_cast<delta_type>(w) >> size_1));
		}
		else {
			return S_::template root_e<N_pow>(w);
		}
	}
	template <int N_pow>
	XTAL_DEF_(short)
	XTAL_SET root_e(alpha_type const &w, alpha_type const &n)
	noexcept -> alpha_type
	{
		static_assert(N_pow < 0);
		if (_std::is_constant_evaluated()) {
			if constexpr (N_pow == -1) {
				return (2.0 - n*w)*(w);
			}	else
			if constexpr (N_pow == -2) {
				return (1.5 - 0.5*w*n*n);
			}
		}
		else {
			return S_::template root_e<N_pow>(w, n);
		}
	}
	///\
	Computes: `w**(1/N_pow)`. \

	template <int N_pow=1, int N_lim=-1>// requires in_q<N_pow, 1, 0, -1>
	XTAL_DEF_(short)
	XTAL_SET root_f(auto const &w)
	noexcept -> alpha_type
	{
		using _std::sqrt;

		using W = XTAL_ALL_(w);
		using V = absolve_u<W>;

	//	W constexpr W_1{1};
		V constexpr U_1{1};
		V constexpr U_2{2};

		bool constexpr N_etc = not real_number_q<W>;

		int constexpr K_pow = -S_::designed_f(N_pow);
		int constexpr M_lim = below_m<(1<<4), (unsigned) N_lim>;

		XTAL_IF0 //	ELIMINATION
		XTAL_0IF (N_pow ==  0) {return U_1;}
		XTAL_0IF (N_pow ==  1) {return w  ;}
		XTAL_0IF (N_pow == -1 and N_lim < 0 or N_etc) {return U_1/w;}
		XTAL_0IF (N_pow ==  2 and N_lim < 0 or N_etc) {if (N_etc or not _std::is_constant_evaluated()) {return     sqrt(w);}}
		XTAL_0IF (N_pow == -2 and N_lim < 0 or N_etc) {if (N_etc or not _std::is_constant_evaluated()) {return U_1/sqrt(w);}}

	//	assert(_std::is_constant_evaluated()? K_pow == -2: K_pow < 0 and 0 <= N_lim);
	
		XTAL_IF0
		XTAL_0IF (real_number_q<W>) {
		//	ESTIMATION:
			W n = root_e<K_pow>(w);
			seek_forward_f<M_lim>([&] (auto)
				XTAL_0FN {n *= root_e<K_pow>(w, n);}
			);
		//	CORRECTION:
			XTAL_IF0
			XTAL_0IF (K_pow == -2 and N_lim < 0) {
				n /= U_1 + n*n*w;
				n *= U_2;
			}
		//	RESOLUTION:
			XTAL_IF0
		//	XTAL_0IF (N_pow ==  1) {return w;}
			XTAL_0IF (N_pow == -1) {return n;}
			XTAL_0IF (N_pow == -2) {return n;}
			XTAL_0IF (N_pow ==  2) {return w*n;}
		}
	}
	template <int N_pow=1, int N_lim=-1>// requires in_q<N_pow, 1, 0, -1>
	XTAL_DEF_(short)
	XTAL_SET root_f(integral_q auto const &w)
	noexcept -> alpha_type
	{
		return root_f<N_pow, N_lim>((alpha_type) w);
	}

	template <int N_pow=1, int N_lim=-1>// requires in_q<N_pow, 1, 0, -1>
	XTAL_DEF_(short)
	XTAL_SET roots_f(alpha_type const &w)
	noexcept -> couple_t<alpha_type>
	{
		int constexpr K_pow = -S_::designed_f(N_pow);
		alpha_type n = root_f<K_pow, N_lim>(w);
		alpha_type u = n*w;
		XTAL_IF0
		XTAL_0IF (0 < N_pow) {return couple_t<alpha_type> {u, n};}
		XTAL_0IF (N_pow < 0) {return couple_t<alpha_type> {n, u};}
	}
	static_assert(root_f< 2>(3) == (alpha_type) 1.7320508075688772935274463415058723670L);
	static_assert(root_f< 2>(2) == (alpha_type) 1.4142135623730950488016887242096980786L);
	static_assert(root_f<-2>(2) == (alpha_type) 0.7071067811865475244008443621048490393L);
	static_assert(root_f<-2>(3) == (alpha_type) 0.5773502691896257645091487805019574556L);

	static_assert(get<0>(roots_f< 2>(2)) == (alpha_type) 1.4142135623730950488016887242096980786L);
	static_assert(get<1>(roots_f< 2>(2)) == (alpha_type) 0.7071067811865475244008443621048490393L);



	template <int N_pow=1, int N_lim=-1> requires in_q<N_pow, 1, 0, -1>
	XTAL_DEF_(short)
	XTAL_SET unsquare_f(alpha_type const &w)
	noexcept -> decltype(auto)
	{
		XTAL_IF0
		XTAL_0IF (0 == N_pow) {return roots_f<2,       N_lim>(w);}
		XTAL_0IF (0 != N_pow) {return root_f <2*N_pow, N_lim>(w);}
	}
	template <int N_pow=1, int N_lim=-1> requires in_q<N_pow, 1, 0, -1>
	XTAL_DEF_(short)
	XTAL_SET unsquare_dot_f(auto &&u)
	noexcept -> decltype(auto)
	{
		return unsquare_f<N_pow, N_lim>(dot_f(XTAL_REF_(u)));
	}


	template <int N_pow=1, int N_lim=+1> requires in_q<N_pow, 1, 0, -1>
	XTAL_DEF_(long)
	XTAL_SET square_f(auto const &z)
	noexcept -> auto
	{
		using Z = XTAL_ALL_(z);

		XTAL_IF0
		XTAL_0IF (N_lim == 0) {
			return versus_f<N_pow>(z);
		}
		XTAL_0IF (complex_number_q<Z>) {
			auto x = z.real();
			auto y = z.imag();
			seek_forward_f<N_lim>([&] (auto) XTAL_0FN {
				auto const xx = square_f(x);
				auto const yy = square_f(y);
				y *= two*x;
				x  = xx - yy;
			});
			return versus_f<N_pow>(Z{x, y});
		}
		XTAL_0IF (multiplicative_group_p<1, Z>) {
			auto zz = z;
			seek_forward_f<N_lim>([&] (auto)
				XTAL_0FN_(zz *= zz)
			);
			return versus_f<N_pow>(zz);
		}
		XTAL_0IF (multiplicative_group_p<2, Z>) {
			return square_f<N_pow, N_lim - 1>(z*z);
		}
	}


	template <int N_pow=1> requires in_q<N_pow, 1, 0, -1>
	XTAL_DEF_(short)
	XTAL_SET circle_f(alpha_type const &u)
	noexcept -> aphex_type
	{
		auto const x = _std::cos(u);
		auto const y = _std::sin(u);
		if constexpr (N_pow == 0) {
			return couple_t<aphex_type> {{x, y}, {x, -y}};
		}
		else {
			return aphex_type{x, y*N_pow};
		}
	}
	

	XTAL_DEF_(short)
	XTAL_SET round_f(real_number_q auto const x)
	noexcept -> decltype(auto)
	{
#if XTAL_SYS_(builtin)
		return           round(x);
#else
		return __builtin_round(x);
#endif
	}
	XTAL_DEF_(short)
	XTAL_SET round_f(complex_number_q auto const &x)
	noexcept -> XTAL_ALL_(x)
	{
		return {round_f(x.real()), round_f(x.imag())};
	}


////////////////////////////////////////////////////////////////////////////////

	///\returns the `constexpr` equivalent of `std:pow(base, n_zoom)` for an `unsigned int n_zoom`. \
	
	XTAL_DEF_(long)
	XTAL_SET explo_f(auto &&base, sigma_type const &n_exponent)
	noexcept -> auto
	{
		XTAL_ALL_(base) u = XTAL_REF_(base), w = {1};
		for (sigma_type n = n_exponent; n; n >>= 1) {
			if (n&1U) {
				w *= u;
			}
			u = square_f(XTAL_MOV_(u));
		}
		return w;
	}
	template <size_type N_exponent>
	XTAL_DEF_(short)
	XTAL_SET explo_f(auto &&base, auto result)
	noexcept -> auto
	{
		XTAL_LET N = N_exponent >> 0U;
		XTAL_LET M = N_exponent >> 1U;
		XTAL_LET I = N_exponent  & 1U;
		XTAL_IF0
		XTAL_0IF (N == 0) {return result;}
		XTAL_0IF (I == 0) {return explo_f<M>(square_f(XTAL_REF_(base)),                 XTAL_MOV_(result));}
		XTAL_0IF (I == 1) {return explo_f<M>(square_f(          base ), XTAL_REF_(base)*XTAL_MOV_(result));}
	}
	template <int N_exponent>
	XTAL_DEF_(short)
	XTAL_SET explo_f(auto &&base)
	noexcept -> auto
	{
		using Y = based_t<decltype(base)>;
		using V = absolve_u<Y>;

		V const v{1};// NOTE: Won't work for matricies...
		Y const y{v};

		XTAL_IF0
		XTAL_0IF (0 == N_exponent) {return y;}
		XTAL_0IF (0 <  N_exponent) {return explo_f< N_exponent>(  XTAL_REF_(base), y);}
		XTAL_0IF (N_exponent <  0) {return explo_f<-N_exponent>(y/XTAL_REF_(base), y);}
	}
	static_assert(explo_f<0>(alpha_type(2.0)) == 1.00);
	static_assert(explo_f<1>(alpha_type(2.0)) == 2.00);
	static_assert(explo_f<2>(alpha_type(2.0)) == 4.00);


	///\returns the `constexpr` equivalent of `std:pow(2.0, n_zoom)`. \

	XTAL_DEF_(short)
	XTAL_SET diplo_e(alpha_type n_zoom, alpha_type o_silon)
	noexcept -> alpha_type
	{
		if constexpr (XTAL_SYS_(builtin)) {
			return o_silon*__builtin_exp2(n_zoom);
		}
		else {
			XTAL_LET N_ln2 = alpha_f(0.6931471805599453094172321214581770e0L);
			return o_silon*exp(n_zoom*N_ln2);// TODO: Handle `consteval`?
		}
	}
	XTAL_DEF_(short)
	XTAL_SET diplo_e(delta_type n_zoom, alpha_type o_silon)
	noexcept -> alpha_type
	{
		if (_std::is_constant_evaluated()) {
			auto m = _xtd::bit_cast<sigma_type>(n_zoom);
			m  += unit.mark;
			m <<= 1 + exponent.shift;
			m >>= 1;
			return o_silon*_xtd::bit_cast<alpha_type>(m);
		}
		else {
			return _std::ldexp(o_silon, (int) n_zoom);// not `constexpr` until `C++23`!
		}
	}
	XTAL_DEF_(short)
	XTAL_SET diplo_e(sigma_type n_zoom, alpha_type o_silon)
	noexcept -> alpha_type
	{
		return diplo_e(_xtd::bit_cast<delta_type>(n_zoom), o_silon);
	}
	XTAL_DEF_(short) XTAL_SET diplo_e(auto n_zoom, alpha_type o_silon)
	noexcept -> decltype(auto)
	{
		return diplo_e(internal_f(XTAL_REF_(n_zoom)), o_silon);
	}

	template <int N_silon=0>
	XTAL_DEF_(short)
	XTAL_SET diplo_f(auto const &n_zoom)
	noexcept -> alpha_type
	{
		XTAL_LET o_silon = one/alpha_type{sigma_1 << fraction.depth - magnum_n<N_silon>};
		XTAL_IF0
		XTAL_0IF (0 < N_silon) {return diplo_e(n_zoom, one + alpha_type{0.50}/o_silon);}
		XTAL_0IF (N_silon < 0) {return diplo_e(n_zoom, one - alpha_type{0.25}/o_silon);}
		XTAL_0IF_(else)        {return diplo_e(n_zoom,       alpha_type{1.00}        );}
	}
	template <int N_silon=0>
	XTAL_DEF_(short)
	XTAL_SET diplo_f()
	noexcept -> alpha_type
	{
		return diplo_f<N_silon>(N_depth);
	}

	template <int N_zoom=N_depth>
	XTAL_SET_(alpha_type) diplo_n = diplo_f(N_zoom);
	///< Value expression of `diplo_f`. \

	static_assert(diplo_n<+1> == 2.0);
	static_assert(diplo_n< 0> == 1.0);
	static_assert(diplo_n<-1> == 0.5);

	XTAL_SET_(alpha_type) diplo_0 = diplo_n<0>;
	XTAL_SET_(alpha_type) diplo_1 = diplo_n<1>;
	XTAL_SET_(alpha_type) diplo_2 = diplo_n<2>;


	///\returns the `constexpr` equivalent of `std:pow(0.5, n_zoom)`. \

	template <int N_silon=0> XTAL_DEF_(short) XTAL_SET haplo_f(auto const &n_zoom) noexcept -> auto {return diplo_f<-N_silon>(-n_zoom );}
	template <int N_silon=0> XTAL_DEF_(short) XTAL_SET haplo_f(                  ) noexcept -> auto {return diplo_f<-N_silon>(-N_depth);}

	template <int N_zoom=N_depth>
	XTAL_SET_(alpha_type) haplo_n = haplo_f(N_zoom);
	///< Value expression of `haplo_f`. \

	static_assert(haplo_n<+1> == 0.5);
	static_assert(haplo_n< 0> == 1.0);
	static_assert(haplo_n<-1> == 2.0);

	XTAL_SET_(alpha_type) haplo_0 = haplo_n<0>;
	XTAL_SET_(alpha_type) haplo_1 = haplo_n<1>;
	XTAL_SET_(alpha_type) haplo_2 = haplo_n<2>;


////////////////////////////////////////////////////////////////////////////////

	///\returns the `n_num`erator divided by the given de`n_nom`inator.

	template <int N_pow=1>
	XTAL_DEF_(short)
	XTAL_SET ratio_f(alpha_type const &n_num, alpha_type const &n_nom=1)
	noexcept -> alpha_type
	{
		static_assert(in_q<N_pow, 1, 0, -1>);
		XTAL_IF0
		XTAL_0IF (N_pow ==  0) {return 1;}
		XTAL_0IF (N_pow ==  1) {return n_num/n_nom;}
		XTAL_0IF (N_pow == -1) {return n_nom/n_num;}
	}
	static_assert(ratio_f(1, 2.0) == 0.5 && ratio_f<-1>(1, 2.0) == 2.0);
	static_assert(ratio_f(4, 2.0) == 2.0 && ratio_f<-1>(4, 2.0) == 0.5);

	XTAL_SET_(alpha_type) ratio_0 = ratio_f(0, 1);
	XTAL_SET_(alpha_type) ratio_1 = ratio_f(1, 1);
	XTAL_SET_(alpha_type) ratio_2 = ratio_f(2, 1);

	///\returns `ratio_f<N_pow>(PI*n_num, n_nom)`.

	template <int N_pow=1> requires in_q<N_pow, 1, 0, -1>
	XTAL_DEF_(short)
	XTAL_SET patio_f(alpha_type const &n_num, alpha_type const &n_nom=1)
	noexcept -> alpha_type
	{
		return ratio_f<N_pow>(_std::numbers::pi_v<alpha_type>*n_num, n_nom);
	}
	static_assert(patio_f(1, 2) ==  alpha_type(1.570796326794896619231321691639751442L));
	static_assert(patio_f(1,-2) == -alpha_type(1.570796326794896619231321691639751442L));
	static_assert(patio_f(4, 2) ==  alpha_type(6.283185307179586476925286766559005768L));
	static_assert(patio_f(4,-2) == -alpha_type(6.283185307179586476925286766559005768L));

	XTAL_SET_(alpha_type) patio_0 = patio_f(0, 1);
	XTAL_SET_(alpha_type) patio_1 = patio_f(1, 1);
	XTAL_SET_(alpha_type) patio_2 = patio_f(2, 1);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\returns the difference between floating-point values at the scale designated by `n_zoom`. \

	XTAL_DEF_(short)
	XTAL_SET epsilon_f(delta_type const &n_zoom=1)
	noexcept -> alpha_type
	{
		auto constexpr N = fraction.depth + 1;
		return haplo_f(N - n_zoom);
	}
	template <int N_zoom=0>
	XTAL_SET_(alpha_type) epsilon_n = epsilon_f(N_zoom);
	///< Value expression of `epsilon_f`. \

	static_assert(epsilon_n<0> != 0);
	static_assert(epsilon_n<0> <  epsilon_n<1>);
	static_assert(epsilon_n<1> <  epsilon_n<2>);
	static_assert(epsilon_n<1> == _std::numeric_limits<alpha_type>::epsilon());
	
	static_assert(one <  one + epsilon_n< 1>);
	static_assert(one == one + epsilon_n< 0>);
	static_assert(one == one - epsilon_n<-1>);
	static_assert(one  > one - epsilon_n< 1>);
	
	XTAL_SET_(alpha_type) epsilon_0 = epsilon_n<0>;
	XTAL_SET_(alpha_type) epsilon_1 = epsilon_n<1>;
	XTAL_SET_(alpha_type) epsilon_2 = epsilon_n<2>;


	///\returns the value `n_zoom` steps above `(alpha_type) 1`. \

	XTAL_DEF_(short)
	XTAL_SET upsilon_f(delta_type const &n_zoom=1, delta_type const &n_zone=0)
	noexcept -> alpha_type
	{
		auto constexpr N_diff = fraction.depth + 1;
		auto const     n_unit = one + haplo_f(N_diff - n_zoom);
		return n_unit*diplo_f(n_zone);
	}
	template <int N_zoom=0>
	XTAL_SET_(alpha_type) upsilon_n = upsilon_f(N_zoom);
	///< Value expression of `upsilon_f`. \
	
	static_assert(         one == upsilon_n<0>);
	static_assert(upsilon_n<0> <  upsilon_n<1>);
	static_assert(upsilon_n<1> <  upsilon_n<2>);
	
	XTAL_SET_(alpha_type) upsilon_0 = upsilon_n<0>;
	XTAL_SET_(alpha_type) upsilon_1 = upsilon_n<1>;
	XTAL_SET_(alpha_type) upsilon_2 = upsilon_n<2>;


	///\returns the value `n_zoom` steps below `(alpha_type) 1`. \

	XTAL_DEF_(short)
	XTAL_SET dnsilon_f(delta_type const &n_zoom=1, delta_type const &n_zone=0)
	noexcept -> alpha_type
	{
		auto constexpr N_diff = fraction.depth + 2;
		auto const     n_unit = one - haplo_f(N_diff - n_zoom);
		return n_unit*diplo_f(n_zone);
	}
	template <int N_zoom=0>
	XTAL_SET_(alpha_type) dnsilon_n = dnsilon_f(N_zoom);
	///< Value expression of `dnsilon_f`. \
	
	static_assert(         one == dnsilon_n<0>);
	static_assert(dnsilon_n<1> <  dnsilon_n<0>);
	static_assert(dnsilon_n<2> <  dnsilon_n<1>);
	
	XTAL_SET_(alpha_type) dnsilon_0 = dnsilon_n<0>;
	XTAL_SET_(alpha_type) dnsilon_1 = dnsilon_n<1>;
	XTAL_SET_(alpha_type) dnsilon_2 = dnsilon_n<2>;


////////////////////////////////////////////////////////////////////////////////

	///\returns the minimum value that still accommodates arithmetic puncturing. \

	XTAL_DEF_(short)
	XTAL_SET minilon_f(delta_type const &n_zoom=0)
	noexcept -> alpha_type
	{
		return haplo_f(unit.mark - 1)*diplo_f(n_zoom);
	}
	template <int N_zoom=0>
	XTAL_SET_(alpha_type) minilon_n = minilon_f(N_zoom);
	///< Value expression for `minilon_f`. \

	XTAL_SET minilon_0 = minilon_n<0>;
	XTAL_SET minilon_1 = minilon_n<1>;
	XTAL_SET minilon_2 = minilon_n<2>;
	XTAL_SET minilon_3 = minilon_n<3>;


	///\returns the minimum of the given arguments `xs...`, evaluated with respect to type `alpha_type`. \

	XTAL_DEF_(short)
	XTAL_SET minimum_f()
	noexcept -> decltype(auto)
	{
		return minilon_f();
	}
	XTAL_DEF_(short)
	XTAL_SET minimum_f(auto const &w)
	noexcept -> auto const &
	{
		return XTAL_REF_(w);
	}
	XTAL_DEF_(short)
	XTAL_SET minimum_f(auto const &w, auto const &x)
	noexcept -> auto const &
	{
		return w < x? w: x;
	}
	XTAL_DEF_(short)
	XTAL_SET minimum_f(auto const &w, auto const &x, auto const &...xs)
	noexcept -> auto const &
	{
		return minimum_f(minimum_f(w, x), xs...);
	}


	///\returns the maximum value that still accommodates arithmetic truncation. \

	XTAL_DEF_(short)
	XTAL_SET maxilon_f(delta_type const &n_zoom=0)
	noexcept -> alpha_type
	{
		return diplo_f(unit.mark - 1)*haplo_f(n_zoom);
	}
	template <int N_zoom=0>
	XTAL_SET_(alpha_type) maxilon_n = maxilon_f(N_zoom);
	///< Value expression for `maxilon_f`. \

	XTAL_SET maxilon_0 = maxilon_n<0>;
	XTAL_SET maxilon_1 = maxilon_n<1>;
	XTAL_SET maxilon_2 = maxilon_n<2>;
	XTAL_SET maxilon_3 = maxilon_n<3>;


	///\returns the maximum of the given arguments `xs...`, evaluated with respect to type `alpha_type`. \

	XTAL_DEF_(short)
	XTAL_SET maximum_f()
	noexcept -> decltype(auto)
	{
		return maxilon_f();
	}
	XTAL_DEF_(short)
	XTAL_SET maximum_f(auto const &w)
	noexcept -> auto const &
	{
		return w;
	}
	XTAL_DEF_(short)
	XTAL_SET maximum_f(auto const &w, auto const &x)
	noexcept -> auto const &
	{
		return w < x? x: w;
	}
	XTAL_DEF_(short)
	XTAL_SET maximum_f(auto const &w, auto const &x, auto const &...xs)
	noexcept -> auto const &
	{
		return maximum_f(maximum_f(w, x), xs...);
	}


////////////////////////////////////////////////////////////////////////////////

	XTAL_DEF_(short)
	XTAL_SET mantissa_f(delta_type n)
	noexcept -> alpha_type
	{
		n >>= sign.depth + exponent.depth;
		return alpha_type(n)*haplo_f(fraction.depth);
	}
	XTAL_DEF_(short)
	XTAL_SET mantissa_f(mt19937_t &m)
	noexcept -> alpha_type
	{
		return mantissa_f(m());
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\returns the sign of `value` as an `alpha_type`. \

	XTAL_DEF_(short)
	XTAL_SET assigned_f(integral_q auto u)
	noexcept -> alpha_type
	{
		return assigned_f(S_::internal_f(u));
	}
	XTAL_DEF_(short)
	XTAL_SET assigned_f(sigma_type u)
	noexcept -> alpha_type
	{
		static_assert(_std::numeric_limits<alpha_type>::is_iec559);
		u <<= positive.depth;
		u  |= unit.mask;
		return _xtd::bit_cast<alpha_type>(u);
	}
	XTAL_DEF_(short)
	XTAL_SET assigned_f(delta_type u)
	noexcept -> alpha_type
	{
		static_assert(_std::numeric_limits<alpha_type>::is_iec559);
		u &= sign.mask;
		u |= unit.mask;
		return _xtd::bit_cast<alpha_type>(u);
	}

	///\returns the sign of `value`. \

	XTAL_DEF_(short)
	XTAL_SET assigned_f(alpha_type const &value)
	noexcept -> alpha_type
	{
		return _xtd::copysign(alpha_1, value);
	}
	static_assert(assigned_f((alpha_type)  0.5) ==  1.0);
	static_assert(assigned_f((alpha_type)  0.0) ==  1.0);
	static_assert(assigned_f((alpha_type) -0.5) == -1.0);

	XTAL_DEF_(short)
	XTAL_SET assigned_f(aphex_type const &value)
	noexcept -> aphex_type
	{
		return unsquare_dot_f<-1>(value)*(value);
	}


	///\returns the original sign of `target`, after making it `abs`olute.

	using S_::design_f;

	XTAL_DEF_(long)
	XTAL_SET design_f(alpha_type &target)
	noexcept -> alpha_type
	{
		alpha_type const signum = assigned_f(target);
		target *= signum;
		return signum;
	}

	///\returns the magnitude of `value` (in the direction of `N_side`, if provided). \
	
	using S_::designed_f;

	template <int N_side=0>
	XTAL_DEF_(short)
	XTAL_SET designed_f(integral_q auto value)
	noexcept -> decltype(auto)
	{
		return S_::template designed_f<N_side>(value);
	}
	template <int N_side=0>
	XTAL_DEF_(short)
	XTAL_SET designed_f(alpha_type value)
	noexcept -> alpha_type
	{
		if constexpr (N_side == 0) {
			return _xtd::copysign(value, alpha_1);
		}
		else {
			delta_type constexpr N_diff = designed_f(N_side);
			alpha_type constexpr N_sign = assigned_f(N_side);
			value *= N_sign*haplo_f(1); value -= minilon_n<N_diff - 1>;
			value += designed_f(value); value += minilon_n<N_diff - 1>;
			return value;
		}
	}
	static_assert(designed_f( alpha_1) ==  1.0);
	static_assert(designed_f(-alpha_1) ==  1.0);

//	static_assert(designed_f< 1>( alpha_1) ==  1.0);
//	static_assert(designed_f< 1>(-alpha_1) ==  0.0);
//	static_assert(designed_f<-1>( alpha_1) ==  0.0);
//	static_assert(designed_f<-1>(-alpha_1) ==  1.0);


	///\returns the original sign of `target`, before applying the sign of `source`. \

	using S_::resign_f;

	XTAL_DEF_(long)
	XTAL_SET resign_f(alpha_type &target, auto source=1)
	noexcept -> alpha_type
	{
		return resign_f(target, internal_f(source));
	}
	XTAL_DEF_(long)
	XTAL_SET resign_f(alpha_type &target, auto source=1)
	noexcept -> alpha_type
	requires in_q<sizeof(target), sizeof(source)>
	{
		XTAL_IF0
		XTAL_0IF_(consteval) {
			alpha_type const signum = assigned_f(target);
			target = resigned_f(target, source);
			return signum;
		}
		XTAL_0IF_(else) {
			auto &t = reinterpret_cast<delta_type &>(target);
			auto &s = reinterpret_cast<delta_type &>(source);
			s &= sign.mask;
			t ^= s;
			s ^= sign.mask*t;
			t ^= s;
			s |= unit.mask;
			return source;
		}
	}
	///\returns the `target` magnitude with the sign of the `source`. \

	XTAL_DEF_(short)
	XTAL_SET resigned_f(alpha_type const &target, alpha_type const &source=1)
	noexcept -> alpha_type
	{
		return _xtd::copysign(target, source);
	}
	XTAL_DEF_(short)
	XTAL_SET resigned_f(alpha_type const &target, delta_type source=0)
	noexcept -> alpha_type
	{
		source &= sign.mask;
		source |= unit.mask;
		return target*_xtd::bit_cast<alpha_type>(source);
	}


////////////////////////////////////////////////////////////////////////////////
	///\todo\
	Implement in-place `clamp_f`?
	
//	using S_::clamped_f;
	///\returns `value` (restricted to `N_side`, if provided). \
	
	template <int N_side=0>
	XTAL_DEF_(short)
	XTAL_SET clamped_f(integral_q auto value)
	noexcept -> decltype(auto)
	{
		return S_::template clamped_f<N_side>(value);
	}
	template <int N_side=0>
	XTAL_DEF_(short)
	XTAL_SET clamped_f(alpha_type value)
	noexcept -> alpha_type
	{
		XTAL_IF0
		XTAL_0IF (N_size == 0) {return                                     value ;}
		XTAL_0IF (N_size != 0) {return signum_n<N_side>*designed_f<N_side>(value);}
	}
	static_assert(clamped_f<+1>( alpha_1) == +1.0);
	static_assert(clamped_f<+1>( alpha_0) == +minilon_f());
	static_assert(clamped_f<+1>(-alpha_1) == +minilon_f());
	static_assert(clamped_f<-1>( alpha_1) == -minilon_f());
	static_assert(clamped_f<-1>( alpha_0) == -minilon_f());
	static_assert(clamped_f<-1>(-alpha_1) == -1.0);


////////////////////////////////////////////////////////////////////////////////

	XTAL_DEF_(short)
	XTAL_SET scientific_f(alpha_type const &f)
	noexcept -> couple_t<delta_type>
	{
		delta_type constexpr N = unit.mark + fraction.depth;
		sigma_type constexpr M =      one << fraction.depth;
		
		auto       const o = _xtd::bit_cast<sigma_type>(f);
		delta_type const z = static_cast<delta_type>(o) >> positive.depth;
		delta_type const n = N - (o << sign.depth >> sign.depth + exponent.shift);
		delta_type       m = M | (o&fraction.mask);
		m  ^= z;
		m  -= z;
		return {m, n};
	}
	XTAL_DEF_(short)
	XTAL_SET unscientific_f(couple_t<delta_type> const &mn)
	noexcept -> alpha_type
	{
		auto const [m, n] = mn;
		return static_cast<alpha_type>(m)*haplo_f(n);
	}

	static_assert( 2.25 == unscientific_f(scientific_f( 2.25)));
	static_assert( 1.25 == unscientific_f(scientific_f( 1.25)));
	static_assert( 0.25 == unscientific_f(scientific_f( 0.25)));
	static_assert( 0.75 == unscientific_f(scientific_f( 0.75)));
	static_assert( 1.75 == unscientific_f(scientific_f( 1.75)));
	static_assert( 2.75 == unscientific_f(scientific_f( 2.75)));

	static_assert(-2.25 == unscientific_f(scientific_f(-2.25)));
	static_assert(-1.25 == unscientific_f(scientific_f(-1.25)));
	static_assert(-0.25 == unscientific_f(scientific_f(-0.25)));
	static_assert(-0.75 == unscientific_f(scientific_f(-0.75)));
	static_assert(-1.75 == unscientific_f(scientific_f(-1.75)));
	static_assert(-2.75 == unscientific_f(scientific_f(-2.75)));







//	using S_::bit_floor_f;
	template <int N_zero=-1>
	XTAL_DEF_(short)
	XTAL_SET bit_floor_f(integral_q auto &&f)
	noexcept -> auto
	{
		return S_::template bit_floor_f<N_zero>(XTAL_REF_(f));
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_floor_f(real_number_q auto &&f)
	noexcept -> auto
	{
		return bit_floor_f<N_zero>(internal_f(XTAL_REF_(f)));
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_floor_f(alpha_type const f)
	noexcept -> auto
	{
		XTAL_LET Z = -unit.mark;
		XTAL_LET N = N_zero - Z << unit.shift;

		auto n = _xtd::bit_cast<sigma_type>(f);
		n &= ~sign.mask;
		n -=  unit.mask;
		n += N&S_::bit_sign_f(n);
		return _xtd::bit_cast<delta_type>(n) >> unit.shift;
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_floor_f(aphex_type const f)
	noexcept -> auto
	{
		return bit_floor_f<N_zero>(dot_f(f)) >> 1;
	}

//	using S_::bit_ceiling_f;
	template <int N_zero=-1>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(integral_q auto &&f)
	noexcept -> auto
	{
		return S_::template bit_ceiling_f<N_zero>(XTAL_REF_(f));
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(real_number_q auto &&f)
	noexcept -> auto
	{
		return bit_ceiling_f<N_zero>(internal_f(XTAL_REF_(f)));
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(alpha_type const f)
	noexcept -> auto
	{
		return bit_floor_f<N_zero>(f*diplo_1*dnsilon_1);
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(aphex_type const &f)
	noexcept -> auto
	{
		return bit_ceiling_f<N_zero>(dot_f(f)) >> 1;
	}



	///\returns the fractional component of `x` as a full-width `delta_type`.

	template <integer_q Y=delta_type>
	XTAL_DEF_(short)
	XTAL_SET bit_fraction_f(real_number_q auto const x)
	noexcept -> Y
	{
		XTAL_LET X_width = sizeof(x), X_depth = X_width << 3;
		XTAL_LET Y_width = sizeof(Y), Y_depth = Y_width << 3;
		XTAL_IF0
		XTAL_0IF (X_width != full.width) {
			return realize<X_width>::template bit_fraction_f<Y>(x);
		}
		//\
		XTAL_0IF (true) {
		XTAL_0IF_(consteval) {
			XTAL_LET N_exp = unit.mark + fraction.depth - Y_depth;

			auto o = _xtd::bit_cast<sigma_type>(x);
			sigma_type const _o = S_::bit_sign_f(o);
			sigma_type        x = o << 1;
			sigma_type const  i = x != 0;

			x >>= fraction.depth + 1;
			x  -= N_exp&-i;
			delta_type const x_dn = -x&S_::bit_sign_f(x);
			delta_type const x_up =  x + x_dn;

			o  &=        fraction. mask;
			o  |=   i << fraction.depth;
			o <<=   x_up;
			o >>=   x_dn;
			o  +=   o&sigma_1;
			o  ^=  _o;
			o  -=  _o;
			return _xtd::bit_cast<delta_type>(o);
		}
		XTAL_0IF_(else) {
			auto y = x - round_f(x); y *= diplo_n<Y_depth>;
			return _xtd::bit_cast<Y>(static_cast<_std::make_signed_t<Y>>(y));
		}
	}
	template <class Y=_std::complex<delta_type>>
	XTAL_DEF_(short)
	XTAL_SET bit_fraction_f(complex_number_q auto const &x)
	noexcept -> Y
	{
		using V = typename Y::value_type;
		return {bit_fraction_f<V>(x.real()), bit_fraction_f<V>(x.imag())};
	}
	
	template <real_number_q Y=alpha_type>
	XTAL_DEF_(short)
	XTAL_SET fraction_f(integer_q auto const &x)
	noexcept -> Y
	{
		XTAL_LET X_width = sizeof(x), X_depth = X_width << 3;
		XTAL_LET Y_width = sizeof(Y), Y_depth = Y_width << 3;
		XTAL_IF0
		XTAL_0IF (X_width != full.width) {
			return realize<X_width>::template fraction_f<Y>(x);
		}
		XTAL_0IF_(else) {
			return realize<Y_width>::haplo_f(full.depth)*realize<Y_width>::alpha_f(delta_f(x));
		}
	}
	template <class Y=_std::complex<alpha_type>, integer_q X>
	XTAL_DEF_(short)
	XTAL_SET fraction_f(_std::complex<X> const &x)
	noexcept -> Y
	{
		using V = typename Y::value_type;
		return {fraction_f<V>(x.real()), fraction_f<V>(x.imag())};
	}

	XTAL_DEF_(short)
	XTAL_SET fraction_f(alpha_type const &f)
	noexcept -> alpha_type
	{
		return static_cast<alpha_type>(bit_fraction_f(f))*haplo_f(full.depth);
	}

	static_assert(fraction_f( 2.25) ==  0.25);
	static_assert(fraction_f( 1.25) ==  0.25);
	static_assert(fraction_f( 0.25) ==  0.25);
	static_assert(fraction_f( 0.75) == -0.25);
	static_assert(fraction_f( 1.75) == -0.25);
	static_assert(fraction_f( 2.75) == -0.25);

	static_assert(fraction_f(-2.25) == -0.25);
	static_assert(fraction_f(-1.25) == -0.25);
	static_assert(fraction_f(-0.25) == -0.25);
	static_assert(fraction_f(-0.75) ==  0.25);
	static_assert(fraction_f(-1.75) ==  0.25);
	static_assert(fraction_f(-2.75) ==  0.25);


	XTAL_DEF_(short)
	XTAL_SET factorial_f(sigma_type n)
	noexcept -> sigma_type
	{
		auto m{n}; for (; --n; m *= n);
		return m;
	}
	template <int N>
	XTAL_DEF_(short)
	XTAL_SET factorial_f()
	noexcept -> alpha_type
	{
		XTAL_IF0
		XTAL_0IF (0 == N) {return one;}
		XTAL_0IF (0 <  N) {return     factorial_f((sigma_type) N);}
		XTAL_0IF (N <  0) {return one/factorial_f((sigma_type)-N);}
	}

	static_assert(factorial_f(5) == 120);


////////////////////////////////////////////////////////////////////////////////

	///\returns the `target` to `N_zoom` bits of precision after the decimal. \

	template <int N_zoom=0>
	XTAL_DEF_(verbatim)
	XTAL_SET trim_f(alpha_type target)
	noexcept -> alpha_type
	{
		delta_type constexpr N_unzoom = 0 < N_zoom? N_zoom - fraction.depth: N_zoom - 1;
		alpha_type constexpr N_minima = diplo_f(N_unzoom)*_std::numeric_limits<alpha_type>::min();
		target *= N_minima;
		target /= N_minima;
		return target;
	}
	static_assert(trim_f<2>(patio_f(2, 1)) == 6.25);
	static_assert(trim_f<3>(patio_f(1, 1)) == 3.125);
	static_assert(trim_f<4>(patio_f(1, 2)) == 1.5625);

	template <int N_zoom=fraction.depth - 1>
	XTAL_DEF_(verbatim)
	XTAL_SET trim_f(aphex_type const &target)
	noexcept -> aphex_type
	{
		alpha_type const x = trim_f<N_zoom>(target.real());
		alpha_type const y = trim_f<N_zoom>(target.imag());
		return aphex_type{x, y};
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
};


}///////////////////////////////////////////////////////////////////////////////

template <class ...Ts>
struct   operate
:	complete_t<_detail::realize<sizeof(absolve_u<Ts...>)>>
{
};
template <class ...Ts> requires seek_constant_q<Ts...>
struct   operate<Ts...>
:	complete_t<_detail::realize<sizeof(absolve_u<Ts>)>...>::template widen<seek_constant_n<Ts...>>
{
};
using operating = operate<size_type>;

static_assert(same_q<size_type, typename operating::sigma_type>);
static_assert(sizeof(size_type) == sizeof(typename operating::sigma_type));
static_assert(sizeof(size_type) == sizeof(typename operating::delta_type));
static_assert(sizeof(size_type) == sizeof(typename operating::alpha_type));


static_assert(operating::full.width == operating::template widen<1>::full.width);


///////////////////////////////////////////////////////////////////////////////

///\see `operating::trim_f`. \

template <auto ...N_etc>
XTAL_SET computrim_f = []<class T>(T &&t)
XTAL_0FN_(operate<T>::template trim_f<N_etc...>(XTAL_REF_(t)));


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
