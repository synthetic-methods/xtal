#pragma once
#include "./any.hh"
#include "./lattice.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	struct   lateral;
template <class   ..._s>	using    lateral_t = typename lateral<_s...>::type;
template <class   ...Ts>	concept  lateral_q = bond::tag_p<lateral_t, Ts...>;
template <class  V=void>
XTAL_DEF_(short)
XTAL_LET lateral_f(auto &&...oo)
noexcept -> auto
{
	return _detail::initialize<lateral_t>::template via<V>(XTAL_REF_(oo)...);
}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `lattice` with point-wise addition, and the scalar sum/product. \
Provides even/odd-reflection iff `N_data == 2`. \

template <vector_q A>
struct lateral<A>
{
	using A_op = bond::operate<A>;
	using A_sigma = typename A_op::sigma_type;
	using A_alpha = typename A_op::alpha_type;
	using A_aphex = typename A_op::aphex_type;
	
	template <class T>
	using endotype = typename lattice<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<lateral_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using  S_ = holotype<T>;
	
	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:// CONSTRUCT
	//	using S_::S_;
	~	homotype()                noexcept=default;
	//	homotype()                noexcept=default;
		XTAL_NEW_(copy, homotype, noexcept=default)
		XTAL_NEW_(move, homotype, noexcept=default)

		XTAL_NEW_(implicit) homotype()
		noexcept
		{
			auto &s = self();

			if (_std::is_constant_evaluated() or N_data <= A_op::alignment::value) {
				[&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN {((get<I>(s) = U_data{1}),...);}
				(bond::seek_s<N_data>{});
			}
			else {
				_std::uninitialized_fill_n(S_::data(), S_::size(), U_data{1});
			}
		}
		XTAL_NEW_(implicit) homotype(_std::initializer_list<U_data> w)
		noexcept
		{
			auto &s = self();
			auto const m = w.size();
			
			_detail::copy_to(S_::begin(), w);

			assert(1 == m or m == N_data);
			if (1 == m) {
				auto const &u = get<0>(s);
				if (_std::is_constant_evaluated() or N_data <= A_op::alignment::value) {
					[&]<auto ...I> (bond::seek_t<I...>)
						XTAL_0FN {((get<I + 1>(s) = u),...);}
					(bond::seek_s<N_data - 1>{});
				}
				else {
					_std::uninitialized_fill_n(_std::next(S_::data(), m), S_::size() - m, u);
				}
			}
		}
		XTAL_NEW_(explicit) homotype(auto &&...oo)
		noexcept
		requires (0 < sizeof...(oo))
		:	S_(XTAL_REF_(oo)...)
		{}

		XTAL_NEW_(explicit) homotype(bool o)
		noexcept
		:	S_{condition_f<U_data>(o), condition_f<U_data>(not o)}
		{}

	public:// ACCESS
		using S_::self;
		using S_::twin;

	public:// OPERATE
		using S_::  zeroed;
		using S_::unzeroed;

		template <int N_value=1>
		XTAL_DEF_(inline)
		XTAL_LET unzero()
		noexcept -> logical_type
		{
			using U_value = dissolve_u<U_data>;
			using V_value = typename bond::operate<U_value>::sigma_type;

			auto constexpr u  =    static_cast<U_value>(N_value);
			auto constexpr v  = _xtd::bit_cast<V_value>(u);
			bool const     z  = zeroed();
			auto const     zu = u* static_cast<U_value>(z);
			auto const    _zv = v&-z;
#if XTAL_ENV_(LLVM)
			if constexpr (false) {
			}
#else
			if constexpr (real_number_q<U_data> or complex_number_q<U_data>) {
				auto &s = dissolve_f(*this);
				bond::seek_forward_f<N_data>([&] (auto I) XTAL_0FN {
					XTAL_IF0
					XTAL_0IF (   real_number_q<U_data>) {return reinterpret_cast<V_value &>(s[I]   ) |= _zv;}
					XTAL_0IF (complex_number_q<U_data>) {return reinterpret_cast<V_value &>(s[I][0]) |= _zv;}
				});
			}
#endif
			else {
				auto const n = static_cast<U_value>(z)*u;
				auto      &s = *this;
				bond::seek_forward_f<N_data>([&] (auto I) XTAL_0FN {
					get<I>(s) += n;
				});
			}
			return z;
		}

		using S_::operator*=;
		using S_::operator/=;
		using S_::operator%=;

		XTAL_DEF_(short)  XTAL_LET operator * (auto const &t)              const noexcept -> auto   {return twin() *=   t ;}
		XTAL_DEF_(short)  XTAL_LET operator / (auto const &t)              const noexcept -> auto   {return twin() /=   t ;}
		XTAL_DEF_(short)  XTAL_LET operator % (auto const &t)              const noexcept -> auto   {return twin() %=   t ;}
		XTAL_DEF_(inline) XTAL_LET operator *=(_std::initializer_list<U_data> t) noexcept -> auto & {return self() *= T(t);}
		XTAL_DEF_(inline) XTAL_LET operator /=(_std::initializer_list<U_data> t) noexcept -> auto & {return self() /= T(t);}
		XTAL_DEF_(inline) XTAL_LET operator %=(_std::initializer_list<U_data> t) noexcept -> auto & {return self() %= T(t);}

	//	Vector multiplication (Hadamard product):
		
		XTAL_DEF_(inline)
		XTAL_LET operator *=(array_q<N_data> auto const &t)
		noexcept -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v)
				XTAL_0FN {u *= v;}>(XTAL_REF_(t));
		}
		XTAL_DEF_(inline)
		XTAL_LET operator /=(array_q<N_data> auto const &t)
		noexcept -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v)
				XTAL_0FN {u /= v;}>(XTAL_REF_(t));
		}
		XTAL_DEF_(inline)
		XTAL_LET operator %=(array_q<N_data> auto const &t)
		noexcept -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v)
				XTAL_0FN {u %= v;}>(XTAL_REF_(t));
		}

		///\
		Produces the progressive sum/difference, \
		starting from zero if post-fixed. \

		///\note\
		Defined only for `const this`. \

		XTAL_DEF_(inline)
		XTAL_LET operator++() const
				{
			//\
			auto t = S_::twin();
			auto t = typename T::taboo::template ectotype<U_data[N_data]>(S_::self());

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I + 1>(t) += get<I>(t)),...);}
			(bond::seek_s<N_data - 1>{});
			
			return t;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator--() const
				{
			//\
			auto t = S_::twin();
			auto t = typename T::taboo::template ectotype<U_data[N_data]>(S_::self());

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I + 1>(t) -= get<I>(t)),...);}
			(bond::antiseek_s<N_data - 1>{});
			
			return t;
		}

		XTAL_DEF_(inline)
		XTAL_LET operator++(int) const
				{
			//\
			auto t = S_::twin();
			auto t = typename T::taboo::template ectotype<U_data[N_data]>(S_::self());

			U_data u{};
			U_data v{};
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(((u += get<I>(t)), (get<I>(t) = v), (v = u)),...);}
			(bond::seek_s<N_data>{});
			
			return t;
		}
		XTAL_DEF_(inline)
		XTAL_LET operator--(int) const
				{
			//\
			auto t = S_::twin();
			auto t = typename T::taboo::template ectotype<U_data[N_data]>(S_::self());

			U_data u{};
			U_data v{};
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(((u += get<I>(t)), (get<I>(t) = v), (v = u)),...);}
			(bond::antiseek_s<N_data>{});
			
			return t;
		}

	//	Scalar sum:
		template <int N_sgn=1>
		XTAL_DEF_(short)
		XTAL_LET sum(U_data const &u={}) const
		noexcept -> U_data
		{
			auto &s = self();

			if constexpr (0 < N_sgn) {
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(u +...+ (get<I>(s)))
				(bond::seek_s<N_data>{});
			}
			else {
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(u +...+ (get<I>(s)*U_data(-signum_n<I&1, -1>)))
				(bond::seek_s<N_data>{});
			}
		}

	//	Scalar product:
		template <int N_sgn=1>
		XTAL_DEF_(short)
		XTAL_LET product(U_data u={}) const
		noexcept -> U_data
		{
			auto &s = self();
			
			if constexpr (0 < N_sgn) {
				bond::seek_forward_f<N_data>([&] (auto I) XTAL_0FN {
					auto const &v = get<I>(s);
					u = _xtd::accumulator(XTAL_MOV_(u), v, v);
				});
			}
			else {
				bond::seek_forward_f<N_data>([&] (auto I) XTAL_0FN {
					auto const &v = get<I>(s);
					u = _xtd::accumulator(XTAL_MOV_(u), v, v*U_data{-signum_n<I&1, -1>});
				});
			}
			return u;
		}
		XTAL_DEF_(short)
		XTAL_LET product(bond::pack_sized_q<N_data> auto &&t) const
		noexcept -> U_data
		{
			auto &s = self();
			
			U_data u{};
			bond::seek_forward_f<N_data>([&, this] (auto I) XTAL_0FN {
				u = _xtd::accumulator(XTAL_MOV_(u), get<I>(s), get<I>(t));
			});
			return u;
		}

		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(inline)
		XTAL_LET ratio()
		noexcept -> U_data
		{
			auto &s = self();
			
			XTAL_IF0
			XTAL_0IF (0 <= N_par) {return get<0>(s)/get<1>(s);}
			XTAL_0IF (N_par <  0) {return get<1>(s)/get<0>(s);}
		}
		///\
		Modifies `this`; \see `reflected()`.

		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(inline)
		XTAL_LET reflect()
		noexcept -> T &
		{
			return self() = reflected<N_par>();
		}
		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(short)
		XTAL_LET reflected() const
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
		XTAL_DEF_(short,static)
		XTAL_LET reflector()
		noexcept -> absolve_u<U_data>
		{
			XTAL_IF0
			XTAL_0IF (N_par == -1) {return 0.5000000000000000000000000000000000000L;}
			XTAL_0IF (N_par ==  0) {return 0.7071067811865475244008443621048490393L;}
			XTAL_0IF (N_par == +1) {return 1.0000000000000000000000000000000000000L;}
		}

		XTAL_DEF_(short) XTAL_LET  maximum() const noexcept -> auto const & {return *_xtd::ranges::max_element(self());}
		XTAL_DEF_(short) XTAL_LET  minimum() const noexcept -> auto const & {return *_xtd::ranges::min_element(self());}
		XTAL_DEF_(short) XTAL_LET extremum() const noexcept -> auto const
		{
			auto const &[min_, max_] = _xtd::ranges::minmax_element(self());
			return _std::tie(*min_, *max_);
		}
		template <int N>
		XTAL_DEF_(short)
		XTAL_LET extremum() const
		noexcept -> U_data
		{
			XTAL_IF0
			XTAL_0IF (0 <  N) {return maximum();}
			XTAL_0IF (N <= 0) {return minimum();}
		}

		XTAL_DEF_(let)  maximal() const {return S_::template pointless<XTAL_FUN_(_std::lcm)>();}
		XTAL_DEF_(let)  minimal() const {return S_::template pointless<XTAL_FUN_(_std::gcd)>();}
		XTAL_DEF_(let) extremal() const {return bond::pack_f(minimal(), maximal());}

		template <int N>
		XTAL_DEF_(short)
		XTAL_LET extremal() const
		noexcept -> U_data
		{
			XTAL_IF0
			XTAL_0IF (N == 1) {return S_::template pointless<XTAL_FUN_(_std::lcm)>();}
			XTAL_0IF (N <= 0) {return S_::template pointless<XTAL_FUN_(_std::gcd)>();}
		}


	};
	using type = bond::isotype<homotype>;

};
static_assert(atomic_q<lateral_t<float[2]>>);

static_assert(fungible_q<_std::array<float, 2>,
	XTAL_ALL_(XTAL_ANY_(lateral_t<float(&)[2]>)*XTAL_ANY_(lateral_t<float(&)[2]>))>
);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
