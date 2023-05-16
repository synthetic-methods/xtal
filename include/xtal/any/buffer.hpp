#pragma once
#include "./any.hpp"
#include "./collate.hpp"// next





XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <iota_t N=-1>
struct buffer
{
	template <typename S>
	class subtype: public S
	{
		using co = S;
	public:
		using co::co;

		template <typename U>
		XTAL_IF1 positive_q<N>
		struct scalar
		{
		//	TODO: Specialize the appropriate types so that e.g. `std::apply` works. \

		//	TODO: Specialize `field` to match `scalar<alpha_q>`. \
		
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

				///\
				Replace the contents of `this` with the given range. \

				template <iterated_q I>
				XTAL_IF1 is_q<iteratee_t<I>, U>
				XTAL_FN1_(void) refill(I &&in)
				{
					assert(N == _std::size(in));
					refill(in.begin(), in.end());
				}
				template <iterator_q I>
				XTAL_IF1 is_q<iteratee_t<I>, U>
				XTAL_FN1_(void) refill(I &&i0, I &&iN)
				{
					assert(N == _std::distance(i0, iN));
					_std::copy(XTAL_FWD_(I) (i0), XTAL_FWD_(I) (iN), co::begin());
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

				XTAL_OP1 = (bracket_t<U> etc)
				{
					refill(etc.begin(), etc.end());
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
				Elementwise comparators. \

			//	XTAL_OP2        <=> (heterotype const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=> t.get(Ns)) <=>...         ) (seek_v<N>);}
				XTAL_OP2_(bool) ==  (heterotype const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ==  t.get(Ns)) and... and true) (seek_v<N>);}
				XTAL_OP2_(bool) <=  (heterotype const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=  t.get(Ns)) and... and true) (seek_v<N>);}
				XTAL_OP2_(bool) >=  (heterotype const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >=  t.get(Ns)) and... and true) (seek_v<N>);}
				XTAL_OP2_(bool) <   (heterotype const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <   t.get(Ns)) and... and true) (seek_v<N>);}
				XTAL_OP2_(bool) >   (heterotype const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >   t.get(Ns)) and... and true) (seek_v<N>);}

			};				
			template <typename T>
			class homotype;

			template <typename T>
			XTAL_IF1 iota_q<U>
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
				
				XTAL_OP1_(T&) &=           (T const &t) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) &= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) |=           (T const &t) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) |= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) ^=           (T const &t) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ^= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) +=           (T const &t) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) -=           (T const &t) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				
				XTAL_OP1_(T&) &= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) &= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) |= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) |= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) ^= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ^= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) += (XTAL_DEF_(as_q<U>) w) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) -= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}

				XTAL_OP1_(T&) ++                     () XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_(++get(Ns), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) --                     () XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_(--get(Ns), ..., get()) (seek_v<N>); return get();}

			};
			template <typename T>
			XTAL_IF1 field_q<U>
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
				
				XTAL_OP1_(T&) *=           (T const &t) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) *= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) /=           (T const &t) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) /= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) %=           (T const &t) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) %= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) +=           (T const &t) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) -=           (T const &t) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= t.get(Ns)),       ..., get()) (seek_v<N>); return get();}
				
				XTAL_OP1_(T&) *= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) *= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) /= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) /= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) %= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) %= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) += (XTAL_DEF_(as_q<U>) w) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}
				XTAL_OP1_(T&) -= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {[&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= U(XTAL_REF_(w))), ..., get()) (seek_v<N>); return get();}

			//	XTAL_OP2_(T) ~ ()
			//	XTAL_0FX
			//	XTAL_IF1 (N == 2)
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
		XTAL_IF1 positive_q<N>
		struct series
		{
			template <typename T>
			using heterotype = typename scalar<U>::template homotype<T>;

			template <typename T>
			class homotype;

			template <typename T>
			XTAL_IF1 field_q<U>
			class homotype<T>: public heterotype<T>
			{
				using co = heterotype<T>;
			public:
				using co::co;
				using co::get;

				/// Fills `this` with the basis series `{1, u, u*u, u*u*u, ...}`. \

				///\returns `this` for chaining. \

				///\note This algorithm uses squaring, \
				which is more precise/efficient than multiplication for complex numbers. \

				XTAL_FN1_(T&) basis(U const &u, sigma_t const &n = N)
				XTAL_0EX
				{
					auto &s = get();
					s[0] = 1;
					s[1] = u;
					for (sigma_t i = 1; i < n >> 1; ++i)
					{
						auto w = square_y(s[i]);
						auto h = i << 1;
						s[h] = w;
						h   += 1;
						w   *= u;
						s[h] = w;
					}
					if (n&1)
					{
						s[n - 1] = s[n - 2]*u;
					}
					return s;
				}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		template <typename U>
		XTAL_IF1 positive_q<N>
		struct spectra
		{
			template <typename T>
			using heterotype = typename series<U>::template homotype<T>;

			template <typename T>
			class homotype;

			template <typename T>
			XTAL_IF1 field_q<U>
			class homotype<T>: public heterotype<T>
			{
				using co = heterotype<T>;
			public:
				using co::co;
				using co::get;

				/// Fills `this` with the `basis` used by `transform`, \
				comprising `N` values of the half-period complex sinusoid.

				///\returns `this` for chaining. \

				XTAL_FN1_(T&) basis()
				XTAL_0EX
				XTAL_IF1 complex_q<U> and bit_ceiling_q<N, 2>
				{
					auto &s = get();
					auto constexpr L = N >> 2;
					auto constexpr A = realized::patio_y<-1> (N);
					co::basis(arc_y<U>(A), L + 1);
					auto const i0 =  s.begin();
					auto const i1 = _std::next(i0,     1);
					auto const j0 = _std::next(i0, L + 0);
					auto const k1 = _std::next(j0, L + 1);
					auto      _k1 = _std::make_reverse_iterator(k1);
					_std::transform(i0, j0,_k1, [] (U const &v) XTAL_0FN_(U(-v.imag(), -v.real())));
					_std::transform(i1, k1, k1, [] (U const &v) XTAL_0FN_(U( v.imag(), -v.real())));
					return s;
				}
				
				/// Applies the Fourier transform to `this`. \

				///\returns `this` for chaining. \

				XTAL_FN1_(T&) transform()
				XTAL_0EX
				{
					T o; o.basis();
					return this->transform(o);
				}

				/// Applies the Fourier transform to `this`, using a precomputed `basis`. \

				///\returns `this` for chaining. \

				XTAL_FN1_(T&) transform(T const &basis)
				XTAL_0EX
				XTAL_IF1 bit_ceiling_q<N, 1>
				{
					sigma_t constexpr H = N >> 1;
					sigma_t constexpr O = bit_ceiling_y(N);

					auto& s = get();
					for (sigma_t h = 0; h < H; ++h)
					{
						_std::swap(s[h], s[bit_reverse_y<O>(h)]);
					}
					for (sigma_t o = 0; o < O; ++o)
					{
						sigma_t const on = O - o;
						sigma_t const u = 1 << o;
						sigma_t const w = u << 1;
						for (sigma_t               i = 0; i < u; i += 1)
						for (sigma_t in = i << on, j = i; j < N; j += w)
						{
							U const su = s[j + u]*basis[in];
							U const s0 = s[j + 0];
							s[j + u] = s0 - su;
							s[j + 0] = s0 + su;
						}
					}
					return s;
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

				XTAL_NEW_(explicit) homotype(size_type sN, XTAL_DEF... ws)
				{
					insert_back(sN, XTAL_REF_(ws)...);
				}

				///\
				Span constructor. \
				Initializes `this` with the values between `i0` and `iN`. \

				template <iterator_q I>
				XTAL_IF1 as_q<iteratee_t<I>, V>
				XTAL_NEW_(explicit) homotype(I &&i0, I &&iN)
				{
					insert_back(XTAL_FWD_(I) (i0), XTAL_FWD_(I) (iN));
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
			//	XTAL_IF1 _std::swappable<V>
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

				XTAL_FN1_(void) deallocate(const_iterator i0)
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

				XTAL_FN1_(void) erase(const_iterator i0)
				XTAL_0EX
				{
					erase(i0, size_type(1));
				}
				///\
				Deletes `sN` elements starting from `i0`. \

				XTAL_FN1_(void) erase(const_iterator i0, size_type sN)
				XTAL_0EX
				{
					erase(i0, _v3::ranges::next(i0, sN), sN);
				}
				///\
				Deletes the elements between `i0` and `iN`. \

				XTAL_FN1_(void) erase(const_iterator i0, const_iterator iN)
				XTAL_0EX
				{
					erase(i0, iN, _std::distance(i0, iN));
				}
				///\
				Deletes `sN` elements between `i0` and `iN`. \

				XTAL_FN1_(void) erase(const_iterator i0, const_iterator iN, size_type sN)
				XTAL_0EX
				{
					erode(const_cast<iterator>(i0), const_cast<iterator>(iN), sN);
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

				XTAL_FN1_(void) resize(size_type sN, XTAL_DEF... ws)
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

				XTAL_FN1_(void) refill(XTAL_DEF... ws)
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

				XTAL_FN1_(void) push_back(XTAL_DEF_(as_q<V>)... etc)
				{
					push_back(bracket_t<V>{V(XTAL_REF_(etc))...});
				}

				///\
				Constructs an element at the end of `this` using the given arguments. \
				\returns a reference to the element.

				XTAL_FN1_(reference) emplace_back(XTAL_DEF... ws) 
				{
					return *inplace_back(XTAL_REF_(ws)...);
				}
				///\
				Constructs an element at the end of `this` using the given arguments. \
				\returns a pointer to the element.

				XTAL_FN1_(iterator) inplace_back(XTAL_DEF... ws) 
				{
					reserve(size_type(1) + size());
					return ::new (index_m++) V(XTAL_REF_(ws)...);
				}

				///\
				Invokes `insert` at `this->end()` with the given arguments. \

				XTAL_FN1_(iterator) insert_back(XTAL_DEF... ws)
				{
					return insert(end(), XTAL_REF_(ws)...);
				}

				///\
				Inserts the values delimited by `j0` and `jN` beginning at `i`. \

				template <iterator_q J>
			//	XTAL_IF1 as_q<iteratee_t<J>, V>
				XTAL_FN1_(iterator) insert(const_iterator i, J j0, J jN)
				{
					inject(i, _std::distance(j0, jN));
					copy_linear_f(false, iterator(i), j0, jN);
					return iterator(i);
				}
				XTAL_FN1_(iterator) insert(const_iterator i, const_iterator j0, const_iterator jN)
				{
					inject(i, _std::distance(j0, jN));
					copy_linear_f(false, iterator(i), j0, jN);
					return iterator(i);
				}

				///\
				Inserts the values `etc` beginning at `i`. \

				XTAL_FN1_(iterator) insert(const_iterator i, bracket_t<V> etc)
				{
					return insert(i, etc.begin(), etc.end());
				}

				///\
				Initialises `sN` values with `v` beginning at `i`. \

				XTAL_FN1_(iterator) insert(const_iterator i, size_type sN, V const &v)
				{
					inject(i, sN);
					_std::uninitialized_fill_n(i, sN, v);
					return iterator(i);
				}
				XTAL_FN1_(iterator) insert(const_iterator i, size_type sN, V &&v)
				{
					inject(i, sN);
					_std::uninitialized_fill_n(i, sN, _std::move(v));
					return iterator(i);
				}

				///\
				Initialises `sN` values beginning at `i`. \

				XTAL_FN1_(iterator) insert(const_iterator i, size_type sN)
				{
					inject(i, sN);
					_std::uninitialized_value_construct_n(i, sN);
					return iterator(i);
				}
				
			protected:
				///\
				Allocates `sN` elements beginning at `i`. \

				XTAL_FN1_(iterator) inject(const_iterator i, size_type sN)
				{
					reserve(sN + size());
					if (i < end())// and _std::move_constructible<V>)
					{
						auto j = _std::make_reverse_iterator(index_m);
						move_linear_f(true, _v3::ranges::prev(j, sN), j, _v3::ranges::next(j, sN));
					}
					else
					{
						assert(i == end());
					}
					index_m += sN;
					return iterator(i);
				}

				///\
				Deletes `sN` elements between `i0` and `iN`. \

				XTAL_FN1_(void) erode(iterator i0, iterator iN, size_type sN)
				XTAL_0EX
				{
					iterator begin_m = begin(), end_m = end();
					assert(begin_m <= i0 and iN <= end_m and _std::distance(i0, iN) == sN);
					if constexpr (_std::destructible<V>)
					{
						_std::destroy(i0, iN);
					}
					if (iN < end_m)// and _std::move_constructible<V>)
					{
						auto jN = appointee_f(iN);
						auto j0 = appointee_f(i0);
						move_linear_f(sN <= _std::distance(jN, index_m), j0, jN, index_m);
					}
					else
					{
						assert(end_m == iN);
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
		XTAL_IF1 negative_q<N>
		struct vector<V>
		{
			using type = _std::vector<V>;

		};

		template <typename U>
		using scalar_t = typename scalar<U>::type;

		template <typename U>
		using series_t = typename series<U>::type;

		template <typename U>
		using spectra_t = typename spectra<U>::type;

		template <typename V>
		using vector_t = typename vector<V>::type;

		template <typename V>
		using funnel_t = _std::priority_queue<V, vector_t<V>, _std::greater<V>>;

		template <typename V>
		using allocator_t = typename vector_t<V>::allocator_type;

	};
	using type = subtype<_std::monostate>;

};

template <iota_t N=-1>
using buffer_t = typename buffer<N>::type;

template <iota_t N=-1, typename U=alpha_t>
using buffer_scalar_t = typename buffer_t<N>::template scalar_t<U>;

template <iota_t N=-1, typename U=alpha_t>
using buffer_series_t = typename buffer_t<N>::template series_t<U>;

template <iota_t N=-1, typename U=alpha_t>
using buffer_spectra_t = typename buffer_t<N>::template spectra_t<U>;

template <iota_t N=-1, typename V=alpha_t>
using buffer_vector_t = typename buffer_t<N>::template vector_t<V>;

template <iota_t N=-1, typename V=alpha_t>
using buffer_funnel_t = typename buffer_t<N>::template funnel_t<V>;

template <iota_t N=-1, typename V=alpha_t>
using buffer_allocator_t = typename buffer_t<N>::template allocator_t<V>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
