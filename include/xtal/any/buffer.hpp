#pragma once
#include "./any.hpp"
#include "./collate.hpp"// next

#include <complex>



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
		private:
			using V = based_t<U>;

		//	TODO: Use indirection rather than inheritance to access `std::array`? \

		//	TODO: Specialize the appropriate types so that e.g. `std::apply` works. \

		//	TODO: Specialize the appropriate types to allow `alpha_q` to match `scalar<alpha_q>`. \
		
		//	TODO: Reify `buffer_scalar_t<2, U>` with even/odd semantics, \
			e.g. stereo or mid-side signals, and results like `exp(+x), exp(-x)` or `cosh(x), sinh(x)`, \
			and define the operations to interconvert them. \

		//	TODO: Reify `buffer_scalar_t<2, U>` with `std::complex` semantics, \
			and define componentwise multiplication either by: \
			-	using `std::bit_cast<scalar_t<U>>` \
			-	defining a non-summing companion to `dot` e.g. `zot` \
			-	supplying real and imaginary projections with a range interface \

		//	TODO: Define orbital and FFT operations. \

		public:
			template <arrayed_q _S>
			class subtype;

			template <arrayed_q _S>
			XTAL_IF1 is_q<iteratee_t<_S>, U>// and alpha_q<U>
			class subtype<_S>: public _S
			{
				using co = _S; using T = subtype<_S>;
			public:
				using co::co;
				using co::size;

				XTAL_FN2 get() XTAL_0FX_( &) {return static_cast<co const  &>(*this);}
				XTAL_FN2 get() XTAL_0EX_( &) {return static_cast<co        &>(*this);}
				XTAL_FN2 get() XTAL_0FX_(&&) {return static_cast<co const &&>(*this);}
				XTAL_FN2 get() XTAL_0EX_(&&) {return static_cast<co       &&>(*this);}

				XTAL_RE4_(XTAL_FN2 get(XTAL_DEF i), get()[XTAL_REF_(i)]);

			//	XTAL_OP2        <=>          (T const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=> t[Ns]) <=>...         ) (seek_v<N>);}
				XTAL_OP2_(bool) <=           (T const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=  t[Ns]) and... and true) (seek_v<N>);}
				XTAL_OP2_(bool) >=           (T const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >=  t[Ns]) and... and true) (seek_v<N>);}
				XTAL_OP2_(bool) <            (T const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <   t[Ns]) and... and true) (seek_v<N>);}
				XTAL_OP2_(bool) >            (T const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >   t[Ns]) and... and true) (seek_v<N>);}

				XTAL_OP1_(T&  ) *=           (T const &t) XTAL_0EX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) *= t[Ns]), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) /=           (T const &t) XTAL_0EX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) /= t[Ns]), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) %=           (T const &t) XTAL_0EX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) %= t[Ns]), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) +=           (T const &t) XTAL_0EX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += t[Ns]), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) -=           (T const &t) XTAL_0EX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= t[Ns]), ..., *this) (seek_v<N>);}
				
				XTAL_OP1_(T&  ) *=       (bracket_t<V> t) XTAL_0EX {assert(N == t.size()); for (auto n = N; ~--n;) get(n) *= t[n]; return *this;}
				XTAL_OP1_(T&  ) /=       (bracket_t<V> t) XTAL_0EX {assert(N == t.size()); for (auto n = N; ~--n;) get(n) /= t[n]; return *this;}
				XTAL_OP1_(T&  ) %=       (bracket_t<V> t) XTAL_0EX {assert(N == t.size()); for (auto n = N; ~--n;) get(n) %= t[n]; return *this;}
				XTAL_OP1_(T&  ) +=       (bracket_t<V> t) XTAL_0EX {assert(N == t.size()); for (auto n = N; ~--n;) get(n) += t[n]; return *this;}
				XTAL_OP1_(T&  ) -=       (bracket_t<V> t) XTAL_0EX {assert(N == t.size()); for (auto n = N; ~--n;) get(n) -= t[n]; return *this;}
				
				XTAL_OP1_(T&  ) *= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {auto const u = U(XTAL_REF_(w)); return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) *= u), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) /= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {auto const u = U(XTAL_REF_(w)); return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) /= u), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) %= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {auto const u = U(XTAL_REF_(w)); return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) %= u), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) += (XTAL_DEF_(as_q<U>) w) XTAL_0EX {auto const u = U(XTAL_REF_(w)); return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += u), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) -= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {auto const u = U(XTAL_REF_(w)); return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= u), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) ++                     () XTAL_0EX {                                return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_(     ++get(Ns), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) --                     () XTAL_0EX {                                return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_(     --get(Ns), ..., *this) (seek_v<N>);}
				
				XTAL_OP2_(T   ) *            (XTAL_DEF w) XTAL_0FX {auto r = *this; return r *= XTAL_REF_(w);}
				XTAL_OP2_(T   ) /            (XTAL_DEF w) XTAL_0FX {auto r = *this; return r /= XTAL_REF_(w);}
				XTAL_OP2_(T   ) %            (XTAL_DEF w) XTAL_0FX {auto r = *this; return r %= XTAL_REF_(w);}
				XTAL_OP2_(T   ) +            (XTAL_DEF w) XTAL_0FX {auto r = *this; return r += XTAL_REF_(w);}
				XTAL_OP2_(T   ) -            (XTAL_DEF w) XTAL_0FX {auto r = *this; return r -= XTAL_REF_(w);}

				XTAL_OP2_(T) ~ ()
				XTAL_0FX
				XTAL_IF1 (N == 2)
				{
					auto const x = get(0) + get(1);
					auto const y = get(0) - get(1);
					return T{x, y};//*realize<U>::SQRT_HALF;
				}
				
				/// Fills `this` with the geometric series `{1, u, u*u, u*u*u, ...}`. \

				///\returns `*this` for chaining. \

				///\note This algorithm uses squaring, \
				which is more precise/efficient than multiplication for complex numbers. \

				XTAL_FN1_(T&) series_geometric(U const &u, sigma_t const &i_lim = N)
				XTAL_0EX
				XTAL_IF1 even_q<N>
				{
					auto &s = *this;
					s[0] = 1;
					s[1] = u;
					for (sigma_t i = 1; i < i_lim >> 1; ++i)
					{
						auto w = square_y(s[i]);
						auto h = i << 1;
						s[h] = w;
						h   += 1;
						w   *= u;
						s[h] = w;
					}
					return s;
				}
				
				/// Fills `this` with the `basis` used by `transform_fourier`, \
				comprising `N` values of the half-period complex sinusoid.

				///\returns `*this` for chaining. \

				XTAL_FN1_(T&) series_fourier()
				XTAL_0EX
				XTAL_IF1 even_q<N> and complex_q<U>
				{
					auto &s = *this;
					auto constexpr rho = [] (U const &u) XTAL_0FN_(U(u.imag(), -u.real()));
					auto const     phi = realized::patio_y<-1> (N);
					auto const     x = _std::cos(phi);
					auto const     y = _std::sin(phi);
					auto const     u = U(x, y);
					auto const     o = U(1, 0);
					auto constexpr H = N >> 1;
					/*/
					series_geometric(U(x, y), H);
					auto const _H = s.begin() + H;
					auto const _0 = s.begin();
					_std::transform(_0, _H, _H, rho);
					/*/
					s[0] = o; s[0 + H] = rho(o);
					s[1] = u; s[1 + H] = rho(u);
					for (sigma_t h = 1; h < H >> 1; ++h)
					{
						auto w = square_y(s[h]);
						auto i = h << 1;
						s[i] = w; s[i + H] = rho(w);
						i   += 1;
						w   *= u;
						s[i] = w; s[i + H] = rho(w);
					}
					/***/
					return s;
				}
				
				/// Applies the Fourier transform to `this`. \

				///\returns `*this` for chaining. \

				XTAL_FN1_(T&) transform_fourier()
				XTAL_0EX
				XTAL_IF1 even_q<N> and complex_q<U>
				{
					T basis; basis.series_fourier();
					return this->transform_fourier(basis);
				}

				/// Applies the Fourier transform to `this`, using a precomputed `basis`. \

				///\returns `*this` for chaining. \

				XTAL_FN1_(T&) transform_fourier(T const &basis)
				XTAL_0EX
				XTAL_IF1 even_q<N> and complex_q<U>
				{
					sigma_t constexpr H = N >> 1;
					sigma_t constexpr O = bit_ceiling_y(N);
					static_assert(1 << O == N);

					auto& s = *this;
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
			template <arrayed_q _S>
			XTAL_IF1 is_q<iteratee_t<_S>, U> and iota_q<U>
			class subtype<_S>: public _S
			{
				using co = _S; using T = subtype<_S>;

			public:
				using co::co;
				using co::size;

				XTAL_FN2 get() XTAL_0FX_( &) {return static_cast<co const  &>(*this);}
				XTAL_FN2 get() XTAL_0EX_( &) {return static_cast<co        &>(*this);}
				XTAL_FN2 get() XTAL_0FX_(&&) {return static_cast<co const &&>(*this);}
				XTAL_FN2 get() XTAL_0EX_(&&) {return static_cast<co       &&>(*this);}

				XTAL_RE4_(XTAL_FN2 get(XTAL_DEF i), get()[XTAL_REF_(i)]);

			//	XTAL_OP2        <=>          (T const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=> t[Ns]) <=>...         ) (seek_v<N>);}
				XTAL_OP2_(bool) <=           (T const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=  t[Ns]) and... and true) (seek_v<N>);}
				XTAL_OP2_(bool) >=           (T const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >=  t[Ns]) and... and true) (seek_v<N>);}
				XTAL_OP2_(bool) <            (T const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <   t[Ns]) and... and true) (seek_v<N>);}
				XTAL_OP2_(bool) >            (T const &t) XTAL_0FX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >   t[Ns]) and... and true) (seek_v<N>);}

				XTAL_OP1_(T&  ) &=           (T const &t) XTAL_0EX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) &= t[Ns]), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) |=           (T const &t) XTAL_0EX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) |= t[Ns]), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) ^=           (T const &t) XTAL_0EX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ^= t[Ns]), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) +=           (T const &t) XTAL_0EX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += t[Ns]), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) -=           (T const &t) XTAL_0EX {return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= t[Ns]), ..., *this) (seek_v<N>);}
				
				XTAL_OP1_(T&  ) &=       (bracket_t<V> t) XTAL_0EX {assert(N == t.size()); for (auto n = N; ~--n;) get(n) &= t[n]; return *this;}
				XTAL_OP1_(T&  ) |=       (bracket_t<V> t) XTAL_0EX {assert(N == t.size()); for (auto n = N; ~--n;) get(n) |= t[n]; return *this;}
				XTAL_OP1_(T&  ) ^=       (bracket_t<V> t) XTAL_0EX {assert(N == t.size()); for (auto n = N; ~--n;) get(n) ^= t[n]; return *this;}
				XTAL_OP1_(T&  ) +=       (bracket_t<V> t) XTAL_0EX {assert(N == t.size()); for (auto n = N; ~--n;) get(n) += t[n]; return *this;}
				XTAL_OP1_(T&  ) -=       (bracket_t<V> t) XTAL_0EX {assert(N == t.size()); for (auto n = N; ~--n;) get(n) -= t[n]; return *this;}
				
				XTAL_OP1_(T&  ) &= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {auto const u = U(XTAL_REF_(w)); return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) &= u), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) |= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {auto const u = U(XTAL_REF_(w)); return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) |= u), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) ^= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {auto const u = U(XTAL_REF_(w)); return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ^= u), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) += (XTAL_DEF_(as_q<U>) w) XTAL_0EX {auto const u = U(XTAL_REF_(w)); return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += u), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) -= (XTAL_DEF_(as_q<U>) w) XTAL_0EX {auto const u = U(XTAL_REF_(w)); return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= u), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) ++                     () XTAL_0EX {                                return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_(     ++get(Ns), ..., *this) (seek_v<N>);}
				XTAL_OP1_(T&  ) --                     () XTAL_0EX {                                return [&] <auto... Ns>(seek_t<Ns...>) XTAL_0FN_(     --get(Ns), ..., *this) (seek_v<N>);}
				
				XTAL_OP2_(T   ) &            (XTAL_DEF w) XTAL_0FX {auto r = *this; return r &= XTAL_REF_(w);}
				XTAL_OP2_(T   ) |            (XTAL_DEF w) XTAL_0FX {auto r = *this; return r |= XTAL_REF_(w);}
				XTAL_OP2_(T   ) ^            (XTAL_DEF w) XTAL_0FX {auto r = *this; return r ^= XTAL_REF_(w);}
				XTAL_OP2_(T   ) +            (XTAL_DEF w) XTAL_0FX {auto r = *this; return r += XTAL_REF_(w);}
				XTAL_OP2_(T   ) -            (XTAL_DEF w) XTAL_0FX {auto r = *this; return r -= XTAL_REF_(w);}
				
				XTAL_OP2_(T   ) ++                 (int) XTAL_0EX {auto r = *this; operator++(); return r;}
				XTAL_OP2_(T   ) --                 (int) XTAL_0EX {auto r = *this; operator--(); return r;}
				XTAL_OP2_(T   ) ~                     () XTAL_0FX {return _std::apply([] (XTAL_DEF... xs) XTAL_0FN_(T{(~xs, ...)}), get());}
				XTAL_OP2_(T   ) -                     () XTAL_0FX {return _std::apply([] (XTAL_DEF... xs) XTAL_0FN_(T{(-xs, ...)}), get());}

			};
			using type = subtype<_std::array<U, N>>;

		};
		template <typename U>
		using scalar_t = typename scalar<U>::type;

		template <typename U>
		struct vector
		{
			template <typename T>
			using kind = iterate_t<T>;

			class type: public kind<type>
			{
				using co = kind<type>;

				static_assert(based_q<U>);
				using V = based_t<U>;
				using A = _std::aligned_storage_t<sizeof(V), alignof(V)>;

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
			//	using co;
				using co::size;

				using             value_type = V;
				using         allocator_type = type;

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

				~type()
				{
					clear();
				}
				///\
				Default constructor. \

				type() noexcept = default;

				///\
				Insert constructor. \
				Initializes `this` with `sN` values determined by the given arguments. \

				XTAL_NEW_(explicit) type(size_type sN, XTAL_DEF... ws)
				{
					insert_back(sN, XTAL_REF_(ws)...);
				}

				///\
				Span constructor. \
				Initializes `this` with the values between `i0` and `iN`. \

				template <iterator_q I>
				XTAL_IF1 as_q<iteratee_t<I>, V>
				XTAL_NEW_(explicit) type(I &&i0, I &&iN)
				{
					insert_back(XTAL_FWD_(I) (i0), XTAL_FWD_(I) (iN));
				}

				///\
				List constructor. \
				Initializes `this` with the given values. \

				XTAL_NEW_(explicit) type(_std::initializer_list<V> vs)
				:	type(vs.begin(), vs.end())
				{
				}
				///\
				List assignment. \
				Replaces the contents of `this` with the given values. \

				XTAL_OP1 = (_std::initializer_list<V> vs)
				{
					refill(vs.begin(), vs.end());
					return *this;
				}

				///\
				Copy constructor. \
				Initializes `this` with the given vector. \

				XTAL_NEW type(type const &t)
				:	type(t.begin(), t.end())
				{
				}
				///\
				Copy assigment. \
				Replaces the contents of `this` with the given vector. \

				XTAL_OP1 = (type const &t)
				{
					refill(t.begin(), t.end());
					return *this;
				}

				///\
				Move constructor. \
				Initializes `this` with the given vector. \

				XTAL_NEW type(type &&t)
				:	type(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()))
				{
				}
				///\
				Move assigment. \
				Replaces the contents of `this` with the given vector. \

				XTAL_OP1 = (type &&t)
				{
					refill(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()));
					return *this;
				}

				///\
				Swaps the contents of `this` with the given vector. \

				XTAL_FN1_(void) swap(type &t)
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
				Inserts the values `vs` beginning at `i0`. \

				XTAL_FN1_(void) push_back(_std::initializer_list<V> vs)
				{
					insert_back(vs.begin(), vs.end());
				}
				///\
				Inserts the values `vs...` beginning at `i0`. \

				XTAL_FN1_(void) push_back(XTAL_DEF_(as_q<V>)... vs)
				{
					push_back(_std::initializer_list<V>{V(XTAL_REF_(vs))...});
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
				Inserts the values `vs` beginning at `i`. \

				XTAL_FN1_(iterator) insert(const_iterator i, _std::initializer_list<V> vs)
				{
					return insert(i, vs.begin(), vs.end());
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
		};
		template <typename U>
		XTAL_IF1 negative_q<N>
		struct vector<U>
		{
			using type = _std::vector<U>;

		};
		template <typename U>
		using vector_t = typename vector<U>::type;

		template <typename U>
		using allocator_t = typename vector_t<U>::allocator_type;

		template <typename U>
		using still_t = _std::priority_queue<U, vector_t<U>, _std::greater<U>>;

	};
	using type = subtype<_std::monostate>;

};

template <iota_t N=-1>
using buffer_t = typename buffer<N>::type;

template <iota_t N=-1, typename U=alpha_t>
using buffer_still_t = typename buffer_t<N>::template still_t<U>;

template <iota_t N=-1, typename U=alpha_t>
using buffer_vector_t = typename buffer_t<N>::template vector_t<U>;

template <iota_t N=-1, typename U=alpha_t>
using buffer_scalar_t = typename buffer_t<N>::template scalar_t<U>;

template <iota_t N=-1, typename U=alpha_t>
using buffer_allocator_t = typename buffer_t<N>::template allocator_t<U>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
