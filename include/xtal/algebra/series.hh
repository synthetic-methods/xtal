#pragma once
#include "./any.hh"
#include "./serial.hh"
#include "./lateral.hh"




XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	struct   series;
template <class   ..._s>	using    series_t = typename series<_s...>::type;
template <class   ...Ts>	concept  series_q = bond::tag_p<series_t, Ts...>;
template <class  V=void>
XTAL_DEF_(short)
XTAL_LET series_f(auto &&...oo)
noexcept -> auto
{
	return _detail::initialize<series_t>::template via<V>(XTAL_REF_(oo)...);
}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `serial` with multiplication defined by circular convolution. \

template <vector_q A>
struct series<A>
{
	using U_v0 = _std::remove_extent_t<A>;
	using U_v1 =  valued_u<U_v0>;
	using U_v2 =  valued_u<U_v1>;

	using _op = bond::operate<A>;
	
	template <class T>
	using endotype = typename serial<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<series_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using  S_ = holotype<T>;

	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:
		using S_::S_;
		using S_::self;
		using S_::twin;

		///\
		Generates part of the complex sinusoid determined by `std::pow(2, o_shift{})`. \

		XTAL_DEF_(inline)
		XTAL_NEW_(explicit) homotype(constant_q auto const o_shift)
		{
			generate<o_shift>();
		}
		///\
		Generates the power series with the given seed. \

		XTAL_DEF_(inline)
		XTAL_NEW_(explicit) homotype(auto &&...oo)
		{
			generate(XTAL_REF_(oo)...);
		}

		//\
		template <size_type N_count=N_data> requires complex_field_q<U_v1> and same_q<lateral_t<U_v1[2]>, U_data>
		template <size_type N_count=N_data> requires complex_field_q<U_v1> and bond::dipack_q<U_data>
		XTAL_DEF_(inline)
		XTAL_LET generate(U_v1 const &u1, U_v2 const &u2)
		noexcept -> T &
		{
			auto &s = self();

			using W1  = U_v1;
			using U2  = lateral_t<U_v2[2]>;
			using W1_ = series_t<W1[N_data<<1U]>;
			using U2_ = series_t<U2[N_data<<1U]>;
			static_assert(sizeof(W1_) == sizeof(U2_));
			
			reinterpret_cast<W1_ &>(self()).template generate<N_data, 0, 2, 0>(u1);
			reinterpret_cast<U2_ &>(self()).template generate<N_data, 0, 2, 1>({u2, _op::template root_f<-1>(u2)});
			bond::seek_forward_f<N_data>([&, this] (auto I) XTAL_0FN {
				auto &[o, e] = get<I>(s);
				auto &[f, g] = destruct_f(e);
				get<I>(s) = {o*f, _std::conj(o)*g};
			});
			return self();
		}
		///\returns `this` with the elements `N_index, ..., N_index + N_count - 1` \
			filled by the corresponding powers of `u`. \

		template <size_type N_count=N_data, size_type N_index=0, ordinal_type N_step=1, ordinal_type N_skip=0>
		XTAL_DEF_(inline)
		XTAL_LET generate(U_data const &u)
		noexcept -> T &
		{
			auto &s = self();

			using A_delta = typename S_::difference_type;
			using A_sigma = typename S_::      size_type;

		//	Compute the start- and end-points for the required segment:
			A_delta constexpr N_limit = N_index + N_count;
			A_delta constexpr _0 =  0*N_step;
			A_delta constexpr _1 =  1*N_step;
			A_delta constexpr _2 =  2*N_step;
			A_delta constexpr U0 = _1*N_index + N_skip, W0 = _2*N_index + N_skip;
			A_delta constexpr UZ = _1*N_limit + N_skip, WZ = _2*N_limit + N_skip;

		//	Populate the 0th and 1st powers:
			auto const o = _op::template explo_f<N_index>(u);
			get<U0 + _0>(s) = o;
			get<U0 + _1>(s) = o*u;

		//	Populate the remaining powers by squaring/multiplication:
			bond::seek_forward_f<(N_count >> 1U)>([&] (auto M)
				XTAL_0FN {
					auto constexpr UM = U0 + _1*M;
					auto constexpr WM = W0 + _2*M;
					
					auto const w = _op::square_f(get<UM>(s));
					get<WM + _0>(s) =   w;
					get<WM + _1>(s) = u*w;
				}
			);
		//	Compute the final value if `N_count` is odd:
			if constexpr ((N_count&1U) and (N_count^1U)) {
				get<UZ - _1>(s) = get<UZ - _2>(s)*(u);
			}
			return self();
		}

		///\returns `this` as the complex sinusoid with length `2*PI*std::pow(2, N_shift)`,  `-3 <= N_shift`. \
		
		///\note\
		To generate the FFT basis used by `transform` etc, use `N_shift == -1`. \

		template <int N_shift=0> requires complex_field_q<U_data>
		XTAL_LET generate()
		noexcept -> T &
		{
			using _std::span;
			using _std::prev;
			using _std::next;

		//	Initialize the forwards and backwards iterators:
			auto const i = S_::begin();
			auto const j = S_::rend() - 1;
			
		//	Compute the fractional sinusoid for this `N_data`:
			auto constexpr x = _op::patio_f(-1, N_data);
			auto const     y = _op::circle_f(x);// TODO: Make `constexpr`?
			
		//	Compute the initial `1/8`th then mirror the remaining segments:
			typename S_::difference_type constexpr M = N_data >> 2U;// `1/8`th
			static_assert(-4 <  N_shift);
			generate<M + (-3 <  N_shift)>(y);
			if constexpr (-2 <= N_shift) _detail::copy_to<[] (U_data const &v) XTAL_0FN_(U_data{-v.imag(), -v.real()})>(prev(j, 2*M), span(i, next(i, 1*M)));
			if constexpr (-1 <= N_shift) _detail::copy_to<[] (U_data const &v) XTAL_0FN_(U_data{ v.imag(), -v.real()})>(next(i, 2*M), span(i, next(i, 2*M)));
			if constexpr (-0 <= N_shift) _detail::copy_to<[] (U_data const &v) XTAL_0FN_(U_data{-v.real(), -v.imag()})>(next(i, 4*M), span(i, next(i, 4*M)));
			static_assert( 0 >= N_shift);// TODO: Extend to allow multiple copies using `bond::seek`.
			
			return self();
		}
		
		///\returns `that` transformed by the FFT, using `this` as the Fourier basis. \
		
		///\note\
		The size of both `this` and `that` must be expressible as an integral power of two, \
		and `1 < that.size() <= this->size()`. \

		template <int N_direction=1> requires in_q<N_direction, 1, -1> and complex_field_q<U_data>
		XTAL_LET transform(isomorphic_q<T> auto &that) const
		noexcept -> decltype(auto)
		{
			using Xs = XTAL_ALL_(that);
			using Ys = typename Xs::transverse::type;
			using I  = typename Xs:: difference_type;
		
		//	Ensure the size of both domain and codomain are powers of two:
			I constexpr N_width = N_data;
			I const     n_width = that.size();
			I const     h_width = n_width >> 1U; assert(1 <= h_width);
			I const     n_depth = bond::operate<I>::bit_floor_f(n_width); assert(n_width == I{1} << n_depth);
			I constexpr N_depth = bond::operate<I>::bit_floor_f(N_width); assert(n_depth         <= N_depth);

		//	Move all entries to their bit-reversed locations:
			for (I h{}; h < h_width; ++h) {
				_std::swap(that[h], that[bond::operate<I>::bit_reverse_f(h, n_depth)]);
			}
		
		//	Conjugate the input if computing the inverse transform of the codomain:
			if constexpr (N_direction == -1) {
				_detail::apply_to<XTAL_FUN_(_std::conj)>(that);
			}
		//	Compute the transform of `that` using the precomputed half-period sinusoid in `this`:
			for (I n{}; n < n_depth; ++n) {
				I const  u_width = I{1} << n;
				I const  w_width = u_width << 1U;
				I const un_depth = N_depth   - n;
				for (I u{ }; u < u_width; u +=     one) {auto const &o = S_::element(u << un_depth);
				for (I w{u}; w < n_width; w += w_width) {
					auto const m = w + u_width;
					U_data &y = that[m];
					U_data &x = that[w];
					U_data const yo = y*o;
					y  = x - yo;
					x +=     yo;
				}}
			}
		//	Conjugate and scale the output if computing the inverse transform of the codomain:
			if constexpr (N_direction == -1) {
				_detail::apply_to<XTAL_FUN_(_std::conj)>(that);
				that /= n_width;
			}

		//	Cast the output to the transformed domain:
			return reinterpret_cast<Ys &>(that);
		}
		template <int N_direction=1> requires in_q<N_direction, 1, -1> and complex_field_q<U_data>
		XTAL_LET transform(isomorphic_q<T> auto &&that) const
		noexcept -> decltype(auto)
		{
			(void) transform<N_direction >(that);
			return reinterpret_cast<typename XTAL_ALL_(that)::transverse::type &&>(that);
		}
		///\returns a new `series` representing the FFT of `that`, \
		using `this` as the Fourier basis. \

		template <int N_direction=1> requires in_q<N_direction, 1, -1>
		XTAL_DEF_(short)
		XTAL_LET transformation(isomorphic_q<T> auto that) const
		noexcept -> auto
		{
			return transform<N_direction>(XTAL_MOV_(that));
		}

		///\returns `lhs` convolved with `rhs`, \
		using `this` as the Fourier basis. \
s
		XTAL_LET convolve(isomorphic_q<T> auto &&y0, XTAL_SYM_(y0) auto y1) const
		noexcept -> decltype(auto)
		{
			return transform<-1>(transform<1>(XTAL_REF_(y0)) *= transform<1>(y1));
		}
		///\returns a new `series` representing the convolution of `y0` with `y1`, \
		using `this` as the Fourier basis. \

		XTAL_DEF_(short)
		XTAL_LET convolution(isomorphic_q<T> auto y0, XTAL_SYM_(y0) auto const &y1) const
		noexcept -> auto
		{
			return convolve(XTAL_MOV_(y0), y1);
		}

		///\
		Multiplication by circular convolution. \

		using S_::operator*=;

		XTAL_DEF_(short) XTAL_LET operator * (auto const &w)              const noexcept -> auto   {return twin() *=   w ;}
		XTAL_DEF_(inline)        XTAL_LET operator *=(_std::initializer_list<U_data> w) noexcept -> auto & {return self() *= T(w);}

	//	XTAL_DEF_(inline)
		XTAL_LET operator *=(T const &t)
		noexcept -> T &
		{
			auto &s = self();
			if constexpr (complex_field_q<U_data>) {
				T(constant_t<-1>{}).convolve(s, t);
			}
			else {
				using X = typename _op::aphex_type;
				using Y = typename series<X[N_data]>::type;
				Y s_(s);
				Y t_(t);
				Y(constant_t<-1>{}).convolve(s_, t_);
				_detail::move_to<XTAL_FUN_(_std::real)>(s.begin(), s_);
			}
			return s;
		}

		///\
		The dual of `T`, defined by `lateral`. \
		
		struct transverse
		{
			template <class R>
			using holotype = typename lateral<A>::template homotype<R>;

			template <class R>
			class homotype : public holotype<R>
			{
				friend R;
				using  R_ = holotype<R>;
			
			public:
				using R_::R_;
				struct transverse {using type = T;};

			};
			using type = bond::isotype<homotype>;

		};
	};
	using type = bond::isotype<homotype>;

};
static_assert(atomic_q<lattice_t<float[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
