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
	using typename S_::delta_type;
	using typename S_::sigma_type;

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

	using S_::  delta_0;
	using S_::  delta_1;

	using S_::  sigma_0;
	using S_::  sigma_1;

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

	XTAL_DEF_(short) XTAL_SET internal_f(alpha_type      i) noexcept -> auto {return                         i ;}
	XTAL_DEF_(short) XTAL_SET internal_f(    real_q auto i) noexcept -> auto {return static_cast<alpha_type>(i);}
	XTAL_DEF_(short) XTAL_SET internal_f(integral_q auto i) noexcept -> auto {return          S_::internal_f(i);}


	XTAL_DEF_(short)
	XTAL_SET delta_f(auto &&o)
	noexcept -> delta_type
	{
		if constexpr (cardinal_q<decltype(o)>) {
			return _std::bit_cast<delta_type>(static_cast<sigma_type>(XTAL_REF_(o)));
		}
		else {
			return static_cast<delta_type>(XTAL_REF_(o));
		}
	}
	XTAL_DEF_(short)
	XTAL_SET sigma_f(auto &&o)
	noexcept -> sigma_type
	{
		if constexpr (cardinal_q<decltype(o)>) {
			return static_cast<sigma_type>(XTAL_REF_(o));
		}
		else {
			return _std::bit_cast<sigma_type>(static_cast<delta_type>(XTAL_REF_(o)));
		}
	}
	XTAL_DEF_(short)
	XTAL_SET alpha_f(auto &&o)
	noexcept -> alpha_type
	{
		if constexpr (integral_q<decltype(o)>) {
			return static_cast<alpha_type>(delta_f(XTAL_REF_(o)));
		}
		else {
			return static_cast<alpha_type>(XTAL_REF_(o));
		}
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
			XTAL_LET N_ln2 = _std::numbers::ln2_v<alpha_type>;
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
		XTAL_LET o_silon = one/alpha_type{one << fraction.depth - sign_n<N_silon>*N_silon};
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
template <>
struct   operate<>
:	operate<size_type>
{
};


///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
