#pragma once
#include "./any.hpp"
#include "./utilize.hpp"





XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///\
Establishes the base types for the supplied `N_size` \
(which should be representative of the desired `std::size_t`): \
\
-	`aleph_t` represents floating-point complex numbers. \
-	`alpha_t` represents floating-point real numbers. \
-	`sigma_t` represents full-width `unsigned int`s like `std::size`. \
-	`delta_t` represents full-width   `signed int`s used for binary and integer arithmetic. \
-	`iota_t`  represents half-width   `signed int`s required for `ranges::difference_type`. \
-	`flux_t`  represents the ternary return value for `/(de|ef|in)(?:flux|fuse)/`, \
	indicating either that the state has changed (`+1`), the state remains unchanged (`0`), \
	or that the message wasn't handled (`-1`). \
\
The constants labelled `carmack_v` are provided for `Q_rsqrt` (in lieu of `constexpr`). \

template <XTAL_STD_SIZE>
struct systematization;

template <>
struct systematization<1>
{
//	using      flux_t  =       _std::int_fast8_t;
//	using      iota_t  =       _std::int4_t;
	using     delta_t  =   signed      char;
	using     sigma_t  = unsigned      char;
//	using     alpha_t  =     _std::float8_t;
	XTAL_LET_(sigma_t)      fraction_n =  4;
	XTAL_LET_(sigma_t)      exponent_n =  3;

};
template <>
struct systematization<2>
{
	using      flux_t  =       _std::int_fast16_t;
	using      iota_t  =       _std::int8_t;
	using     delta_t  =   signed short int;
	using     sigma_t  = unsigned short int;
//	using     alpha_t  =    _std::float16_t;
	XTAL_LET_(sigma_t)      fraction_n = 10;
	XTAL_LET_(sigma_t)      exponent_n =  5;

};
template <>
struct systematization<4>
{
	using      flux_t  =      _std::int_fast32_t;
	using      iota_t  =      _std::int16_t;
	using     delta_t  =   signed       int;
	using     sigma_t  = unsigned       int;
	using     alpha_t  =              float;
	XTAL_LET_(sigma_t)      fraction_n = 23;
	XTAL_LET_(sigma_t)      exponent_n =  8;
//	XTAL_LET_(sigma_t)       carmack_m = 0x5f3759df;
	XTAL_LET_(alpha_t)       carmack_v = 13211836172961054720.;

	using mt19937_t = _std::mersenne_twister_engine<sigma_t, 32, 624, 397, 31
	,	0x9908b0df, 11
	,	0xffffffff,  7
	,	0x9d2c5680, 15
	,	0xefc60000, 18
	,	1812433253
	>;

};
template <>
struct systematization<8>
{
	using      flux_t  =      _std::int_fast64_t;
	using      iota_t  =      _std::int32_t;
	using     delta_t  =   signed long  int;
	using     sigma_t  = unsigned long  int;
	using     alpha_t  =             double;
	XTAL_LET_(sigma_t)      fraction_n = 52;
	XTAL_LET_(sigma_t)      exponent_n = 11;
//	XTAL_LET_(sigma_t)       carmack_m = 0x5fe6eb50c7b537a9;//-Wconstant-conversion
	XTAL_LET_(alpha_t)       carmack_v =\
9603007803048108861399\
4805888797202081276539\
3074306646911819923505\
5127342612577990950479\
1958781678276435340763\
5938084899034689508292\
4854912593744361422848\
.;

	using mt19937_t = _std::mersenne_twister_engine<sigma_t, 64, 312, 156, 31
	,	0xb5026f5aa96619e9, 29
	,	0x5555555555555555, 17
	,	0x71d67fffeda60000, 37
	,	0xfff7eee000000000, 43
	,	6364136223846793005
	>;

};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <XTAL_STD_SIZE N_size>
struct rationalization
:	systematization<N_size>
{
private:
	using co = systematization<N_size>;

public:
	using typename co::delta_t;
	using typename co::sigma_t;

	XTAL_LET_(sigma_t)   width = N_size;
	XTAL_LET_(sigma_t)   depth = N_size << 3;
	XTAL_LET_(sigma_t) breadth = N_size >> 2;

	XTAL_LET_(sigma_t) fraction_n =          co::fraction_n;
	XTAL_LET_(sigma_t) exponent_n =          co::exponent_n;
	XTAL_LET_(sigma_t) positive_n = fraction_n + exponent_n;
	XTAL_LET_(sigma_t) negative_n = positive_n + 1;
	XTAL_LET_(sigma_t)     unit_n = exponent_n - 1;
	XTAL_LET_(sigma_t)     sign_n =              1;
	static_assert(negative_n == depth);

	XTAL_FZ2_(sigma_t) bit_flag_y(sigma_t const m=0)                    XTAL_0EX {return sigma_t(m <= negative_n) << m;};
	XTAL_FZ2_(sigma_t) bit_mark_y(sigma_t const m=0)                    XTAL_0EX {return bit_flag_y(m)  - 1;};
	XTAL_FZ2_(sigma_t) bit_mask_y(sigma_t const m=0, sigma_t const n=0) XTAL_0EX {return bit_mark_y(m) << n;};

	template <sigma_t M_depth, sigma_t N_shift>
	struct word
	{
		XTAL_LET_(sigma_t) depth = M_depth;
		XTAL_LET_(sigma_t) shift = N_shift;
		XTAL_LET_(sigma_t) mark = bit_mark_y(M_depth);
		XTAL_LET_(sigma_t) mask = bit_mask_y(M_depth, N_shift);
	};
	struct negative: word<negative_n,          0> {};
	struct positive: word<positive_n,          0> {};
	struct fraction: word<fraction_n,          0> {};
	struct exponent: word<exponent_n, fraction_n> {};
	struct     unit: word<    unit_n, fraction_n> {};
	struct     sign: word<    sign_n, positive_n> {};
	static_assert((sigma_t) ~sign::mask == positive::mask);


};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <XTAL_STD_SIZE N_size>
struct realization: rationalization<N_size>
{
};
template <XTAL_STD_SIZE N_size>
requires _std::floating_point<typename rationalization<N_size>::alpha_t>
struct realization<N_size>: rationalization<N_size>
{
private:
	using co = rationalization<N_size>;

public:
	using typename co:: negative;
	using typename co:: positive;
	using typename co:: fraction;
	using typename co:: exponent;
	using typename co::     unit;
	using typename co::     sign;

	using typename co::   iota_t;
	using typename co::  delta_t;
	using typename co::  sigma_t;
	using typename co::  alpha_t; using aleph_t = _std::complex<alpha_t>;
	using typename co::mt19937_t;

	using co::breadth;
	using co::  width;
	using co::  depth;

	#if XTAL_STD_IEEE == 754
		static_assert(_std::numeric_limits<alpha_t>::is_iec559);
	#endif


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	XTAL_FZ2 unit_y(sigma_t n)
	XTAL_0EX
	{
		return std::bit_cast<alpha_t>(n & ~unit::mask);
	}
	XTAL_FZ2 unit_y(mt19937_t &m)
	XTAL_0EX
	{
		return unit_y(m());
	}


///////////////////////////////////////////////////////////////////////////////

	XTAL_FZ2_(alpha_t) dot_y(aleph_t const &u)
	XTAL_0EX
	{
		alpha_t const x = u.real(), xx = square_y(x);
		alpha_t const y = u.imag(), yy = square_y(y);
		return xx + yy;
	}

	template <delta_t M_iso=1>
	XTAL_FZ2 circle_y(auto const &u)
	XTAL_0EX
	{
		if constexpr (M_iso == +1)
		{
			return aleph_t(_std::cos(u), _std::sin(u));
		}
		else
		if constexpr (M_iso == -1)
		{
			return alpha_t(_std::atan2(u));
		}
	}

	template <delta_t M_iso=1, delta_t M_pow=1, delta_t N_ord=-1>
	XTAL_FZ2_(alpha_t) square_y(alpha_t const &u)
	XTAL_0EX
	{
		if constexpr (M_iso == +1 and M_pow == +1)
		{
			return (u*u);
		}
		else
		if constexpr (M_iso == +1 and M_pow == -1)
		{
			return square_y<M_iso, -M_pow, N_ord>(1/u);
		}
		else
		if constexpr (M_iso == -1 and M_pow == +1)
		{
			if (not _std::is_constant_evaluated()) return _std::sqrt(u);
			return square_y<M_iso, -M_pow, N_ord>(u)*(u);
		}
		else
		if constexpr (M_iso == -1 and M_pow == -1)
		{
			if (not _std::is_constant_evaluated()) return 1/_std::sqrt(u);
			delta_t o = _std::bit_cast<delta_t>(co::carmack_v); o -= _std::bit_cast<delta_t>(u) >> 1;
			alpha_t n = _std::bit_cast<alpha_t>(o);
			alpha_t const k = u*0.5;
			if constexpr (0 < N_ord)
			{
				seek_f<N_ord>([&] (auto) XTAL_0FN_(n *= alpha_t(1.5) - k*n*n));
			}
			else
			{
				alpha_t _n; o = 0x20;
				do    {_n  = n; n *= 1.5 - k*n*n;}
				while (_n != n and ~--o);
				n /= alpha_t(0.5) + k*n*n;
			}
			return n;
		}
	}
	static_assert(square_y<-1,  1>((alpha_t) 2) == (alpha_t) 0.1414213562373095048801688724209698079e+1);
	static_assert(square_y<-1, -1>((alpha_t) 2) == (alpha_t) 0.7071067811865475244008443621048490393e+0);

	XTAL_FZ2_(aleph_t) square_y(aleph_t const &u)
	XTAL_0EX
	{
		alpha_t const x = u.real(), xx = square_y(x);
		alpha_t const y = u.imag(), yy = square_y(y);
		return aleph_t(xx - yy, x*y*2.0);
	}

	template <delta_t M_iso=1, delta_t M_pow=1, delta_t N_ord=-1>
	XTAL_FZ2_(alpha_t) square_dot_y(XTAL_DEF_(is_q<aleph_t>) u)
	XTAL_0EX
	{
		return square_y<M_iso, M_pow, N_ord>(dot_y(XTAL_REF_(u)));
	}


////////////////////////////////////////////////////////////////////////////////

	///\returns the `constexpr` equivalent of `std:pow(2.0, zoom)`. \

	XTAL_FZ2 diplo_y(delta_t const &zoom)
	XTAL_0EX
	{
	#if XTAL_STD_IEEE == 754
		delta_t m = zoom << unit::shift;
		m += unit::mask;
		m &= exponent::mask;
		return _std::bit_cast<alpha_t> (m);
	#else
		sigma_t const i_sgn =   zoom >> positive::depth;
		sigma_t const i_neg = -(zoom &  i_sgn);
		sigma_t const i_pos =  (zoom & ~i_sgn);
		return alpha_t((sigma_t) 1 << i_pos)/((sigma_t) 1 << i_neg);
	#endif
	}
	template <delta_t N_zoom=0>
	XTAL_LET diplo_v = diplo_y(N_zoom);
	///< Value expression of `diplo_y`. \

	static_assert(diplo_v<+1> == 2.0);
	static_assert(diplo_v< 0> == 1.0);
	static_assert(diplo_v<-1> == 0.5);


	///\returns the `constexpr` equivalent of `std:pow(0.5, zoom)`. \

	XTAL_FZ2 haplo_y(delta_t const &zoom)
	XTAL_0EX
	{
	#if XTAL_STD_IEEE == 754
		return diplo_y(-zoom);
	#else
		sigma_t const i_sgn =   zoom >> positive::depth;
		sigma_t const i_neg = -(zoom &  i_sgn);
		sigma_t const i_pos =  (zoom & ~i_sgn);
		return alpha_t((sigma_t) 1 << i_neg)/((sigma_t) 1 << i_pos);
	#endif
	}
	template <delta_t N_zoom=0>
	XTAL_LET haplo_v = haplo_y(N_zoom);
	///< Value expression of `haplo_y`. \

	static_assert(haplo_v<+1> == 0.5);
	static_assert(haplo_v< 0> == 1.0);
	static_assert(haplo_v<-1> == 2.0);


	///\returns the `constexpr` equivalent of `std:pow(base, zoom)` for an `unsigned int zoom`. \
	
	XTAL_FZ2 explo_y(sigma_t const &zoom, XTAL_DEF base)
	XTAL_0EX
	{
		XTAL_TYP_(base) u = XTAL_REF_(base), w = 1;
		for (sigma_t n = zoom; n; n >>= 1)
		{
			if (n & 1)
			{
				n ^= 1;
				w *= u;
			}
			u = square_y(u);
		}
		return w;
	}
	template <sigma_t N_zoom>
	XTAL_FZ2 explo_y(XTAL_DEF base)
	XTAL_0EX
	{
		if constexpr (0 == bit_count_v<N_zoom>)
		{
			return XTAL_TYP_(base) (1);
		}
		if constexpr (1 == bit_count_v<N_zoom>)
		{
			alpha_t w = XTAL_REF_(base);
			for (sigma_t n = N_zoom; n >>= 1; w = square_y(w));
			return w;
		}
		else
		{
			return explo_y(N_zoom, XTAL_REF_(base));
		}
	}
	static_assert(explo_y<0> (alpha_t(2.0)) == 1.00);
	static_assert(explo_y<1> (alpha_t(2.0)) == 2.00);
	static_assert(explo_y<2> (alpha_t(2.0)) == 4.00);


////////////////////////////////////////////////////////////////////////////////

	///\returns the `N_num`erator divided by the given de`nom`inator.

	template <auto N_num=1>
	XTAL_FZ2_(alpha_t) ratio_y(XTAL_DEF nom)
	XTAL_0EX
	{
		return alpha_t(N_num)/XTAL_REF_(nom);
	}
	using ratio_t = alpha_t (*const) (alpha_t const &);
	///< Function type of `ratio_y`. \

	template <auto N_num=1>
	XTAL_LET_(ratio_t) ratio_x = [] (alpha_t const& nom)
	XTAL_0FN_(ratio_y<N_num> (nom));
	///< Function expression of `ratio_y`. \

	///<\note The explicit function-type avoids potential interruptation fault \
	raised when dynamically resolving the nested templated lambda. \

	static_assert(ratio_y    (alpha_t(2.0)) == 0.5);
	static_assert(ratio_y<1> (alpha_t(2.0)) == 0.5);
	static_assert(ratio_y<4> (alpha_t(2.0)) == 2.0);


	///\returns `pi` times `ratio_y<N_num> (nom)`.

	template <auto N_num=1>
	XTAL_FZ2_(alpha_t) patio_y(XTAL_DEF u)
	XTAL_0EX
	{
		return ratio_y<N_num> (XTAL_REF_(u))*3.141592653589793238462643383279502884;
	}
	using patio_t = alpha_t (*const) (alpha_t const &);
	///< Function type of `patio_y`. \

	template <auto N_num=1>
	XTAL_LET_(patio_t) patio_x = [] (alpha_t const& nom)
	XTAL_0FN_(patio_y<N_num> (nom));
	///< Function expression of `patio_y`. \

	///<\note The explicit function-type avoids potential interruptation fault \
		raised when dynamically resolving the nested templated lambda. \

	static_assert(patio_y    (alpha_t(2.0)) == alpha_t(1.570796326794896619231321691639751442));
	static_assert(patio_y<1> (alpha_t(2.0)) == alpha_t(1.570796326794896619231321691639751442));
	static_assert(patio_y<4> (alpha_t(2.0)) == alpha_t(6.283185307179586476925286766559005768));


	XTAL_LET_(_std::array<alpha_t, 4>) codomain_vs {1.0
	,	0.159154943091895335768883763372514362//  1 => (Pi*2)^-1
	,	1.442695040888963407359924681001892137//  2 => Log[2]^-1
	,	0.318309886183790671537767526745028724// -1 => (Pi*1)^-1
	};
	XTAL_LET_(_std::array<alpha_t, 4>)   domain_vs {1.0
	,	6.283185307179586476925286766559005768//  1 => (Pi*2)
	,	0.693147180559945309417232121458176568//  2 => Log[2]
	,	3.141592653589793238462643383279502884// -1 => (Pi*1)
	};
	template <delta_t N_base, delta_t N_shift=0>
	XTAL_LET codomain_v = codomain_vs[N_base&0b11]*haplo_v<N_shift>;
///< Value expression representing the multiplicative inverse of the logarithmic `domain_v`.

	template <delta_t N_base, delta_t N_shift=0>
	XTAL_LET   domain_v =   domain_vs[N_base&0b11]*diplo_v<N_shift>;
///< Value expression representing the logarithmic domain for `N_base`, scaled by `diplo_y<N_shift>`. \
	Additionally scaled by `1*PI`, `2*PI`, or `LOG2` if `N_base` is `-1`, `1`, or `2` respectively.

///<\note The scaling w.r.t. `PI` reflects the imaginary logarithm where \
	`std::exp(std::complex(0, 1*PI)) == -1` and `std::exp(std::complex(0, 2*PI)) == 1`.

///<\note To convert between domains, multiply the target `domain_v` and source `codomain_v`. \

	static_assert(domain_v<-1> == patio_y<1>(1));
	static_assert(domain_v<-1> == domain_v<1, -1>);
	static_assert(domain_v<1, -0>*codomain_v<1, -0> == 1);
	static_assert(domain_v<1, -1>*codomain_v<1, -1> == 1);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\returns the difference between floating-point values at the scale designated by `zoom`. \

	XTAL_FZ2_(alpha_t) epsilon_y(delta_t const &zoom=1)
	XTAL_0EX
	{
		auto constexpr N = fraction::depth + 1;
		return haplo_y(N - zoom);
	}
	template <delta_t N_zoom=0>
	XTAL_LET epsilon_v = epsilon_y(N_zoom);
	///< Value expression of `epsilon_y`. \

	static_assert(epsilon_v<0> != 0);
	static_assert(epsilon_v<0> <  epsilon_v<1>);
	static_assert(epsilon_v<1> <  epsilon_v<2>);
	static_assert(epsilon_v<1> == _std::numeric_limits<alpha_t>::epsilon());
	

	///\returns the value `zoom` steps above `(alpha_t) 1`. \

	XTAL_FZ2_(alpha_t) upsilon_y(delta_t const &zoom=1, delta_t const &zone=0)
	XTAL_0EX
	{
		return (1 + epsilon_y(zoom + 1))*diplo_y(zone);
	}
	template <delta_t N_zoom=0>
	XTAL_LET upsilon_v = upsilon_y(N_zoom);
	///< Value expression of `upsilon_y`. \
	
	static_assert(upsilon_v<1> > upsilon_v<0>);
	static_assert(upsilon_v<2> > upsilon_v<1>);


	///\returns the value `zoom` steps below `(alpha_t) 1`. \

	XTAL_FZ2_(alpha_t) dnsilon_y(delta_t const &zoom=1, delta_t const &zone=0)
	XTAL_0EX
	{
		return (1 - epsilon_y(zoom + 0))*diplo_y(zone);
	}
	template <delta_t N_zoom=0>
	XTAL_LET dnsilon_v = dnsilon_y(N_zoom);
	///< Value expression of `dnsilon_y`. \
	
	static_assert(dnsilon_v<1> < dnsilon_v<0>);
	static_assert(dnsilon_v<2> < dnsilon_v<1>);
	

////////////////////////////////////////////////////////////////////////////////

	///\returns `std::numeric_limits<alpha_t>::min()` magnified by `diplo_y(zoom)`. \

	XTAL_FZ2_(alpha_t) minimal_y(delta_t const &zoom=0)
	XTAL_0EX
	{
		return diplo_y(zoom)*std::numeric_limits<alpha_t>::min();
	}
	template <delta_t N_zoom=0>
	XTAL_LET minimal_v = minimal_y(N_zoom);
	///< Value expression for `minimal_y`. \

	///\returns the minimum of the given arguments `xs...`, evaluated with respect to type `alpha_t`. \

	XTAL_FZ2 minimum_y()
	XTAL_0EX
	{
		return minimal_y();
	}
	XTAL_FZ2 minimum_y(XTAL_DEF ...values)
	XTAL_0EX
	{
		return _std::min<alpha_t> ({XTAL_REF_(values)...});
	}
	XTAL_LET  minimum_x = [] (XTAL_DEF ...values)
	XTAL_0FN_(minimum_y(XTAL_REF_(values)...));
	///< Function expression for `minimum_y`. \


	///\returns haplo_y(zoom)/std::numeric_limits<alpha_t>::min()`. \
	
	///\note Defined as the multiplicative inverse of `minimal_y`, \
		rather than w.r.t. `std::numeric_limits<alpha_t>::max()`, \
		which is two orders of (binary) magnitude larger. \

	XTAL_FZ2_(alpha_t) maximal_y(delta_t const &zoom=0)
	XTAL_0EX
	{
		return haplo_y(zoom)/std::numeric_limits<alpha_t>::min();
	}
	template <delta_t N_zoom=0>
	XTAL_LET maximal_v = maximal_y(N_zoom);
	///< Value expression for `maximal_y`. \

	///\returns the maximum of the given arguments `xs...`, evaluated with respect to type `alpha_t`. \

	XTAL_FZ2 maximum_y()
	XTAL_0EX
	{
		return maximal_y();
	}
	XTAL_FZ2 maximum_y(XTAL_DEF ...values)
	XTAL_0EX
	{
		return _std::max<alpha_t> ({XTAL_REF_(values)...});
	}
	XTAL_LET  maximum_x = [] (XTAL_DEF ...values)
	XTAL_0FN_(maximum_y(XTAL_REF_(values)...));
	///< Function expression for `maximum_y`. \


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\returns the sign of `value`. \

	XTAL_FZ2 sign_y(alpha_t const &value)
	XTAL_0EX
	{
		#ifdef XTAL_V00_MSVC
			static_assert(_std::numeric_limits<alpha_t>::is_iec559);
			delta_t u = _std::bit_cast<delta_t> (value);
			u &= sign::mask;
			u |= unit::mask;
			return _std::bit_cast<alpha_t> (_std::move(u));
		#else
			return __builtin_copysign((alpha_t) 1, value);
		#endif
	}
	XTAL_LET  sign_x = [] (XTAL_DEF value)
	XTAL_0FN_(sign_y(XTAL_REF_(value)));
	///< Function expression for `sign_y` \

	static_assert(sign_y( 0.5) ==  1.0);
	static_assert(sign_y( 0.0) ==  1.0);
	static_assert(sign_y(-0.5) == -1.0);


	///\returns the `target` magnitude with the sign of the `source`. \

	XTAL_FZ1_(alpha_t) resign_y(alpha_t target, alpha_t const &source=1)
	XTAL_0EX
	{
		#if XTAL_V00_MSVC
			static_assert(_std::numeric_limits<alpha_t>::is_iec559);
			delta_t n = _std::bit_cast<delta_t> (source);
			delta_t m = _std::bit_cast<delta_t> (target);
			m &=    ~sign::mask;
			m |= n & sign::mask;
			return _std::bit_cast<alpha_t> (_std::move(m));
		#else
			return __builtin_copysign(target, source);// constexpr
		#endif
	}

	///\returns the original sign of `target`, after applying the sign of `source`.

	XTAL_FZ1_(alpha_t) resign_z(alpha_t &target, alpha_t const &source=1)
	XTAL_0EX
	{
		alpha_t const signum = sign_y(target);
		target = resign_y(target, source);
		return signum;
	}


	///\returns the original sign of `target`, after making it `abs`olute.

	XTAL_FZ1_(alpha_t) design_z(alpha_t &target)
	XTAL_0EX
	{
		alpha_t const signum = sign_y(target);
		target *= signum;
		return signum;
	}
	///\returns the `abs`olute value of `target`. \

	XTAL_FZ1_(alpha_t) design_y(alpha_t target)
	XTAL_0EX
	{
		#if XTAL_V00_MSVC
			static_assert(_std::numeric_limits<alpha_t>::is_iec559);
			delta_t u = _std::bit_cast<delta_t> (target);
			u &= positive::mask;
			return _std::bit_cast<alpha_t> (_std::move(u));
		#else
			return __builtin_copysign(target, (alpha_t) 1);// constexpr
		#endif
	}
	XTAL_LET  design_x = [] (XTAL_DEF value)
	XTAL_0FN_(design_y(XTAL_REF_(value)));
	///< Function expression for `design_y` \

	static_assert(design_y( 1.0) ==  1.0);
	static_assert(design_y(-1.0) ==  1.0);


////////////////////////////////////////////////////////////////////////////////

	///\returns `value` when positive, zero otherwise. \

	template <delta_t N_proximity=0>
	XTAL_FZ2 positive_y(alpha_t value)
	XTAL_0EX
	{
		value *= haplo_y(1);
		if constexpr (0 < N_proximity) value -= minimal_v<N_proximity - 1>;
		value += design_y(value);
		if constexpr (0 < N_proximity) value += minimal_v<N_proximity - 1>;
		return value;
	}
	XTAL_LET  positive_x = [] (XTAL_DEF value)
	XTAL_0FN_(positive_y(XTAL_REF_(value)));
	///< Function expression for `positive_y` \

	static_assert(positive_y<0>( 1.0) ==  1.0);
	static_assert(positive_y<0>( 0.0) ==  0.0);
	static_assert(positive_y<0>(-1.0) ==  0.0);

	static_assert(positive_y<1>( 1.0) ==  1.0);
	static_assert(positive_y<1>( 0.0) ==  minimal_y());
	static_assert(positive_y<1>(-1.0) ==  minimal_y());


	///\returns `value` when negative, zero otherwise. \

	template <delta_t N_proximity=0>
	XTAL_FZ2 negative_y(alpha_t value)
	XTAL_0EX
	{
		value *= haplo_y(1);
		if constexpr (0 < N_proximity) value += minimal_v<N_proximity - 1>;
		value -= design_y(value);
		if constexpr (0 < N_proximity) value -= minimal_v<N_proximity - 1>;
		return value;
	}
	XTAL_LET  negative_x = [] (XTAL_DEF value)
	XTAL_0FN_(negative_y(XTAL_REF_(value)));
	///< Function expression for `negative_y` \
	
	static_assert(negative_y<0>( 1.0) ==  0.0);
	static_assert(negative_y<0>( 0.0) ==  0.0);
	static_assert(negative_y<0>(-1.0) == -1.0);

	static_assert(negative_y<1>( 1.0) == -minimal_y());
	static_assert(negative_y<1>( 0.0) == -minimal_y());
	static_assert(negative_y<1>(-1.0) == -1.0);


////////////////////////////////////////////////////////////////////////////////

	/// Modifies the `target`, clamping the magnitude below `dnsilon_y(N_zoom, zone)`. \

	///\returns zero if unchanged, else the sign of the `target`. \
	
	template <delta_t N_zoom=0, bool N_infinity=0>
	XTAL_FZ1_(alpha_t) truncate_z(alpha_t &target, delta_t const &zone)
	XTAL_0EX
	{
	#if XTAL_STD_IEEE == 754
		auto const Y = N_infinity + unit::mask - (1 << N_zoom);
		auto const N = zone << exponent::shift;
		auto const M = N + Y;
		delta_t m, n, i;
		auto  t  = _std::bit_cast<delta_t> (_std::move(target));
		n  =  t  &  sign::mask;
		m  =  t  ^  n;
		m  =  M  -  m;
		i  =  m >>  positive::depth;
		n |=  i  &  unit::mask;
		t +=  i  &  m;
		target   = _std::bit_cast<alpha_t> (_std::move(t));
		return     _std::bit_cast<alpha_t> (n);
	#else
		alpha_t const t = N_infinity? maximal_y(zone): dnsilon_y(N_zoom, zone);
		alpha_t const s = design_z(target);
		bool const r = t < target;
		if constexpr (N_infinity)
		{
			target = minimum_y(t, target);
		}
		else
		{
			target += negative_y(t - target);
		}
		target *= s; return r*s;
	#endif
	}
	/// Modifies the `target`, clamping the magnitude below `maximal_y(N_zoom)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <delta_t N_zoom=0>
	XTAL_FZ1_(alpha_t) truncate_z(alpha_t &target)
	XTAL_0EX
	{
	#if XTAL_STD_IEEE == 754
		auto constexpr zone = (((delta_t) 1 << unit::depth) - 2) - (N_zoom);
	#else
		auto constexpr zone = N_zoom;
	#endif
		return truncate_z<0, 1>(target, zone);
	}
	

	///\returns the `target` with magnitude clamped to the region below `dnsilon_y(N_zoom, zone)`. \

	template <delta_t N_zoom=0, bool N_infinity=0>
	XTAL_FZ2_(alpha_t) truncate_y(alpha_t target, delta_t const &zone)
	XTAL_0EX
	{
	#if XTAL_STD_IEEE == 754
		auto const Y = N_infinity + unit::mask - (1 << N_zoom);
		auto const N = zone << exponent::shift;
		auto const M = N + Y;
		delta_t m, n, i;
		auto  t  = _std::bit_cast<delta_t> (_std::move(target));
		m  =  t  & ~sign::mask;
		m  =  M  -  m;
		i  =  m >>  positive::depth;
		t +=  i  &  m;
		return     _std::bit_cast<alpha_t> (_std::move(t));
	#else
		alpha_t const t = N_infinity? maximal_y(zone): dnsilon_y(N_zoom, zone);
		alpha_t const s = design_z(target);
		if constexpr (N_infinity)
		{
			target = minimum_y(t, target);
		}
		else
		{
			target += negative_y(t - target);
		}
		target *= s; return target;
	#endif
	}
	///\returns the `target` with magnitude clamped to the region below `maximal_y(N_zoom)`. \

	template <delta_t N_zoom=0>
	XTAL_FZ2_(alpha_t) truncate_y(alpha_t const &target)
	XTAL_0EX
	{
	#if XTAL_STD_IEEE == 754
		auto constexpr zone = (((delta_t) 1 << unit::depth) - 2) - (N_zoom);
	#else
		auto constexpr zone = N_zoom;
	#endif
		return truncate_y<0, 1>(target, zone);
	}

	template <delta_t N_zoom=0>
	XTAL_FZ2 truncate_y(aleph_t const &target)
	XTAL_0EX
	{
		alpha_t const x = truncate_y<N_zoom>(target.real());
		alpha_t const y = truncate_y<N_zoom>(target.imag());
		return aleph_t {x, y};
	}
	template <delta_t N_zoom=0, bool N_zero=0>
	XTAL_FZ2 truncate_y(aleph_t target, delta_t const &zone)
	XTAL_0EX
	{
		target = truncate_y<16>(_std::move(target));// TODO: Handle infinity before `std::abs`.
		alpha_t w = square_dot_y<-1>(target), m = 1/w;
		target *= m; truncate_z<N_zoom, N_zero>(w, zone);
		target *= w;
		return target;
	}
	

////////////////////////////////////////////////////////////////////////////////

	/// Modifies the `target`, clamping the magnitude above `upsilon_y(N_zoom, zone)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <delta_t N_zoom=0, bool N_zero=0>
	XTAL_FZ1_(alpha_t) puncture_z(alpha_t &target, delta_t const &zone)
	XTAL_0EX
	{
		auto constexpr N_unit = N_zero^1;
	#if XTAL_STD_IEEE == 754
		auto const Z = unit::mask + (1 << N_zoom);
		auto const N = zone << exponent::shift;
		auto const M = N + Z*N_unit;
		delta_t m, n, i;
		auto  t  = _std::bit_cast<delta_t> (_std::move(target));
		n   = t  &  sign::mask;
		m   = t  ^  n;
		m  -= M;
		i   = m >>  positive::depth;
		n  |= i  &  unit::mask;
		t  -= i  &  m;
		target   = _std::bit_cast<alpha_t> (_std::move(t));
		return     _std::bit_cast<alpha_t> (_std::move(n));
	#else
		auto const t = N_zero? minimal_y(zone - 1): upsilon_y(N_zoom, zone);
		auto const s = design_z(target);
		auto const a = positive_y(t - target);
		target += a;
		target *= s;
		return s*(a != 0);
	#endif
	}
	/// Modifies the `target`, clamping the magnitude above `minimal_y(N_zoom)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <delta_t N_zoom=0>
	XTAL_FZ1_(alpha_t) puncture_z(alpha_t &target)
	XTAL_0EX
	{
		return puncture_z<0, 1>(target, N_zoom + 1);
	}
	

	///\returns the `target` with magnitude clamped to the region above `upsilon_y(N_zoom, zone)`. \

	template <delta_t N_zoom=0, bool N_zero=0>
	XTAL_FZ2_(alpha_t) puncture_y(alpha_t target, delta_t const &zone)
	XTAL_0EX
	{
		auto constexpr N_unit = N_zero^1;
	#if XTAL_STD_IEEE == 754
		auto const Z = unit::mask + (1 << N_zoom);
		auto const N = zone << exponent::shift;
		auto const M = N + Z*N_unit;
		delta_t m, n, i;
		auto  t  = _std::bit_cast<delta_t> (_std::move(target));
		m   = t  & ~sign::mask;
		m  -= M;
		i   = m >>  positive::depth;
		t  -= i  &  m;
		return     _std::bit_cast<alpha_t> (_std::move(t));
	#else
		auto const t = N_zero? minimal_y(zone - 1): upsilon_y(N_zoom, zone);
		auto const s = design_z(target);
		auto const a = positive_y(t - target);
		target += a;
		target *= s;
		return target;
	#endif
	}
	///\returns the `target` with magnitude clamped to the region above `minimal_y(N_zoom)`. \

	template <delta_t N_zoom=0>
	XTAL_FZ2_(alpha_t) puncture_y(alpha_t const &target)
	XTAL_0EX
	{
		return puncture_y<0, 1>(target, N_zoom + 1);
	}

	template <delta_t N_zoom=0>
	XTAL_FZ2 puncture_y(aleph_t const &target)
	XTAL_0EX
	{
		alpha_t const x = puncture_y<N_zoom>(target.real());
		alpha_t const y = puncture_y<N_zoom>(target.imag());
		return aleph_t {x, y};
	}
	template <delta_t N_zoom=0, bool N_zero=0>
	XTAL_FZ2 puncture_y(aleph_t target, delta_t const &zone)
	XTAL_0EX
	{
		alpha_t w = square_dot_y<-1>(target), m = 1/w;
		target *= m; puncture_z<N_zoom, N_zero>(w, zone);
		target *= w;
		return target;
	}
	

////////////////////////////////////////////////////////////////////////////////

	///\returns the `target` to `N_zoom` bits of precision after the decimal. \

	template <delta_t N_zoom=0>
	XTAL_FZ2_(alpha_t) trim_y(alpha_t target)
	XTAL_0EX
	{
		delta_t constexpr N_unzoom = N_zoom? N_zoom - fraction::depth: -1;
		alpha_t constexpr y = minimal_y(N_unzoom);
		target *= y;
		target /= y;
	//	target *= 1/y;// prevent optimization by not doing this...
		return target;
	}
	static_assert(trim_y<2>(patio_y<2>(1)) == 6.25);
	static_assert(trim_y<3>(patio_y<1>(1)) == 3.125);
	static_assert(trim_y<4>(patio_y<1>(2)) == 1.5625);

	template <delta_t N_zoom=fraction::depth - 1>
	XTAL_FZ2 trim_y(aleph_t const &target)
	XTAL_0EX
	{
		alpha_t const x = trim_y<N_zoom>(target.real());
		alpha_t const y = trim_y<N_zoom>(target.imag());
		return aleph_t {x, y};
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
};
template <typename ...Ts > struct realize       : realization<sizeof(construct_t<Ts...>)> {};
template <value_q  ...Ts > struct realize<Ts...>: realize<value_t<Ts>...> {};

using realized = realize<XTAL_STD_SIZE>;
using   flux_t = typename realized:: flux_t;
using   iota_t = typename realized:: iota_t;
using  delta_t = typename realized::delta_t;//_std::ptrdiff_t;
using  sigma_t = typename realized::sigma_t;//_std::size_t;
using  alpha_t = typename realized::alpha_t;
using  aleph_t = typename realized::aleph_t;

static_assert(is_q<XTAL_STD_SIZE, sigma_t>);
static_assert(sizeof(XTAL_STD_SIZE) == sizeof(sigma_t));
static_assert(sizeof(XTAL_STD_SIZE) == sizeof(delta_t));
static_assert(sizeof(XTAL_STD_SIZE) == sizeof(alpha_t));

template <typename    T  > concept delta_b = _std::signed_integral<based_t<T>>;
template <typename ...Ts > concept delta_q = unfalse_p<delta_b<Ts>...>;

template <typename    T  > concept sigma_b = _std::unsigned_integral<based_t<T>>;
template <typename ...Ts > concept sigma_q = unfalse_p<sigma_b<Ts>...>;

template <typename    T  > concept alpha_b = _std::floating_point<based_t<T>>;
template <typename ...Ts > concept alpha_q = unfalse_p<sigma_b<Ts>...>;


///////////////////////////////////////////////////////////////////////////////

///\see `realized::trim_y`. \

template <auto ...N_etc>
XTAL_FZ2 trim_y(XTAL_DEF... etc)
XTAL_0EX
{
	return realize<decltype(etc)...>::template trim_y<N_etc...>(XTAL_REF_(etc)...);
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
