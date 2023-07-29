#pragma once
#include "./any.hpp"
#include "./sector.hpp"





XTAL_ENV_(push)
namespace xtal::compound::solid
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_NYM series;
template <class ..._s> XTAL_USE series_t = typename series<_s...>::type;
template <class ...Ts> XTAL_ASK series_q = tag_p<series, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `sector::type` with multiplication defined by circular convolution. \

template <class U, size_t N>
struct series<U[N]>
{
	using _computer = compute<U>;
	
	template <class T>
	using demitype = typename sector<U[N]>::template homotype<T>;

	template <class T>
	using hemitype = compose_s<demitype<T>, tag<series>>;

	template <class T>
	class homotype: public hemitype<T>
	{
		friend T;
		using S_ = hemitype<T>;
	
		template <class Y>
		using duel_t = typename Y::template dual_t<T>;

	public:
		using S_::S_;
		using S_::d;
		using S_::self;
		using S_::twin;

		///\
		Generates part of the complex sinusoid determined by `std::pow(2, shift_o{})`. \

		XTAL_CXN homotype(constant_q auto const shift_o)
		{
			generate<shift_o>();
		}
		///\
		Generates the power series with the given seed. \

		XTAL_CXN homotype(XTAL_DEF_(is_q<U>) v)
		{
			generate(XTAL_REF_(v));
		}

		///\returns `this` with the elements `N_index, ..., N_index + N_limit - 1` \
			filled by the corresponding powers of `u`. \

		template <size_t N_limit=N, size_t N_index=0>
		XTAL_FN1_(T &) generate(U const &u)
		XTAL_0EX
		{
			using I = typename S_::difference_type;

		//	Compute the start- and end-points for the required segment:
			I constexpr H_limit = N_limit >> 1;
			I constexpr _0 = N_index + 0;
			I constexpr _1 = N_index + 1;
			I constexpr _H = N_index + H_limit;
			I constexpr N1 = N_index + N_limit - 1;
			I constexpr N2 = N_index + N_limit - 2;

		//	Compute and populate the 0th and 1st powers:
			auto const o = _computer::template explo_f<N_index>(u);
			d(_0) = o;
			d(_1) = o*u;

			for (I i = _1; i < _H; ++i) {
				auto w = _computer::square_f(d(i));
			
			//	Use the square of the previous value to populate the value at `i << 1`:
				I ii = i << 1;
				d(ii + 0) = w;
				d(ii + 1) = w*u;
			}
		//	Compute the final value if `N_limit` is odd:
			if constexpr (N_limit&1) {
				d(N1) = d(N2)*u;
			}
			return self();
		}

		///\returns `this` as the complex sinusoid with length `2*PI*std::pow(2, N_shift)`,  `-3 <= N_shift`. \
		
		///\note\
		To generate the FFT basis used by `transform` etc, use `N_shift == -1`. \

		template <int N_shift=0>
		XTAL_FN1_(T &) generate()
		XTAL_0EX
		XTAL_REQ complex_field_q<U>
		{
		//	Initialize the forwards and backwards iterators:
			auto const i = S_::begin();
			auto const j = S_::rend() - 1;
			
		//	Compute the fractional sinusoid for the given `N`:
			auto constexpr x = _computer::template patio_f<-1>(N);
			auto const     y = _computer::circle_f(x);// TODO: Make `constexpr`.
			
		//	Compute the initial `1/8`th then mirror the remaining segments:
			typename S_::difference_type constexpr M = N >> 2;// `1/8`th
			static_assert(-4 <  N_shift);
			generate<M + (-3 <  N_shift)>(y);
			if constexpr (-2 <= N_shift) _detail::copy_to(j - 2*M, _std::span(i, i + 1*M), [] (U const &v) XTAL_0FN_(U(-v.imag(), -v.real())));
			if constexpr (-1 <= N_shift) _detail::copy_to(i + 2*M, _std::span(i, i + 2*M), [] (U const &v) XTAL_0FN_(U( v.imag(), -v.real())));
			if constexpr (-0 <= N_shift) _detail::copy_to(i + 4*M, _std::span(i, i + 4*M), [] (U const &v) XTAL_0FN_(U(-v.real(), -v.imag())));
			static_assert( 0 >= N_shift);// TODO: Extend to allow multiple copies using `seek`.
			
			return self();
		}
		
		///\returns `that` transformed by the FFT, using `this` as the Fourier basis. \
		
		///\note\
		The size of both `this` and `that` must be expressible as an integral power of two, \
		and `1 < that.size() <= this->size()`. \

		template <isomorphic_p<T> Y>
		XTAL_FN1_(duel_t<Y> &) transform(Y &that)
		XTAL_0FX
		XTAL_REQ complex_field_q<U>
		{
			using I = typename Y::difference_type;
		
		//	Detect whether `Y` is a `scalar` of any `N` (by sleight of hand):
			bool constexpr degenerate = is_q<typename Y::template dual_t<Y>, Y>;

		//	Ensure the size of both domain and codomain are powers of two:
			I const n_size = that.size(); assert(2 <= n_size);
			I const h_size = n_size >> 1; assert(1 <= h_size);
			I const k_size = compute<I>::bit_floor_f((I) n_size); assert(n_size == 1 << k_size);
			I const K_size = compute<I>::bit_floor_f((I) N); assert(k_size <= K_size);

		//	Move all entries to their bit-reversed locations:
			for (I h = 0; h < h_size; ++h) {
				_std::swap(that[h], that[compute<I>::bit_reverse_f(h, k_size)]);
			}
		
		//	Conjugate the input if computing the inverse transform of the codomain:
			if constexpr (degenerate) {
				_detail::apply_to(that, [] XTAL_1FN_(_std::conj));
			}
		//	Compute the transform of `that` using the precomputed sinusoid via `d`:
			for (I k = 0; k < k_size; ++k) {
				I const kn = K_size - k;
				I const u = 1 << k;
				I const w = u << 1;
				I const n = n_size;
				for (I                  i = 0; i < u; i += 1) {
				for (I knife = i << kn, j = i; j < n; j += w) {
					U const y = that[j + u]*d(knife);
					U const x = that[j + 0];
					that[j + u] = x - y;
					that[j + 0] = x + y;
				}}
			}
		//	Conjugate and scale the output if computing the inverse transform of the codomain:
			if constexpr (degenerate) {
				auto const u_size = _computer::template ratio_f<1>(n_size);
				_detail::apply_to(that, [&]XTAL_1FN_(u_size*_std::conj));
			}
		
		//	Cast the output to the transformed domain:
			return that.template self<duel_t<Y> &>();
		}
		///\returns a new `series` representing the FFT of `lhs`, \
		using `this` as the Fourier basis. \

		template <isomorphic_p<T> Y>
		XTAL_FN2_(duel_t<Y>) transformation(Y that)
		XTAL_0FX
		{
			return transform(that);//.template self<duel_t<Y>>();
		}

		///\returns `lhs` convolved with `rhs`, \
		using `this` as the Fourier basis. \

		template <isomorphic_p<T> Y>
		XTAL_FN1_(Y &) convolve(Y &lhs, Y rhs)
		XTAL_0FX
		{
			return transform(transform(lhs) *= transform(rhs));
		}
		///\returns a new `series` representing the convolution of `lhs` with `rhs`, \
		using `this` as the Fourier basis. \

		template <isomorphic_p<T> Y>
		XTAL_FN2_(Y) convolution(Y lhs, Y const &rhs)
		XTAL_0FX
		{
			return convolve(lhs, rhs);
		}

		///\
		Multiplication by circular convolution. \

		XTAL_OP1_(T &) *=(T const &t)
		XTAL_0EX
		{
			auto &s = self();
			if constexpr (complex_field_q<U>) {
				T(integer_t<-1>{}).convolve(s, t);
			}
			else {
				using X = typename _computer::aphex_t;
				using Y = typename series<X>::type;
				Y s_(s);
				Y t_(t);
				Y(integer_t<-1>{}).convolve(s_, t_);
				_detail::move_to(s.begin(), s_, [] XTAL_1FN_(_std::real));
			}
			return s;
		}
		XTAL_OP2_(T) * (T const &t)
		XTAL_0FX
		{
			return twin() *= t;
		}

	};
	using type = _detail::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
