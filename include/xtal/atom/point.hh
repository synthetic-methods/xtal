#pragma once
#include "./any.hh"
#include "./quanta.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Extends `quanta` with component-wise operation.
*/

template <class ...Us>	struct  point;
template <class ...Us>	using   point_t = typename point<Us...>::type;
template <class ...Us>	concept point_q = bond::tag_infixed_p<point_t, Us...>;

XTAL_DEF_(let) point_f = [] XTAL_1FN_(call) (_detail::fake_f<point_t>);


////////////////////////////////////////////////////////////////////////////////

template <class U, auto  N, auto  ...Ns> struct   point<U   [N][Ns]...> : point<point_t<U[Ns]...>   [N]> {};
template <class U, auto  N, auto  ...Ns> struct   point<U(&)[N][Ns]...> : point<point_t<U[Ns]...>(&)[N]> {};


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ...Us> requires common_q<Us...>
struct point<Us ...>
:	point<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct point
{
	using _fit = bond::fit<Us...>;

	template <class T>
	using endotype = typename quanta<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<point_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using V_ = typename S_::scale_type;
		using U_ = typename S_::value_type;
		using U0 = typename S_::template tuple_element<0>::type;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		using S_::size;
		using S_::self;
		using S_::twin;

	protected:
		template <size_type I> XTAL_DEF_(return,inline,set) zip_get(auto &&t) noexcept -> decltype(auto) {return           (XTAL_REF_(t));}
		template <size_type I> XTAL_DEF_(return,inline,set) zip_got(auto &&t) noexcept -> decltype(auto) {return zip_get<I>(XTAL_REF_(t));}

		template <size_type I> XTAL_DEF_(return,inline,set) zip_get(block_q auto &&t) noexcept -> decltype(auto) requires XTAL_TRY_(to) (get<I>(XTAL_REF_(t)))
		template <size_type I> XTAL_DEF_(return,inline,set) zip_got(block_q auto &&t) noexcept -> decltype(auto) requires XTAL_TRY_(to) (got<I>(XTAL_REF_(t)))

	public:
		/*!
		\brief  	Determines whether the operation `f` can be applied at the value-level.
		*/
		template <class U, auto f>
		XTAL_DEF_(set) zip_value_q = _std::conditional_t<common_q<Us...>
			,	constant_t<un_n<0, requires (U_ u_, U u) {f(u_, u);}   >>
			,	constant_t<un_n<0, requires (Us u_, U u) {f(u_, u);}...>>
		>{}();

		/*!
		\returns	The pointwise result of applying the vector operation `f`.
		*/
		template <auto f>
		XTAL_DEF_(return,inline,set)
		zip_from(auto const &...ts)
		noexcept -> auto
		{
			return [f_=[&]
				(auto    I)                      XTAL_0FN_(to) (f (zip_got<I>(ts)...))]
				<auto ...I> (bond::seek_t<I...>) XTAL_0FN_(to) (S_::form(f_(constant_t<I>{})...))
					(bond::seek_s<size>{});
		}
		/*!
		\brief  	Evaluates `f` pointwise for each row across `s, ts...`.
		*/
		template <auto f>
		XTAL_DEF_(return,inline,set)
		zip_into(auto &s, auto &&...ts)
		noexcept -> auto
		{
			[f_=[&]
				(auto    I)                      XTAL_0FN_(do) (f (get<I>(s), zip_get<I>(ts)...))]
				<auto ...I> (bond::seek_t<I...>) XTAL_0FN_(do) (f_(constant_t<I>{}),...)
					(bond::seek_s<size>{});
		}
		/*!
		\returns	This after applying the vector operation `f`.
		*/
		template <auto f>
		XTAL_DEF_(mutate,inline,let)
		zip_with(auto const &...ts)
		noexcept -> auto &
		{
			auto &s = self(); zip_into<f>(s, ts...); return s;
		}

		/*!
		\returns	The reduction of `this` w.r.t. the binary operation `f`.
		*/
		template <auto f, int I=size - 1>
		XTAL_DEF_(return,inline,let)
		reduce() const
		{
			XTAL_IF0
			XTAL_0IF (0 == I) {return   get<I>(self())                     ;}
			XTAL_0IF (1 <= I) {return f(get<I>(self()), reduce<f, I - 1>());}
		}

	//	Vector comparison (performed component-wise):

		XTAL_DEF_(return,inline,met)
		operator <=> (homotype const &s, homotype const &t)
		noexcept -> auto
		requires simplex_variable_q<U_>
		{
			return ordering_f([&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(to) (disordering_f()|...|disordering_f(get<I>(s) - get<I>(t)))
			(bond::seek_s<size>{}));
		}

	//	Vector reflection (performed component-wise):

		template <int N_sgn=1>
		XTAL_DEF_(inline,let)
		flip()
		noexcept -> auto &
		{
			XTAL_IF0
			XTAL_0IF (0 <= N_sgn) {
				return self();
			}
			XTAL_0IF (N_sgn <  0) {
				return zip_with<[] (auto &x) XTAL_0FN_(to) (x = -XTAL_MOV_(x))>();
			}
		}
		template <int N_sgn=1>
		XTAL_DEF_(inline,let)
		flipped()
		noexcept -> auto
		{
			return twin().template flip<N_sgn>();
		}

		XTAL_DEF_(return,inline,let) operator - () noexcept -> auto requires requires (U_ u) {-u;}{return zip_with<[] (           auto const &u) XTAL_0FN_(to) (-u)>();}
		XTAL_DEF_(return,inline,let) operator ~ () noexcept -> auto requires requires (U_ u) {~u;}{return zip_with<[] (integral_q auto const &u) XTAL_0FN_(to) (~u)>();}

	//	TODO: Restrict scalar-distribution to multiplicative/conjunctive operations?

	protected:
		/*!
		\internal
		The purpose of the different `operator` implementations is to handle
		`block_coordinated_q`s, which have different `initializer_t`s and `value_type`s.

		It's safer to assign the result of the binary operator via `zip_from` (using `got`/`coelement`),
		than to use apply the assignment directly via `zip_with` (using `get` for both `self()` and the arguments).
		*/
		/**/
		template <class W>
		XTAL_DEF_(mutate,inline,get)
		div1_(W const &w)
		noexcept
		{
			if constexpr (real_q<V_>) {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x *=y)>(V_{one}/w);}
			else                      {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x /=y)>(        w);}
		}
		/***/
		template <class W> XTAL_DEF_(mutate,inline,get)  mul1_(W const &w)       noexcept requires block_coordinated_q<T> {auto &s = self(); s = mul2_(w); return s;}
		template <class W> XTAL_DEF_(mutate,inline,get)  div1_(W const &w)       noexcept requires block_coordinated_q<T> {auto &s = self(); s = div2_(w); return s;}
		template <class W> XTAL_DEF_(mutate,inline,get)  add1_(W const &w)       noexcept requires block_coordinated_q<T> {auto &s = self(); s = add2_(w); return s;}
		template <class W> XTAL_DEF_(mutate,inline,get)  sub1_(W const &w)       noexcept requires block_coordinated_q<T> {auto &s = self(); s = sub2_(w); return s;}
		template <class W> XTAL_DEF_(mutate,inline,get)  mul1_(W const &w)       noexcept {return zip_with<[] (auto       &x, auto const &y) XTAL_0FN_(do) (x *=y)>(w);}
	//	template <class W> XTAL_DEF_(mutate,inline,get)  div1_(W const &w)       noexcept {return zip_with<[] (auto       &x, auto const &y) XTAL_0FN_(do) (x /=y)>(w);}
		template <class W> XTAL_DEF_(mutate,inline,get)  add1_(W const &w)       noexcept {return zip_with<[] (auto       &x, auto const &y) XTAL_0FN_(do) (x +=y)>(w);}
		template <class W> XTAL_DEF_(mutate,inline,get)  sub1_(W const &w)       noexcept {return zip_with<[] (auto       &x, auto const &y) XTAL_0FN_(do) (x -=y)>(w);}
		template <class W> XTAL_DEF_(return,inline,let) _mul2 (W const &w) const noexcept {return zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x * y)>(w, self());}
		template <class W> XTAL_DEF_(return,inline,let) _div2 (W const &w) const noexcept {return zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x / y)>(w, self());}
		template <class W> XTAL_DEF_(return,inline,let) _add2 (W const &w) const noexcept {return zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x + y)>(w, self());}
		template <class W> XTAL_DEF_(return,inline,let) _sub2 (W const &w) const noexcept {return zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x - y)>(w, self());}
		template <class W> XTAL_DEF_(return,inline,let)  mul2_(W const &w) const noexcept {return zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x * y)>(self(), w);}
		template <class W> XTAL_DEF_(return,inline,let)  div2_(W const &w) const noexcept {return zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x / y)>(self(), w);}
		template <class W> XTAL_DEF_(return,inline,let)  add2_(W const &w) const noexcept {return zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x + y)>(self(), w);}
		template <class W> XTAL_DEF_(return,inline,let)  sub2_(W const &w) const noexcept {return zip_from<[] (auto const &x, auto const &y) XTAL_0FN_(to) (x - y)>(self(), w);}

	public:
		template <class U> XTAL_DEF_(return,inline,met) operator * (U const &u, homotype const &s) noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ *= u)>> {return s. mul2_(u);}
		template <class U> XTAL_DEF_(return,inline,met) operator / (U const &u, homotype const &s) noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ /= u)>> {return s._div2 (u);}
		template <class U> XTAL_DEF_(return,inline,met) operator + (U const &u, homotype const &s) noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ += u)>> {return s. add2_(u);}
		template <class U> XTAL_DEF_(return,inline,met) operator - (U const &u, homotype const &s) noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ -= u)>> {return s._sub2 (u);}
		template <class U> XTAL_DEF_(return,inline,let) operator * (U const &u)              const noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ *= u)>> {return    mul2_(u);}
		template <class U> XTAL_DEF_(return,inline,let) operator / (U const &u)              const noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ /= u)>> {return    div2_(u);}
		template <class U> XTAL_DEF_(return,inline,let) operator + (U const &u)              const noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ += u)>> {return    add2_(u);}
		template <class U> XTAL_DEF_(return,inline,let) operator - (U const &u)              const noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ -= u)>> {return    sub2_(u);}
		template <class U> XTAL_DEF_(mutate,inline,get) operator *=(U const &u)                    noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ *= u)>> {return    mul1_(u);}
		template <class U> XTAL_DEF_(mutate,inline,get) operator /=(U const &u)                    noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ /= u)>> {return    div1_(u);}
		template <class U> XTAL_DEF_(mutate,inline,get) operator +=(U const &u)                    noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ += u)>> {return    add1_(u);}
		template <class U> XTAL_DEF_(mutate,inline,get) operator -=(U const &u)                    noexcept requires bond::tab_preference_p<T, U> and in_n<zip_value_q<U, [] (auto &u_, auto const &u) XTAL_0FN_(if) (u_ -= u)>> {return    sub1_(u);}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
