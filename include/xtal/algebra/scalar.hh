#pragma once
#include "./any.hh"
#include "./quantity.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	struct   scalar;
template <class   ..._s>	using    scalar_t = typename scalar<_s...>::type;
template <class   ...Ts>	concept  scalar_q = bond::any_tag_p<scalar_t, Ts...>;
template <class  V=void>
XTAL_DEF_(short)
XTAL_LET scalar_f(auto &&...oo)
noexcept -> auto
{
	return _detail::initialize<scalar_t>::template via<V>(XTAL_REF_(oo)...);
}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `quantity` with point-wise addition, and the scalar sum/product. \
Provides even/odd-reflection iff `N_data == 2`. \

template <class A>
struct scalar<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using endotype = typename quantity<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<scalar_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using  S_ = holotype<T>;
	
	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:// CONSTRUCT
	//	using S_::S_;

	~	homotype() noexcept=default;
	//	homotype() noexcept=default;

		XTAL_NEW_(copy, homotype, noexcept=default)
		XTAL_NEW_(move, homotype, noexcept=default)

		XTAL_NEW_(implicit) homotype()
		noexcept
		{
			auto &s = self();

			if (_std::is_constant_evaluated() or N_data <= _op::alignment::value) {
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
				if (_std::is_constant_evaluated() or N_data <= _op::alignment::value) {
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
		using S_::let;
		using S_::self;
		using S_::twin;

	public:// OPERATE
		using S_::operator*=;
		using S_::operator/=;
		using S_::operator%=;

		XTAL_DEF_(short) XTAL_LET operator * (auto const &t)              const noexcept -> auto   {return twin() *=   t ;}
		XTAL_DEF_(short) XTAL_LET operator / (auto const &t)              const noexcept -> auto   {return twin() /=   t ;}
		XTAL_DEF_(short) XTAL_LET operator % (auto const &t)              const noexcept -> auto   {return twin() %=   t ;}
		XTAL_DEF_(inline)        XTAL_LET operator *=(_std::initializer_list<U_data> t) noexcept -> auto & {return self() *= T(t);}
		XTAL_DEF_(inline)        XTAL_LET operator /=(_std::initializer_list<U_data> t) noexcept -> auto & {return self() /= T(t);}
		XTAL_DEF_(inline)        XTAL_LET operator %=(_std::initializer_list<U_data> t) noexcept -> auto & {return self() %= T(t);}

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
			auto t = typename T::template tagged_t<U_data[N_data]>(S_::self());

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
			auto t = typename T::template tagged_t<U_data[N_data]>(S_::self());

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
			auto t = typename T::template tagged_t<U_data[N_data]>(S_::self());

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
			auto t = typename T::template tagged_t<U_data[N_data]>(S_::self());

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
					u = _op::accumulate_f(u, v, v);
				});
			}
			else {
				bond::seek_forward_f<N_data>([&] (auto I) XTAL_0FN {
					auto const &v = get<I>(s);
					u = _op::accumulate_f(u, v, v, U_data(-signum_n<I&1, -1>));
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
				u = _op::accumulate_f(u, get<I>(s), get<I>(t));
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
		noexcept -> devolved_u<U_data>
		{
			XTAL_IF0
			XTAL_0IF (N_par == -1) {return 0.5000000000000000000000000000000000000L;}
			XTAL_0IF (N_par ==  0) {return 0.7071067811865475244008443621048490393L;}
			XTAL_0IF (N_par == +1) {return 1.0000000000000000000000000000000000000L;}
		}


		XTAL_DEF_(short)
		XTAL_LET ordering() const
		{
			if constexpr (N_data == 2) {
				auto const &[x, y] = self();
				return x <=> y;
			}
		//	TODO: Provide variadic `ordering`.
		}
		XTAL_DEF_(short)
		XTAL_LET ordered() const
		{
			return S_::twin().order();
		}
		XTAL_DEF_(short)
		XTAL_LET order()
		noexcept -> T &
		{
			if constexpr (N_data == 2) {
				if (_std::strong_ordering::greater == ordering()) {
					reverse();
				}
			}
			else {
				_std::sort(S_::begin(), S_::end());
			}
			return self();
		}

		XTAL_DEF_(short)
		XTAL_LET reversed() const
		{
			return S_::twin().reverse();
		}
		XTAL_DEF_(inline)
		XTAL_LET reverse()
		noexcept -> T &
		{
			if constexpr (N_data == 2) {
				auto &[x, y] = self();
				_std::swap(x, y);
			}
			else {
				_std::reverse(S_::begin(), S_::end());
			}
			return self();
		}

		
		template <size_type N>
		XTAL_DEF_(short)
		XTAL_LET colimited() const
		noexcept -> U_data
		{
			return S_::template apply([] (auto &&...oo)
			XTAL_0FN {
				XTAL_IF0
				XTAL_0IF (N == 1) {return _std::max<U_data>({XTAL_REF_(oo)...});}
				XTAL_0IF (N <= 0) {return _std::min<U_data>({XTAL_REF_(oo)...});}
			});
		}
		XTAL_DEF_(short)
		XTAL_LET colimited() const
		{
			using  U2 = typename T::template tagged_t<U_data[2]>;
			return U2{colimited<0>(), colimited<1>()};
		}

		template <size_type N>
		XTAL_DEF_(short)
		XTAL_LET cofactored() const
		noexcept -> U_data
		{
			XTAL_IF0
			XTAL_0IF (N == 1) {return S_::template pointless<[] XTAL_1FN_(_std::lcm)>();}
			XTAL_0IF (N <= 0) {return S_::template pointless<[] XTAL_1FN_(_std::gcd)>();}
		}
		XTAL_DEF_(short)
		XTAL_LET cofactored() const
		{
			using  U2 = typename T::template tagged_t<U_data[2]>;
			return U2{cofactored<0>(), cofactored<1>()};
		}
		XTAL_DEF_(short)
		XTAL_LET cofactorable() const
		{
			auto t = ordered();
			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(...and (0 == get<I + 1>(t)%get<I>(t)))
			(bond::seek_s<N_data - 1>{});
		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(based_q<scalar_t<float[2]>>);

static_assert(fungible_q<_std::array<float, 2>,
	XTAL_ALL_(XTAL_ANY_(scalar_t<float(&)[2]>)*XTAL_ANY_(scalar_t<float(&)[2]>))>
);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
