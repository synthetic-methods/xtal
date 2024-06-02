#pragma once
#include "./any.hh"
#include "./linear.hh"





XTAL_ENV_(push)
namespace xtal::algebra::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP circular;
template <class   ..._s>	XTAL_USE circular_t = typename circular<_s...>::type;
template <class   ...Ts>	XTAL_ASK circular_q = bond::head_tag_p<circular, Ts...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_FN1 circular_f(auto &&...oo)
XTAL_0EX {return _detail::build<circular_t>::template via<V>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `linear` as a fixed-point fractional/circular value. \
\
Allows floating-point construction via `std::initializer_list`, \
and access to the floating-point value via `operator()`/`operator(size_t)`. \
\
Implements truncated floating-point multiplication (affecting all elements) \
and addition (affecting only the initial element). \

///\todo\
Might be worth implementing multiplication for the first element only, \
either by truncating the type or by parameterizing the operator. \
The latter could be achieved using `std::initializer_list`s, \
parameterized by an `U_alpha`-wrapper with a distinguished element. \

template <class K_data> requires disarray_q<K_data>
struct circular<K_data> : circular<K_data[2]>
{};
template <class K_data, size_t N_data>
struct circular<K_data[N_data]>
{
	using Op = bond::operate<K_data>;
	using U_delta = typename Op::delta_t;
	using U_sigma = typename Op::sigma_t;
	using U_alpha = typename Op::alpha_t;
	
	using W_delta = linear_t<U_delta[N_data]>;
	using W_sigma = linear_t<U_sigma[N_data]>;
	using W_alpha = linear_t<U_alpha[N_data]>;

	static_assert(_std::numeric_limits<U_sigma>::is_modulo);// D'oh!

	template <class T>
	using allotype = typename linear<U_sigma[N_data]>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<circular>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;

		XTAL_LET   ordinate_f = [] (U_alpha const &o) XTAL_0FN_(static_cast<U_sigma>(U_delta(o*Op::diplo_f())));
		XTAL_LET coordinate_f = [] (U_sigma const &o) XTAL_0FN_(U_alpha(static_cast<U_delta>(o))*Op::haplo_f());

	public:// MAP
		XTAL_DEF_(return,inline) XTAL_FN1   ordinate(auto &&o) XTAL_0EX {return   ordinate_f(XTAL_REF_(o));}
		XTAL_DEF_(return,inline) XTAL_FN1 coordinate(auto &&o) XTAL_0EX {return coordinate_f(XTAL_REF_(o));}

	public:// ACCESS
		using T_::self;
		using T_::twin;
		using T_::get;
		using T_::let;

		XTAL_OP2() (size_t i) XTAL_0FX {return self().got(i);}
	//	XTAL_OP2 * (        ) XTAL_0FX {return self().got( );}
	//	using T_::operator*;

	public:// CONSTRUCTION
	//	using T_::T_;

	//	Reified to allow inspection of initializer-type:
		using initializer_list = _std::initializer_list<U_alpha>;

		XTAL_CO0_(homotype)
	//	XTAL_CO1_(homotype)
		XTAL_CO4_(homotype)
		
		XTAL_CXN homotype(size_t const n)
		XTAL_0EX
		:	T_(n)
		{}

		XTAL_CON  homotype                          () XTAL_0EX : homotype(size_0)                                                {}
		XTAL_CXN  homotype  (real_number_q auto ...oo) XTAL_0EX : homotype(sizeof...(oo))         {operator>>=({XTAL_MOV_(oo)...});}
		XTAL_CON  homotype        (initializer_list o) XTAL_0EX : homotype(count_f(XTAL_REF_(o))) {operator<<=( XTAL_REF_(o)     );}
		XTAL_CXN  homotype        (bounded_q auto &&o) XTAL_0EX : homotype(count_f(XTAL_MOV_(o))) {operator<<=( XTAL_REF_(o)     );}
		
		using T_::operator >>=;
		using T_::operator <<=;

		XTAL_OP1_(homotype &) >>= (initializer_list o) XTAL_0EX {_detail::copy_to(T_::data(), XTAL_REF_(o), ordinate_f); return *this;}
		XTAL_OP1_(homotype &) >>= (bounded_q auto &&o) XTAL_0EX {_detail::move_to(T_::data(), XTAL_REF_(o), ordinate_f); return *this;}
		
		XTAL_OP1_(homotype &) <<= (initializer_list o) XTAL_0EX {_detail::copy_to(_std::next(T_::data(), T_::size() - o.size()), XTAL_REF_(o), ordinate_f); return *this;}
		XTAL_OP1_(homotype &) <<= (bounded_q auto &&o) XTAL_0EX {_detail::move_to(_std::next(T_::data(), T_::size() - o.size()), XTAL_REF_(o), ordinate_f); return *this;}
		
	public:// OPERATION
		///\
		Scales all elements. \

		///\note\
		The symmetric signatures for `/=` and `*=` are declared-but-undefined \
		to avoid compilation-failure when type-checking e.g. `multiplicative_group_q`. \

		auto operator /= (T const &) XTAL_0EX -> T &;// Asymmetric!
		using T_::operator/=;

		XTAL_OP1_(T &) /= (number_q auto const &f)
		XTAL_0EX
		{
			return operator*=(Op::alpha_1/f);
		}

		auto operator *= (T const &) XTAL_0EX -> T &;// Asymmetric!
		using T_::operator*=;

		//\note\
		This unit-circular fixed-point multiply has ~20 bit accuracy, \
		and takes ~40% longer than the equivalent multiplication/rounding/subtraction. \

		XTAL_OP1_(T &) *= (real_number_q auto const &f)
		XTAL_0EX
		{
			size_t constexpr M_bias = Op::N_width >> 3;
			size_t constexpr M_size = Op::half.depth - M_bias;// {52,23} -> {23, 9}
			auto [m, n] = Op::scientific_f((U_alpha) f);
			auto &s = reinterpret_cast<W_delta &>(self());
			m >>= n - M_size;
			s >>=     M_size;
			s  *= m;
			return self();
		}
		
		XTAL_OP1_(T &) *= (integral_number_q auto const &i)
		XTAL_0EX
		{
			return T_::operator*=(i);
		}

		///\
		Offsets the first element. \
		
		using T_::operator-=;
		using T_::operator+=;

		XTAL_OP1_(T &) -= (number_q auto const &f)
		XTAL_0EX
		{
			return operator+=(-f);
		}
		XTAL_OP1_(T &) += (real_number_q auto const &f)
		XTAL_0EX
		{
			T_::operator[](0) += Op::fractional_f(f);
			return self();
		}
		XTAL_OP1_(T &) += (integral_number_q auto const &i)
		XTAL_0EX
		{
			return self();
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
