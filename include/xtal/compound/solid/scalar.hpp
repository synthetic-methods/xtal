#pragma once
#include "./any.hpp"
#include "./strata.hpp"





XTAL_ENV_(push)
namespace xtal::compound::solid
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_NYM scalar;
template <class ..._s> XTAL_USE scalar_t = typename scalar<_s...>::type;
template <class ...Ts> XTAL_ASK scalar_q = tag_p<scalar, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `strata::type` with elementwise multiplication/division. \

template <class U, size_t N>
struct scalar<U[N]>
{
	using _computer = compute<U>;
	
	template <class T>
	using demitype = typename strata<U[N]>::template homotype<T>;

	template <class T>
	using hemitype = compose_s<demitype<T>, tag<scalar>>;

	template <class T>
	class homotype: public hemitype<T>
	{
		friend T;
		using S_ = hemitype<T>;
	
	public:
		using S_::S_;
		using S_::d;
		using S_::self;
		using S_::twin;

		///\
		The counterpart to `this` for which addition is linear, \
		and multiplication is performed via convolution. \
		
		template <class Z>
		using dual_t = Z;

		XTAL_OP1_(T &) *= (bracket_t<U> w) XTAL_0EX {return self() *= T(w.begin(), w.end());}
		XTAL_OP1_(T &) /= (bracket_t<U> w) XTAL_0EX {return self() /= T(w.begin(), w.end());}				
		
		XTAL_OP1_(T &) *= (T const &t) XTAL_0EX {return seek_e<N>([&, this] (auto i) XTAL_0FN_(d(i) *= t.d(i))), self();}
		XTAL_OP1_(T &) /= (T const &t) XTAL_0EX {return seek_e<N>([&, this] (auto i) XTAL_0FN_(d(i) /= t.d(i))), self();}

		XTAL_FN2 sum()
		XTAL_0FX
		{
			return [&, this]<auto ...M>(seek_t<M...>)
				XTAL_0FN_(d(M) +...+ U())
			(seek_f<N> {});
		}
		XTAL_FN2 dot()
		XTAL_0FX
		{
			return _computer::square_f(*this).sum();
		}
		XTAL_FN2 dot(XTAL_DEF_(iterated_q) that)
		XTAL_0FX
		{
			return (twin() *= XTAL_REF_(that)).sum();
		}

		///\returns the mutually inverse `lhs +/- rhs`, \
		scaled by the value indexed by `N_bias`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
		
		///\note\
		Useful for converting between e.g. exponential/hyperbolic or stereo/mid-side pairs. \

		template <int N_par=0>
		XTAL_FN2 reflected(int const n_bias=0)
		XTAL_0FX
		XTAL_REQ (N == 2)
		{
			auto const scale = _computer::explo_f(_computer::template unsquare_f<-1>(2), 1 - n_bias);
			auto const lhs = scale*d(0);
			auto const rhs = scale*d(1);
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
		Modifies `this`; \see `reflected()`.

		XTAL_FN2 reflect(int const n_bias=0)
		XTAL_0FX
		XTAL_REQ (N == 2)
		{
			return self() = reflected(n_bias);
		}

	};
	using type = _detail::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
