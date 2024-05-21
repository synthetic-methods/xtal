#pragma once
#include "./any.hh"

//#include "./realize.hh"
#include "./pack.hh"



XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class        ..._s> XTAL_TYP couple;
template <class        ..._s> XTAL_ASK couple_q = bond::tag_p<couple, _s...>;
template <class X, class Y=X> XTAL_USE couple_t = typename couple<X, Y>::type;

template <template <class> class F=based_t, class X, class Y>
XTAL_FN2 couple_f(X &&x, Y &&y)
XTAL_0EX
{
	return couple_t<F<X>, F<Y>>(XTAL_REF_(x), XTAL_REF_(y));
}


////////////////////////////////////////////////////////////////////////////////

template <class X, class Y>
struct couple<X, Y>
{
	using supertype = bond::compose_s<_std::pair<X, Y>, tag<couple>>;

//	using re = bond::realize<X>;

	class type : public supertype
	{
		using supertype::XTAL_1st;
		using supertype::XTAL_2nd;

	public:
		using supertype::supertype;
		
		using tuple_size = cardinal_t<2>;
		
		template <size_t N, class _> struct tuple_element_;
		template <          class _> struct tuple_element_<0, _> {using type = X;};
		template <          class _> struct tuple_element_<1, _> {using type = Y;};
		template <size_t N         > using  tuple_element = tuple_element_<N, type>;

		template <size_t N> XTAL_TN2 get() XTAL_0EX_(&&) {if constexpr (N&1) return XTAL_MOV_(XTAL_2nd); else return XTAL_MOV_(XTAL_1st);}
		template <size_t N> XTAL_TN2 get() XTAL_0EX_( &) {if constexpr (N&1) return          (XTAL_2nd); else return          (XTAL_1st);}
		template <size_t N> XTAL_TN2 get() XTAL_0FX_(&&) {if constexpr (N&1) return XTAL_MOV_(XTAL_2nd); else return XTAL_MOV_(XTAL_1st);}
		template <size_t N> XTAL_TN2 get() XTAL_0FX_( &) {if constexpr (N&1) return          (XTAL_2nd); else return          (XTAL_1st);}

		template <pack_q W> XTAL_OP2 * (W const &w) XTAL_0FX {using _std::get; return couple_f(XTAL_1st*get<0>(w), XTAL_2nd*get<1>(w));}
		template <pack_q W> XTAL_OP2 / (W const &w) XTAL_0FX {using _std::get; return couple_f(XTAL_1st/get<0>(w), XTAL_2nd/get<1>(w));}

	//	Scalar sum:
		template <int N_sgn=1>
		XTAL_TN2 sum()
		XTAL_0FX
		{
			if constexpr (N_sgn < 0) {
				return XTAL_1st - XTAL_2nd;
			}
			else {
				return XTAL_1st + XTAL_2nd;
			}
		}
		
		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0>
		XTAL_TN2 reflected()
		XTAL_0FX
		{
			auto constexpr o = reflector<N_par>();
			auto const     x = o*XTAL_1st;
			auto const     y = o*XTAL_2nd;
			return couple_f(x + y, x - y);
		}

		///\returns the reflection coefficient indexed by `N_par`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		template <int N_par=0>
		XTAL_DEF_(return,inline)
		XTAL_LET reflector()
		XTAL_0EX -> devolve_t<X, Y>
		{
			XTAL_IF0
			XTAL_0IF_(N_par == -1) {return 0.5000000000000000000000000000000000000L;}
			XTAL_0IF_(N_par ==  0) {return 0.7071067811865475244008443621048490393L;}
			XTAL_0IF_(N_par == +1) {return 1.0000000000000000000000000000000000000L;}
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
