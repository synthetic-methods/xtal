#pragma once
#include "./etc.hpp"
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
class isotype: public T_<isotype<T_>>
{
	using S_ = T_<isotype<T_>>;
	
public:
	using S_::S_;

};


}///////////////////////////////////////////////////////////////////////////////

template <typename T>
concept collated_p = requires ()
{
	typename T::collated;
	requires constant_q<typename T::collated>;
	requires (T::collated::value != 0);
	
	typename T::template spool<unit_t>;
	requires iterated_q<typename T::template spool<unit_t>::type>;

};
template <typename ...Ts>
concept collated_q = (... and collated_p<Ts>);


template <int ...Ns>
struct collate;

template <int ...Ns>
using collate_t = typename collate<Ns...>::type;

template <int N_size>
struct collate<N_size>
{
	using metatype = collect_t<N_size>;

	template <typename S>
	class subtype: public S
	{
		template <typename V>
		struct solid_
		{
			using demikind = typename metatype::template solid<V>;
			using demitype = typename demikind::type;
		
			template <typename T>
			using homotype = typename deform<T>::template subtype<demitype>;

			using type = _detail::isotype<homotype>;

		};
		template <typename V>
		struct fluid_
		{
			using demikind = typename metatype::template fluid<V>;
			using demitype = typename demikind::type;
		
			template <typename T>
			using homotype = typename deform<T>::template subtype<demitype>;

			using type = _detail::isotype<homotype>;

		};
		
	public:
		using S::S;
		using collated = constant_t<N_size>;

		///\
		Event spool based on a insertion-sorted `std::array`. \
		
		template <typename V>
		struct spool
		{
			using _realized = realize<V>;
			
			template <typename T>
			using hemitype = typename deform<T>::template subtype<iterate_t<T>>;

			class type: public hemitype<type>
			{
				using R_ = hemitype<type>;

				using value_t = V;
				using fluid_t = typename fluid_<V>::type;
				using valve_t = typename fluid_t::iterator;
				using count_t = typename fluid_t::difference_type;

				fluid_t fluid_m{};
				count_t begin_n = 0;
				count_t   end_n = 0;

			public:
				using R_::R_;
				
				///\note\
				The `size()` of the `std::initializer_list` determines the collated of lookup/lookahead. \

				XTAL_CON type(bracket_t<V> w)
				:	end_n {_std::distance(w.begin(), w.end())}
				,	fluid_m(w)
				{}

				XTAL_TO2_(XTAL_FN2     begin(count_t n=0), _std::next(fluid_m.begin(), begin_n + n))
				XTAL_TO2_(XTAL_FN2       end(count_t n=0), _std::prev(fluid_m.  end(),   end_n + n))
				XTAL_FN2_(value_t &)    peek(count_t n=0) XTAL_0EX {              return *begin(n);}
				XTAL_FN1_(value_t &) advance(count_t n=1) XTAL_0EX {begin_n += n; return *begin(0);}
				XTAL_FN1_(value_t &) abandon(bool    n=1)
				XTAL_0EX
				{
					if (n) {
						begin_n = 0;
						clear();
					}
					return *begin();
				}
				XTAL_FN0 clear()
				XTAL_0EX
				{
					fluid_m.erase(fluid_m.begin(), end());
				}

				///\note\
				Cost can be amortized by invoking `advance` and `abandon` separately, \
				allowing for branchless `advance`ment. \

				XTAL_FN0 pop(valve_t i)
				XTAL_0EX
				{
					assert(i < end());
					begin_n -= i < begin();
					fluid_m.erase(i);
					abandon(begin() == end());
				}
				XTAL_FN0 pop()
				XTAL_0EX
				{
					advance();
					abandon(begin() == end());
				}
				XTAL_FN2_(valve_t) scan(XTAL_DEF w)
				XTAL_0EX
				{
					return _std::lower_bound(fluid_m.begin(), fluid_m.end()
					,	XTAL_REF_(w)
					);
				}
				XTAL_FN2_(valve_t) scan(XTAL_DEF w, XTAL_DEF f)
				XTAL_0EX
				{
					return _std::lower_bound(fluid_m.begin(), fluid_m.end()
					,	XTAL_REF_(w)
					,	[f = XTAL_REF_(f)] (XTAL_DEF x, XTAL_DEF y) XTAL_0FN_(f(x) < f(y))
					);
				}
				///\note\
				Conflicting entries w.r.t. `==` are overwritten. \

				XTAL_FN1_(valve_t) push(V v)
				XTAL_0EX
				{
					valve_t v_ = scan(v);
					if (*v_ == v) {
						_std::swap(*v_, v); return v_;
					}
					else {
						return poke(v_, XTAL_MOV_(v));
					}
				}
				template <is_q<V> W>
				XTAL_FN1_(valve_t) poke(valve_t v_, W &&w)
				XTAL_0EX
				{
					return fluid_m.insert(v_, XTAL_REF_(w));
				}
				XTAL_FN1_(valve_t) poke(valve_t v_, XTAL_DEF ...ws)
				XTAL_0EX
				{
					return fluid_m.insert(v_, V(XTAL_REF_(ws)...));
				}
				XTAL_FN1_(valve_t) poke(valve_t v_, XTAL_DEF ...ws)
				XTAL_0EX
				XTAL_REQ_(fluid_m.inplace(v_, XTAL_REF_(ws)...))
				{
					return fluid_m.inplace(v_, XTAL_REF_(ws)...);
				}

			};
		};
		///\
		Defines a fixed-width `type` that supports arithmetic operations. \

		template <typename V>
		struct group
		{
			using _realized = realize<V>;
			
			template <typename T>
			using hemitype = typename solid_<V>::template homotype<T>;

			template <typename T>// requires field_operators_q<V>
			class homotype: public hemitype<T>
			{
				friend T;
				using R_ = hemitype<T>;

			public:
				using R_::R_;
				using R_::self;
				using R_::twin;
				using R_::operator[];
			//	XTAL_LET v_ = static_cast<V& (R_::*) (size_t) &>(&R_::operator[]);

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
					seeker_f<N_size>([&, this] (auto i) XTAL_0FN_(operator[](i) = f(operator[](i))));
					return self();
				}

				///\
				Elementwise comparators. \

				XTAL_OP2 <=> (homotype const &t)
				XTAL_0FX
				{
					homotype const &s = *this;
					if (0);
					else if (s <  t) return _std::strong_ordering::      less;
					else if (s == t) return _std::strong_ordering::     equal;
					else if (s  > t) return _std::strong_ordering::   greater;
					else             return _std::strong_ordering::equivalent;
				}
				XTAL_OP2_(bool) == (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(seek_t<I...>) XTAL_0FN_(... and (operator[](I) == t[I])) (seek_f<N_size> {});}
				XTAL_OP2_(bool) <= (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(seek_t<I...>) XTAL_0FN_(... and (operator[](I) <= t[I])) (seek_f<N_size> {});}
				XTAL_OP2_(bool) >= (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(seek_t<I...>) XTAL_0FN_(... and (operator[](I) >= t[I])) (seek_f<N_size> {});}
				XTAL_OP2_(bool) <  (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(seek_t<I...>) XTAL_0FN_(... and (operator[](I) <  t[I])) (seek_f<N_size> {});}
				XTAL_OP2_(bool) >  (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(seek_t<I...>) XTAL_0FN_(... and (operator[](I) >  t[I])) (seek_f<N_size> {});}

				XTAL_OP2_(T)    *  (XTAL_DEF w) XTAL_0FX {return twin() *= XTAL_REF_(w);}
				XTAL_OP2_(T)    /  (XTAL_DEF w) XTAL_0FX {return twin() /= XTAL_REF_(w);}
				XTAL_OP2_(T)    +  (XTAL_DEF w) XTAL_0FX {return twin() += XTAL_REF_(w);}
				XTAL_OP2_(T)    -  (XTAL_DEF w) XTAL_0FX {return twin() -= XTAL_REF_(w);}

				XTAL_OP1_(T &)  *= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {return seeker_f<N_size>([&, this] (auto i) XTAL_0FN_(operator[](i) *= XTAL_REF_(w))), self();}
				XTAL_OP1_(T &)  /= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {return seeker_f<N_size>([&, this] (auto i) XTAL_0FN_(operator[](i) /= XTAL_REF_(w))), self();}

			};
			using type = _detail::isotype<homotype>;
		};
		///\
		Extends `group::type` with elementwise multiplication/division. \

		template <typename V>
		struct scalar
		{
			using _realized = realize<V>;
			
			template <typename T>
			using hemitype = typename group<V>::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
				friend T;
				using R_ = hemitype<T>;
			
			public:
				using R_::R_;
				using R_::self;
				using R_::twin;
				using R_::operator[];

				///\
				The counterpart to `this` for which addition is linear, \
				and multiplication is performed via convolution. \
				
				template <typename Z>
				using dual_t = Z;

				XTAL_OP1_(T &) *= (bracket_t<V> w) XTAL_0EX {return self() *= T(w.begin(), w.end());}
				XTAL_OP1_(T &) /= (bracket_t<V> w) XTAL_0EX {return self() /= T(w.begin(), w.end());}				
				
				XTAL_OP1_(T &) *= (T const &t) XTAL_0EX {return seeker_f<N_size>([&, this] (auto i) XTAL_0FN_(operator[](i) *= t[i])), self();}
				XTAL_OP1_(T &) /= (T const &t) XTAL_0EX {return seeker_f<N_size>([&, this] (auto i) XTAL_0FN_(operator[](i) /= t[i])), self();}

				XTAL_FN2 sum()
				XTAL_0FX
				{
					return [&, this]<auto ...N>(seek_t<N...>)
						XTAL_0FN_(operator[](N) +...+ V())
					(seek_f<N_size> {});
				}
				XTAL_FN2 dot()
				XTAL_0FX
				{
					return _realized::square_y(*this).sum();
				}
				XTAL_FN2 dot(XTAL_DEF_(iterated_q) that)
				XTAL_0FX
				{
					return (twin() *= XTAL_REF_(that)).sum();
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
					auto const lhs = scale*operator[](0);
					auto const rhs = scale*operator[](1);
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
			using type = _detail::isotype<homotype>;
		};
		///\
		Extends `group::type` with elementwise addition/subtracion. \

		template <typename V>
		struct sector
		{
			using _realized = realize<V>;
			
			template <typename T>
			using hemitype = typename group<V>::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
				friend T;
				using R_ = hemitype<T>;
			
			public:
				using R_::R_;
				using R_::self;
				using R_::twin;
				using R_::operator[];

				///\
				The counterpart to `this` for which multiplication is linear. \

				template <typename Z>
				using dual_t = typename scalar<V>::type;

				XTAL_OP1_(T &) += (bracket_t<V> w) XTAL_0EX {return self() += T(w.begin(), w.end());}
				XTAL_OP1_(T &) -= (bracket_t<V> w) XTAL_0EX {return self() -= T(w.begin(), w.end());}
				
				XTAL_OP1_(T &) += (T const &t) XTAL_0EX {return seeker_f<N_size>([&, this] (auto i) XTAL_0FN_(operator[](i) += t[i])), self();}
				XTAL_OP1_(T &) -= (T const &t) XTAL_0EX {return seeker_f<N_size>([&, this] (auto i) XTAL_0FN_(operator[](i) -= t[i])), self();}

			};
			using type = _detail::isotype<homotype>;
		};
		///\
		Extends `sector::type` with multiplication defined by circular convolution. \

		template <typename V>
		struct series
		{
			using _realized = realize<V>;
			
			template <typename T>
			using hemitype = typename sector<V>::template homotype<T>;

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
				using R_::operator[];

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
				XTAL_REQ complex_operators_q<V>
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

				template <isomorphic_p<T> Y>
				XTAL_FN1_(duel_t<Y> &) transform(Y &that)
				XTAL_0FX
				XTAL_REQ complex_operators_q<V>
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
				//	Compute the transform of `that` using the precomputed sinusoid via `operator[]`:
					for (I k = 0; k < k_size; ++k) {
						I const kn = K_size - k;
						I const u = 1 << k;
						I const w = u << 1;
						I const n = n_size;
						for (I                  i = 0; i < u; i += 1) {
						for (I knife = i << kn, j = i; j < n; j += w) {
							V const y = that[j + u]*operator[](knife);
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

				template <isomorphic_p<T> Y>
				XTAL_FN2_(duel_t<Y>) transformation(Y that)
				XTAL_0FX
				{
					return transform(that);//.template self<duel_t<Y>>();
				}

				///\returns `lhs` convolved with `rhs`, \
				using `this` as the Fourier basis. \

				template <isomorphic_p<T> Y>
				XTAL_FN1_(Y &) convolve(Y &lhs, Y rhs)
				XTAL_0FX
				{
					return transform(transform(lhs) *= transform(rhs));
				}
				///\returns a new `series` representing the convolution of `lhs` with `rhs`, \
				using `this` as the Fourier basis. \

				template <isomorphic_p<T> Y>
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
					if constexpr (complex_operators_q<V>) {
						T(constant_t<-1>{}).convolve(s, t);
					}
					else {
						using W = typename _realized::aphex_t;
						using Y = typename series<W>::type;
						Y s_(s);
						Y t_(t);
						Y(constant_t<-1>{}).convolve(s_, t_);
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
			using type = _detail::isotype<homotype>;
		};
		///\
		Extends `sector::type` with multiplication defined by linear convolution. \
		
		template <typename V>
		struct serial
		{
			using _realized = realize<V>;
			
			template <typename T>
			using hemitype = typename sector<V>::template homotype<T>;

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
				using R_::operator[];

				///\
				Multiplication by linear convolution, truncated by `N_size`. \

				XTAL_OP1_(T &) *=(T const &t)
				XTAL_0EX
				{
					auto constexpr h = N_size;
					auto &s = self();
					auto _s = self();
					if constexpr (_realized::alignment_v < N_size) {
						for (_std::ptrdiff_t i = h;   ~--i;) {s[i] *= t[0];
						for (_std::ptrdiff_t j = i; j; --j ) {s[i] += t[j]*_s[i - j];}}
					}
					else {
						antiseeker_f<h, 0>([&, this] (auto i) XTAL_0FN {s[i] *= t[0];
						antiseeker_f<i, 1>([&, this] (auto j) XTAL_0FN {s[i] += t[j]*_s[i - j];});});
					}
					return s;
				}
				XTAL_OP2_(T) * (T const &t)
				XTAL_0FX
				{
					return twin() *= t;
				}
				
			};
			using type = _detail::isotype<homotype>;
		};
		///\
		Extends `serial::type` with `++/--` defined in terms of finite differences/derivatives. \

		template <typename V>
		struct pulsar
		{
			using _realized = realize<V>;
			
			template <typename T>
			using hemitype = typename serial<V>::template homotype<T>;

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
					seeker_f<M>([&, this] (auto i) XTAL_0FN_(s[0 + i] += s[1 + i]));
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
					seeker_f<M>([&, this] (auto i) XTAL_0FN_(s[M - i] -= s[N - i]));
					s.reduce();
					return s;
				}

				XTAL_FN0 reduce()
				XTAL_0EX
				{}

			};
			using type = _detail::isotype<homotype>;
		};
		///\
		Extends `pulsar::type` with `++/--` wrapping the initial argument to `{-1, 1}/2`. \

		template <typename V>
		struct phasor
		{
			using _realized = realize<V>;
			
			template <typename T>
			using hemitype = typename pulsar<V>::template homotype<T>;

			template <typename T>
			class homotype: public hemitype<T>
			{
			//	TODO: Subclass to define serial pairs like `complex`. \

				friend T;
				using R_ = hemitype<T>;
			
			public:
				using R_::R_;
				using R_::self;

				///\
				Wraps the first argument to the range `+/- 1/2`, assuming `std::is_floating_point_v<V>`. \

				XTAL_FN0 reduce()
				XTAL_0EX
				{
					static_assert(_std::floating_point<V> and 0 < N_size);
					auto &s = self();
					s[0] -= _std::round(s[0]);
				}

			};
			using type = _detail::isotype<homotype>;
		};

		template <typename V> using  spool_t = typename  spool<V>::type;
		template <typename V> using  group_t = typename  group<V>::type;
		template <typename V> using scalar_t = typename scalar<V>::type;
		template <typename V> using sector_t = typename sector<V>::type;
		template <typename V> using series_t = typename series<V>::type;
		template <typename V> using serial_t = typename serial<V>::type;
		template <typename V> using pulsar_t = typename pulsar<V>::type;
		template <typename V> using phasor_t = typename phasor<V>::type;

	};
	using type = subtype<unit_t>;
};
template <>
struct collate<>
:	collate<-1>
{};
template <int N, int ...Ns>
struct collate<N, Ns...>
{
	template <typename S>
	class subtype: public S
	{
	public:
		using S::S;

		template <typename V> using value_t = typename collate_t<N>::template group_t<V>;
		template <typename V> using group_t = typename collate_t<Ns...>::template group_t<value_t<V>>;
		template <typename V> using group   = typename collate_t<Ns...>::template group  <value_t<V>>;

	};
	using type = subtype<unit_t>;
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
