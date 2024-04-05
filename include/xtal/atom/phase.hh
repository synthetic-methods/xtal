#pragma once
#include "./any.hh"
#include "./serial.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_NEW phase;
template <class ..._s> XTAL_USE phase_t = typename phase<_s...>::type;
template <class ...Ts> XTAL_ASK phase_q = bond::tag_p<phase, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `serial` as a fixed-point fractional/cyclic value. \
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

template <class A, size_t N>
struct phase<A[N]>
{
	using re = bond::realize<A>;
	using U_delta = typename re::delta_t;
	using U_sigma = typename re::sigma_t;
	using U_alpha = typename re::alpha_t;
	
	using W_delta = serial_t<U_delta[N]>;
	using W_sigma = serial_t<U_sigma[N]>;
	using W_alpha = serial_t<U_alpha[N]>;

	XTAL_LET V_f = [] (U_alpha const &u) XTAL_0FN_(_std::bit_cast<U_sigma>(U_delta(u*re::diplo_f(re::N_depth))));
	XTAL_LET U_f = [] (U_sigma const &v) XTAL_0FN_(U_alpha(_std::bit_cast<U_delta>(v))*re::haplo_f(re::N_depth));

	static_assert(_std::numeric_limits<U_sigma>::is_modulo);// D'oh!

	template <class T>
	using demitype = typename serial<U_sigma[N]>::template homotype<T>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<phase>>;

	template <class T>
	class homotype : public hemitype<T>
	{
		friend T;
		using  T_ = hemitype<T>;


	public:// CONSTRUCTION

		~homotype() {};
		XTAL_CO4_(homotype)
		
		XTAL_CON homotype()
		XTAL_0EX
		:	T_()
		{}

	//	Reified to allow inspection of initializer-type:
		using initializer_list = _std::initializer_list<U_alpha>;

		XTAL_CON homotype(initializer_list      o) XTAL_0EX: T_(o.size()) {_detail::copy_to(T_::data(), o, V_f);}
		XTAL_CXN homotype(bounded_q auto const &o) XTAL_0EX: T_(o.size()) {_detail::copy_to(T_::data(), o, V_f);}
		XTAL_CXN homotype(bounded_q auto      &&o) XTAL_0EX: T_(o.size()) {_detail::move_to(T_::data(), XTAL_MOV_(o), V_f);}
		XTAL_CXN homotype(bounded_q auto      &&o) XTAL_0EX requires _std::integral<value_t<decltype(o)>> : T_(XTAL_REF_(o)) {}


	public:// OPERATION
		using T_::self;
		using T_::twin;

		XTAL_OP2 () ()          XTAL_0FX {return     T_::template transmorph<W_alpha>(U_f);}
		XTAL_OP2 () (size_t i)  XTAL_0FX {return U_f(T_::operator[](i));}
		XTAL_TN2   d(size_t i)  XTAL_0FX {return U_f(T_::operator[](i));}
		
		XTAL_OP0_(implicit) W_alpha() XTAL_0FX {return operator()( );}
		XTAL_OP0_(implicit) U_alpha() XTAL_0FX {return operator()(0);}


		///\
		Scales all elements of the `phase`. \

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
		Offsets the first element of the `phase`. \
		
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
XTAL_ENV_(pop)
