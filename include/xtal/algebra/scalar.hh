#pragma once
#include "./any.hh"
#include "./serial.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP scalar;
template <class   ..._s>	XTAL_USE scalar_t = typename scalar<_s...>::type;
template <class   ...Ts>	XTAL_ASK scalar_q = bond::head_tag_p<scalar_t, Ts...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_FN1 scalar_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<scalar_t>::template via<V>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////
///\
Extends the `transverse` of `serial` with even/odd-reflection iff `N_data == 2`. \

template <class A>
struct scalar<A>
{
	using _op = bond::operate<A>;
	using U_delta = typename _op::delta_t;
	using U_sigma = typename _op::sigma_t;
	using U_alpha = typename _op::alpha_t;
	
	template <class T>
	using allotype = typename serial<A>::type::transverse::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<scalar_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
	
	public:// CONSTRUCT
		using T_::T_;

	};
	template <class T> requires (_std::extent_v<A> == 2)
	class homotype<T> : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
	
	protected:
		using          T_::N_data;
		using typename T_::U_data;

	public:
		using T_::get;
		using T_::let;
		using T_::self;
		using T_::twin;

	public:// CONSTRUCT
		using T_::T_;

		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0>
		XTAL_DEF_(return,inline)
		XTAL_TN1 reflected()
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
		XTAL_0EX -> devolved_t<U_data>
		{
			XTAL_IF0
			XTAL_0IF (N_par == -1) {return 0.5000000000000000000000000000000000000L;}
			XTAL_0IF (N_par ==  0) {return 0.7071067811865475244008443621048490393L;}
			XTAL_0IF (N_par == +1) {return 1.0000000000000000000000000000000000000L;}
		}
		///\
		Modifies `this`; \see `reflected()`.

		template <int N_par=0>
		XTAL_DEF_(inline)
		XTAL_TN1 reflect()
		XTAL_0EX
		{
			return self() = reflected<N_par>();
		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(fungible_q<_std::array<float, 2>,
	XTAL_TYP_(XTAL_VAL_(scalar_t<float(&)[2]>)*XTAL_VAL_(scalar_t<float(&)[2]>))>
);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
