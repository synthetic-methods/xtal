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
even/odd-inflection iff `N_size == 2`, \
and Dirichlet characterization. \

template <class U_type, int N_size>
struct scalar<U_type[N_size]>
{
	using re = bond::realize<U_type>;
	
	template <class T>
	using demitype = typename sector<U_type[N_size]>::type::dual::template homotype<T>;

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
		~homotype() noexcept = default;
	//	XTAL_CO0_(homotype)
		XTAL_CO4_(homotype)

		XTAL_CON homotype()
		XTAL_0EX
		{
			_std::uninitialized_fill_n(T_::data(), T_::size(), U_type{1});
		}
		/***/
		XTAL_CON homotype(braces_t<U_type> w)
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

		XTAL_TN2 sum()
		XTAL_0FX
		{
			return [&, this]<auto ...M>(bond::seek_t<M...>)
				XTAL_0FN_(get(M) +...+ U_type())
			(bond::seek_f<N_size> {});
		}
		XTAL_TN2 product()
		XTAL_0FX
		{
			U_type u{};
			bond::seek_forward_f<N_size>([&, this] (auto i) XTAL_0FN {
				auto const &w = get(i);
				u = re::accumulate_f(u, w, w);
			});
			return u;
		}
		XTAL_TN2 product(iterated_q auto &&t)
		XTAL_0FX
		{
			U_type u{}; T &s = self();
			bond::seek_forward_f<N_size>([&, this] (auto i) XTAL_0FN {
				u = re::accumulate_f(u, s[i], t[i]);
			});
			return u;
		}

		///\returns the mutually inverse `lhs +/- rhs`, \
		scaled by the value indexed by `N_bias`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		///\todo\
		Generalize by taking the alternating sum for `N_par == -1`.

		template <int N_par=0>
		XTAL_TN2 inflected(int const n_bias=0)
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
		///\
		Modifies `this`; \see `inflected()`.

		XTAL_TN2 inflect(int const n_bias=0)
		XTAL_0FX
		XTAL_REQ (2 == N_size)
		{
			return self() = inflected(n_bias);
		}

		///\
		Dirichlet character generation. \

		XTAL_TN1_(T &) characterize()
		XTAL_0EX
		XTAL_REQ ((bool) (1&N_size)) and integral_number_q<U_type>
		{
			size_t constexpr M_size = N_size  - 1;
			size_t constexpr K      = M_size >> 1;
			size_t           k      =           1;

			let(0) = {};
			bond::seek_forward_f<M_size>([&, this] (auto const &i) XTAL_0FN {
				let(k%N_size) = i - M_size*(K < i);
				k *= K;
			});
			return self();
		}
		XTAL_TN1_(T &) characterize()
		XTAL_0EX
		XTAL_REQ ((bool) (1&N_size)) and complex_field_q<U_type>
		{
			size_t constexpr M_size = N_size  - 1;
			size_t constexpr K      = M_size >> 1;
			size_t           k      =           1;
			U_type u = re::circle_f(re::patio_f(2, M_size));
			U_type w = 1;

			let(0) = {};
			bond::seek_forward_f<K>([&, this] (auto &&) XTAL_0FN {
				auto const head = k%N_size;
				auto const tail =   N_size - head;
				let(head) =  w;
				let(tail) = -w;
				w *= u;
				k *= K;
			});
			return self();
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
