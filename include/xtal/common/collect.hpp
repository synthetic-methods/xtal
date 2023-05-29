#pragma once
#include "../any.hpp"
#include "./seek.hpp"





XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <iterator_q I, iterator_q J>
XTAL_FZ0 copy_to(I i, J const j0, J const jN, bool const &ord=false)
requires iso_q<I, J>
{
	using namespace _std;
#ifdef __cpp_lib_execution
	auto constexpr seq = execution::  seq;
	auto constexpr par = execution::unseq;
	if (ord) copy(seq, j0, jN, i);
	else     copy(par, j0, jN, i);
#else
	copy(j0, jN, i);
#endif
}
template <iterator_q I, iterator_q J>
XTAL_FZ0 copy_to(I i, J const j0, J const jN, bool const &ord=false)
{
	copy_to(i, j0, jN, to_f<iteratee_t<I>>, ord);
}
template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ0 copy_to(I i, J const j0, J const jN, F &&f, bool const &ord=false)
{
	using namespace _std;
#ifdef __cpp_lib_execution
	auto constexpr seq = execution::  seq;
	auto constexpr par = execution::unseq;
	if (ord) transform(seq, j0, jN, i, XTAL_FWD_(F) (f));
	else     transform(par, j0, jN, i, XTAL_FWD_(F) (f));
#else
	transform(j0, jN, i, XTAL_FWD_(F) (f));
#endif
}

template <iterator_q I, iterated_q J>
XTAL_FZ0 copy_to(I i, J const &j, bool const &ord=false)
{
	copy_to(i, j.begin(), j.end(), ord);
}
template <iterator_q I, iterated_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ0 copy_to(I i, J const &j, F &&f, bool const &ord=false)
{
	copy_to(i, j.begin(), j.end(), XTAL_FWD_(F) (f), ord);
}


template <iterator_q I, iterator_q J>
XTAL_FZ0 move_to(I i, J j0, J jN, bool const &ord=false)
{
	auto const _j0 = _std::make_move_iterator(j0);
	auto const _jN = _std::make_move_iterator(jN);
	return copy_to(i, _j0, _jN, ord);
}
template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ0 move_to(I i, J const j0, J const jN, F &&f, bool const &ord=false)
{
	auto const _j0 = _std::make_move_iterator(j0);
	auto const _jN = _std::make_move_iterator(jN);
	return copy_to(i, _j0, _jN, XTAL_FWD_(F) (f), ord);
}

template <iterator_q I, iterated_q J>
XTAL_FZ0 move_to(I i, J const &j, bool const &ord=false)
{
	move_to(i, j.begin(), j.end(), ord);
}
template <iterator_q I, iterated_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ0 move_to(I i, J const &j, F &&f, bool const &ord=false)
{
	move_to(i, j.begin(), j.end(), XTAL_FWD_(F) (f), ord);
}

template <iterated_q J, _std::invocable<iteratee_t<J>> F>
XTAL_FZ0 apply_to(J &j, F &&f, bool const &ord=false)
{
	move_to(j.begin(), j, XTAL_FWD_(F) (f), ord);
}

}///////////////////////////////////////////////////////////////////////////////

template <int N_size=-1>
struct collect
{
	template <typename S>
	class subtype: public S
	{
		using co = S;
		
		template <typename W> using etc_t = _std::initializer_list<W>;
	public:
		using co::co;

		template <typename V>
		struct scalar;
		template <typename V>
		using  scalar_t = typename scalar<V>::type;
		
		template <typename V>
		struct parallel;
		template <typename V>
		using  parallel_t = typename parallel<V>::type;
		
		template <typename V, int N_shift=0>
		struct converse;
		template <typename V, int N_shift=0>
		using  converse_t = typename converse<V, N_shift>::type;
		
		template <typename V>
		struct serial;
		template <typename V>
		using  serial_t = typename serial<V>::type;
		
		template <typename V>
		struct series;
		template <typename V>
		using  series_t = typename series<V>::type;
		
		template <typename V>
		struct buffer;
		template <typename V>
		using  buffer_t = typename buffer<V>::type;
		
		template <typename V>
		struct debuff;
		template <typename V>
		using  debuff_t = typename debuff<V>::type;
		
		template <typename V>
		struct siphon;
		template <typename V>
		using  siphon_t = typename siphon<V>::type;
		
		template <typename V>
		requires (0 < N_size)
		struct scalar<V>
		{
			using realized = realize<V>;

		//	TODO: Alleviate the dependency on `std::array`, \
			but specialize the appropriate types so that e.g. `std::apply` works. \

			using archetype = _std::array<V, N_size>;// Hmmm...

			template <typename T>
			class heterotype: public archetype
			{
				using co = archetype;

			public:
				using co::co;
				using co::end;
				using co::begin;
				using it = typename co::iterator;

				XTAL_NEW heterotype()
				XTAL_0EX
				:	co()
				{
				}

				///\
				Replace the contents of `this` with the given range. \

				template <iso_q<it> I>
				XTAL_FN0 refill(I &&i0, I &&iN)
				XTAL_0EX
				{
					assert(N_size == _std::distance(i0, iN));
					_detail::copy_to(co::begin(), XTAL_FWD_(I) (i0), XTAL_FWD_(I) (iN));
				}
				template <iso_q<co> I>
				XTAL_FN0 refill(I &&in)
				XTAL_0EX
				{
					refill(in.begin(), in.end());
				}

				///\
				Span constructor. \
				Initializes `this` with the values between `i0` and `iN`. \

				template <iso_q<it> I>
				XTAL_NEW heterotype(I &&i0, I &&iN)
				XTAL_0EX
				{
					refill(XTAL_FWD_(I) (i0), XTAL_FWD_(I) (iN));
				}

				///\
				List constructor. \
				Initializes `this` with the given values. \

				template <iso_q<co> I>
				XTAL_NEW heterotype(I &&in)
				XTAL_0EX
				{
					refill(XTAL_FWD_(I) (in));
				}
				XTAL_NEW heterotype(etc_t<V> in)
				XTAL_0EX
				:	heterotype(in.begin(), in.end())
				{
				}

				///\
				List assignment. \
				Replaces the contents of `this` with the given values. \

				XTAL_OP1 = (etc_t<V> w)
				XTAL_0EX
				{
					refill(w.begin(), w.end());
					return *this;
				}

				///\
				Copy constructor. \
				Initializes `this` with the given data. \

				XTAL_NEW heterotype(heterotype const &t)
				XTAL_0EX
				:	heterotype(t.begin(), t.end())
				{
				}
				///\
				Copy assigment. \
				Replaces the contents of `this` with the given data. \

				XTAL_OP1 = (heterotype const &t)
				XTAL_0EX
				{
					refill(t.begin(), t.end());
					return *this;
				}

				///\
				Move constructor. \
				Initializes `this` with the given data. \

				XTAL_NEW heterotype(heterotype &&t)
				XTAL_0EX
				:	heterotype(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()))
				{
				}
				///\
				Move assigment. \
				Replaces the contents of `this` with the given data. \

				XTAL_OP1 = (heterotype &&t)
				XTAL_0EX
				{
					refill(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()));
					return *this;
				}

				///\
				Read accessor. \

				template <typename Y=T>
				XTAL_FN2 got() XTAL_0EX_(&)
				{
					if constexpr (is_q<Y, T>)
						return static_cast<T>(*this);
					else
						return reinterpret_cast<Y>(*this);
				}
				template <typename Y=T>
				XTAL_FN2 get() XTAL_0EX_(&)
				{
					if constexpr (is_q<Y, T>)
						return static_cast<T &>(*this);
					else
						return reinterpret_cast<Y>(*this);
				}
				template <typename Y=T>
				XTAL_FN2 get() XTAL_0FX_(&)
				{
					if constexpr (is_q<Y, T>)
						return static_cast<T const &>(*this);
					else
						return reinterpret_cast<_std::add_const_t<Y>>(*this);
				}
				XTAL_RE2_(XTAL_FN2 get(XTAL_DEF i), get()[XTAL_REF_(i)]);

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
				requires (0x00 < N_size) and (N_size <= 0x10)// TODO: Limit by cache line size?
				{
					seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) = f(get(i))));
					return get();
				}
				
				///\
				Elementwise comparators. \

			//	XTAL_OP2        <=> (heterotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=> t.get(Ns)) <=>...         ) (seek_v<N_size>);}
				XTAL_OP2_(bool) ==  (heterotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ==  t.get(Ns)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) <=  (heterotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=  t.get(Ns)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) >=  (heterotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >=  t.get(Ns)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) <   (heterotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <   t.get(Ns)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) >   (heterotype const &t) XTAL_0FX {return [&, this] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >   t.get(Ns)) and ...and true) (seek_v<N_size>);}

			};				
			template <typename T>
			class homotype;

			template <typename T>
			requires bit_operators_q<V>
			class homotype<T>: public heterotype<T>
			{
				using co = heterotype<T>;

			public:
				using co::co;
				using co::get;
				using co::got;

			//	Elementwise:
				XTAL_OP2_(T)  &  (XTAL_DEF w) XTAL_0FX {return got() &= XTAL_REF_(w);}
				XTAL_OP2_(T)  |  (XTAL_DEF w) XTAL_0FX {return got() |= XTAL_REF_(w);}
				XTAL_OP2_(T)  ^  (XTAL_DEF w) XTAL_0FX {return got() ^= XTAL_REF_(w);}
				XTAL_OP2_(T)  +  (XTAL_DEF w) XTAL_0FX {return got() += XTAL_REF_(w);}
				XTAL_OP2_(T)  -  (XTAL_DEF w) XTAL_0FX {return got() -= XTAL_REF_(w);}

				XTAL_OP1_(T&) %= (etc_t<V> w) XTAL_0EX {return get() %= T(w.begin(), w.end());}
				XTAL_OP1_(T&) &= (etc_t<V> w) XTAL_0EX {return get() &= T(w.begin(), w.end());}
				XTAL_OP1_(T&) |= (etc_t<V> w) XTAL_0EX {return get() |= T(w.begin(), w.end());}
				XTAL_OP1_(T&) ^= (etc_t<V> w) XTAL_0EX {return get() ^= T(w.begin(), w.end());}
				XTAL_OP1_(T&) += (etc_t<V> w) XTAL_0EX {return get() += T(w.begin(), w.end());}
				XTAL_OP1_(T&) -= (etc_t<V> w) XTAL_0EX {return get() -= T(w.begin(), w.end());}
				
				XTAL_OP1_(T&) %= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) %= t.get(i))), get();}
				XTAL_OP1_(T&) &= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) &= t.get(i))), get();}
				XTAL_OP1_(T&) |= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) |= t.get(i))), get();}
				XTAL_OP1_(T&) ^= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) ^= t.get(i))), get();}
				XTAL_OP1_(T&) += (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) += t.get(i))), get();}
				XTAL_OP1_(T&) -= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) -= t.get(i))), get();}

			//	Elementwise:
				XTAL_OP1_(T&) %= (V const &v) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) %= v)), get();}
				XTAL_OP1_(T&) &= (V const &v) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) &= v)), get();}
				XTAL_OP1_(T&) |= (V const &v) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) |= v)), get();}
				XTAL_OP1_(T&) ^= (V const &v) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) ^= v)), get();}
				XTAL_OP1_(T&) += (V const &v) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) += v)), get();}
				XTAL_OP1_(T&) -= (V const &v) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) -= v)), get();}

				XTAL_OP1_(T&) ++           () XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(++get(i))), get();}
				XTAL_OP1_(T&) --           () XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(--get(i))), get();}

			};
			template <typename T>
			requires field_operators_q<V>
			class homotype<T>: public heterotype<T>
			{
				using co = heterotype<T>;

			public:
				using co::co;
				using co::get;
				using co::got;

				XTAL_OP2_(T)  *  (XTAL_DEF w) XTAL_0FX {return got() *= XTAL_REF_(w);}
				XTAL_OP2_(T)  /  (XTAL_DEF w) XTAL_0FX {return got() /= XTAL_REF_(w);}
				XTAL_OP2_(T)  +  (XTAL_DEF w) XTAL_0FX {return got() += XTAL_REF_(w);}
				XTAL_OP2_(T)  -  (XTAL_DEF w) XTAL_0FX {return got() -= XTAL_REF_(w);}

				XTAL_OP1_(T&) *= (V const &v) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) *= v)), get();}
				XTAL_OP1_(T&) /= (V const &v) XTAL_0EX {return seek_f<N_size>([&, this](auto i) XTAL_0FN_(get(i) /= v)), get();}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;
			public:
				using co::co;

			};
		};
		template <typename V>
		struct parallel
		{
			using realized = realize<V>;

			template <typename T>
			using heterotype = typename scalar<V>::template homotype<T>;

			template <typename T>
			class homotype: public heterotype<T>
			{
				using co = heterotype<T>;
			public:
				using co::co;
				using co::get;

				using transformed_t = serial_t<V>;

			//	Elementwise multiplication/division:

				XTAL_OP1_(T&) *= (etc_t<V> w) XTAL_0EX {return get() *= T(w.begin(), w.end());}
				XTAL_OP1_(T&) /= (etc_t<V> w) XTAL_0EX {return get() /= T(w.begin(), w.end());}				
				
				XTAL_OP1_(T&) *= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](XTAL_DEF i) XTAL_0FN_(get(i) *= t.get(i))), get();}
				XTAL_OP1_(T&) /= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](XTAL_DEF i) XTAL_0FN_(get(i) /= t.get(i))), get();}

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
		
		template <typename V, int N_shift>
		requires (N_size == 2)
		struct converse<V, N_shift>
		{
			using realized = realize<V>;

			template <typename T>
			using heterotype = typename parallel<V>::template homotype<T>;

			template <typename T>
			class homotype: public heterotype<T>
			{
				using co = heterotype<T>;
			public:
				using co::co;
				using co::get;

				using reflected_t = converse_t<V, N_shift^1>;

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
		template <typename V>
		struct serial
		{
			using realized = realize<V>;

			template <typename T>
			using heterotype = typename scalar<V>::template homotype<T>;

			template <typename T>
			class homotype: public heterotype<T>
			{
			//	TODO: Subclass to define serial pairs like `complex`. \

				using co = heterotype<T>;
			public:
				using co::co;
				using co::get;

				using transformed_t = parallel_t<V>;

			//	Elementwise addition/subtraction:
				
				XTAL_OP1_(T&) += (etc_t<V> w) XTAL_0EX {return get() += T(w.begin(), w.end());}
				XTAL_OP1_(T&) -= (etc_t<V> w) XTAL_0EX {return get() -= T(w.begin(), w.end());}
				
				XTAL_OP1_(T&) += (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](XTAL_DEF i) XTAL_0FN_(get(i) += t.get(i))), get();}
				XTAL_OP1_(T&) -= (T const &t) XTAL_0EX {return seek_f<N_size>([&, this](XTAL_DEF i) XTAL_0FN_(get(i) -= t.get(i))), get();}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;
			public:
				using co::co;

			};
		};
		template <typename V>
		struct series
		{
			using realized = realize<V>;

			template <typename T>
			using heterotype = typename serial<V>::template homotype<T>;

			template <typename T>
			class homotype: public heterotype<T>
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

				template <size_t N_limit=N_size, size_t N_index=0>
				XTAL_FN1_(T&) generate(V const &u)
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
					{
						auto w = realized::square_y(s[i]);
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
				comprising `N_size` values of the half-period complex sinusoid.

				///\note Only the first eighth-period is computed, \
				then mirrored to complete the quarter and half respectively. \

				XTAL_FN1_(T &) generate()
				XTAL_0EX
				requires complex_q<V> and bit_ceiling_q<N_size, 2>
				{
					auto &s = get();
					auto constexpr x = realized::template patio_y<-1> (N_size);
					auto constexpr L = N_size >> 2;
					auto const  i0 =         s.begin(), i1 = _std::next(i0, 1);
					auto const  j0 = _std::next(i0, L), j1 = _std::next(j0, 1);
					auto const  k0 = _std::next(j0, L), k1 = _std::next(k0, 1);
					auto const _k1 = _std::make_reverse_iterator(k1);
					generate<L + 1> (realized::circle_y(x));
					_detail::copy_to(_k1, _std::span(i0, j0), [](V const &v) XTAL_0FN_(V(-v.imag(), -v.real())));
					_detail::copy_to( k1, _std::span(i1, k1), [](V const &v) XTAL_0FN_(V( v.imag(), -v.real())));
					return s;
				}
				
				///\returns `that` transformed by the FFT, \
				using `this` as the Fourier basis. \

				template <iterated_q Y>
				XTAL_FN1_(typename Y::transformed_t &) transform(Y &that)
				XTAL_0EX
				requires bit_ceiling_q<N_size, 1>
				{
					using size_type = typename Y::size_type; static_assert(_std::integral<size_type>);

					size_type const n_size = that.size();
					size_type const h_size = n_size >> 1;
					size_type const k_size = bit_ceiling_y(n_size); assert(n_size == 1 << k_size);
					size_type const K_size = bit_ceiling_y(N_size); assert(k_size <= K_size);

					for (size_type h = 0; h < h_size; ++h)
					{
						_std::swap(that[h], that[bit_reverse_y(h, k_size)]);
					}
					if constexpr (if_q<parallel_t<V>, Y>)
					{
						_detail::apply_to(that, [](XTAL_DEF u) XTAL_0FN_(_std::conj(XTAL_REF_(u))));
					}
					for (size_type k = 0; k < k_size; ++k)
					{
						size_type const kn = K_size - k;
						size_type const u = 1 << k;
						size_type const w = u << 1;
						for (size_type                 i = 0; i < u; i += 1)
						for (size_type kn_i = i << kn, j = i; j < n_size; j += w)
						{
							V const y = that[j + u]*get(kn_i);
							V const x = that[j + 0];
							that[j + u] = x - y;
							that[j + 0] = x + y;
						}
					}
					if constexpr (if_q<parallel_t<V>, Y>)
					{
						auto const u_size = realized::template ratio_y<1>(n_size);
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
		
		
		
		template <typename V>
		struct buffer
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
				
				XTAL_FZ2_(A       *) appointee_f(V       *i) XTAL_0EX {return appointed_f<A       *>(i);}
				XTAL_FZ2_(A const *) appointee_f(V const *i) XTAL_0EX {return appointed_f<A const *>(i);}
				XTAL_FZ2_(V       *) appointer_f(A       *i) XTAL_0EX {return appointed_f<V       *>(i);}
				XTAL_FZ2_(V const *) appointer_f(A const *i) XTAL_0EX {return appointed_f<V const *>(i);}
				
				XTAL_FZ2 reverse_appointee_f(XTAL_DEF i) XTAL_0EX {return _std::make_reverse_iterator(appointee_f(XTAL_REF_(i)));}
				XTAL_FZ2 reverse_appointer_f(XTAL_DEF i) XTAL_0EX {return _std::make_reverse_iterator(appointer_f(XTAL_REF_(i)));}

			//	alignas(V) _std::byte block_m[sizeof(V)*(N_size)];
				A  block_m[N_size];
				A* limit_m = block_m;

			public:
				XTAL_FN2 get() XTAL_0FX_(&) {return static_cast<T const &>(*this);}
				XTAL_FN2 get() XTAL_0EX_(&) {return static_cast<T       &>(*this);}
				XTAL_RE4_(XTAL_FN2 get(XTAL_DEF i), get()[XTAL_REF_(i)]);

			//	using co;
				using co::size;

				using             value_type = V;
				using         allocator_type = T;

				using              size_type = _std::size_t;
				using        difference_type = _std::ptrdiff_t;

				using              reference = value_type       &;
				using        const_reference = value_type const &;
				
				using                pointer = value_type       *;
				using          const_pointer = value_type const *;

				using               iterator = value_type       *;
				using         const_iterator = value_type const *;
				
				using       reverse_iterator = _std::reverse_iterator<      iterator>;
				using const_reverse_iterator = _std::reverse_iterator<const_iterator>;
				
				XTAL_RE4_(XTAL_OP2[](size_type i), *appointer_f(block_m + i));
				XTAL_RE4_(XTAL_OP2() (size_type i),  appointer_f(block_m + i));

				XTAL_RE4_(XTAL_FN2 rbegin(), reverse_appointer_f(limit_m));
				XTAL_RE4_(XTAL_FN2  begin(),   appointer_f(block_m));
				XTAL_RE4_(XTAL_FN2   rend(), reverse_appointer_f(block_m));
				XTAL_RE4_(XTAL_FN2    end(),   appointer_f(limit_m));
				
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

				template <iso_q<iterator> I0, iso_q<iterator> IN>
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

				XTAL_NEW_(explicit) homotype(etc_t<V> etc)
				:	homotype(etc.begin(), etc.end())
				{
				}
				///\
				List assignment. \
				Replaces the contents of `this` with the given values. \

				XTAL_OP1 = (etc_t<V> etc)
				{
					refill(etc.begin(), etc.end());
					return get();
				}

				///\
				Copy constructor. \
				Initializes `this` with the given data. \

				XTAL_NEW homotype(homotype const &t)
				:	homotype(t.begin(), t.end())
				{
				}
				///\
				Copy assigment. \
				Replaces the contents of `this` with the given data. \

				XTAL_OP1 = (homotype const &t)
				{
					refill(t.begin(), t.end());
					return get();
				}

				///\
				Move constructor. \
				Initializes `this` with the given data. \

				XTAL_NEW homotype(homotype &&t)
				:	homotype(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()))
				{
				}
				///\
				Move assigment. \
				Replaces the contents of `this` with the given data. \

				XTAL_OP1 = (homotype &&t)
				{
					refill(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()));
					return get();
				}

				///\
				Swaps the contents of `this` with the given data. \

				XTAL_FN0 swap(T &t)
				requires _std::swappable<value_type>
				{
					_std::swap_ranges(begin(), end(), t.begin());
				}

				///\
				\returns the fixed capacity `N_size`. \

				XTAL_FN2_(size_type) capacity()
				XTAL_0EX
				{
					return N_size;
				}

				///\
				Allocates and initializes `sN` elements at the end of the buffer. \

				XTAL_FN2_(iterator) allocate(size_type sN)
				{
					return insert_back(sN);
				}

				///\
				Deletes the elements from `i0` to `end()`. \

				template <is_q<iterator> I0>
				XTAL_FN0 deallocate(I0 i0)
				XTAL_0EX
				{
					erase(i0, end());
				}

				///\
				Deletes all elements. \

				XTAL_FN0 clear()
				XTAL_0EX
				{
					erase(begin(), end());
				}

				///\
				Deletes the element at `i0`. \

				template <is_q<iterator> I0>
				XTAL_FN0 erase(I0 i0)
				XTAL_0EX
				{
					erase(i0, size_type(1));
				}
				///\
				Deletes `sN` elements starting from `i0`. \

				template <is_q<iterator> I0>
				XTAL_FN0 erase(I0 i0, size_type sN)
				XTAL_0EX
				{
					erase(i0, _std::next(i0, sN), sN);
				}
				///\
				Deletes the elements between `i0` and `iN`. \

				template <is_q<iterator> I0, is_q<iterator> IN>
				XTAL_FN0 erase(I0 i0, IN iN)
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
				XTAL_FN0 erase(I0 i0, IN iN, size_type sN)
				XTAL_0EX
				{
					using I = _std::common_type_t<I0, IN>;
					I i0_ = i0;
					I iN_ = iN;
					erode(i0_, iN_, sN);
				}

				///\
				Does nothing. \

				XTAL_FN0 shrink_to_fit()
				XTAL_0EX
				{
				}

				///\
				Does nothing besides `throw std::bad_alloc` if the required `sN` exceeds the maximum `N_size`. \

				XTAL_FN0 reserve(size_type sN)
				{
					if (N_size < sN)
					{
						throw _std::bad_alloc {};
					}
				}

				///\
				Resizes `this` to `sN` elements. \

				XTAL_FN0 resize(size_type sN, XTAL_DEF ...ws)
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

				XTAL_FN0 refill(XTAL_DEF ...ws)
				{
					clear();
					insert_back(XTAL_REF_(ws)...);
				}

				///\
				Removes the last element from `this`. \

				XTAL_FN0 pop_back()
				{
					pop_back(size_type(1));
				}
				///\
				Removes the last `sN` elements from `this`. \

				XTAL_FN0 pop_back(size_type sN)
				{
					deallocate(end() - sN);
				}

				///\
				Inserts the values `etc` beginning at `i0`. \

				XTAL_FN0 push_back(etc_t<V> etc)
				{
					insert_back(etc.begin(), etc.end());
				}
				///\
				Inserts the values `etc...` beginning at `i0`. \

				XTAL_FN0 push_back(XTAL_DEF_(to_q<V>) ...etc)
				{
					push_back(etc_t<V>{V(XTAL_REF_(etc))...});
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
					return ::new (limit_m++) V(XTAL_REF_(ws)...);
				}

				///\
				Invokes `insert` at `this->end()` with the given arguments. \

				XTAL_FN1_(iterator) insert_back(XTAL_DEF ...ws)
				{
					return insert(end(), XTAL_REF_(ws)...);
				}

				///\
				Inserts the values delimited by `j0` and `jN` beginning at `i`. \

				template <is_q<iterator> I, iso_q<iterator> J0, iso_q<iterator> JN>
				XTAL_FN1_(iterator) insert(I i, J0 j0, JN jN)
				{
					using J = _std::common_type_t<J0, JN>;
					J j0_ = j0;
					J jN_ = jN;
					inject(i, _std::distance(j0_, jN_));
					_detail::copy_to(i, j0_, jN_);
					return i;
				}

				///\
				Inserts the values `etc` beginning at `i`. \

				template <is_q<iterator> I>
				XTAL_FN1_(iterator) insert(I i, etc_t<V> etc)
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
						auto j = reverse_appointer_f(limit_m);
						_detail::move_to(_std::prev(j, sN), j, _std::next(j, sN), true);
					}
					else
					{
						assert(i == end());
					}
					limit_m += sN;
					return i;
				}

				///\
				Deletes `sN` elements between `i0` and `iN`. \

				template <is_q<iterator> I0, is_q<iterator> IN>
				XTAL_FN0 erode(I0 i0, IN iN, size_type sN)
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
						_detail::move_to(j0, jN, limit_m, sN <= _std::distance(jN, limit_m));
					}
					else
					{
						assert(end_m == iN_);
					}
					limit_m -= sN;
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
		requires (N_size < 0)
		struct buffer<V>
		{
			using type = _std::vector<V>;

		};
		template <typename V>
		struct debuff
		{
			using type = deranged_t<buffer_t<V>>;
		};
		template <typename V>
		struct siphon
		{
			using type = _std::priority_queue<V, buffer_t<V>, _std::greater<V>>;
		};
	};
	using type = subtype<unit_t>;
};

template <int N_size               > using collect_t           = typename collect  <N_size>::type;
template <int N_size,    typename V> using collect_scalar_t    = typename collect_t<N_size>::template scalar_t<V>;
template <int N_size,    typename V> using collect_parallel_t  = typename collect_t<N_size>::template parallel_t<V>;
template <typename V, int N_shift=0> using collect_converse_t  = typename collect_t<2>::template converse_t<V, N_shift>;
template <int N_size,    typename V> using collect_serial_t    = typename collect_t<N_size>::template serial_t<V>;
template <int N_size,    typename V> using collect_series_t    = typename collect_t<N_size>::template series_t<V>;
template <int N_size,    typename V> using collect_siphon_t    = typename collect_t<N_size>::template siphon_t<V>;
template <int N_size,    typename V> using collect_buffer_t    = typename collect_t<N_size>::template buffer_t<V>;
template <int N_size,    typename V> using collect_debuff_t    = typename collect_t<N_size>::template debuff_t<V>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
