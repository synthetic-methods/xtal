#pragma once
#include "./any.hh"
#include "./lattice.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP scalar;
template <class   ..._s>	XTAL_USE scalar_t = typename scalar<_s...>::type;
template <class   ...Ts>	XTAL_REQ scalar_q = bond::any_tag_p<scalar_t, Ts...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_LET scalar_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<scalar_t>::template via<V>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `lattice` with point-wise addition, and the scalar sum/product. \
Provides even/odd-reflection iff `N_data == 2`. \

template <class A>
struct scalar<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using allotype = typename lattice<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<scalar_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  S_ = holotype<T>;
	
	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:// CONSTRUCT
	//	using S_::S_;

		XTAL_CO0_(homotype)
	//	XTAL_CO1_(homotype)
		XTAL_CO4_(homotype)

		XTAL_CON_(implicit) homotype()
		XTAL_0EX
		{
			auto &s = self();

			XTAL_IF0
			if (_std::is_constant_evaluated() or N_data <= _op::alignment::value) {
				[&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN {((get<I>(s) = U_data{1}),...);}
				(bond::seek_s<N_data>{});
			}
			else {
				_std::uninitialized_fill_n(S_::data(), S_::size(), U_data{1});
			}
		}
		XTAL_CON_(implicit) homotype(embrace_t<U_data> w)
		XTAL_0EX
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
		XTAL_CON_(explicit) homotype(auto &&...oo)
		XTAL_0EX requires (0 < sizeof...(oo))
		:	S_(XTAL_REF_(oo)...)
		{}

		XTAL_CON_(explicit) homotype(bool o)
		XTAL_0EX
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

		XTAL_DEF_(return,inline) XTAL_LET operator * (auto       const &t) XTAL_0FX        {return twin() *=   t ;}
		XTAL_DEF_(return,inline) XTAL_LET operator / (auto       const &t) XTAL_0FX        {return twin() /=   t ;}
		XTAL_DEF_(return,inline) XTAL_LET operator % (auto       const &t) XTAL_0FX        {return twin() %=   t ;}
		XTAL_DEF_(inline)        XTAL_LET operator *=(embrace_t<U_data> t) XTAL_0EX -> T & {return self() *= T(t);}
		XTAL_DEF_(inline)        XTAL_LET operator /=(embrace_t<U_data> t) XTAL_0EX -> T & {return self() /= T(t);}
		XTAL_DEF_(inline)        XTAL_LET operator %=(embrace_t<U_data> t) XTAL_0EX -> T & {return self() %= T(t);}

	//	Vector multiplication (Hadamard product):
		
		XTAL_DEF_(inline)
		XTAL_LET operator *=(array_q<N_data> auto const &t)
		XTAL_0EX -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v)
				XTAL_0FN {u *= v;}>(XTAL_REF_(t));
		}
		XTAL_DEF_(inline)
		XTAL_LET operator /=(array_q<N_data> auto const &t)
		XTAL_0EX -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v)
				XTAL_0FN {u /= v;}>(XTAL_REF_(t));
		}
		XTAL_DEF_(inline)
		XTAL_LET operator %=(array_q<N_data> auto const &t)
		XTAL_0EX -> T &
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
		XTAL_LET operator++()
		XTAL_0FX
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
		XTAL_LET operator--()
		XTAL_0FX
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
		XTAL_LET operator++(int)
		XTAL_0FX
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
		XTAL_LET operator--(int)
		XTAL_0FX
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
		XTAL_DEF_(return,inline)
		XTAL_LET sum(U_data const &u={})
		XTAL_0FX -> U_data
		{
			auto &s = self();

			if constexpr (0 < N_sgn) {
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(u +...+ (get<I>(s)))
				(bond::seek_s<N_data>{});
			}
			else {
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(u +...+ (get<I>(s)*U_data(-sign_n<I&1, -1>)))
				(bond::seek_s<N_data>{});
			}
		}

	//	Scalar product:
		template <int N_sgn=1>
		XTAL_DEF_(return,inline)
		XTAL_LET product(U_data u={})
		XTAL_0FX -> U_data
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
					u = _op::accumulate_f(u, v, v, U_data(-sign_n<I&1, -1>));
				});
			}
			return u;
		}
		XTAL_DEF_(return,inline)
		XTAL_LET product(bond::pack_sized_q<N_data> auto &&t)
		XTAL_0FX -> U_data
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
		XTAL_0EX -> U_data
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
		XTAL_0EX -> T &
		{
			return self() = reflected<N_par>();
		}
		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(return,inline)
		XTAL_LET reflected()
		XTAL_0FX -> decltype(auto)
		{
			auto &s = self();

			auto constexpr o = reflector<N_par>();
			auto const     x = o*get<0>(s);
			auto const     y = o*get<1>(s);
			return decltype(twin()) {x + y, x - y};
		}
		///\returns the reflection coefficient indexed by `N_par`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(return,inline)
		XTAL_SET reflector()
		XTAL_0EX -> devolved_u<U_data>
		{
			XTAL_IF0
			XTAL_0IF (N_par == -1) {return 0.5000000000000000000000000000000000000L;}
			XTAL_0IF (N_par ==  0) {return 0.7071067811865475244008443621048490393L;}
			XTAL_0IF (N_par == +1) {return 1.0000000000000000000000000000000000000L;}
		}


		XTAL_DEF_(return,inline)
		XTAL_LET ordering()
		XTAL_0FX
		{
			if constexpr (N_data == 2) {
				auto const &[x, y] = self();
				return x <=> y;
			}
		//	TODO: Provide variadic `ordering`.
		}
		XTAL_DEF_(return,inline)
		XTAL_LET ordered()
		XTAL_0FX
		{
			return S_::twin().order();
		}
		XTAL_DEF_(return,inline)
		XTAL_LET order()
		XTAL_0EX -> T &
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

		XTAL_DEF_(return,inline)
		XTAL_LET reversed()
		XTAL_0FX
		{
			return S_::twin().reverse();
		}
		XTAL_DEF_(inline)
		XTAL_LET reverse()
		XTAL_0EX -> T &
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
		XTAL_DEF_(return,inline)
		XTAL_LET colimited()
		XTAL_0FX -> U_data
		{
			return S_::template apply([] (auto &&...oo)
			XTAL_0FN {
				XTAL_IF0
				XTAL_0IF (N == 1) {return _std::max<U_data>({XTAL_REF_(oo)...});}
				XTAL_0IF (N <= 0) {return _std::min<U_data>({XTAL_REF_(oo)...});}
			});
		}
		XTAL_DEF_(return,inline)
		XTAL_LET colimited()
		XTAL_0FX
		{
			using  U2 = typename T::template tagged_t<U_data[2]>;
			return U2{colimited<0>(), colimited<1>()};
		}

		template <size_type N>
		XTAL_DEF_(return,inline)
		XTAL_LET cofactored()
		XTAL_0FX -> U_data
		{
			XTAL_IF0
			XTAL_0IF (N == 1) {return S_::template pointless<[] XTAL_1FN_(_std::lcm)>();}
			XTAL_0IF (N <= 0) {return S_::template pointless<[] XTAL_1FN_(_std::gcd)>();}
		}
		XTAL_DEF_(return,inline)
		XTAL_LET cofactored()
		XTAL_0FX
		{
			using  U2 = typename T::template tagged_t<U_data[2]>;
			return U2{cofactored<0>(), cofactored<1>()};
		}
		XTAL_DEF_(return,inline)
		XTAL_LET cofactorable()
		XTAL_0FX
		{
			auto t = ordered();
			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(...and (0 == get<I + 1>(t)%get<I>(t)))
			(bond::seek_s<N_data - 1>{});
		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(fungible_q<_std::array<float, 2>,
	XTAL_ALL_(XTAL_ANY_(scalar_t<float(&)[2]>)*XTAL_ANY_(scalar_t<float(&)[2]>))>
);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
