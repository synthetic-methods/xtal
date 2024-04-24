#pragma once
#include "./any.hh"
#include "./linear.hh"





XTAL_ENV_(push)
namespace xtal::algebra::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  modular;
template <class ..._s> using   modular_t = typename modular<_s...>::type;
template <class ...Ts> concept modular_q = bond::tag_p<modular, Ts...>;

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

template <class U_data> requires disarray_q<U_data>
struct modular<U_data> : modular<U_data[2]>
{};
template <class A_data, size_t N_data>
struct modular<A_data[N_data]>
{
	using re = bond::realize<A_data>;
	using U_delta = typename re::delta_t;
	using U_sigma = typename re::sigma_t;
	using U_alpha = typename re::alpha_t;
	
	using W_delta = linear_t<U_delta[N_data]>;
	using W_sigma = linear_t<U_sigma[N_data]>;
	using W_alpha = linear_t<U_alpha[N_data]>;

	XTAL_LET V_f = [] (U_alpha const &u) XTAL_0FN_(_std::bit_cast<U_sigma>(U_delta(u*re::diplo_f())));
	XTAL_LET U_f = [] (U_sigma const &v) XTAL_0FN_(U_alpha(_std::bit_cast<U_delta>(v))*re::haplo_f());

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
		
		XTAL_CON homotype(size_t const n)
		XTAL_0EX
		:	T_(n)
		{}

		using T_::operator >>=;
		using T_::operator <<=;

		XTAL_CON  homotype                          () XTAL_0EX : homotype(size_0)                                                  {}
		XTAL_CON  homotype  (real_number_q auto ...oo) XTAL_0EX : homotype(sizeof...(oo))           {operator>>=({XTAL_MOV_(oo)...});}
		XTAL_CON  homotype        (initializer_list o) XTAL_0EX : homotype(devalue_f(XTAL_REF_(o))) {operator<<=( XTAL_REF_(o)     );}
		XTAL_CXN  homotype        (bounded_q auto &&o) XTAL_0EX : homotype(devalue_f(XTAL_MOV_(o))) {operator<<=( XTAL_REF_(o)     );}
		
		XTAL_OP1_(homotype &) >>= (initializer_list o) XTAL_0EX {_detail::copy_to(T_::data(), XTAL_REF_(o), V_f); return *this;}
		XTAL_OP1_(homotype &) >>= (bounded_q auto &&o) XTAL_0EX {_detail::move_to(T_::data(), XTAL_REF_(o), V_f); return *this;}
		
		XTAL_OP1_(homotype &) <<= (initializer_list o) XTAL_0EX {_detail::copy_to(_std::next(T_::data(), T_::size() - o.size()), XTAL_REF_(o), V_f); return *this;}
		XTAL_OP1_(homotype &) <<= (bounded_q auto &&o) XTAL_0EX {_detail::move_to(_std::next(T_::data(), T_::size() - o.size()), XTAL_REF_(o), V_f); return *this;}
		
	public:// OPERATION
		using T_::self;
		using T_::twin;

		XTAL_OP2 () ()                XTAL_0FX {return     T_::template transact<W_alpha>(U_f);}
		XTAL_OP2 () (size_t i)        XTAL_0FX {return U_f(T_::get(i));}
		XTAL_TN2 got(size_t i)        XTAL_0FX {return U_f(T_::get(i));}
		
		XTAL_OP0_(implicit) W_alpha() XTAL_0FX {return operator()( );}
		XTAL_OP0_(implicit) U_alpha() XTAL_0FX {return operator()(0);}

		///\
		Scales all elements. \

		///\note\
		The symmetric signatures for `/=` and `*=` are declared-but-undefined \
		to avoid compilation-failure when type-checking e.g. `multiplicative_group_q`. \

	//	using T_::operator/=;
		XTAL_VAR operator /= (T const &f)
		XTAL_0EX -> T &;// Asymmetric!

		XTAL_OP1_(T &) /= (number_q auto const &f)
		XTAL_0EX
		{
			return operator*=(re::alpha_1/f);
		}

	//	using T_::operator*=;
		XTAL_VAR operator *= (T const &t)
		XTAL_0EX -> T &;// Asymmetric!

		//\note\
		This unit-modular fixed-point multiply has ~30 bit accuracy, \
		and takes ~40% longer than the equivalent multiplication/rounding/subtraction. \

		XTAL_OP1_(T &) *= (real_number_q auto const &f)
		XTAL_0EX
		{
			size_t constexpr M_size = re::half.depth - 1;// {52,23} -> {20, 8}
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
