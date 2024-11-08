#pragma once
#include "./any.hh"
#include "./linear.hh"





XTAL_ENV_(push)
namespace xtal::algebra::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends `linear` as a fixed-point fractional/circular value. \
\
Allows floating-point construction via `std::initializer_list`, \
and access to the floating-point value via `operator()`/`operator(size_type)`. \
\
Implements truncated floating-point multiplication (affecting all elements) \
and addition (affecting only the initial element). \

///\todo\
Might be worth implementing multiplication for the first element only, \
either by truncating the type or by parameterizing the operator. \
The latter could be achieved using `std::initializer_list`s, \
parameterized by an `continuous_field_q`-wrapper with a distinguished head. \

///\todo\
Rework `operator`s to accommodate `std::complex`. \

template <class   ..._s>	XTAL_TYP         circular;
template <class   ..._s>	XTAL_USE         circular_t = typename circular<_s...>::type;
template <class   ...Ts>	XTAL_REQ         circular_q = bond::any_tag_p<circular_t, Ts...>;
template <class   ...Ts>	XTAL_REQ    real_circular_q = bond::any_tag_p<circular_t, Ts...> and   real_number_q<debraced_t<Ts>...>;
template <class   ...Ts>	XTAL_REQ simplex_circular_q = bond::any_tag_p<circular_t, Ts...> and simplex_field_q<debraced_t<Ts>...>;
template <class   ...Ts>	XTAL_REQ complex_circular_q = bond::any_tag_p<circular_t, Ts...> and complex_field_q<debraced_t<Ts>...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_LET circular_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<circular_t>::template via<V>(XTAL_REF_(oo)...);}


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <            class V> struct circumspect    : circumspect<devolved_u<V>> {};
template <    real_number_q V> struct circumspect<V> : bond::operate<V>::template widen<-1> {};
template <integral_number_q V> struct circumspect<V> : bond::operate<V>::template widen< 0> {};

template <class V>
struct circumscribe : circumspect<V>
{
	using _op = circumspect<V>;
	using _Op = typename _op::template widen<1>;

	using   ordinate_type = typename _op::sigma_type;
	using inordinate_type = typename _op::delta_type;
	using coordinate_type = typename _Op::alpha_type;

	XTAL_DEF_(return,inline)
	XTAL_SET    ordinate(real_number_q auto const &co)
	XTAL_0EX -> ordinate_type
	{
		return _op::sigma_f(_op::delta_f(co*_op::diplo_f()));
	};
	XTAL_DEF_(return,inline)
	XTAL_SET    coordinate(integral_number_q auto const &o)
	XTAL_0EX -> coordinate_type
	{
		return _Op::alpha_f(_op::delta_f(o))*_op::haplo_f();
	};

};
template <complex_number_q A>
struct circumscribe<A> : circumscribe<devalued_u<A>>
{
	using _op = circumscribe<devalued_u<A>>;

	using   ordinate_type = _std::complex<typename _op::  ordinate_type>;
	using inordinate_type = _std::complex<typename _op::inordinate_type>;
	using coordinate_type = _std::complex<typename _op::coordinate_type>;

	XTAL_DEF_(return,inline)
	XTAL_SET    ordinate(coordinate_type const &co)
	XTAL_0EX -> ordinate_type
	{
		auto const o_re = _op::ordinate(co.real());
		auto const o_im = _op::ordinate(co.imag());
		return {o_re, o_im};
	};
	XTAL_DEF_(return,inline)
	XTAL_SET    coordinate(ordinate_type const &o)
	XTAL_0EX -> coordinate_type
	{
		auto const co_re = _op::coordinate(o.real());
		auto const co_im = _op::coordinate(o.imag());
		return {co_re, co_im};
	};
};
template <column_q A>
struct circumscribe<A> : circumscribe<devalued_u<A>>
{
};

static_assert(circumspect <double>::full.width == circumspect <int>::full.width);
static_assert(circumscribe<double>::full.width == circumscribe<int>::full.width);


}///////////////////////////////////////////////////////////////////////////////

template <column_q A>
struct circular<A>
{
	using _op = _detail::circumscribe<A>;
	
	XTAL_SET M_data = _std::extent_v<based_t<A>>;

	using   ordinate_type = typename _op::  ordinate_type;
	using inordinate_type = typename _op::inordinate_type;
	using coordinate_type = typename _op::coordinate_type;

	static_assert(_std::numeric_limits<devalued_u<ordinate_type>>::is_modulo);// D'oh!

	template <class T>
	using allotype = typename linear<ordinate_type[M_data]>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<circular_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  S_ = holotype<T>;

//		template <class A_>
//		using  Vs_ = typename T::template tagged<A_>::type;

	protected:
		using          S_::N_data;
		using typename S_::U_data;


	public:// MAP
		using   ordinates_type = linear<  ordinate_type[M_data]>;
		using coordinates_type = linear<coordinate_type[M_data]>;

		XTAL_DEF_(return,inline)
		XTAL_SET ordinate(coordinate_type const &co)
		XTAL_0EX
		{
			return _op::ordinate(co);
		}
		XTAL_DEF_(return,inline)
		XTAL_SET coordinate(ordinate_type const &o)
		XTAL_0EX
		{
			return _op::coordinate(o);
		}

	public:// ACCESS
		using S_::self;
		using S_::twin;
		using S_::let;

	public:// CONSTRUCT
	//	using S_::S_;

	//	Reified to allow inspection of initializer-type:
		using initializer_list = _std::initializer_list<coordinate_type>;

		XTAL_CO0_(homotype)
	//	XTAL_CO1_(homotype)
		XTAL_CO4_(homotype)
		
		XTAL_CON_(explicit) homotype(size_type const n)
		XTAL_0EX
		:	S_(n)
		{}

		XTAL_CON_(implicit) homotype()
		XTAL_0EX : homotype(size_0)
		{
		}
		XTAL_CON_(explicit) homotype(real_number_q auto &&...oo)
		XTAL_0EX : homotype(sizeof...(oo))
		{
			operator>>=({XTAL_REF_(oo)...});
		}
		XTAL_CON_(implicit) homotype(initializer_list o)
		XTAL_0EX : homotype(count_f(o))
		{
			operator>>=(XTAL_REF_(o));
		}
		XTAL_CON_(explicit) homotype(iterable_q auto &&o)
		XTAL_0EX : homotype(count_f(o))
		{
			operator>>=(XTAL_REF_(o));
		}
		
	//	XTAL_DEF_(inline)
	//	XTAL_DO4_(XTAL_CVN_(implicit)
	//	auto(),
	//	{
	//		if constexpr (complex_field_q<coordinate_type>) {
	//			using F = _std::complex<typename S_::template tagged_t<devalued_u<coordinate_type>[N_data]>>;
	//			auto &s = self();
	//			
	//			return [&]<auto ...I> (bond::seek_t<I...>)
	//				XTAL_0FN_(F({s(I).real()...}, {s(I).imag()...}))
	//			(bond::seek_s<N_data>{});
	//		}
	//	})
		
	public:// RECONSTRUCT
		using S_::operator >>=;
		using S_::operator <<=;

		XTAL_DEF_(inline)
		XTAL_LET operator >>=(initializer_list  o)
		XTAL_0EX -> homotype &
		{
			_detail::copy_to(S_::data()
			,	XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)
			);
			return *this;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator >>=(iterable_q auto &&o)
		XTAL_0EX -> homotype &
		{
			_detail::move_to(S_::data()
			,	XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)
			);
			return *this;
		}
		
		XTAL_DEF_(inline)
		XTAL_LET operator <<=(initializer_list  o)
		XTAL_0EX -> homotype &
		{
			_detail::copy_to(_std::next(S_::data(), S_::size() - o.size())
			,	XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)
			);
			return *this;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator <<=(iterable_q auto &&o)
		XTAL_0EX -> homotype &
		{
			_detail::move_to(_std::next(S_::data(), S_::size() - o.size())
			,	XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)
			);
			return *this;
		}

	public:// OPERATE
		
		///\
		Scales all elements. \

		///\note\
		The symmetric signatures for `/=` and `*=` are declared-but-undefined \
		to avoid compilation-failure when type-checking e.g. `multiplicative_group_q`. \

		using S_::operator*=;
		using S_::operator/=;

		auto operator *= (T const &) XTAL_0EX -> T &;// Asymmetric!
		auto operator /= (T const &) XTAL_0EX -> T &;// Asymmetric!

		XTAL_DEF_(return,inline)
		XTAL_LET operator * (auto const &t)
		XTAL_0FX {
			return twin() *= t;
		}
		XTAL_DEF_(return,inline)
		XTAL_LET operator / (auto const &t)
		XTAL_0FX {
			return twin() /= t;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator *= (initializer_list t)
		XTAL_0EX -> T &
		{
			return self() *= T(t);
		}
		XTAL_DEF_(inline)
		XTAL_LET operator /= (initializer_list t)
		XTAL_0EX -> T &
		{
			return self() /= T(t);
		}

		XTAL_DEF_(inline)
		XTAL_LET operator /= (number_q auto const &f)
		XTAL_0EX -> T &
		{
			return operator*=(_op::alpha_1/f);
		}
	//	XTAL_DEF_(inline)
		XTAL_LET operator *= (real_number_q auto const &f)
		XTAL_0EX -> T &
		{
			auto &s = reinterpret_cast<linear_t<inordinate_type[N_data]> &>(self());
			XTAL_IF0
			XTAL_0IF (1*sizeof(ordinate_type) == sizeof(coordinate_type)) {
				size_type constexpr M_bias = _op::half.depth >> _op::half.width;
				size_type constexpr M_size = _op::half.depth - M_bias;
				auto [m, n] = bond::operate<decltype(f)>::scientific_f(f);
				m >>= n - M_size;
				s >>=     M_size;
				s  *= m;
			}
			XTAL_IF0
			XTAL_0IF (2*sizeof(ordinate_type) == sizeof(coordinate_type)) {
				using V = typename bond::operate<coordinate_type>::sigma_type;
				using U = typename bond::operate<  ordinate_type>::sigma_type;
				V const s_k(f*_op::diplo_f());
				V       s_i;
				#pragma unroll
				for (int i{}; i < N_data; ++i) {
					s_i  = s_k*s[i];
					s[i] = reinterpret_cast<U(&)[2]>(s_i)[1];
				}
			}
			/***/
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator *= (integral_number_q auto const &i)
		XTAL_0EX -> T &
		{
			return S_::operator*=(i);
		}

		///\
		Offsets the first element. \
		
		using S_::operator-=;
		using S_::operator+=;

		XTAL_DEF_(inline)
		XTAL_LET operator -= (number_q auto const &f)
		XTAL_0EX -> T &
		{
			return operator+=(-f);
		}
		XTAL_DEF_(inline)
		XTAL_LET operator += (real_number_q auto const &f)
		XTAL_0EX -> T &
		{
			get<0>(*this) += _op::fractional_f(f);
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator += (integral_number_q auto const &i)
		XTAL_0EX -> T &
		{
			return self();
		}

		template <class Y=coordinate_type>
		XTAL_DEF_(return,inline)
		XTAL_LET continuity()
		XTAL_0EX -> Y
		{
			return condition_f<Y>(not discontinuity<bool>());
		}
		template <class Y=coordinate_type>
		XTAL_DEF_(return,inline)
		XTAL_LET discontinuity()
		XTAL_0EX -> Y
		{
			auto [u0, u1] = *this;
			auto const v0 = _xtd::make_signed_f(u0) >> _op::positive.depth; u0 ^= v0; u0 -= v0;
			auto const v1 = _xtd::make_signed_f(u1) >> _op::positive.depth; u1 ^= v1; u1 -= v1;
			return condition_f<Y>(v0 == v1 and u0 < u1);
		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(bond::pack_size_q<circular_t<double[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
