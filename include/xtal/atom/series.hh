#pragma once
#include "./any.hh"
#include "./sector.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_NEW series;
template <class ..._s> XTAL_USE series_t = typename series<_s...>::type;
template <class ...Ts> XTAL_ASK series_q = bond::tag_p<series, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `sector` with multiplication defined by circular convolution. \

template <class U, int N_size>
struct series<U[N_size]>
{
	using re = bond::realize<U>;
	
	template <class T>
	using demitype = typename sector<U[N_size]>::template homotype<T>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<series>>;

	template <class T>
	class homotype : public hemitype<T>
	{
		friend T;
		using  T_ = hemitype<T>;
	
	public:
		using T_::T_;
		using T_::get;
		using T_::self;
		using T_::twin;

		///\
		Generates part of the complex sinusoid determined by `std::pow(2, o_shift{})`. \

		XTAL_CXN homotype(integral_q auto const o_shift)
		{
			generate<o_shift>();
		}
		///\
		Generates the power series with the given seed. \

		XTAL_CXN homotype(is_q<U> auto &&v)
		{
			generate(XTAL_REF_(v));
		}

		///\returns `this` with the elements `N_index, ..., N_index + N_limit - 1` \
			filled by the corresponding powers of `u`. \

		template <size_t N_limit=N_size, size_t N_index=0>
		XTAL_TN1_(T &) generate(U const &u)
		XTAL_0EX
		{
			using I = typename T_::difference_type;

		//	Compute the start- and end-points for the required segment:
			I constexpr i0 = N_index + 0;
			I constexpr i1 = N_index + 1;
			I constexpr iM = N_index + (N_limit >> 1);
			I constexpr iN = N_index + (N_limit  - 1);

		//	Compute and populate the 0th and 1st powers:
			auto const o = re::template explo_f<N_index>(u);
			get(i0) = o;
			get(i1) = o*u;

			for (I i = i1; i < iM; ++i) {
				auto w = re::square_f(get(i));
			
			//	Use the square of the previous value to populate the value at `i << 1`:
				I ii = i << 1;
				get(ii + 0) = w;
				get(ii + 1) = w*u;
			}
		//	Compute the final value if `N_limit` is odd:
			if constexpr (N_limit&1) {
				get(iN) = get(iN - 1)*u;
			}
			return self();
		}

		///\returns `this` as the complex sinusoid with length `2*PI*std::pow(2, N_shift)`,  `-3 <= N_shift`. \
		
		///\note\
		To generate the FFT basis used by `transform` etc, use `N_shift == -1`. \

		template <int N_shift=0>
		XTAL_TN1_(T &) generate()
		XTAL_0EX
		XTAL_REQ complex_field_q<U>
		{
		//	Initialize the forwards and backwards iterators:
			auto const i = T_::begin();
			auto const j = T_::rend() - 1;
			
		//	Compute the fractional sinusoid for this `N_size`:
			auto constexpr x = re::patio_f(-1, N_size);
			auto const     y = re::circle_f(x);// TODO: Make `constexpr`?
			
		//	Compute the initial `1/8`th then mirror the remaining segments:
			typename T_::difference_type constexpr M = N_size >> 2;// `1/8`th
			static_assert(-4 <  N_shift);
			generate<M + (-3 <  N_shift)>(y);
			if constexpr (-2 <= N_shift) _detail::copy_to(_std::prev(j, 2*M), _std::span(i, _std::next(i, 1*M)), [] (U const &v) XTAL_0FN_(U {-v.imag(), -v.real()}));
			if constexpr (-1 <= N_shift) _detail::copy_to(_std::next(i, 2*M), _std::span(i, _std::next(i, 2*M)), [] (U const &v) XTAL_0FN_(U { v.imag(), -v.real()}));
			if constexpr (-0 <= N_shift) _detail::copy_to(_std::next(i, 4*M), _std::span(i, _std::next(i, 4*M)), [] (U const &v) XTAL_0FN_(U {-v.real(), -v.imag()}));
			static_assert( 0 >= N_shift);// TODO: Extend to allow multiple copies using `bond::seek`.
			
			return self();
		}
		
		///\returns `that` transformed by the FFT, using `this` as the Fourier basis. \
		
		///\note\
		The size of both `this` and `that` must be expressible as an integral power of two, \
		and `1 < that.size() <= this->size()`. \

		template <int N_direction=1> requires sign_p<N_direction, 1>
		XTAL_TN1 transform(isomorphic_q<T> auto &that)
		XTAL_0FX
		XTAL_REQ complex_field_q<U>
		{
			using Y = XTAL_TYP_(that);
			using I = typename Y::difference_type;
		
		//	Ensure the size of both domain and codomain are powers of two:
			I const n_size = that.size(); assert(2 <= n_size);
			I const h_size = n_size >> 1; assert(1 <= h_size);
			I const k_size = bond::realize<I>::bit_floor_f((I) n_size); assert(n_size == 1 << k_size);
			I const K_size = bond::realize<I>::bit_floor_f((I) N_size); assert(k_size <= K_size);

		//	Move all entries to their bit-reversed locations:
			for (I h = 0; h < h_size; ++h) {
				_std::swap(that[h], that[bond::realize<I>::bit_reverse_f(h, k_size)]);
			}
		
		//	Conjugate the input if computing the inverse transform of the codomain:
			if constexpr (N_direction == -1) {
				_detail::apply_to(that, [] XTAL_1FN_(_std::conj));
			}
		//	Compute the transform of `that` using the precomputed sinusoid via `d`:
			for (I k = 0; k < k_size; ++k) {
				I const _k = K_size - k;
				I const  u = 1 << k;
				I const  w = u << 1;
				I const  n = n_size;
				for (I i = 0; i < u; i += 1) {I const i_k = i << _k;
				for (I j = i; j < n; j += w) {
					U const y = that[j + u]*get(i_k);
					U const x = that[j + 0];
					that[j + u] = x - y;
					that[j + 0] = x + y;
				}}
			}
		//	Conjugate and scale the output if computing the inverse transform of the codomain:
			if constexpr (N_direction == -1) {
				_detail::apply_to(that, [] XTAL_1FN_(_std::conj));
				that *= re::ratio_f(1, n_size);
			}
		
		//	Cast the output to the transformed domain:
			return reinterpret_cast<typename Y::template dual<T>::type &>(that);
		}
		///\returns a new `series` representing the FFT of `lhs`, \
		using `this` as the Fourier basis. \

		template <int N_direction=1> requires sign_p<N_direction, 1>
		XTAL_TN2 transformation(isomorphic_q<T> auto that)
		XTAL_0FX
		{
			return transform<N_direction>(that);
		}

		///\returns `lhs` convolved with `rhs`, \
		using `this` as the Fourier basis. \

		template <isomorphic_q<T> Y>
		XTAL_TN1 convolve(Y &lhs, Y rhs)
		XTAL_0FX
		{
			return transform<-1>(transform<1>(lhs) *= transform<1>(rhs));
		}
		///\returns a new `series` representing the convolution of `lhs` with `rhs`, \
		using `this` as the Fourier basis. \

		template <isomorphic_q<T> Y>
		XTAL_TN2 convolution(Y lhs, Y const &rhs)
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
				T(ordinal_t<-1>{}).convolve(s, t);
			}
			else {
				using X = typename re::aphex_t;
				using Y = typename series<X>::type;
				Y s_(s);
				Y t_(t);
				Y(ordinal_t<-1>{}).convolve(s_, t_);
				_detail::move_to(s.begin(), s_, [] XTAL_1FN_(_std::real));
			}
			return s;
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
