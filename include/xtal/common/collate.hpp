#pragma once
#include "./any.hpp"
#include "./seek.hpp"
#include "./collect.hpp"




XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename T> struct realize;


////////////////////////////////////////////////////////////////////////////////
template <typename V>
struct collate
{
	using _realized = realize<V>;

	template <typename S>
	class subtype: public S
	{
		using co = S;

		XTAL_LET N_size = co::volume::value;

	public:
		using co::co;

		template <typename U>
		using recollate_t = typename collate<U>::template subtype<S>;

		template <typename R>
		struct graft;
		struct fluid;
		struct fixed;

		template <size_t N_retain=0>
		struct siphon;// fluid
		struct sluice;// fluid
		struct scalar;// fixed
		struct product;// fixed
		struct serial;// fixed
		struct series;// fixed
		
		template <typename R>
		struct graft
		{
			template <typename T>
			class homotype: public R
			{
				friend T;
				using co = R;

			public:
				using co::co;

				///\returns\
				a copy of `*this` with type `Y=T`. \

				template <typename Y=T>
				XTAL_FN2_(Y) twin()
				XTAL_0FX_(&)
				{
					return self<Y>();
				}
				///\returns\
				`*this` with type `Y=T`. \

				template <typename Y=T>
				XTAL_FN2 self()
				XTAL_0FX_(&)
				{
					if constexpr (is_q<Y, T>) return static_cast<T const &>(*this);
					else                 return reinterpret_cast<Y const &>(*this);
				}
				template <typename Y=T>
				XTAL_FN2 self()
				XTAL_0EX_(&)
				{
					if constexpr (is_q<Y, T>) return static_cast<T &>(*this);
					else                 return reinterpret_cast<Y &>(*this);
				}
				///\
				Alias of `operator[]`. \

				XTAL_RN2_(XTAL_FN2 datum(XTAL_DEF i), self()[XTAL_REF_(i)]);

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		struct fluid
		{
			using demitype = typename co::template fluid<V>::type;

			template <typename T>
			using homotype = typename graft<demitype>::template homotype<T>;

			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		struct fixed
		{
			using demitype = typename co::template fixed<V>::type;

			template <typename T>
			using homotype = typename graft<demitype>::template homotype<T>;

			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};

		///\
		Event spool based on a insertion-sorted `std::array`, \
		presenting a similar interface to `sluice`. \
		
		///\
		If `N_retain == 1`, the _current_ value is available via `next(0)`. \

		template <size_t N_retain>
		struct siphon
		{
			template <typename T>
			using hemitype = typename fluid::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
				friend T;
				using co = hemitype<T>;

				using  size_t = typename co::      size_type;
				using value_t = typename co::     value_type;
				using count_t = typename co::difference_type;
				using point_t = typename co::iterator;
				using next_t  = typename co::const_reference;

				point_t point_m;

				XTAL_LET N = N_retain;
				static_assert(N <= 1);

			public:
				using co::co;

				XTAL_NEW homotype()
				XTAL_0EX
				XTAL_IF1 (N == 0)
				:	co {}
				,	point_m {co::begin()}
				{
				}
				XTAL_NEW homotype()
				XTAL_0EX
				XTAL_IF1 (N == 1)
				:	co {value_t(_std::numeric_limits<typename value_t::head_t>::max())}
				,	point_m {co::begin()}
				{
				}
				XTAL_FN2_(point_t)     begin() XTAL_0EX {return  point_m;}
				XTAL_FN2_(count_t) completed() XTAL_0EX {return _std::distance(co::begin(), begin());}
				XTAL_FN2_(count_t) remaining() XTAL_0EX {return _std::distance(    begin(),   end());}
				XTAL_FN2_(point_t)       end() XTAL_0EX {return _std::prev(co::end(), N);}

				XTAL_FN2_(next_t)    next(bool i=N) XTAL_0EX {return *(point_m +  i);}
				XTAL_FN1_(next_t) advance(bool i=1) XTAL_0EX {return *(point_m += i);}
				XTAL_FN1_(next_t) abandon(bool i=1)
				XTAL_0EX
				{
					if (i)
					{	co::erase(co::begin(), end());
						point_m = co::begin();
					}
					return *point_m;
				}

				///\returns\
				the result of queuing the given message, \
				with zero indicating that the message was already scheduled. \
				
				///\note\
				Conflicting entries are overwritten. \

				XTAL_FN1_(sign_t) push(value_t const &e)
				XTAL_0EX
				{
					auto &s = co::self();
					auto e_ = s.peek(e);
					return *e_ == e? s.prod(e, e_): s.poke(e, e_);
				}

			protected:
				///\
				Inserts `e` at `e_`, return `1` if inserted before `end()`, `-1` otherwise. \
				
				XTAL_FN1_(sign_t) poke(value_t e, value_t* e_)
				XTAL_0EX
				{
					co::insert(e_, {e}); return sign_f<1>(point_m - e_);
				}
				
				///\
				Exchanges `e` with `e_`, returning `1` if changed, `0` otherwise. \

				XTAL_FN1_(sign_t) prod(value_t e, value_t* e_)
				XTAL_0EX
				{
					_std::swap(*e_, e); return e_->tail() != e.tail();
				}

				///\returns\
				a pointer to the first element `>= e`. \

				XTAL_FN1 peek(value_t e)
				XTAL_0EX
				{
					return _std::lower_bound(co::begin(), end(), e);
				}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		///\
		Event spool based on an inverted `std::priority_queue`, \
		interchangeable with `siphon<0>` as far as the interface aligns. \

		struct sluice
		{
			using demitype = _std::priority_queue<V, typename fluid::type, _std::greater<V>>;

			template <typename T>
			class homotype: public demitype
			{
				friend T;
				using co = demitype;
				using count_t = typename co:: size_type;
				using value_t = typename co::value_type;
				using next_t  = typename co::const_reference;

				XTAL_FN0 clear()
				XTAL_0EX
				{
					while (not co::empty())
					{
						co::pop();
					}
				}
			public:
				using co::co;

				XTAL_FN2_(count_t) completed()           XTAL_0EX {return          0;}
				XTAL_FN2_(count_t) remaining()           XTAL_0EX {return co::size();}
				XTAL_FN1_(void)      advance(bool i=1)   XTAL_0EX {if (i) co:: pop();}
				XTAL_FN1_(void)      abandon(bool i=1)   XTAL_0EX {if (i)    clear();}
				XTAL_FN2_(next_t)       next()           XTAL_0EX {return co:: top();}
				XTAL_FN1_(sign_t)       push(XTAL_DEF o) XTAL_0EX {return co::push(XTAL_REF_(o)), 1;}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		///\
		Represents a scalable fixed-length vector. \

		struct scalar
		{
			template <typename T>
			using hemitype = typename fixed::template homotype<T>;

			template <typename T>// requires arithmetic_operators_q<V>
			class homotype: public hemitype<T>
			{
				friend T;
				using co = hemitype<T>;

			public:
				using co::co;
				using co::self;
				using co::twin;
				using co::datum;

				template <bracket_q U> requires (not is_q<U, V>)
				XTAL_NEW_(explicit) homotype(U &&u)
				:	co()
				{
					_detail::move_to(co::begin(), u);
				}
				template <bracket_q U> requires (not is_q<U, V>)
				XTAL_NEW_(explicit) homotype(U const &u)
				:	co()
				{
					_detail::copy_to(co::begin(), u);
				}
				XTAL_NEW homotype(bracket_t<V> etc)
				XTAL_0EX
				{
					_detail::copy_to(co::begin(), etc);
				}

				template <typename U>
				XTAL_FZ2_(T &) refer(U &u)
				XTAL_0EX
				{
					static_assert(is_q<value_t<U>, V> and sizeof(U) == sizeof(T));
					return reinterpret_cast<T &>(u);
				}

				///\
				Elementwise mutating transformer. \

				XTAL_FN1 transmute(XTAL_DEF_(_std::invocable<V>) ...fs)
				XTAL_0EX
				{
					(transmute(XTAL_REF_(fs)), ...);
					return self();
				}
				XTAL_FN1 transmute(XTAL_DEF_(_std::invocable<V>) f)
				XTAL_0EX
				{
					_detail::apply_to(self(), XTAL_REF_(f));
					return self();
				}
				XTAL_FN1 transmute(_std::invocable<V> auto const &f)
				XTAL_0EX
				XTAL_IF1 (0 < N_size) and (N_size <= _realized::destructive_alignment_v)
				{
					seek_f<N_size>([&, this](auto i) XTAL_0FN_(datum(i) = f(datum(i))));
					return self();
				}

				///\
				Elementwise comparators. \

			//	XTAL_OP2        <=> (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) <=> t.datum(N)) <=>...         ) (seek_v<N_size>);}
				XTAL_OP2_(bool) ==  (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) ==  t.datum(N)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) <=  (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) <=  t.datum(N)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) >=  (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) >=  t.datum(N)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) <   (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) <   t.datum(N)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) >   (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) >   t.datum(N)) and ...and true) (seek_v<N_size>);}

				XTAL_OP2_(T)    *  (XTAL_DEF w) XTAL_0FX {return twin() *= XTAL_REF_(w);}
				XTAL_OP2_(T)    /  (XTAL_DEF w) XTAL_0FX {return twin() /= XTAL_REF_(w);}
				XTAL_OP2_(T)    +  (XTAL_DEF w) XTAL_0FX {return twin() += XTAL_REF_(w);}
				XTAL_OP2_(T)    -  (XTAL_DEF w) XTAL_0FX {return twin() -= XTAL_REF_(w);}

				XTAL_OP1_(T &)  *= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(datum(i) *= XTAL_REF_(w))), self();}
				XTAL_OP1_(T &)  /= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(datum(i) /= XTAL_REF_(w))), self();}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		///\
		Represents a sequence that supports elementwise multiplication/division. \

		struct product
		{
			template <typename T>
			using hemitype = typename scalar::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
				friend T;
				using co = hemitype<T>;
			
			public:
				using co::co;
				using co::self;
				using co::twin;
				using co::datum;

				///\
				The counterpart to `this` for which addition is linear, \
				and multiplication is performed via convolution. \
				
				template <typename Z>
				using dual_t = Z;
			//	using dual_t = typename series::type;
			//	using dual_t = typename serial::type;

				XTAL_OP1_(T &) *= (bracket_t<V> w) XTAL_0EX {return self() *= T(w.begin(), w.end());}
				XTAL_OP1_(T &) /= (bracket_t<V> w) XTAL_0EX {return self() /= T(w.begin(), w.end());}				
				
				XTAL_OP1_(T &) *= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(datum(i) *= t.datum(i))), self();}
				XTAL_OP1_(T &) /= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(datum(i) /= t.datum(i))), self();}

				///\returns\
				the mutually inverse product `lhs +/- rhs`, \
				scaled by the value indexed by `N_bias`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
				
				///\note\
				Useful for converting between e.g. exponential/hyperbolic or stereo/mid-side pairs. \

				template <int N_bias=0>
				XTAL_FN2 reflected()
				XTAL_0FX
				XTAL_IF1 (N_size == 2)
				{
					using alpha_t = typename _realized::alpha_t;
					alpha_t constexpr   base = _realized::template unsquare_y<-1>((alpha_t) 2);// `std::sqrt(0.5)`
					alpha_t constexpr debase = _realized::explo_y(1 - N_bias, base);
					auto const &lhs = debase*datum(0);
					auto const &rhs = debase*datum(1);
					return T {lhs + rhs, lhs - rhs};
				}
				///\
				Modifies `this`; \see `reflected()`.

				template <int N_bias=0>
				XTAL_FN2 reflect()
				XTAL_0FX
				XTAL_IF1 (N_size == 2)
				{
					return self() = reflected<N_bias>();
				}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		///\
		Represents a sequence that supports elementwise addition/subtracion. \

		struct sum
		{
			template <typename T>
			using hemitype = typename scalar::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
				friend T;
				using co = hemitype<T>;
			
			public:
				using co::co;
				using co::self;
				using co::twin;
				using co::datum;

				///\
				The counterpart to `this` for which multiplication is linear. \

				template <typename Z>
				using dual_t = typename product::type;

				XTAL_OP1_(T &) += (bracket_t<V> w) XTAL_0EX {return self() += T(w.begin(), w.end());}
				XTAL_OP1_(T &) -= (bracket_t<V> w) XTAL_0EX {return self() -= T(w.begin(), w.end());}
				
				XTAL_OP1_(T &) += (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(datum(i) += t.datum(i))), self();}
				XTAL_OP1_(T &) -= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(datum(i) -= t.datum(i))), self();}

			};
		};
		///\
		Represents a sequence that supports elementwise addition/subtracion, \
		where multiplication is performed by circular convolution. \

		struct series
		{
			template <typename T>
			using hemitype = typename sum::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
				friend T;
				using co = hemitype<T>;
			
			public:
				using co::co;
				using co::self;
				using co::twin;
				using co::datum;

				///\
				Generates part of the complex sinusoid determined by `std::pow(2, shift_o::value)`. \

				XTAL_NEW_(explicit) homotype(constant_q auto const shift_o)
				{
					generate<shift_o>();
				}
				///\
				Generates the power series with the given seed. \

				XTAL_NEW_(explicit) homotype(XTAL_DEF_(is_q<V>) v)
				{
					generate(XTAL_REF_(v));
				}

				///\returns `this` with the elements `N_index, ..., N_index + N_limit - 1` \
					filled by the corresponding powers of `u`. \

				template <size_t N_limit=N_size, size_t N_index=0>
				XTAL_FN1_(T &) generate(V const &u)
				XTAL_0EX
				{
					auto &s = self();
					using I = typename co::difference_type;

				//	Compute the start- and end-points for the required segment:
					I constexpr H_limit = N_limit >> 1;
					I constexpr _0 = N_index + 0;
					I constexpr _1 = N_index + 1;
					I constexpr _H = N_index + H_limit;
					I constexpr N1 = N_index + N_limit - 1;
					I constexpr N2 = N_index + N_limit - 2;

				//	Compute and populate the 0th and 1st powers:
					auto const o = _realized::template explo_y(N_index, u);
					s[_0] = o;
					s[_1] = o*u;

					for (I i = _1; i < _H; ++i)
					{	auto w = _realized::square_y(s[i]);
					
					//	Use the square of the previous value to populate the value at `i << 1`:
						I ii = i << 1;
						s[ii + 0] = w;
						s[ii + 1] = w*u;

					}
				//	Compute the final value if `N_limit` is odd:
					if constexpr (N_limit&1)
					{	s[N1] = s[N2]*u;
					}
					return s;
				}

				///\returns\
				`this` as the section of the complex sinusoid with length `2*PI*std::pow(2, N_shift)`, \
				where `-3 <= N_shift`. \
				
				///\note\
				To generate the FFT basis used by `transform` etc, use `N_shift == -1`. \

				template <int N_shift=0>
				XTAL_FN1_(T &) generate()
				XTAL_0EX
				XTAL_IF1 complex_q<V>
				{
				//	Initialize the forwards and backwards iterators:
					auto const i = co::begin();
					auto const j = co::rend() - 1;
					
				//	Compute the fractional sinusoid for the given `N_size`:
					auto constexpr x = _realized::template patio_y<-1>(N_size);
					auto const     y = _realized::circle_y(x);// TODO: Make `constexpr`.
					
				//	Compute the initial `1/8`th then mirror the remaining segments:
					typename co::difference_type constexpr N = N_size >> 2;// `1/8`th
					static_assert(-4 <  N_shift);
					generate<N + (-3 <  N_shift)>(y);
					if constexpr (-2 <= N_shift) _detail::copy_to(j - 2*N, _std::span(i, i + 1*N), [](V const &v) XTAL_0FN_(V(-v.imag(), -v.real())));
					if constexpr (-1 <= N_shift) _detail::copy_to(i + 2*N, _std::span(i, i + 2*N), [](V const &v) XTAL_0FN_(V( v.imag(), -v.real())));
					if constexpr (-0 <= N_shift) _detail::copy_to(i + 4*N, _std::span(i, i + 4*N), [](V const &v) XTAL_0FN_(V(-v.real(), -v.imag())));
					static_assert( 0 >= N_shift);// TODO: Extend to allow multiple copies using `seek`.
					
					return self();
				}
				
				///\returns\
				`that` transformed by the FFT, using `this` as the Fourier basis. \
				
				///\note\
				The size of both `this` and `that` must be expressible as an integral power of two, \
				and `1 < that.size() <= this->size()`. \

				template <isomorphic_q<T> Y>
				XTAL_FN1_(typename Y::template dual_t<T> &) transform(Y &that)
				XTAL_0FX
				XTAL_IF1 complex_q<V>
				{
					using I = typename Y::difference_type;
				
				//	Detect whether `Y` is a `product` of any `N_size` (by sleight of hand):
					bool constexpr degenerate = is_q<typename Y::template dual_t<Y>, Y>;

				//	Ensure the size of both domain and codomain are powers of two:
					I const n_size = that.size(); assert(2 <= n_size);
					I const h_size = n_size >> 1; assert(1 <= h_size);
					I const k_size = realize<I>::bit_floor_y((I) n_size); assert(n_size == 1 << k_size);
					I const K_size = realize<I>::bit_floor_y((I) N_size); assert(k_size <= K_size);

				//	Move all entries to their bit-reversed locations:
					for (I h = 0; h < h_size; ++h)
					{	_std::swap(that[h], that[realize<I>::bit_reverse_y(h, k_size)]);
					}
				
				//	Conjugate the input if computing the inverse transform of the codomain:
					if constexpr (degenerate)
					{	_detail::apply_to(that, XTAL_1FN_(_std::conj));
					}
				//	Compute the transform of `that` using the precomputed sinusoid via `datum`:
					for (I k = 0; k < k_size; ++k)
					{	I const kn = K_size - k;
						I const u = 1 << k;
						I const w = u << 1;
						I const n = n_size;
						for (I                  i = 0; i < u; i += 1)
						for (I knife = i << kn, j = i; j < n; j += w)
						{	V const y = that[j + u]*datum(knife);
							V const x = that[j + 0];
							that[j + u] = x - y;
							that[j + 0] = x + y;
						}
					}
				//	Conjugate and scale the output if computing the inverse transform of the codomain:
					if constexpr (degenerate)
					{	auto const u_size = _realized::template ratio_y<1>(n_size);
						_detail::apply_to(that, XTAL_1FN_(u_size*_std::conj));
					}
				
				//	Cast the output to the transformed domain:
					return that.template self<typename Y::template dual_t<T> &>();
				}
				///\returns a new `series` representing the FFT of `lhs`, \
				using `this` as the Fourier basis. \

				template <isomorphic_q<T> Y>
				XTAL_FN2_(typename Y::template dual_t<T>) transformation(Y that)
				XTAL_0FX
				{
					return transform(that);
				}

				///\returns `lhs` convolved with `rhs`, \
				using `this` as the Fourier basis. \

				template <isomorphic_q<T> Y>
				XTAL_FN1_(Y &) convolve(Y &lhs, Y rhs)
				XTAL_0FX
				{
					return transform(transform(lhs) *= transform(rhs));
				}
				///\returns a new `series` representing the convolution of `lhs` with `rhs`, \
				using `this` as the Fourier basis. \

				template <isomorphic_q<T> Y>
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
					T &s = self();
					if constexpr (complex_q<V>)
					{	T(constant_o<-1>).convolve(s, t);
					}
					else
					{	using W = typename _realized::aphex_t;
						using Y = typename recollate_t<W>::series::type;
						Y s_(s);
						Y t_(t);
						Y(constant_o<-1>).convolve(s_, t_);
						_detail::move_to(s.begin(), s_, XTAL_1FN_(_std::real));
					}
					return s;
				}
				XTAL_OP2_(T) * (T const &t)
				XTAL_0FX
				{
					return twin() *= t;
				}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		///\
		Represents a sequence that supports elementwise addition/subtracion, \
		where multiplication is performed by linear convolution. \
		
		///\note\
		The increment/decrement operators provide forward/backward iteration \
		based on finite differences/derivatives. \

	//	TODO: Generalize as the linear counterpart to `series::transform` using the z-transform. \

		struct serial
		{
			template <typename T>
			using hemitype = typename sum::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
			//	TODO: Subclass to define serial pairs like `complex`. \

				friend T;
				using co = hemitype<T>;
			
			public:
				using co::co;
				using co::self;
				using co::twin;
				using co::datum;

				///\
				Multiplication by linear convolution, truncated by `N_size`. \

				XTAL_OP1_(T &) *=(T const &t)
				XTAL_0EX
				{
				//	NOTE: Accuracy is better when looped from back-to-front, \
					but `MSVC` doesn't inline for some reason (even when the following is rephrased...). \

				//	for (count_t i = N_size;  ~--i;) {s[i] *= t[0];
				//	for (count_t j = i; 0 < j; --j ) {s[i] += t[j]*_s[i - j];}}

					auto &s = self();
					auto _s = self();
					auto constexpr h = N_size - 1; static_assert(1 < N_size);

					seek_f<N_size>([&, this](constant_q auto n)
					XTAL_0FN
					{	size_t constexpr i = h - n; s[i] *= t[0];
						seek_f<i>([&, this](constant_q auto m)
						XTAL_0FN
						{	size_t constexpr j = i - m; s[i] += _s[i - j]*t[j];
						});
					});
					return s;
				}
				XTAL_OP2_(T) * (T const &t)
				XTAL_0FX
				{	return twin() *= t;
				}
				
				///\
				Produces the successor by pairwise addition starting from `begin()`, \
				assuming the entries of `this` are finite differences/derivatives. \

				XTAL_OP1 ++ (int)
				XTAL_0EX
				{
					auto o = self(); operator++(); return o;
				}
				XTAL_OP1 ++ ()
				XTAL_0EX
				{
					auto constexpr N = N_size - 0;
					auto constexpr M = N_size - 1;
					seek_f<M>([&, this](auto i) XTAL_0FN_(datum(0 + i) += datum(1 + i)));
					return self().wrap();
				}

				///\
				Produces the predecessor by pairwise subtraction starting from `end()`, \
				assuming the entries of `this` are finite differences/derivatives. \

				XTAL_OP1 -- (int)
				XTAL_0EX
				{
					auto o = self(); operator--(); return o;
				}
				XTAL_OP1 -- ()
				XTAL_0EX
				{
					auto constexpr N = N_size - 0;
					auto constexpr M = N_size - 1;
					seek_f<M>([&, this](auto i) XTAL_0FN_(datum(M - i) -= datum(N - i)));
					return self().wrap();
				}

				XTAL_FN1_(T &) wrap()
				XTAL_0EX
				{
					auto &s = self();
					if constexpr (alpha_q<V>)
					{	s[0] -= _std::round(s[0]);
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

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
