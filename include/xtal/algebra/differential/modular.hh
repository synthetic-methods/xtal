#pragma once
#include "./any.hh"
#include "./linear.hh"





XTAL_ENV_(push)
namespace xtal::algebra::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_TYP modular;
template <class ..._s> XTAL_USE modular_t = typename modular<_s...>::type;
template <class ...Ts> XTAL_ASK modular_q = bond::tag_p<modular, Ts...>;

XTAL_LET  modular_f = []<class ...Xs> (Xs &&...xs)
XTAL_0FN_(modular_t<common_t<Xs...>[sizeof...(Xs)]>{XTAL_REF_(xs)...});


////////////////////////////////////////////////////////////////////////////////
///\
Extends `linear` as a fixed-point fractional/modular value. \
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
struct modular<K_data> : modular<K_data[2]>
{};
template <class K_data, size_t N_data>
struct modular<K_data[N_data]>
{
	using re = bond::realize<K_data>;
	using U_delta = typename re::delta_t;
	using U_sigma = typename re::sigma_t;
	using U_alpha = typename re::alpha_t;
	
	using W_delta = linear_t<U_delta[N_data]>;
	using W_sigma = linear_t<U_sigma[N_data]>;
	using W_alpha = linear_t<U_alpha[N_data]>;
	using M_alpha = bond::pact_make_t<W_alpha>;
//	using M_alpha = bond::pact_t<U_alpha, U_alpha>;

	XTAL_LET   ordinant = [] (U_alpha const &u) XTAL_0FN_(static_cast<U_sigma>(U_delta(u*re::diplo_f())));
	XTAL_LET coordinant = [] (U_sigma const &v) XTAL_0FN_(U_alpha(static_cast<U_delta>(v))*re::haplo_f());

	static_assert(_std::numeric_limits<U_sigma>::is_modulo);// D'oh!

	template <class T>
	using allotype = typename linear<U_sigma[N_data]>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<modular>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;

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

		XTAL_CON  homotype                          () XTAL_0EX : homotype(size_0)                                                  {}
		XTAL_CXN  homotype  (real_number_q auto ...oo) XTAL_0EX : homotype(sizeof...(oo))           {operator>>=({XTAL_MOV_(oo)...});}
		XTAL_CON  homotype        (initializer_list o) XTAL_0EX : homotype(devalue_f(XTAL_REF_(o))) {operator<<=( XTAL_REF_(o)     );}
		XTAL_CXN  homotype        (bounded_q auto &&o) XTAL_0EX : homotype(devalue_f(XTAL_MOV_(o))) {operator<<=( XTAL_REF_(o)     );}
		
		using T_::operator >>=;
		using T_::operator <<=;

		XTAL_OP1_(homotype &) >>= (initializer_list o) XTAL_0EX {_detail::copy_to(T_::data(), XTAL_REF_(o), ordinant); return *this;}
		XTAL_OP1_(homotype &) >>= (bounded_q auto &&o) XTAL_0EX {_detail::move_to(T_::data(), XTAL_REF_(o), ordinant); return *this;}
		
		XTAL_OP1_(homotype &) <<= (initializer_list o) XTAL_0EX {_detail::copy_to(_std::next(T_::data(), T_::size() - o.size()), XTAL_REF_(o), ordinant); return *this;}
		XTAL_OP1_(homotype &) <<= (bounded_q auto &&o) XTAL_0EX {_detail::move_to(_std::next(T_::data(), T_::size() - o.size()), XTAL_REF_(o), ordinant); return *this;}
		
	public:// OPERATION
		using T_::self;
		using T_::twin;
		using T_::get;
		using T_::let;

		XTAL_FN2   ordinate(U_alpha u) XTAL_0EX {return   ordinant(u);}
		XTAL_FN2 coordinate(U_sigma u) XTAL_0EX {return coordinant(u);}

		XTAL_OP2 () (        ) XTAL_0FX {return self().got( );}
		XTAL_OP2 () (size_t i) XTAL_0FX {return self().got(i);}
		
		///\
		Scales all elements. \

		///\note\
		The symmetric signatures for `/=` and `*=` are declared-but-undefined \
		to avoid compilation-failure when type-checking e.g. `multiplicative_group_q`. \

		XTAL_VAR operator /= (T const &) XTAL_0EX -> T &;// Asymmetric!
		using T_::operator/=;

		XTAL_OP1_(T &) /= (number_q auto const &f)
		XTAL_0EX
		{
			return operator*=(re::alpha_1/f);
		}

		XTAL_VAR operator *= (T const &) XTAL_0EX -> T &;// Asymmetric!
		using T_::operator*=;

		//\note\
		This unit-modular fixed-point multiply has ~20 bit accuracy, \
		and takes ~40% longer than the equivalent multiplication/rounding/subtraction. \

		XTAL_OP1_(T &) *= (real_number_q auto const &f)
		XTAL_0EX
		{
			size_t constexpr M_bias = re::N_width >> 3;
			size_t constexpr M_size = re::half.depth - M_bias;// {52,23} -> {23, 9}
			auto [m, n] = re::scientific_f((U_alpha) f);
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
			T_::operator[](0) += re::fractional_f(f);
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
/**/
namespace xtal
{///////////////////////////////////////////////////////////////////////////////

//template <size_t N_datum, algebra::differential::modular_q T> XTAL_FN2 get(T &&t)
//XTAL_0EX {return XTAL_REF_(t) (N_datum);}


}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
