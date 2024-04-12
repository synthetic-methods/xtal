#pragma once
#include "./any.hh"
#include "./sector.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  scalar;
template <class ..._s> using   scalar_t = typename scalar<_s...>::type;
template <class ...Ts> concept scalar_q = bond::tag_p<scalar, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends the `dual` of `sector` with even/odd-reflection iff `N_data == 2`. \

template <class U_data, int N_data>
struct scalar<U_data[N_data]>
{
	using re = bond::realize<U_data>;
	using U_delta = typename re::delta_t;
	using U_sigma = typename re::sigma_t;
	using U_alpha = typename re::alpha_t;
	
	template <class T>
	using demitype = typename sector<U_data[N_data]>::type::dual::template homotype<T>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<scalar>>;

	template <class T>
	class homotype : public hemitype<T>
	{
		friend T;
		using  T_ = hemitype<T>;
	
	public:
		using T_::get;
		using T_::let;
		using T_::self;
		using T_::twin;

	public:// CONSTRUCT
		using T_::T_;

	};
	template <class T> requires (N_data == 2)
	class homotype<T> : public hemitype<T>
	{
		friend T;
		using  T_ = hemitype<T>;
	
	public:
		using T_::get;
		using T_::let;
		using T_::self;
		using T_::twin;

	public:// CONSTRUCT
		using T_::T_;

		///\returns the mutually inverse `lhs +/- rhs`, \
		scaled by the value indexed by `n_bias`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		///\todo\
		Generalize by taking the alternating sum for `N_par == -1`?

		///\
		Modifies `this`; \see `reflected()`.

		XTAL_TN2 reflect(int const n_bias=0)
		XTAL_0FX
		{
			return self() = reflected(n_bias);
		}
		template <int N_par=0>
		XTAL_TN2 reflected(int const n_bias=0)
		XTAL_0FX
		{
			auto const o = re::explo_f(re::template unsquare_f<-1>(2), 1 - n_bias);
			auto const x = o*get(0);
			auto const y = o*get(1);
			if constexpr (N_par ==  0) {
				return T {x + y, x - y};
			}
			if constexpr (N_par == +1) {
				return x + y;
			}
			if constexpr (N_par == -1) {
				return x - y;
			}
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
