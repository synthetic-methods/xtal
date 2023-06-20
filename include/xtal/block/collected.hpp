#pragma once
#include "./any.hpp"
#include "../common/seek.hpp"





XTAL_ENV_(push)
namespace xtal::block
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
template <typename V>
struct collected
{
	using _realized = realize<V>;

	template <typename S>
	class subtype: public S
	{
		using co = S;

		XTAL_LET N_size = co::volume::value;

	public:
		using co::co;

		using fluid = typename co::template fluid<V>;
		using solid = typename co::template solid<V>;

		template <typename U>
		using recollected_t = typename collected<U>::template subtype<S>;

		struct buffer;
		struct sluice;
		struct siphon;
		struct scalar;
		struct serial;
		struct series;
		struct couple;
		
		struct buffer
		{
			using type = typename fluid::type;

		};

		///\
		Event spool based on an inverted `std::priority_queue`, \
		presenting a similar interface to `siphon`. \

		struct sluice
		{
			using demitype = _std::priority_queue<V, typename fluid::type, _std::greater<V>>;

			template <typename T>
			class homotype: public demitype
			{
				friend T;
				using co = demitype;
				using count_t = typename co:: size_type;
				using event_t = typename co::value_type;

				using next_t = event_t const &;

			public:
				using co::co;

				XTAL_FN2_(count_t) completed()           XTAL_0EX {return            0;}
				XTAL_FN2_(count_t) remaining()           XTAL_0EX {return co::  size();}
				XTAL_FN1_(void)      advance(bool i=1)   XTAL_0EX {if (i) co::   pop();}
				XTAL_FN1_(void)      abandon(bool i=1)   XTAL_0EX {if (i) co:: clear();}
				XTAL_FN2_(next_t)       next()           XTAL_0EX {return co::   top();}
				XTAL_FN1_(sign_t)       push(XTAL_DEF o) XTAL_0EX {return co::  push(XTAL_REF_(o)), 1;}

			};
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

		struct siphon
		{
			using demitype = typename fluid::type;

			template <typename T>
			class homotype: demitype
			{
				friend T;
				using co = demitype;

				using  size_t = typename co::      size_type;
				using event_t = typename co::     value_type;
				using count_t = typename co::difference_type;
				using point_t = typename co::iterator;

				using next_t = event_t const &;

				point_t point_m;

			public:
				using co::co;

				XTAL_NEW homotype()
				XTAL_0EX
				:	co {event_t(_std::numeric_limits<typename event_t::head_t>::max())}
				,	point_m {co::begin()}
				{
				}
				XTAL_FN2_(point_t)     begin() XTAL_0EX {return  point_m;}
				XTAL_FN2_(count_t) completed() XTAL_0EX {return _std::distance(co::begin(), begin());}
				XTAL_FN2_(count_t) remaining() XTAL_0EX {return _std::distance(    begin(),   end());}
				XTAL_FN2_(point_t)       end() XTAL_0EX {return                _std::prev(co::end());}
				///\
				\returns the result of queuing the given message, \
				with zero indicating that the message was already scheduled. \
				
				///\
				\note Conflicting entries are overwritten (only `event_t::head`s are compared by e.g. `==`). \

				XTAL_FN1_(sign_t) push(event_t e)
				XTAL_0EX
				{
					auto e_ = _std::lower_bound(co::begin(), end(), e);
					if (*e_ == e)
					{	_std::swap(*e_, e);
						return e_->tail() != e.tail();
					}
					else
					{	co::insert(e_, {e});
						return sign_f<1>(point_m - e_);
					}
				}
				XTAL_FN2_(next_t)    next(bool i=1) XTAL_0EX {return *(point_m +  i);}
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

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		struct scalar
		{
			using demitype = typename co::template solid<V>::type;

			template <typename T>// requires field_operators_q<V>
			class homotype: public demitype
			{
				friend T;
				using co = demitype;

			public:
				using co::co;

				template <iterate_q U> requires (not is_q<U, V>)
				XTAL_NEW_(explicit) homotype(U &&u)
				:	co()
				{
					_detail::move_to(co::begin(), u);
				}
				template <iterate_q U> requires (not is_q<U, V>)
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

				///\
				Read accessor. \

				template <typename Y=T>
				XTAL_FN2_(Y) twin()
				XTAL_0FX_(&)
				{
					return self<Y>();
				}
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
				XTAL_RN2_(XTAL_FN2 at(XTAL_DEF i), self()[XTAL_REF_(i)]);

				///\
				Elementwise transformer. \

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
					seek_f<N_size>([&, this](auto i) XTAL_0FN_(at(i) = f(at(i))));
					return self();
				}
				

				///\
				Elementwise comparators. \

			//	XTAL_OP2        <=> (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((at(N) <=> t.at(N)) <=>...         ) (seek_v<N_size>);}
				XTAL_OP2_(bool) ==  (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((at(N) ==  t.at(N)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) <=  (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((at(N) <=  t.at(N)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) >=  (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((at(N) >=  t.at(N)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) <   (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((at(N) <   t.at(N)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) >   (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((at(N) >   t.at(N)) and ...and true) (seek_v<N_size>);}

				XTAL_OP2_(T)    *  (XTAL_DEF w) XTAL_0FX {return twin() *= XTAL_REF_(w);}
				XTAL_OP2_(T)    /  (XTAL_DEF w) XTAL_0FX {return twin() /= XTAL_REF_(w);}
				XTAL_OP2_(T)    +  (XTAL_DEF w) XTAL_0FX {return twin() += XTAL_REF_(w);}
				XTAL_OP2_(T)    -  (XTAL_DEF w) XTAL_0FX {return twin() -= XTAL_REF_(w);}

				XTAL_OP1_(T &)  *= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(at(i) *= XTAL_REF_(w))), self();}
				XTAL_OP1_(T &)  /= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(at(i) /= XTAL_REF_(w))), self();}

				XTAL_OP2        -> () XTAL_0FX {return static_cast<const pointed_t<T>*>(this);}
				XTAL_OP2        -> () XTAL_0EX {return static_cast<      pointed_t<T>*>(this);}

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

		///\
		The increment/decrement operators provide forward/backward iteration \
		based on finite differences/derivatives. \

	//	TODO: Reify `{phase, frequency}` with sample-rate to define `control::phasor`. \
	
	//	TODO: Combine `control::phasor` with the aperiodic counterpart `{counter, trigger}`, \
		allowing event-to-signal integration `{{delta}, {omega}} -> {{sigma, delta}, {phi, omega}}`. \

		struct serial
		{
			template <typename T>
			using hemitype = typename scalar::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
			//	TODO: Subclass to define serial pairs like `complex`. \

				friend T;
				using co = hemitype<T>;
			
			public:
				using co::co;
				using co::at;
				using co::self;
				using co::twin;

				XTAL_OP1_(T &) += (bracket_t<V> w) XTAL_0EX {return self() += T(w.begin(), w.end());}
				XTAL_OP1_(T &) -= (bracket_t<V> w) XTAL_0EX {return self() -= T(w.begin(), w.end());}
				
				XTAL_OP1_(T &) += (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(at(i) += t.at(i))), self();}
				XTAL_OP1_(T &) -= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(at(i) -= t.at(i))), self();}

				///\
				Multiplication by linear convolution, truncated by `N_size`. \

				XTAL_OP1_(T &) *=(T const &t)
				XTAL_0EX
				{
				//	NOTE: Accuracy is better when looped from back-to-front, \
					but `MSVC` doesn't inline for some reason (even when the following is rephrased...). \

				//	for (iota_t i = N_size;  ~--i;) {s[i] *= t[0];
				//	for (iota_t j = i; 0 < j; --j ) {s[i] += t[j]*_s[i - j];
				//	}}

					auto &s = self();
					auto _s = self();
					auto constexpr h = N_size - 1;

					seek_f<N_size>([&, this](auto n)
					XTAL_0FN
					{	size_t constexpr i = h - n; s[i] *= t[0];
						seek_f<i>([&, this](auto m)
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
					seek_f<M>([&, this](auto i) XTAL_0FN_(at(0 + i) += at(1 + i)));
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
					seek_f<M>([&, this](auto i) XTAL_0FN_(at(M - i) -= at(N - i)));
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
		///\
		Represents a sequence that supports elementwise addition/subtracion, \
		where multiplication is performed by circular convolution. \

		struct series
		{
			template <typename T>
			using hemitype = typename serial::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
				friend T;
				using co = hemitype<T>;
			
			public:
				using co::co;
				using co::at;
				using co::self;
				using co::twin;

				///\
				The transformed domain of the FFT (\see `transform`), \
				in which multiplication is performed elementwise (\see `convolve`). \

				using transformed_t = typename couple::type;

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
				XTAL_IF1 bit_ceiling_q<N_size, 2> and complex_q<V>
				{
				//	Compute the segment indicies for `1/8`, `1/4`, and `1/2`:
					typename co::difference_type constexpr H = N_size >> 2;
					auto const i = co::begin();
					auto const i0_8 = i + 0*H;
					auto const i1_8 = i + 1*H;
					auto const i2_8 = i + 2*H;
					auto const i4_8 = i + 4*H;
					auto const j2_8 = _std::make_reverse_iterator(i2_8 + 1);
					
				//	Compute the fractional sinusoid for the given `N_size`:
					auto constexpr x = _realized::template patio_y<-1>(N_size);
					auto const     y = _realized::circle_y(x);// TODO: Make `constexpr`.
					
				//	Compute the initial `1/8`th then mirror the remaining segments:
					static_assert(-4 <  N_shift);// NOTE: Minimum period is 1/8th.
					generate<H + (-3 <  N_shift)>(y);
					if constexpr (-2 <= N_shift) _detail::copy_to(j2_8, _std::span(i0_8, i1_8), [](V const &v) XTAL_0FN_(V(-v.imag(), -v.real())));
					if constexpr (-1 <= N_shift) _detail::copy_to(i2_8, _std::span(i0_8, i2_8), [](V const &v) XTAL_0FN_(V( v.imag(), -v.real())));
					if constexpr (-0 <= N_shift) _detail::copy_to(i4_8, _std::span(i0_8, i4_8), [](V const &v) XTAL_0FN_(V(-v.real(), -v.imag())));
					static_assert( 0 >= N_shift);// TODO: Extend to allow multiple copies using `seek`.
					
					return self();
				}
				
				///\returns\
				`that` transformed by the FFT, using `this` as the Fourier basis. \
				
				///\note\
				The size of both `this` and `that` must be expressible as an integral power of two, \
				and `1 < that.size() <= this->size()`. \

				template <iso_q<T> Y>
				XTAL_FN1_(typename Y::transformed_t &) transform(Y &that)
				XTAL_0FX
				XTAL_IF1 bit_ceiling_q<N_size, 1> and complex_q<V>
				{
					using I = typename Y::difference_type;

				//	Determine whether the input corresponds to the codomain (possibly with a smaller `N_size`):
				//	bool constexpr degenerate = if_q<transformed_t, Y>;
					bool constexpr degenerate = not requires (Y y) {y.generate();};

				//	Ensure the size of both domain and codomain are powers of two:
					I const n_size = that.size(); assert(2 <= n_size);
					I const h_size = n_size >> 1; assert(1 <= h_size);
					I const k_size = bit_ceiling_y(n_size); assert(n_size == 1 << k_size);
					I const K_size = bit_ceiling_y(N_size); assert(k_size <= K_size);

				//	Move all entries to their bit-reversed locations:
					for (I h = 0; h < h_size; ++h)
					{	_std::swap(that[h], that[bit_reverse_y(h, k_size)]);
					}
				
				//	Conjugate the input if computing the inverse transform of the codomain:
					if constexpr (degenerate)
					{	_detail::apply_to(that, XTAL_1FN_(_std::conj));
					}
				//	Compute the transform of `that` using the precomputed sinusoid via `self`:
					for (I k = 0; k < k_size; ++k)
					{	I const kn = K_size - k;
						I const u = 1 << k;
						I const w = u << 1;
						I const n = n_size;
						for (I                  i = 0; i < u; i += 1)
						for (I knife = i << kn, j = i; j < n; j += w)
						{	V const y = that[j + u]*at(knife);
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
					return that.template self<typename Y::transformed_t &>();
				}
				///\returns a new `series` representing the FFT of `lhs`, \
				using `this` as the Fourier basis. \

				template <iso_q<T> Y>
				XTAL_FN2_(typename Y::transformed_t) transformation(Y that)
				XTAL_0FX
				{
					return transform(that);
				}

				///\returns `lhs` convolved with `rhs`, \
				using `this` as the Fourier basis. \

				template <iso_q<T> Y>
				XTAL_FN1_(Y &) convolve(Y &lhs, Y rhs)
				XTAL_0FX
				{
					return transform(transform(lhs) *= transform(rhs));
				}
				///\returns a new `series` representing the convolution of `lhs` with `rhs`, \
				using `this` as the Fourier basis. \

				template <iso_q<T> Y>
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
					{	using W = typename _realized::alphaplex_t;
						using Y = typename recollected_t<W>::series::type;
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
		Represents a sequence that supports elementwise multiplication/division. \

		struct couple
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
				using co::at;
				using co::self;
				using co::twin;

				///\
				The transformed domain of the inverse FFT, \
				in which multiplication is performed via convolution. \
				
				using transformed_t = typename series::type;

			//	Elementwise multiplication/division:

				XTAL_OP1_(T &) *= (bracket_t<V> w) XTAL_0EX {return self() *= T(w.begin(), w.end());}
				XTAL_OP1_(T &) /= (bracket_t<V> w) XTAL_0EX {return self() /= T(w.begin(), w.end());}				
				
				XTAL_OP1_(T &) *= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(at(i) *= t.at(i))), self();}
				XTAL_OP1_(T &) /= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(at(i) /= t.at(i))), self();}

				///\returns\
				the mutually inverse couple `(lhs +/- rhs)*reflector()`, \
				e.g. for exponential or mid/side pairs. \

				template <int N_bias=0>
				XTAL_FN2 reflected()
				XTAL_0FX
				XTAL_IF1 (N_size == 2)
				{
					auto const &lhs = at(0)*reflector<N_bias>();
					auto const &rhs = at(1)*reflector<N_bias>();
					return T {lhs + rhs, lhs - rhs};
				}
				template <int N_bias=0>
				XTAL_FZ2 reflector()
				XTAL_IF1 (N_size == 2)
				{
					using alpha_t = typename _realized::alpha_t;
					switch (N_bias)
					{
						case +1: return (alpha_t) 1.0000000000000000000000000000000000000;
						case  0: return (alpha_t) 0.7071067811865475244008443621048490393;
						case -1: return (alpha_t) 0.5000000000000000000000000000000000000;
					}
				//	return _realized::explo_y(1 - N_bias, _realized::template unsquare_y<-1>((alpha_t) 2));
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
