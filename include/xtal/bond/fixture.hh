#pragma once
#include "./any.hh"
#include "./seek.hh"





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

	static sigma_type constexpr N_exponent = 3;
	static sigma_type constexpr N_fraction = 4;

	template <int N_pow, class _=void> struct   expound;
	template <           class _     > struct   expound<2, _> : constant_t<(sigma_type) 0x80U> {};
	template <           class _     > struct   expound<3, _> : constant_t<(sigma_type) 0x51U> {};
	template <int N_pow>  static constexpr auto expound_n = expound<N_pow, void>::value;

};
template <>
struct recognize<(1U<<1U)>
{
	using       _zed =  constant_t<true>;
	using delta_type = _std::  make_signed_t<XTAL_STD_(int,   1)>;
	using sigma_type = _std::make_unsigned_t<XTAL_STD_(int,   1)>;
//	using alpha_type =                       XTAL_STD_(float, 1) ;
//	using aphex_type =  _std::complex<alpha_type>;

	static sigma_type constexpr N_exponent =  5;
	static sigma_type constexpr N_fraction = 10;

	template <int N_pow, class _=void> struct   expound;
	template <           class _     > struct   expound<2, _> : constant_t<(sigma_type) 0x8000U> {};
	template <           class _     > struct   expound<3, _> : constant_t<(sigma_type) 0x4CE3U> {};
	template <int N_pow>  static constexpr auto expound_n = expound<N_pow, void>::value;

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

	static sigma_type constexpr N_exponent =  8;
	static sigma_type constexpr N_fraction = 23;

#ifdef FP_FAST_FMAF
	static sigma_type constexpr N_fused = 0b1;
#else
	static sigma_type constexpr N_fused = 0b0;
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
	template <int N_pow>  static constexpr auto expound_n = expound<N_pow, void>::value;

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

	static sigma_type constexpr N_exponent = 11;
	static sigma_type constexpr N_fraction = 52;

#ifdef FP_FAST_FMA
	static sigma_type constexpr N_fused = 0b1;
#else
	static sigma_type constexpr N_fused = 0b0;
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
	template <int N_pow>  static constexpr auto expound_n = expound<N_pow, void>::value;

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

	static delta_type constexpr delta_0{0};
	static delta_type constexpr delta_1{1};

	static sigma_type constexpr sigma_0{0};
	static sigma_type constexpr sigma_1{1};

	static sigma_type constexpr N_width = N_size;
	static sigma_type constexpr N_depth = N_size << 3U;

	static sigma_type constexpr N_fraction =          S_::N_fraction;
	static sigma_type constexpr N_exponent =          S_::N_exponent;
	static sigma_type constexpr N_positive = N_fraction + N_exponent;
	static sigma_type constexpr N_negative = N_positive + 1;
	static sigma_type constexpr N_unit     = N_exponent - 1;
	static sigma_type constexpr N_sign     =              1;

	struct word
	{
		sigma_type const width;
		sigma_type const depth;
		sigma_type const shift;
		sigma_type const mark;
		sigma_type const mask;

		XTAL_DEF_(return,inline,set) flag_f(sigma_type const m=0)                       noexcept -> sigma_type {return one << (m&(N_depth - one));};
		XTAL_DEF_(return,inline,set) mark_f(sigma_type const m=0)                       noexcept -> sigma_type {return        ~-flag_f(m)        ;};
		XTAL_DEF_(return,inline,set) mask_f(sigma_type const m=0, sigma_type const n=0) noexcept -> sigma_type {return          mark_f(m) << n   ;};

		XTAL_NEW_(explicit) word(sigma_type m_depth, sigma_type n_shift=0)
		noexcept
		:	width (m_depth >> 3U)
		,	depth (m_depth)
		,	shift (n_shift)
		,	mark  (mark_f(m_depth))
		,	mask  (mask_f(m_depth, n_shift))
		{}

	};
	static word constexpr negative {N_negative};
	static word constexpr positive {N_positive};
	static word constexpr fraction {N_fraction};
	static word constexpr exponent {N_exponent, N_fraction};
	static word constexpr     unit     {N_unit, N_fraction};
	static word constexpr     sign     {N_sign, N_positive};
	static word constexpr     half {N_depth >> 1U, N_depth >> 1U};
	static word constexpr     full = negative;

	using default_alignment = constant_t<(size_type) XTAL_SYS_(L1)/N_width>;

#ifdef __cpp_lib_hardware_interference_size
	using constructive_alignment = constant_t<(size_type) _std::hardware_constructive_interference_size/N_width>;
//	using  destructive_alignment = constant_t<(size_type) _std:: hardware_destructive_interference_size/N_width>;
#else
	using constructive_alignment = default_alignment;
//	using  destructive_alignment = default_alignment;
#endif
	using alignment = constructive_alignment;


	XTAL_DEF_(return,inline,set) internal_f(     delta_type i) noexcept -> auto {return i;}
	XTAL_DEF_(return,inline,set) internal_f(     sigma_type i) noexcept -> auto {return i;}
	XTAL_DEF_(return,inline,set) internal_f( ordinal_q auto i) noexcept -> auto {return static_cast<delta_type>(i);}
	XTAL_DEF_(return,inline,set) internal_f(cardinal_q auto i) noexcept -> auto {return static_cast<sigma_type>(i);}


////////////////////////////////////////////////////////////////////////////////

	///\returns the remainder from the maximal power of `N`, \
	which is zero if the argument is a power of `N`. \

	///\note\
	Currently only supports `N={2,3}`.

	template <sigma_type N>
	XTAL_DEF_(return,inline,set)
	expound_f(sigma_type u)
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
	XTAL_DEF_(return,inline,set)
	expound_f(un_q<sigma_type> auto const &value)
	noexcept -> auto
	{
		return expound_f<N>(static_cast<sigma_type>(value));
	}



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

	using S_::N_width;
	using S_::N_depth;
	using S_::N_fused;

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

	using typename S_::delta_type;
	using typename S_::sigma_type;
	using typename S_::alpha_type;
	using typename S_::aphex_type;
	using typename S_::mt19937_t;


	static alpha_type constexpr alpha_0{0};
	static alpha_type constexpr alpha_1{1};
	static alpha_type constexpr alpha_oo{_std::numeric_limits<alpha_type>().infinity()};
	
	static aphex_type constexpr aphex_0{0, 0};
	static aphex_type constexpr aphex_1{1, 0};
	static aphex_type constexpr aphex_i{0, 1};

	XTAL_DEF_(return,inline,set) internal_f(alpha_type      i) noexcept -> auto {return                         i ;}
	XTAL_DEF_(return,inline,set) internal_f(    real_q auto i) noexcept -> auto {return static_cast<alpha_type>(i);}
	XTAL_DEF_(return,inline,set) internal_f(integral_q auto i) noexcept -> auto {return          S_::internal_f(i);}


	XTAL_DEF_(return,inline,set)
	delta_f(auto &&o)
	noexcept -> delta_type
	{
		if constexpr (cardinal_q<decltype(o)>) {
			return _std::bit_cast<delta_type>(static_cast<sigma_type>(XTAL_REF_(o)));
		}
		else {
			return static_cast<delta_type>(XTAL_REF_(o));
		}
	}
	XTAL_DEF_(return,inline,set)
	sigma_f(auto &&o)
	noexcept -> sigma_type
	{
		if constexpr (cardinal_q<decltype(o)>) {
			return static_cast<sigma_type>(XTAL_REF_(o));
		}
		else {
			return _std::bit_cast<sigma_type>(static_cast<delta_type>(XTAL_REF_(o)));
		}
	}
	XTAL_DEF_(return,inline,set)
	alpha_f(auto &&o)
	noexcept -> alpha_type
	{
		if constexpr (integral_q<decltype(o)>) {
			return static_cast<alpha_type>(delta_f(XTAL_REF_(o)));
		}
		else {
			return static_cast<alpha_type>(XTAL_REF_(o));
		}
	}


	static sigma_type constexpr IEC = _std::numeric_limits<alpha_type>::is_iec559? XTAL_SYS_(IEC)&60559: 0;

	static constant_t<IEC&559> constexpr use_IEC{};
	static constant_t<N_fused> constexpr use_FMA{};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\returns the `constexpr` equivalent of `std:pow(2.0, n_zoom)*(o_silon)`. \

	XTAL_DEF_(return,inline,set)
	diplo_f(alpha_type n_zoom, alpha_type o_silon)
	noexcept -> alpha_type
	{
		if constexpr (XTAL_SYS_(builtin)) {
			return o_silon*__builtin_exp2(n_zoom);
		}
		else {
			auto constexpr N_ln2 = _std::numbers::ln2_v<alpha_type>;
			return o_silon*exp(n_zoom*N_ln2);// TODO: Handle `consteval`?
		}
	}
	XTAL_DEF_(return,inline,set)
	diplo_f(delta_type n_zoom, alpha_type o_silon)
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
	XTAL_DEF_(return,inline,set)
	diplo_f(sigma_type n_zoom, alpha_type o_silon)
	noexcept -> alpha_type
	{
		return diplo_f(_xtd::bit_cast<delta_type>(n_zoom), o_silon);
	}
	XTAL_DEF_(return,inline,set) diplo_f(auto n_zoom, alpha_type o_silon)
	noexcept -> auto
	{
		return diplo_f(internal_f(XTAL_REF_(n_zoom)), o_silon);
	}

	template <int N_silon=0>
	XTAL_DEF_(return,inline,set)
	diplo_f(auto const &n_zoom)
	noexcept -> alpha_type
	{
		auto constexpr o_silon = one/alpha_type{one << fraction.depth - sign_n<N_silon>*N_silon};
		XTAL_IF0
		XTAL_0IF (0 < N_silon) {return diplo_f(n_zoom, one + alpha_type{0.50}/o_silon);}
		XTAL_0IF (N_silon < 0) {return diplo_f(n_zoom, one - alpha_type{0.25}/o_silon);}
		XTAL_0IF_(else)        {return diplo_f(n_zoom,       alpha_type{1.00}        );}
	}
	template <int N_silon=0>
	XTAL_DEF_(return,inline,set)
	diplo_f()
	noexcept -> alpha_type
	{
		return diplo_f<N_silon>(N_depth);
	}

	template <int N_zoom=N_depth>
	static alpha_type constexpr diplo_n = diplo_f(N_zoom);
	///< Value expression of `diplo_f`. \


	static alpha_type constexpr diplo_0 = diplo_n<0>;
	static alpha_type constexpr diplo_1 = diplo_n<1>;
	static alpha_type constexpr diplo_2 = diplo_n<2>;


	///\returns the `constexpr` equivalent of `std:pow(0.5, n_zoom)`. \

	template <int N_silon=0> XTAL_DEF_(return,inline,set) haplo_f(auto const &n_zoom) noexcept -> auto {return diplo_f<-N_silon>(-n_zoom );}
	template <int N_silon=0> XTAL_DEF_(return,inline,set) haplo_f(                  ) noexcept -> auto {return diplo_f<-N_silon>(-N_depth);}

	template <int N_zoom=N_depth>
	static alpha_type constexpr haplo_n = haplo_f(N_zoom);
	///< Value expression of `haplo_f`. \


	static alpha_type constexpr haplo_0 = haplo_n<0>;
	static alpha_type constexpr haplo_1 = haplo_n<1>;
	static alpha_type constexpr haplo_2 = haplo_n<2>;


////////////////////////////////////////////////////////////////////////////////

	///\returns the `n_num`erator divided by the given de`n_nom`inator.

	template <int N_pow=1>
	XTAL_DEF_(return,inline,set)
	ratio_f(alpha_type n_num, alpha_type n_nom=1)
	noexcept -> alpha_type
	{
		XTAL_IF0
		XTAL_0IF (N_pow ==  0) {return 1;}
		XTAL_0IF (N_pow ==  1) {return n_num/n_nom;}
		XTAL_0IF (N_pow == -1) {return n_nom/n_num;}
		XTAL_0IF_(abort)
	}

	static alpha_type constexpr ratio_0 = ratio_f(0, 1);
	static alpha_type constexpr ratio_1 = ratio_f(1, 1);
	static alpha_type constexpr ratio_2 = ratio_f(2, 1);

	///\returns `ratio_f<N_pow>(PI*n_num, n_nom)`.

	template <int N_pow=1> requires in_n<N_pow, 1, 0, -1>
	XTAL_DEF_(return,inline,set)
	patio_f(alpha_type n_num, alpha_type n_nom=1)
	noexcept -> alpha_type
	{
		return ratio_f<N_pow>(_std::numbers::pi_v<alpha_type>*n_num, n_nom);
	}

	static alpha_type constexpr patio_0 = patio_f(0, 1);
	static alpha_type constexpr patio_1 = patio_f(1, 1);
	static alpha_type constexpr patio_2 = patio_f(2, 1);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\returns the difference between floating-point values at the scale designated by `n_zoom`. \

	XTAL_DEF_(return,inline,set)
	epsilon_f(delta_type const &n_zoom=1)
	noexcept -> alpha_type
	{
		auto constexpr N = fraction.depth + 1;
		return haplo_f(N - n_zoom);
	}
	template <int N_zoom=0>
	static alpha_type constexpr epsilon_n = epsilon_f(N_zoom);
	///< Value expression of `epsilon_f`. \

	
	
	static alpha_type constexpr epsilon_0 = epsilon_n<0>;
	static alpha_type constexpr epsilon_1 = epsilon_n<1>;
	static alpha_type constexpr epsilon_2 = epsilon_n<2>;


	///\returns the value `n_zoom` steps above `(alpha_type) 1`. \

	XTAL_DEF_(return,inline,set)
	upsilon_f(delta_type const &n_zoom=1, delta_type const &n_zone=0)
	noexcept -> alpha_type
	{
		auto constexpr N_diff = fraction.depth + 1;
		auto const     n_unit = one + haplo_f(N_diff - n_zoom);
		return n_unit*diplo_f(n_zone);
	}
	template <int N_zoom=0>
	static alpha_type constexpr upsilon_n = upsilon_f(N_zoom);
	///< Value expression of `upsilon_f`. \
	
	
	static alpha_type constexpr upsilon_0 = upsilon_n<0>;
	static alpha_type constexpr upsilon_1 = upsilon_n<1>;
	static alpha_type constexpr upsilon_2 = upsilon_n<2>;


	///\returns the value `n_zoom` steps below `(alpha_type) 1`. \

	XTAL_DEF_(return,inline,set)
	dnsilon_f(delta_type const &n_zoom=1, delta_type const &n_zone=0)
	noexcept -> alpha_type
	{
		auto constexpr N_diff = fraction.depth + 2;
		auto const     n_unit = one - haplo_f(N_diff - n_zoom);
		return n_unit*diplo_f(n_zone);
	}
	template <int N_zoom=0>
	static alpha_type constexpr dnsilon_n = dnsilon_f(N_zoom);
	///< Value expression of `dnsilon_f`. \
	
	
	static alpha_type constexpr dnsilon_0 = dnsilon_n<0>;
	static alpha_type constexpr dnsilon_1 = dnsilon_n<1>;
	static alpha_type constexpr dnsilon_2 = dnsilon_n<2>;


////////////////////////////////////////////////////////////////////////////////

	///\returns the minimum value that still accommodates arithmetic puncturing. \

	XTAL_DEF_(return,inline,set)
	minilon_f(delta_type const &n_zoom=0)
	noexcept -> alpha_type
	{
		return haplo_f(unit.mark - 1)*diplo_f(n_zoom);
	}
	template <int N_zoom=0>
	static alpha_type constexpr minilon_n = minilon_f(N_zoom);
	///< Value expression for `minilon_f`. \

	static alpha_type constexpr minilon_0 = minilon_n<0>;
	static alpha_type constexpr minilon_1 = minilon_n<1>;
	static alpha_type constexpr minilon_2 = minilon_n<2>;


	///\returns the minimum of the given arguments `xs...`, evaluated with respect to type `alpha_type`. \

	XTAL_DEF_(return,inline,set)
	minimum_f()
	noexcept -> decltype(auto)
	{
		return minilon_f();
	}
	XTAL_DEF_(return,inline,set)
	minimum_f(auto &&w)
	noexcept -> decltype(auto)
	{
		return XTAL_REF_(w);
	}
	XTAL_DEF_(return,inline,set)
	minimum_f(auto &&w, auto &&x)
	noexcept -> decltype(auto)
	{
		return w < x? XTAL_REF_(w): XTAL_REF_(x);
	}
	XTAL_DEF_(return,inline,set)
	minimum_f(auto &&w, auto &&x, auto &&...xs)
	noexcept -> decltype(auto)
	{
		return minimum_f(minimum_f(XTAL_REF_(w), XTAL_REF_(x)), XTAL_REF_(xs)...);
	}


	///\returns the maximum value that still accommodates arithmetic truncation. \

	XTAL_DEF_(return,inline,set)
	maxilon_f(delta_type const &n_zoom=0)
	noexcept -> alpha_type
	{
		return diplo_f(unit.mark - 1)*haplo_f(n_zoom);
	}
	template <int N_zoom=0>
	static alpha_type constexpr maxilon_n = maxilon_f(N_zoom);
	///< Value expression for `maxilon_f`. \

	static alpha_type constexpr maxilon_0 = maxilon_n<0>;
	static alpha_type constexpr maxilon_1 = maxilon_n<1>;
	static alpha_type constexpr maxilon_2 = maxilon_n<2>;
	static alpha_type constexpr maxilon_3 = maxilon_n<3>;


	///\returns the maximum of the given arguments `xs...`, evaluated with respect to type `alpha_type`. \

	XTAL_DEF_(return,inline,set)
	maximum_f()
	noexcept -> decltype(auto)
	{
		return maxilon_f();
	}
	XTAL_DEF_(return,inline,set)
	maximum_f(auto &&w)
	noexcept -> decltype(auto)
	{
		return XTAL_REF_(w);
	}
	XTAL_DEF_(return,inline,set)
	maximum_f(auto &&w, auto &&x)
	noexcept -> decltype(auto)
	{
		return w > x? XTAL_REF_(w): XTAL_REF_(x);
	}
	XTAL_DEF_(return,inline,set)
	maximum_f(auto &&w, auto &&x, auto &&...xs)
	noexcept -> decltype(auto)
	{
		return maximum_f(maximum_f(XTAL_REF_(w), XTAL_REF_(x)), XTAL_REF_(xs)...);
	}


////////////////////////////////////////////////////////////////////////////////

	XTAL_DEF_(return,inline,set)
	mantissa_f(delta_type n)
	noexcept -> alpha_type
	{
		n >>= sign.depth + exponent.depth;
		return alpha_type(n)*haplo_f(fraction.depth);
	}
	XTAL_DEF_(return,inline,set)
	mantissa_f(mt19937_t &m)
	noexcept -> alpha_type
	{
		return mantissa_f(m());
	}


////////////////////////////////////////////////////////////////////////////////

	XTAL_DEF_(return,inline,set)
	sentry_f(_std::partial_ordering const &o)
	noexcept -> auto
	{
		using is = _std::partial_ordering;
		if (o == is:: equivalent) return 0b00U; else
		if (o == is::    greater) return 0b01U; else
		if (o == is::       less) return 0b10U; else
		return 0b11U;
	}
	XTAL_DEF_(return,inline,set)
	sentry_f(auto const &o)
	noexcept -> _std::partial_ordering
	{
		using is = _std::partial_ordering;
		_std::array constexpr table
		{	is:: equivalent
		,	is::    greater
		,	is::       less
		,	is::  unordered
		};
		return table[o];
	}


	XTAL_DEF_(return,inline,set)
	sentinel_f(alpha_type const &o)
	noexcept -> auto
	{
		return sentinel_f(_xtd::bit_cast<sigma_type>(o));
	}
	XTAL_DEF_(return,inline,set)
	sentinel_f(sigma_type const &o)
	noexcept -> auto
	{
		auto v = o >> sign.shift; v += o != 0; return v;
	}
	XTAL_DEF_(return,inline,set)
	sentinel_f(delta_type const &o)
	noexcept -> auto
	{
		return sentinel_f(sigma_f(o));
	}
	XTAL_DEF_(return,inline,set)
	sentinel_f(auto const &o)
	noexcept -> auto
	{
		return sentinel_f(internal_f(o));
	}


////////////////////////////////////////////////////////////////////////////////

	///\returns the `target` to `N_zoom` bits of precision after the decimal. \

	template <int N_zoom=0>
	XTAL_DEF_(verbatim,set)
	trim_f(alpha_type target)
	noexcept -> alpha_type
	{
		delta_type constexpr N_unzoom = 0 < N_zoom? N_zoom - fraction.depth: N_zoom - 1;
		alpha_type constexpr N_minima = diplo_f(N_unzoom)*_std::numeric_limits<alpha_type>::min();
		target *= N_minima;
		target /= N_minima;
		return target;
	}

	template <int N_zoom=fraction.depth - 1>
	XTAL_DEF_(verbatim,set)
	trim_f(aphex_type const &target)
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
struct   fixture
:	complete_t<_detail::realize<sizeof(absolve_u<Ts...>)>>
{
};
template <class ...Ts> requires seek_constant_q<Ts...>
struct   fixture<Ts...>
:	complete_t<_detail::realize<sizeof(absolve_u<Ts>)>...>::template widen<seek_constant_n<Ts...>>
{
};
template <>
struct   fixture<>
:	fixture<size_type>
{
};


///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
