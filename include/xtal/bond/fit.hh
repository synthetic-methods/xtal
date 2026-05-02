#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace _detail
{//////////////////////////////////////////////////////////////////////////////

template <cardinal_variable_q U>
struct fitting
{
	U const width{};
	U const depth{};
	U const shift;
	U const  mark;
	U const  mask;

	XTAL_NEW_(explicit)
	fitting(U m_depth, U n_shift=0)
	noexcept
	:	width (m_depth >> 3U)
	,	depth (m_depth)
	,	shift (n_shift)
	,	mark  (mark_f(m_depth))
	,	mask  (mask_f(m_depth, n_shift))
	{}

private:
	XTAL_DEF_(set) N_width  =  sizeof(U) << 0;
	XTAL_DEF_(set) N_depth  =  sizeof(U) << 3;
	XTAL_DEF_(set) N_mask   = ~U{};

	XTAL_DEF_(return,inline,set) mark_f(U const m) noexcept -> auto {return N_mask >> N_depth - (m);}
	XTAL_DEF_(return,inline,set) mask_f(U const m,
	                                    U const n) noexcept -> auto {return        mark_f(m) << (n);}

};


//////////////////////////////////////////////////////////////////////////////////

template <size_type N_size>
struct fit_recognize;
#ifndef XTAL_DOC
template <size_type N_size>
struct fit_recognize : fit_recognize<N_size/2>
{
	using fix = succedent_s<typename fit_recognize<N_size/2>::fix>;

};
#endif
template <>
struct fit_recognize<0x1>
{
	XTAL_TYP_(set)        fix =  cardinal_constant_t<0>;
	XTAL_TYP_(set) delta_type = _std::  make_signed_t<XTAL_STD_(int, 0)>;
	XTAL_TYP_(set) sigma_type = _std::make_unsigned_t<XTAL_STD_(int, 0)>;
//	XTAL_TYP_(set) alpha_type =                       XTAL_STD_(flt, 0) ;
//	XTAL_TYP_(set) aphex_type = _std::complex<alpha_type>;
	XTAL_TYP_(set)    fitting = _detail::fitting<sigma_type>;
	XTAL_DEF_(set)   negative =  fitting{ 8};
	XTAL_DEF_(set)   positive =  fitting{ 7};
	XTAL_DEF_(set)   fraction =  fitting{ 4};
	XTAL_DEF_(set)   IEC      =  constant_t<sigma_type{0}>{};
	XTAL_DEF_(set)   FMA      =  constant_t<sigma_type{0}>{};
	XTAL_TYP_(set)   MT19937  =  void;

};
template <>
struct fit_recognize<0x2>
{
	XTAL_TYP_(set)        fix =  cardinal_constant_t<0>;
	XTAL_TYP_(set) delta_type = _std::  make_signed_t<XTAL_STD_(int, 1)>;
	XTAL_TYP_(set) sigma_type = _std::make_unsigned_t<XTAL_STD_(int, 1)>;
//	XTAL_TYP_(set) alpha_type =                       XTAL_STD_(flt, 1) ;
//	XTAL_TYP_(set) aphex_type = _std::complex<alpha_type>;
	XTAL_TYP_(set)    fitting = _detail::fitting<sigma_type>;
	XTAL_DEF_(set)   negative =  fitting{16};
	XTAL_DEF_(set)   positive =  fitting{15};
	XTAL_DEF_(set)   fraction =  fitting{10};
	XTAL_DEF_(set)   IEC      =  constant_t<sigma_type{0}>{};
	XTAL_DEF_(set)   FMA      =  constant_t<sigma_type{0}>{};
	XTAL_TYP_(set)   MT19937  =  void;

};
#if 0x20 <= XTAL_SYS_(CPU)
template <>
struct fit_recognize<0x4>
{
	XTAL_TYP_(set)        fix =  cardinal_constant_t<0>;
	XTAL_TYP_(set) delta_type = _std::  make_signed_t<XTAL_STD_(int, 2)>;
	XTAL_TYP_(set) sigma_type = _std::make_unsigned_t<XTAL_STD_(int, 2)>;
	XTAL_TYP_(set) alpha_type =                       XTAL_STD_(flt, 2) ;
	XTAL_TYP_(set) aphex_type = _std::complex<alpha_type>;
	XTAL_TYP_(set)    fitting = _detail::fitting<sigma_type>;
	XTAL_DEF_(set)   negative =  fitting{32};
	XTAL_DEF_(set)   positive =  fitting{31};
	XTAL_DEF_(set)   fraction =  fitting{23};

	XTAL_DEF_(set)   IEC      =  constant_t<sigma_type{_std::numeric_limits<alpha_type>::is_iec559? XTAL_SYS_(IEC): 0}>{};
#ifdef FP_FAST_FMAF
	XTAL_DEF_(set)   FMA      =  constant_t<sigma_type{1}>{};
#else
	XTAL_DEF_(set)   FMA      =  constant_t<sigma_type{0}>{};
#endif
	XTAL_TYP_(set)   MT19937  = _std::mersenne_twister_engine<sigma_type, 32, 624, 397, 31
	,	0x9908B0DFU, 11
	,	0xFFFFFFFFU,  7
	,	0x9D2C5680U, 15
	,	0xEFC60000U, 18
	,	0x6C078965U
	>;

};
#endif
#if 0x40 <= XTAL_SYS_(CPU)
template <>
struct fit_recognize<0x8>
{
	XTAL_TYP_(set)        fix =  cardinal_constant_t<0>;
	XTAL_TYP_(set) delta_type = _std::  make_signed_t<XTAL_STD_(int, 3)>;
	XTAL_TYP_(set) sigma_type = _std::make_unsigned_t<XTAL_STD_(int, 3)>;
	XTAL_TYP_(set) alpha_type =                       XTAL_STD_(flt, 3) ;
	XTAL_TYP_(set) aphex_type = _std::complex<alpha_type>;
	XTAL_TYP_(set)    fitting = _detail::fitting<sigma_type>;
	XTAL_DEF_(set)   negative =  fitting{64};
	XTAL_DEF_(set)   positive =  fitting{63};
	XTAL_DEF_(set)   fraction =  fitting{52};

	XTAL_DEF_(set)   IEC      =  constant_t<sigma_type{_std::numeric_limits<alpha_type>::is_iec559? XTAL_SYS_(IEC): 0}>{};
#ifdef FP_FAST_FMA
	XTAL_DEF_(set)   FMA      =  constant_t<sigma_type{1}>{};
#else
	XTAL_DEF_(set)   FMA      =  constant_t<sigma_type{0}>{};
#endif
	XTAL_TYP_(set)   MT19937  = _std::mersenne_twister_engine<sigma_type, 64, 312, 156, 31
	,	0xB5026F5A'A96619E9U, 29
	,	0x55555555'55555555U, 17
	,	0x71D67FFF'EDA60000U, 37
	,	0xFFF7EEE0'00000000U, 43
	,	0x5851F42D'4C958000U
	>;

};
#endif
#ifndef XTAL_DOC
template <size_type N_size>
concept fit_recognized_q = antecedent_q<typename fit_recognize<N_size>::fix>;
#endif


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef XTAL_DOC
template <size_type N_size>
struct fit_rationalize : fit_rationalize<N_size/2>
{
	using fix = succedent_s<typename fit_recognize<N_size/2>::fix>;

};
#endif
template <size_type N_size> requires fit_recognized_q<N_size>
struct fit_rationalize<N_size> : fit_recognize<N_size>
{
private:
	using S_ = fit_recognize<N_size>;

public:
	XTAL_TYP_(set) typename S_::sigma_type;
	XTAL_TYP_(set) typename S_::delta_type;
	XTAL_DEF_(set)    sigma_0 = sigma_type{0};
	XTAL_DEF_(set)    sigma_1 = sigma_type{1};
	XTAL_DEF_(set)    delta_0 = delta_type{0};
	XTAL_DEF_(set)    delta_1 = delta_type{1};

	XTAL_DEF_(return,inline,set) value_f(cardinal_q auto  i) noexcept -> auto {return static_cast<sigma_type>(i);}
	XTAL_DEF_(return,inline,set) value_f( ordinal_q auto  i) noexcept -> auto {return static_cast<delta_type>(i);}
	XTAL_DEF_(return,inline,set) value_f(sigma_type const i) noexcept -> auto {return                        (i);}
	XTAL_DEF_(return,inline,set) value_f(delta_type const i) noexcept -> auto {return                        (i);}

	XTAL_TYP_(set) S_::negative;
	XTAL_TYP_(set) S_::positive;
	XTAL_TYP_(set) S_::fraction;
	XTAL_DEF_(set)     exponent = typename S_::fitting{positive.depth - fraction.depth, fraction.depth};
	XTAL_DEF_(set)         unit = typename S_::fitting{exponent.depth -        sigma_1, fraction.depth};
	XTAL_DEF_(set)         sign = typename S_::fitting{negative.depth - positive.depth, positive.depth};
	XTAL_DEF_(set)         full = typename S_::fitting{negative.depth};
	XTAL_DEF_(set)         half = typename S_::fitting{full.depth/2, full.depth/2};

	XTAL_DEF_(set)         default_alignment = cardinal_constant_t<XTAL_SYS_(L1)/full.width>{};
#ifdef __cpp_lib_hardware_interference_size
	XTAL_DEF_(set)    constructive_alignment = cardinal_constant_t<_std::hardware_constructive_interference_size/full.width>{};
	XTAL_DEF_(set)     destructive_alignment = cardinal_constant_t<_std:: hardware_destructive_interference_size/full.width>{};
#else
	XTAL_DEF_(set)    constructive_alignment = default_alignment;
	XTAL_DEF_(set)     destructive_alignment = default_alignment;
#endif
	XTAL_DEF_(set)                 alignment = destructive_alignment;


///////////////////////////////////////////////////////////////////////////////
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef XTAL_DOC
template <size_type N_size>
struct fit_realize : fit_realize<N_size/2>
{
	using fix = succedent_s<typename fit_recognize<N_size/2>::fix>;

	template <int N_shift=0>
	using adjust = fit_realize<(N_shift < 0)? (N_size >> -N_shift): (N_size << N_shift)>;

};
template <size_type N_size> requires fit_recognized_q<N_size>
struct fit_realize<N_size> : fit_rationalize<N_size>
{
	template <int N_shift=0>
	using adjust = fit_realize<(N_shift < 0)? (N_size >> -N_shift): (N_size << N_shift)>;

};
#endif
template <size_type N_size> requires fit_recognized_q<N_size> and requires {typename fit_recognize<N_size>::alpha_type;}
struct fit_realize<N_size> : fit_rationalize<N_size>
{
private:
	using S_ = fit_rationalize<N_size>;

public:
	template <int N_shift=0>
	using adjust = fit_realize<(N_shift < 0)? (N_size >> -N_shift): (N_size << N_shift)>;
	using halved = fit_realize<(N_size >> 1)>;

	using S_:: negative;
	using S_:: positive;
	using S_:: fraction;
	using S_:: exponent;
	using S_::     unit;
	using S_::     sign;
	using S_::     full;
	using S_::     half;
	using S_::  sigma_0;
	using S_::  sigma_1;
	using S_::  delta_0;
	using S_::  delta_1;

	XTAL_TYP_(set) typename S_::MT19937;
	XTAL_TYP_(set) typename S_::sigma_type;
	XTAL_TYP_(set) typename S_::delta_type;
	XTAL_TYP_(set) typename S_::alpha_type;
	XTAL_TYP_(set) typename S_::aphex_type;
	XTAL_DEF_(set)    alpha_0 = alpha_type{0};
	XTAL_DEF_(set)    alpha_1 = alpha_type{1};
	XTAL_DEF_(set)    aphex_0 = aphex_type{0, 0};
	XTAL_DEF_(set)    aphex_1 = aphex_type{1, 0};
	XTAL_DEF_(set)    aphex_i = aphex_type{0, 1};

	XTAL_DEF_(return,inline,set)
	delta_f(auto &&o)
	noexcept -> delta_type
	{
		if constexpr (cardinal_q<decltype(o)>) {return _std::bit_cast<delta_type>(static_cast<sigma_type>(XTAL_REF_(o)));}
		else                                   {return    static_cast<delta_type>(                        XTAL_REF_(o) );}
	}
	XTAL_DEF_(return,inline,set)
	sigma_f(auto &&o)
	noexcept -> sigma_type
	{
		if constexpr (cardinal_q<decltype(o)>) {return    static_cast<sigma_type>(                        XTAL_REF_(o) );}
		else                                   {return _std::bit_cast<sigma_type>(static_cast<delta_type>(XTAL_REF_(o)));}
	}
	XTAL_DEF_(return,inline,set)
	alpha_f(auto &&o)
	noexcept -> alpha_type
	{
		if constexpr (integral_q<decltype(o)>) {return    static_cast<alpha_type>(delta_f(XTAL_REF_(o)));}
		else                                   {return    static_cast<alpha_type>(        XTAL_REF_(o) );}
	}

	XTAL_DEF_(return,inline,set)
	aphex_f(simplex_q auto &&o_re, simplex_q auto &&o_im)
	noexcept -> aphex_type
	{
		return {alpha_f(XTAL_REF_(o_re)), alpha_f(XTAL_REF_(o_im))};
	}
	XTAL_DEF_(return,inline,set)
	aphex_f(simplex_q auto &&o_re)
	noexcept -> aphex_type
	{
		return {alpha_f(XTAL_REF_(o_re))};
	}
	XTAL_DEF_(return,inline,set)
	aphex_f(complex_q auto &&o)
	noexcept -> aphex_type
	{
		return aphex_f(o.real(), o.imag());
	}

	XTAL_DEF_(return,inline,set) value_f(integral_q auto i) noexcept -> auto {return             S_::value_f(i);}
	XTAL_DEF_(return,inline,set) value_f(alpha_type      i) noexcept -> auto {return                        (i);}
	XTAL_DEF_(return,inline,set) value_f(    real_q auto i) noexcept -> auto {return static_cast<alpha_type>(i);}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	/*!
	\returns	The `constexpr` equivalent of `std:pow(2.0, n_zoom)*(o_silon)`.
	*/
	XTAL_DEF_(return,inline,set)
	diplo_f(delta_type n_zoom, alpha_type o_silon)
	noexcept -> alpha_type
	{
		XTAL_IF1_(consteval) {
			auto m = _xtd::bit_cast<sigma_type>(n_zoom);
			m  += unit.mark;
			m <<= 1 + exponent.shift;
			m >>= 1;
			return o_silon*_xtd::bit_cast<alpha_type>(m);
		}
		XTAL_0IF_(else) {
			return _std::ldexp(o_silon, (int) n_zoom);// not `constexpr` until `C++23`!
		}
	}
	XTAL_DEF_(return,inline,set)
	diplo_f(sigma_type n_zoom, alpha_type o_silon)
	noexcept -> alpha_type
	{
		return diplo_f(_xtd::bit_cast<delta_type>(n_zoom), o_silon);
	}
	XTAL_DEF_(return,inline,set)
	diplo_f(alpha_type n_zoom, alpha_type o_silon)
	noexcept -> alpha_type
	{
		XTAL_IF1_(consteval) {
			int constexpr M = 0x01;
			int constexpr N = 0x10;

			auto n = static_cast<delta_type>(n_zoom);
			auto u = n_zoom - n;
			u *= _std::numbers::ln2_v<alpha_type>/diplo_f(M, alpha_1);

			auto v = alpha_1;
			for (auto i=N; i; --i) {v = _xtd::plus_multiplies_f(alpha_1, v, u/i);}
			for (auto i=M; i; --i) {v *= v;}

			v *= diplo_f(n, alpha_1);
			return o_silon*v;
		}
		XTAL_0IF (XTAL_SYS_(builtin)) {
			return o_silon*__builtin_exp2(n_zoom);
		}
		else {
			auto constexpr N_ln2 = _std::numbers::ln2_v<alpha_type>;
			return o_silon*exp(n_zoom*N_ln2);// TODO: Handle `constant`?
		}
	}
	XTAL_DEF_(return,inline,set) diplo_f(auto n_zoom, alpha_type o_silon)
	noexcept -> auto
	{
		return diplo_f(value_f(XTAL_REF_(n_zoom)), o_silon);
	}

	template <int N_silon=0>
	XTAL_DEF_(return,inline,set)
	diplo_f(auto const &n_zoom)
	noexcept -> alpha_type
	{
		auto constexpr o_silon = alpha_1/alpha_type{sigma_1 << fraction.depth - sign_v<N_silon>*N_silon};
		XTAL_IF0
		XTAL_0IF (0 < N_silon) {return diplo_f(n_zoom, alpha_1 + alpha_type{0.50}/o_silon);}
		XTAL_0IF (N_silon < 0) {return diplo_f(n_zoom, alpha_1 - alpha_type{0.25}/o_silon);}
		XTAL_0IF_(else)        {return diplo_f(n_zoom,           alpha_type{1.00}        );}
	}
	template <int N_silon=0>
	XTAL_DEF_(return,inline,set)
	diplo_f()
	noexcept -> alpha_type
	{
		return diplo_f<N_silon>(full.depth);
	}
	XTAL_DEF_(set) diplo_0 = diplo_f(0);
	XTAL_DEF_(set) diplo_1 = diplo_f(1);
	XTAL_DEF_(set) diplo_2 = diplo_f(2);


	/*!
	\returns	The `constexpr` equivalent of `std:pow(0.5, n_zoom)`.
	*/
	template <int N_silon=0> XTAL_DEF_(return,inline,set) haplo_f(auto const &n_zoom) noexcept -> auto {return diplo_f<-N_silon>(-   n_zoom );}
	template <int N_silon=0> XTAL_DEF_(return,inline,set) haplo_f(                  ) noexcept -> auto {return diplo_f<-N_silon>(-full.count);}
	XTAL_DEF_(set) haplo_0 = haplo_f(0);
	XTAL_DEF_(set) haplo_1 = haplo_f(1);
	XTAL_DEF_(set) haplo_2 = haplo_f(2);


////////////////////////////////////////////////////////////////////////////////

	/*!
	\returns	The `n_num`erator divided by the given de`n_nom`inator.
	*/
	template <int N_pow=1>
	XTAL_DEF_(return,inline,set)
	ratio_f(alpha_type n_num, alpha_type n_nom=1)
	noexcept -> alpha_type
	{
		XTAL_IF0
		XTAL_0IF (N_pow ==  0) {return           1;}
		XTAL_0IF (N_pow ==  1) {return n_num/n_nom;}
		XTAL_0IF (N_pow == -1) {return n_nom/n_num;}
		XTAL_0IF (N_pow <= -2) {return ratio_f<-N_pow>(n_nom, n_num);}
		XTAL_0IF (N_pow >=  2) {
			alpha_type const n = n_num/n_nom;
			alpha_type       o = 1;
			#pragma unroll
			for (int i{}; i < N_pow; ++i) {o *= n;} return o;
		}
		XTAL_0IF_(void)
	}
	XTAL_DEF_(set) ratio_0 = ratio_f(0, 1);
	XTAL_DEF_(set) ratio_1 = ratio_f(1, 1);
	XTAL_DEF_(set) ratio_2 = ratio_f(2, 1);

	/*!
	\returns	The ratio of `n_num` to `n_nom` multiplied by `Pi`.
	*/
	template <int N_pow=1>
	XTAL_DEF_(return,inline,set)
	patio_f(alpha_type n_num, alpha_type n_nom=1)
	noexcept -> alpha_type
	{
		return ratio_f<N_pow>(_std::numbers::pi_v<alpha_type>*n_num, n_nom);
	}
	XTAL_DEF_(set) patio_0 = patio_f(0, 1);
	XTAL_DEF_(set) patio_1 = patio_f(1, 1);
	XTAL_DEF_(set) patio_2 = patio_f(2, 1);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	/*!
	\returns	The difference between floating-point values at the scale designated by `n_zoom`.
	*/
	XTAL_DEF_(return,inline,set)
	epsilon_f(delta_type const &n_zoom=1)
	noexcept -> alpha_type
	{
		auto constexpr N = fraction.depth + 1;
		return haplo_f(N - n_zoom);
	}

	/*!
	\returns	The value `n_zoom` steps above `(alpha_type) 1`.
	*/
	XTAL_DEF_(return,inline,set)
	upsilon_f(delta_type const &n_zoom=1, delta_type const &n_zone=0)
	noexcept -> alpha_type
	{
		auto constexpr N_diff = fraction.depth + 1;
		auto const     n_unit = alpha_1 + haplo_f(N_diff - n_zoom);
		return n_unit*diplo_f(n_zone);
	}

	/*!
	\returns	The value `n_zoom` steps below `(alpha_type) 1`.
	*/
	XTAL_DEF_(return,inline,set)
	dnsilon_f(delta_type const &n_zoom=1, delta_type const &n_zone=0)
	noexcept -> alpha_type
	{
		auto constexpr N_diff = fraction.depth + 2;
		auto const     n_unit = alpha_1 - haplo_f(N_diff - n_zoom);
		return n_unit*diplo_f(n_zone);
	}


////////////////////////////////////////////////////////////////////////////////

	/*!
	\returns	The minimum value that accomodates exponentiation by `n_zoom` without underflow.
	\note    Equivalent to `_std::numeric_limits<alpha_type>::min()/2`.
	*/
	XTAL_DEF_(return,inline,set)
	minilon_f(delta_type const &n_zoom=0)
	noexcept -> alpha_type
	{
		return haplo_f(unit.mark >> n_zoom);
	}

	/*!
	\returns	The minimum of the given arguments `xs...`, evaluated with respect to type `alpha_type`.
	*/
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
		using W = XTAL_ALL_(w);
		using X = XTAL_ALL_(x);
		XTAL_IF0
		XTAL_0IF (sizeof(W) < full.width) {
			return minimum_f(value_f(XTAL_REF_(w)), XTAL_REF_(x));
		}
		XTAL_0IF (sizeof(X) < full.width) {
			return minimum_f(XTAL_REF_(w), value_f(XTAL_REF_(x)));
		}
		XTAL_0IF (different_q<W, X>) {
			return w > x? XTAL_REF_(x): XTAL_REF_(w);
		}
		XTAL_0IF_(consteval) {
			auto m_ = -  static_cast<delta_type>(w > x);
			auto w_ = _xtd::bit_cast<delta_type>(XTAL_REF_(w));
			auto x_ = _xtd::bit_cast<delta_type>(XTAL_REF_(x));
			w_ ^= x_; m_ &= w_;
			x_ ^= m_;
			w_ ^= x_;
			return _xtd::bit_cast<W>(w_);
		}
		XTAL_0IF_(else) {
			return _std::min<W>({XTAL_REF_(w), XTAL_REF_(x)});
		}
	}
	XTAL_DEF_(return,inline,set)
	minimum_f(auto &&w, auto &&x, auto &&...xs)
	noexcept -> decltype(auto)
	{
		return minimum_f(minimum_f(XTAL_REF_(w), XTAL_REF_(x)), XTAL_REF_(xs)...);
	}

	/*!
	\returns	The maximum value that accomodates exponentiation by `n_zoom` without overflow.
	\note    Equivalent to `2/_std::numeric_limits<alpha_type>::min()`.
*/
	XTAL_DEF_(return,inline,set)
	maxilon_f(delta_type const &n_zoom=0)
	noexcept -> alpha_type
	{
		return diplo_f(unit.mark >> n_zoom);
	}

	/*!
	\returns	The maximum of the given arguments `xs...`, evaluated with respect to type `alpha_type`.
	*/
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
		using W = XTAL_ALL_(w);
		using X = XTAL_ALL_(x);
		XTAL_IF0
		XTAL_0IF (sizeof(W) < full.width) {
			return maximum_f(value_f(XTAL_REF_(w)), XTAL_REF_(x));
		}
		XTAL_0IF (sizeof(X) < full.width) {
			return maximum_f(XTAL_REF_(w), value_f(XTAL_REF_(x)));
		}
		XTAL_0IF (different_q<W, X>) {
			return w < x? XTAL_REF_(x): XTAL_REF_(w);
		}
		XTAL_0IF_(consteval) {
			auto m_ = -  static_cast<delta_type>(w < x);
			auto w_ = _xtd::bit_cast<delta_type>(XTAL_REF_(w));
			auto x_ = _xtd::bit_cast<delta_type>(XTAL_REF_(x));
			w_ ^= x_; m_ &= w_;
			x_ ^= m_;
			w_ ^= x_;
			return _xtd::bit_cast<W>(w_);
		}
		XTAL_0IF_(else) {
			return _std::max<W>({XTAL_REF_(w), XTAL_REF_(x)});
		}
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
	mantissa_f(MT19937 &m)
	noexcept -> alpha_type
	{
		return mantissa_f(m());
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
};


}///////////////////////////////////////////////////////////////////////////////
/*!
\brief  	Provides floating-point format information and related helpers.
\note   	Resolves to the maximum supported `sizeof <= 8`.
\details	Reduces the supplied parameters to the common scalar, using the `sizeof` to index the underlying provider.
*/
template <class ...Ts> struct fit       : complete_t<_detail::fit_realize<sizeof(unstruct_t<Ts...>)>> {};
template <           > struct fit<void> : fit<size_type> {};
template <           > struct fit<    > : fit<size_type> {};


///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
