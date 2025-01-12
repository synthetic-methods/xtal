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
	using       _zed =  constant_t<true>;
//	using  iota_type =                               _std::int4_t;
	using delta_type = _std::  make_signed_t<XTAL_STD_(int,   0)>;
	using sigma_type = _std::make_unsigned_t<XTAL_STD_(int,   0)>;
//	using alpha_type =                       XTAL_STD_(float, 0) ;
//	using aphex_type = _std::complex<alpha_type>;

	XTAL_SET_(sigma_type) N_exponent = 3;
	XTAL_SET_(sigma_type) N_fraction = 4;

	template <int N_pow, class _=void> struct   expound;
	template <           class _     > struct   expound<2, _> : constant_t<(sigma_type) 0x80U> {};
	template <           class _     > struct   expound<3, _> : constant_t<(sigma_type) 0x51U> {};
	template <int N_pow              > XTAL_SET expound_n = expound<N_pow, void>::value;

};
template <>
struct recognize<(1U<<1U)>
{
	using       _zed =  constant_t<true>;
	using  iota_type = _std::  make_signed_t<XTAL_STD_(int,   0)>;
	using delta_type = _std::  make_signed_t<XTAL_STD_(int,   1)>;
	using sigma_type = _std::make_unsigned_t<XTAL_STD_(int,   1)>;
//	using alpha_type =                       XTAL_STD_(float, 1) ;
//	using aphex_type =  _std::complex<alpha_type>;

	XTAL_SET_(sigma_type) N_exponent =  5;
	XTAL_SET_(sigma_type) N_fraction = 10;

	template <int N_pow, class _=void> struct   expound;
	template <           class _     > struct   expound<2, _> : constant_t<(sigma_type) 0x8000U> {};
	template <           class _     > struct   expound<3, _> : constant_t<(sigma_type) 0x4CE3U> {};
	template <int N_pow              > XTAL_SET expound_n = expound<N_pow, void>::value;

};
#if 0x20 <= XTAL_SYS_(CPU)
template <>
struct recognize<(1U<<2U)>
{
	using       _zed =  constant_t<true>;
	using  iota_type = _std::  make_signed_t<XTAL_STD_(int,   1)>;
	using delta_type = _std::  make_signed_t<XTAL_STD_(int,   2)>;
	using sigma_type = _std::make_unsigned_t<XTAL_STD_(int,   2)>;
	using alpha_type =                       XTAL_STD_(float, 2) ;
	using aphex_type = _std::complex<alpha_type>;

	XTAL_SET_(sigma_type) N_exponent =  8;
	XTAL_SET_(sigma_type) N_fraction = 23;

#ifdef FP_FAST_FMAF
	XTAL_SET_(sigma_type) N_fused = 0b1;
#else
	XTAL_SET_(sigma_type) N_fused = 0b0;
#endif

	using mt19937_t = _std::mersenne_twister_engine<sigma_type, 32, 624, 397, 31
	,	0x9908B0DFU, 11
	,	0xFFFFFFFFU,  7
	,	0x9D2C5680U, 15
	,	0xEFC60000U, 18
	,	0x6C078965U
	>;

	template <int N_pow, class _=void> struct   expound;
	template <           class _     > struct   expound<2, _> : constant_t<(sigma_type) 0x80000000U> {};
	template <           class _     > struct   expound<3, _> : constant_t<(sigma_type) 0x4546B3DBU> {};
	template <int N_pow              > XTAL_SET expound_n = expound<N_pow, void>::value;

};
#endif
#if 0x40 <= XTAL_SYS_(CPU)
template <>
struct recognize<(1U<<3U)>
{
	using       _zed =  constant_t<true>;
	using  iota_type = _std::  make_signed_t<XTAL_STD_(int,   2)>;
	using delta_type = _std::  make_signed_t<XTAL_STD_(int,   3)>;
	using sigma_type = _std::make_unsigned_t<XTAL_STD_(int,   3)>;
	using alpha_type =                       XTAL_STD_(float, 3) ;
	using aphex_type = _std::complex<alpha_type>;

	XTAL_SET_(sigma_type) N_exponent = 11;
	XTAL_SET_(sigma_type) N_fraction = 52;

#ifdef FP_FAST_FMA
	XTAL_SET_(sigma_type) N_fused = 0b1;
#else
	XTAL_SET_(sigma_type) N_fused = 0b0;
#endif

	using mt19937_t = _std::mersenne_twister_engine<sigma_type, 64, 312, 156, 31
	,	0xB5026F5A'A96619E9U, 29
	,	0x55555555'55555555U, 17
	,	0x71D67FFF'EDA60000U, 37
	,	0xFFF7EEE0'00000000U, 43
	,	0x5851F42D'4C958000U
	>;

	template <int N_pow, class _=void> struct   expound;
	template <           class _     > struct   expound<2, _> : constant_t<(sigma_type) 0x80000000'00000000U> {};
	template <           class _     > struct   expound<3, _> : constant_t<(sigma_type) 0x383D9170'B85FF80BU> {};
	template <int N_pow              > XTAL_SET expound_n = expound<N_pow, void>::value;

};
#endif
//\todo\
Allow for 128-bit. \

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

	XTAL_SET_(delta_type) delta_0{0};
	XTAL_SET_(delta_type) delta_1{1};

	XTAL_SET_(sigma_type) sigma_0{0};
	XTAL_SET_(sigma_type) sigma_1{1};

	XTAL_SET_(sigma_type) N_width = N_size;
	XTAL_SET_(sigma_type) N_depth = N_size << 3U;

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

		XTAL_DEF_(short,static) XTAL_LET flag_f(sigma_type const m=0)                       noexcept -> sigma_type {return one << (m&(N_depth - one));};
		XTAL_DEF_(short,static) XTAL_LET mark_f(sigma_type const m=0)                       noexcept -> sigma_type {return        ~-flag_f(m)        ;};
		XTAL_DEF_(short,static) XTAL_LET mask_f(sigma_type const m=0, sigma_type const n=0) noexcept -> sigma_type {return          mark_f(m) << n   ;};

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


	XTAL_DEF_(short) XTAL_SET internal_f(     delta_type i) noexcept -> auto {return i;}
	XTAL_DEF_(short) XTAL_SET internal_f(     sigma_type i) noexcept -> auto {return i;}
	XTAL_DEF_(short) XTAL_SET internal_f( ordinal_q auto i) noexcept -> auto {return static_cast<delta_type>(i);}
	XTAL_DEF_(short) XTAL_SET internal_f(cardinal_q auto i) noexcept -> auto {return static_cast<sigma_type>(i);}


////////////////////////////////////////////////////////////////////////////////

	///\returns the remainder from the maximal power of `N`, \
	which is zero if the argument is a power of `N`. \

	///\note\
	Currently only supports `N={2,3}`.

	template <sigma_type N>
	XTAL_DEF_(short)
	XTAL_SET expound_f(sigma_type u)
	noexcept -> sigma_type
	{
		//\
		if constexpr (complete_q<typename S_::template expound<N>>) {
		if constexpr (N == 2 or N == 3) {
			return S_::template expound_n<N>%u|(u == 0)|(u == 1);
		}
		else {
			return 1U;
		}
	}
	template <sigma_type N>
	XTAL_DEF_(short)
	XTAL_SET expound_f(un_q<sigma_type> auto const &value)
	noexcept -> auto
	{
		return expound_f<N>(static_cast<sigma_type>(value));
	}

	static_assert(0 != expound_f<2>( 1) and 0 != expound_f<3>( 1));
	static_assert(0 == expound_f<2>( 2) and 0 != expound_f<3>( 2));
	static_assert(0 != expound_f<2>( 3) and 0 == expound_f<3>( 3));
	static_assert(0 == expound_f<2>( 4) and 0 != expound_f<3>( 4));
	static_assert(0 == expound_f<2>( 8) and 0 != expound_f<3>( 8));
	static_assert(0 != expound_f<2>( 9) and 0 == expound_f<3>( 9));
	static_assert(0 == expound_f<2>(16) and 0 != expound_f<3>(16));
	static_assert(0 != expound_f<2>(27) and 0 == expound_f<3>(27));


///////////////////////////////////////////////////////////////////////////////

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

	template <int N_side=0> requires in_n<N_side, 1, 0, -1>
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
	
	template <int N_side=0> requires in_n<N_side, 1, 0, -1>
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
	requires un_n<full.width, sizeof(i)>
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
	requires un_n<full.width, sizeof(i)>
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
			sigma_type const  z =      one == i;
			sigma_type const _z = unit.depth&-z;
			return _std::bit_width(i) - (one << _z) + z;// 0 -> -1023
			/*/
			return _std::bit_width(i) - one;// 0 -> -1
			/***/
		}
		else {
			XTAL_LET Z =         -1;
			XTAL_LET N = N_zero - Z;
			i  =  bit_floor_f(i);
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
	requires un_n<full.width, sizeof(i)>
	{
		return bit_ceiling_f<N_zero>(internal_f(i));
	}
	template <int N_zero=-1>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(sigma_type i)
	noexcept -> sigma_type
	{
		if constexpr (N_zero == -1) {
			sigma_type const z = i == zero;
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
		#pragma inline
		for (sigma_type m = -1, i = N_depth; i >>= 1;) {
			m ^= m<<i;
			u = (u&m)<<i | (u&~m)>>i;
		}
		u >>= N_depth - subdepth; assert(0 < subdepth and subdepth <= N_depth);
		return u;
	}
	template <int N_subdepth=0>
	XTAL_DEF_(short)
	XTAL_SET bit_reverse_f(sigma_type u)
	noexcept -> sigma_type
	{
		sigma_type constexpr subdepth = 0 < N_subdepth? N_subdepth: N_depth;
		return bit_reverse_f(u, subdepth);
	}

	template <int N_subdepth=0>
	XTAL_DEF_(short)
	XTAL_SET bit_reverse_f(integral_q auto i)
	noexcept -> auto
	requires un_n<full.width, sizeof(i)>
	{
		return bit_reverse_f<N_subdepth>(internal_f(i));
	}
	XTAL_DEF_(short)
	XTAL_SET bit_reverse_f(integral_q auto i, sigma_type const &subdepth)
	noexcept -> auto
	requires un_n<full.width, sizeof(i)>
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
	
	using S_::  delta_0;
	using S_::  delta_1;

	using S_::  sigma_0;
	using S_::  sigma_1;

	using typename S_::   iota_type;
	using typename S_::  delta_type;
	using typename S_::  sigma_type;
	using typename S_::  alpha_type;
	using typename S_::  aphex_type;
	using typename S_::mt19937_t;

	XTAL_SET_(alpha_type)  alpha_0{0};
	XTAL_SET_(alpha_type)  alpha_1{1};
	
	XTAL_SET_(aphex_type)  aphex_0{0, 0};
	XTAL_SET_(aphex_type)  aphex_1{1, 0};
	XTAL_SET_(aphex_type)  aphex_i{0, 1};

	XTAL_SET_(aphex_type) square_0{0, 0};
	XTAL_SET_(aphex_type) square_1{1, 1};
	
	XTAL_SET_(aphex_type) circle_0 = square_0*0.7071067811865475244008443621048490393L;
	XTAL_SET_(aphex_type) circle_1 = square_1*0.7071067811865475244008443621048490393L;

	XTAL_DEF_(short) XTAL_SET internal_f(alpha_type      i) noexcept -> auto {return                         i ;}
	XTAL_DEF_(short) XTAL_SET internal_f(    real_q auto i) noexcept -> auto {return static_cast<alpha_type>(i);}
	XTAL_DEF_(short) XTAL_SET internal_f(integral_q auto i) noexcept -> auto {return          S_::internal_f(i);}


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
		XTAL_0IF (same_q<delta_type, Q>) {return                                 XTAL_REF_(o)  ;}
		XTAL_0IF (same_q<sigma_type, Q>) {return      _std::bit_cast<delta_type>(XTAL_REF_(o)) ;}
		XTAL_0IF (same_q<alpha_type, Q>) {return         static_cast<delta_type>(XTAL_REF_(o)) ;}
		XTAL_0IF (        cardinal_q<Q>) {return delta_f(static_cast<sigma_type>(XTAL_REF_(o)));}
	//	XTAL_0IF (         ordinal_q<Q>) {return delta_f(static_cast<delta_type>(XTAL_REF_(o)));}
		XTAL_0IF (            real_q<Q>) {return delta_f(static_cast<alpha_type>(XTAL_REF_(o)));}
		XTAL_0IF_(else)                  {return         static_cast<delta_type>(XTAL_REF_(o)) ;}
	}
	XTAL_DEF_(short)
	XTAL_SET sigma_f(auto &&o)
	noexcept -> sigma_type
	{
		using Q = XTAL_ALL_(o);
		XTAL_IF0
		XTAL_0IF (same_q<delta_type, Q>) {return      _std::bit_cast<sigma_type>(XTAL_REF_(o)) ;}
		XTAL_0IF (same_q<sigma_type, Q>) {return                                 XTAL_REF_(o)  ;}
		XTAL_0IF (same_q<alpha_type, Q>) {return                 sigma_f(delta_f(XTAL_REF_(o)));}
	//	XTAL_0IF (        cardinal_q<Q>) {return sigma_f(static_cast<sigma_type>(XTAL_REF_(o)));}
		XTAL_0IF (         ordinal_q<Q>) {return sigma_f(static_cast<delta_type>(XTAL_REF_(o)));}
		XTAL_0IF (            real_q<Q>) {return sigma_f(static_cast<alpha_type>(XTAL_REF_(o)));}
		XTAL_0IF_(else)                  {return         static_cast<sigma_type>(XTAL_REF_(o)) ;}
	}
	XTAL_DEF_(short)
	XTAL_SET alpha_f(auto &&o)
	noexcept -> alpha_type
	{
		using Q = XTAL_ALL_(o);
		XTAL_IF0
		XTAL_0IF (same_q<delta_type, Q>) {return         static_cast<alpha_type>(XTAL_REF_(o)) ;}
		XTAL_0IF (same_q<sigma_type, Q>) {return                 alpha_f(delta_f(XTAL_REF_(o)));}
		XTAL_0IF (same_q<alpha_type, Q>) {return                                 XTAL_REF_(o)  ;}
		XTAL_0IF (        cardinal_q<Q>) {return alpha_f(static_cast<sigma_type>(XTAL_REF_(o)));}
		XTAL_0IF (         ordinal_q<Q>) {return alpha_f(static_cast<delta_type>(XTAL_REF_(o)));}
	//	XTAL_0IF (            real_q<Q>) {return         static_cast<alpha_type>(XTAL_REF_(o)) ;}
		XTAL_0IF_(else)                  {return         static_cast<alpha_type>(XTAL_REF_(o)) ;}
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

	///\returns the `constexpr` equivalent of `std:pow(2.0, n_zoom)*(o_silon)`. \

	XTAL_DEF_(short)
	XTAL_SET diplo_f(alpha_type n_zoom, alpha_type o_silon)
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
	XTAL_SET diplo_f(delta_type n_zoom, alpha_type o_silon)
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
	XTAL_SET diplo_f(sigma_type n_zoom, alpha_type o_silon)
	noexcept -> alpha_type
	{
		return diplo_f(_xtd::bit_cast<delta_type>(n_zoom), o_silon);
	}
	XTAL_DEF_(short) XTAL_SET diplo_f(auto n_zoom, alpha_type o_silon)
	noexcept -> auto
	{
		return diplo_f(internal_f(XTAL_REF_(n_zoom)), o_silon);
	}

	template <int N_silon=0>
	XTAL_DEF_(short)
	XTAL_SET diplo_f(auto const &n_zoom)
	noexcept -> alpha_type
	{
		XTAL_LET o_silon = one/alpha_type{one << fraction.depth - magnum_n<N_silon>};
		XTAL_IF0
		XTAL_0IF (0 < N_silon) {return diplo_f(n_zoom, one + alpha_type{0.50}/o_silon);}
		XTAL_0IF (N_silon < 0) {return diplo_f(n_zoom, one - alpha_type{0.25}/o_silon);}
		XTAL_0IF_(else)        {return diplo_f(n_zoom,       alpha_type{1.00}        );}
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
	XTAL_SET ratio_f(alpha_type n_num, alpha_type n_nom=1)
	noexcept -> alpha_type
	{
		static_assert(in_n<N_pow, 1, 0, -1>);
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

	template <int N_pow=1> requires in_n<N_pow, 1, 0, -1>
	XTAL_DEF_(short)
	XTAL_SET patio_f(alpha_type n_num, alpha_type n_nom=1)
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
	XTAL_SET assigned_f(integral_q auto i)
	noexcept -> alpha_type
	requires un_n<full.width, sizeof(i)>
	{
		return assigned_f(S_::internal_f(i));
	}
	XTAL_DEF_(short)
	XTAL_SET assigned_f(sigma_type u)
	noexcept -> alpha_type
	{
		//\
		if constexpr (IEC&559) {
		if constexpr (false) {
			u <<= positive.depth;
			u  ^= sign.mask|unit.mask;
			return _xtd::bit_cast<alpha_type>(u);
		}
		else {
			return assigned_f(_xtd::bit_cast<delta_type>(u&one));
		}
	}
//	static_assert(assigned_f((sigma_type)  1) ==  1.0);
//	static_assert(assigned_f((sigma_type)  0) == -1.0);
//	static_assert(assigned_f((sigma_type) -1) ==  1.0);
	XTAL_DEF_(short)
	XTAL_SET assigned_f(delta_type u)
	noexcept -> alpha_type
	{
		u  -= 1;
		u >>= positive.depth;
		//\
		if constexpr (IEC&559) {
		if constexpr (false) {
			u &= sign.mask;
			u |= unit.mask;
			return _xtd::bit_cast<alpha_type>(u);
		}
		else {
			u |= 1;
			return    static_cast<alpha_type>(u);
		}
	}
//	static_assert(assigned_f((delta_type)  1) ==  1.0);
//	static_assert(assigned_f((delta_type)  0) ==  1.0);
//	static_assert(assigned_f((delta_type) -1) == -1.0);

	///\returns the sign of `value`. \

	XTAL_DEF_(short)
	XTAL_SET assigned_f(alpha_type value)
	noexcept -> alpha_type
	{
		return _xtd::copysign(alpha_1, value);
	}
	static_assert(assigned_f((alpha_type)  1) ==  1.0);
	static_assert(assigned_f((alpha_type)  0) ==  1.0);
	static_assert(assigned_f((alpha_type) -1) == -1.0);


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
	XTAL_SET designed_f(integral_q auto i)
	noexcept -> decltype(auto)
	requires un_n<full.width, sizeof(i)>
	{
		return S_::template designed_f<N_side>(i);
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
	requires in_n<sizeof(target), sizeof(source)>
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
	XTAL_SET resigned_f(alpha_type target, alpha_type source=1)
	noexcept -> alpha_type
	{
		return _xtd::copysign(target, source);
	}
	XTAL_DEF_(short)
	XTAL_SET resigned_f(alpha_type target, delta_type source=0)
	noexcept -> alpha_type
	{
		source &= sign.mask;
		source |= unit.mask;
		return target*_xtd::bit_cast<alpha_type>(source);
	}


////////////////////////////////////////////////////////////////////////////////

	XTAL_DEF_(short)
	XTAL_SET scientific_f(alpha_type f)
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
	XTAL_SET bit_floor_f(integral_q auto value)
	noexcept -> auto
	requires un_n<full.width, sizeof(value)>
	{
		return S_::template bit_floor_f<N_zero>(value);
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_floor_f(real_q auto value)
	noexcept -> auto
	requires un_n<full.width, sizeof(value)>
	{
		return bit_floor_f<N_zero>(internal_f(value));
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_floor_f(alpha_type const value)
	noexcept -> auto
	{
		XTAL_LET Z = -unit.mark;
		XTAL_LET N = N_zero - Z << unit.shift;

		auto n = _xtd::bit_cast<sigma_type>(value);
		n &= ~sign.mask;
		n -=  unit.mask;
		n += N&S_::bit_sign_f(n);
		return _xtd::bit_cast<delta_type>(n) >> unit.shift;
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_floor_f(aphex_type const value)
	noexcept -> auto
	{
		return bit_floor_f<N_zero>(norm(value)) >> 1;
	}

//	using S_::bit_ceiling_f;
	template <int N_zero=-1>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(integral_q auto &&i)
	noexcept -> auto
	requires un_n<full.width, sizeof(i)>
	{
		return S_::template bit_ceiling_f<N_zero>(XTAL_REF_(i));
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(real_q auto &&f)
	noexcept -> auto
	requires un_n<full.width, sizeof(f)>
	{
		return bit_ceiling_f<N_zero>(internal_f(XTAL_REF_(f)));
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(alpha_type const &f)
	noexcept -> auto
	{
		return bit_floor_f<N_zero>(f*diplo_1*dnsilon_1);
	}
	template <int N_zero=-int{unit.mark}>
	XTAL_DEF_(short)
	XTAL_SET bit_ceiling_f(aphex_type const &f)
	noexcept -> auto
	{
		return bit_ceiling_f<N_zero>(norm(f)) >> 1;
	}



	///\returns the fractional component of `x` as a full-width `delta_type`.

	template <integral_q Y=delta_type>
	XTAL_DEF_(short)
	XTAL_SET bit_fraction_f(real_q auto const x)
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
			XTAL_LET N_exp = exponent.shift;
			XTAL_LET M_exp = unit.mark + unit.shift - Y_depth;
			XTAL_LET M_sgn = sign.mask;

			auto o = _xtd::bit_cast<sigma_type>(x);

			delta_type o_ = o &  M_sgn; o  ^= o_; o_ >>= sign.shift;
			sigma_type x  = o >> N_exp; x  -= M_exp;
			sigma_type u  = x != 0    ; u <<= fraction.depth;

			auto const x_on = ~S_::bit_sign_f(x);
			auto const x_up = x_on & x;
			auto const x_dn = x_up - x;

			o  &=  fraction.mask;
			o  ^=  u;
			o <<=  x_up;
			o >>=  x_dn;
		//	o  |=  1;
			o  ^=  o_;
			o  -=  o_;
			return _xtd::bit_cast<delta_type>(o);
		}
		XTAL_0IF_(else) {
			auto y = x - round(x); y *= diplo_n<Y_depth>;
			return _xtd::bit_cast<Y>(static_cast<_std::make_signed_t<Y>>(y));
		}
	}
	template <class Y=_std::complex<delta_type>>
	XTAL_DEF_(short)
	XTAL_SET bit_fraction_f(complex_q auto const &x)
	noexcept -> Y
	{
		using V = typename Y::value_type;
		return {bit_fraction_f<V>(x.real()), bit_fraction_f<V>(x.imag())};
	}
	
	template <real_q Y=alpha_type>
	XTAL_DEF_(short)
	XTAL_SET fraction_f(integral_q auto const &x)
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
	template <class Y=_std::complex<alpha_type>, integral_q X>
	XTAL_DEF_(short)
	XTAL_SET fraction_f(_std::complex<X> const &x)
	noexcept -> Y
	{
		using V = typename Y::value_type;
		return {fraction_f<V>(x.real()), fraction_f<V>(x.imag())};
	}

	XTAL_DEF_(short)
	XTAL_SET fraction_f(alpha_type f)
	noexcept -> alpha_type
	{
		return static_cast<alpha_type>(bit_fraction_f(f))*haplo_f(full.depth);
	}

//	static_assert(fraction_f( 2.25) ==  0.25);
//	static_assert(fraction_f( 1.25) ==  0.25);
//	static_assert(fraction_f( 0.25) ==  0.25);
//	static_assert(fraction_f( 0.75) == -0.25);
//	static_assert(fraction_f( 1.75) == -0.25);
//	static_assert(fraction_f( 2.75) == -0.25);
//
//	static_assert(fraction_f(-2.25) == -0.25);
//	static_assert(fraction_f(-1.25) == -0.25);
//	static_assert(fraction_f(-0.25) == -0.25);
//	static_assert(fraction_f(-0.75) ==  0.25);
//	static_assert(fraction_f(-1.75) ==  0.25);
//	static_assert(fraction_f(-2.75) ==  0.25);


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

//static_assert(same_q<size_type, typename operating::sigma_type>);
//static_assert(sizeof(size_type) == sizeof(typename operating::sigma_type));
//static_assert(sizeof(size_type) == sizeof(typename operating::delta_type));
//static_assert(sizeof(size_type) == sizeof(typename operating::alpha_type));


static_assert(operating::full.width == operating::template widen<1>::full.width);


///////////////////////////////////////////////////////////////////////////////

///\see `operating::trim_f`. \

template <auto ...N_etc>
XTAL_SET computrim_f = []<class T>(T &&t)
XTAL_0FN_(operate<T>::template trim_f<N_etc...>(XTAL_REF_(t)));


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
