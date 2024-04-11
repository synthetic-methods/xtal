#pragma once
#include "./any.hh"
#include "./sector.hh"





XTAL_ENV_(push)
namespace xtal::atom::group
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  scalar;
template <class ..._s> using   scalar_t = typename scalar<_s...>::type;
template <class ...Ts> concept scalar_q = bond::tag_p<scalar, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends the `dual` of `sector` with the inner-sum/product, \
and even/odd-reflection iff `N_size == 2`. \

template <class U_data, int N_size>
struct scalar<U_data[N_size]>
{
	using re = bond::realize<U_data>;
	using U_delta = re::delta_t;
	using U_sigma = re::sigma_t;
	using U_alpha = re::alpha_t;
	
	template <class T>
	using demitype = typename sector<U_data[N_size]>::type::dual::template homotype<T>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<scalar>>;

	template <class T>
	class homotype : public hemitype<T>
	{
		friend T;
		using  T_ = hemitype<T>;
	
	public:
		using T_::get;
		using T_::let;
		using T_::self;
		using T_::twin;

	public:// CONSTRUCT
		/*/
		using T_::T_;
		/*/
		XTAL_CO0_(homotype)
	//	XTAL_CO1_(homotype)
		XTAL_CO4_(homotype)

		XTAL_CON homotype()
		XTAL_0EX
		{
			_std::uninitialized_fill_n(T_::data(), T_::size(), U_data{1});
		}
		/***/
		XTAL_CON homotype(braces_t<U_data> w)
		XTAL_0EX
		{
			_detail::copy_to(T_::begin(), w.begin(), w.end());
			if (1 == w.size()) {
				_std::uninitialized_fill_n(_std::next(T_::data(), w.size()), T_::size() - w.size(), get(0));
			}
			else {
				assert(w.size() == N_size);
			}
		}
		XTAL_CON homotype(iterated_q auto &&w)
		XTAL_0EX
		:	T_(XTAL_REF_(w))
		{}

		template <int N_sign=1>
		XTAL_TN2 sum(U_data const &u={})
		XTAL_0FX
		{
			if constexpr (0 < N_sign) {
				return [&, this]<auto ...M>(bond::seek_t<M...>)
					XTAL_0FN_(u +...+ (get(M)))
				(bond::seek_f<N_size>{});
			}
			else {
				return [&, this]<auto ...M>(bond::seek_t<M...>)
					XTAL_0FN_(u +...+ (get(M)*re::assign_f((U_sigma) M)))
				(bond::seek_f<N_size>{});
			}
		}
		template <int N_sign=1>
		XTAL_TN2 product(U_data u={})
		XTAL_0FX
		{
			if constexpr (0 < N_sign) {
				bond::seek_forward_f<N_size>([&, this] (auto i) XTAL_0FN {
					auto const &v = get(i);
					u = re::accumulate_f(u, v, v);
				});
			}
			else {
				bond::seek_forward_f<N_size>([&, this] (auto i) XTAL_0FN {
					auto const &v = get(i);
					u = re::accumulate_f(u, v, v, re::assign_f((U_sigma) i));
				});
			}
			return u;
		}
		XTAL_TN2 product(iterated_q auto &&t)
		XTAL_0FX
		{
			U_data u{}; T &s = self();
			bond::seek_forward_f<N_size>([&, this] (auto i) XTAL_0FN {
				u = re::accumulate_f(u, s[i], t[i]);
			});
			return u;
		}

		///\returns the mutually inverse `lhs +/- rhs`, \
		scaled by the value indexed by `N_bias`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		///\todo\
		Generalize by taking the alternating sum for `N_par == -1`?

		///\
		Modifies `this`; \see `reflected()`.

		XTAL_TN2 reflect(int const n_bias=0)
		XTAL_0FX
		XTAL_REQ (2 == N_size)
		{
			return self() = reflected(n_bias);
		}
		template <int N_par=0>
		XTAL_TN2 reflected(int const n_bias=0)
		XTAL_0FX
		XTAL_REQ (2 == N_size)
		{
			auto const scale = re::explo_f(re::template unsquare_f<-1>(2), 1 - n_bias);
			auto const lhs = scale*get(0);
			auto const rhs = scale*get(1);
			if constexpr (N_par ==  0) {
				return T {lhs + rhs, lhs - rhs};
			}
			if constexpr (N_par == +1) {
				return lhs + rhs;
			}
			if constexpr (N_par == -1) {
				return lhs - rhs;
			}
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
