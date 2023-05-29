#pragma once
#include "../any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <delta_t N_size=-1>
struct buffer
{
private:
	template <iterator_q I, iterator_q J>
	XTAL_FZ1_(void) copy_linear_f(bool const &order, I i, J const j0, J const jN)
	{
		copy_linear_f(i, j0, jN, construct_f<iteratee_t<I>>);
	}
	template <iterator_q I, iterator_q J>
	XTAL_FZ1_(void) copy_linear_f(bool const &order, I i, J const j0, J const jN)
	requires iso_q<I, J>
	{
	#ifdef __cpp_lib_execution
		if (order) _std::copy(_std::execution::seq, j0, jN, i);
		else     _std::copy(_std::execution::unseq, j0, jN, i);
	#else
		_std::copy(j0, jN, i);
	#endif
	}
	template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
	XTAL_FZ1_(void) copy_linear_f(bool const &order, I i, J const j0, J const jN, F &&f)
	{
	#ifdef __cpp_lib_execution
		if (order) _std::transform(_std::execution::seq, j0, jN, i, XTAL_FWD_(F) (f));
		else     _std::transform(_std::execution::unseq, j0, jN, i, XTAL_FWD_(F) (f));
	#else
		_std::transform(j0, jN, i, XTAL_FWD_(F) (f));
	#endif
	}

	template <iterator_q I, iterated_q J>
	XTAL_FZ1_(void) copy_linear_f(bool const &order, I i, J const &j)
	{
		copy_linear_f(order, i, j.begin(), j.end());
	}
	template <iterator_q I, iterated_q J, _std::invocable<iteratee_t<J>> F>
	XTAL_FZ1_(void) copy_linear_f(bool const &order, I i, J const &j, F &&f)
	{
		copy_linear_f(order, i, j.begin(), j.end(), XTAL_FWD_(F) (f));
	}


	template <iterator_q I, iterator_q J>
	XTAL_FZ1_(void) move_linear_f(bool const &order, I i, J j0, J jN)
	{
		auto const _j0 = _std::make_move_iterator(j0);
		auto const _jN = _std::make_move_iterator(jN);
		return copy_linear_f(order, i, _j0, _jN);
	}
	template <iterator_q I, iterator_q J, _std::invocable<iteratee_t<J>> F>
	XTAL_FZ1_(void) move_linear_f(bool const &order, I i, J const j0, J const jN, F &&f)
	{
		auto const _j0 = _std::make_move_iterator(j0);
		auto const _jN = _std::make_move_iterator(jN);
		return copy_linear_f(order, i, _j0, _jN, XTAL_FWD_(F) (f));
	}

	template <iterator_q I, iterated_q J>
	XTAL_FZ1_(void) move_linear_f(bool const &order, I i, J const &j)
	{
		move_linear_f(order, i, j.begin(), j.end());
	}
	template <iterator_q I, iterated_q J, _std::invocable<iteratee_t<J>> F>
	XTAL_FZ1_(void) move_linear_f(bool const &order, I i, J const &j, F &&f)
	{
		move_linear_f(order, i, j.begin(), j.end(), XTAL_FWD_(F) (f));
	}

	template <iterated_q J, _std::invocable<iteratee_t<J>> F>
	XTAL_FZ1_(void) mutate_linear_f(bool const &order, J &j, F &&f)
	{
		move_linear_f(order, j.begin(), j, XTAL_FWD_(F) (f));
	}

public:
	template <typename S>
	class subtype: public S
	{
		using co = S;
	public:
		using co::co;

		template <typename U>
		requires (0 < N_size)
		struct scalar
		{
			using V = based_t<U>;
			using realized = realize<V>;

		//	TODO: Specialize the appropriate types so that e.g. `std::apply` works. \

		//	TODO: Reify `buffer_scalar_t<2, V>` with even/odd semantics, \
			e.g. stereo or mid-side signals, and results like `exp(+x), exp(-x)` or `cosh(x), sinh(x)`, \
			and define the operations to interconvert them. \

		//	TODO: Reify `buffer_scalar_t<2, V>` with `std::complex` semantics, \
			and define componentwise multiplication either by: \
			-	using `std::bit_cast<scalar_t<V>>` \
			-	defining a non-summing companion to `dot` e.g. `zot` \
			-	supplying real and imaginary projections with a range interface \

			using archetype = _std::array<V, N_size>;// Hmmm...

			template <typename T>
			class heterotype: public archetype
			{
				using co = archetype;

			public:
				using co::co;
				using co::end;
				using co::begin;

				XTAL_NEW heterotype()
				XTAL_0EX
				:	co()
				{
				}

				///\
				Replace the contents of `this` with the given range. \

				template <iterator_q I>
				requires is_q<iteratee_t<I>, V>
				XTAL_FN1_(void) refill(I &&i0, I &&iN)
				XTAL_0EX
				{
					assert(N_size == _std::distance(i0, iN));
					copy_linear_f(false, co::begin(), XTAL_FWD_(I) (i0), XTAL_FWD_(I) (iN));
				}
				template <iterated_q I>
				requires is_q<iteratee_t<I>, V>
				XTAL_FN1_(void) refill(I &&in)
				XTAL_0EX
				{
					refill(in.begin(), in.end());
				}

				///\
				Span constructor. \
				Initializes `this` with the values between `i0` and `iN`. \

				template <iterator_q I>
				XTAL_NEW heterotype(I &&i0, I &&iN)
				XTAL_0EX
				{
					refill(XTAL_FWD_(I) (i0), XTAL_FWD_(I) (iN));
				}

				///\
				List constructor. \
				Initializes `this` with the given values. \

				template <iterated_q I>
				XTAL_NEW heterotype(I &&in)
				XTAL_0EX
				{
					refill(XTAL_FWD_(I) (in));
				}
				XTAL_NEW heterotype(bracket_t<V> in)
				XTAL_0EX
				:	heterotype(in.begin(), in.end())
				{
				}

				///\
				List assignment. \
				Replaces the contents of `this` with the given values. \

				XTAL_OP1 = (bracket_t<V> w)
				XTAL_0EX
				{
					refill(w.begin(), w.end());
					return *this;
				}

				///\
				Copy constructor. \
				Initializes `this` with the given vector. \

				XTAL_NEW heterotype(heterotype const &t)
				XTAL_0EX
				:	heterotype(t.begin(), t.end())
				{
				}
				///\
				Copy assigment. \
				Replaces the contents of `this` with the given vector. \

				XTAL_OP1 = (heterotype const &t)
				XTAL_0EX
				{
					refill(t.begin(), t.end());
					return *this;
				}

				///\
				Move constructor. \
				Initializes `this` with the given vector. \

				XTAL_NEW heterotype(heterotype &&t)
				XTAL_0EX
				:	heterotype(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()))
				{
				}
				///\
				Move assigment. \
				Replaces the contents of `this` with the given vector. \

				XTAL_OP1 = (heterotype &&t)
				XTAL_0EX
				{
					refill(_std::make_move_iterator(t.begin()), _std::make_move_iterator(t.end()));
					return *this;
				}

				///\
				Read accessor. \

				template <typename Y=T>
				XTAL_FN2 get() XTAL_0FX_(&)
				{
					if constexpr (is_q<Y, T>)
					{
						return static_cast<T const &>(*this);
					}
					else
					{
						return reinterpret_cast<_std::add_const_t<Y>>(*this);
					}
				}
				template <typename Y=T>
				XTAL_FN2 get() XTAL_0EX_(&)
				{
					if constexpr (is_q<Y, T>)
					{
						return static_cast<T &>(*this);
					}
					else
					{
						return reinterpret_cast<Y>(*this);
					}
				}
				XTAL_RE2_(XTAL_FN2 get(XTAL_DEF i), get()[XTAL_REF_(i)]);

				///\
				Elementwise transformer. \

				XTAL_FN1 transmute(XTAL_DEF_(_std::invocable<V>) f)
				XTAL_0EX
				{
					/*/
					[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) = f(get(Ns))), ..., V()) (seek_v<N_size>);
					/*/
					mutate_linear_f(false, get(), XTAL_REF_(f));
					/***/
					return get();
				}
				
				///\
				Elementwise comparators. \

			//	XTAL_OP2        <=> (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=> t.get(Ns)) <=>...         ) (seek_v<N_size>);}
				XTAL_OP2_(bool) ==  (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ==  t.get(Ns)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) <=  (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <=  t.get(Ns)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) >=  (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >=  t.get(Ns)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) <   (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) <   t.get(Ns)) and ...and true) (seek_v<N_size>);}
				XTAL_OP2_(bool) >   (heterotype const &t) XTAL_0FX {return [&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) >   t.get(Ns)) and ...and true) (seek_v<N_size>);}

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

				XTAL_OP2_(T ) &            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r &= XTAL_REF_(w);}
				XTAL_OP2_(T ) |            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r |= XTAL_REF_(w);}
				XTAL_OP2_(T ) ^            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r ^= XTAL_REF_(w);}
				XTAL_OP2_(T ) +            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r += XTAL_REF_(w);}
				XTAL_OP2_(T ) -            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r -= XTAL_REF_(w);}

				XTAL_OP1_(T&) %=       (bracket_t<V> w) XTAL_0EX {return get() %= T(w.begin(), w.end());}
				XTAL_OP1_(T&) &=       (bracket_t<V> w) XTAL_0EX {return get() &= T(w.begin(), w.end());}
				XTAL_OP1_(T&) |=       (bracket_t<V> w) XTAL_0EX {return get() |= T(w.begin(), w.end());}
				XTAL_OP1_(T&) ^=       (bracket_t<V> w) XTAL_0EX {return get() ^= T(w.begin(), w.end());}
				XTAL_OP1_(T&) +=       (bracket_t<V> w) XTAL_0EX {return get() += T(w.begin(), w.end());}
				XTAL_OP1_(T&) -=       (bracket_t<V> w) XTAL_0EX {return get() -= T(w.begin(), w.end());}
				
				XTAL_OP1_(T&) %=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) %= t.get(Ns)),       ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) &=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) &= t.get(Ns)),       ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) |=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) |= t.get(Ns)),       ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) ^=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ^= t.get(Ns)),       ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) +=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += t.get(Ns)),       ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) -=           (T const &t) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= t.get(Ns)),       ..., get()) (seek_v<N_size>); return get();}
				
				XTAL_OP1_(T&) %= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) %= V(XTAL_REF_(w))), ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) &= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) &= V(XTAL_REF_(w))), ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) |= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) |= V(XTAL_REF_(w))), ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) ^= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) ^= V(XTAL_REF_(w))), ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) += (XTAL_DEF_(to_q<V>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += V(XTAL_REF_(w))), ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) -= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= V(XTAL_REF_(w))), ..., get()) (seek_v<N_size>); return get();}

				XTAL_OP1_(T&) ++                     () XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_(++get(Ns), ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) --                     () XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_(--get(Ns), ..., get()) (seek_v<N_size>); return get();}

			};
			template <typename T>
			requires field_operators_q<V>
			class homotype<T>: public heterotype<T>
			{
				using co = heterotype<T>;

			public:
				using co::co;
				using co::get;

				XTAL_OP2_(T ) *            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r *= XTAL_REF_(w);}
				XTAL_OP2_(T ) /            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r /= XTAL_REF_(w);}
				XTAL_OP2_(T ) +            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r += XTAL_REF_(w);}
				XTAL_OP2_(T ) -            (XTAL_DEF w) XTAL_0FX {auto r = get(); return r -= XTAL_REF_(w);}

				XTAL_OP1_(T&) *= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) *= V(XTAL_REF_(w))), ..., get()) (seek_v<N_size>); return get();}
				XTAL_OP1_(T&) /= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) /= V(XTAL_REF_(w))), ..., get()) (seek_v<N_size>); return get();}
			//	XTAL_OP1_(T&) += (XTAL_DEF_(to_q<V>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) += V(XTAL_REF_(w))), ..., get()) (seek_v<N_size>); return get();}
			//	XTAL_OP1_(T&) -= (XTAL_DEF_(to_q<V>) w) XTAL_0EX {[&] <auto ...Ns>(seek_t<Ns...>) XTAL_0FN_((get(Ns) -= V(XTAL_REF_(w))), ..., get()) (seek_v<N_size>); return get();}

			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};

		};
		template <typename V>
		using scalar_t = typename scalar<V>::type;

		template <typename U> struct multiplicative;
		template <typename U> using  multiplicative_t = typename multiplicative<U>::type;

		template <typename U> struct additive;
		template <typename U> using  additive_t = typename additive<U>::type;

		///

		template <typename U>
		struct multiplicative
		{
			using V = based_t<U>;
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

				using transformed_t = typename additive<U>::type;

			//	Elementwise multiplication/division:
				XTAL_OP1_(T&) *= (bracket_t<V> w) XTAL_0EX {return get() *= T(w.begin(), w.end());}
				XTAL_OP1_(T&) /= (bracket_t<V> w) XTAL_0EX {return get() /= T(w.begin(), w.end());}				
				
				XTAL_OP1_(T&) *= (T const &t)
				XTAL_0EX
				{
					[&] <auto ...Ns>(seek_t<Ns...>)
						XTAL_0FN_((get(Ns) *= t.get(Ns)), ..., get())
					(seek_v<N_size>);
					return get();
				}
				
				XTAL_OP1_(T&) /= (T const &t)
				XTAL_0EX
				{
					[&] <auto ...Ns>(seek_t<Ns...>)
						XTAL_0FN_((get(Ns) /= t.get(Ns)), ..., get())
					(seek_v<N_size>);
					return get();
				}
				
			};
			class type: public homotype<type>
			{
				using co = homotype<type>;

			public:
				using co::co;

			};
		};
		template <typename U, auto N_shift>
		struct converse;

		template <typename U, auto N_shift>
		requires (N_size == 2)
		struct converse<U, N_shift>
		{
			using V = based_t<U>;
			using realized = realize<V>;

			template <typename T>
			using heterotype = typename multiplicative<V>::template homotype<T>;

			template <typename T>
			class homotype: public heterotype<T>
			{
				using co = heterotype<T>;
			public:
				using co::co;
				using co::get;

				using reflected_t = typename converse<U, N_shift^1>::type;

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
		template <typename U, auto N_shift>
		using converse_t = typename converse<U, N_shift>::type;

		template <typename U>
		struct additive
		{
			using V = based_t<U>;
			using realized = realize<V>;

			template <typename T>
			using heterotype = typename scalar<V>::template homotype<T>;

			template <typename T>
			class homotype: public heterotype<T>
			{
			//	TODO: Subclass to define additive pairs like `complex`. \

				using co = heterotype<T>;
			public:
				using co::co;
				using co::get;

				using transformed_t = typename multiplicative<U>::type;

			//	Elementwise addition/subtraction:
				XTAL_OP1_(T&) += (bracket_t<V> w) XTAL_0EX {return get() += T(w.begin(), w.end());}
				XTAL_OP1_(T&) -= (bracket_t<V> w) XTAL_0EX {return get() -= T(w.begin(), w.end());}
				
				XTAL_OP1_(T&) += (T const &t)
				XTAL_0EX
				{
					[&] <auto ...Ns>(seek_t<Ns...>)
						XTAL_0FN_((get(Ns) += t.get(Ns)), ..., get())
					(seek_v<N_size>);
					return get();
				}
				XTAL_OP1_(T&) -= (T const &t)
				XTAL_0EX
				{
					[&] <auto ...Ns>(seek_t<Ns...>)
						XTAL_0FN_((get(Ns) -= t.get(Ns)), ..., get())
					(seek_v<N_size>);
					return get();
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
		struct series
		{
			using V = based_t<U>;
			using realized = realize<V>;

			template <typename T>
			using heterotype = typename additive<V>::template homotype<T>;

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

				template <sigma_t N_limit=N_size, sigma_t N_index=0>
				XTAL_FN1_(T&) generate(V const &u)
				XTAL_0EX
				{
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
					for (sigma_t i = _1; i < _H; ++i)
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
					copy_linear_f(false, _k1, _std::span(i0, j0), [] (V const &v) XTAL_0FN_(V(-v.imag(), -v.real())));
					copy_linear_f(false,  k1, _std::span(i1, k1), [] (V const &v) XTAL_0FN_(V( v.imag(), -v.real())));
					return s;
				}
				
				///\returns `that` transformed by the FFT, \
				using `this` as the Fourier basis. \

				template <iterated_q Y>
				XTAL_FN1_(typename Y::transformed_t &) transform(Y &that)
				XTAL_0EX
				requires bit_ceiling_q<N_size, 1>
				{
					sigma_t const n_size = that.size();
					sigma_t const h_size = n_size >> 1;
					sigma_t const k_size = bit_ceiling_y(n_size); assert(n_size == 1 << k_size);
					sigma_t const K_size = bit_ceiling_y(N_size); assert(k_size <= K_size);

					for (sigma_t h = 0; h < h_size; ++h)
					{
						_std::swap(that[h], that[bit_reverse_y(h, k_size)]);
					}
					if constexpr (of_q<Y, typename multiplicative<U>::type>)
					{
						mutate_linear_f(false, that, [] (XTAL_DEF u) XTAL_0FN_(_std::conj(XTAL_REF_(u))));
					}
					for (sigma_t k = 0; k < k_size; ++k)
					{
						sigma_t const kn = K_size - k;
						sigma_t const u = 1 << k;
						sigma_t const w = u << 1;
						for (sigma_t                 i = 0; i < u; i += 1)
						for (sigma_t kn_i = i << kn, j = i; j < n_size; j += w)
						{
							V const y = that[j + u]*get(kn_i);
							V const x = that[j + 0];
							that[j + u] = x - y;
							that[j + 0] = x + y;
						}
					}
					if constexpr (of_q<Y, typename multiplicative<U>::type>)
					{
						auto const u_size = realized::template ratio_y<1>(n_size);
						mutate_linear_f(false, that, [=] (XTAL_DEF u) XTAL_0FN_(_std::conj(XTAL_REF_(u)*u_size)));
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
		using series_t = typename series<V>::type;

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
				\returns the fixed capacity `N_size` of the `vector`. \

				XTAL_FN2_(size_type) capacity()
				XTAL_0EX
				{
					return N_size;
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
					erase(i0, _std::next(i0, sN), sN);
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
				Does nothing besides `throw std::bad_alloc` if the required `sN` exceeds the maximum `N_size`. \

				XTAL_FN1_(void) reserve(size_type sN)
				{
					if (N_size < sN)
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
						auto j = reverse_appointer_f(limit_m);
						move_linear_f(true, _std::prev(j, sN), j, _std::next(j, sN));
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
						move_linear_f(sN <= _std::distance(jN, limit_m), j0, jN, limit_m);
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
		struct vector<V>
		{
			using type = _std::vector<V>;

		};
		template <typename V>
		using vector_t = typename vector<V>::type;

		template <typename V>
		using visor_t = spanner_t<vector_t<V>>;

		template <typename V>
		using funnel_t = _std::priority_queue<V, vector_t<V>, _std::greater<V>>;

		template <typename V>
		using allocator_t = typename vector_t<V>::allocator_type;

	};
	using type = subtype<construct_t<>>;

};

template <delta_t N_size>
using buffer_t = typename buffer<N_size>::type;

template <delta_t N_size, typename V>
using buffer_scalar_t = typename buffer_t<N_size>::template scalar_t<V>;

template <delta_t N_size, typename V>
using buffer_series_t = typename buffer_t<N_size>::template series_t<V>;

template <delta_t N_size, typename V>
using buffer_multiplicative_t = typename buffer_t<N_size>::template multiplicative_t<V>;

template <delta_t N_size, typename V>
using buffer_converse_t = typename buffer_t<2>::template converse_t<V, N_size>;

template <delta_t N_size, typename V>
using buffer_vector_t = typename buffer_t<N_size>::template vector_t<V>;

template <delta_t N_size, typename V>
using buffer_funnel_t = typename buffer_t<N_size>::template funnel_t<V>;

template <delta_t N_size, typename V>
using buffer_allocator_t = typename buffer_t<N_size>::template allocator_t<V>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
