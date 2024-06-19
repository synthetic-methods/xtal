#pragma once
#include "./any.hh"
#include "./serial.hh"
#include "./scalar.hh"




XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP series;
template <class   ..._s>	XTAL_USE series_t = typename series<_s...>::type;
template <class   ...Ts>	XTAL_REQ series_q = bond::any_tag_p<series_t, Ts...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_LET series_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<series_t>::template via<V>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `serial` with multiplication defined by circular convolution. \

template <column_q A>
struct series<A>
{
	using U_v0 = invalued_t<A>;
	using U_v1 = devalued_t<U_v0>;
	using U_v2 = devalued_t<U_v1>;

	using _op = bond::operate<A>;
	
	template <class T>
	using allotype = typename serial<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<series_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  S_ = holotype<T>;

	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:
		using S_::S_;
		using S_::let;
		using S_::self;
		using S_::twin;

		///\
		Generates part of the complex sinusoid determined by `std::pow(2, o_shift{})`. \

		XTAL_CON_(explicit) homotype(nominal_q auto const o_shift)
		{
			generate<o_shift>();
		}
		///\
		Generates the power series with the given seed. \

		XTAL_CON_(explicit) homotype(auto &&...oo)
		{
			generate(XTAL_REF_(oo)...);
		}

		template <size_type N_limit=N_data> requires complex_field_q<U_v1> and is_q<scalar_t<U_v1[2]>, U_data>
		XTAL_LET generate(U_v1 const &u1, U_v2 const &u2)
		XTAL_0EX -> T &
		{
			auto &s = self();

			using W1  = U_v1;
			using U2  = scalar_t<U_v2[2]>;
			using W1_ = series_t<W1[N_data<<1]>;
			using U2_ = series_t<U2[N_data<<1]>;
			static_assert(sizeof(W1_) == sizeof(U2_));
			
			reinterpret_cast<W1_ &>(self()).template generate<N_data, 0, 2, 0>(u1);
			reinterpret_cast<U2_ &>(self()).template generate<N_data, 0, 2, 1>({u2, _op::template root_f<-1>(u2)});
			bond::seek_forward_f<N_data>([&, this] (auto I) XTAL_0FN {
				auto const &[o, e] = get<I>(s);
				let(I) = {o*e.real(), _std::conj(o)*e.imag()};
			});
			return self();
		}
		///\returns `this` with the elements `N_index, ..., N_index + N_limit - 1` \
			filled by the corresponding powers of `u`. \

		template <size_type N_limit=N_data, size_type N_index=0, integral_type N_step=1, integral_type N_skip=0>
		XTAL_LET generate(U_data const &u)
		XTAL_0EX -> T &
		{
		//	auto &s = self();

			using I = typename S_::difference_type;

			XTAL_LET N_shift = _op::bit_ceiling_f(N_step);
			static_assert(N_step == 1 << N_shift);

		//	Compute the start- and end-points for the required segment:
			I constexpr I0 = N_skip + N_step*(N_index +             0 );
			I constexpr I1 = N_skip + N_step*(N_index +             1 );
			I constexpr IM = N_skip + N_step*(N_index + (N_limit >> 1));
			I constexpr IN = N_skip + N_step*(N_index + (N_limit  - 1));
			I constexpr M_skip = N_step - N_skip;

		//	Compute and populate the 0th and 1st powers:
			auto const o = _op::template explo_f<N_index>(u);
			let(I0) = o;
			let(I1) = o*u;

			for (I i = I1; i < IM; i += N_step) {
				auto w = _op::square_f(let(i));
			
			//	Use the square of the previous value to populate the values at `i << 1`:
				I ii = i << 1;
				let(ii - N_skip) = w;
				let(ii + M_skip) = w*u;
			}
		//	Compute the final value if `N_limit` is odd:
			if constexpr (N_limit&1) {
				let(IN) = let(IN - N_step)*(u);
			}
			return self();
		}

		///\returns `this` as the complex sinusoid with length `2*PI*std::pow(2, N_shift)`,  `-3 <= N_shift`. \
		
		///\note\
		To generate the FFT basis used by `transform` etc, use `N_shift == -1`. \

		template <int N_shift=0> requires complex_field_q<U_data>
		XTAL_LET generate()
		XTAL_0EX -> T &
		{
		//	Initialize the forwards and backwards iterators:
			auto const i = S_::begin();
			auto const j = S_::rend() - 1;
			
		//	Compute the fractional sinusoid for this `N_data`:
			auto constexpr x = _op::patio_f(-1, N_data);
			auto const     y = _op::circle_f(x);// TODO: Make `constexpr`?
			
		//	Compute the initial `1/8`th then mirror the remaining segments:
			typename S_::difference_type constexpr M = N_data >> 2;// `1/8`th
			static_assert(-4 <  N_shift);
			generate<M + (-3 <  N_shift)>(y);
			if constexpr (-2 <= N_shift) _detail::copy_to(_std::prev(j, 2*M), _std::span(i, _std::next(i, 1*M)), [] (U_data const &v) XTAL_0FN_(U_data {-v.imag(), -v.real()}));
			if constexpr (-1 <= N_shift) _detail::copy_to(_std::next(i, 2*M), _std::span(i, _std::next(i, 2*M)), [] (U_data const &v) XTAL_0FN_(U_data { v.imag(), -v.real()}));
			if constexpr (-0 <= N_shift) _detail::copy_to(_std::next(i, 4*M), _std::span(i, _std::next(i, 4*M)), [] (U_data const &v) XTAL_0FN_(U_data {-v.real(), -v.imag()}));
			static_assert( 0 >= N_shift);// TODO: Extend to allow multiple copies using `bond::seek`.
			
			return self();
		}
		
		///\returns `that` transformed by the FFT, using `this` as the Fourier basis. \
		
		///\note\
		The size of both `this` and `that` must be expressible as an integral power of two, \
		and `1 < that.size() <= this->size()`. \

		template <int N_direction=1, isomorphic_q<T> Y0>
			requires sign_p<N_direction, 1> and complex_field_q<U_data>
		XTAL_LET transform(Y0 &&that)
		XTAL_0FX -> decltype(auto)
		{
			using Y = based_t<Y0>;
			using I = typename Y::difference_type;
		
		//	Ensure the size of both domain and codomain are powers of two:
			I constexpr N_width = N_data;
			I const     n_width = that.size();
			I const     h_width = n_width >> 1; assert(1 <= h_width);
			I const     n_depth = bond::operate<I>::bit_floor_f(n_width); assert(n_width == I{1} << n_depth);
			I constexpr N_depth = bond::operate<I>::bit_floor_f(N_width); assert(n_depth         <= N_depth);

		//	Move all entries to their bit-reversed locations:
			for (I h{}; h < h_width; ++h) {
				_std::swap(that[h], that[bond::operate<I>::bit_reverse_f(h, n_depth)]);
			}
		
		//	Conjugate the input if computing the inverse transform of the codomain:
			if constexpr (N_direction == -1) {
				_detail::apply_to(that, [] XTAL_1FN_(_std::conj));
			}
		//	Compute the transform of `that` using the precomputed half-period sinusoid in `this`:
			for (I n{}; n < n_depth; ++n) {
				I const  u_width = I{1} << n;
				I const  w_width = u_width << 1;
				I const un_depth = N_depth  - n;
				for (I u{ }; u < u_width; u +=       1) {auto const &o = let(u << un_depth);
				for (I w{u}; w < n_width; w += w_width) {
					auto const m = w + u_width;
					U_data &y = that[m];
					U_data &x = that[w];
					U_data const yo = y*o;
					y = x - yo;
					x = x + yo;
				}}
			}
		//	Conjugate and scale the output if computing the inverse transform of the codomain:
			if constexpr (N_direction == -1) {
				_detail::apply_to(that, [=] XTAL_1FN_(_std::conj));
				that /= n_width;
			}
		
		//	Cast the output to the transformed domain:
			return fudge_f<typename Y::transverse::type>(that);
		}


		///\returns a new `series` representing the FFT of `lhs`, \
		using `this` as the Fourier basis. \

		template <int N_direction=1, isomorphic_q<T> Y0>
			requires sign_p<N_direction, 1>
		XTAL_DEF_(return,inline)
		XTAL_LET transformation(Y0 y0)
		XTAL_0FX -> decltype(auto)
		{
			return transform<N_direction>(XTAL_MOV_(y0));
		}

		///\returns `lhs` convolved with `rhs`, \
		using `this` as the Fourier basis. \

		template <isomorphic_q<T> Y0, is_q<Y0> Y1>
		XTAL_LET convolve(Y0 &&y0, Y1 y1)
		XTAL_0FX -> decltype(auto)
		{
			return transform<-1>(transform<1>(XTAL_REF_(y0)) *= transform<1>(y1));
		}
		///\returns a new `series` representing the convolution of `y0` with `y1`, \
		using `this` as the Fourier basis. \

		template <isomorphic_q<T> Y0, is_q<Y0> Y1>
		XTAL_DEF_(return,inline)
		XTAL_LET convolution(Y0 y0, Y1 const &y1)
		XTAL_0FX -> Y0
		{
			return convolve(XTAL_MOV_(y0), y1);
		}

		///\
		Multiplication by circular convolution. \

		using S_::operator*=;

		XTAL_DEF_(return,inline) XTAL_LET operator * (auto       const &w) XTAL_0FX        {return twin() *=   w ;}
		XTAL_DEF_(inline)        XTAL_LET operator *=(embrace_t<U_data> w) XTAL_0EX -> T & {return self() *= T(w);}

	//	XTAL_DEF_(inline)
		XTAL_LET operator *=(T const &t)
		XTAL_0EX -> T &
		{
			auto &s = self();
			if constexpr (complex_field_q<U_data>) {
				T(nominal_t<-1>{}).convolve(s, t);
			}
			else {
				using X = typename _op::aphex_type;
				using Y = typename series<X>::type;
				Y s_(s);
				Y t_(t);
				Y(nominal_t<-1>{}).convolve(s_, t_);
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
