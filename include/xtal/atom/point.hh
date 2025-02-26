#pragma once
#include "./any.hh"
#include "./quanta.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends `quanta` with point-wise operation. \

template <class ...Us>	struct  point;
template <class ...Us>	using   point_t = typename point<Us...>::type;
template <class ...Us>	concept point_q = bond::fixed_tagged_with_p<point_t, Us...>;

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
				(auto    I)                      XTAL_0FN_(to) (f (zot<I>(ts)...))]
				<auto ...I> (bond::seek_t<I...>) XTAL_0FN_(to) (S_::form(f_(constant_t<I>{})...))
					(bond::seek_s<size>{});
		}
		///\
		Evaluates `f` pointwise for each row across `s, ts...`. \

		template <auto f>
		XTAL_DEF_(return,inline,set)
		zip_into(auto &s, auto &&...ts)
		noexcept -> auto
		{
			[f_=[&]
				(auto    I)                      XTAL_0FN_(do) (f (get<I>(s), zot<I>(ts)...))]
				<auto ...I> (bond::seek_t<I...>) XTAL_0FN_(do) (f_(constant_t<I>{}),...)
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
			return ordering_f([&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(to) (disordering_f()|...|disordering_f(get<I>(s) - get<I>(t)))
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

		XTAL_DEF_(return,inline,let) operator - () noexcept -> auto requires requires (value_type u) {-u;}{return zip_with<[] (           auto const &u) XTAL_0FN_(to) (-u)>();}
		XTAL_DEF_(return,inline,let) operator ~ () noexcept -> auto requires requires (value_type u) {~u;}{return zip_with<[] (integral_q auto const &u) XTAL_0FN_(to) (~u)>();}

	//	Scalar operation (performed point-wide):

		XTAL_DEF_(mutate,inline,let)
		operator /= (auto const &o)
		noexcept -> auto &
		requires requires (value_type &u) {u /= o;}
		{
			auto &s = self();
			auto const q = scale_type{1}/o;
			bond::seek_out_f<size>([&]<constant_q I> (I) XTAL_0FN {
				XTAL_IF0
				XTAL_0IF (integral_q<scale_type>) {get<I{}>(s) /= o;}
				XTAL_0IF_(else)                   {get<I{}>(s) *= q;}
			});
			return s;
		}
		XTAL_DEF_(mutate,inline,let)
		operator /  (auto const &o)
		noexcept -> auto
		requires requires (value_type &u) {u /= o;}
		{
			return twin() /= o;
		}

	//	TODO: Restrict scalar-distribution to multiplicative/conjunctive operations?

		XTAL_DEF_(mutate,inline,let) operator +=(auto const &o)                    noexcept -> auto & requires in_n<requires (value_type v) {v += o;}> {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x += y)>(o);}
		XTAL_DEF_(mutate,inline,let) operator -=(auto const &o)                    noexcept -> auto & requires in_n<requires (value_type v) {v -= o;}> {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x -= y)>(o);}
		XTAL_DEF_(mutate,inline,let) operator *=(auto const &o)                    noexcept -> auto & requires in_n<requires (value_type v) {v *= o;}> {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x *= y)>(o);}
	//	XTAL_DEF_(mutate,inline,let) operator /=(auto const &o)                    noexcept -> auto & requires in_n<requires (value_type v) {v /= o;}> {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x /= y)>(o);}
		XTAL_DEF_(mutate,inline,let) operator %=(auto const &o)                    noexcept -> auto & requires in_n<requires (value_type v) {v %= o;}> {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x %= y)>(o);}
		XTAL_DEF_(mutate,inline,let) operator &=(auto const &o)                    noexcept -> auto & requires in_n<requires (value_type v) {v &= o;}> {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x &= y)>(o);}
		XTAL_DEF_(mutate,inline,let) operator |=(auto const &o)                    noexcept -> auto & requires in_n<requires (value_type v) {v |= o;}> {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x |= y)>(o);}
		XTAL_DEF_(mutate,inline,let) operator ^=(auto const &o)                    noexcept -> auto & requires in_n<requires (value_type v) {v ^= o;}> {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x ^= y)>(o);}
		XTAL_DEF_(mutate,inline,let) operator<<=(auto const &o)                    noexcept -> auto & requires in_n<requires (value_type v) {v<<= o;}> {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x<<= y)>(o);}
		XTAL_DEF_(mutate,inline,let) operator>>=(auto const &o)                    noexcept -> auto & requires in_n<requires (value_type v) {v>>= o;}> {return zip_with<[] (auto &x, auto const &y) XTAL_0FN_(do) (x>>= y)>(o);}

		XTAL_DEF_(return,inline,let) operator + (auto const &o)              const noexcept -> auto   requires in_n<requires (value_type v) {v += o;}> {return     twin() += o;}
		XTAL_DEF_(return,inline,let) operator - (auto const &o)              const noexcept -> auto   requires in_n<requires (value_type v) {v -= o;}> {return     twin() -= o;}
		XTAL_DEF_(return,inline,let) operator * (auto const &o)              const noexcept -> auto   requires in_n<requires (value_type v) {v *= o;}> {return     twin() *= o;}
		XTAL_DEF_(return,inline,let) operator / (auto const &o)              const noexcept -> auto   requires in_n<requires (value_type v) {v /= o;}> {return     twin() /= o;}
		XTAL_DEF_(return,inline,let) operator % (auto const &o)              const noexcept -> auto   requires in_n<requires (value_type v) {v %= o;}> {return     twin() %= o;}
		XTAL_DEF_(return,inline,let) operator & (auto const &o)              const noexcept -> auto   requires in_n<requires (value_type v) {v &= o;}> {return     twin() &= o;}
		XTAL_DEF_(return,inline,let) operator | (auto const &o)              const noexcept -> auto   requires in_n<requires (value_type v) {v |= o;}> {return     twin() |= o;}
		XTAL_DEF_(return,inline,let) operator ^ (auto const &o)              const noexcept -> auto   requires in_n<requires (value_type v) {v ^= o;}> {return     twin() ^= o;}
		XTAL_DEF_(return,inline,let) operator<< (auto const &o)              const noexcept -> auto   requires in_n<requires (value_type v) {v<<= o;}> {return     twin()<<= o;}
		XTAL_DEF_(return,inline,let) operator>> (auto const &o)              const noexcept -> auto   requires in_n<requires (value_type v) {v>>= o;}> {return     twin()>>= o;}

	//	Scalar commutation:
		XTAL_DEF_(return,inline,met) operator + (auto const &o, homotype const &s) noexcept -> auto   requires in_n<requires (value_type v) {v += o;}> {return   s.twin() += o;}
	//	XTAL_DEF_(return,inline,met) operator - (auto const &o, homotype const &s) noexcept -> auto   requires in_n<requires (value_type v) {v -= o;}> {return   s.twin() -= o;}
		XTAL_DEF_(return,inline,met) operator * (auto const &o, homotype const &s) noexcept -> auto   requires in_n<requires (value_type v) {v *= o;}> {return   s.twin() *= o;}
	//	XTAL_DEF_(return,inline,met) operator / (auto const &o, homotype const &s) noexcept -> auto   requires in_n<requires (value_type v) {v /= o;}> {return   s.twin() /= o;}
	//	XTAL_DEF_(return,inline,met) operator % (auto const &o, homotype const &s) noexcept -> auto   requires in_n<requires (value_type v) {v %= o;}> {return   s.twin() %= o;}
		XTAL_DEF_(return,inline,met) operator & (auto const &o, homotype const &s) noexcept -> auto   requires in_n<requires (value_type v) {v &= o;}> {return   s.twin() &= o;}
		XTAL_DEF_(return,inline,met) operator | (auto const &o, homotype const &s) noexcept -> auto   requires in_n<requires (value_type v) {v |= o;}> {return   s.twin() |= o;}
		XTAL_DEF_(return,inline,met) operator ^ (auto const &o, homotype const &s) noexcept -> auto   requires in_n<requires (value_type v) {v ^= o;}> {return   s.twin() ^= o;}
	//	XTAL_DEF_(return,inline,met) operator<< (auto const &o, homotype const &s) noexcept -> auto   requires in_n<requires (value_type v) {v<<= o;}> {return   s.twin()<<= o;}
	//	XTAL_DEF_(return,inline,met) operator>> (auto const &o, homotype const &s) noexcept -> auto   requires in_n<requires (value_type v) {v>>= o;}> {return   s.twin()>>= o;}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
