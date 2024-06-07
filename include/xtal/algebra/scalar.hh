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
XTAL_FN1 scalar_f(auto &&...oo)
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

		XTAL_CON homotype()
		XTAL_0EX
		{
			using _std::get; auto &s = self();

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
		XTAL_CON homotype(embrace_t<U_data> w)
		XTAL_0EX
		{
			using _std::get; auto &s = self();
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
		XTAL_CXN homotype(iterated_q auto &&w)
		XTAL_0EX
		:	T_(XTAL_REF_(w))
		{}

	public:// ACCESS
		using T_::get;
		using T_::let;
		using T_::self;
		using T_::twin;

	public:// OPERATE
		using T_::operator*=;
		using T_::operator/=;

		XTAL_DEF_(return,inline) XTAL_OP1_(auto) * (auto       const &t) XTAL_0FX {return twin() *=  (t);}
		XTAL_DEF_(return,inline) XTAL_OP1_(auto) / (auto       const &t) XTAL_0FX {return twin() /=  (t);}
		XTAL_DEF_(inline)        XTAL_OP1_(T  &) *=(embrace_t<U_data> t) XTAL_0EX {return self() *= T(t);}
		XTAL_DEF_(inline)        XTAL_OP1_(T  &) /=(embrace_t<U_data> t) XTAL_0EX {return self() /= T(t);}

	//	Vector multiplication (Hadamard product):
		
		XTAL_DEF_(inline)
		XTAL_OP1_(T &) *=(array_q<N_data> auto const &t)
		XTAL_0EX
		{
			using _std::get; auto &s = self();
			
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(s) *= get<I>(t)),...);}
			(bond::seek_s<N_data>{});
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_OP1_(T &) /=(array_q<N_data> auto const &t)
		XTAL_0EX
		{
			using _std::get; auto &s = self();
			
			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(s) /= get<I>(t)),...);}
			(bond::seek_s<N_data>{});
			return self();
		}

	//	Scalar sum:
		template <int N_sgn=1>
		XTAL_DEF_(return,inline)
		XTAL_TN1 sum(U_data const &u={})
		XTAL_0FX
		{
			using _std::get; auto &s = self();

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
		XTAL_TN1 product(U_data u={})
		XTAL_0FX
		{
			using _std::get; auto &s = self();
			
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
		XTAL_TN1 product(iterated_q auto &&t)
		XTAL_0FX
		{
			using _std::get; auto &s = self();
			
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
		XTAL_TN1 reflect()
		XTAL_0EX
		{
			return self() = reflected<N_par>();
		}
		///\returns the mutually inverse `lhs +/- rhs` scaled by the `reflector<N_par>()`. \
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(return,inline)
		XTAL_TN1 reflected()
		XTAL_0FX
		{
			using _std::get; auto &s = self();

			auto constexpr o = reflector<N_par>();
			auto const     x = o*get<0>(s);
			auto const     y = o*get<1>(s);
			return T {x + y, x - y};
		}
		///\returns the reflection coefficient indexed by `N_par`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		template <int N_par=0> requires (N_data == 2)
		XTAL_DEF_(return,inline)
		XTAL_LET reflector()
		XTAL_0EX -> devolved_t<U_data>
		{
			XTAL_IF0
			XTAL_0IF (N_par == -1) {return 0.5000000000000000000000000000000000000L;}
			XTAL_0IF (N_par ==  0) {return 0.7071067811865475244008443621048490393L;}
			XTAL_0IF (N_par == +1) {return 1.0000000000000000000000000000000000000L;}
		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(fungible_q<_std::array<float, 2>,
	XTAL_TYP_(XTAL_VAL_(scalar_t<float(&)[2]>)*XTAL_VAL_(scalar_t<float(&)[2]>))>
);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
