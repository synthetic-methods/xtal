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
\
The constants labelled `quake_v` are provided for `Q_rsqrt` (in lieu of `constexpr`). \

template <size_t>
struct systematization;

template <>
struct systematization<1>
{
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
	using      iota_t  =      _std::int16_t;
	using     delta_t  =   signed       int;
	using     sigma_t  = unsigned       int;
	using     alpha_t  =              float;
	XTAL_LET_(sigma_t)      fraction_n = 23;
	XTAL_LET_(sigma_t)      exponent_n =  8;
//	XTAL_LET_(sigma_t)         quake_n = 0x5F3759DF;
	XTAL_LET_(alpha_t)         quake_v = 13211836172961054720.;

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
	using      iota_t  =      _std::int32_t;
	using     delta_t  =   signed long  int;
	using     sigma_t  = unsigned long  int;
	using     alpha_t  =             double;
	XTAL_LET_(sigma_t)      fraction_n = 52;
	XTAL_LET_(sigma_t)      exponent_n = 11;
//	XTAL_LET_(sigma_t)         quake_n = 0x5FE6EB50C7B537A9;//-Wconstant-conversion
	XTAL_LET_(alpha_t)         quake_v =\
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

template <size_t N_size>
struct rationalization
:	systematization<N_size>
{
private:
	using co = systematization<N_size>;

public:
	using typename co::delta_t;
	using typename co::sigma_t;

	XTAL_LET_(sigma_t) width = N_size;
	XTAL_LET_(sigma_t) depth = N_size << 3;

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

	template <size_t M_depth, size_t N_shift>
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

	XTAL_LET_(sigma_t) sigma_1 = 1;
	XTAL_LET_(delta_t) delta_1 = 1;

};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <size_t N_size>
struct realization: rationalization<N_size>
{
};
template <size_t N_size> requires _std::floating_point<typename rationalization<N_size>::alpha_t>
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

	using co::width;
	using co::depth;
	using co::delta_1;
	using co::sigma_1;
	XTAL_LET_(alpha_t) alpha_1 = 1;

#if XTAL_STD_IEEE == 754
	static_assert(_std::numeric_limits<alpha_t>::is_iec559);
#endif

//	TODO: Define hardware cache line size w.r.t. `N_size`? \


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	XTAL_FZ2 mantissa_y(sigma_t n)
	XTAL_0EX
	{
		return _std::bit_cast<alpha_t>(n & ~unit::mask);
	}
	XTAL_FZ2 mantissa_y(mt19937_t &m)
	XTAL_0EX
	{
		return mantissa_y(m());
	}


///////////////////////////////////////////////////////////////////////////////

	template <auto M_pow=1> requires sign_q<M_pow>
	XTAL_FZ2_(alpha_t) it_y(XTAL_DEF u)
	XTAL_0EX
	{
		if constexpr (M_pow == +1)
		{	return XTAL_REF_(u);
		}
		else
		if constexpr (M_pow == -1)
		{	return alpha_1/XTAL_REF_(u);
		}
	}

	template <int M_pow=1> requires sign_q<M_pow>
	XTAL_FZ2_(alpha_t) dot_y(aleph_t const &u)
	XTAL_0EX
	{
		alpha_t const x = u.real(), xx = square_y(x);
		alpha_t const y = u.imag(), yy = square_y(y);
		return it_y<M_pow>(xx + yy);
	}

	template <int M_pow=1> requires sign_q<M_pow>
	XTAL_FZ2 circle_y(auto const &u)
	XTAL_0EX
	{
		return aleph_t(_std::cos(u), _std::sin(u)*M_pow);
	}

	template <int M_pow=1, int N_lim=-1> requires sign_q<M_pow>
	XTAL_FZ2_(alpha_t) square_y(alpha_t const &w)
	XTAL_0EX
	{
		return it_y<M_pow>(w*w);
	}
	XTAL_FZ2_(aleph_t) square_y(aleph_t const &u)
	XTAL_0EX
	{
		alpha_t const x = u.real(), xx = square_y(x);
		alpha_t const y = u.imag(), yy = square_y(y);
		return aleph_t(xx - yy, x*y*2.0);
	}
	XTAL_FZ2 square_y(auto u)
	XTAL_0EX
	{
		u *= u; return u;
	}

	template <int M_pow=1, int N_lim=-1> requires sign_q<M_pow>
	XTAL_FZ2_(alpha_t) unsquare_y(alpha_t const &w)
	XTAL_0EX
	{
		if (_std::is_constant_evaluated())
		{	delta_t o = _std::bit_cast<delta_t>(co::quake_v); o -= _std::bit_cast<delta_t>(w) >> 1;
			alpha_t n = _std::bit_cast<alpha_t>(o);
			alpha_t const k = w*0.5;
			if constexpr (N_lim < 0)
			{	alpha_t m = k*n*n;
				for (sigma_t i = 0; m != 0.5 and i < 0x10; ++i)
				{	n *= 1.5 - m; m = k*n*n;
				}
				n /= m + 0.5;
			}
			else
			{	for (sigma_t i = 0; i < N_lim; ++i)
				{	n *= 1.5 - k*n*n;
				}
			//	seek_f<N_lim>([&](auto) XTAL_0FN_(n *= 1.5 - k*n*n));
				return n;
			}
			if constexpr (M_pow == +1)
			{	return n*w;
			}
			else
			if constexpr (M_pow == -1)
			{	return n;
			}
		}
		else
		{	return it_y<M_pow>(_std::sqrt(w));
		}
	}
	static_assert(unsquare_y< 1>((alpha_t) 2) == (alpha_t) 0.1414213562373095048801688724209698079e+1);
	static_assert(unsquare_y<-1>((alpha_t) 2) == (alpha_t) 0.7071067811865475244008443621048490393e+0);

	template <int M_pow=1, int N_lim=-1> requires sign_q<M_pow>
	XTAL_FZ2_(alpha_t) unsquare_dot_y(aleph_t const &u)
	XTAL_0EX
	{
		if (_std::is_constant_evaluated())
		{	return unsquare_y<M_pow, N_lim>(dot_y(u));
		}
		else
		{	return it_y<M_pow>(_std::hypot(u.real(), u.imag()));
		}
	}


////////////////////////////////////////////////////////////////////////////////

	///\returns the `constexpr` equivalent of `std:pow(base, zoom)` for an `unsigned int zoom`. \
	
	XTAL_FZ2 explo_y(sigma_t const &zoom, XTAL_DEF base)
	XTAL_0EX
	{
		XTAL_TYP_(base) u = XTAL_REF_(base), w = 1;
		for (sigma_t n = zoom; n; n >>= 1)
		{	if (n & 1)
			{	n ^= 1;
				w *= u;
			}
			u = square_y(u);
		}
		return w;
	}
	template <size_t N_zoom>
	XTAL_FZ2 explo_y(XTAL_DEF base)
	XTAL_0EX
	{
		return explo_y(N_zoom, XTAL_REF_(base));
	}
	static_assert(explo_y<0> (alpha_t(2.0)) == 1.00);
	static_assert(explo_y<1> (alpha_t(2.0)) == 2.00);
	static_assert(explo_y<2> (alpha_t(2.0)) == 4.00);

	///\returns the `constexpr` equivalent of `std:pow(2.0, zoom)`. \

	XTAL_FZ2 diplo_y(delta_t const &zoom)
	XTAL_0EX
	{
	#if 1//XTAL_STD_IEEE == 754
		delta_t m = zoom << unit::shift;
		m += unit::mask;
		m &= exponent::mask;
		return _std::bit_cast<alpha_t> (m);
	#else
		return _std::ldexp(alpha_1, zoom);// not `constexpr` until `C++23`!
	#endif
	}
	template <int N_zoom=0>
	XTAL_LET diplo_v = diplo_y(N_zoom);
	///< Value expression of `diplo_y`. \

	static_assert(diplo_v<+1> == 2.0);
	static_assert(diplo_v< 0> == 1.0);
	static_assert(diplo_v<-1> == 0.5);


	///\returns the `constexpr` equivalent of `std:pow(0.5, zoom)`. \

	XTAL_FZ2 haplo_y(delta_t const &zoom)
	XTAL_0EX
	{
		return diplo_y(-zoom);
	}
	template <int N_zoom=0>
	XTAL_LET haplo_v = haplo_y(N_zoom);
	///< Value expression of `haplo_y`. \

	static_assert(haplo_v<+1> == 0.5);
	static_assert(haplo_v< 0> == 1.0);
	static_assert(haplo_v<-1> == 2.0);


////////////////////////////////////////////////////////////////////////////////

	///\returns the `N_num`erator divided by the given de`nom`inator.

	template <int N_num=1>
	XTAL_FZ2_(alpha_t) ratio_y(XTAL_DEF nom)
	XTAL_0EX
	{
		return alpha_t(N_num)/XTAL_REF_(nom);
	}
	static_assert(ratio_y    (alpha_t(2.0)) == 0.5);
	static_assert(ratio_y<1> (alpha_t(2.0)) == 0.5);
	static_assert(ratio_y<4> (alpha_t(2.0)) == 2.0);


	///\returns `pi` times `ratio_y<N_num> (nom)`.

	template <int N_num=1>
	XTAL_FZ2_(alpha_t) patio_y(XTAL_DEF u)
	XTAL_0EX
	{
		return ratio_y<N_num> (XTAL_REF_(u))*3.141592653589793238462643383279502884;
	}
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
	template <int N_base, int N_shift=0>
	XTAL_LET codomain_v = codomain_vs[N_base&0b11]*haplo_v<N_shift>;
///< Value expression representing the multiplicative inverse of the logarithmic `domain_v`.

	template <int N_base, int N_shift=0>
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
	template <int N_zoom=0>
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
	template <int N_zoom=0>
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
	template <int N_zoom=0>
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
	template <int N_zoom=0>
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


	///\returns haplo_y(zoom)/std::numeric_limits<alpha_t>::min()`. \
	
	///\note Defined as the multiplicative inverse of `minimal_y`, \
		rather than w.r.t. `std::numeric_limits<alpha_t>::max()`, \
		which is two orders of (binary) magnitude larger. \

	XTAL_FZ2_(alpha_t) maximal_y(delta_t const &zoom=0)
	XTAL_0EX
	{
		return haplo_y(zoom)/std::numeric_limits<alpha_t>::min();
	}
	template <int N_zoom=0>
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
	static_assert(design_y( 1.0) ==  1.0);
	static_assert(design_y(-1.0) ==  1.0);


////////////////////////////////////////////////////////////////////////////////

	///\returns `value` when positive, zero otherwise. \

	template <int N_proximity=0>
	XTAL_FZ2 positive_y(alpha_t value)
	XTAL_0EX
	{
		value *= haplo_y(1);
		if constexpr (0 < N_proximity) value -= minimal_v<N_proximity - 1>;
		value += design_y(value);
		if constexpr (0 < N_proximity) value += minimal_v<N_proximity - 1>;
		return value;
	}
	static_assert(positive_y<0>( 1.0) ==  1.0);
	static_assert(positive_y<0>( 0.0) ==  0.0);
	static_assert(positive_y<0>(-1.0) ==  0.0);

	static_assert(positive_y<1>( 1.0) ==  1.0);
	static_assert(positive_y<1>( 0.0) ==  minimal_y());
	static_assert(positive_y<1>(-1.0) ==  minimal_y());


	///\returns `value` when negative, zero otherwise. \

	template <int N_proximity=0>
	XTAL_FZ2 negative_y(alpha_t value)
	XTAL_0EX
	{
		value *= haplo_y(1);
		if constexpr (0 < N_proximity) value += minimal_v<N_proximity - 1>;
		value -= design_y(value);
		if constexpr (0 < N_proximity) value -= minimal_v<N_proximity - 1>;
		return value;
	}
	static_assert(negative_y<0>( 1.0) ==  0.0);
	static_assert(negative_y<0>( 0.0) ==  0.0);
	static_assert(negative_y<0>(-1.0) == -1.0);

	static_assert(negative_y<1>( 1.0) == -minimal_y());
	static_assert(negative_y<1>( 0.0) == -minimal_y());
	static_assert(negative_y<1>(-1.0) == -1.0);


////////////////////////////////////////////////////////////////////////////////

	/// Modifies the `target`, clamping the magnitude below `dnsilon_y(N_zoom, zone)`. \

	///\returns zero if unchanged, else the sign of the `target`. \
	
	template <int N_zoom=0, bool N_infinity=0>
	XTAL_FZ1_(alpha_t) truncate_z(alpha_t &target, delta_t const &zone)
	XTAL_0EX
	{
		bool constexpr N_unit = not N_infinity;
	#if XTAL_STD_IEEE == 754
		delta_t constexpr M_zone = unit::mask + (delta_1);
		delta_t constexpr M_zoom = unit::mask - (sigma_1 << N_zoom);
		delta_t const     dezone = zone << exponent::shift;
		delta_t const     rezone = N_infinity? M_zone - dezone: dezone;
		delta_t const M = rezone + M_zoom;
		delta_t _, n, m;
		auto &t  = reinterpret_cast<delta_t &> (target);
		n  =  t  & sign::mask;
		m  =  t  ^ n;
		m  =  M  - m;
		_  =  m >> positive::depth;
		n |=  _  & unit::mask;
		t +=  _  & m;
		return    _std::bit_cast<alpha_t> (n);
	#else
		alpha_t const t = N_infinity? maximal_y(zone - 1): dnsilon_y(N_zoom, zone);
		alpha_t const s = design_z(target), _ = t < target;
		target = s*minimum_y(t, target);
		return _*s;
	#endif
	}
	/// Modifies the `target`, clamping the magnitude below `maximal_y(N_zoom)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <int N_zoom=0>
	XTAL_FZ1_(alpha_t) truncate_z(alpha_t &target)
	XTAL_0EX
	{
		return truncate_z<0, 1>(target, N_zoom + 1);
	}
	template <int N_zoom=0>
	XTAL_FZ1_(aleph_t) truncate_z(aleph_t &target)
	XTAL_0EX
	{
		auto z = reinterpret_cast<alpha_t(&)[2]>(target);
		alpha_t const x = truncate_z<N_zoom>(z[0]);
		alpha_t const y = truncate_z<N_zoom>(z[1]);
		return aleph_t {x, y};
	}

	///\returns the `target` with magnitude clamped to the region below `dnsilon_y(N_zoom, zone)`. \

	template <int N_zoom=0, bool N_infinity=0>
	XTAL_FZ2_(alpha_t) truncate_y(alpha_t target, delta_t const &zone)
	XTAL_0EX
	{
		(void) truncate_z<N_zoom, N_infinity>(target, zone); return target;
	}
	///\returns the `target` with magnitude clamped to the region below `maximal_y(N_zoom)`. \

	template <int N_zoom=0>
	XTAL_FZ2_(alpha_t) truncate_y(alpha_t const &target)
	XTAL_0EX
	{
		return truncate_y<0, 1>(target, N_zoom + 1);
	}	

	template <int N_zoom=0>
	XTAL_FZ2 truncate_y(aleph_t const &target)
	XTAL_0EX
	{
		alpha_t const x = truncate_y<N_zoom>(target.real());
		alpha_t const y = truncate_y<N_zoom>(target.imag());
		return aleph_t {x, y};
	}
	template <int N_zoom=0, bool N_zero=0>
	XTAL_FZ2 truncate_y(aleph_t target, delta_t const &zone)
	XTAL_0EX
	{
		truncate_z<(sigma_1 << (exponent::depth - 2))>(target);
		alpha_t w = unsquare_dot_y(target), m = 1/w;
		target *= m; truncate_z<N_zoom, N_zero>(w, zone);
		target *= w;
		return target;
	}
	

////////////////////////////////////////////////////////////////////////////////

	/// Modifies the `target`, clamping the magnitude above `upsilon_y(N_zoom, zone)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <int N_zoom=0, bool N_zero=0>
	XTAL_FZ1_(alpha_t) puncture_z(alpha_t &target, delta_t const &zone)
	XTAL_0EX
	{
		bool constexpr N_unit = not N_zero;
	#if XTAL_STD_IEEE == 754
		delta_t constexpr M_zoom = unit::mask + (sigma_1 << N_zoom);
		delta_t const     dezone = zone << exponent::shift;
		delta_t const M = dezone + M_zoom*N_unit;
		delta_t _, n, m;
		auto &t  = reinterpret_cast<delta_t &> (target);
		n   = t  & sign::mask;
		m   = t  ^ n;
		m  -= M;
		_   = m >> positive::depth;
		n  |= _  & unit::mask;
		t  -= _  & m;
		return    _std::bit_cast<alpha_t> (_std::move(n));
	#else
		alpha_t const t = N_zero? minimal_y(zone - 1): upsilon_y(N_zoom, zone);
		alpha_t const s = design_z(target);
		alpha_t const a = positive_y(t - target), _ = a != 0;
		target += a;
		target *= s;
		return  _*s;
	#endif
	}
	/// Modifies the `target`, clamping the magnitude above `minimal_y(N_zoom)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <int N_zoom=0>
	XTAL_FZ1_(alpha_t) puncture_z(alpha_t &target)
	XTAL_0EX
	{
		return puncture_z<0, 1>(target, N_zoom + 1);
	}
	template <int N_zoom=0>
	XTAL_FZ1_(aleph_t) puncture_z(aleph_t &target)
	XTAL_0EX
	{
		auto z = reinterpret_cast<alpha_t(&)[2]>(target);
		alpha_t const x = puncture_z<N_zoom>(z[0]);
		alpha_t const y = puncture_z<N_zoom>(z[1]);
		return aleph_t {x, y};
	}

	///\returns the `target` with magnitude clamped to the region above `upsilon_y(N_zoom, zone)`. \

	template <int N_zoom=0, bool N_zero=0>
	XTAL_FZ2_(alpha_t) puncture_y(alpha_t target, delta_t const &zone)
	XTAL_0EX
	{
		(void) puncture_z<N_zoom, N_zero>(target, zone); return target;
	}
	///\returns the `target` with magnitude clamped to the region above `minimal_y(N_zoom)`. \

	template <int N_zoom=0>
	XTAL_FZ2_(alpha_t) puncture_y(alpha_t const &target)
	XTAL_0EX
	{
		return puncture_y<0, 1>(target, N_zoom + 1);
	}

	template <int N_zoom=0>
	XTAL_FZ2 puncture_y(aleph_t const &target)
	XTAL_0EX
	{
		alpha_t const x = puncture_y<N_zoom>(target.real());
		alpha_t const y = puncture_y<N_zoom>(target.imag());
		return aleph_t {x, y};
	}
	template <int N_zoom=0, bool N_zero=0>
	XTAL_FZ2 puncture_y(aleph_t target, delta_t const &zone)
	XTAL_0EX
	{
		alpha_t w = unsquare_dot_y(target), m = 1/w;
		target *= m; puncture_z<N_zoom, N_zero>(w, zone);
		target *= w;
		return target;
	}
	

////////////////////////////////////////////////////////////////////////////////

	///\returns the `target` to `N_zoom` bits of precision after the decimal. \

	template <int N_zoom=0>
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

	template <int N_zoom=fraction::depth - 1>
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
template <typename T> struct realize: realization<sizeof(revalue_t<T>)> {};

using realized = realize<size_t>;
using   iota_t = typename realized:: iota_t;
using  delta_t = typename realized::delta_t;//_std::ptrdiff_t;
using  sigma_t = typename realized::sigma_t;//_std::size_t;
using  alpha_t = typename realized::alpha_t;
using  aleph_t = typename realized::aleph_t;

XTAL_LET delta_1 = realized::delta_1;
XTAL_LET sigma_1 = realized::sigma_1;
XTAL_LET alpha_1 = realized::alpha_1;

static_assert(is_q<size_t, sigma_t>);
static_assert(sizeof(size_t) == sizeof(sigma_t));
static_assert(sizeof(size_t) == sizeof(delta_t));
static_assert(sizeof(size_t) == sizeof(alpha_t));

template <typename    T  > concept  iota_p = _std::integral<based_t<T>>;
template <typename ...Ts > concept  iota_q = every_q<iota_p<Ts>...>;

template <typename    T  > concept delta_p = _std::signed_integral<based_t<T>>;
template <typename ...Ts > concept delta_q = every_q<delta_p<Ts>...>;

template <typename    T  > concept sigma_p = _std::unsigned_integral<based_t<T>>;
template <typename ...Ts > concept sigma_q = every_q<sigma_p<Ts>...>;

template <typename    T  > concept alpha_p = _std::floating_point<based_t<T>>;
template <typename ...Ts > concept alpha_q = every_q<sigma_p<Ts>...>;


///////////////////////////////////////////////////////////////////////////////

///\see `realized::trim_y`. \

template <auto ...N_etc>
XTAL_LET trim_y = [](XTAL_DEF... etc)
XTAL_0FN_(realize<decltype(etc)...>::template trim_y<N_etc...>(XTAL_REF_(etc)...));


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
