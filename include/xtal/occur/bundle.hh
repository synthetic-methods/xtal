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
XTAL_DEF_(short)
XTAL_LET bundle_f(Xs &&...xs)
noexcept -> auto
{
	XTAL_IF0
	XTAL_0IF (complete_q<V>) {
		XTAL_LET f = invoke_n<V>;
		using    F = invoke_t<V>;
		using    T = bundle_t<return_t<F, Xs>...>;
		if constexpr (automorphism_p<F, Xs...>) {
			return T{  XTAL_REF_(xs) ...};
		}
		else {
			return T{f(XTAL_REF_(xs))...};
		}
	}
	XTAL_0IF (incomplete_q<V>) {
		return bundle_f<decltype(XTAL_FUN_(objective_f))>(XTAL_REF_(xs)...);
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
		using S_::slots;

		XTAL_DO2_(template <size_type ...Ns>
		XTAL_DEF_(short)
		XTAL_LET slot(),
		noexcept -> decltype(auto)
		{
			return S_::template slot<Ns...>();
		})


	public:// ARITHMETIC

		template <auto f>
		XTAL_DEF_(inline)
		XTAL_LET pointwise()
		noexcept -> auto &
		requires requires {f(S_::template slot<0>());}
		{
			auto &s_ = slots();
			XTAL_LET N = bond::pack_size_n<decltype(s_)>;

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(f(get<I>(s_)),...);}
			(bond::seek_s<N>{});
			
			return self();
		}
		template <auto f>
		XTAL_DEF_(inline)
		XTAL_LET pointwise(auto const &t)
		noexcept -> auto &
	//	requires requires {f(S_::template slot<0>(), t);}
	//	requires requires {(f(XTAL_ANY_(Xs), t), ...);}
		requires complete_q<common_t<Xs..., decltype(t)>>
		{
			auto &s_ = slots();
			XTAL_LET N = bond::pack_size_n<decltype(s_)>;

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(f(get<I>(s_), t),...);}
			(bond::seek_s<N>{});
			
			return self();
		}
		template <auto f>
		XTAL_DEF_(inline)
		XTAL_LET pointwise(bundle_q auto const &t)
		noexcept -> auto &
		requires complete_q<common_t<Xs..., decltype(get<0>(t))>>
	//	requires requires {f(S_::template slot<0>(), get<0>(t));}
		{
			auto       &s_ =   slots();
			auto const &t_ = t.slots();
			XTAL_LET N = bond::pack_size_n<decltype(s_)>;
			XTAL_LET M = bond::pack_size_n<decltype(t_)>;
			static_assert(M <= N);

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(f(get<I>(s_), get<I>(t_)),...);}
			(bond::seek_s<M>{});
			
			return self();
		}

		template <auto f>
		XTAL_DEF_(short,static)
		XTAL_LET pointwise(subtype const &s)
		noexcept -> auto
		requires requires {f(get<0>(s));}
		{
			auto &s_ = s.slots();
			XTAL_LET N = bond::pack_size_n<decltype(s_)>;

			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(T_(f(get<I>(s_))...))
			(bond::seek_s<N>{});
		}
		template <auto f>
		XTAL_DEF_(short,static)
		XTAL_LET pointwise(subtype const &s, auto const &t)
		noexcept -> auto
		requires complete_q<common_t<Xs..., decltype(t)>>
	//	requires un_n<_retail::bundle_q<decltype(t)>> and requires {(f(XTAL_ANY_(Xs), t), ...);}
		{
			auto &s_ = s.slots();
			XTAL_LET N = bond::pack_size_n<decltype(s_)>;

			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(T_(f(get<I>(s_), t)...))
			(bond::seek_s<N>{});
		}
		template <auto f>
		XTAL_DEF_(short,static)
		XTAL_LET pointwise(auto const &t, subtype const &s)
		noexcept -> auto
		requires complete_q<common_t<decltype(t), Xs...>>
	//	requires un_n<_retail::bundle_q<decltype(t)>> and requires {(f(t, XTAL_ANY_(Xs)), ...);}
		{
			auto &s_ = s.slots();
			XTAL_LET N = bond::pack_size_n<decltype(s_)>;

			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(T_(f(t, get<I>(s_))...))
			(bond::seek_s<N>{});
		}
		template <auto f>
		XTAL_DEF_(short,static)
		XTAL_LET pointwise(subtype const &s, auto const &t)
		noexcept -> auto
		requires requires {f(get<0>(s), get<0>(t));}
		{
			auto       &s_ = s.slots();
			auto const &t_ = t.slots();
			XTAL_LET N = bond::pack_size_n<decltype(s_)>;
			XTAL_LET M = bond::pack_size_n<decltype(t_)>;
			static_assert(M <= N);
			
			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(T_(f(get<I>(s_), get<I>(t_))...))
			(bond::seek_s<M>{});
		}


		XTAL_DEF_(inline)
		XTAL_LET operator *= (auto const &t)
		noexcept -> auto &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(x *= y)>(t);
		}
		XTAL_DEF_(inline)
		XTAL_LET operator /= (auto const &t)
		noexcept -> auto &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(x /= y)>(t);
		}
		XTAL_DEF_(inline)
		XTAL_LET operator += (auto const &t)
		noexcept -> auto &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(x += y)>(t);
		}
		XTAL_DEF_(inline)
		XTAL_LET operator -= (auto const &t)
		noexcept -> auto &
		{
			return pointwise<[] (auto &x, auto const &y) XTAL_0FN_(x -= y)>(t);
		}

		XTAL_DEF_(short,friend)
		XTAL_LET operator * (subtype const &s, auto const &t)
		noexcept -> auto
		{
			return pointwise<[] (auto const &x, auto const &y) XTAL_0FN_(x * y)>(s, t);
		}
		XTAL_DEF_(short,friend)
		XTAL_LET operator * (auto const &t, subtype const &s)
		noexcept -> auto
		{
			return pointwise<[] (auto const &x, auto const &y) XTAL_0FN_(x * y)>(t, s);
		}
		XTAL_DEF_(short,friend)
		XTAL_LET operator / (subtype const &s, auto const &t)
		noexcept -> auto
		{
			return pointwise<[] (auto const &x, auto const &y) XTAL_0FN_(x / y)>(s, t);
		}
		XTAL_DEF_(short,friend)
		XTAL_LET operator + (subtype const &s, auto const &t)
		noexcept -> auto
		{
			return pointwise<[] (auto const &x, auto const &y) XTAL_0FN_(x + y)>(s, t);
		}
		XTAL_DEF_(short,friend)
		XTAL_LET operator - (subtype const &s, auto const &t)
		noexcept -> auto
		{
			return pointwise<[] (auto const &x, auto const &y) XTAL_0FN_(x - y)>(s, t);
		}

		XTAL_DEF_(short,friend)
		XTAL_LET operator - (subtype const &s)
		noexcept -> subtype
		{
			return pointwise<[] (auto const &x) XTAL_0FN_(-x)>(s);
		}

		template <int N_sgn=1>
		XTAL_DEF_(inline)
		XTAL_LET flip()
		noexcept -> subtype
		{
			XTAL_IF0
			XTAL_0IF (0 <= N_sgn) {
				return self();
			}
			XTAL_0IF (N_sgn <  0) {
				return pointwise<[] (auto &x) XTAL_0FN_(x = -XTAL_MOV_(x))>();
			}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
