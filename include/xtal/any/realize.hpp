#pragma once
#include "./any.hpp"
#include <cstdint>





XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <auto...     Ns>       concept     true_q =     (bool(Ns)  or...);///< Matches if any `Ns... == 1`.
template <auto...     Ns>       concept    false_q = not (bool(Ns) and...);///< Matches if any `Ns... == 0`.
template <auto...     Ns>       concept   untrue_q = not (bool(Ns)  or...);///< Matches if all `Ns... == 0`.
template <auto...     Ns>       concept  unfalse_q =     (bool(Ns) and...);///< Matches if all `Ns... == 1`.
template <auto        N=0>      concept positive_q = (0 < N);
template <auto        N=0>      concept negative_q = (N < 0);
template <auto        N=0>      concept     even_q = (N & 1) == 0;
template <auto        N=0>      concept      odd_q = (N & 1) == 1;
template <typename T, auto N>   concept  breadth_q = (N == sizeof(T));

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///\
Establishes the base types for the supplied `Q` \
(which should be representative of the desired `std::size_t`): \
\
-	The `alpha_t` represents floating-point real numbers. \
-	The `sigma_t` represents full-width `unsigned int`s like `std::size`. \
-	The `delta_t` represents full-width   `signed int`s used for binary and integer arithmetic. \
-	The `iota_t`  represents half-width   `signed int`s required for `ranges::difference_type`. \
\
The constants labelled `carmack_v` are provided for `Q_rsqrt` (in lieu of `constexpr`). \

template <typename>
struct realization;

template <breadth_q<1> Q>
struct realization<Q>
{
//	using     alpha_t  =     _std::float4_t;
//	using      iota_t  =       _std::int4_t;
	using     delta_t  =   signed      char;
	using     sigma_t  = unsigned      char;
	XTAL_LET_(sigma_t)      fraction_n = 10;
	XTAL_LET_(sigma_t)      exponent_n =  5;

};
template <breadth_q<2> Q>
struct realization<Q>
{
//	using     alpha_t  =     _std::float8_t;
	using      iota_t  =       _std::int8_t;
	using     delta_t  =   signed short int;
	using     sigma_t  = unsigned short int;
	XTAL_LET_(sigma_t)      fraction_n = 10;
	XTAL_LET_(sigma_t)      exponent_n =  5;

};
template <breadth_q<4> Q>
struct realization<Q>
{
	using     alpha_t  =              float;
	using      iota_t  =      _std::int16_t;
	using     delta_t  =   signed       int;
	using     sigma_t  = unsigned       int;
	XTAL_LET_(sigma_t)      fraction_n = 23;
	XTAL_LET_(sigma_t)      exponent_n =  8;
//	XTAL_LET_(sigma_t)       carmack_m = 0x5f3759df;
	XTAL_LET_(alpha_t)       carmack_v = 13211836172961054720.;

};
template <breadth_q<8> Q>
struct realization<Q>
{
	using     alpha_t  =             double;
	using      iota_t  =      _std::int32_t;
	using     delta_t  =   signed long  int;
	using     sigma_t  = unsigned long  int;
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
};

template <typename Q>
struct realize
:	realization<Q>
{
private:
	using co = realization<Q>;

public:
	using typename co::delta_t;
	using typename co::sigma_t;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	XTAL_LET sigma_x = [] (XTAL_DEF w) XTAL_0FN_(sigma_t(XTAL_REF_(w)));
	XTAL_LET delta_x = [] (XTAL_DEF w) XTAL_0FN_(delta_t(XTAL_REF_(w)));

	XTAL_LET delta_0 = delta_t(0), delta_1 = delta_t(1);
	XTAL_LET sigma_0 = sigma_t(0), sigma_1 = sigma_t(1);

	XTAL_LET breadth = sizeof(Q) >> 2;
	XTAL_LET   width = sizeof(Q);
	XTAL_LET   depth = sizeof(Q) << 3;

};
template <typename Q>
XTAL_IF2
{
	typename realization<Q>::alpha_t;
	requires std::is_floating_point_v<typename realization<Q>::alpha_t>;
}
struct realize<Q>
:	realization<Q>
{
private:
	using co = realization<Q>;

public:
	using typename co::alpha_t; using aleph_t = _std::complex<alpha_t>;
	using typename co:: iota_t;
	using typename co::delta_t;
	using typename co::sigma_t;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	XTAL_LET aleph_x = [] (XTAL_DEF... ws) XTAL_0FN_(aleph_t(XTAL_REF_(ws)...));
	XTAL_LET alpha_x = [] (XTAL_DEF     w) XTAL_0FN_(alpha_t(XTAL_REF_(w)));
	XTAL_LET  iota_x = [] (XTAL_DEF     w) XTAL_0FN_( iota_t(XTAL_REF_(w)));
	XTAL_LET delta_x = [] (XTAL_DEF     w) XTAL_0FN_(delta_t(XTAL_REF_(w)));
	XTAL_LET sigma_x = [] (XTAL_DEF     w) XTAL_0FN_(sigma_t(XTAL_REF_(w)));

//	static_assert(_std::numeric_limits<alpha_t>::has_infinity);
//	XTAL_LET alpha_oo = _std::numeric_limits<alpha_t>::infinity();
//	...not needed?
	XTAL_LET alpha_0 = alpha_t(0), alpha_1 = alpha_t(1);
	XTAL_LET  iota_0 =  iota_t(0),  iota_1 =  iota_t(1);
	XTAL_LET delta_0 = delta_t(0), delta_1 = delta_t(1);
	XTAL_LET sigma_0 = sigma_t(0), sigma_1 = sigma_t(1);


	using co::fraction_n;
	using co::exponent_n;
	XTAL_LET     positive_n = fraction_n + exponent_n;
	XTAL_LET     negative_n = positive_n + sigma_1;
	XTAL_LET         unit_n = exponent_n - sigma_1;
	XTAL_LET         sign_n =              sigma_1;
	XTAL_LET        breadth = sizeof(Q) >> 2;
	XTAL_LET          width = sizeof(Q);
	XTAL_LET          depth = sizeof(Q) << 3;
	static_assert(negative_n == depth);

	XTAL_FZ2 flag_f(delta_t const depth=0)
	XTAL_0EX
	{
		return sigma_t(0 <= depth and depth <= negative_n) << depth;
	};
	XTAL_FZ2 mark_f(sigma_t const depth=0)
	XTAL_0EX
	{
		return flag_f(depth)  - 1;
	};
	XTAL_FZ2 mask_f(sigma_t const depth=0, sigma_t const shift=0)
	XTAL_0EX
	{
		return mark_f(depth) << shift;
	};
	template <sigma_t N_depth, sigma_t M_shift>
	struct word
	{
		XTAL_LET depth = N_depth;
		XTAL_LET shift = M_shift;
		XTAL_LET mark = mark_f(N_depth);
		XTAL_LET mask = mask_f(N_depth, M_shift);
	};
	struct negative: word<negative_n,    sigma_0> {};
	struct positive: word<positive_n,    sigma_0> {};
	struct fraction: word<fraction_n,    sigma_0> {};
	struct exponent: word<exponent_n, fraction_n> {};
	struct     unit: word<    unit_n, fraction_n> {};
	struct     sign: word<    sign_n, positive_n> {};
	static_assert(~sign::mask == positive::mask);

	XTAL_LET IEC_559 = XTAL_IEC_559 and _std::numeric_limits<alpha_t>::is_iec559;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\
	\returns the `constexpr` equivalent of `std:pow(2.0, zoom)`. \

	XTAL_FZ2 diplo_y(delta_t const &zoom)
	XTAL_0EX
	{
		if constexpr (IEC_559)
		{
			delta_t m = zoom << unit::shift; m += unit::mask;
			return _std::bit_cast<alpha_t> (m);
		}
		else
		{
			sigma_t const i_sgn =   zoom >> positive::depth;
			sigma_t const i_neg = -(zoom &  i_sgn);
			sigma_t const i_pos =  (zoom & ~i_sgn);
			return alpha_t(sigma_1 << i_pos)/(sigma_1 << i_neg);
		}
	}
	XTAL_LET  diplo_x = [] (XTAL_DEF zoom)
	XTAL_0FN_(diplo_y(XTAL_REF_(zoom)));
	///<\
	Function expression of `diplo_y`. \

	template <delta_t N_zoom=0>
	XTAL_LET  diplo_v = diplo_y(N_zoom);
	///<\
	Value expression of `diplo_y`. \

	static_assert(diplo_v<+1> == 2.0);
	static_assert(diplo_v< 0> == 1.0);
	static_assert(diplo_v<-1> == 0.5);


	///\
	\returns the `constexpr` equivalent of `std:pow(0.5, zoom)`. \

	XTAL_FZ2 haplo_y(delta_t const &zoom)
	XTAL_0EX
	{
		if constexpr (IEC_559)
		{
			return diplo_y(-zoom);
		}
		else
		{
			sigma_t const i_sgn =   zoom >> positive::depth;
			sigma_t const i_neg = -(zoom &  i_sgn);
			sigma_t const i_pos =  (zoom & ~i_sgn);
			return alpha_t(sigma_1 << i_neg)/(sigma_1 << i_pos);
		}
	}
	XTAL_LET  haplo_x = [] (XTAL_DEF zoom)
	XTAL_0FN_(haplo_y(XTAL_REF_(zoom)));
	///<\
	Function expression of `haplo_y`. \

	template <delta_t N_zoom=0>
	XTAL_LET  haplo_v = haplo_y(N_zoom);
	///<\
	Value expression of `haplo_y`. \

	static_assert(haplo_v<+1> == 0.5);
	static_assert(haplo_v< 0> == 1.0);
	static_assert(haplo_v<-1> == 2.0);


////////////////////////////////////////////////////////////////////////////////

	///\
	\returns the `constexpr` equivalent of `std:pow(base, exponent)` for an `unsigned int exponent`. \
	
	///\
	\note This is provided within `realize` for completeness/convenience, \
	but could/should be defined generically at the top level of `xtal` or `xtal-math`. \

	XTAL_FZ2 explo_y(sigma_t const &exponent, alpha_t const &base)
	XTAL_0EX
	{
		alpha_t w = 1, u = base;
		for (sigma_t n = exponent; n; n >>= 1)
		{
			if (n & 1)
			{
				n ^= 1;
				w *= u;
			}
			u *= u;
		}
		return w;
	}
	template <sigma_t N_zoom>
	XTAL_FZ2 explo_y(XTAL_DEF base)
	XTAL_0EX
	{
		return explo_y(N_zoom, XTAL_REF_(base));
	}
	using explo_t = alpha_t (*const) (alpha_t const &);
	///<\
	Function type of `explo_y`. \

	template <sigma_t N_zoom>
	XTAL_LET_(explo_t) explo_x = [] (alpha_t const &base)
	XTAL_0FN_(explo_y<N_zoom> (base));
	///<\
	Function expression of `explo_y`. \

	///\note The explicit function-type avoids potential segmentation fault \
	raised when dynamically resolving the nested templated lambda. \

	static_assert(explo_y<0> (alpha_t(2.0)) == 1.00);
	static_assert(explo_y<1> (alpha_t(2.0)) == 2.00);
	static_assert(explo_y<2> (alpha_t(2.0)) == 4.00);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\
	\returns the `N_num`erator divided by the given de`nom`inator.

	template <auto N_num=1>
	XTAL_FZ2_(alpha_t) ratio_y(XTAL_DEF nom)
	XTAL_0EX
	{
		return alpha_t(N_num)/XTAL_REF_(nom);
	}
	using ratio_t = alpha_t (*const) (alpha_t const &);
	///<\
	Function type of `ratio_y`. \

	template <auto N_num=1>
	XTAL_LET_(ratio_t) ratio_x = [] (alpha_t const& nom)
	XTAL_0FN_(ratio_y<N_num> (nom));
	///<\
	Function expression of `ratio_y`. \

	///\note The explicit function-type avoids potential segmentation fault \
	raised when dynamically resolving the nested templated lambda. \

	static_assert(ratio_y    (alpha_t(2.0)) == 0.5);
	static_assert(ratio_y<1> (alpha_t(2.0)) == 0.5);
	static_assert(ratio_y<4> (alpha_t(2.0)) == 2.0);


	///\
	\returns `pi` multiplied by the `ratio_y<N_num> (nom)`.

	template <auto N_num=1>
	XTAL_FZ2_(alpha_t) patio_y(XTAL_DEF u)
	XTAL_0EX
	{
		return ratio_y<N_num> (XTAL_REF_(u))*3.14159265358979323846264338327950288419717;
	}
	using patio_t = alpha_t (*const) (alpha_t const &);
	///<\
	Function type of `patio_y`. \

	template <auto N_num=1>
	XTAL_LET_(patio_t) patio_x = [] (alpha_t const& nom)
	XTAL_0FN_(patio_y<N_num> (nom));
	///<\
	Function expression of `patio_y`. \

	///\note The explicit function-type avoids potential segmentation fault \
	raised when dynamically resolving the nested templated lambda. \

	static_assert(patio_y    (alpha_t(2.0)) == alpha_t(1.57079632679489661923132169163975144209858));
	static_assert(patio_y<1> (alpha_t(2.0)) == alpha_t(1.57079632679489661923132169163975144209858));
	static_assert(patio_y<4> (alpha_t(2.0)) == alpha_t(6.28318530717958647692528676655900576839434));


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\returns the difference between floating-point values at the scale designated by `zoom`. \

	XTAL_FZ2_(alpha_t) epsilon_y(delta_t const &zoom=1)
	XTAL_0EX
	{
		auto constexpr N = fraction::depth + 1;
		return haplo_y(N - zoom);
	}
	XTAL_LET  epsilon_x = [] (XTAL_DEF zoom)
	XTAL_0FN_(epsilon_y(XTAL_REF_(zoom)));
	///<\
	Function expression of `epsilon_y`. \

	template <delta_t N_zoom=0>
	XTAL_LET  epsilon_v = epsilon_y(N_zoom);
	///<\
	Value expression of `epsilon_y`. \

	static_assert(epsilon_v<0> != alpha_0);
	static_assert(epsilon_v<0> <  epsilon_v<1>);
	static_assert(epsilon_v<1> <  epsilon_v<2>);
	static_assert(epsilon_v<1> == _std::numeric_limits<alpha_t>::epsilon());
	

	///\returns the value `zoom` steps above `alpha_1`. \

	XTAL_FZ2_(alpha_t) upsilon_y(delta_t const &zoom=1)
	XTAL_0EX
	{
		return alpha_1 + epsilon_y(zoom - 0);
	}
	XTAL_LET  upsilon_x = [] (XTAL_DEF zoom)
	XTAL_0FN_(upsilon_y(XTAL_REF_(zoom)));
	///<\
	Function expression of `upsilon_y`. \

	template <delta_t N_zoom=0>
	XTAL_LET  upsilon_v = upsilon_y(N_zoom);
	///<\
	Value expression of `upsilon_y`. \
	
	static_assert(upsilon_v<0> == alpha_1);
	static_assert(upsilon_v<1>  > upsilon_v<0>);
	static_assert(upsilon_v<2>  > upsilon_v<1>);


	///\returns the value `zoom` steps below `alpha_1`. \

	XTAL_FZ2_(alpha_t) dnsilon_y(delta_t const &zoom=1)
	XTAL_0EX
	{
		return alpha_1 - epsilon_y(zoom - 1);
	}
	XTAL_LET  dnsilon_x = [] (XTAL_DEF zoom)
	XTAL_0FN_(dnsilon_y(XTAL_REF_(zoom)));
	///<\
	Function expression of `dnsilon_y`. \

	template <delta_t N_zoom=0>
	XTAL_LET  dnsilon_v = dnsilon_y(N_zoom);
	///<\
	Value expression of `dnsilon_y`. \
	
	static_assert(dnsilon_v<0> == alpha_1);
	static_assert(dnsilon_v<1> <  dnsilon_v<0>);
	static_assert(dnsilon_v<2> <  dnsilon_v<1>);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\returns `std::numeric_limits<alpha_t>::min()/(1 << (zoom - 1))`, or zero when `zoom=0`. \

	///\note The return value is doubled when `zoom` increases by one. \

	XTAL_FZ2_(alpha_t) minimal_y(delta_t const &zoom=0)
	XTAL_0EX
	{
		auto const num = std::numeric_limits<alpha_t>::min()*(0 < zoom);
		return num*diplo_y(zoom - delta_1);
	}
	XTAL_LET  minimal_x = [] (XTAL_DEF zoom)
	XTAL_0FN_(minimal_y(XTAL_REF_(zoom)));
	///<\
	Function expression for `minimal_y`. \

	template <delta_t N_zoom=0>
	XTAL_LET  minimal_v = minimal_y(N_zoom);
	///<\
	Value expression for `minimal_y`. \

	static_assert(minimal_v<0> == alpha_0);
	static_assert(minimal_v<1> == std::numeric_limits<alpha_t>::min()*(1 << 0));
	static_assert(minimal_v<2> == std::numeric_limits<alpha_t>::min()*(1 << 1));


	///\returns the minimum of the given arguments `xs...`, evaluated with respect to type `alpha_t`. \

	XTAL_FZ2_(alpha_t) minimum_y()
	XTAL_0EX
	{
		return minimal_y();
	}
	XTAL_FZ2_(alpha_t) minimum_y(XTAL_DEF... values)
	XTAL_0EX
	{
		return _std::min<alpha_t> ({XTAL_REF_(values)...});
	}
	XTAL_LET  minimum_x = [] (XTAL_DEF... values)
	XTAL_0FN_(minimum_y(XTAL_REF_(values)...));


////////////////////////////////////////////////////////////////////////////////

	///\returns `1/std::numeric_limits<alpha_t>::min()` magnified by `1 << (zoom - 1)`, or zero if `zoom == 0`. \
	
	///\note The return value is halved when `zoom` increases by one. \
	
	///\note Defined as the multiplicative inverse of `minimal_y`, \
	rather than w.r.t. `std::numeric_limits<alpha_t>::max()`, \
	which is two orders of (binary) magnitude larger. \

	XTAL_FZ2_(alpha_t) maximal_y(delta_t const &zoom=0)
	XTAL_0EX
	{
		auto const nom = std::numeric_limits<alpha_t>::min()*(0 < zoom);
		auto const num = alpha_1/nom;
		return num*haplo_y(zoom - delta_1);
	}
	XTAL_LET  maximal_x = [] (XTAL_DEF zoom)
	XTAL_0FN_(maximal_y(XTAL_REF_(zoom)));
	///<\
	Function expression for `maximal_y`. \

	template <delta_t N_zoom=0>
	XTAL_LET  maximal_v = maximal_y(N_zoom);
	///<\
	Value expression for `maximal_y`. \

//	static_assert(maximal_y<0> == alpha_oo);
	static_assert(maximal_v<1> == alpha_1/minimal_v<1>);
	static_assert(maximal_v<2> == alpha_1/minimal_v<2>);


	///\returns the maximum of the given arguments `xs...`, evaluated with respect to type `alpha_t`. \

	XTAL_FZ2_(alpha_t) maximum_y()
	XTAL_0EX
	{
		return maximal_y();
	}
	XTAL_FZ2_(alpha_t) maximum_y(XTAL_DEF... values)
	XTAL_0EX
	{
		return _std::max<alpha_t> ({XTAL_REF_(values)...});
	}
	XTAL_LET  maximum_x = [] (XTAL_DEF... values)
	XTAL_0FN_(maximum_y(XTAL_REF_(values)...));
	///<\
	Function expression for `maximum_y`. \


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	///\returns the sign of `value`. \

	XTAL_FZ2 sign_y(alpha_t const &value)
	XTAL_0EX
	{
		#ifdef XTAL_V00_MSVC
			delta_t u = _std::bit_cast<delta_t> (value);
			u &= sign::mask;
			u |= unit::mask;
			return _std::bit_cast<alpha_t> (_std::move(u));
		#else
			return __builtin_copysign(alpha_1, value);
		#endif
	}
	XTAL_LET  sign_x = [] (XTAL_DEF value)
	XTAL_0FN_(sign_y(XTAL_REF_(value)));
	///<\
	Function expression for `sign_y` \

	static_assert(sign_y( 0.5) ==  1.0);
	static_assert(sign_y( 0.0) ==  1.0);
	static_assert(sign_y(-0.5) == -1.0);

	///\returns the `target` magnitude with the sign of the `source`. \

	XTAL_FZ1_(alpha_t) resign_y(alpha_t target, alpha_t const &source=alpha_1)
	XTAL_0EX
	{
		#ifdef XTAL_V00_MSVC
			delta_t n = _std::bit_cast<delta_t> (source);
			delta_t m = _std::bit_cast<delta_t> (target);
			m &=    ~sign::mask;
			m |= n & sign::mask;
			return _std::bit_cast<alpha_t> (_std::move(m));
		#else
			return __builtin_copysign(target, source);
		#endif
		return _std::copysign(target, source);
	}

	///\returns the original sign of `target`, after applying the sign of `source`.

	XTAL_FZ1_(alpha_t) resign_z(alpha_t &target, alpha_t const &source=alpha_1)
	XTAL_0EX
	{
		if constexpr (IEC_559)
		{
			alpha_t result; delta_t m, n, o = unit::mask;
			n   =     _std::bit_cast<delta_t> (_std::move(source));
			m   =     _std::bit_cast<delta_t> (_std::move(target));
			o  |=  m & sign::mask;
			m  &=    ~ sign::mask;
			m  |=  n & sign::mask;
			target = _std::bit_cast<alpha_t> (_std::move(m));
			result = _std::bit_cast<alpha_t> (_std::move(o));
			return result;
		}
		else
		{
			alpha_t const result = sign_y(target);
			target = resign_y(target, source);
			return result;
		}
	}


	///\returns the original sign of `target`, after making it `abs`olute.

	XTAL_FZ1_(alpha_t) design_z(alpha_t &target)
	XTAL_0EX
	{
		if constexpr (IEC_559)
		{
			alpha_t e; delta_t m, o = unit::mask;
			m  = _std::bit_cast<delta_t> (target);
			o |=  sign::mask & m;
			e  = _std::bit_cast<alpha_t> (_std::move(o));
			target *= e; return e;
		}
		else
		{
			alpha_t const u = sign_y(target);
			target *= u; return u;
		}
	}
	///\returns the `abs`olute value of `target`. \

	XTAL_FZ1_(alpha_t) design_y(alpha_t target)
	XTAL_0EX
	{
		#ifdef XTAL_V00_MSVC
			delta_t u = _std::bit_cast<delta_t> (target);
			u &= positive::mask;
			return _std::bit_cast<alpha_t> (_std::move(u));
		#else
			return __builtin_copysign(target, alpha_1);
		#endif
	}
	XTAL_LET  design_x = [] (XTAL_DEF value)
	XTAL_0FN_(design_y(XTAL_REF_(value)));
	///<\
	Function expression for `design_y` \

	static_assert(design_y( 1.0) ==  1.0);
	static_assert(design_y(-1.0) ==  1.0);


////////////////////////////////////////////////////////////////////////////////

	///\
	\returns `value` when positive, zero otherwise. \

	XTAL_FZ2 positive_y(alpha_t value)
	XTAL_0EX
	{
		value *= haplo_y(1);
		value += design_y(value);
		return value;
	}
	XTAL_LET  positive_x = [] (XTAL_DEF value)
	XTAL_0FN_(positive_y(XTAL_REF_(value)));
	///<\
	Function expression for `positive_y` \

	static_assert(positive_y( 1.0) ==  1.0);
	static_assert(positive_y( 0.0) ==  0.0);
	static_assert(positive_y(-1.0) ==  0.0);

	///\
	\returns `value` when negative, zero otherwise. \

	XTAL_FZ2 negative_y(alpha_t value)
	XTAL_0EX
	{
		value *= haplo_y(1);
		value -= design_y(value);
		return value;
	}
	XTAL_LET  negative_x = [] (XTAL_DEF value)
	XTAL_0FN_(negative_y(XTAL_REF_(value)));
	///<\
	Function expression for `negative_y` \
	
	static_assert(negative_y( 1.0) ==  0.0);
	static_assert(negative_y( 0.0) ==  0.0);
	static_assert(negative_y(-1.0) == -1.0);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//	TODO: Assess performance of both branches for `truncate` and `puncture`. \

	/// Modifies the `target`, clamping the magnitude below `dnsilon_y(N_zoom)*diplo_y(zone)`. \

	///\returns zero if unchanged, else the sign of the `target`. \
	
	template <delta_t N_zoom=0, bool N_zero=0>
	XTAL_FZ1_(alpha_t) truncate_z(alpha_t &target, delta_t const &zone)
	XTAL_0EX
	{
		auto constexpr N_unit = N_zero ^ 1;
		if constexpr (IEC_559)
		{
			auto const Z = unit::mask - flag_f(N_zoom - 1);
			auto const N = zone << exponent::shift;
			auto const M = N + Z*N_unit;
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
		}
		else
		{
			auto const t = N_zero? maximal_y(zone): diplo_y(zone)*dnsilon_y(N_zoom);
			auto const s = design_z(target);
			auto const a = negative_y(t - target);
			target += a;
			target *= s;
			return s*(a != alpha_0);
		}
	}
	/// Modifies the `target`, clamping the magnitude below `maximal_y(N_zoom)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <delta_t N_zoom=0>
	XTAL_FZ1_(alpha_t) truncate_z(alpha_t &target)
	XTAL_0EX
	{
		if constexpr (0 == N_zoom) return resign_y(alpha_0, target); // `target` unchanged
		else return truncate_z<0, 1>(target, N_zoom);
	}
	

	///\returns the `target` with magnitude clamped to the region below `diplo_y(zone)*dnsilon_y(N_zoom)`. \

	template <delta_t N_zoom=0, bool N_zero=0>
	XTAL_FZ2_(alpha_t) truncate_y(alpha_t target, delta_t const &zone)
	XTAL_0EX
	{
		auto constexpr N_unit = N_zero ^ 1;
		if constexpr (IEC_559)
		{
			auto const Z = unit::mask - flag_f(N_zoom - 1);
			auto const N = zone << exponent::shift;
			auto const M = N + Z*N_unit;
			delta_t m, n, i;
			auto  t  = _std::bit_cast<delta_t> (_std::move(target));
			m  =  t  & ~sign::mask;
			m  =  M  -  m;
			i  =  m >>  positive::depth;
			t +=  i  &  m;
			return     _std::bit_cast<alpha_t> (_std::move(t));
		}
		else
		{
			auto const t = N_zero? maximal_y(zone): diplo_y(zone)*dnsilon_y(N_zoom);
			auto const s = design_z(target);
			auto const a = negative_y(t - target);
			target += a;
			target *= s;
			return target;

		}
	}
	///\returns the `target` with magnitude clamped to the region below `maximal_y(N_zoom)`. \

	template <delta_t N_zoom=0>
	XTAL_FZ2_(alpha_t) truncate_y(alpha_t target)
	XTAL_0EX
	{
		if constexpr (0 == N_zoom) return resign_y(alpha_0, target); // `target` unchanged
		else return truncate_y<0, 1>(target, N_zoom);
	}



////////////////////////////////////////////////////////////////////////////////

	/// Modifies the `target`, clamping the magnitude above `upsilon_y(N_zoom)*diplo_y(zone)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <delta_t N_zoom=0, bool N_zero=0>
	XTAL_FZ1_(alpha_t) puncture_z(alpha_t &target, delta_t const &zone)
	XTAL_0EX
	{
		auto constexpr N_unit = N_zero ^ 1;
		if constexpr (IEC_559)
		{
			auto const Z = unit::mask + flag_f(N_zoom - 1);
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
		}
		else
		{
			auto const t = N_zero? minimal_y(zone): diplo_y(zone)*upsilon_y(N_zoom);
			auto const s = design_z(target);
			auto const a = positive_y(t - target);
			target += a;
			target *= s;
			return s*(a != alpha_0);
		}
	}
	/// Modifies the `target`, clamping the magnitude above `minimal_y(N_zoom)`. \

	///\returns zero if unchanged, else the sign of the `target`. \

	template <delta_t N_zoom=0>
	XTAL_FZ1_(alpha_t) puncture_z(alpha_t &target)
	XTAL_0EX
	{
		if constexpr (0 == N_zoom) return resign_y(alpha_0, target); // `target` unchanged
		else return puncture_z<0, 1>(target, N_zoom);
	}
	

	///\returns the `target` with magnitude clamped to the region above `diplo_y(zone)*upsilon_y(N_zoom)`. \

	template <delta_t N_zoom=0, bool N_zero=0>
	XTAL_FZ2_(alpha_t) puncture_y(alpha_t target, delta_t const &zone)
	XTAL_0EX
	{
		auto constexpr N_unit = N_zero ^ 1;
		if constexpr (IEC_559)
		{
			auto const Z = unit::mask + flag_f(N_zoom - 1);
			auto const N = zone << exponent::shift;
			auto const M = N + Z*N_unit;
			delta_t m, n, i;
			auto  t  = _std::bit_cast<delta_t> (_std::move(target));
			m   = t  & ~sign::mask;
			m  -= M;
			i   = m >>  positive::depth;
			t  -= i  &  m;
			return     _std::bit_cast<alpha_t> (_std::move(t));
		}
		else
		{
			auto const t = N_zero? minimal_y(zone): diplo_y(zone)*upsilon_y(N_zoom);
			auto const s = design_z(target);
			auto const a = positive_y(t - target);
			target += a;
			target *= s;
			return target;
		}
	}
	///\returns the `target` with magnitude clamped to the region above `minimal_y(N_zoom)`. \

	template <delta_t N_zoom=0>
	XTAL_FZ2_(alpha_t) puncture_y(alpha_t target)
	XTAL_0EX
	{
		if constexpr (0 == N_zoom) return resign_y(alpha_0, target); // `target` unchanged
		else return puncture_y<0, 1>(target, N_zoom);
	}


	///\returns the `target` without the lowest `N_zoom` bits of precision. \

	template <delta_t N_zoom=0>
	XTAL_FZ2_(alpha_t) approximate_y(alpha_t target)
	XTAL_0EX
	{
		if constexpr (IEC_559|1)
		{
			auto constexpr M = -1 << N_zoom;
			return _std::bit_cast<alpha_t> (_std::bit_cast<delta_t> (_std::move(target)) & M);
		}
		else
		{
		//	TODO: Fix this, and prevent optimization.

			auto constexpr N = fraction::depth - N_zoom;
			target *= minimal_y(N);
			target *= maximal_y(N);
			return target;
		}
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	XTAL_LET_(alpha_t) domain_v[] = {1.
	,	6.2831853071795864769252867665590057683943387987502116419498891846//2*Pi
	,	0.6931471805599453094172321214581765680755001343602552541206800094//Log[2]
	,	3.1415926535897932384626433832795028841971693993751058209749445923//1*Pi
	};

	template <delta_t N_base=0>
	XTAL_FZ2_(alpha_t) domain_y(delta_t n_base)
	XTAL_0EX
	{
		return domain_v[n_base&0b11]/domain_v[N_base&0b11];
	}
	template <auto... etc>
	XTAL_LET  domain_x = [] <typename W> (W &&w)
	XTAL_0FN_(domain_y<etc...> (XTAL_FWD_(W) (w)));


	template <delta_t N_base=0>
	XTAL_FZ2_(alpha_t) codomain_y(delta_t n_base)
	XTAL_0EX
	{
		return domain_v[N_base&0b11]/domain_v[n_base&0b11];
	}
	template <auto... etc>
	XTAL_LET  codomain_x = [] <typename W> (W &&w)
	XTAL_0FN_(codomain_y<etc...> (XTAL_FWD_(W) (w)));

};

//using realized  = realize<unsigned int>;
using realized  = realize<_std::size_t>;

using aleph_t = typename realized::aleph_t;
using alpha_t = typename realized::alpha_t;
using  iota_t = typename realized:: iota_t;
using delta_t = typename realized::delta_t;//_std::ptrdiff_t;
using sigma_t = typename realized::sigma_t;//_std::size_t;

static_assert(sizeof(_std::size_t) == sizeof(alpha_t));
static_assert(sizeof(_std::size_t) == sizeof(delta_t));
static_assert(sizeof(_std::size_t) == sizeof(sigma_t));
static_assert(_std::is_same_v<_std::size_t,  sigma_t>);

///////////////////////////////////////////////////////////////////////////////

template <typename    T >     concept    complex_b   = requires (T t) {{t.real()} -> _std::same_as<decltype(t.imag())>;};
template <typename    T >     concept    boolean_b   = _std::is_same_v     <bool, _std::remove_reference_t<T>>;
template <typename    T >     concept       iota_b   = _std::is_integral_v       <_std::remove_reference_t<T>>;
template <typename    T >     concept      alpha_b   = _std::is_floating_point_v <_std::remove_reference_t<T>>;
template <typename    T >     concept      aleph_b   = complex_b<T> and requires (T t) {{t.real()} -> alpha_b;};
template <typename    T >     struct       field     : _std::false_type {};
template <complex_b   T >     struct       field<T>  : _std:: true_type {};
template <alpha_b     T >     struct       field<T>  : _std:: true_type {};
template <typename    T >     concept      field_b   = field<T>::value;

template <typename... Ts>     concept    complex_q   = unfalse_q<complex_b<Ts>...>;
template <typename... Ts>     concept    boolean_q   = unfalse_q<boolean_b<Ts>...>;
template <typename... Ts>     concept       iota_q   = unfalse_q<   iota_b<Ts>...>;
template <typename... Ts>     concept      alpha_q   = unfalse_q<  alpha_b<Ts>...>;
template <typename... Ts>     concept      aleph_q   = unfalse_q<  aleph_b<Ts>...>;
template <typename... Ts>     concept      field_q   = unfalse_q<  field_b<Ts>...>;

template <typename    T >     concept    equated_b   = requires (T u, T v) {u  == v;};
template <typename    T >     concept    ordered_b   = requires (T u, T v) {u <=> v;};
template <typename    T >     concept    numeric_b   = iota_b<T> or field_b<T>;

template <typename... Ts>     concept    equated_q   = unfalse_q<equated_b<Ts>...>;
template <typename... Ts>     concept    ordered_q   = unfalse_q<ordered_b<Ts>...>;
template <typename... Ts>     concept    numeric_q   = iota_q<Ts...> or field_q<Ts...>;

template <typename... Ts>     struct       craft      {using type = _std::variant<Ts...>;};
template <              >     struct       craft< >   {using type = _std::monostate     ;};
template <typename    T >     struct       craft<T>   {using type = T                 ;};
template <typename... Ts>     using        craft_t   = typename craft<Ts...>::type;
template <typename... Ts>     XTAL_LET     craft_f   = [] (XTAL_DEF... ws) XTAL_0FN_(craft_t<Ts...> (XTAL_REF_(ws)...));

template <typename    T >     struct       shape       {using type =      T;};
template <              >     struct       shape<bool> {using type = bool  ;};
template <iota_q      T >     struct       shape<T>    {using type = iota_t;};
template <alpha_q     T >     struct       shape<T>    {using type = alpha_t;};
template <typename    T >     using        shape_t   = typename shape<T>::type;
									   XTAL_LET     shape_f   = [] <typename T> (T &&t) XTAL_0FN_(shape_t<T> (XTAL_FWD_(T) (t)));

template <auto        N >     using        cased     = _std::integral_constant<shape_t<XTAL_TYP_(N)>, N>;
template <typename    T >     concept      cased_b   = _std::is_base_of_v<_std::integral_constant<typename T::value_type, T::value>, T>;
template <typename... Ts>     concept      cased_q   = unfalse_q<cased_b<Ts>...>;

template <typename    T >     using        based_t   = _std::decay_t<T>;
template <typename    T >     concept      based_b   = _std::is_same_v<T, based_t<T>> and _std::is_trivially_copy_constructible_v<T>;
template <typename    T >     concept    unbased_b   = not based_b<T>;

template <typename    T >     struct     debased           : cased<false> {using type = based_t<T>;};
template <typename    T >     struct     debased<T const &>: cased<false> {using type = based_t<T>;};
template <unbased_b   T >     struct     debased<T       &>: cased<true>  {using type =         T*;};
template <typename    T >     using      debased_t   = typename debased<T>::type;
template <typename    T >     concept    debased_b   =          debased<T>::value;

template <typename... Ts>     concept    debased_q   = unfalse_q<debased_b<Ts>...>;
template <typename... Ts>     concept    unbased_q   = unfalse_q<unbased_b<Ts>...>;
template <typename... Ts>     concept      based_q   = unfalse_q<  based_b<Ts>...>;

template <typename    V >     using      bracket_t   = _std::initializer_list<V>;
template <sigma_t...  Ns>     using         seek_t   = _std::     index_sequence<Ns...>;
template <sigma_t     N >     XTAL_LET      seek_v   = _std::make_index_sequence<N>{};
template <sigma_t     N >     XTAL_LET      seek_y   = [] <typename W> (W &&w) XTAL_0FN_(XTAL_REF_(w));
template <auto N=0> XTAL_FZ1 seek_f(            auto f) XTAL_0EX {return [&] <auto... Ns> (seek_t<Ns...>) XTAL_0FN_(              ..., f(Ns)) (seek_v<N>);}
template <auto N=0> XTAL_FZ1 seek_f(XTAL_DEF w, auto f) XTAL_0EX {return [&] <auto... Ns> (seek_t<Ns...>) XTAL_0FN_(XTAL_REF_(w), ..., f(Ns)) (seek_v<N>);}

///////////////////////////////////////////////////////////////////////////////

template <typename... Ys>
struct identical
:	_std::false_type
{};

XTAL_FZ2_(bool) id_y(XTAL_DEF s, XTAL_DEF t)
XTAL_0EX
{
	return _std::addressof(XTAL_REF_(s)) == _std::addressof(XTAL_REF_(t));
}

template <typename T, typename... Ys>
struct identical<T, Ys...>
:	_std::disjunction<_std::is_same<T, Ys>...>
{};
template <typename... Ys>
struct isomeric
:	identical<based_t<Ys>...> 
{};
template <typename... Ys>
struct isomorphic
:	isomeric<Ys...>
{};
template <typename... Ys>              concept id_q = identical <Ys...>::value;
template <typename... Ys>              concept is_q = isomeric  <Ys...>::value;
template <typename... Ys>      concept isomorphic_q = isomorphic<Ys...>::value;

template <typename T, typename    Y >  concept as_b = requires (T t) {based_t<Y> (t);};//TODO: Remove `based_t`?
template <typename T, typename... Ys>  concept as_q = unfalse_q<as_b<T, Ys>...>;

template <typename T, typename    Y >  concept of_b = _std::is_base_of_v<based_t<Y>, based_t<T>>;
template <typename T, typename... Ys>  concept of_q = unfalse_q<of_b<T, Ys>...> or numeric_q<T, Ys...>;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename T>
XTAL_FZ2_(T) square_y(T const &lhs)
XTAL_0EX
{
	return lhs * lhs;
}
template <complex_q T>
XTAL_FZ2_(T) square_y(T const &lhs)
XTAL_0EX
{
	auto const x = lhs.real(), xx = square_y(x);
	auto const y = lhs.imag(), yy = square_y(y);
	return T(xx - yy, x*y*2.0);
}

template <complex_q T>
XTAL_FZ2_(T) dot_y(T const &lhs)
XTAL_0EX
{
	auto const x = lhs.real(), xx = square_y(x);
	auto const y = lhs.imag(), yy = square_y(y);
	return xx + yy;
}

template <complex_q T>
XTAL_FZ2_(T) arc_y(auto const &phi)
XTAL_0EX
{
	auto const x = _std::cos(phi);
	auto const y = _std::sin(phi);
	return T(x, y);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <_std::integral T>
XTAL_FZ2_(T) bit_floor_y(T n)
XTAL_0EX
{
	T m = 0;
	for (; n >>= 1; ++m);
	return m;
}
template <sigma_t N, sigma_t M=0>
concept bit_floor_q = N == 1 << (bit_floor_y(N >> M) + M);


template <_std::integral T>
XTAL_FZ2_(T) bit_ceiling_y(T const &n)
XTAL_0EX
{
	T m = bit_floor_y<T>(n);
	m += 1 << m != n;
	return m;
}
template <sigma_t N, sigma_t M=0>
concept bit_ceiling_q = N == 1 << (bit_ceiling_y(N >> M) + M);


///\returns the bitwise-reversal of the given value `n`, \
restricted to `N_subdepth` iff `0 < N_subdepth < depth`. \

///\note Requires `log2(realized::depth)` iterations. \

///\note Can be reified as a `process` to dynamically control `N_subdepth`. \

template <sigma_t N_subdepth=0>
XTAL_FZ2 bit_reverse_y(_std::integral auto n)
XTAL_0EX
{
	using realized = realize<XTAL_TYP_(n)>;
	auto constexpr depth = realized::depth;

	static_assert(0 <= N_subdepth && N_subdepth <= depth);
	if constexpr (0 == N_subdepth || N_subdepth == depth)
	{
		for (sigma_t m = -1, i = depth; i >>= 1;)
		{
			m ^= m<<i;
			n = (n&m)<<i | (n&~m)>>i;
		}
		return n;
	}
	else
	{
		return bit_reverse_y<0>(n) >> (depth - N_subdepth);
	}
}
template <sigma_t N_subdepth=0>
XTAL_LET  bit_reverse_x = [] (XTAL_DEF n)
XTAL_0FN_(bit_reverse_y<N_subdepth> (XTAL_REF_(n)));
///<\
Function expression of `bit_reverse_y`. \

static_assert(bit_reverse_x<0> (realized::sigma_1 << (realized::depth - 1)) == 1);


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// TODO: Implement `constexpr sqrt`. \


///\see `realized::truncate_y`. \

template <delta_t N_zoom=0>
XTAL_FZ2 truncate_y(XTAL_DEF_(alpha_q) target, XTAL_DEF... zone)
XTAL_0EX
{
	using realized = realize<XTAL_TYP_(target)>;
	return realized::template truncate_y<N_zoom>(XTAL_REF_(target), XTAL_REF_(zone)...);
}
///\see `realized::truncate_y`. \

template <delta_t N_zoom=0>
XTAL_FZ2 truncate_y(XTAL_DEF_(complex_q) target, XTAL_DEF... zone)
XTAL_0EX
{
	auto x = target.real();
	auto y = target.imag();
	auto m = 1.0/_std::sqrt(square_y(x) + square_y(x));
	realize<XTAL_TYP_(m)>::template puncture_z<N_zoom>(m, XTAL_REF_(zone)...);
	x *= m;
	y *= m;
	return XTAL_TYP_(target) {x, y};
}


///\see `realized::puncture_y`. \

template <delta_t N_zoom=0>
XTAL_FZ2 puncture_y(XTAL_DEF_(alpha_q) target, XTAL_DEF... zone)
XTAL_0EX
{
	using realized = realize<XTAL_TYP_(target)>;
	return realized::template puncture_y<N_zoom>(XTAL_REF_(target), XTAL_REF_(zone)...);
}
///\see `realized::puncture_y`. \

template <delta_t N_zoom=0>
XTAL_FZ2 puncture_y(XTAL_DEF_(complex_q) target, XTAL_DEF... zone)
XTAL_0EX
{
	auto x = target.real();
	auto y = target.imag();
	auto m = 1.0/_std::sqrt(square_y(x) + square_y(x));
	realize<XTAL_TYP_(m)>::template truncate_z<N_zoom>(m, XTAL_REF_(zone)...);
	x *= m;
	y *= m;
	return XTAL_TYP_(target) {x, y};
}


///\see `realized::approximate_y`. \

template <delta_t N_zoom=0>
XTAL_FZ2 approximate_y(XTAL_DEF_(alpha_q) target)
XTAL_0EX
{
	using realized = realize<XTAL_TYP_(target)>;
	return realized::template approximate_y<N_zoom>(XTAL_REF_(target));
}
///\see `realized::approximate_y`. \

template <delta_t N_zoom=0>
XTAL_FZ2 approximate_y(XTAL_DEF_(complex_q) target)
XTAL_0EX
{
	auto const x = approximate_y<N_zoom>(target.real());
	auto const y = approximate_y<N_zoom>(target.imag());
	return XTAL_TYP_(target) {x, y};
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
