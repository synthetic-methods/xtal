#pragma once
#include "./any.hh"
#include "./linear.hh"





XTAL_ENV_(push)
namespace xtal::algebra::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP circular;
template <class   ..._s>	XTAL_USE circular_t = typename circular<_s...>::type;
template <class   ...Ts>	XTAL_ASK circular_q = bond::head_tag_p<circular_t, Ts...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_FN1 circular_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<circular_t>::template via<V>(XTAL_REF_(oo)...);}


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

template <column_q A>
struct circular<A>
{
	using _op = bond::operate<A>;
	using U_delta = typename _op::delta_t;
	using U_sigma = typename _op::sigma_t;
	using U_alpha = typename _op::alpha_t;
	
	static_assert(_std::numeric_limits<U_sigma>::is_modulo);// D'oh!

	template <class T>
	using allotype = typename linear<U_sigma[_std::extent_v<A>]>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<circular_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;

	protected:
		using          T_::N_data;
		using typename T_::U_data;

	public:// MAP
		XTAL_DEF_(return,inline) XTAL_FN1   ordinate_f(U_alpha const &o) XTAL_0EX {return static_cast<U_sigma>(static_cast<U_delta>(o*_op::diplo_f()));};
		XTAL_DEF_(return,inline) XTAL_FN1 coordinate_f(U_sigma const &o) XTAL_0EX {return static_cast<U_alpha>(static_cast<U_delta>(o))*_op::haplo_f();};

	public:// ACCESS
		using T_::self;
		using T_::twin;
		using T_::get;
		using T_::let;

	//	using T_::operator*;
	//	XTAL_OP2 * (        ) XTAL_0FX {return self().got( );}
		XTAL_OP2() (size_t i) XTAL_0FX {return self().got(i);}

	public:// CONSTRUCT
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

		XTAL_CON  homotype                           () XTAL_0EX : homotype(size_0)        {                                }
		XTAL_CXN  homotype (real_number_q auto &&...oo) XTAL_0EX : homotype(sizeof...(oo)) {operator>>=({XTAL_REF_(oo)...});}
		XTAL_CON  homotype         (initializer_list o) XTAL_0EX : homotype(count_f(o))    {operator<<=( XTAL_REF_(o)     );}
		XTAL_CXN  homotype         (bounded_q auto &&o) XTAL_0EX : homotype(count_f(o))    {operator<<=( XTAL_REF_(o)     );}
		
	public:// RECONSTRUCT
		using T_::operator >>=;
		using T_::operator <<=;

		XTAL_OP1_(homotype &) >>= (initializer_list o) XTAL_0EX {_detail::copy_to(T_::data(), XTAL_REF_(o), [] XTAL_1FN_(T::ordinate_f)); return *this;}
		XTAL_OP1_(homotype &) >>= (bounded_q auto &&o) XTAL_0EX {_detail::move_to(T_::data(), XTAL_REF_(o), [] XTAL_1FN_(T::ordinate_f)); return *this;}
		
		XTAL_OP1_(homotype &) <<= (initializer_list o) XTAL_0EX {_detail::copy_to(_std::next(T_::data(), T_::size() - o.size()), XTAL_REF_(o), [] XTAL_1FN_(T::ordinate_f)); return *this;}
		XTAL_OP1_(homotype &) <<= (bounded_q auto &&o) XTAL_0EX {_detail::move_to(_std::next(T_::data(), T_::size() - o.size()), XTAL_REF_(o), [] XTAL_1FN_(T::ordinate_f)); return *this;}
		
	public:// OPERATE
		///\
		Scales all elements. \

		///\note\
		The symmetric signatures for `/=` and `*=` are declared-but-undefined \
		to avoid compilation-failure when type-checking e.g. `multiplicative_group_q`. \

		using T_::operator*=;
		using T_::operator/=;

		auto operator *= (T const &) XTAL_0EX -> T &;// Asymmetric!
		auto operator /= (T const &) XTAL_0EX -> T &;// Asymmetric!

		XTAL_DEF_(return,inline) XTAL_OP1_(auto) * (auto       const &t) XTAL_0FX XTAL_REQ_TO_(twin() *=  (t))
		XTAL_DEF_(return,inline) XTAL_OP1_(auto) / (auto       const &t) XTAL_0FX XTAL_REQ_TO_(twin() /=  (t))
		XTAL_DEF_(inline)        XTAL_OP1_(T  &) *=(embrace_t<U_data> t) XTAL_0EX XTAL_REQ_TO_(self() *= T(t))
		XTAL_DEF_(inline)        XTAL_OP1_(T  &) /=(embrace_t<U_data> t) XTAL_0EX XTAL_REQ_TO_(self() /= T(t))

		XTAL_OP1_(T &) /= (number_q auto const &f)
		XTAL_0EX
		{
			return operator*=(_op::alpha_1/f);
		}
		XTAL_OP1_(T &) *= (real_number_q auto const &f)
		XTAL_0EX
		{
			size_t constexpr M_bias = _op::N_width >> 3;
			size_t constexpr M_size = _op::half.depth - M_bias;// {52,23} -> {23, 9}
			auto [m, n] = _op::scientific_f((U_alpha) f);
			auto &s = reinterpret_cast<linear_t<U_delta[N_data]> &>(self());
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
			T_::operator[](0) += _op::fractional_f(f);
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
static_assert(bond::pack_size_q<circular_t<double[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
