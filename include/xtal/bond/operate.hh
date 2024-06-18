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
struct recognize : recognize<(N_size >> 1)>
{
	using _zed = nominal_t<false>;

};
template <>
struct recognize<(1<<0)>
{
	using       _zed =        nominal_t<true>;
//	using  iota_type =           _std::int4_t;
	using delta_type =    signed XTAL_INT_(0);
	using sigma_type =  unsigned XTAL_INT_(0);
//	using alpha_type =           XTAL_FLT_(0);
//	using aphex_type = _std::complex<alpha_type>;

	template <auto ...Ns> static constexpr delta_type delta_n = lateral_n<delta_type(Ns)...>;
	template <auto ...Ns> static constexpr sigma_type sigma_n = lateral_n<sigma_type(Ns)...>;

	static constexpr sigma_type N_exponent = 3;
	static constexpr sigma_type N_fraction = 4;

};
template <>
struct recognize<(1<<1)>
{
	using       _zed =        nominal_t<true>;
	using  iota_type =    signed XTAL_INT_(0);
	using delta_type =    signed XTAL_INT_(1);
	using sigma_type =  unsigned XTAL_INT_(1);
//	using alpha_type =           XTAL_FLT_(1);
//	using aphex_type = _std::complex<alpha_type>;

	template <auto ...Ns> static constexpr delta_type delta_n = lateral_n<delta_type(Ns)...>;
	template <auto ...Ns> static constexpr sigma_type sigma_n = lateral_n<sigma_type(Ns)...>;

	static constexpr sigma_type N_exponent =  5;
	static constexpr sigma_type N_fraction = 10;

};
template <>
struct recognize<(1<<2)>
{
	using       _zed =        nominal_t<true>;
	using  iota_type =    signed XTAL_INT_(1);
	using delta_type =    signed XTAL_INT_(2);
	using sigma_type =  unsigned XTAL_INT_(2);
	using alpha_type =           XTAL_FLT_(2);
	using aphex_type = _std::complex<alpha_type>;

	using aphex_1x1_t = simde_float32x2_t;
	using alpha_2x1_t = simde_float32x2_t;   // v(?:ld|st)1_f32
	using alpha_2x2_t = simde_float32x2x2_t; // v(?:ld|st)2_f32

	template <auto ...Ns> using                       delta_u = lateral_t<(delta_type) Ns...>;
	template <auto ...Ns> using                       sigma_u = lateral_t<(sigma_type) Ns...>;
	template <auto ...Ns> static constexpr delta_type delta_n = lateral_n<(delta_type) Ns...>;
	template <auto ...Ns> static constexpr sigma_type sigma_n = lateral_n<(sigma_type) Ns...>;

	static constexpr sigma_type N_exponent =  8;
	static constexpr sigma_type N_fraction = 23;

#ifdef FP_FAST_FMAF
	static constexpr sigma_type N_fused = 0b1;
#else
	static constexpr sigma_type N_fused = 0b0;
#endif

	using mt19937_t = _std::mersenne_twister_engine<sigma_type, 32, 624, 397, 31
	,	sigma_n<0x9908B0DF>, 11
	,	sigma_n<0xFFFFFFFF>,  7
	,	sigma_n<0x9D2C5680>, 15
	,	sigma_n<0xEFC60000>, 18
	,	sigma_n<0x6C078965>
	>;

	template <int _, int N_pow> struct   root;
	template <int _> struct root<_,-1> : sigma_u<0x7EEEEEEE> {};
	template <int _> struct root<_,-2> : sigma_u<0x5F375A86> {};

	template <int N_pow>
	static constexpr sigma_type root_n = root<0, N_pow>::value;
//	static constexpr sigma_type root_1 = sigma_n<0x7EEEEEEE>;
//	static constexpr sigma_type root_2 = sigma_n<0x5F375A86>;

	template <int N_pow=-1>
	XTAL_DEF_(return,inline,static)
	XTAL_LET root_e(alpha_type const &w)
	XTAL_0EX -> alpha_type
	{
		static_assert(N_pow <  -0);
		if constexpr (N_pow == -1) {
			return simde_vrecpes_f32(w);
		}	else
		if constexpr (N_pow == -2) {
			return simde_vrsqrtes_f32(w);
		}
	}
	template <int N_pow=-1>
	XTAL_DEF_(return,inline,static)
	XTAL_LET root_e(alpha_type const &w, alpha_type const &n)
	XTAL_0EX -> alpha_type
	{
		static_assert(N_pow <  -0);
		if constexpr (N_pow == -1) {
			return simde_vrecpss_f32(w, n);
		}	else
		if constexpr (N_pow == -2) {
			return simde_vrsqrtss_f32(w, n*n);
		}
	}

};
template <>
struct recognize<(1<<3)>
{
	using   _zed =           nominal_t< true>;
	using  iota_type =    signed XTAL_INT_(2);
	using delta_type =    signed XTAL_INT_(3);
	using sigma_type =  unsigned XTAL_INT_(3);
	using alpha_type =           XTAL_FLT_(3);
	using aphex_type = _std::complex<alpha_type>;

	using aphex_1x1_t = simde_float64x2_t;
	using alpha_2x1_t = simde_float64x2_t;   // v(?:ld|st)1q_f64
	using alpha_2x2_t = simde_float64x2x2_t; // v(?:ld|st)1q_f64_x2

	template <auto ...Ns> using                       delta_u = lateral_t<(delta_type) Ns...>;
	template <auto ...Ns> using                       sigma_u = lateral_t<(sigma_type) Ns...>;
	template <auto ...Ns> static constexpr delta_type delta_n = lateral_n<(delta_type) Ns...>;
	template <auto ...Ns> static constexpr sigma_type sigma_n = lateral_n<(sigma_type) Ns...>;

	static constexpr sigma_type N_exponent = 11;
	static constexpr sigma_type N_fraction = 52;

#ifdef FP_FAST_FMA
	static constexpr sigma_type N_fused = 0b1;
#else
	static constexpr sigma_type N_fused = 0b0;
#endif

	using mt19937_t = _std::mersenne_twister_engine<sigma_type, 64, 312, 156, 31
	,	sigma_n<0xB5026F5A, 0xA96619E9>, 29
	,	sigma_n<0x55555555, 0x55555555>, 17
	,	sigma_n<0x71D67FFF, 0xEDA60000>, 37
	,	sigma_n<0xFFF7EEE0, 0x00000000>, 43
	,	sigma_n<0x5851F42D, 0x4C958000>
	>;

	template <int _, int N_pow> struct   root;
	template <int _> struct root<_,-1> : sigma_u<0x7EEEEEEE, 0xEEEEEEEE> {};
	template <int _> struct root<_,-2> : sigma_u<0x5FE6EB50, 0xC7B537A9> {};
	
	template <int N_pow>
	static constexpr sigma_type root_n = root<0, N_pow>::value;

	template <int N_pow=-1>
	XTAL_DEF_(return,inline,static)
	XTAL_LET root_e(alpha_type const &w)
	XTAL_0EX -> alpha_type
	{
		static_assert(N_pow <  -0);
		if constexpr (N_pow == -1) {
			return simde_vrecped_f64(w);
		}	else
		if constexpr (N_pow == -2) {
			return simde_vrsqrted_f64(w);
		}
	}
	template <int N_pow=-1>
	XTAL_DEF_(return,inline,static)
	XTAL_LET root_e(alpha_type const &w, alpha_type const &n)
	XTAL_0EX -> alpha_type
	{
		static_assert(N_pow <  -0);
		if constexpr (N_pow == -1) {
			return simde_vrecpsd_f64(w, n);
		}	else
		if constexpr (N_pow == -2) {
			return simde_vrsqrtsd_f64(w, n*n);
		}
	}

};

template <size_type N_size>
concept recognized_q = recognize<N_size>::_zed::value;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <size_type N_size>
struct rationalize : rationalize<(N_size >> 1)>
{
	using _zed = nominal_t<false>;

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

//	static constexpr  iota_type  iota_0 = 0,  iota_1 = 1;
	static constexpr delta_type delta_0 = 0, delta_1 = 1;
	static constexpr sigma_type sigma_0 = 0, sigma_1 = 1;

	static constexpr sigma_type N_width = N_size;
	static constexpr sigma_type N_depth = N_size << 3;

	static constexpr sigma_type N_fraction =          S_::N_fraction;
	static constexpr sigma_type N_exponent =          S_::N_exponent;
	static constexpr sigma_type N_positive = N_fraction + N_exponent;
	static constexpr sigma_type N_negative = N_positive + 1;
	static constexpr sigma_type N_unit     = N_exponent - 1;
	static constexpr sigma_type N_sign     =              1;
	static_assert(N_negative == N_depth);

	struct word
	{
		sigma_type width;
		sigma_type depth;
		sigma_type shift;
		sigma_type mark;
		sigma_type mask;

		XTAL_DEF_(return,inline,static) XTAL_LET flag_f(sigma_type const m=0)                    XTAL_0EX -> sigma_type {return N_negative <= m?  sigma_0: sigma_1 << m;};
		XTAL_DEF_(return,inline,static) XTAL_LET mark_f(sigma_type const m=0)                    XTAL_0EX -> sigma_type {return N_negative <= m? ~sigma_0: flag_f(m) - 1;};
		XTAL_DEF_(return,inline,static) XTAL_LET mask_f(sigma_type const m=0, sigma_type const n=0) XTAL_0EX -> sigma_type {return mark_f(m) << n;};

		XTAL_CON_(explicit) word(sigma_type m_depth, sigma_type n_shift=0)
		XTAL_0EX
		:	width (flag_f(m_depth))
		,	depth (m_depth)
		,	shift (n_shift)
		,	mark  (mark_f(m_depth))
		,	mask  (mask_f(m_depth, n_shift))
		{}

	};
	static constexpr word negative {N_negative};
	static constexpr word positive {N_positive};
	static constexpr word fraction {N_fraction};
	static constexpr word exponent {N_exponent, N_fraction};
	static constexpr word     unit     {N_unit, N_fraction};
	static constexpr word     sign     {N_sign, N_positive};
	static constexpr word     half {N_depth >> 1, N_depth >> 1};
	static_assert((sigma_type) ~sign.mask == positive.mask);


	template <class      T> struct internal;
	template <cardinal_q T> struct internal<T> {using type = sigma_type;};
	template < ordinal_q T> struct internal<T> {using type = delta_type;};
	template <class      T>  using internal_t = typename internal<T>::type;

	template <integral_q I> requires (sizeof(I) < N_depth)
	XTAL_DEF_(return,inline,static)
	XTAL_LET internal_f(I i)
	XTAL_0EX
	{
		return static_cast<internal_t<I>>(i);
	}


///////////////////////////////////////////////////////////////////////////////

	template <int N_side=0> requires sign_p<N_side, 0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET clamped_f(integral_q auto value)
	XTAL_0EX
	{
		XTAL_IF0
		XTAL_0IF (N_side == 0) {return                           value ;}
		XTAL_0IF (N_side != 0) {return N_side*designed_f<N_side>(value);}
	}

	///\returns the original sign of `target`, before applying the sign of `source`. \

	XTAL_DEF_(return, static)
	XTAL_LET resign_f(delta_type &target, delta_type const &source=0)
	XTAL_0EX -> delta_type
	{
		delta_type const t = target >> positive.depth;
		delta_type const s = source >> positive.depth;
		target ^= s;
		target -= s;
		return t;
	}
	///\returns the `target` magnitude with the sign of the `source`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET resigned_f(delta_type target, delta_type const &source=0)
	XTAL_0EX -> delta_type
	{
		(void) resign_f(target, source); return target;
	}


	///\returns the original sign of `target`, after making it `abs`olute.

	template <int N_side=0> requires sign_p<N_side, 0>
	XTAL_DEF_(return, static)
	XTAL_LET design_f(delta_type &target)
	XTAL_0EX -> delta_type
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
	
	template <int N_side=0> requires sign_p<N_side, 0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET designed_f(delta_type value)
	XTAL_0EX
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

	///\returns the number of bits set in `u`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_count_f(integral_q auto i)
	XTAL_0EX requires (sizeof(i) < N_width)
	{
		return bit_count_f(internal_f(i));
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_count_f(sigma_type i)
	XTAL_0EX -> sigma_type
	{
		return _std::popcount(i);
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_count_f(delta_type i)
	XTAL_0EX -> delta_type
	{
		delta_type v = design_f(i);
		delta_type u = bit_count_f((sigma_type) i);
		u ^= v;
		u -= v;
		return u;
	}


	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_floor_f(integral_q auto i)
	XTAL_0EX requires (sizeof(i) < N_width)
	{
		return bit_floor_f(internal_f(i));
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_floor_f(sigma_type i)
	XTAL_0EX -> sigma_type
	{
		sigma_type n = 0; for (; i >>= 1; ++n);
		return n;
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_floor_f(delta_type i)
	XTAL_0EX -> delta_type
	{
		delta_type v = design_f(i);
		delta_type u = bit_floor_f((sigma_type) i);
		u ^= v;
		u -= v;
		return u;
	}

	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_ceiling_f(integral_q auto i)
	XTAL_0EX requires (sizeof(i) < N_width)
	{
		return bit_ceiling_f(internal_f(i));
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_ceiling_f(sigma_type i)
	XTAL_0EX -> sigma_type
	{
		return _std::bit_width(i) - 1;
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_ceiling_f(delta_type i)
	XTAL_0EX -> delta_type
	{
		delta_type v = design_f(i);
		delta_type u = bit_ceiling_f((sigma_type) i);
		u ^= v;
		u -= v;
		return u;
	}

	///\returns the bitwise-reversal of `u`, \
	restricted to `N_subdepth` when `0 < N_subdepth < sizeof(u) << 3`. \

	///\note Requires `log2(sizeof(u) << 3)` iterations. \

	XTAL_DEF_(return,static)
	XTAL_LET bit_reverse_f(sigma_type u, sigma_type const &subdepth)
	XTAL_0EX -> sigma_type
	{
		for (sigma_type m = -1, i = N_depth; i >>= 1;) {
			m ^= m<<i;
			u = (u&m)<<i | (u&~m)>>i;
		}
		u >>= N_depth - subdepth; assert(0 < subdepth and subdepth <= N_depth);
		return u;
	}
	template <size_type N_subdepth=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_reverse_f(sigma_type const &u)
	XTAL_0EX -> sigma_type
	{
		sigma_type constexpr subdepth = 0 < N_subdepth? N_subdepth: N_depth;
		return bit_reverse_f(u, subdepth);
	}

	template <size_type N_subdepth=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_reverse_f(integral_q auto i)
	XTAL_0EX requires (sizeof(i) < N_width)
	{
		return bit_reverse_f<N_subdepth>(internal_f(i));
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET bit_reverse_f(integral_q auto i, sigma_type const &subdepth)
	XTAL_0EX requires (sizeof(i) < N_width)
	{
		return bit_reverse_f(internal_f(i), subdepth);
	}


};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <size_type N_size>
struct realize : realize<(N_size >> 1)>
{
	using _zed = nominal_t<false>;

};
template <size_type N_size> requires recognized_q<N_size>
struct realize<N_size> : rationalize<N_size>
{};
template <size_type N_size> requires recognized_q<N_size> and requires {typename recognize<N_size>::alpha_type;}
struct realize<N_size> : rationalize<N_size>
{
private:
	using S_ = rationalize<N_size>;

public:
	using S_:: negative;
	using S_:: positive;
	using S_:: fraction;
	using S_:: exponent;
	using S_::     unit;
	using S_::     sign;

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

	static constexpr alpha_type alpha_0 = 0;
	static constexpr alpha_type alpha_1 = 1;
	static constexpr aphex_type aphex_0 = {0, 0};
	static constexpr aphex_type aphex_1 = {1, 0};
	static constexpr aphex_type aphex_i = {0, 1};


	using S_::N_width;
	using S_::N_depth;
	using S_::N_fused;


	static constexpr sigma_type IEC = _std::numeric_limits<alpha_type>::is_iec559? XTAL_STD_(IEC)&60559: 0;

	XTAL_DEF_(return,static)
	XTAL_LET use_IEC()
	XTAL_0EX -> bool
	{
		return IEC&559;
	}
	XTAL_DEF_(return,static)
	XTAL_LET use_FMA()
	XTAL_0EX -> bool
	{
		return N_fused;
	}

	using default_alignment = nominal_t<(size_type) XTAL_STD_(L1)/N_width>;

#ifdef __cpp_lib_hardware_interference_size
	using constructive_alignment = nominal_t<(size_type) _std::hardware_constructive_interference_size/N_width>;
//	using  destructive_alignment = nominal_t<(size_type) _std:: hardware_destructive_interference_size/N_width>;
#else
	using constructive_alignment = default_alignment;
//	using  destructive_alignment = default_alignment;
#endif
	using alignment = constructive_alignment;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	template <class Z>
	//\
	using couple_t = typename _std::array<Z, 2>;
	using couple_t = bond::couple_t<Z, Z>;


////////////////////////////////////////////////////////////////////////////////

	template <int N_sign=1> requires sign_p<N_sign, 1>
	XTAL_DEF_(return,inline,static)
	XTAL_LET accumulate_f(auto &&w, auto &&x, auto &&...xs)
	XTAL_0EX -> alpha_type
	{
		using _std::fma;

		alpha_type constexpr n_sign = N_sign;

		XTAL_IF0
		XTAL_0IF_(dynamic) {
			if constexpr (use_FMA() and requires {fma((xs *...* n_sign), x, w);}) {
				return fma((XTAL_REF_(xs) *...* n_sign), XTAL_REF_(x), XTAL_REF_(w));
			}
			else {
				return (XTAL_REF_(xs) *...* (n_sign*XTAL_REF_(x))) + XTAL_REF_(w);
			}
		}
		XTAL_0IF_(default) {
			return (XTAL_REF_(xs) *...* (n_sign*XTAL_REF_(x))) + XTAL_REF_(w);
		}
	}

	template <auto N_pow=1>
	XTAL_DEF_(return,inline,static)
	XTAL_LET versus_f(auto &&u)
	XTAL_0EX
	{
		using U = XTAL_ALL_(u);
		XTAL_IF0
		XTAL_0IF (sign_n<N_pow> ==  0) {return couple_t<U>{u, 1/XTAL_REF_(u)};}
		XTAL_0IF (sign_n<N_pow> == -1) {return static_cast<U>(1/XTAL_REF_(u));}
		XTAL_0IF (sign_n<N_pow> == +1) {return static_cast<U>(  XTAL_REF_(u));}
	}


////////////////////////////////////////////////////////////////////////////////

	///\
	Computes: `abs(u)**2`. \

	template <int N_pow=1> requires sign_p<N_pow, 0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET dot_f(aphex_type const &u)
	XTAL_0EX -> alpha_type
	{
		alpha_type const x = u.real();
		alpha_type const y = u.imag();
		return versus_f<N_pow>(accumulate_f(x*x, y, y));
	}


	///\
	Estimates: `w**(1/N_pow)`. \

	template <int N_pow>
	XTAL_DEF_(return,inline,static)
	XTAL_LET root_e(alpha_type const &w)
	XTAL_0EX -> alpha_type
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
	XTAL_DEF_(return,inline,static)
	XTAL_LET root_e(alpha_type const &w, alpha_type const &n)
	XTAL_0EX -> alpha_type
	{
		static_assert(N_pow < 0);
		if (_std::is_constant_evaluated()) {
			if constexpr (N_pow == -1) {
				return (2.0 - n*w)*(w);
			}	else
			if constexpr (N_pow == -2) {
				return (0.5)*(3.0 - w*n*n);
			}
		}
		else {
			return S_::template root_e<N_pow>(w, n);
		}
	}
	///\
	Computes: `w**(1/N_pow)`. \

	template <int N_pow=1, int N_lim=-1>// requires sign_p<N_pow, 0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET root_f(auto const &w)
	XTAL_0EX
	{
		using _std::sqrt;

		using W = XTAL_ALL_(w);
		using U = devolved_t<W>;

	//	W constexpr W_1{1};
		U constexpr U_1{1};
		U constexpr U_2{2};

		bool constexpr N_etc = not real_number_q<W>;

		int constexpr K_pow = -S_::designed_f(N_pow);
		int constexpr M_lim = N_lim&0xF;

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
	template <int N_pow=1, int N_lim=-1>// requires sign_p<N_pow, 0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET root_f(integral_q auto const &w)
	XTAL_0EX
	{
		return root_f<N_pow, N_lim>((alpha_type) w);
	}

	template <int N_pow=1, int N_lim=-1>// requires sign_p<N_pow, 0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET roots_f(alpha_type const &w)
	XTAL_0EX
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



	template <int N_pow=1, int N_lim=-1> requires sign_p<N_pow, 0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET unsquare_f(alpha_type const &w)
	XTAL_0EX
	{
		XTAL_IF0
		XTAL_0IF (0 == N_pow) {return roots_f<2,       N_lim>(w);}
		XTAL_0IF (0 != N_pow) {return root_f <2*N_pow, N_lim>(w);}
	}
	template <int N_pow=1, int N_lim=-1> requires sign_p<N_pow, 0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET unsquare_dot_f(auto &&u)
	XTAL_0EX
	{
		return unsquare_f<N_pow, N_lim>(dot_f(XTAL_REF_(u)));
	}


	template <int N_pow=1, int N_lim=+1> requires sign_p<N_pow, 0>
	XTAL_DEF_(return,static)
	XTAL_LET square_f(auto const &z)
	XTAL_0EX
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
				y = y*x*2;
				x = xx - yy;
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


	template <int N_pow=1> requires sign_p<N_pow, 0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET circle_f(alpha_type const &u)
	XTAL_0EX -> aphex_type
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
	

////////////////////////////////////////////////////////////////////////////////

	///\returns the `constexpr` equivalent of `std:pow(base, n_zoom)` for an `unsigned int n_zoom`. \
	
	XTAL_DEF_(return,static)
	XTAL_LET explo_f(auto &&base, sigma_type const &n_exponent)
	XTAL_0EX
	{
		XTAL_ALL_(base) u = XTAL_REF_(base), w = {1};
		for (sigma_type n = n_exponent; n; n >>= 1) {
			if (n&1) {
				w *= u;
			}
			u = square_f(u);
		}
		return w;
	}
	template <size_type N_exponent>
	XTAL_DEF_(return,inline,static)
	XTAL_LET explo_f(auto &&base, auto result)
	XTAL_0EX
	{
		XTAL_LET N = N_exponent >> 0;
		XTAL_LET M = N_exponent >> 1;
		XTAL_LET I = N_exponent  & 1;
		XTAL_IF0
		XTAL_0IF (N == 0) {return result;}
		XTAL_0IF (I == 0) {return explo_f<M>(square_f(XTAL_REF_(base)),                 XTAL_MOV_(result));}
		XTAL_0IF (I == 1) {return explo_f<M>(square_f(          base ), XTAL_REF_(base)*XTAL_MOV_(result));}
	}
	template <int N_exponent>
	XTAL_DEF_(return,inline,static)
	XTAL_LET explo_f(auto &&base)
	XTAL_0EX
	{
		using X = decltype(base);
		using Y =    based_t<X>;
		using V = devolved_t<Y>;

		XTAL_LET N = N_exponent;
		XTAL_IF0
		XTAL_0IF (N == 0) {return                                   Y{1} ;}// FIXME: Won't work for `eigenclass_t`.
		XTAL_0IF (0 <  N) {return explo_f< N>(     XTAL_REF_(base), V{1});}
		XTAL_0IF (N <  0) {return explo_f<-N>(V{1}/XTAL_REF_(base), V{1});}
	}
	static_assert(explo_f<0>(alpha_type(2.0)) == 1.00);
	static_assert(explo_f<1>(alpha_type(2.0)) == 2.00);
	static_assert(explo_f<2>(alpha_type(2.0)) == 4.00);


	///\returns the `constexpr` equivalent of `std:pow(2.0, n_zoom)`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET diplo_f(delta_type const &n_zoom=N_depth)
	XTAL_0EX
	{
		if (_std::is_constant_evaluated()) {
			delta_type m = n_zoom << unit.shift;
			m += unit.mask;
			m &= exponent.mask;
			return _xtd::bit_cast<alpha_type>(m);
		}
		else {
			return _std::ldexp(alpha_1, (int) n_zoom);// not `constexpr` until `C++23`!
		}
	}
	template <int N_zoom=N_depth>
	static constexpr alpha_type diplo_n = diplo_f(N_zoom);
	///< Value expression of `diplo_f`. \

	static_assert(diplo_n<+1> == 2.0);
	static_assert(diplo_n< 0> == 1.0);
	static_assert(diplo_n<-1> == 0.5);

	static constexpr alpha_type diplo_1 = diplo_n<1>;


	///\returns the `constexpr` equivalent of `std:pow(0.5, n_zoom)`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET haplo_f(delta_type const &n_zoom=N_depth)
	XTAL_0EX
	{
		return diplo_f(-n_zoom);
	}
	template <int N_zoom=N_depth>
	static constexpr alpha_type haplo_n = haplo_f(N_zoom);
	///< Value expression of `haplo_f`. \

	static_assert(haplo_n<+1> == 0.5);
	static_assert(haplo_n< 0> == 1.0);
	static_assert(haplo_n<-1> == 2.0);

	static constexpr alpha_type haplo_1 = haplo_n<1>;


////////////////////////////////////////////////////////////////////////////////

	///\returns the `n_num`erator divided by the given de`n_nom`inator.

	template <int N_pow=1>
	XTAL_DEF_(return,inline,static)
	XTAL_LET ratio_f(alpha_type const &n_num, alpha_type const &n_nom=1)
	XTAL_0EX -> alpha_type
	{
		static_assert(sign_p<N_pow, 0>);
		XTAL_IF0
		XTAL_0IF (N_pow ==  0) {return 1;}
		XTAL_0IF (N_pow ==  1) {return n_num/n_nom;}
		XTAL_0IF (N_pow == -1) {return n_nom/n_num;}
	}
	static_assert(ratio_f(1, 2.0) == 0.5 && ratio_f<-1>(1, 2.0) == 2.0);
	static_assert(ratio_f(4, 2.0) == 2.0 && ratio_f<-1>(4, 2.0) == 0.5);


	///\returns `ratio_f<N_pow>(PI*n_num, n_nom)`.

	template <int N_pow=1> requires sign_p<N_pow, 0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET patio_f(alpha_type const &n_num, alpha_type const &n_nom=1)
	XTAL_0EX -> alpha_type
	{
		return ratio_f<N_pow>(_std::numbers::pi_v<alpha_type>*n_num, n_nom);
	}
	static_assert(patio_f(1, 2) ==  alpha_type(1.570796326794896619231321691639751442L));
	static_assert(patio_f(1,-2) == -alpha_type(1.570796326794896619231321691639751442L));
	static_assert(patio_f(4, 2) ==  alpha_type(6.283185307179586476925286766559005768L));
	static_assert(patio_f(4,-2) == -alpha_type(6.283185307179586476925286766559005768L));

	static constexpr alpha_type patio_1 = patio_f(1, 1);
	static constexpr alpha_type patio_2 = patio_f(2, 1);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\returns the difference between floating-point values at the scale designated by `n_zoom`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET epsilon_f(delta_type const &n_zoom=1)
	XTAL_0EX -> alpha_type
	{
		auto constexpr N = fraction.depth + 1;
		return haplo_f(N - n_zoom);
	}
	template <int N_zoom=0>
	static constexpr alpha_type epsilon_n = epsilon_f(N_zoom);
	///< Value expression of `epsilon_f`. \

	static_assert(epsilon_n<0> != 0);
	static_assert(epsilon_n<0> <  epsilon_n<1>);
	static_assert(epsilon_n<1> <  epsilon_n<2>);
	static_assert(epsilon_n<1> == _std::numeric_limits<alpha_type>::epsilon());
	

	///\returns the value `n_zoom` steps above `(alpha_type) 1`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET upsilon_f(delta_type const &n_zoom=1, delta_type const &n_zone=0)
	XTAL_0EX -> alpha_type
	{
		return (1 + epsilon_f(n_zoom + 1))*diplo_f(n_zone);
	}
	template <int N_zoom=0>
	static constexpr alpha_type upsilon_n = upsilon_f(N_zoom);
	///< Value expression of `upsilon_f`. \
	
	static_assert(upsilon_n<1> > upsilon_n<0>);
	static_assert(upsilon_n<2> > upsilon_n<1>);


	///\returns the value `n_zoom` steps below `(alpha_type) 1`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET dnsilon_f(delta_type const &n_zoom=1, delta_type const &n_zone=0)
	XTAL_0EX -> alpha_type
	{
		return (1 - epsilon_f(n_zoom + 0))*diplo_f(n_zone);
	}
	template <int N_zoom=0>
	static constexpr alpha_type dnsilon_n = dnsilon_f(N_zoom);
	///< Value expression of `dnsilon_f`. \
	
	static_assert(dnsilon_n<1> < dnsilon_n<0>);
	static_assert(dnsilon_n<2> < dnsilon_n<1>);
	

////////////////////////////////////////////////////////////////////////////////

	///\returns `std::numeric_limits<alpha_type>::min()` magnified by `diplo_f(n_zoom)`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET minimal_f(delta_type const &n_zoom=0)
	XTAL_0EX -> alpha_type
	{
		alpha_type constexpr co = _std::numeric_limits<alpha_type>::min();
		return co*diplo_f(n_zoom);
	}
	template <int N_zoom=0>
	static constexpr alpha_type minimal_n = minimal_f(N_zoom);
	///< Value expression for `minimal_f`. \

	///\returns the minimum of the given arguments `xs...`, evaluated with respect to type `alpha_type`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET minimum_f()
	XTAL_0EX
	{
		return minimal_f();
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET minimum_f(auto &&...values)
	XTAL_0EX
	{
		return _std::min<alpha_type>({XTAL_REF_(values)...});
	}


	///\returns haplo_f(n_zoom)/std::numeric_limits<alpha_type>::min()`. \
	
	///\note Defined as the multiplicative inverse of `minimal_f`, \
		rather than w.r.t. `std::numeric_limits<alpha_type>::max()`, \
		which is two orders of (binary) magnitude larger. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET maximal_f(delta_type const &n_zoom=0)
	XTAL_0EX -> alpha_type
	{
		alpha_type constexpr co = alpha_1/_std::numeric_limits<alpha_type>::min();
		return co*haplo_f(n_zoom);
	}
	template <int N_zoom=0>
	static constexpr alpha_type maximal_n = maximal_f(N_zoom);
	///< Value expression for `maximal_f`. \

	///\returns the maximum of the given arguments `xs...`, evaluated with respect to type `alpha_type`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET maximum_f()
	XTAL_0EX
	{
		return maximal_f();
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET maximum_f(auto &&...values)
	XTAL_0EX
	{
		return _std::max<alpha_type>({XTAL_REF_(values)...});
	}


////////////////////////////////////////////////////////////////////////////////

	XTAL_DEF_(return,inline,static)
	XTAL_LET mantissa_f(delta_type n)
	XTAL_0EX -> alpha_type
	{
		n >>= sign.depth + exponent.depth;
		return alpha_type(n)*haplo_f(fraction.depth);
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET mantissa_f(mt19937_t &m)
	XTAL_0EX -> alpha_type
	{
		return mantissa_f(m());
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\returns the sign of `value` as an `alpha_type`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET assigned_f(integral_q auto u)
	{
		return assigned_f(S_::internal_f(u));
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET assigned_f(sigma_type u)
	{
		static_assert(_std::numeric_limits<alpha_type>::is_iec559);
		u <<= positive.depth;
		u  |= unit.mask;
		return _xtd::bit_cast<alpha_type>(u);
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET assigned_f(delta_type u)
	{
		static_assert(_std::numeric_limits<alpha_type>::is_iec559);
		u &= sign.mask;
		u |= unit.mask;
		return _xtd::bit_cast<alpha_type>(u);
	}

	///\returns the sign of `value`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET assigned_f(alpha_type const &value)
	XTAL_0EX -> alpha_type
	{
	#if XTAL_V00_(MSVC)
		return assigned_f(_xtd::bit_cast<delta_type>(value));
	#else
		return __builtin_copysign(alpha_1, value);
	#endif
	}
	static_assert(assigned_f((alpha_type)  0.5) ==  1.0);
	static_assert(assigned_f((alpha_type)  0.0) ==  1.0);
	static_assert(assigned_f((alpha_type) -0.5) == -1.0);

	XTAL_DEF_(return,inline,static)
	XTAL_LET assigned_f(aphex_type const &value)
	XTAL_0EX -> aphex_type
	{
		return unsquare_dot_f<-1>(value)*(value);
	}


	///\returns the original sign of `target`, after making it `abs`olute.

	using S_::design_f;

	XTAL_DEF_(return, static)
	XTAL_LET design_f(alpha_type &target)
	XTAL_0EX -> alpha_type
	{
		alpha_type const signum = assigned_f(target);
		target *= signum;
		return signum;
	}

	///\returns the magnitude of `value` (in the direction of `N_side`, if provided). \
	
	using S_::designed_f;

	template <int N_side=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET designed_f(integral_q auto value)
	XTAL_0EX
	{
		return S_::template designed_f<N_side>(value);
	}
	template <int N_side=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET designed_f(alpha_type value)
	XTAL_0EX -> alpha_type
	{
		if constexpr (N_side == 0) {
		#if XTAL_V00_(MSVC)
			static_assert(_std::numeric_limits<alpha_type>::is_iec559);
			delta_type u = _xtd::bit_cast<delta_type>(value);
			u &= positive.mask;
			return _xtd::bit_cast<alpha_type>(XTAL_MOV_(u));
		#else
			return __builtin_copysign(value, alpha_1);// constexpr
		#endif
		}
		else {
			int constexpr N_sign =     assigned_f(N_side);
			int constexpr M_side = designed_f(N_side);
			value *= N_sign*haplo_f(1); value -= minimal_n<M_side - 1>;
			value += designed_f(value); value += minimal_n<M_side - 1>;
			return value;
		}
	}
	static_assert(designed_f( alpha_1) ==  1.0);
	static_assert(designed_f(-alpha_1) ==  1.0);


	///\returns the original sign of `target`, before applying the sign of `source`. \

	using S_::resign_f;

	XTAL_DEF_(return, static)
	XTAL_LET resign_f(alpha_type &target, auto const &source=1)
	XTAL_0EX -> alpha_type
	{
		alpha_type const signum = assigned_f(target);
		target = resigned_f(target, source);
		return signum;
	}
	///\returns the `target` magnitude with the sign of the `source`. \

	XTAL_DEF_(return,inline,static)
	XTAL_LET resigned_f(alpha_type target, alpha_type const &source=1)
	XTAL_0EX -> alpha_type
	{
	#if XTAL_V00_(MSVC)
		return resigned_f(XTAL_MOV_(target), _xtd::bit_cast<delta_type>(source));
	#else
		return __builtin_copysign(target, source);// constexpr
	#endif
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET resigned_f(alpha_type target, delta_type source=0)
	XTAL_0EX -> alpha_type
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
	XTAL_DEF_(return,inline,static)
	XTAL_LET clamped_f(integral_q auto value)
	XTAL_0EX
	{
		return S_::template clamped_f<N_side>(value);
	}
	template <int N_side=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET clamped_f(alpha_type value)
	XTAL_0EX
	{
		XTAL_IF0
		XTAL_0IF (N_size == 0) {return                                   value ;}
		XTAL_0IF (N_size != 0) {return sign_n<N_side>*designed_f<N_side>(value);}
	}
	static_assert(clamped_f<+1>( alpha_1) == +1.0);
	static_assert(clamped_f<+1>( alpha_0) == +minimal_f());
	static_assert(clamped_f<+1>(-alpha_1) == +minimal_f());
	static_assert(clamped_f<-1>( alpha_1) == -minimal_f());
	static_assert(clamped_f<-1>( alpha_0) == -minimal_f());
	static_assert(clamped_f<-1>(-alpha_1) == -1.0);


////////////////////////////////////////////////////////////////////////////////

	XTAL_DEF_(return,static)
	XTAL_LET scientific_f(alpha_type const &f)
	XTAL_0EX -> couple_t<delta_type>
	{
		delta_type constexpr N = unit.mark + fraction.depth;
		sigma_type constexpr M =  sigma_1 << fraction.depth;
		
		sigma_type o = _xtd::bit_cast<sigma_type>(f);
		delta_type n = N - (o << sign.depth >> sign.depth + exponent.shift);
		delta_type m = M | (o&fraction.mask);
		delta_type z = static_cast<delta_type>(o) >> positive.depth;
		m  ^= z;
		m  -= z;
		return {m, n};
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET unscientific_f(couple_t<delta_type> const &mn)
	XTAL_0EX -> alpha_type
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

	XTAL_DEF_(return,static)
	XTAL_LET fractional_f(alpha_type const &f)
	XTAL_0EX -> delta_type
	{
		sigma_type  o = _xtd::bit_cast<sigma_type>(f);
		delta_type  n = (o << sign.depth >> sign.depth + exponent.shift) - (unit.mark - exponent.depth - 1);
		delta_type  m = (o & fraction.mask) | (sigma_1 << fraction.depth);
		delta_type  z =       (static_cast<delta_type>(o) >> positive.depth);
		delta_type up = designed_f<1>(n);
		delta_type dn = up - n;
		m   <<= up;
		m   >>= dn;
		m    ^=  z;
		m    -=  z;
		return   m;
	}
	XTAL_DEF_(return,inline,static)
	XTAL_LET fraction_f(alpha_type const &f)
	XTAL_0EX -> alpha_type
	{
		return static_cast<alpha_type>(fractional_f(f))*haplo_f(N_depth);
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

////////////////////////////////////////////////////////////////////////////////

	/// Modifies the `target`, clamping the magnitude below `dnsilon_f(N_zoom, n_zone)`. \

	///\returns zero if unchanged, else the sign of the `target`. \
	
	template <int N_zoom=0, bool N_infinity=0>
	XTAL_DEF_(static)
	XTAL_LET truncate_f(alpha_type &target, delta_type const &n_zone)
	XTAL_0EX -> alpha_type
	{
	//	bool constexpr N_unit = not N_infinity;
		if constexpr (IEC&559) {
			delta_type constexpr M_zone = unit.mask + (1);
			delta_type constexpr M_zoom = unit.mask - (delta_type(1) << N_zoom);
			delta_type const     dezone = n_zone << exponent.shift;
			delta_type const     rezone = N_infinity? M_zone - dezone: dezone;
			delta_type const M = rezone + M_zoom;
			delta_type o, n, m;
			auto &t  = reinterpret_cast<delta_type &>(target);
			n  =  t  & sign.mask;
			m  =  t  ^ n;
			m  =  M  - m;
			o  =  m >> positive.depth;
			n |=  o  & unit.mask;
			t +=  o  & m;
			return    _xtd::bit_cast<alpha_type>(n);
		}
		else {
			alpha_type const t = N_infinity? maximal_f(n_zone - 1): dnsilon_f(N_zoom, n_zone);
			alpha_type const s = design_f(target), o = t < target;
			target = s*minimum_f(t, target);
			return o*s;
		}
	}
	/// Modifies the `target`, clamping the magnitude below `maximal_f(N_zoom)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <int N_zoom=0>
	XTAL_DEF_(static)
	XTAL_LET truncate_f(alpha_type &target)
	XTAL_0EX -> alpha_type
	{
		return truncate_f<0, 1>(target, N_zoom + 1);
	}
	template <int N_zoom=0>
	XTAL_DEF_(static)
	XTAL_LET truncate_f(aphex_type &target)
	XTAL_0EX -> aphex_type
	{
		auto &z = devolved_f(target);
		alpha_type const x = truncate_f<N_zoom>(z[0]);
		alpha_type const y = truncate_f<N_zoom>(z[1]);
		return aphex_type{x, y};
	}

	///\returns the `target` with magnitude clamped to the region below `dnsilon_f(N_zoom, n_zone)`. \

	template <int N_zoom=0, bool N_infinity=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET truncated_f(alpha_type target, delta_type const &n_zone)
	XTAL_0EX -> alpha_type
	{
		(void) truncate_f<N_zoom, N_infinity>(target, n_zone); return target;
	}
	///\returns the `target` with magnitude clamped to the region below `maximal_f(N_zoom)`. \

	template <int N_zoom=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET truncated_f(alpha_type const &target)
	XTAL_0EX -> alpha_type
	{
		return truncated_f<0, 1>(target, N_zoom + 1);
	}

	template <int N_zoom=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET truncated_f(aphex_type const &target)
	XTAL_0EX -> aphex_type
	{
		alpha_type const x = truncated_f<N_zoom>(target.real());
		alpha_type const y = truncated_f<N_zoom>(target.imag());
		return aphex_type{x, y};
	}
	template <int N_zoom=0, bool N_zero=0>
#if XTAL_V00_(GNUC) and XTAL_V00_(GNUC) < 1300
	[[gnu::optimize(1)]]
#endif
	XTAL_DEF_(return,inline,static)
	XTAL_LET truncated_f(aphex_type const &source, delta_type const &n_zone)
	XTAL_0EX -> aphex_type
	{
		auto target = truncated_f<(delta_1 << (exponent.depth - 2))>(source);
		auto [w, m] = unsquare_dot_f<0>(target);
		target *= m; truncate_f<N_zoom, N_zero>(w, n_zone);
		target *= w;
		return target;
	}

////////////////////////////////////////////////////////////////////////////////

	/// Modifies the `target`, clamping the magnitude above `upsilon_f(N_zoom, n_zone)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <int N_zoom=0, bool N_zero=0>
	XTAL_DEF_(static)
	XTAL_LET puncture_f(alpha_type &target, delta_type const &n_zone)
	XTAL_0EX -> alpha_type
	{
		bool constexpr N_unit = not N_zero;
		if constexpr (IEC&559) {
			delta_type constexpr M_zoom = unit.mask + (delta_type(1) << N_zoom);
			delta_type const     dezone = n_zone << exponent.shift;
			delta_type const M = dezone + M_zoom*N_unit;
			delta_type o, n, m;
			auto &t  = reinterpret_cast<delta_type &>(target);
			n   = t  & sign.mask;
			m   = t  ^ n;
			m  -= M;
			o   = m >> positive.depth;
			n  |= o  & unit.mask;
			t  -= o  & m;
			return    _xtd::bit_cast<alpha_type>(XTAL_MOV_(n));
		}
		else {
			alpha_type const t = N_zero? minimal_f(n_zone - 1): upsilon_f(N_zoom, n_zone);
			alpha_type const s = design_f(target), o = target < t;
			target = s*maximum_f(t, target);
			return o*s;
		}
	}
	/// Modifies the `target`, clamping the magnitude above `minimal_f(N_zoom)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <int N_zoom=0>
	XTAL_DEF_(static)
	XTAL_LET puncture_f(alpha_type &target)
	XTAL_0EX -> alpha_type
	{
		return puncture_f<0, 1>(target, N_zoom + 1);
	}
	template <int N_zoom=0>
	XTAL_DEF_(static)
	XTAL_LET puncture_f(aphex_type &target)
	XTAL_0EX -> alpha_type
	{
		auto &z = reinterpret_cast<alpha_type(&)[2]>(target);
		alpha_type const x = puncture_f<N_zoom>(z[0]);
		alpha_type const y = puncture_f<N_zoom>(z[1]);
		return aphex_type{x, y};
	}

	///\returns the `target` with magnitude clamped to the region above `upsilon_f(N_zoom, n_zone)`. \

	template <int N_zoom=0, bool N_zero=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET punctured_f(alpha_type target, delta_type const &n_zone)
	XTAL_0EX -> alpha_type
	{
		(void) puncture_f<N_zoom, N_zero>(target, n_zone); return target;
	}
	///\returns the `target` with magnitude clamped to the region above `minimal_f(N_zoom)`. \

	template <int N_zoom=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET punctured_f(alpha_type const &target)
	XTAL_0EX -> alpha_type
	{
		return punctured_f<0, 1>(target, N_zoom + 1);
	}

	template <int N_zoom=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET punctured_f(aphex_type const &target)
	XTAL_0EX
	{
		alpha_type const x = punctured_f<N_zoom>(target.real());
		alpha_type const y = punctured_f<N_zoom>(target.imag());
		return aphex_type{x, y};
	}
	template <int N_zoom=0, bool N_zero=0>
	XTAL_DEF_(return,inline,static)
	XTAL_LET punctured_f(aphex_type target, delta_type const &n_zone)
	XTAL_0EX
	{
		auto [w, m] = unsquare_dot_f<0>(target);
		target *= m; puncture_f<N_zoom, N_zero>(w, n_zone);
		target *= w;
		return target;
	}
	

////////////////////////////////////////////////////////////////////////////////

	///\returns the `target` to `N_zoom` bits of precision after the decimal. \

	template <int N_zoom=0>
	XTAL_DEF_(verbatim,static)
	XTAL_LET trim_f(alpha_type target)
	XTAL_0EX -> alpha_type
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
	XTAL_DEF_(verbatim,static)
	XTAL_LET trim_f(aphex_type const &target)
	XTAL_0EX
	{
		alpha_type const x = trim_f<N_zoom>(target.real());
		alpha_type const y = trim_f<N_zoom>(target.imag());
		return aphex_type{x, y};
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
};


}///////////////////////////////////////////////////////////////////////////////

template <class T>
struct operate : _detail::realize<sizeof(devolved_t<T>)> {};

using operating = operate<size_type>;

static_assert(is_q<size_type, typename operating::sigma_type>);
static_assert(sizeof(size_type) == sizeof(typename operating::sigma_type));
static_assert(sizeof(size_type) == sizeof(typename operating::delta_type));
static_assert(sizeof(size_type) == sizeof(typename operating::alpha_type));


///////////////////////////////////////////////////////////////////////////////

///\see `operating::trim_f`. \

template <auto ...N_etc>
XTAL_DEF_(static)
XTAL_LET computrim_f = []<class T>(T &&t)
XTAL_0FN_(operate<T>::template trim_f<N_etc...>(XTAL_REF_(t)));


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
