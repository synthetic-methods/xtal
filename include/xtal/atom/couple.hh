#pragma once
#include "./any.hh"
#include "./group.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends the multiplicative `group` with the scalar sum/product. \
Provides even/odd-reflection iff `N_data == 2`. \

template <class ..._s>	struct   couple;
template <class ..._s>	using    couple_t = typename couple<_s...>::type;
template <class ..._s>	concept  couple_q = bond::array_tag_p<couple_t, _s...> and same_n<sized_n<_s>...>;

template <auto f=null_type{}>
XTAL_DEF_(return,inline,let)
couple_f(auto &&...oo)
noexcept -> auto
{
	return _detail::build<couple_t>::template with<f>(XTAL_REF_(oo)...);
}


////////////////////////////////////////////////////////////////////////////////

template <class ..._s>
struct couple
{
	using A_fix = bond::fixture<_s...>;
	using A_sigma = typename A_fix::sigma_type;
	using A_alpha = typename A_fix::alpha_type;
	using A_aphex = typename A_fix::aphex_type;
	
	template <class T>
	using endotype = typename group<_std::multiplies<void>, _s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<couple_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using I_ = typename S_::initializer_list;
	
	protected:
		using          S_::N_data;
		using typename S_::U_data;
		using typename S_::V_data;
		using typename S_::W_data;

	public:// CONSTRUCT
	//	using S_::S_;
	~	homotype()                 noexcept=default;
	//	homotype()                 noexcept=default;
		XTAL_NEW_(copy) (homotype, noexcept=default)
		XTAL_NEW_(move) (homotype, noexcept=default)

		XTAL_NEW_(explicit) homotype(auto &&...oo)
		noexcept
		:	S_{XTAL_REF_(oo)...}
		{}
		XTAL_NEW_(implicit) homotype()
		noexcept
		requires different_q<_s...>
		:	S_{}
		{
		}
		XTAL_NEW_(implicit) homotype()
		noexcept
		requires   vector_q<_s...>
		{
			auto &s = self();

			if (_std::is_constant_evaluated() or N_data <= A_fix::alignment::value) {
				[&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN {((get<I>(s) = W_data{1}),...);}
				(bond::seek_s<N_data>{});
			}
			else {
				_std::uninitialized_fill_n(S_::data(), S_::size(), W_data{1});
			}
		}
		XTAL_NEW_(implicit) homotype(I_ w)
		noexcept
		requires   vector_q<_s...>
		{
			auto &s = self();
			auto const m = w.size();
			
			_detail::copy_to(S_::begin(), w);

			assert(1 == m or m == N_data);
			if (1 == m) {
				auto const &u = get<0>(s);
				if (_std::is_constant_evaluated() or N_data <= A_fix::alignment::value) {
					[&]<auto ...I> (bond::seek_t<I...>)
						XTAL_0FN {((get<I + 1>(s) = u),...);}
					(bond::seek_s<N_data - 1>{});
				}
				else {
					_std::uninitialized_fill_n(_std::next(S_::data(), m), S_::size() - m, u);
				}
			}
		}

		template <class U> requires real_q<U> or complex_q<U>
		XTAL_NEW_(explicit) homotype(U &&u)
		noexcept
		requires in_n<N_data, 2> and vector_q<_s...> and      same_q<U, W_data>
		:	S_{u, one/(u + A_fix::minilon_f()*(not u))}
		{}
		template <class U> requires real_q<U> or complex_q<U>
		XTAL_NEW_(explicit) homotype(U &&u)
		noexcept
		requires in_n<N_data, 2> and vector_q<_s...> and different_q<U, W_data>
		:	homotype(static_cast<W_data>(XTAL_REF_(u)))
		{}
		template <class U> requires logical_q<U>
		XTAL_NEW_(explicit) homotype(U &&u)
		noexcept
		requires in_n<N_data, 2> and vector_q<_s...> and different_q<U, W_data>
		:	S_{static_cast<W_data>(u), static_cast<W_data>(not u)}
		{}
	//	TODO: Adapt the above with `objective_f`?

	public:// ACCESS
		using S_::self;
		using S_::twin;

	public:// OPERATE

		///\returns the result of `blanked()` before refilling with `N_value=1`. \

		template <auto N_value=1>
		XTAL_DEF_(inline,let)
		blanket()
		noexcept -> bool
		{
			return S_::template blanket<N_value>();
		}

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
			(bond::seek_s<N_data - 1>{});
			
			return t;
		}
		XTAL_DEF_(inline,let)
		operator--() const
		noexcept -> auto
		{
			auto t = S_::twin();

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I + 1>(t) -= get<I>(t)),...);}
			(bond::antiseek_s<N_data - 1>{});
			
			return t;
		}

		XTAL_DEF_(inline,let)
		operator++(int) const
		noexcept -> auto
		requires vector_q<_s...>
		{
			auto t = S_::twin();

			W_data u{};
			W_data v{};
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(((u += get<I>(t)), (get<I>(t) = v), (v = u)),...);}
			(bond::seek_s<N_data>{});
			
			return t;
		}
		XTAL_DEF_(inline,let)
		operator--(int) const
		noexcept -> auto
		requires vector_q<_s...>
		{
			auto t = S_::twin();

			W_data u{};
			W_data v{};
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(((u += get<I>(t)), (get<I>(t) = v), (v = u)),...);}
			(bond::antiseek_s<N_data>{});
			
			return t;
		}

	//	Scalar sum:
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		sum() const
		noexcept -> auto
		{
			return sum<N_sgn>(V_data{0});
		}
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		sum(auto const &u) const
		noexcept -> auto
		{
			auto &s = self();

			if constexpr (0 < N_sgn) {
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(return) (u +...+ (                         get<I>(s)))
				(bond::seek_s<N_data>{});
			}
			else {
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(return) (u +...+ (V_data{-sign_n<I&1, -1>}*get<I>(s)))
				(bond::seek_s<N_data>{});
			}
		}

	//	Scalar product:
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		product() const
		noexcept -> auto
		{
			return product<N_sgn>(V_data{1});
		}
		template <int N_sgn=1>
		XTAL_DEF_(return,inline,let)
		product(auto u) const
		noexcept -> auto
		requires un_n<bond::pack_sized_q<decltype(u), N_data>>
		{
			auto &s = self();
			
			bond::seek_forward_f<N_data>([&] (auto I) XTAL_0FN {
				auto const &v = get<I>(s);
				XTAL_IF0
				XTAL_0IF (0 < N_sgn) {u = _xtd::accumulator(XTAL_MOV_(u),                          v, v);}
				XTAL_0IF (N_sgn < 0) {u = _xtd::accumulator(XTAL_MOV_(u), V_data{-sign_n<I&1, -1>}*v, v);}
			});

			return u;
		}
		template <int N_sgn=1> requires vector_q<_s...>
		XTAL_DEF_(return,inline,let)
		product(auto &&t) const
		noexcept -> auto
		requires in_n<bond::pack_sized_q<decltype(t), N_data>>
		{
			auto &s = self();
			W_data u{};
			
			bond::seek_forward_f<N_data>([&, this] (auto I) XTAL_0FN {
				XTAL_IF0
				XTAL_0IF (0 < N_sgn) {u = _xtd::accumulator(XTAL_MOV_(u),                          get<I>(s), get<I>(t));}
				XTAL_0IF (N_sgn < 0) {u = _xtd::accumulator(XTAL_MOV_(u), V_data{-sign_n<I&1, -1>}*get<I>(s), get<I>(t));}
			});
			
			return u;
		}

		template <int N_par=0> requires (N_data == 2)
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

		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(inline,let)
		reflect()
		noexcept -> T &
		{
			return self() = reflected<N_par>();
		}
		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0> requires (N_data == 2)
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
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(return,inline,set)
		reflector()
		noexcept -> V_data
		{
			V_data constexpr up = one;
			V_data constexpr un = one/_std::numbers::sqrt2_v<V_data>;
			V_data constexpr dn = half;
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

		XTAL_DEF_(return,inline,let)  maximal() const {return S_::template pointless<[] XTAL_0FN_(alias) (_std::lcm)>();}
		XTAL_DEF_(return,inline,let)  minimal() const {return S_::template pointless<[] XTAL_0FN_(alias) (_std::gcd)>();}
		XTAL_DEF_(return,inline,let) extremal() const {return bond::pack_f(minimal(), maximal());}

		template <int N>
		XTAL_DEF_(return,inline,let)
		extremal() const
		noexcept -> auto
		{
			XTAL_IF0
			XTAL_0IF (N == 1) {return S_::template pointless<[] XTAL_0FN_(alias) (_std::lcm)>();}
			XTAL_0IF (N <= 0) {return S_::template pointless<[] XTAL_0FN_(alias) (_std::gcd)>();}
		}


	};
	using type = derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

static_assert(bond::array_tag_p<couple_t, couple_t<int[2]>, int[2]>);
static_assert(couple_q<couple_t<int[2]>>);
static_assert(couple_q<couple_t<int[2]>, int[2]>);

static_assert(complete_q<couple_t<float, double>>);

static_assert(atomic_q<couple_t<float[2]>>);

static_assert(fungible_q<_std::array<float, 2>,
	XTAL_ALL_(XTAL_ANY_(couple_t<float(&)[2]>)*XTAL_ANY_(couple_t<float(&)[2]>))>
);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
