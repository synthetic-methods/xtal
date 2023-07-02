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


////////////////////////////////////////////////////////////////////////////////

template <typename V>
struct collate
{
	using _realized = realize<V>;

	template <typename S>
	struct semitype
	{
		template <typename T>
		class homotype: public S
		{
			friend T;

		public:
			using S::S;

			///\returns `*this` with type `Y=T`. \

			template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&&) XTAL_REQ is_q<Y, T> {return static_cast<Y const &&>(XTAL_MOV_(*this));}
			template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&&) XTAL_REQ is_q<Y, T> {return static_cast<Y       &&>(XTAL_MOV_(*this));}
			template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&)  XTAL_REQ is_q<Y, T> {return static_cast<Y const  &>(*this);}
			template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&)  XTAL_REQ is_q<Y, T> {return static_cast<Y        &>(*this);}

			template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&&) {return reinterpret_cast<Y const &&>(XTAL_MOV_(*this));}
			template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&&) {return reinterpret_cast<Y       &&>(XTAL_MOV_(*this));}
			template <typename Y=T> XTAL_FN2 self() XTAL_0FX_(&)  {return reinterpret_cast<Y const  &>(*this);}
			template <typename Y=T> XTAL_FN2 self() XTAL_0EX_(&)  {return reinterpret_cast<Y        &>(*this);}

			///\returns a copy of `*this` with type `Y=T`. \

			template <typename Y=T>
			XTAL_FN2_(Y) twin()
			XTAL_0FX_(&)
			{
				return self<Y>();
			}
			///\
			Alias of `operator[]`. \

			XTAL_DO4_(XTAL_FN2 datum(XTAL_DEF i), self()[XTAL_REF_(i)]);

		};
		class type: public homotype<type>
		{
			using S_ = homotype<type>;

		public:
			using S_::S_;

		};
	};
	template <typename S>
	class subtype: public S
	{
		XTAL_LET_(auto) N_size = S::volume::value;

	public:
		using S::S;
		using solid = semitype<typename S::template solid<V>::type>;
		using fluid = semitype<typename S::template fluid<V>::type>;
		///\
		Event spool based on a insertion-sorted `std::array`. \
		
		struct spool
		{
			template <typename T>
			using hemitype = typename semitype<iterate_t<T>>::template homotype<T>;

			class type: public hemitype<type>
			{
				using R_ = hemitype<type>;

				using fluid_t = typename fluid::type;
				using index_t = typename fluid_t::iterator;
				using count_t = typename fluid_t::difference_type;

				fluid_t fluid_m;
				count_t begin_n = 0;
				count_t   end_n = 0;

			public:
				using R_::R_;

				///\note\
				The `size()` of the `std::initializer_list` determines the extent of lookup/lookahead: \
				- `1 == w.size()`: represents the next value only. \
				- `2 == w.size()`: represents the current and next values respectively. \

				XTAL_CON type(bracket_t<V> w)
				:	end_n {_std::distance(w.begin(), w.end())}
				,	fluid_m(w)
				{
					assert(0 < w.size());
				}

				XTAL_DO4_(XTAL_FN2 begin(count_t n=0), _std::next(fluid_m.begin(), begin_n + n))
				XTAL_DO4_(XTAL_FN2   end(count_t n=0), _std::prev(fluid_m.  end(),   end_n + n))
				
				XTAL_FN2    next(bool n=1) XTAL_0EX {return *begin(n);}
				XTAL_FN1 advance(bool n=1) XTAL_0EX {begin_n += n; return *begin();}
				XTAL_FN1 abandon(bool n=1)
				XTAL_0EX
				{
					if (n) {
						begin_n = 0;
						fluid_m.erase(fluid_m.begin(), end());
					}
					return *begin();
				}
				///\note\
				Cost can be amortized by invoking `advance` and `abandon` separately, \
				allowing for branchless `advance`ment. \

				XTAL_FN0 pop(index_t i)
				XTAL_0EX
				{
					begin_n -= i < begin();
					fluid_m.erase(i, 1);
					abandon(begin() == end());
				}
				XTAL_FN0 pop()
				XTAL_0EX
				{
					advance();
					abandon(begin() == end());
				}
				///\returns the top-most element assuming `front()` is minimal \
				(if initialized with two or more elements). \
				
				XTAL_FN2 top()
				XTAL_0EX
				{
					return *begin(end_n - 1);
				}

				XTAL_FN2 scan(V const &v)
				XTAL_0EX
				{
					return _std::lower_bound(fluid_m.begin(), fluid_m.end(), v);
				}
				///\note\
				Conflicting entries w.r.t. `==` are overwritten. \

				XTAL_FN0 push(V v)
				XTAL_0EX
				{
					auto v_ = scan(v); *v_ == v? _std::swap(*v_, v): poke(v_, XTAL_MOV_(v));
				}
				XTAL_FN0 poke(index_t v_, V v)
				XTAL_0EX
				{
					fluid_m.insert(v_, {XTAL_MOV_(v)});
				}
				XTAL_FN0 poke(index_t v_, index_t u_)
				XTAL_0EX
				{
					fluid_m.insert(v_, u_, 1);
				}

			};
		};
		///\
		Defines a fixed-width `type` that supports arithmetic operations. \

		struct group
		{
			template <typename T>
			using hemitype = typename solid::template homotype<T>;

			template <typename T>// requires arithmetic_operators_q<V>
			class homotype: public hemitype<T>
			{
				friend T;
				using R_ = hemitype<T>;

			public:
				using R_::R_;
				using R_::self;
				using R_::twin;
				using R_::datum;

				template <bracket_q U>
				XTAL_CXN homotype(U &&u)
				{
					_detail::move_to(R_::begin(), u);
				}
				template <bracket_q U>
				XTAL_CXN homotype(U const &u)
				{
					_detail::copy_to(R_::begin(), u);
				}
				XTAL_CON homotype(bracket_t<V> etc)
				{
					_detail::copy_to(R_::begin(), etc);
				}

				template <typename U>
				XTAL_CN2_(T &) refer(U &u)
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
					return (transmute(XTAL_REF_(fs)), ...);
				}
				XTAL_FN1 transmute(XTAL_DEF_(_std::invocable<V>) f)
				XTAL_0EX
				{
					_detail::apply_to(self(), XTAL_REF_(f));
					return self();
				}
				XTAL_FN1 transmute(_std::invocable<V> auto const &f)
				XTAL_0EX
				XTAL_REQ (0 < N_size) and (N_size <= _realized::alignment_v)
				{
					seek_f<N_size>([&, this] (auto i) XTAL_0FN_(datum(i) = f(datum(i))));
					return self();
				}

				///\
				Elementwise comparators. \

			//	XTAL_OP2        <=> (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) <=> t.datum(N)) <=>...         ) (seek_v<N_size>);}
				XTAL_OP2_(bool) ==  (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) ==  t.datum(N)) and...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) <=  (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) <=  t.datum(N)) and...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) >=  (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) >=  t.datum(N)) and...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) <   (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) <   t.datum(N)) and...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) >   (homotype const &t) XTAL_0FX {return [&, this]<auto ...N>(seek_t<N...>) XTAL_0FN_((datum(N) >   t.datum(N)) and...and true) (seek_v<N_size>);}

				XTAL_OP2_(T)    *  (XTAL_DEF w) XTAL_0FX {return twin() *= XTAL_REF_(w);}
				XTAL_OP2_(T)    /  (XTAL_DEF w) XTAL_0FX {return twin() /= XTAL_REF_(w);}
				XTAL_OP2_(T)    +  (XTAL_DEF w) XTAL_0FX {return twin() += XTAL_REF_(w);}
				XTAL_OP2_(T)    -  (XTAL_DEF w) XTAL_0FX {return twin() -= XTAL_REF_(w);}

				XTAL_OP1_(T &)  *= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {return seek_f<N_size>([&, this] (auto i) XTAL_0FN_(datum(i) *= XTAL_REF_(w))), self();}
				XTAL_OP1_(T &)  /= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {return seek_f<N_size>([&, this] (auto i) XTAL_0FN_(datum(i) /= XTAL_REF_(w))), self();}

			};
			class type: public homotype<type>
			{
				using S_ = homotype<type>;

			public:
				using S_::S_;

			};
		};
		///\
		Extends `group::type` with elementwise multiplication/division. \

		struct scalar
		{
			template <typename T>
			using hemitype = typename group::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
				friend T;
				using R_ = hemitype<T>;
			
			public:
				using R_::R_;
				using R_::self;
				using R_::twin;
				using R_::datum;

				///\
				The counterpart to `this` for which addition is linear, \
				and multiplication is performed via convolution. \
				
				template <typename Z>
				using dual_t = Z;

				XTAL_OP1_(T &) *= (bracket_t<V> w) XTAL_0EX {return self() *= T(w.begin(), w.end());}
				XTAL_OP1_(T &) /= (bracket_t<V> w) XTAL_0EX {return self() /= T(w.begin(), w.end());}				
				
				XTAL_OP1_(T &) *= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this] (auto i) XTAL_0FN_(datum(i) *= t.datum(i))), self();}
				XTAL_OP1_(T &) /= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this] (auto i) XTAL_0FN_(datum(i) /= t.datum(i))), self();}

				XTAL_FN2 sum()
				XTAL_0FX
				{
					return [&, this]<auto ...N>(seek_t<N...>)
						XTAL_0FN_(datum(N) +...+ V())
					(seek_v<N_size>);
				}
				XTAL_FN2 dot()
				XTAL_0FX
				{
					return _realized::square_y(*this).sum();
				}
				XTAL_FN2 dot(XTAL_DEF_(iterated_q) that)
				XTAL_0FX
				{
					return (*this*XTAL_REF_(that)).sum();
				}

				///\returns the mutually inverse `lhs +/- rhs`, \
				scaled by the value indexed by `N_bias`: `{-1, 0, 1} -> {0.5, std::sqrt(0.5), 1.0}`. \
				
				///\note\
				Useful for converting between e.g. exponential/hyperbolic or stereo/mid-side pairs. \

				template <int N_side=0>
				XTAL_FN2 reflected(int const n_bias=0)
				XTAL_0FX
				XTAL_REQ (N_size == 2)
				{
					auto const scale = _realized::explo_y(_realized::template unsquare_y<-1>(2), 1 - n_bias);
					auto const lhs = scale*datum(0);
					auto const rhs = scale*datum(1);
					if constexpr (N_side ==  0) {
						return T {lhs + rhs, lhs - rhs};
					}
					if constexpr (N_side == +1) {
						return lhs + rhs;
					}
					if constexpr (N_side == -1) {
						return lhs - rhs;
					}
				}
				///\
				Modifies `this`; \see `reflected()`.

				XTAL_FN2 reflect(int const n_bias=0)
				XTAL_0FX
				XTAL_REQ (N_size == 2)
				{
					return self() = reflected(n_bias);
				}

			};
			class type: public homotype<type>
			{
				using S_ = homotype<type>;

			public:
				using S_::S_;

			};
		};
		///\
		Extends `group::type` with elementwise addition/subtracion. \

		struct sector
		{
			template <typename T>
			using hemitype = typename group::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
				friend T;
				using R_ = hemitype<T>;
			
			public:
				using R_::R_;
				using R_::self;
				using R_::twin;
				using R_::datum;

				///\
				The counterpart to `this` for which multiplication is linear. \

				template <typename Z>
				using dual_t = typename scalar::type;

				XTAL_OP1_(T &) += (bracket_t<V> w) XTAL_0EX {return self() += T(w.begin(), w.end());}
				XTAL_OP1_(T &) -= (bracket_t<V> w) XTAL_0EX {return self() -= T(w.begin(), w.end());}
				
				XTAL_OP1_(T &) += (T const &t) XTAL_0EX {return seek_f<N_size>([&, this] (auto i) XTAL_0FN_(datum(i) += t.datum(i))), self();}
				XTAL_OP1_(T &) -= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this] (auto i) XTAL_0FN_(datum(i) -= t.datum(i))), self();}

			};
			class type: public homotype<type>
			{
				using S_ = homotype<type>;

			public:
				using S_::S_;

			};
		};
		///\
		Extends `sector::type` with multiplication defined by circular convolution. \

		struct series
		{
			template <typename T>
			using hemitype = typename sector::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
				friend T;
				using R_ = hemitype<T>;
			
				template <typename Y>
				using duel_t = typename Y::template dual_t<T>;

			public:
				using R_::R_;
				using R_::self;
				using R_::twin;
				using R_::datum;

				///\
				Generates part of the complex sinusoid determined by `std::pow(2, shift_o::value)`. \

				XTAL_CXN homotype(constant_q auto const shift_o)
				{
					generate<shift_o>();
				}
				///\
				Generates the power series with the given seed. \

				XTAL_CXN homotype(XTAL_DEF_(is_q<V>) v)
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
					using I = typename R_::difference_type;

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

					for (I i = _1; i < _H; ++i) {
						auto w = _realized::square_y(s[i]);
					
					//	Use the square of the previous value to populate the value at `i << 1`:
						I ii = i << 1;
						s[ii + 0] = w;
						s[ii + 1] = w*u;
					}
				//	Compute the final value if `N_limit` is odd:
					if constexpr (N_limit&1) {
						s[N1] = s[N2]*u;
					}
					return s;
				}

				///\returns `this` as the complex sinusoid with length `2*PI*std::pow(2, N_shift)`,  `-3 <= N_shift`. \
				
				///\note\
				To generate the FFT basis used by `transform` etc, use `N_shift == -1`. \

				template <int N_shift=0>
				XTAL_FN1_(T &) generate()
				XTAL_0EX
				XTAL_REQ complex_q<V>
				{
				//	Initialize the forwards and backwards iterators:
					auto const i = R_::begin();
					auto const j = R_::rend() - 1;
					
				//	Compute the fractional sinusoid for the given `N_size`:
					auto constexpr x = _realized::template patio_y<-1>(N_size);
					auto const     y = _realized::circle_y(x);// TODO: Make `constexpr`.
					
				//	Compute the initial `1/8`th then mirror the remaining segments:
					typename R_::difference_type constexpr N = N_size >> 2;// `1/8`th
					static_assert(-4 <  N_shift);
					generate<N + (-3 <  N_shift)>(y);
					if constexpr (-2 <= N_shift) _detail::copy_to(j - 2*N, _std::span(i, i + 1*N), [] (V const &v) XTAL_0FN_(V(-v.imag(), -v.real())));
					if constexpr (-1 <= N_shift) _detail::copy_to(i + 2*N, _std::span(i, i + 2*N), [] (V const &v) XTAL_0FN_(V( v.imag(), -v.real())));
					if constexpr (-0 <= N_shift) _detail::copy_to(i + 4*N, _std::span(i, i + 4*N), [] (V const &v) XTAL_0FN_(V(-v.real(), -v.imag())));
					static_assert( 0 >= N_shift);// TODO: Extend to allow multiple copies using `seek`.
					
					return self();
				}
				
				///\returns `that` transformed by the FFT, using `this` as the Fourier basis. \
				
				///\note\
				The size of both `this` and `that` must be expressible as an integral power of two, \
				and `1 < that.size() <= this->size()`. \

				template <isomorphic_q<T> Y>
				XTAL_FN1_(duel_t<Y> &) transform(Y &that)
				XTAL_0FX
				XTAL_REQ complex_q<V>
				{
					using I = typename Y::difference_type;
				
				//	Detect whether `Y` is a `scalar` of any `N_size` (by sleight of hand):
					bool constexpr degenerate = is_q<typename Y::template dual_t<Y>, Y>;

				//	Ensure the size of both domain and codomain are powers of two:
					I const n_size = that.size(); assert(2 <= n_size);
					I const h_size = n_size >> 1; assert(1 <= h_size);
					I const k_size = realize<I>::bit_floor_y((I) n_size); assert(n_size == 1 << k_size);
					I const K_size = realize<I>::bit_floor_y((I) N_size); assert(k_size <= K_size);

				//	Move all entries to their bit-reversed locations:
					for (I h = 0; h < h_size; ++h) {
						_std::swap(that[h], that[realize<I>::bit_reverse_y(h, k_size)]);
					}
				
				//	Conjugate the input if computing the inverse transform of the codomain:
					if constexpr (degenerate) {
						_detail::apply_to(that, [] XTAL_1FN_(_std::conj));
					}
				//	Compute the transform of `that` using the precomputed sinusoid via `datum`:
					for (I k = 0; k < k_size; ++k) {
						I const kn = K_size - k;
						I const u = 1 << k;
						I const w = u << 1;
						I const n = n_size;
						for (I                  i = 0; i < u; i += 1) {
						for (I knife = i << kn, j = i; j < n; j += w) {
							V const y = that[j + u]*datum(knife);
							V const x = that[j + 0];
							that[j + u] = x - y;
							that[j + 0] = x + y;
						}}
					}
				//	Conjugate and scale the output if computing the inverse transform of the codomain:
					if constexpr (degenerate) {
						auto const u_size = _realized::template ratio_y<1>(n_size);
						_detail::apply_to(that, [&]XTAL_1FN_(u_size*_std::conj));
					}
				
				//	Cast the output to the transformed domain:
					return that.template self<duel_t<Y> &>();
				}
				///\returns a new `series` representing the FFT of `lhs`, \
				using `this` as the Fourier basis. \

				template <isomorphic_q<T> Y>
				XTAL_FN2_(duel_t<Y>) transformation(Y that)
				XTAL_0FX
				{
					return transform(that);//.template self<duel_t<Y>>();
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
					if constexpr (complex_q<V>) {
						T(constant_f<-1>()).convolve(s, t);
					}
					else {
						using W = typename _realized::aphex_t;
						using Y = typename compose_s<S, collate<W>>::series::type;
						Y s_(s);
						Y t_(t);
						Y(constant_f<-1>()).convolve(s_, t_);
						_detail::move_to(s.begin(), s_, [] XTAL_1FN_(_std::real));
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
				using S_ = homotype<type>;

			public:
				using S_::S_;

			};
		};
		///\
		Extends `sector::type` with multiplication defined by linear convolution. \
		
		struct serial
		{
			template <typename T>
			using hemitype = typename sector::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
			//	TODO: Subclass to define serial pairs like `complex`. \

				friend T;
				using R_ = hemitype<T>;
			
			public:
				using R_::R_;
				using R_::self;
				using R_::twin;
				using R_::datum;

				///\
				Multiplication by linear convolution, truncated by `N_size`. \

				XTAL_OP1_(T &) *=(T const &t)
				XTAL_0EX
				{
					auto constexpr h = N_size;
					auto &s = self();
					auto _s = self();
					if constexpr (_realized::alignment_v < N_size) {
						for (count_t i = h;   ~--i;) {s[i] *= t[0];
						for (count_t j = i; j; --j ) {s[i] += t[j]*_s[i - j];}}
					}
					else {
						antiseek_f<h, 0>([&, this] (auto i) XTAL_0FN {s[i] *= t[0];
						antiseek_f<i, 1>([&, this] (auto j) XTAL_0FN {s[i] += t[j]*_s[i - j];});});
					}
					return s;
				}
				XTAL_OP2_(T) * (T const &t)
				XTAL_0FX {
					return twin() *= t;
				}
				
			};
			class type: public homotype<type>
			{
				using S_ = homotype<type>;

			public:
				using S_::S_;

			};
		};
		///\
		Extends `serial::type` with `++/--` defined in terms of finite differences/derivatives. \

		struct pulsar
		{
			template <typename T>
			using hemitype = typename serial::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
			//	TODO: Subclass to define serial pairs like `complex`. \

				friend T;
				using R_ = hemitype<T>;
			
			public:
				using R_::R_;
				using R_::self;
				using R_::twin;

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
					seek_f<M>([&, this] (auto i) XTAL_0FN_(s[0 + i] += s[1 + i]));
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
					seek_f<M>([&, this] (auto i) XTAL_0FN_(s[M - i] -= s[N - i]));
					s.reduce();
					return s;
				}

				XTAL_FN0 reduce()
				XTAL_0EX
				{
				}

			};
			class type: public homotype<type>
			{
				using S_ = homotype<type>;

			public:
				using S_::S_;

			};
		};
		///\
		Extends `pulsar::type` with `++/--` wrapping the initial argument to `{-1, 1}/2`. \

		struct phasor
		{
			template <typename T>
			using hemitype = typename pulsar::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
			//	TODO: Subclass to define serial pairs like `complex`. \

				friend T;
				using R_ = hemitype<T>;
			
			public:
				using R_::R_;
				using R_::self;
				using R_::twin;
				using R_::datum;

				///\
				Wraps the first argument to the range `+/- 1/2`, assuming `std::is_floating_point_v<V>`. \

				XTAL_FN0 reduce()
				XTAL_0EX
				{
					auto &s = self(); static_assert(alpha_q<V>);
					s[0] -= _std::round(s[0]);
				}

			};
			class type: public homotype<type>
			{
				using S_ = homotype<type>;

			public:
				using S_::S_;

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
