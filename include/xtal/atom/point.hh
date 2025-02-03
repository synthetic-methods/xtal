#pragma once
#include "./any.hh"
#include "./quanta.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends `quanta` with point-wise operation. \

template <        class ..._s>	struct   point;
template <        class ..._s>	using    point_t = typename point<_s...>::type;
template <        class ..._s>	concept  point_q = bond::array_tag_p<point_t, _s...> and fixed_shaped_q<_s...>;

template <class U, auto  N, auto  ..._s> struct   point<U   [N][_s]...> : point<point_t<U[_s]...>   [N]> {};
template <class U, auto  N, auto  ..._s> struct   point<U(&)[N][_s]...> : point<point_t<U[_s]...>(&)[N]> {};


XTAL_FX0_(alias) (template <auto f=_std::identity{}>
XTAL_DEF_(return,inline,let)
point_f(auto &&...oo),
	_detail::factory<point_t>::
		template make<f>(XTAL_REF_(oo)...))


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ..._s> requires same_q<_s...>
struct point<_s ...>
:	point<common_t<_s...>[sizeof...(_s)]>
{
};
template <class ..._s>
struct point
{
	using _fix = bond::fixture<_s...>;

	template <class T>
	using endotype = typename quanta<_s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<point_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

	public:// CONSTRUCT
		using S_::S_;

		using typename S_::value_type;
		using typename S_::scale_type;

	protected:
		template <size_type I>
		XTAL_DEF_(return,inline,set)
		zot(auto &&t)
		noexcept -> decltype(auto)
		{
			XTAL_IF0
		//	XTAL_0IF (        same_q<T, decltype(t)>) {return get<I>(XTAL_REF_(t));}
			XTAL_0IF (fixed_shaped_q<T, decltype(t)>) {return got<I>(XTAL_REF_(t));}
			XTAL_0IF_(else)                           {return        XTAL_REF_(t) ;}
		}

	public:// OPERATE
		using S_::size;
		using S_::self;
		using S_::twin;

		///\returns the pointwise result of applying the vector operation `f`. \

		template <auto f>
		XTAL_DEF_(return,inline,set)
		zip_from(auto const &...ts)
		noexcept -> auto
		{
			return [f_=[&]
				(auto    I)                      XTAL_0FN_(return) (f (zot<I>(ts)...))]
				<auto ...I> (bond::seek_t<I...>) XTAL_0FN_(return) (S_::form(f_(constant_t<I>{})...))
					(bond::seek_s<size>{});
		}
		///\
		Evaluates `f` pointwise for each row across `s, ts...`. \

		template <auto f>
		XTAL_DEF_(return,inline,set)
		zip_into(T &s, auto &&...ts)
		noexcept -> auto
		{
			[f_=[&]
				(auto    I)                      XTAL_0FN_(void) (f (get<I>(s), zot<I>(ts)...))]
				<auto ...I> (bond::seek_t<I...>) XTAL_0FN_(void) (f_(constant_t<I>{}),...)
					(bond::seek_s<size>{});
		}
		///\returns `self()`, after applying the vector operation `f`. \

		template <auto f>
		XTAL_DEF_(mutate,inline,let)
		zip_with(auto const &...ts)
		noexcept -> auto &
		{
			auto &s = self(); zip_into<f>(s, ts...); return s;
		}

		///\returns the reduction of `this` w.r.t. the binary operation `f`. \

		template <auto f, int I=size - 1>
		XTAL_DEF_(return,inline,let)
		reduce() const
		{
			XTAL_IF0
			XTAL_0IF (0 == I) {return   get<I>(self())                     ;}
			XTAL_0IF (1 <= I) {return f(get<I>(self()), reduce<f, I - 1>());}
		}

	//	Vector comparison (performed point-wise):

		XTAL_DEF_(return,inline,met)
		operator <=> (homotype const &s, homotype const &t)
		noexcept -> auto
		requires simplex_variable_q<value_type>
		{
			return _fix::sentry_f([&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(return) (_fix::sigma_0|...|_fix::sentinel_f(get<I>(s) - get<I>(t)))
			(bond::seek_s<size>{}));
		}

	//	Vector reflection (performed point-wise):

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
				return zip_with<[] (auto &x) XTAL_0FN_(return) (x = -XTAL_MOV_(x))>();
			}
		}
		template <int N_sgn=1>
		XTAL_DEF_(inline,let)
		flipped()
		noexcept -> auto
		{
			return twin().template flip<N_sgn>();
		}

		XTAL_DEF_(return,inline,let) operator - () noexcept -> auto requires requires (value_type u) {-u;}{return zip_with<[] (           auto const &u) XTAL_0FN_(return) (-u)>();}
		XTAL_DEF_(return,inline,let) operator ~ () noexcept -> auto requires requires (value_type u) {~u;}{return zip_with<[] (integral_q auto const &u) XTAL_0FN_(return) (~u)>();}

	//	Scalar assignment (performed point-wide):

		XTAL_DEF_(inline,let)
		operator /= (auto const &u)
		noexcept -> T &
		requires requires (value_type &w) {w /= u;}
		{
			auto &s = self();
			bond::seek_forward_f<size>([&] (auto I) XTAL_0FN {
				XTAL_IF0
				XTAL_0IF (integral_q<scale_type>) {get<I>(s) /=               u;}
				XTAL_0IF_(else)                   {get<I>(s) *= scale_type{1}/u;}
			});
			return s;
		}
		XTAL_DEF_(mutate,inline,let) operator +=(auto const &o)                    noexcept -> auto & requires requires (value_type u) {u +=o;} {return zip_with<[] (auto &u, auto const &v) XTAL_0FN {u +=v;}>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator -=(auto const &o)                    noexcept -> auto & requires requires (value_type u) {u -=o;} {return zip_with<[] (auto &u, auto const &v) XTAL_0FN {u -=v;}>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator *=(auto const &o)                    noexcept -> auto & requires requires (value_type u) {u *=o;} {return zip_with<[] (auto &u, auto const &v) XTAL_0FN {u *=v;}>(XTAL_REF_(o));}
	//	XTAL_DEF_(mutate,inline,let) operator /=(auto const &o)                    noexcept -> auto & requires requires (value_type u) {u /=o;} {return zip_with<[] (auto &u, auto const &v) XTAL_0FN {u /=v;}>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator %=(auto const &o)                    noexcept -> auto & requires requires (value_type u) {u %=o;} {return zip_with<[] (auto &u, auto const &v) XTAL_0FN {u %=v;}>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator &=(auto const &o)                    noexcept -> auto & requires requires (value_type u) {u &=o;} {return zip_with<[] (auto &u, auto const &v) XTAL_0FN {u &=v;}>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator |=(auto const &o)                    noexcept -> auto & requires requires (value_type u) {u |=o;} {return zip_with<[] (auto &u, auto const &v) XTAL_0FN {u |=v;}>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator ^=(auto const &o)                    noexcept -> auto & requires requires (value_type u) {u ^=o;} {return zip_with<[] (auto &u, auto const &v) XTAL_0FN {u ^=v;}>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator<<=(auto const &o)                    noexcept -> auto & requires requires (value_type u) {u<<=o;} {return zip_with<[] (auto &u, auto const &v) XTAL_0FN {u<<=v;}>(XTAL_REF_(o));}
		XTAL_DEF_(mutate,inline,let) operator>>=(auto const &o)                    noexcept -> auto & requires requires (value_type u) {u>>=o;} {return zip_with<[] (auto &u, auto const &v) XTAL_0FN {u>>=v;}>(XTAL_REF_(o));}

	//	Scalar commutation:
		XTAL_DEF_(return,inline,met) operator + (auto const &o, homotype const &t) noexcept -> auto   requires un_n<point_q<decltype(o)>> and XTAL_TRY_(return) (t.self() + o)
	//	XTAL_DEF_(return,inline,met) operator - (auto const &o, homotype const &t) noexcept -> auto   requires un_n<point_q<decltype(o)>> and XTAL_TRY_(return) (t.self() - o)
		XTAL_DEF_(return,inline,met) operator * (auto const &o, homotype const &t) noexcept -> auto   requires un_n<point_q<decltype(o)>> and XTAL_TRY_(return) (t.self() * o)
	//	XTAL_DEF_(return,inline,met) operator / (auto const &o, homotype const &t) noexcept -> auto   requires un_n<point_q<decltype(o)>> and XTAL_TRY_(return) (t.self() / o)
	//	XTAL_DEF_(return,inline,met) operator % (auto const &o, homotype const &t) noexcept -> auto   requires un_n<point_q<decltype(o)>> and XTAL_TRY_(return) (t.self() % o)
		XTAL_DEF_(return,inline,met) operator & (auto const &o, homotype const &t) noexcept -> auto   requires un_n<point_q<decltype(o)>> and XTAL_TRY_(return) (t.self() & o)
		XTAL_DEF_(return,inline,met) operator | (auto const &o, homotype const &t) noexcept -> auto   requires un_n<point_q<decltype(o)>> and XTAL_TRY_(return) (t.self() | o)
		XTAL_DEF_(return,inline,met) operator ^ (auto const &o, homotype const &t) noexcept -> auto   requires un_n<point_q<decltype(o)>> and XTAL_TRY_(return) (t.self() ^ o)

	//	Vector reassignment:
		XTAL_DEF_(return,inline,let) operator + (auto const &o)              const noexcept -> auto   requires XTAL_TRY_(return) (twin() += o)
		XTAL_DEF_(return,inline,let) operator - (auto const &o)              const noexcept -> auto   requires XTAL_TRY_(return) (twin() -= o)
		XTAL_DEF_(return,inline,let) operator * (auto const &o)              const noexcept -> auto   requires XTAL_TRY_(return) (twin() *= o)
		XTAL_DEF_(return,inline,let) operator / (auto const &o)              const noexcept -> auto   requires XTAL_TRY_(return) (twin() /= o)
		XTAL_DEF_(return,inline,let) operator % (auto const &o)              const noexcept -> auto   requires XTAL_TRY_(return) (twin() %= o)
		XTAL_DEF_(return,inline,let) operator & (auto const &o)              const noexcept -> auto   requires XTAL_TRY_(return) (twin() &= o)
		XTAL_DEF_(return,inline,let) operator | (auto const &o)              const noexcept -> auto   requires XTAL_TRY_(return) (twin() |= o)
		XTAL_DEF_(return,inline,let) operator ^ (auto const &o)              const noexcept -> auto   requires XTAL_TRY_(return) (twin() ^= o)

	};
	using type = derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
