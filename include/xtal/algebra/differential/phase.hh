#pragma once
#include "./any.hh"
#include "./pulse.hh"





XTAL_ENV_(push)
namespace xtal::algebra::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  phase;
template <class ..._s> using   phase_t = typename phase<_s...>::type;
template <class ...Ts> concept phase_q = bond::tag_p<phase, Ts...>;

XTAL_LET  phase_f = []<class ...Xs> (Xs &&...xs)
XTAL_0FN_(phase_t<common_t<Xs...>[sizeof...(Xs)]>{XTAL_REF_(xs)...});


////////////////////////////////////////////////////////////////////////////////
///\
Extends `pulse` as a fixed-point fractional/phase value. \
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
struct phase<U_data> : phase<U_data[2]>
{};
template <class A_data, size_t N_data>
struct phase<A_data[N_data]>
{
	using re = bond::realize<A_data>;
	using U_delta = typename re::delta_t;
	using U_sigma = typename re::sigma_t;
	using U_alpha = typename re::alpha_t;
	
	using W_delta = pulse_t<U_delta[N_data]>;
	using W_sigma = pulse_t<U_sigma[N_data]>;
	using W_alpha = pulse_t<U_alpha[N_data]>;

	XTAL_LET V_f = [] (U_alpha const &u) XTAL_0FN_(_std::bit_cast<U_sigma>(U_delta(u*re::diplo_f())));
	XTAL_LET U_f = [] (U_sigma const &v) XTAL_0FN_(U_alpha(_std::bit_cast<U_delta>(v))*re::haplo_f());

	static_assert(_std::numeric_limits<U_sigma>::is_modulo);// D'oh!

	template <class T>
	using allotype = typename pulse<U_sigma[N_data]>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<phase>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;

	public:// CONSTRUCTION
	//	using T_::T_;

	//	Reified to allow inspection of initializer-type:
		using initializer_list = _std::initializer_list<U_alpha>;

		template <int N_side=1>
		XTAL_TN0 blank(size_t n)
		XTAL_0EX
		{
			assert(n <= T_::size()); auto const m = T::size() - n;
			XTAL_IF0
			XTAL_0IF_(0 < T_::size()) {
				_std::uninitialized_value_construct_n(T_::data(), m);
			}
			XTAL_0IF_(T_::size() < 0) {
				_std::uninitialized_value_construct_n(_std::next(T_::data(), n), m);
			}
		}

		XTAL_CO0_(homotype)
	//	XTAL_CO1_(homotype)
		XTAL_CO4_(homotype)
		
		XTAL_CON homotype()
		XTAL_0EX
		:	homotype(0)
		{}
		XTAL_CXN homotype(int n)
		XTAL_0EX
		{
			assert(n <= T_::size());
			blank(n);
		}

		using T_::operator >>=;
		using T_::operator <<=;

		XTAL_CON  homotype        (initializer_list      o) XTAL_0EX {blank(o.size()); operator<<=(         (o));}
		XTAL_CXN  homotype        (bounded_q auto const &o) XTAL_0EX {blank(o.size()); operator<<=(         (o));}
		XTAL_CXN  homotype        (bounded_q auto      &&o) XTAL_0EX {blank(o.size()); operator<<=(XTAL_MOV_(o));}
		
		XTAL_OP1_(homotype &) <<= (initializer_list      o) XTAL_0EX {_detail::copy_to(_std::next(T_::data(), T_::size() - o.size()),          (o), V_f); return *this;}
		XTAL_OP1_(homotype &) <<= (bounded_q auto const &o) XTAL_0EX {_detail::copy_to(_std::next(T_::data(), T_::size() - o.size()),          (o), V_f); return *this;}
		XTAL_OP1_(homotype &) <<= (bounded_q auto      &&o) XTAL_0EX {_detail::move_to(_std::next(T_::data(), T_::size() - o.size()), XTAL_MOV_(o), V_f); return *this;}
		
		XTAL_OP1_(homotype &) >>= (initializer_list      o) XTAL_0EX {_detail::copy_to(T_::data(),          (o), V_f); return *this;}
		XTAL_OP1_(homotype &) >>= (bounded_q auto const &o) XTAL_0EX {_detail::copy_to(T_::data(),          (o), V_f); return *this;}
		XTAL_OP1_(homotype &) >>= (bounded_q auto      &&o) XTAL_0EX {_detail::move_to(T_::data(), XTAL_MOV_(o), V_f); return *this;}
		
		XTAL_CXN  homotype      (bounded_q auto      &&o) XTAL_0EX requires _std::integral<devalue_t<decltype(o)>> :        T_(XTAL_REF_(o))  {}
		XTAL_CON  homotype      (U_alpha             &&o) XTAL_0EX                                                 : homotype({XTAL_MOV_(o)}) {}
		XTAL_CON  homotype      (U_alpha        const &o) XTAL_0EX                                                 : homotype({         (o)}) {}



	public:// OPERATION
		using T_::self;
		using T_::twin;

		XTAL_OP2 () ()          XTAL_0FX {return     T_::template transact<W_alpha>(U_f);}
		XTAL_OP2 () (size_t i)  XTAL_0FX {return U_f(T_::get(i));}
		XTAL_TN2   d(size_t i)  XTAL_0FX {return U_f(T_::get(i));}
		
		XTAL_OP0_(implicit) W_alpha() XTAL_0FX {return operator()( );}
		XTAL_OP0_(implicit) U_alpha() XTAL_0FX {return operator()(0);}


		///\
		Scales all elements. \

	//	using T_::operator/=;
	//	using T_::operator*=;

		XTAL_OP1 /= (numeric_q auto const &f)
		XTAL_0EX
		{
			return operator*=(re::alpha_1/f);
		}
		XTAL_OP1 *= (real_number_q auto const &f)
		XTAL_0EX
		{
			auto [m, n] = re::scientific_f((U_alpha) f);

			U_sigma constexpr  N_bias = re::N_width;
			U_sigma constexpr  N_half = re::half.depth - N_bias;// e.g. {64,32} => {32,16}-B
			U_sigma constexpr  M_half = re::half.depth + N_bias;// e.g. {52,23} => {32,16}+B
			U_delta constexpr  M_down = re::fraction.depth - M_half;
			auto const shift = M_down + n;

			auto &s = reinterpret_cast<W_delta &>(self());

			/**/
			auto const up = re::template designed_f<1>(shift);
			auto const dn = up - shift;

			s <<= up;
			s >>= dn;
			/*/
			s >>= -shift;
			/***/
			T_::operator*=(m >> M_down);
			
			return self();
		}
		XTAL_OP1 *= (integral_number_q auto const &i)
		XTAL_0EX
		{
			return T_::operator*=(i);
		}

		///\
		Offsets the first element. \
		
		using T_::operator-=;
		using T_::operator+=;

		XTAL_OP1 -= (numeric_q auto const &f)
		XTAL_0EX
		{
			return operator+=(-f);
		}
		XTAL_OP1 += (real_number_q auto const &f)
		XTAL_0EX
		{
			T_::operator[](0) += re::fractional_f(f);
			return self();
		}
		XTAL_OP1 += (integral_number_q auto const &i)
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

//template <size_t N_datum, algebra::differential::phase_q T> XTAL_FN2 get(T &&t)
//XTAL_0EX {return XTAL_REF_(t) (N_datum);}


}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
