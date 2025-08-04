#pragma once
#include "./any.hh"
#include "./brace.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Extends `brace` with component-wise operation.
\note    More an almost-`atom::group` than an algebraic groupoid.
*/

template <class ...Us>	struct  groupoid;
template <class ...Us>	using   groupoid_t = typename groupoid<Us...>::type;
template <class ...Us>	concept groupoid_q = bond::tag_infixed_p<groupoid_t, Us...>;

XTAL_DEF_(let) groupoid_f = [] XTAL_1FN_(call) (_detail::factory<groupoid_t>::make);


////////////////////////////////////////////////////////////////////////////////

template <class U, auto  N, auto  ...Ns> struct   groupoid<U   [N][Ns]...> : groupoid<groupoid_t<U[Ns]...>   [N]> {};
template <class U, auto  N, auto  ...Ns> struct   groupoid<U(&)[N][Ns]...> : groupoid<groupoid_t<U[Ns]...>(&)[N]> {};


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ...Us> requires common_q<Us...>
struct groupoid<Us ...>
:	groupoid<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct groupoid
{
	using _fit = bond::fit<Us...>;
	using sigma_type = typename _fit::sigma_type;
	using delta_type = typename _fit::delta_type;

	template <class T>
	using endotype = typename brace<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<groupoid_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using V_ = typename S_::scale_type;
		using U_ = typename S_::value_type;
		using U0 = typename S_::template tuple_element<0>::type;

	public:// CONSTRUCT
		using S_::S_;

		using typename S_::value_type;
		using typename S_::scale_type;

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
		\returns	The groupoidwise result of applying the vector operation `f`.
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
		\brief  	Evaluates `f` groupoidwise for each row across `s, ts...`.
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


	//	Scalar sum:
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		sum() const
		noexcept -> auto
		{
			return sum<N_sgn>(scale_type{0});
		}
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		sum(auto const &u) const
		noexcept -> auto
		{
			auto &s = self();

			if constexpr (0 < N_sgn) {
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(to) (u +...+ get<I>(s))
				(bond::seek_s<size>{});
			}
			else {
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(to) (u +...+ (scale_type{cosign_v<I>}*get<I>(s)))
				(bond::seek_s<size>{});
			}
		}

	//	Scalar product:
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		product() const
		noexcept -> auto
		{
			return product<N_sgn>(scale_type{0});
		}
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		product(auto u) const
		noexcept -> auto
		requires in_n<requires (value_type v) {v += u;}>
		{
			auto &s = self();
			
			bond::seek_until_f<size>([&]<constant_q I> (I) XTAL_0FN {
				sigma_type constexpr  i{I{}};
				scale_type constexpr _1{cosign_v<i>};
				auto const &v = get<I>(s);
				XTAL_IF0
				XTAL_0IF (0 < N_sgn) {u = _xtd::accumulator(XTAL_MOV_(u),    v, v);}
				XTAL_0IF (N_sgn < 0) {u = _xtd::accumulator(XTAL_MOV_(u), _1*v, v);}
			});

			return u;
		}
		template <int N_sgn=1> requires common_q<Us...>
		XTAL_DEF_(return,inline,let)
		product(auto &&t) const
		noexcept -> auto
		requires un_n<requires (value_type v) {v += t;}> and fixed_shaped_q<decltype(t), S_>
		{
			auto &s = self();
			value_type u{0};
			
			bond::seek_until_f<size>([&, this]<constant_q I> (I) XTAL_0FN {
				sigma_type constexpr  i{I{}};
				scale_type constexpr _1{cosign_v<i>};
				XTAL_IF0
				XTAL_0IF (0 < N_sgn) {u = _xtd::accumulator(XTAL_MOV_(u),    get<i>(s), get<i>(t));}
				XTAL_0IF (N_sgn < 0) {u = _xtd::accumulator(XTAL_MOV_(u), _1*get<i>(s), get<i>(t));}
			});
			
			return u;
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
		`block_revalued_q`s, which have different `initializer_t`s and `value_type`s.

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
		template <class W> XTAL_DEF_(mutate,inline,get)  mul1_(W const &w)       noexcept requires block_revalued_q<T> {auto &s = self(); s = mul2_(w); return s;}
		template <class W> XTAL_DEF_(mutate,inline,get)  div1_(W const &w)       noexcept requires block_revalued_q<T> {auto &s = self(); s = div2_(w); return s;}
		template <class W> XTAL_DEF_(mutate,inline,get)  add1_(W const &w)       noexcept requires block_revalued_q<T> {auto &s = self(); s = add2_(w); return s;}
		template <class W> XTAL_DEF_(mutate,inline,get)  sub1_(W const &w)       noexcept requires block_revalued_q<T> {auto &s = self(); s = sub2_(w); return s;}
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
