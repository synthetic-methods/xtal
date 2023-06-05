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
	using realized = realize<V>;

	template <typename S>
	class subtype: public S
	{
		using co = S; template <typename W> using etc_t = _std::initializer_list<W>;

	public:
		using co::co;
		using typename co::arity;

		using fixed = typename co::template fixed<V>;
		using fluid = typename co::template fluid<V>;

		struct buffer;
		struct scalar;
		struct serial;
		struct series;
		struct parallel;
		template <int N_shift=0> struct converse;
		
		struct buffer
		{
			using type = typename fluid::type;

		};
		struct siphon
		{
			using archetype = _std::priority_queue<V, typename fluid::type, _std::greater<V>>;

			template <typename T>
			class homotype: public archetype
			{
				using co = archetype;
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
		struct sluice
		{
			using archetype = typename fluid::type;

			template <typename T>
			class homotype: archetype
			{
				using co = archetype;

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
			using archetype = typename fixed::type;

			template <typename T>// requires field_operators_q<V>
			class homotype: public archetype
			{
				using co = archetype;

			public:
				using co::co;

				///\
				Read accessor. \

				template <typename Y=T>
				XTAL_FN2 got() XTAL_0EX_(&)
				{
					if constexpr (is_q<Y, T>)
					{	return static_cast<T>(*this);
					}
					else
					{	return reinterpret_cast<Y>(*this);
					}
				}
				template <typename Y=T>
				XTAL_FN2 get() XTAL_0EX_(&)
				{
					if constexpr (is_q<Y, T>)
					{	return static_cast<T &>(*this);
					}
					else
					{	return reinterpret_cast<Y>(*this);
					}
				}
				template <typename Y=T>
				XTAL_FN2 get() XTAL_0FX_(&)
				{
					if constexpr (is_q<Y, T>)
					{	return static_cast<T const &>(*this);
					}
					else
					{	return reinterpret_cast<_std::add_const_t<Y>>(*this);
					}
				}
				XTAL_RN2_(XTAL_FN2 get(XTAL_DEF i), get()[XTAL_REF_(i)]);

				///\
				Elementwise transformer. \

				XTAL_FN1 transmute(XTAL_DEF_(_std::invocable<V>) ...fs)
				XTAL_0EX
				{
					(transmute(XTAL_REF_(fs)), ...);
					return get();
				}
				XTAL_FN1 transmute(XTAL_DEF_(_std::invocable<V>) f)
				XTAL_0EX
				{
					_detail::apply_to(get(), XTAL_REF_(f));
					return get();
				}
				XTAL_FN1 transmute(_std::invocable<V> auto const &f)
				XTAL_0EX
				XTAL_IF1 (0x00 < arity::value) and (arity::value <= 0x10)// TODO: Limit by cache line size?
				{
					seek_f<arity::value>([&, this](auto i) XTAL_0FN_(get(i) = f(get(i))));
					return get();
				}
				
				///\
				Elementwise comparators. \

			//	XTAL_OP2        <=> (homotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=> t.get(Ns)) <=>...         ) (seek_v<arity::value>);}
				XTAL_OP2_(bool) ==  (homotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ==  t.get(Ns)) and ...and true) (seek_v<arity::value>);}
				XTAL_OP2_(bool) <=  (homotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=  t.get(Ns)) and ...and true) (seek_v<arity::value>);}
				XTAL_OP2_(bool) >=  (homotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >=  t.get(Ns)) and ...and true) (seek_v<arity::value>);}
				XTAL_OP2_(bool) <   (homotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <   t.get(Ns)) and ...and true) (seek_v<arity::value>);}
				XTAL_OP2_(bool) >   (homotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >   t.get(Ns)) and ...and true) (seek_v<arity::value>);}

				XTAL_OP2_(T)    *  (XTAL_DEF w) XTAL_0FX {return got() *= XTAL_REF_(w);}
				XTAL_OP2_(T)    /  (XTAL_DEF w) XTAL_0FX {return got() /= XTAL_REF_(w);}
				XTAL_OP2_(T)    +  (XTAL_DEF w) XTAL_0FX {return got() += XTAL_REF_(w);}
				XTAL_OP2_(T)    -  (XTAL_DEF w) XTAL_0FX {return got() -= XTAL_REF_(w);}

				XTAL_OP1_(T &)  *= (V const &v) XTAL_0EX {return seek_f<arity::value>([&, this](auto i) XTAL_0FN_(get(i) *= v)), get();}
				XTAL_OP1_(T &)  /= (V const &v) XTAL_0EX {return seek_f<arity::value>([&, this](auto i) XTAL_0FN_(get(i) /= v)), get();}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		struct serial
		{
			template <typename T>
			using heterotype = typename scalar::template homotype<T>;

			template <typename T>
			class homotype: public heterotype<T>
			{
			//	TODO: Subclass to define serial pairs like `complex`. \

				using co = heterotype<T>;
			
			public:
				using co::co;
				using co::get;

				using transformed_t = typename parallel::type;

			//	Elementwise addition/subtraction:
				
				XTAL_OP1_(T &) += (etc_t<V> w) XTAL_0EX {return get() += T(w.begin(), w.end());}
				XTAL_OP1_(T &) -= (etc_t<V> w) XTAL_0EX {return get() -= T(w.begin(), w.end());}
				
				XTAL_OP1_(T &) += (T const &t) XTAL_0EX {return seek_f<arity::value>([&, this](XTAL_DEF i) XTAL_0FN_(get(i) += t.get(i))), get();}
				XTAL_OP1_(T &) -= (T const &t) XTAL_0EX {return seek_f<arity::value>([&, this](XTAL_DEF i) XTAL_0FN_(get(i) -= t.get(i))), get();}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		struct series
		{
			template <typename T>
			using heterotype = typename serial::template homotype<T>;

			template <typename T>
			class homotype: public heterotype<T>
			{
				using co = heterotype<T>;
			
			public:
				using co::co;
				using co::get;

				///\
				Initializing constructor. \

				XTAL_NEW_(explicit) homotype(bool const &basis)
				:	co()
				{
					if (basis) generate();
				}
				///\
				Initializing constructor. \

				XTAL_NEW_(explicit) homotype(V &&u)
				{
					generate(_std::move(u));
				}
				///\
				Initializing constructor. \

				XTAL_NEW_(explicit) homotype(V const &u)
				{
					generate(u);
				}

				///\returns `this` with the elements `N_index, ..., N_index + N_limit - 1` \
					filled by the corresponding powers of `u`. \

				///\note This algorithm uses squaring, \
					which is more precise/efficient than multiplication for complex numbers. \

				template <size_t N_limit=arity::value, size_t N_index=0>
				XTAL_FN1_(T &) generate(V const &u)
				XTAL_0EX
				{
					using size_type = typename co::size_type; static_assert(_std::integral<size_type>);
					auto &s = get();
					auto constexpr H_limit = N_limit >> 1; static_assert(0 < H_limit);
					auto constexpr _0 = N_index + 0;
					auto constexpr _1 = N_index + 1;
					auto constexpr _H = N_index + H_limit;
					auto constexpr N1 = N_index + N_limit - 1;
					auto constexpr N2 = N_index + N_limit - 2;
					auto const      o = realized::template explo_y(N_index, u);
					s[_0] = o;
					s[_1] = o*u;
					for (size_type i = _1; i < _H; ++i)
					{	auto w = realized::square_y(s[i]);
						auto h = i << 1;
						s[h] = w;
						h   += 1;
						w   *= u;
						s[h] = w;
					}
					if constexpr (N_limit&1)
					{	s[N1] = s[N2]*u;
					}
					return s;
				}

				///\returns `this` as the Fourier basis used by `transform` etc, \
				comprising `arity::value` values of the half-period complex sinusoid.

				///\note Only the first eighth-period is computed, \
				then mirrored to complete the quarter and half respectively. \

				XTAL_FN1_(T &) generate()
				XTAL_0EX
				XTAL_IF1 bit_ceiling_q<arity::value, 2> and complex_q<V>
				{
					auto &s = get();
					auto constexpr x = realized::template patio_y<-1>(arity::value);
					auto constexpr L = arity::value >> 2;
					auto const  i0 =         s.begin(), i1 = _std::next(i0, 1);
					auto const  j0 = _std::next(i0, L), j1 = _std::next(j0, 1);
					auto const  k0 = _std::next(j0, L), k1 = _std::next(k0, 1);
					auto const _k1 = _std::make_reverse_iterator(k1);
					generate<L + 1>(realized::circle_y(x));
					_detail::copy_to(_k1, _std::span(i0, j0), [](V const &v) XTAL_0FN_(V(-v.imag(), -v.real())));
					_detail::copy_to( k1, _std::span(i1, k1), [](V const &v) XTAL_0FN_(V( v.imag(), -v.real())));
					return s;
				}
				
				///\returns `that` transformed by the FFT, \
				using `this` as the Fourier basis. \

				template <iterated_q Y>
				XTAL_FN1_(typename Y::transformed_t &) transform(Y &that)
				XTAL_0EX
				XTAL_IF1 bit_ceiling_q<arity::value, 1>
				{
					using size_type = typename Y::size_type; static_assert(_std::integral<size_type>);

					size_type const n_size = that.size();
					size_type const h_size = n_size >> 1;
					size_type const k_size = bit_ceiling_y(n_size); assert(n_size == 1 << k_size);
					size_type const K_size = bit_ceiling_y(arity::value); assert(k_size <= K_size);

					for (size_type h = 0; h < h_size; ++h)
					{	_std::swap(that[h], that[bit_reverse_y(h, k_size)]);
					}
					if constexpr (if_q<typename parallel::type, Y>)
					{	_detail::apply_to(that, [](XTAL_DEF u) XTAL_0FN_(_std::conj(XTAL_REF_(u))));
					}
					for (size_type k = 0; k < k_size; ++k)
					{	size_type const kn = K_size - k;
						size_type const u = 1 << k;
						size_type const w = u << 1;
						for (size_type                 i = 0; i < u; i += 1)
						for (size_type kn_i = i << kn, j = i; j < n_size; j += w)
						{	V const y = that[j + u]*get(kn_i);
							V const x = that[j + 0];
							that[j + u] = x - y;
							that[j + 0] = x + y;
						}
					}
					if constexpr (if_q<typename parallel::type, Y>)
					{	auto const u_size = realized::template ratio_y<1>(n_size);
						_detail::apply_to(that, [=](XTAL_DEF u) XTAL_0FN_(_std::conj(XTAL_REF_(u)*u_size)));
					}
					return that.template get<typename Y::transformed_t &>();
				}
				///\returns a new `series` representing the FFT of `lhs`, \
				using `this` as the Fourier basis. \

				template <iterated_q Y>
				XTAL_FN2_(typename Y::transformed_t) transformation(Y that)
				XTAL_0EX
				{
					return transform(that);
				}

				///\returns `lhs` convolved with `rhs`, \
				using `this` as the Fourier basis. \

				template <iterated_q Y>
				XTAL_FN1 convolve(Y &lhs, Y rhs)
				XTAL_0EX
				{
					return transform(transform(lhs) *= transform(rhs));
				}
				///\returns a new `series` representing the convolution of `lhs` with `rhs`, \
				using `this` as the Fourier basis. \

				template <iterated_q Y>
				XTAL_FN2_(Y) convolution(Y lhs, Y const &rhs)
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
		struct parallel
		{
			template <typename T>
			using heterotype = typename scalar::template homotype<T>;

			template <typename T>
			class homotype: public heterotype<T>
			{
				using co = heterotype<T>;
			
			public:
				using co::co;
				using co::get;

			//	using transformed_t = typename serial::type;
				using transformed_t = typename series::type;

			//	Elementwise multiplication/division:

				XTAL_OP1_(T &) *= (etc_t<V> w) XTAL_0EX {return get() *= T(w.begin(), w.end());}
				XTAL_OP1_(T &) /= (etc_t<V> w) XTAL_0EX {return get() /= T(w.begin(), w.end());}				
				
				XTAL_OP1_(T &) *= (T const &t) XTAL_0EX {return seek_f<arity::value>([&, this](XTAL_DEF i) XTAL_0FN_(get(i) *= t.get(i))), get();}
				XTAL_OP1_(T &) /= (T const &t) XTAL_0EX {return seek_f<arity::value>([&, this](XTAL_DEF i) XTAL_0FN_(get(i) /= t.get(i))), get();}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		///\
		A mutually inverse couple that can be mapped to their dual via `lhs +/- rhs >> N_shift`, \
		and used to represent e.g. cosine/sine or mid/side pairs.
		
		template <int N_shift> requires (arity::value == 2)
		struct converse<N_shift>
		{
			template <typename T>
			using heterotype = typename parallel::template homotype<T>;

			template <typename T>
			class homotype: public heterotype<T>
			{
				using co = heterotype<T>;
			
			public:
				using co::co;
				using co::get;

				using reflected_t = typename converse<N_shift^1>::type;

				XTAL_FN2 even()
				XTAL_0FX
				{
					return (get(0) + get(1))*(realized::template haplo_v<N_shift>);
				}
				XTAL_FN2 odd()
				XTAL_0FX
				{
					return (get(0) - get(1))*(realized::template haplo_v<N_shift>);
				}
				XTAL_OP2 ~ ()
				XTAL_0FX
				{
					return reflected_t{even(), odd()};
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
