#pragma once
#include "./any.hh"
#include "./serial.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_TYP scalar;
template <class ..._s> XTAL_USE scalar_t = typename scalar<_s...>::type;
template <class ...Ts> XTAL_ASK scalar_q = bond::head_tag_p<scalar, Ts...>;

template <auto f, class ...Xs> requires common_q<Xs...>
XTAL_DEF_(return,inline)
XTAL_FN1 scalar_f(Xs &&...xs)
XTAL_0EX
{
	XTAL_USE U = common_t<Xs...>;
	XTAL_SET N = sizeof...(xs);
	if constexpr (idempotent_p<U, decltype(f)>) {
		return scalar_t<U[N]>{ (XTAL_REF_(xs))...};
	}
	else {
		return scalar_t<U[N]>{f(XTAL_REF_(xs))...};
	}
}
template <class ...Xs>
XTAL_DEF_(return,inline)
XTAL_FN1 scalar_f(Xs &&...xs)
XTAL_0EX
{
	return scalar_f<[] XTAL_1FN_(objective_f)>(XTAL_REF_(xs)...);
}


////////////////////////////////////////////////////////////////////////////////
///\
Extends the `transverse` of `serial` with even/odd-reflection iff `N_data == 2`. \

template <class U_data> requires disarray_q<U_data>
struct scalar<U_data> : scalar<U_data[2]>
{};
template <class U_data, int N_data>
struct scalar<U_data[N_data]>
{
	using Op = bond::operate<U_data>;
	using U_delta = typename Op::delta_t;
	using U_sigma = typename Op::sigma_t;
	using U_alpha = typename Op::alpha_t;
	
	template <class T>
	using allotype = typename serial<U_data[N_data]>::type::transverse::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<scalar>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
	
	public:// CONSTRUCT
		using T_::T_;

	};
	template <class T> requires (N_data == 2)
	class homotype<T> : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
	
	public:
		using T_::get;
		using T_::let;
		using T_::self;
		using T_::twin;

	public:// CONSTRUCT
		using T_::T_;

		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0>
		XTAL_TN2 reflected()
		XTAL_0FX
		{
			auto constexpr o = reflector<N_par>();
			auto const     x = o*get(0);
			auto const     y = o*get(1);
			return T {x + y, x - y};
		}
		///\returns the reflection coefficient indexed by `N_par`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		template <int N_par=0>
		XTAL_DEF_(return,inline)
		XTAL_LET reflector()
		XTAL_0EX -> devolve_t<U_data>
		{
			XTAL_IF0
			XTAL_0IF (N_par == -1) {return 0.5000000000000000000000000000000000000L;}
			XTAL_0IF (N_par ==  0) {return 0.7071067811865475244008443621048490393L;}
			XTAL_0IF (N_par == +1) {return 1.0000000000000000000000000000000000000L;}
		}
		///\
		Modifies `this`; \see `reflected()`.

		template <int N_par=0>
		XTAL_TN2 reflect()
		XTAL_0FX
		{
			return self() = reflected<N_par>();
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
