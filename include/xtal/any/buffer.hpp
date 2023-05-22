#pragma once
#include "./any.hpp"
#include "./realize.hpp"
#include "./iterate.hpp"




XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <delta_t N=-1>
struct buffer
{
	template <typename S>
	class subtype: public S
	{
		using co = S;
	public:
		using co::co;

		template <typename U>
		requires (0 < N)
		struct scalar
		{
		//	TODO: Specialize the appropriate types so that e.g. `std::apply` works. \

		//	TODO: Specialize `field` to match `buffer_scalar_t<alpha_q>`. \
		
		//	TODO: Reify `buffer_scalar_t<2, U>` with even/odd semantics, \
			e.g. stereo or mid-side signals, and results like `exp(+x), exp(-x)` or `cosh(x), sinh(x)`, \
			and define the operations to interconvert them. \

		//	TODO: Reify `buffer_scalar_t<2, U>` with `std::complex` semantics, \
			and define componentwise multiplication either by: \
			-	using `std::bit_cast<scalar_t<U>>` \
			-	defining a non-summing companion to `dot` e.g. `zot` \
			-	supplying real and imaginary projections with a range interface \

			using archetype = _std::array<U, N>;// Hmmm...

			template <typename T>
			class heterotype: public archetype
			{
				using co = archetype;

			public:
				using co::co;
				using co::end;
				using co::begin;

				///\
				Replace the contents of `this` with the given range. \

				template <iterator_q I>
				requires is_q<iteratee_t<I>, U>
				XTAL_FN1_(void) refill(I &&i0, I &&iN)
				{
					assert(N == _std::distance(i0, iN));
					copy_linear_f(false, co::begin(), XTAL_FWD_(I) (i0), XTAL_FWD_(I) (iN));
				}
				template <iterated_q I>
				requires is_q<iteratee_t<I>, U>
				XTAL_FN1_(void) refill(I &&in)
				{
					refill(in.begin(), in.end());
				}

				///\
				Span constructor. \
				Initializes `this` with the values between `i0` and `iN`. \

				template <iterator_q I>
				XTAL_NEW heterotype(I &&i0, I &&iN)
				{
					refill(XTAL_FWD_(I) (i0), XTAL_FWD_(I) (iN));
				}

				///\
				List constructor. \
				Initializes `this` with the given values. \

				template <iterated_q I>
				XTAL_NEW heterotype(I &&in)
				{
					refill(XTAL_FWD_(I) (in));
				}
				XTAL_NEW heterotype(bracket_t<U> in)
				:	heterotype(in.begin(), in.end())
				{
				}

				///\
				List assignment. \
				Replaces the contents of `this` with the given values. \

				XTAL_OP1 = (bracket_t<U> w)
				{
					refill(w.begin(), w.end());
					return *this;
				}

				///\
				Copy constructor. \
				Initializes `this` with the given vector. \

				XTAL_NEW heterotype(heterotype const &t)
				:	heterotype(t.begin(), t.end())
				{
				}
				///\
				Copy assigment. \
				Replaces the contents of `this` with the given vector. \

				XTAL_OP1 = (heterotype const &t)
				{
					refill(t.begin(), t.end());
					return *this;
				}

				///\
				Move constructor. \
				Initializes `this` with the given vector. \

				XTAL_NEW heterotype(heterotype &&t)
				:	heterotype(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()))
				{
				}
				///\
				Move assigment. \
				Replaces the contents of `this` with the given vector. \

				XTAL_OP1 = (heterotype &&t)
				{
					refill(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()));
					return *this;
				}

				///\
				Read accessor. \

				XTAL_FN2 get() XTAL_0FX_(&) {return static_cast<T const &>(*this);}
				XTAL_FN2 get() XTAL_0EX_(&) {return static_cast<T       &>(*this);}
				XTAL_RE2_(XTAL_FN2 get(XTAL_DEF i), get()[XTAL_REF_(i)]);

				///\
				Elementwise transformer. \

				XTAL_FN1 transmute(XTAL_DEF_(_std::invocable<U>) f)
				XTAL_0EX
				{
					/*/
					[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) = f(get(Ns))), ..., U()) (seek_v<N>);
					/*/
					move_linear_f(false, begin(), get(), XTAL_REF_(f));
					/***/
					return get();
				}
				
				///\
				Elementwise comparators. \

			//	XTAL_OP2        <=> (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=> t.get(Ns)) <=>...         ) (seek_v<N>);}
				XTAL_OP2_(bool) ==  (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ==  t.get(Ns)) and ...and true) (seek_v<N>);}
				XTAL_OP2_(bool) <=  (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=  t.get(Ns)) and ...and true) (seek_v<N>);}
				XTAL_OP2_(bool) >=  (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >=  t.get(Ns)) and ...and true) (seek_v<N>);}
				XTAL_OP2_(bool) <   (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <   t.get(Ns)) and ...and true) (seek_v<N>);}
				XTAL_OP2_(bool) >   (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >   t.get(Ns)) and ...and true) (seek_v<N>);}

			};				
			template <typename T>
			class homotype;

			template <typename T>
			requires iota_q<U>
			class homotype<T>: public heterotype<T>
			{
				using co = heterotype<T>;

			public:
				using co::co;
				using co::get;

				XTAL_OP2_(T ) &            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r &= XTAL_REF_(w);}
				XTAL_OP2_(T ) |            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r |= XTAL_REF_(w);}
				XTAL_OP2_(T ) ^            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r ^= XTAL_REF_(w);}
				XTAL_OP2_(T ) +            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r += XTAL_REF_(w);}
				XTAL_OP2_(T ) -            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r -= XTAL_REF_(w);}

				XTAL_OP1_(T&) &=       (bracket_t<U> w) XTAL_0EX {return get() &= T(w.begin(), w.end());}
				XTAL_OP1_(T&) |=       (bracket_t<U> w) XTAL_0EX {return get() |= T(w.begin(), w.end());}
				XTAL_OP1_(T&) ^=       (bracket_t<U> w) XTAL_0EX {return get() ^= T(w.begin(), w.end());}
				XTAL_OP1_(T&) +=       (bracket_t<U> w) XTAL_0EX {return get() += T(w.begin(), w.end());}
				XTAL_OP1_(T&) -=       (bracket_t<U> w) XTAL_0EX {return get() -= T(w.begin(), w.end());}
				
				XTAL_OP1_(T&) &=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) &= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) |=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) |= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) ^=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ^= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) +=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) -=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				
				XTAL_OP1_(T&) &= (XTAL_DEF_(to_q<U>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) &= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) |= (XTAL_DEF_(to_q<U>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) |= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) ^= (XTAL_DEF_(to_q<U>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ^= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) += (XTAL_DEF_(to_q<U>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) -= (XTAL_DEF_(to_q<U>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}

				XTAL_OP1_(T&) ++                     () XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_(++get(Ns), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) --                     () XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_(--get(Ns), ..., get()) (seek_v<N>); return get();}

			};
			template <typename T>
			requires field_q<U>
			class homotype<T>: public heterotype<T>
			{
				using co = heterotype<T>;

			public:
				using co::co;
				using co::get;

				XTAL_OP2_(T ) *            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r *= XTAL_REF_(w);}
				XTAL_OP2_(T ) /            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r /= XTAL_REF_(w);}
				XTAL_OP2_(T ) %            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r %= XTAL_REF_(w);}
				XTAL_OP2_(T ) +            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r += XTAL_REF_(w);}
				XTAL_OP2_(T ) -            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r -= XTAL_REF_(w);}

				XTAL_OP1_(T&) *=       (bracket_t<U> w) XTAL_0EX {return get() *= T(w.begin(), w.end());}
				XTAL_OP1_(T&) /=       (bracket_t<U> w) XTAL_0EX {return get() /= T(w.begin(), w.end());}
				XTAL_OP1_(T&) %=       (bracket_t<U> w) XTAL_0EX {return get() %= T(w.begin(), w.end());}
				XTAL_OP1_(T&) +=       (bracket_t<U> w) XTAL_0EX {return get() += T(w.begin(), w.end());}
				XTAL_OP1_(T&) -=       (bracket_t<U> w) XTAL_0EX {return get() -= T(w.begin(), w.end());}
				
				XTAL_OP1_(T&) *=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) *= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) /=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) /= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) %=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) %= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) +=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) -=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				
				XTAL_OP1_(T&) *= (XTAL_DEF_(to_q<U>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) *= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) /= (XTAL_DEF_(to_q<U>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) /= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) %= (XTAL_DEF_(to_q<U>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) %= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) += (XTAL_DEF_(to_q<U>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) -= (XTAL_DEF_(to_q<U>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}

			//	XTAL_OP2_(T) ~ ()
			//	XTAL_0FX
			//	requires (N == 2)
			//	{
			//		auto const x = get(0) + get(1);
			//		auto const y = get(0) - get(1);
			//		return T{x, y};//*realize<U>::SQRT_HALF;
			//	}
				
			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};

		};
		template <typename U>
		requires (0 < N)
		struct series
		{
			template <typename T>
			using heterotype = typename scalar<U>::template homotype<T>;

			template <typename T>
			class homotype;

			template <typename T>
			requires field_q<U>
			class homotype<T>: public heterotype<T>
			{
				using co = heterotype<T>;
			public:
				using co::co;
				using co::get;

				///\
				Initializing constructor. \

				XTAL_NEW_(explicit) homotype(bool const& basis)
				:	co()
				{
					if (basis) generate();
				}
				///\
				Initializing constructor. \

				XTAL_NEW_(explicit) homotype(U &&u)
				{
					generate(_std::move(u));
				}
				///\
				Initializing constructor. \

				XTAL_NEW_(explicit) homotype(U const &u)
				{
					generate(u);
				}

				///\returns `this` with the elements `N_index, ..., N_index + N_limit - 1` \
					filled by the corresponding powers of `u`. \

				///\note This algorithm uses squaring, \
					which is more precise/efficient than multiplication for complex numbers. \

				template <sigma_t N_limit=N, sigma_t N_index=0>
				XTAL_FN1_(T&) generate(U const &u)
				XTAL_0EX
				{
					auto &s = get();
					auto constexpr H_limit = N_limit >> 1; static_assert(0 < H_limit);
					auto constexpr _0 = N_index + 0;
					auto constexpr _1 = N_index + 1;
					auto constexpr _H = N_index + H_limit;
					auto constexpr N1 = N_index + N_limit - 1;
					auto constexpr N2 = N_index + N_limit - 2;
					auto const      o = realized::explo_y(N_index, u);
					s[_0] = o;
					s[_1] = o*u;
					for (sigma_t i = _1; i < _H; ++i)
					{
						auto w = square_y(s[i]);
						auto h = i << 1;
						s[h] = w;
						h   += 1;
						w   *= u;
						s[h] = w;
					}
					if constexpr (N_limit&1)
					{
						s[N1] = s[N2]*u;
					}
					return s;
				}

				///\returns `this` as the Fourier basis used by `transform` etc, \
				comprising `N` values of the half-period complex sinusoid.

				///\note Only the first eighth-period is computed, \
				then mirrored to complete the quarter and half respectively. \

				XTAL_FN1_(T&) generate()
				XTAL_0EX
				requires complex_q<U> and bit_ceiling_q<N, 2>
				{
					auto &s = get();
					auto constexpr x = realized::patio_y<-1> (N);
					auto constexpr L = N >> 2;
					auto const  i0 =         s.begin(), i1 = _std::next(i0, 1);
					auto const  j0 = _std::next(i0, L), j1 = _std::next(j0, 1);
					auto const  k0 = _std::next(j0, L), k1 = _std::next(k0, 1);
					auto const _k1 = _std::make_reverse_iterator(k1);
					generate<L + 1> (arc_y<U>(x));
					copy_linear_f(false, _k1, _std::span(i0, j0), [] (U const &v) XTAL_0FN_(U(-v.imag(), -v.real())));
					copy_linear_f(false,  k1, _std::span(i1, k1), [] (U const &v) XTAL_0FN_(U( v.imag(), -v.real())));
					return s;
				}
				
				///\returns `that` transformed by the FFT, \
				using `this` as the Fourier basis. \

				template <delta_t N_rotate=0>
				XTAL_FN1_(T&) transform(T &that)
				XTAL_0EX
				requires bit_ceiling_q<N, 1>
				{
					sigma_t constexpr H = N >> 1;
					sigma_t constexpr K = bit_ceiling_y(N);

					auto const &o = get();
					for (sigma_t h = 0; h < H; ++h)
					{
						_std::swap(that[h], that[bit_reverse_y<K>(h)]);
					}
					if constexpr (N_rotate&1)
					{
						that.transmute([] (U u) XTAL_0FN_(_std::conj(u)));
					}
					for (sigma_t k = 0; k < K; ++k)
					{
						sigma_t const kn = K - k;
						sigma_t const u = 1 << k;
						sigma_t const w = u << 1;
						for (sigma_t                 i = 0; i < u; i += 1)
						for (sigma_t kn_i = i << kn, j = i; j < N; j += w)
						{
							U const y = that[j + u]*o[kn_i];
							U const x = that[j + 0];
							that[j + u] = x - y;
							that[j + 0] = x + y;
						}
					}
					if constexpr (N_rotate&1)
					{
						that.transmute([] (U u) XTAL_0FN_(_std::conj(u*realized::ratio_y<1>(N))));
					}
					return that;
				}
				///\returns a new `series` representing the FFT of `lhs`, \
				using `this` as the Fourier basis. \

				template <delta_t N_rotate=0>
				XTAL_FN1_(T) transformation(T lhs)
				XTAL_0EX
				{
					return transform(lhs);
				}

				///\returns `lhs` convolved with `rhs`, \
				using `this` as the Fourier basis. \

				template <delta_t N_rotate=0>
				XTAL_FN1_(T) convolve(T &lhs, T rhs)
				XTAL_0EX
				{
					transform(lhs);
					transform(rhs);
					transform<-1>(lhs *= rhs);
					return lhs;
				}
				///\returns a new `series` representing the convolution of `lhs` with `rhs`, \
				using `this` as the Fourier basis. \

				template <delta_t N_rotate=0>
				XTAL_FN1_(T) convolution(T lhs, T const &rhs)
				XTAL_0EX
				{
					return convolve(lhs, rhs);
				}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		template <typename V>
		struct vector
		{
			using A = _std::aligned_storage_t<sizeof(V), alignof(V)>;

			template <typename T>
			using heterotype = iterate_t<T>;

			template <typename T>
			class homotype: public heterotype<T>
			{
				using co = heterotype<T>;

				template <typename I>
				XTAL_FZ2_(I) appointed_f(XTAL_DEF i) XTAL_0EX {return _std::launder(reinterpret_cast<I>(XTAL_REF_(i)));}
				XTAL_FZ2     appointee_f(V       *i) XTAL_0EX {return appointed_f<A       *>(i);}
				XTAL_FZ2     appointee_f(V const *i) XTAL_0EX {return appointed_f<A const *>(i);}
				XTAL_FZ2     appointer_f(A       *i) XTAL_0EX {return appointed_f<V       *>(i);}
				XTAL_FZ2     appointer_f(A const *i) XTAL_0EX {return appointed_f<V const *>(i);}
				XTAL_FZ2   reappointer_f(XTAL_DEF i) XTAL_0EX {return _std::make_reverse_iterator(appointer_f(XTAL_REF_(i)));}

				A  block_m[N];
				A* index_m = block_m;

			public:
				XTAL_FN2 get() XTAL_0FX_(&) {return static_cast<T const &>(*this);}
				XTAL_FN2 get() XTAL_0EX_(&) {return static_cast<T       &>(*this);}
				XTAL_RE4_(XTAL_FN2 get(XTAL_DEF i), get()[XTAL_REF_(i)]);

			//	using co;
				using co::size;

				using             value_type = V;
				using         allocator_type = T;

				using              size_type = sigma_t;
				using        difference_type = delta_t;

				using              reference = value_type       &;
				using        const_reference = value_type const &;
				
				using                pointer = value_type       *;
				using          const_pointer = value_type const *;

				using               iterator = value_type       *;
				using         const_iterator = value_type const *;
				
				using       reverse_iterator = _std::reverse_iterator<      iterator>;
				using const_reverse_iterator = _std::reverse_iterator<const_iterator>;
				
				XTAL_RE4_(XTAL_OP2[] (size_type i), *appointer_f(block_m + i));
				XTAL_RE4_(XTAL_OP2() (size_type i),  appointer_f(block_m + i));

				XTAL_RE4_(XTAL_FN2 rbegin(), reappointer_f(index_m));
				XTAL_RE4_(XTAL_FN2  begin(),   appointer_f(block_m));
				XTAL_RE4_(XTAL_FN2   rend(), reappointer_f(block_m));
				XTAL_RE4_(XTAL_FN2    end(),   appointer_f(index_m));
				
				XTAL_FN2 crbegin() XTAL_0FX {return rbegin();}
				XTAL_FN2  cbegin() XTAL_0FX {return  begin();}
				XTAL_FN2   crend() XTAL_0FX {return   rend();}
				XTAL_FN2    cend() XTAL_0FX {return    end();}

				XTAL_RE4_(XTAL_FN2 data(), begin());

				///\
				Clear destructor. \

				~homotype()
				{
					clear();
				}
				///\
				Default constructor. \

				homotype() noexcept = default;

				///\
				Insert constructor. \
				Initializes `this` with `sN` values determined by the given arguments. \

				XTAL_NEW_(explicit) homotype(size_type sN, XTAL_DEF ...ws)
				{
					insert_back(sN, XTAL_REF_(ws)...);
				}

				///\
				Span constructor. \
				Initializes `this` with the values between `i0` and `iN`. \

				template <iterator_q I0, iterator_q IN>
				requires is_q<iteratee_t<I0>, iteratee_t<IN>, V>// and to_q<iteratee_t<IN>, V>
				XTAL_NEW_(explicit) homotype(I0 i0, IN iN)
				{
					using I = _std::common_type_t<I0, IN>;
					I i0_ = i0;
					I iN_ = iN;
					insert_back(i0_, iN_);
				}

				///\
				List constructor. \
				Initializes `this` with the given values. \

				XTAL_NEW_(explicit) homotype(bracket_t<V> etc)
				:	homotype(etc.begin(), etc.end())
				{
				}
				///\
				List assignment. \
				Replaces the contents of `this` with the given values. \

				XTAL_OP1 = (bracket_t<V> etc)
				{
					refill(etc.begin(), etc.end());
					return get();
				}

				///\
				Copy constructor. \
				Initializes `this` with the given vector. \

				XTAL_NEW homotype(homotype const &t)
				:	homotype(t.begin(), t.end())
				{
				}
				///\
				Copy assigment. \
				Replaces the contents of `this` with the given vector. \

				XTAL_OP1 = (homotype const &t)
				{
					refill(t.begin(), t.end());
					return get();
				}

				///\
				Move constructor. \
				Initializes `this` with the given vector. \

				XTAL_NEW homotype(homotype &&t)
				:	homotype(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()))
				{
				}
				///\
				Move assigment. \
				Replaces the contents of `this` with the given vector. \

				XTAL_OP1 = (homotype &&t)
				{
					refill(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()));
					return get();
				}

				///\
				Swaps the contents of `this` with the given vector. \

				XTAL_FN1_(void) swap(T &t)
			//	requires _std::swappable<V>
				{
					_std::swap_ranges(begin(), end(), t.begin());
				}

				///\
				\returns the fixed capacity `N` of the `vector`. \

				XTAL_FN2_(size_type) capacity()
				XTAL_0EX
				{
					return N;
				}

				///\
				Allocates and initializes `sN` elements at the end of the vector. \

				XTAL_FN2_(iterator) allocate(size_type sN)
				{
					return insert_back(sN);
				}

				///\
				Deletes the elements from `i0` to `end()`. \

				template <is_q<iterator> I0>
				XTAL_FN1_(void) deallocate(I0 i0)
				XTAL_0EX
				{
					erase(i0, end());
				}

				///\
				Deletes all elements. \

				XTAL_FN1_(void) clear()
				XTAL_0EX
				{
					erase(begin(), end());
				}

				///\
				Deletes the element at `i0`. \

				template <is_q<iterator> I0>
				XTAL_FN1_(void) erase(I0 i0)
				XTAL_0EX
				{
					erase(i0, size_type(1));
				}
				///\
				Deletes `sN` elements starting from `i0`. \

				template <is_q<iterator> I0>
				XTAL_FN1_(void) erase(I0 i0, size_type sN)
				XTAL_0EX
				{
					erase(i0, _v3::ranges::next(i0, sN), sN);
				}
				///\
				Deletes the elements between `i0` and `iN`. \

				template <is_q<iterator> I0, is_q<iterator> IN>
				XTAL_FN1_(void) erase(I0 i0, IN iN)
				XTAL_0EX
				{
					using I = _std::common_type_t<I0, IN>;
					I i0_ = i0;
					I iN_ = iN;
					erase(i0_, iN_, _std::distance(i0_, iN_));
				}
				///\
				Deletes `sN` elements between `i0` and `iN`. \

				template <is_q<iterator> I0, is_q<iterator> IN>
				XTAL_FN1_(void) erase(I0 i0, IN iN, size_type sN)
				XTAL_0EX
				{
					using I = _std::common_type_t<I0, IN>;
					I i0_ = i0;
					I iN_ = iN;
					erode(i0_, iN_, sN);
				}

				///\
				Does nothing. \

				XTAL_FN1_(void) shrink_to_fit()
				XTAL_0EX
				{
				}

				///\
				Does nothing besides `throw std::bad_alloc` if the required `sN` exceeds the maximum `N`. \

				XTAL_FN1_(void) reserve(size_type sN)
				{
					if (N < sN)
					{
						throw _std::bad_alloc {};
					}
				}

				///\
				Resizes `this` to `sN` elements. \
				Invokes `insert_back` with the given arguments to extend the vector if required. \

				XTAL_FN1_(void) resize(size_type sN, XTAL_DEF ...ws)
				{
					size_type const sM = size();
					if (sN < sM)
					{
						pop_back(sM - sN);
					}
					else
					{
						insert_back(sN - sM, XTAL_REF_(ws)...);
					}
				}

				///\
				Clears `this` and invokes `insert_back` with the given arguments. \

				XTAL_FN1_(void) refill(XTAL_DEF ...ws)
				{
					clear();
					insert_back(XTAL_REF_(ws)...);
				}

				///\
				Removes the last element from `this`. \

				XTAL_FN1_(void) pop_back()
				{
					pop_back(size_type(1));
				}
				///\
				Removes the last `sN` elements from `this`. \

				XTAL_FN1_(void) pop_back(size_type sN)
				{
					deallocate(end() - sN);
				}

				///\
				Inserts the values `etc` beginning at `i0`. \

				XTAL_FN1_(void) push_back(bracket_t<V> etc)
				{
					insert_back(etc.begin(), etc.end());
				}
				///\
				Inserts the values `etc...` beginning at `i0`. \

				XTAL_FN1_(void) push_back(XTAL_DEF_(to_q<V>) ...etc)
				{
					push_back(bracket_t<V>{V(XTAL_REF_(etc))...});
				}

				///\
				Constructs an element at the end of `this` using the given arguments. \
				\returns a reference to the element.

				XTAL_FN1_(reference) emplace_back(XTAL_DEF ...ws)
				{
					return *inplace_back(XTAL_REF_(ws)...);
				}
				///\
				Constructs an element at the end of `this` using the given arguments. \
				\returns a pointer to the element.

				XTAL_FN1_(iterator) inplace_back(XTAL_DEF ...ws)
				{
					reserve(size_type(1) + size());
					return ::new (index_m++) V(XTAL_REF_(ws)...);
				}

				///\
				Invokes `insert` at `this->end()` with the given arguments. \

				XTAL_FN1_(iterator) insert_back(XTAL_DEF ...ws)
				{
					return insert(end(), XTAL_REF_(ws)...);
				}

				///\
				Inserts the values delimited by `j0` and `jN` beginning at `i`. \

				template <is_q<iterator> I, iterator_q J0, iterator_q JN>
				XTAL_FN1_(iterator) insert(I i, J0 j0, JN jN)
				{
					using J = _std::common_type_t<J0, JN>;
					J j0_ = j0;
					J jN_ = jN;
					inject(i, _std::distance(j0_, jN_));
					copy_linear_f(false, i, j0_, jN_);
					return i;
				}

				///\
				Inserts the values `etc` beginning at `i`. \

				template <is_q<iterator> I>
				XTAL_FN1_(iterator) insert(I i, bracket_t<V> etc)
				{
					return insert(i, etc.begin(), etc.end());
				}

				///\
				Initialises `sN` values with `v` beginning at `i`. \

				template <is_q<iterator> I>
				XTAL_FN1_(iterator) insert(I i, size_type sN, V const &v)
				{
					inject(i, sN);
					_std::uninitialized_fill_n(i, sN, v);
					return i;
				}
				template <is_q<iterator> I>
				XTAL_FN1_(iterator) insert(I i, size_type sN, V &&v)
				{
					inject(i, sN);
					_std::uninitialized_fill_n(i, sN, _std::move(v));
					return i;
				}

				///\
				Initialises `sN` values beginning at `i`. \

				template <is_q<iterator> I>
				XTAL_FN1_(iterator) insert(I i, size_type sN)
				{
					inject(i, sN);
					_std::uninitialized_value_construct_n(i, sN);
					return i;
				}
				
			protected:
				///\
				Allocates `sN` elements beginning at `i`. \

				template <is_q<iterator> I>
				XTAL_FN1_(iterator) inject(I i, size_type sN)
				{
					reserve(sN + size());
					if (i < end())// and _std::move_constructible<V>)
					{
						auto j = reappointer_f(index_m);
						move_linear_f(true, _v3::ranges::prev(j, sN), j, _v3::ranges::next(j, sN));
					}
					else
					{
						assert(i == end());
					}
					index_m += sN;
					return i;
				}

				///\
				Deletes `sN` elements between `i0` and `iN`. \

				template <is_q<iterator> I0, is_q<iterator> IN>
				XTAL_FN1_(void) erode(I0 i0, IN iN, size_type sN)
				XTAL_0EX
				{
					using I = _std::common_type_t<I0, IN>;
					I i0_ = i0;
					I iN_ = iN;
					I begin_m = begin(), end_m = end();
					assert(begin_m <= i0_ and iN_ <= end_m and _std::distance(i0_, iN_) == sN);
					if constexpr (_std::destructible<V>)
					{
						_std::destroy(i0_, iN_);
					}
					if (iN_ < end_m)// and _std::move_constructible<V>)
					{
						auto jN = appointee_f(iN_);
						auto j0 = appointee_f(i0_);
						move_linear_f(sN <= _std::distance(jN, index_m), j0, jN, index_m);
					}
					else
					{
						assert(end_m == iN_);
					}
					index_m -= sN;
				}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		template <typename V>
		requires (N < 0)
		struct vector<V>
		{
			using type = _std::vector<V>;

		};

		template <typename U>
		using scalar_t = typename scalar<U>::type;

		template <typename U>
		using series_t = typename series<U>::type;

		template <typename V>
		using vector_t = typename vector<V>::type;

		template <typename V>
		using funnel_t = _std::priority_queue<V, vector_t<V>, _std::greater<V>>;

		template <typename V>
		using allocator_t = typename vector_t<V>::allocator_type;

	};
	using type = subtype<construct_t<>>;

};

template <delta_t N=-1>
using buffer_t = typename buffer<N>::type;

template <delta_t N=-1, typename U=alpha_t>
using buffer_scalar_t = typename buffer_t<N>::template scalar_t<U>;

template <delta_t N=-1, typename U=alpha_t>
using buffer_series_t = typename buffer_t<N>::template series_t<U>;

template <delta_t N=-1, typename V=alpha_t>
using buffer_vector_t = typename buffer_t<N>::template vector_t<V>;

template <delta_t N=-1, typename V=alpha_t>
using buffer_funnel_t = typename buffer_t<N>::template funnel_t<V>;

template <delta_t N=-1, typename V=alpha_t>
using buffer_allocator_t = typename buffer_t<N>::template allocator_t<V>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
