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

template <class   ..._s>	struct   couple;
template <class   ..._s>	using    couple_t = typename couple<_s...>::type;
//\
template <class   ..._s>	concept  couple_q = bond::any_tag_p<couple, _s...>;
template <class T     , class ...Xs>	concept  couple_q = bond::any_tag_p<couple, T> and (0 == sizeof...(Xs) or as_q<T, bond::pack_t<Xs...>>);
template <class V=void, class ...Xs>
XTAL_DEF_(short)
XTAL_LET couple_f(Xs &&...xs)
noexcept -> auto
{
	XTAL_IF0
	XTAL_0IF (complete_q<V>) {
		XTAL_LET f = invoke_f<V>;
		using    F = invoke_t<V>;
		using    T = couple_t<_std::invoke_result_t<F, Xs>...>;
		if constexpr ((...and idempotent_p<Xs, F>)) {
			return T{ (XTAL_REF_(xs))...};
		}
		else {
			return T{f(XTAL_REF_(xs))...};
		}
	}
	XTAL_0IF (incomplete_q<V>) {
		return couple_f<XTAL_FUN_(objective_f)>(XTAL_REF_(xs)...);
	}
}


////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct couple
{
	XTAL_SET N_data = sizeof...(Xs);
//	using    U_data =   common_t<Xs...>;
	using    V_data = devolved_u<Xs...>;

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

		XTAL_TO4_(template <complete_q F>
		XTAL_DEF_(explicit operator) F(), apply<F>())

		template <class F=XTAL_FUN_(bond::pack_f)>
		XTAL_DEF_(short)
		XTAL_LET apply() const
		noexcept -> decltype(auto)
		{
			return apply(invoke_f<F>);
		}
		template <class F>
		XTAL_DEF_(short)
		XTAL_LET apply(F &&f) const
		noexcept -> decltype(auto)
		{
			return _std::apply(XTAL_REF_(f), *this);
		}

		template <auto f>
		XTAL_DEF_(inline)
		XTAL_LET pointwise()
		noexcept -> auto &
		requires requires (archetype &s) {f(get<0>(s));}
		{
			auto &s = *this;

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(f(get<I>(s)),...);}
			(bond::seek_s<N_data>{});
			
			return s;
		}
		template <auto f>
		XTAL_DEF_(inline)
		XTAL_LET pointwise(auto const &t)
		noexcept -> auto &
		requires requires (archetype &s) {f(get<0>(s), get<0>(t));}
		{
			size_type constexpr N = bond::pack_size_n<decltype(t)>;
			static_assert(N <= N_data);

			auto &s = *this;

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(f(get<I>(s), get<I>(t)),...);}
			(bond::seek_s<N>{});
			
			return s;
		}

		template <auto f>
		XTAL_DEF_(short,static)
		XTAL_LET pointwise(auto const &s)
		noexcept -> auto
		requires requires (archetype const &s) {f(get<0>(s));}
		{
			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(couple_f(f(get<I>(s))...))
			(bond::seek_s<N_data>{});
		}
		template <auto f>
		XTAL_DEF_(short,static)
		XTAL_LET pointwise(auto const &s, auto const &t)
		noexcept -> auto
		requires requires (archetype const &s) {f(get<0>(s), get<0>(t));}
		{
			size_type constexpr N = bond::pack_size_n<decltype(t)>;
			static_assert(N <= N_data);
			
			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(couple_f(f(get<I>(s), get<I>(t))...))
			(bond::seek_s<N>{});
		}


		XTAL_DEF_(short,friend)
		XTAL_LET operator * (type const &s, pack_q auto const &t)
		noexcept -> decltype(auto)
		{
			return pointwise<[] (auto const &u, auto const &v) XTAL_0FN_(u * v)>(s, t);
		}
		XTAL_DEF_(short,friend)
		XTAL_LET operator / (type const &s, pack_q auto const &t)
		noexcept -> decltype(auto)
		{
			return pointwise<[] (auto const &u, auto const &v) XTAL_0FN_(u / v)>(s, t);
		}
		XTAL_DEF_(short,friend)
		XTAL_LET operator + (type const &s, pack_q auto const &t)
		noexcept -> decltype(auto)
		{
			return pointwise<[] (auto const &u, auto const &v) XTAL_0FN_(u + v)>(s, t);
		}
		XTAL_DEF_(short,friend)
		XTAL_LET operator - (type const &s, pack_q auto const &t)
		noexcept -> decltype(auto)
		{
			return pointwise<[] (auto const &u, auto const &v) XTAL_0FN_(u - v)>(s, t);
		}

		XTAL_DEF_(inline)
		XTAL_LET operator *= (pack_q auto const &t)
		noexcept -> type &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(x *= y)>(t);
		}
		XTAL_DEF_(inline)
		XTAL_LET operator /= (pack_q auto const &t)
		noexcept -> type &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(x /= y)>(t);
		}
		XTAL_DEF_(inline)
		XTAL_LET operator += (pack_q auto const &t)
		noexcept -> type &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(x += y)>(t);
		}
		XTAL_DEF_(inline)
		XTAL_LET operator -= (pack_q auto const &t)
		noexcept -> type &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(x -= y)>(t);
		}

		XTAL_DEF_(short,friend)
		XTAL_LET operator - (type const &s)
		noexcept -> type
		{
			return pointwise<[] (auto const &x) XTAL_0FN_(-x)>(s);
		}

		template <int N_sgn=1>
		XTAL_DEF_(inline)
		XTAL_LET flip()
		noexcept -> type
		{
			XTAL_IF0
			XTAL_0IF (0 <= N_sgn) {
				return *this;
			}
			XTAL_0IF (N_sgn <  0) {
				return pointwise<[] (auto &x) XTAL_0FN_(x = -x)>();
			}
		}


	//	Scalar sum:
		template <int N_sgn=1>
		XTAL_DEF_(short)
		XTAL_LET sum(auto const &u) const
		{
			if constexpr (0 < N_sgn) {
				return [&, this]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(u +...+ (get<I>(*this)))
				(bond::seek_s<N_data>{});
			}
			else {
				return [&, this]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(u +...+ (get<I>(*this)*V_data{-signum_n<I&1, -1>}))
				(bond::seek_s<N_data>{});
			}
		}
		template <int N_sgn=1>
		XTAL_DEF_(short)
		XTAL_LET sum() const
		noexcept -> decltype(auto)
		{
			return sum<N_sgn>(V_data{0});
		}
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(inline)
		XTAL_LET ratio()
		noexcept -> auto
		{
			auto &s = *this;
			
			XTAL_IF0
			XTAL_0IF (0 <= N_par) {return get<0>(s)/get<1>(s);}
			XTAL_0IF (N_par <  0) {return get<1>(s)/get<0>(s);}
		}
		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(short)
		XTAL_LET reflected() const
		noexcept -> decltype(auto)
		{
			auto constexpr o = reflector<N_par>();
			auto const x = o*get<0>(*this);
			auto const y = o*get<1>(*this);
			return couple_f(x + y, x - y);
		}

		///\returns the reflection coefficient indexed by `N_par`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(short,static)
		XTAL_LET reflector()
		noexcept -> V_data
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
namespace xtal::_entail
{///////////////////////////////////////////////////////////////////////////////

template <xtal::bond::couple_q T>
struct apart<T>
{
	XTAL_DEF_(short,static)
	XTAL_LET size() noexcept -> size_type {return _std::tuple_size_v<T>;};
	using    value_type = _std::tuple_element_t<0, T>;

};


}/////////////////////////////////////////////////////////////////////////////
/***/
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
