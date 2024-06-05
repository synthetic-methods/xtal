#pragma once
#include "./any.hh"
#include "./tag.hh"
#include "./pack.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class        ..._s> XTAL_TYP couple;
template <class        ..._s> XTAL_ASK couple_q = bond::head_tag_p<couple, _s...>;
template <class X, class Y=X> XTAL_USE couple_t = typename couple<X, Y>::type;

template <class O, class X, class Y>
XTAL_DEF_(return,inline)
XTAL_FN1 couple_f(X &&x, Y &&y)
XTAL_0EX
{
	XTAL_SET f = invoke_f<O>;
	XTAL_USE F = invoke_t<O>;
	if constexpr (idempotent_p<X, F> and idempotent_p<X, F>) {
		using X_ = _std::remove_reference_t<X>;
		using Y_ = _std::remove_reference_t<Y>;
		return couple_t<X_, Y_>(XTAL_REF_(x), XTAL_REF_(y));
	}
	else {
		using X_ = _std::remove_reference_t<_std::invoke_result_t<F, X>>;
		using Y_ = _std::remove_reference_t<_std::invoke_result_t<F, Y>>;
		return couple_t<X_, Y_>(f(XTAL_REF_(x)), f(XTAL_REF_(y)));
	}
}
template <class X, class Y>
XTAL_DEF_(return,inline)
XTAL_FN1 couple_f(X &&x, Y &&y)
XTAL_0EX
{
	return couple_f<decltype([] XTAL_1FN_(objective_f))>(XTAL_REF_(x), XTAL_REF_(y));
}


////////////////////////////////////////////////////////////////////////////////

template <class X, class Y>
struct couple<X, Y>
{
	using supertype = bond::compose_s<_std::pair<X, Y>, tag<couple>>;

//	using Op = bond::operate<X>;

	class type : public supertype
	{
		using supertype::XTAL_0DX;
		using supertype::XTAL_1DX;

	public:
		using supertype::supertype;
		
		using tuple_size = Cardinal_t<2>;
		
		template <size_t N, class _> struct tuple_element_;
		template <          class _> struct tuple_element_<0, _> {using type = X;};
		template <          class _> struct tuple_element_<1, _> {using type = Y;};
		template <size_t N         > using  tuple_element = tuple_element_<N, type>;

		template <size_t N> XTAL_DEF_(return,inline) XTAL_TN1 get() XTAL_0EX_(&&) {if constexpr (N&1) return XTAL_MOV_(XTAL_1DX); else return XTAL_MOV_(XTAL_0DX);}
		template <size_t N> XTAL_DEF_(return,inline) XTAL_TN1 get() XTAL_0FX_(&&) {if constexpr (N&1) return XTAL_MOV_(XTAL_1DX); else return XTAL_MOV_(XTAL_0DX);}
		template <size_t N> XTAL_DEF_(return,inline) XTAL_TN1 get() XTAL_0EX_( &) {if constexpr (N&1) return          (XTAL_1DX); else return          (XTAL_0DX);}
		template <size_t N> XTAL_DEF_(return,inline) XTAL_TN1 get() XTAL_0FX_( &) {if constexpr (N&1) return          (XTAL_1DX); else return          (XTAL_0DX);}

		template <pack_q W> XTAL_DEF_(return,inline) XTAL_OP1 *  (W const &w) XTAL_0FX {using _std::get; return couple_f(XTAL_0DX*get<0>(w), XTAL_1DX*get<1>(w));}
		template <pack_q W> XTAL_DEF_(return,inline) XTAL_OP1 /  (W const &w) XTAL_0FX {using _std::get; return couple_f(XTAL_0DX/get<0>(w), XTAL_1DX/get<1>(w));}

		template <pack_q W> XTAL_DEF_(       inline) XTAL_OP1 *= (W const &w) XTAL_0EX {using _std::get; XTAL_0DX *= get<0>(w); XTAL_1DX *= get<1>(w); return *this;}
		template <pack_q W> XTAL_DEF_(       inline) XTAL_OP1 /= (W const &w) XTAL_0EX {using _std::get; XTAL_0DX /= get<0>(w); XTAL_1DX /= get<1>(w); return *this;}

	//	Scalar sum:
		template <int N_sgn=1>
		XTAL_DEF_(return,inline)
		XTAL_TN1 sum(auto &&o)
		XTAL_0FX
		{
			if constexpr (N_sgn < 0) {
				return XTAL_0DX + XTAL_REF_(o) - XTAL_1DX;
			}
			else {
				return XTAL_0DX + XTAL_REF_(o) + XTAL_1DX;
			}
		}
		template <int N_sgn=1>
		XTAL_DEF_(return,inline)
		XTAL_TN1 sum()
		XTAL_0FX
		{
			if constexpr (N_sgn < 0) {
				return XTAL_0DX - XTAL_1DX;
			}
			else {
				return XTAL_0DX + XTAL_1DX;
			}
		}
		
		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0>
		XTAL_DEF_(return,inline)
		XTAL_TN1 reflected()
		XTAL_0FX
		{
			auto constexpr o = reflector<N_par>();
			auto const     x = o*XTAL_0DX;
			auto const     y = o*XTAL_1DX;
			return couple_f(x + y, x - y);
		}

		///\returns the reflection coefficient indexed by `N_par`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		template <int N_par=0>
		XTAL_DEF_(return,inline)
		XTAL_LET reflector()
		XTAL_0EX -> devolved_t<X, Y>
		{
			XTAL_IF0
			XTAL_0IF (N_par == -1) {return 0.5000000000000000000000000000000000000L;}
			XTAL_0IF (N_par ==  0) {return 0.7071067811865475244008443621048490393L;}
			XTAL_0IF (N_par == +1) {return 1.0000000000000000000000000000000000000L;}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::bond::couple_q T>
struct tuple_size<T> : T::tuple_size {};

template <size_t N, xtal::bond::couple_q T>
struct tuple_element<N, T> : T::template tuple_element<N> {};


}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
