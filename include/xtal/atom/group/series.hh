#pragma once
#include "./any.hh"
#include "./sector.hh"
#include "./scalar.hh"




XTAL_ENV_(push)
namespace xtal::atom::group
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  series;
template <class ..._s> using   series_t = typename series<_s...>::type;
template <class ...Ts> concept series_q = bond::tag_p<series, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `sector` with multiplication defined by circular convolution. \

template <class U_type, int N_size>
struct series<U_type[N_size]>
{
	using U_v0 = U_type;
	using U_v1 = devalue_t<U_v0>;
	using U_v2 = devalue_t<U_v1>;

	using re = bond::realize<U_type>;
	
	template <class T>
	using demitype = typename sector<U_type[N_size]>::template homotype<T>;

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
		using T_::let;
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

		XTAL_CXN homotype(is_q<U_type> auto &&v)
		{
			generate(XTAL_REF_(v));
		}

		template <size_t N_limit=N_size>
		XTAL_TN1_(T &) generate(U_v1 const &u1, U_v2 const &u2)
		XTAL_0EX
		XTAL_REQ complex_field_q<U_v1> and is_q<scalar_t<U_v1[2]>, U_type>
		{
			using W1  = U_v1;
			using U2  = scalar_t<U_v2[2]>;
			using W1_ = series_t<W1[N_size<<1]>;
			using U2_ = series_t<U2[N_size<<1]>;
			static_assert(sizeof(W1_) == sizeof(U2_));
			
			reinterpret_cast<W1_ &>(self()).template generate<N_size, 0, 2, 0>(u1);
			reinterpret_cast<U2_ &>(self()).template generate<N_size, 0, 2, 1>({u2, re::template root_f<-1>(u2)});
			bond::seek_forward_f<N_size>([this] (auto i) XTAL_0FN {
				auto const &[o, e] = get(i);
				let(i) = {o*e.real(), _std::conj(o)*e.imag()};
			});
			return self();
		}
		///\returns `this` with the elements `N_index, ..., N_index + N_limit - 1` \
			filled by the corresponding powers of `u`. \

		template <size_t N_limit=N_size, size_t N_index=0, size_s N_step=1, size_s N_skip=0>
		XTAL_TN1_(T &) generate(U_type const &u)
		XTAL_0EX
		{
			using I = typename T_::difference_type;

			auto constexpr N_shift = re::bit_ceiling_f(N_step);
			static_assert(N_step == 1 << N_shift);

		//	Compute the start- and end-points for the required segment:
			I constexpr I0 = N_skip + N_step*(N_index +            (0));
			I constexpr I1 = N_skip + N_step*(N_index +            (1));
			I constexpr IM = N_skip + N_step*(N_index + (N_limit >> 1));
			I constexpr IN = N_skip + N_step*(N_index + (N_limit  - 1));
			I constexpr M_skip = N_step - N_skip;

		//	Compute and populate the 0th and 1st powers:
			auto const o = re::template explo_f<N_index>(u);
			let(I0) = o;
			let(I1) = o*u;

			for (I i = I1; i < IM; i += N_step) {
				auto w = re::square_f(get(i));
			
			//	Use the square of the previous value to populate the values at `i << 1`:
				I ii = i << 1;
				let(ii - N_skip) = w;
				let(ii + M_skip) = w*u;
			}
		//	Compute the final value if `N_limit` is odd:
			if constexpr (N_limit&1) {
				let(IN) = get(IN - N_step)*(u);
			}
			return self();
		}

		///\returns `this` as the complex sinusoid with length `2*PI*std::pow(2, N_shift)`,  `-3 <= N_shift`. \
		
		///\note\
		To generate the FFT basis used by `transform` etc, use `N_shift == -1`. \

		template <int N_shift=0>
		XTAL_TN1_(T &) generate()
		XTAL_0EX
		XTAL_REQ complex_field_q<U_type>
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
			if constexpr (-2 <= N_shift) _detail::copy_to(_std::prev(j, 2*M), _std::span(i, _std::next(i, 1*M)), [] (U_type const &v) XTAL_0FN_(U_type {-v.imag(), -v.real()}));
			if constexpr (-1 <= N_shift) _detail::copy_to(_std::next(i, 2*M), _std::span(i, _std::next(i, 2*M)), [] (U_type const &v) XTAL_0FN_(U_type { v.imag(), -v.real()}));
			if constexpr (-0 <= N_shift) _detail::copy_to(_std::next(i, 4*M), _std::span(i, _std::next(i, 4*M)), [] (U_type const &v) XTAL_0FN_(U_type {-v.real(), -v.imag()}));
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
		XTAL_REQ complex_field_q<U_type>
		{
			using Y = XTAL_TYP_(that);
			using X = typename Y::dual::type;
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
					U_type const y = that[j + u]*get(i_k);
					U_type const x = that[j + 0];
					that[j + u] = x - y;
					that[j + 0] = x + y;
				}}
			}
		//	Conjugate and scale the output if computing the inverse transform of the codomain:
			if constexpr (N_direction == -1) {
				_detail::apply_to(that, [=] XTAL_1FN_(_std::conj));
				that /= n_size;
			}
		
		//	Cast the output to the transformed domain:
			return reinterpret_cast<X &>(that);
		}
		///\returns a new `series` representing the FFT of `lhs`, \
		using `this` as the Fourier basis. \

		template <int N_direction=1> requires sign_p<N_direction, 1>
		XTAL_TN2 transformation(isomorphic_q<T> auto const &that)
		XTAL_0FX
		{
			using Y = XTAL_TYP_(that);
			using X = typename Y::dual::type;
			X  x = reinterpret_cast<X const &>(that);
			Y &y = reinterpret_cast<Y       &>(x);
			(void) transform<N_direction>(y);
			return x;
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
		XTAL_TN2 convolution(Y const &lhs, Y const &rhs)
		XTAL_0FX
		{
			auto lhs_ = lhs; convolve(lhs_, rhs); return lhs_;
		}

		///\
		Multiplication by circular convolution. \

		using T_::operator*=;

		XTAL_OP1_(T &) *=(T const &t)
		XTAL_0EX
		{
			auto &s = self();
			if constexpr (complex_field_q<U_type>) {
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
