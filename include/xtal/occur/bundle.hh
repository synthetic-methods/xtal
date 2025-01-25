#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Ties `Xs...` to unify handling, arithmetic, etc. \

template <class ...Xs> struct   bundle;
template <class ...Xs> using    bundle_t = confined_t<bundle<Xs...>>;
template <class ..._s> concept  bundle_q = bond::tag_p<bundle, _s...>;

template <class V=void, class ...Xs>
XTAL_DEF_(return,inline,let)
bundle_f(Xs &&...xs)
noexcept -> auto
{
	XTAL_IF0
	XTAL_0IF (complete_q<V>) {
		auto constexpr f = invoke_n<V>;
		using          F = invoke_t<V>;
		using          T = bundle_t<return_t<F, Xs>...>;
		if constexpr (automorphism_p<F, Xs...>) {
			return T{  XTAL_REF_(xs) ...};
		}
		else {
			return T{f(XTAL_REF_(xs))...};
		}
	}
	XTAL_0IF (incomplete_q<V>) {
		return bundle_f<decltype([] XTAL_0FN_(alias) (objective_f))>(XTAL_REF_(xs)...);
	}
}


//////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct bundle
{
	using superkind = bond::compose<bond::tag<bundle>
	,	_retail::bundle<Xs...>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;

	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;
		using S_::twin;
		using S_::node;
		using S_::head;
		using S_::arguments;

		XTAL_FX2_(do) (template <size_type ...Ns>
		XTAL_DEF_(return,inline,let)
		argument(),
		noexcept -> decltype(auto)
		{
			return S_::template argument<Ns...>();
		})


	public:// ARITHMETIC

		template <auto f>
		XTAL_DEF_(inline,let)
		pointwise()
		noexcept -> auto &
		requires requires {f(S_::template argument<0>());}
		{
			auto &s_ = arguments();
			auto constexpr N = bond::pack_size_n<decltype(s_)>;

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(f(get<I>(s_)),...);}
			(bond::seek_s<N>{});
			
			return self();
		}
		template <auto f>
		XTAL_DEF_(inline,let)
		pointwise(auto const &t)
		noexcept -> auto &
	//	requires requires {f(S_::template argument<0>(), t);}
	//	requires requires {(f(XTAL_ANY_(Xs), t), ...);}
		requires complete_q<common_t<Xs..., decltype(t)>>
		{
			auto &s_ = arguments();
			auto constexpr N = bond::pack_size_n<decltype(s_)>;

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(f(get<I>(s_), t),...);}
			(bond::seek_s<N>{});
			
			return self();
		}
		template <auto f>
		XTAL_DEF_(inline,let)
		pointwise(bundle_q auto const &t)
		noexcept -> auto &
		requires complete_q<common_t<Xs..., decltype(get<0>(t))>>
	//	requires requires {f(S_::template argument<0>(), get<0>(t));}
		{
			auto       &s_ =   arguments();
			auto const &t_ = t.arguments();
			auto constexpr N = bond::pack_size_n<decltype(s_)>;
			auto constexpr M = bond::pack_size_n<decltype(t_)>;
			static_assert(M <= N);

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(f(get<I>(s_), get<I>(t_)),...);}
			(bond::seek_s<M>{});
			
			return self();
		}

		template <auto f>
		XTAL_DEF_(return,inline,set)
		pointwise(subtype const &s)
		noexcept -> auto
		requires requires {f(get<0>(s));}
		{
			auto &s_ = s.arguments();
			auto constexpr N = bond::pack_size_n<decltype(s_)>;

			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(return) (T_(f(get<I>(s_))...))
			(bond::seek_s<N>{});
		}
		template <auto f>
		XTAL_DEF_(return,inline,set)
		pointwise(subtype const &s, auto const &t)
		noexcept -> auto
		requires complete_q<common_t<Xs..., decltype(t)>>
	//	requires un_n<_retail::bundle_q<decltype(t)>> and requires {(f(XTAL_ANY_(Xs), t), ...);}
		{
			auto &s_ = s.arguments();
			auto constexpr N = bond::pack_size_n<decltype(s_)>;

			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(return) (T_(f(get<I>(s_), t)...))
			(bond::seek_s<N>{});
		}
		template <auto f>
		XTAL_DEF_(return,inline,set)
		pointwise(auto const &t, subtype const &s)
		noexcept -> auto
		requires complete_q<common_t<decltype(t), Xs...>>
	//	requires un_n<_retail::bundle_q<decltype(t)>> and requires {(f(t, XTAL_ANY_(Xs)), ...);}
		{
			auto &s_ = s.arguments();
			auto constexpr N = bond::pack_size_n<decltype(s_)>;

			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(return) (T_(f(t, get<I>(s_))...))
			(bond::seek_s<N>{});
		}
		template <auto f>
		XTAL_DEF_(return,inline,set)
		pointwise(subtype const &s, auto const &t)
		noexcept -> auto
		requires requires {f(get<0>(s), get<0>(t));}
		{
			auto       &s_ = s.arguments();
			auto const &t_ = t.arguments();
			auto constexpr N = bond::pack_size_n<decltype(s_)>;
			auto constexpr M = bond::pack_size_n<decltype(t_)>;
			static_assert(M <= N);
			
			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(return) (T_(f(get<I>(s_), get<I>(t_))...))
			(bond::seek_s<M>{});
		}


		XTAL_DEF_(inline,let)
		operator *= (auto const &t)
		noexcept -> auto &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(return) (x *= y)>(t);
		}
		XTAL_DEF_(inline,let)
		operator /= (auto const &t)
		noexcept -> auto &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(return) (x /= y)>(t);
		}
		XTAL_DEF_(inline,let)
		operator += (auto const &t)
		noexcept -> auto &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(return) (x += y)>(t);
		}
		XTAL_DEF_(inline,let)
		operator -= (auto const &t)
		noexcept -> auto &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(return) (x -= y)>(t);
		}

		XTAL_DEF_(return,inline,friend,let)
		operator * (subtype const &s, auto const &t)
		noexcept -> auto
		{
			return pointwise<[] (auto const &x, auto const &y) XTAL_0FN_(return) (x * y)>(s, t);
		}
		XTAL_DEF_(return,inline,friend,let)
		operator * (auto const &t, subtype const &s)
		noexcept -> auto
		{
			return pointwise<[] (auto const &x, auto const &y) XTAL_0FN_(return) (x * y)>(t, s);
		}
		XTAL_DEF_(return,inline,friend,let)
		operator / (subtype const &s, auto const &t)
		noexcept -> auto
		{
			return pointwise<[] (auto const &x, auto const &y) XTAL_0FN_(return) (x / y)>(s, t);
		}
		XTAL_DEF_(return,inline,friend,let)
		operator + (subtype const &s, auto const &t)
		noexcept -> auto
		{
			return pointwise<[] (auto const &x, auto const &y) XTAL_0FN_(return) (x + y)>(s, t);
		}
		XTAL_DEF_(return,inline,friend,let)
		operator - (subtype const &s, auto const &t)
		noexcept -> auto
		{
			return pointwise<[] (auto const &x, auto const &y) XTAL_0FN_(return) (x - y)>(s, t);
		}

		XTAL_DEF_(return,inline,friend,let)
		operator - (subtype const &s)
		noexcept -> subtype
		{
			return pointwise<[] (auto const &x) XTAL_0FN_(return) (-x)>(s);
		}

		template <int N_sgn=1>
		XTAL_DEF_(inline,let)
		flip()
		noexcept -> subtype
		{
			XTAL_IF0
			XTAL_0IF (0 <= N_sgn) {
				return self();
			}
			XTAL_0IF (N_sgn <  0) {
				return pointwise<[] (auto &x) XTAL_0FN_(return) (x = -XTAL_MOV_(x))>();
			}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
