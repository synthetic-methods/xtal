#pragma once
#include "./any.hh"
#include "./group.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends the multiplicative `group` with the scalar sum/product. \
Provides even/odd-reflection iff `size() == 2`. \

template <class ..._s>	struct   couple;
template <class ..._s>	using    couple_t = typename couple<_s...>::type;
template <class ..._s>	concept  couple_q = bond::array_tag_p<couple_t, _s...> and fixed_shaped_q<_s...>;


XTAL_FX0_(to) (template <auto f=_std::identity{}>
XTAL_DEF_(return,inline,let)
couple_f(auto &&...oo),
	_detail::factory<couple_t>::
		template make<f>(XTAL_REF_(oo)...))


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ..._s> requires same_q<_s...>
struct couple<_s ...>
:	couple<common_t<_s...>[sizeof...(_s)]>
{
};
template <class ..._s>
struct couple
{
	using A_fit = bond::fit<_s...>;
	using A_sigma = typename A_fit::sigma_type;
	using A_alpha = typename A_fit::alpha_type;
	using A_aphex = typename A_fit::aphex_type;
	
	template <class T>
	using endotype = typename multiplicative_group<_s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<couple_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
	
	public:// ACCESS
		using S_::size;
		using S_::self;
		using S_::twin;

		using typename S_::value_type;
		using typename S_::scale_type;

	public:// CONSTRUCT
		using S_::S_;//NOTE: Inherited and respecialized!

		XTAL_NEW_(explicit)
		homotype(bool u)
		noexcept
		requires in_n<size, 2>
		:	S_{static_cast<value_type>(u), static_cast<value_type>(not u)}
		{
		}
		XTAL_NEW_(explicit)
		homotype(value_type const &u)
		noexcept
		requires in_n<size, 2> and continuous_field_q<value_type>
		:	S_{u, one/u}
		{
			assert(u != value_type{0});
		}
		XTAL_NEW_(explicit)
		homotype(subjective_q auto const &u)
		noexcept
		requires in_n<size, 2> and continuous_field_q<value_type>
		:	homotype(objective_f(u))
		{
		}

	public:// OPERATE

		///\
		Produces the progressive sum/difference, \
		starting from zero if post-fixed. \

		///\note\
		Defined only for `const this`, \
		because this is whack (but fun). \

		XTAL_DEF_(inline,let)
		operator++() const
		noexcept -> auto
		{
			auto t = S_::twin();

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I + 1>(t) += get<I>(t)),...);}
			(bond::seek_s<size - 1>{});
			
			return t;
		}
		XTAL_DEF_(inline,let)
		operator--() const
		noexcept -> auto
		{
			auto t = S_::twin();

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I + 1>(t) -= get<I>(t)),...);}
			(bond::antiseek_s<size - 1>{});
			
			return t;
		}

		XTAL_DEF_(inline,let)
		operator++(int) const
		noexcept -> auto
		requires same_q<_s...>
		{
			auto t = S_::twin();

			value_type u{};
			value_type v{};
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(((u += get<I>(t)), (get<I>(t) = v), (v = u)),...);}
			(bond::seek_s<size>{});
			
			return t;
		}
		XTAL_DEF_(inline,let)
		operator--(int) const
		noexcept -> auto
		requires same_q<_s...>
		{
			auto t = S_::twin();

			value_type u{};
			value_type v{};
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(((u += get<I>(t)), (get<I>(t) = v), (v = u)),...);}
			(bond::antiseek_s<size>{});
			
			return t;
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
					XTAL_0FN_(to) (u +...+ (                             get<I>(s)))
				(bond::seek_s<size>{});
			}
			else {
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(to) (u +...+ (scale_type{-sign_v<I&1, -1>}*get<I>(s)))
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
		requires un_n<fixed_shaped_q<decltype(u), T>>
		{
			auto &s = self();
			
			bond::seek_forward_f<size>([&] (auto I) XTAL_0FN {
				auto const &v = get<I>(s);
				XTAL_IF0
				XTAL_0IF (0 < N_sgn) {u = _xtd::plus_multiplies(XTAL_MOV_(u),                              v, v);}
				XTAL_0IF (N_sgn < 0) {u = _xtd::plus_multiplies(XTAL_MOV_(u), scale_type{-sign_v<I&1, -1>}*v, v);}
			});

			return u;
		}
		template <int N_sgn=1> requires same_q<_s...>
		XTAL_DEF_(return,inline,let)
		product(auto &&t) const
		noexcept -> auto
		requires in_n<fixed_shaped_q<decltype(t), T>>
		{
			auto &s = self();
			value_type u{0};
			
			bond::seek_forward_f<size>([&, this] (auto I) XTAL_0FN {
				XTAL_IF0
				XTAL_0IF (0 < N_sgn) {u = _xtd::plus_multiplies(XTAL_MOV_(u),                              get<I>(s), get<I>(t));}
				XTAL_0IF (N_sgn < 0) {u = _xtd::plus_multiplies(XTAL_MOV_(u), scale_type{-sign_v<I&1, -1>}*get<I>(s), get<I>(t));}
			});
			
			return u;
		}

		template <int N_par=0> requires (size == 2)
		XTAL_DEF_(inline,let)
		ratio()
		noexcept -> auto
		{
			auto &s = self();
			
			XTAL_IF0
			XTAL_0IF (0 <= N_par) {return get<0>(s)/get<1>(s);}
			XTAL_0IF (N_par <  0) {return get<1>(s)/get<0>(s);}
		}
		///\
		Modifies `this`; \see `reflected()`.

		template <int N_par=0> requires (size == 2)
		XTAL_DEF_(inline,let)
		reflect()
		noexcept -> T &
		{
			return self() = reflected<N_par>();
		}
		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0> requires (size == 2)
		XTAL_DEF_(return,inline,let)
		reflected() const
		noexcept -> decltype(auto)
		{
			auto &s = self();

			auto constexpr o = reflector<N_par>();
			auto const     x = o*get<0>(s);
			auto const     y = o*get<1>(s);
			return decltype(twin()) {x + y, x - y};
		}
		///\returns the reflection coefficient indexed by `N_par`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		template <int N_par=0> requires (size() == 2)
		XTAL_DEF_(return,inline,set)
		reflector()
		noexcept -> auto
		{
			scale_type constexpr up = one;
			scale_type constexpr un = one/_std::numbers::sqrt2_v<scale_type>;
			scale_type constexpr dn = half;
			XTAL_IF0
			XTAL_0IF (N_par == +1) {return up;}
			XTAL_0IF (N_par ==  0) {return un;}
			XTAL_0IF (N_par == -1) {return dn;}
		}

		XTAL_DEF_(return,inline,let)  maximum() const noexcept -> auto const & {return *_xtd::ranges::max_element(self());}
		XTAL_DEF_(return,inline,let)  minimum() const noexcept -> auto const & {return *_xtd::ranges::min_element(self());}
		XTAL_DEF_(return,inline,let) extremum() const noexcept -> auto const
		{
			auto const &[min_, max_] = _xtd::ranges::minmax_element(self());
			return _std::tie(*min_, *max_);
		}
		template <int N>
		XTAL_DEF_(return,inline,let)
		extremum() const
		noexcept -> auto
		{
			XTAL_IF0
			XTAL_0IF (0 <  N) {return maximum();}
			XTAL_0IF (N <= 0) {return minimum();}
		}

		XTAL_DEF_(return,inline,let)  maximal() const {return S_::template reduce<[] XTAL_1FN_(function) (_std::lcm)>();}
		XTAL_DEF_(return,inline,let)  minimal() const {return S_::template reduce<[] XTAL_1FN_(function) (_std::gcd)>();}
		XTAL_DEF_(return,inline,let) extremal() const {return bond::pack_f(minimal(), maximal());}

		template <int N>
		XTAL_DEF_(return,inline,let)
		extremal() const
		noexcept -> auto
		{
			XTAL_IF0
			XTAL_0IF (N == 1) {return S_::template reduce<[] XTAL_1FN_(function) (_std::lcm)>();}
			XTAL_0IF (N <= 0) {return S_::template reduce<[] XTAL_1FN_(function) (_std::gcd)>();}
		}


	};
	using type = derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
