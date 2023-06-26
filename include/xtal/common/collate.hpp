#pragma once
#include "./any.hpp"
#include "./seek.hpp"
#include "./compose.hpp"
#include "./collect.hpp"



XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct realize;


namespace _detail
{///////////////////////////////////////////////////////////////////////////////
template <template <typename> typename T_>
struct create
{
	class type: public T_<type>
	{
		using co = T_<type>;

	public:
		using co::co;

	};
};
template <template <typename> typename T_>
using create_t = typename create<T_>::type;


}///////////////////////////////////////////////////////////////////////////////

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
		struct solid;

		struct siphon;// fluid
		struct sluice;// fluid
		struct scalar;// solid
		struct serial;// solid
		struct series;// solid
		struct product;// solid
		
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
				`*this` with type `Y=T`. \

				template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&&) XTAL_IF1 is_q<Y, T> {return static_cast<Y const &&>(_std::move(*this));}
				template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&&) XTAL_IF1 is_q<Y, T> {return static_cast<Y       &&>(_std::move(*this));}
				template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&)  XTAL_IF1 is_q<Y, T> {return static_cast<Y const  &>(*this);}
				template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&)  XTAL_IF1 is_q<Y, T> {return static_cast<Y        &>(*this);}

				template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&&) {return reinterpret_cast<Y const &&>(_std::move(*this));}
				template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&&) {return reinterpret_cast<Y       &&>(_std::move(*this));}
				template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&)  {return reinterpret_cast<Y const  &>(*this);}
				template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&)  {return reinterpret_cast<Y        &>(*this);}

				///\returns\
				a copy of `*this` with type `Y=T`. \

				template <typename Y=T>
				XTAL_FN2_(Y) twin()
				XTAL_0FX_(&)
				{
					return self<Y>();
				}
				///\
				Alias of `operator[]`. \

				XTAL_RN2_(XTAL_FN2 datum(XTAL_DEF i), self()[XTAL_REF_(i)]);

			};
			using type = _detail::create_t<homotype>;
		};
		struct fluid
		{
			using demitype = typename co::template fluid<V>::type;

			template <typename T>
			using homotype = typename graft<demitype>::template homotype<T>;

			using type = _detail::create_t<homotype>;
		};
		struct solid
		{
			using demitype = typename co::template solid<V>::type;

			template <typename T>
			using homotype = typename graft<demitype>::template homotype<T>;

			using type = _detail::create_t<homotype>;
		};

		///\
		Event spool based on a insertion-sorted `std::array`, \
		presenting a similar interface to `sluice`. \
		
		struct siphon
		{
			template <typename T>
			using hemitype = iterate_t<T>;

			class type: public hemitype<type>
			{
				using co = hemitype<type>;

				using fluid_t = typename fluid::type;
				using count_t = typename fluid_t::difference_type;

				fluid_t fluid_m;
				count_t begin_n = 0;
				count_t   end_n = 0;

			public:
				using co::co;

				XTAL_NEW type(bracket_t<V> w)
				:	end_n {(count_t) w.size()}
				,	fluid_m(w)
				{
				}
				XTAL_OP1 = (bracket_t<V> w)
				{
					end_n = (count_t) w.size();
					fluid_m = w;
					return *this;
				}

				XTAL_RN2_(XTAL_FN2 begin(count_t n=0), _std::next(fluid_m.begin(), begin_n + n))
				XTAL_RN2_(XTAL_FN2   end(count_t n=0), _std::prev(fluid_m.  end(),   end_n + n))
				
				XTAL_FN2    next(bool n=1) XTAL_0EX {return *begin(n);}
				XTAL_FN1 advance(bool n=1) XTAL_0EX {begin_n += n; return *begin();}
				XTAL_FN1 abandon(bool n=1)
				XTAL_0EX
				{
					if (n)
					{	begin_n = 0;
						fluid_m.erase(fluid_m.begin(), end());
					}
					return *begin();
				}
				///\note\
				Cost can be amortized by invoking `advance` and `abandon` separately, \
				allowing for branchless `advance`ment. \

				XTAL_FN0 pop()
				XTAL_0EX
				{
					advance(); if (this->empty()) abandon();
				}
				///\returns\
				the top-most element assuming `front()` is minimal \
				(if initialized with two or more elements). \
				
				XTAL_FN2 top()
				XTAL_0EX
				{
					return *begin(2 <= end_n);
				}

				///\note\
				Conflicting entries w.r.t. `==` are overwritten. \

				XTAL_FN0 push(V v)
				XTAL_0EX
				{
					auto v_ = _std::lower_bound(fluid_m.begin(), fluid_m.end(), v);
					if (*v_ == v)
					{	_std::swap(*v_, v);
					}
					else
					{	fluid_m.insert(v_, {_std::move(v)});
					}
				}

			};
		};
		///\
		Event spool based on an inverted `std::priority_queue`, \
		interchangeable with `siphon` as far as the interface aligns. \

		struct sluice
		{
			using demitype = _std::priority_queue<V, typename fluid::type, _std::greater<V>>;

			class type: public demitype
			{
				using co = demitype;

			public:
				using co::co;

				XTAL_FN0 advance(bool i=1) XTAL_0EX {if (i) co::pop();}
				XTAL_FN0 abandon(bool i=1) XTAL_0EX {if (i) while (not co::empty()) co::pop();}

			};
		};
		///\
		Represents a scalable `static_vector`. \

		struct scalar
		{
			template <typename T>
			using hemitype = typename solid::template homotype<T>;

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
				XTAL_IF1 (0 < N_size) and (N_size <= _realized::alignment_v)
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
			using type = _detail::create_t<homotype>;
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

				template <int N_side=0>
				XTAL_FN2 reflected(int const n_bias=0)
				XTAL_0FX
				XTAL_IF1 (N_size == 2)
				{
					auto const scale = _realized::explo_y(_realized::template unsquare_y<-1>(2), 1 - n_bias);
					auto const lhs = scale*datum(0);
					auto const rhs = scale*datum(1);
					if constexpr (N_side ==  0)
					{	return T {lhs + rhs, lhs - rhs};
					}
					else
					if constexpr (N_side == +1)
					{	return lhs + rhs;
					}
					else
					if constexpr (N_side == -1)
					{	return lhs - rhs;
					}
				}
				///\
				Modifies `this`; \see `reflected()`.

				XTAL_FN2 reflect(int const n_bias=0)
				XTAL_0FX
				XTAL_IF1 (N_size == 2)
				{
					return self() = reflected(n_bias);
				}

			};
			using type = _detail::create_t<homotype>;
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
			using type = _detail::create_t<homotype>;
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
					auto const o = _realized::template explo_y<N_index>(u);
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
						using Y = typename compose_s<S, collate<W>>::series::type;
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
			using type = _detail::create_t<homotype>;
		};
		///\
		Represents a sequence that supports elementwise addition/subtracion, \
		where multiplication is performed by linear convolution. \
		
		///\note\
		The increment/decrement operators provide forward/backward iteration \
		based on finite differences/derivatives. \

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
					auto constexpr h = N_size;
					auto &s = self();
					auto _s = self();
					if constexpr (_realized::alignment_v < N_size)
					{	for (count_t i = h;   ~--i;) {s[i] *= t[0];
						for (count_t j = i; j; --j ) {s[i] += t[j]*_s[i - j];}}
					}
					else
					{	antiseek_f<h, 0>([&, this](auto i) XTAL_0FN {s[i] *= t[0];
						antiseek_f<i, 1>([&, this](auto j) XTAL_0FN {s[i] += t[j]*_s[i - j];});});
					}
					return s;
				}
				XTAL_OP2_(T) * (T const &t)
				XTAL_0FX
				{	return twin() *= t;
				}
				
			};
			using type = _detail::create_t<homotype>;
		};
		struct pulsar
		{
			template <typename T>
			using hemitype = typename serial::template homotype<T>;

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

				XTAL_RN2_(XTAL_FN2 datum(), self()[0]);

				///\
				Produces the successor by pairwise addition starting from `begin()`, \
				assuming the entries of `this` are finite differences/derivatives. \

				XTAL_OP1 ++ (int)
				XTAL_0EX
				{
					auto t = twin(); operator++(); return t;
				}
				XTAL_OP1 ++ ()
				XTAL_0EX
				{
					auto &s = self();
					auto constexpr N = N_size - 0;
					auto constexpr M = N_size - 1;
					seek_f<M>([&, this](auto i) XTAL_0FN_(s[0 + i] += s[1 + i]));
					s.reduce();
					return s;
				}

				///\
				Produces the predecessor by pairwise subtraction starting from `end()`, \
				assuming the entries of `this` are finite differences/derivatives. \

				XTAL_OP1 -- (int)
				XTAL_0EX
				{
					auto t = twin(); operator--(); return t;
				}
				XTAL_OP1 -- ()
				XTAL_0EX
				{
					auto &s = self();
					auto constexpr N = N_size - 0;
					auto constexpr M = N_size - 1;
					seek_f<M>([&, this](auto i) XTAL_0FN_(s[M - i] -= s[N - i]));
					s.reduce();
					return s;
				}

				XTAL_FN0 reduce()
				XTAL_0EX
				{
				}

			};
			using type = _detail::create_t<homotype>;
		};
		struct phasor
		{
			template <typename T>
			using hemitype = typename pulsar::template homotype<T>;

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
				Wraps the first argument to the range `+/- 1/2`, assuming `std::is_floating_point_v<V>`. \

				XTAL_FN0 reduce()
				XTAL_0EX
				{
					auto &s = self(); static_assert(alpha_q<V>);
					s[0] -= _std::round(s[0]);
				}

			};
			using type = _detail::create_t<homotype>;
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
