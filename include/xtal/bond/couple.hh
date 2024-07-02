#pragma once
#include "./any.hh"
#include "./tag.hh"
#include "./pack.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Binds multiple values/references, \
providing point-wise multiplication/division and scalar summation. \

template <class   ..._s>	XTAL_TYP couple;
template <class   ..._s>	XTAL_REQ couple_q = bond::any_tag_p<couple, _s...>;
template <class   ..._s>	XTAL_USE couple_t = typename couple<_s...>::type;

template <class V=void, class ...Xs>
XTAL_DEF_(return,inline)
XTAL_LET couple_f(Xs &&...xs)
XTAL_0EX
{
	XTAL_IF0
	XTAL_0IF (complete_q<V>) {
		XTAL_LET f = invoke_f<V>;
		XTAL_USE F = invoke_t<V>;
		if constexpr ((...and idempotent_p<Xs, F>)) {
			return couple_t<_std::invoke_result_t<F, Xs>...>{ (XTAL_REF_(xs))...};
		}
		else {
			return couple_t<_std::invoke_result_t<F, Xs>...>{f(XTAL_REF_(xs))...};
		}
	}
	XTAL_0IF (incomplete_q<V>) {
		return couple_f<decltype([] XTAL_1FN_(objective_f))>(XTAL_REF_(xs)...);
	}
}


////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct couple
{
	XTAL_DEF_(static)
	XTAL_LET N_data = sizeof...(Xs);
	XTAL_USE U_data = devolved_t<Xs...>;

	using archetype = pack_t<Xs...>;
	using supertype = bond::compose_s<archetype, tag<couple>>;

//	using _op = bond::operate<X>;

	class type : public supertype
	{
	public:
		using supertype::supertype;
		
		template <size_type N>
		using tuple_element = _std::tuple_element<N, archetype>;
		using tuple_size    = _std::tuple_size   <   archetype>;

		template <pack_q W> requires (N_data == pack_size_n<W>)
		XTAL_DEF_(return,inline,friend)
		XTAL_LET operator * (type const &s, W const &w)
		XTAL_0EX -> decltype(auto)
		{
			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(couple_f((_std::get<I>(s) * _std::get<I>(w))...))
			(bond::seek_s<N_data>{});
		}
		template <pack_q W> requires (N_data == pack_size_n<W>)
		XTAL_DEF_(return,inline,friend)
		XTAL_LET operator / (type const &s, W const &w)
		XTAL_0EX -> decltype(auto)
		{
			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(couple_f((_std::get<I>(s) / _std::get<I>(w))...))
			(bond::seek_s<N_data>{});
		}

		template <pack_q W> requires (N_data == pack_size_n<W>)
		XTAL_DEF_(inline)
		XTAL_LET operator *= (W const &w)
		XTAL_0EX -> type &
		{
			[&, this]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((_std::get<I>(*this) *= _std::get<I>(w)),...);}
			(bond::seek_s<N_data>{});
			return *this;
		}
		template <pack_q W> requires (N_data == pack_size_n<W>)
		XTAL_DEF_(inline)
		XTAL_LET operator /= (W const &w)
		XTAL_0EX -> type &
		{
			[&, this]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((_std::get<I>(*this) /= _std::get<I>(w)),...);}
			(bond::seek_s<N_data>{});
			return *this;
		}

	//	Scalar sum:
		template <int N_sgn=1>
		XTAL_DEF_(return,inline)
		XTAL_LET sum(auto const &u)
		XTAL_0FX
		{
			if constexpr (0 < N_sgn) {
				return [&, this]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(u +...+ (_std::get<I>(*this)))
				(bond::seek_s<N_data>{});
			}
			else {
				return [&, this]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(u +...+ (_std::get<I>(*this)*U_data{-sign_n<I&1, -1>}))
				(bond::seek_s<N_data>{});
			}
		}
		template <int N_sgn=1>
		XTAL_DEF_(return,inline)
		XTAL_LET sum()
		XTAL_0FX -> decltype(auto)
		{
			return sum<N_sgn>(U_data{0});
		}
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(inline)
		XTAL_LET ratio()
		XTAL_0EX -> U_data
		{
			auto &s = *this;
			
			XTAL_IF0
			XTAL_0IF (0 <= N_par) {return get<0>(s)/get<1>(s);}
			XTAL_0IF (N_par <  0) {return get<1>(s)/get<0>(s);}
		}
		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(return,inline)
		XTAL_LET reflected()
		XTAL_0FX -> decltype(auto)
		{
			auto constexpr o = reflector<N_par>();
			auto const x = o*_std::get<0>(*this);
			auto const y = o*_std::get<1>(*this);
			return couple_f(x + y, x - y);
		}

		///\returns the reflection coefficient indexed by `N_par`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(return,inline,static)
		XTAL_LET reflector()
		XTAL_0EX -> U_data
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
