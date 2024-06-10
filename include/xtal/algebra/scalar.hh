#pragma once
#include "./any.hh"
#include "./lattice.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class           ..._s>	XTAL_TYP scalar;
template <class           ..._s>	XTAL_USE scalar_t = typename scalar<_s...>::type;
template <class           ...Ts>	XTAL_ASK scalar_q = bond::head_tag_p<scalar_t, Ts...>;
template <size_t N, class ...Ts>	XTAL_ASK scalar_p = scalar_q<Ts...> and (...and (N == Ts::size()));
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
	using U_delta = typename _op::delta_t;
	using U_sigma = typename _op::sigma_t;
	using U_alpha = typename _op::alpha_t;
	
	template <class T>
	using allotype = typename lattice<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<scalar_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
	
	protected:
		using          T_::N_data;
		using typename T_::U_data;

	public:// CONSTRUCT
	//	using T_::T_;

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
				_std::uninitialized_fill_n(T_::data(), T_::size(), U_data{1});
			}
		}
		XTAL_CON_(implicit) homotype(embrace_t<U_data> w)
		XTAL_0EX
		{
			auto &s = self();
			auto const m = w.size();
			
			_detail::copy_to(T_::begin(), w);

			assert(1 == m or m == N_data);
			if (1 == m) {
				auto const &u = get<0>(s);
				if (_std::is_constant_evaluated() or N_data <= _op::alignment::value) {
					[&]<auto ...I> (bond::seek_t<I...>)
						XTAL_0FN {((get<I + 1>(s) = u),...);}
					(bond::seek_s<N_data - 1>{});
				}
				else {
					_std::uninitialized_fill_n(_std::next(T_::data(), m), T_::size() - m, u);
				}
			}
		}
		XTAL_CON_(explicit) homotype(auto &&...oo)
		XTAL_0EX
		XTAL_REQ (0 < sizeof...(oo))
		:	T_(XTAL_REF_(oo)...)
		{}

	public:// ACCESS
		using T_::let;
		using T_::self;
		using T_::twin;

	public:// OPERATE
		using T_::operator*=;
		using T_::operator/=;
		using T_::operator%=;

		XTAL_DEF_(return,inline) XTAL_LET operator * (auto       const &t) XTAL_0FX {return twin() *=  (t);}
		XTAL_DEF_(return,inline) XTAL_LET operator / (auto       const &t) XTAL_0FX {return twin() /=  (t);}
		XTAL_DEF_(return,inline) XTAL_LET operator % (auto       const &t) XTAL_0FX {return twin() %=  (t);}
		XTAL_DEF_(inline)        XTAL_REF operator *=(embrace_t<U_data> t) XTAL_0EX {return self() *= T(t);}
		XTAL_DEF_(inline)        XTAL_REF operator /=(embrace_t<U_data> t) XTAL_0EX {return self() /= T(t);}
		XTAL_DEF_(inline)        XTAL_REF operator %=(embrace_t<U_data> t) XTAL_0EX {return self() %= T(t);}

	//	Vector multiplication (Hadamard product):
		
		XTAL_DEF_(inline)
		XTAL_LET operator *=(array_q<N_data> auto const &t)
		XTAL_0EX -> T &
		{
			auto &s = self();
			
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(s) *= get<I>(t)),...);}
			(bond::seek_s<N_data>{});
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator /=(array_q<N_data> auto const &t)
		XTAL_0EX -> T &
		{
			auto &s = self();
			
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(s) /= get<I>(t)),...);}
			(bond::seek_s<N_data>{});
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator %=(array_q<N_data> auto const &t)
		XTAL_0EX -> T &
		{
			auto &s = self();
			
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(s) %= get<I>(t)),...);}
			(bond::seek_s<N_data>{});
			return self();
		}

	//	Scalar sum:
		template <int N_sgn=1>
		XTAL_DEF_(return,inline)
		XTAL_REF sum(U_data const &u={})
		XTAL_0FX
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
		XTAL_REF product(U_data u={})
		XTAL_0FX
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
		XTAL_REF product(iterated_q auto &&t)
		XTAL_0FX
		{
			auto &s = self();
			
			U_data u{};
			bond::seek_forward_f<N_data>([&, this] (auto I) XTAL_0FN {
				u = _op::accumulate_f(u, get<I>(s), get<I>(t));
			});
			return u;
		}

		///\
		Modifies `this`; \see `reflected()`.

		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(inline)
		XTAL_REF reflect()
		XTAL_0EX
		{
			return self() = reflected<N_par>();
		}
		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(return,inline)
		XTAL_REF reflected()
		XTAL_0FX
		{
			auto &s = self();

			auto constexpr o = reflector<N_par>();
			auto const     x = o*get<0>(s);
			auto const     y = o*get<1>(s);
			return decltype(twin()) {x + y, x - y};
		}
		///\returns the reflection coefficient indexed by `N_par`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(return,inline,static)
		XTAL_LET reflector()
		XTAL_0EX -> devolved_t<U_data>
		{
			XTAL_IF0
			XTAL_0IF (N_par == -1) {return 0.5000000000000000000000000000000000000L;}
			XTAL_0IF (N_par ==  0) {return 0.7071067811865475244008443621048490393L;}
			XTAL_0IF (N_par == +1) {return 1.0000000000000000000000000000000000000L;}
		}


		XTAL_DEF_(return,inline)
		XTAL_REF ordered()
		XTAL_0FX
		XTAL_REQ (2 == N_data)
		{
			using U2 = typename T::template tagged_t<U_data[2]>;

			auto const &[x, y] = self();
			return x < y? U2{x, y}: U2{y, x};
		}
		XTAL_DEF_(return,inline)
		XTAL_REF coordered()
		XTAL_0FX
		XTAL_REQ (2 == N_data) and _std::integral<U_data>
		{
			using U2 = typename T::template tagged_t<U_data[2]>;

			auto const [x, y] = ordered();
			if (x == _std::gcd(x, y) and y == _std::lcm(x, y)) {
				return U2{x, y};
			}
			else {
				return U2{0, 0};
			}
		}
		XTAL_DEF_(return,inline)
		XTAL_REF coordered()
		XTAL_0FX
		XTAL_REQ (3 <= N_data) and _std::integral<U_data>
		{
			using U_ = _std::numeric_limits<U_data>;
			using U2 = typename T::template tagged_t<U_data[2]>;
			
			auto &s = self();

			U2 fact{U_::max(), U_::min()};
			for (size_t i = 0; i < N_data - 1; ++i) {
				for (size_t j = i + 1; j < N_data; ++j) {
					auto factoid = U2{s[i], s[j]}.coordered();
					fact.incorporate(factoid);
					if (0 == factoid.sum()) {
						return factoid;
					}
				}
			}
			return fact;
		}

		XTAL_DEF_(inline)
		XTAL_REF incorporate(auto const &t)
		XTAL_0EX
		XTAL_REQ (2 == N_data)
		{
			auto &s = self();
			if (t[0] < s[0]) {s[0] = t[0];}
			if (s[1] < t[1]) {s[1] = t[1];}
			return s;
		}
		XTAL_DEF_(return,inline)
		XTAL_REF incorporated(auto &&t)
		XTAL_0FX
		XTAL_REQ (2 == N_data)
		{
			return twin().incorporate(XTAl_REF_(t));
		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(fungible_q<_std::array<float, 2>,
	XTAL_TYP_(XTAL_ANY_(scalar_t<float(&)[2]>)*XTAL_ANY_(scalar_t<float(&)[2]>))>
);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
