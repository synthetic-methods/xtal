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

template <class A>
struct circumspect : bond::operate<A>
{
	using _op = bond::operate<A>;

	using   ordinate_type = typename _op::sigma_type;
	using inordinate_type = typename _op::delta_type;
	using coordinate_type = typename _op::alpha_type;

	XTAL_DEF_(return,inline,static)
	XTAL_LET    ordinate(coordinate_type const &co)
	XTAL_0EX -> ordinate_type
	{
		return _xtd::bit_cast<ordinate_type>(static_cast<inordinate_type>(co*_op::diplo_f()));
	};
	XTAL_DEF_(return,inline,static)
	XTAL_LET    coordinate(ordinate_type const &o)
	XTAL_0EX -> coordinate_type
	{
		return static_cast<coordinate_type>(_xtd::bit_cast<inordinate_type>(o))*_op::haplo_f();
	};

};
template <class A>
	requires complex_number_q<devalued_t<A>>
struct circumspect<A> : bond::operate<A>
{
	using _op = bond::operate<A>;

	using   ordinate_type = _std::complex<typename _op::sigma_type>;
	using inordinate_type = _std::complex<typename _op::delta_type>;
	using coordinate_type = _std::complex<typename _op::alpha_type>;

	XTAL_DEF_(return,inline,static)
	XTAL_LET    ordinate(coordinate_type const &co)
	XTAL_0EX -> ordinate_type
	{
		auto const o_re = circumspect<devalued_t<A>>::ordinate(co.real());
		auto const o_im = circumspect<devalued_t<A>>::ordinate(co.imag());
		return {o_re, o_im};
	};
	XTAL_DEF_(return,inline,static)
	XTAL_LET    coordinate(ordinate_type const &o)
	XTAL_0EX -> coordinate_type
	{
		auto const co_re = circumspect<devalued_t<A>>::coordinate(o.real());
		auto const co_im = circumspect<devalued_t<A>>::coordinate(o.imag());
		return {co_re, co_im};
	};
};

}///////////////////////////////////////////////////////////////////////////////

template <column_q A>
struct circular<A>
{
	//\
	using _op = bond::operate<A>;
	using _op = _detail::circumspect<A>;
	
	using U_alpha = typename _op::alpha_type;
	using U_delta = typename _op::delta_type;
	using U_sigma = typename _op::sigma_type;
	
	using   ordinate_type = typename _op::   ordinate_type;
	using inordinate_type = typename _op:: inordinate_type;
	using coordinate_type = typename _op:: coordinate_type;

	static_assert(_std::numeric_limits<devalued_t<ordinate_type>>::is_modulo);// D'oh!

	template <class T>
	using allotype = typename linear<ordinate_type[_std::extent_v<A>]>::template homotype<T>;

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
		XTAL_DEF_(return,inline,static) XTAL_LET   ordinate(coordinate_type const &co) XTAL_0EX {return _op::  ordinate(co);}
		XTAL_DEF_(return,inline,static) XTAL_LET coordinate(  ordinate_type const & o) XTAL_0EX {return _op::coordinate( o);}

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

		XTAL_CON_(implicit)  homotype                           () XTAL_0EX : homotype(size_0)        {                                }
		XTAL_CON_(explicit)  homotype (real_number_q auto &&...oo) XTAL_0EX : homotype(sizeof...(oo)) {operator>>=({XTAL_REF_(oo)...});}
		XTAL_CON_(implicit)  homotype        (initializer_list  o) XTAL_0EX : homotype(count_f(o))    {operator>>=( XTAL_REF_(o)     );}
		XTAL_CON_(explicit)  homotype        (iterable_q auto &&o) XTAL_0EX : homotype(count_f(o))    {operator>>=( XTAL_REF_(o)     );}
		
	//	XTAL_DEF_(inline)
	//	XTAL_DO4_(XTAL_CVN_(implicit)
	//	auto(),
	//	{
	//		if constexpr (complex_field_q<coordinate_type>) {
	//			using F = _std::complex<typename S_::template tagged_t<devalued_t<coordinate_type>[N_data]>>;
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

		XTAL_DEF_(inline) XTAL_LET operator >>= (initializer_list  o) XTAL_0EX -> homotype & {_detail::copy_to(S_::data(), XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)); return *this;}
		XTAL_DEF_(inline) XTAL_LET operator >>= (iterable_q auto &&o) XTAL_0EX -> homotype & {_detail::move_to(S_::data(), XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)); return *this;}
		
		XTAL_DEF_(inline) XTAL_LET operator <<= (initializer_list  o) XTAL_0EX -> homotype & {_detail::copy_to(_std::next(S_::data(), S_::size() - o.size()), XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)); return *this;}
		XTAL_DEF_(inline) XTAL_LET operator <<= (iterable_q auto &&o) XTAL_0EX -> homotype & {_detail::move_to(_std::next(S_::data(), S_::size() - o.size()), XTAL_REF_(o), [this] XTAL_1FN_(self().ordinate)); return *this;}

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

		XTAL_DEF_(return,inline) XTAL_LET operator * (auto      const &t) XTAL_0FX        {return twin() *=   t ;}
		XTAL_DEF_(return,inline) XTAL_LET operator / (auto      const &t) XTAL_0FX        {return twin() /=   t ;}
		XTAL_DEF_(inline)        XTAL_LET operator *=(initializer_list t) XTAL_0EX -> T & {return self() *= T(t);}
		XTAL_DEF_(inline)        XTAL_LET operator /=(initializer_list t) XTAL_0EX -> T & {return self() /= T(t);}

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
			size_type constexpr M_bias = _op::N_width >> 3;
			size_type constexpr M_size = _op::half.depth - M_bias;// {52,23} -> {23, 9}
			auto [m, n] = _op::scientific_f((U_alpha) f);
			auto &s = reinterpret_cast<linear_t<U_delta[N_data]> &>(self());
			m >>= n - M_size;
			s >>=     M_size;
			s  *= m;
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
			S_::operator[](0) += _op::fractional_f(f);
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator += (integral_number_q auto const &i)
		XTAL_0EX -> T &
		{
			return self();
		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(bond::pack_size_q<circular_t<double[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
