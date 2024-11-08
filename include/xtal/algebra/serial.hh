#pragma once
#include "./any.hh"
#include "./lattice.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class           ..._s>	XTAL_TYP serial;
template <class           ..._s>	XTAL_USE serial_t = typename serial<_s...>::type;
template <class           ...Ts>	XTAL_REQ serial_q = bond::any_tag_p<serial_t, Ts...>;
template <size_type N, class ...Ts>	XTAL_REQ serial_p = serial_q<Ts...> and (...and (N == Ts::size()));
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_LET serial_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<serial_t>::template via<V>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `lattice` with point-wise addition, and multiplication defined by linear convolution. \

template <column_q A>
struct serial<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using endotype = typename lattice<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<serial_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  S_ = holotype<T>;
	
	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::let;
		using S_::self;
		using S_::twin;
	
	public:// OPERATE
		using S_::operator*=;
	//	using S_::operator+=;
	//	using S_::operator-=;

		XTAL_DEF_(return,inline) XTAL_LET operator  * (auto       const &t) XTAL_0FX        {return twin() *=   t ;}
		XTAL_DEF_(return,inline) XTAL_LET operator  + (auto       const &t) XTAL_0FX        {return twin() +=   t ;}
		XTAL_DEF_(return,inline) XTAL_LET operator  - (auto       const &t) XTAL_0FX        {return twin() -=   t ;}
		XTAL_DEF_(inline)        XTAL_LET operator  *=(embrace_t<U_data> t) XTAL_0EX -> T & {return self() *= T(t);}
		XTAL_DEF_(inline)        XTAL_LET operator  +=(embrace_t<U_data> t) XTAL_0EX -> T & {return self() += T(t);}
		XTAL_DEF_(inline)        XTAL_LET operator  -=(embrace_t<U_data> t) XTAL_0EX -> T & {return self() -= T(t);}
		XTAL_DEF_(inline)        XTAL_LET operator ++ (int)                 XTAL_0EX -> T   {auto t = twin(); operator++(); return t;}
		XTAL_DEF_(inline)        XTAL_LET operator -- (int)                 XTAL_0EX -> T   {auto t = twin(); operator--(); return t;}


		///\
		Produces the successor by pairwise addition from `begin()` to `end()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_DEF_(inline)
		XTAL_LET operator ++ ()
		XTAL_0EX -> T &
		{
			[this]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(self()) += get<I + 1>(self())),...);}
			(bond::seek_s<N_data - 1>{});
			
			return self();
		}
		///\
		Produces the predecessor by pairwise subtraction from `end()` to `begin()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_DEF_(inline)
		XTAL_LET operator -- ()
		XTAL_0EX -> T &
		{
			[this]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(self()) -= get<I + 1>(self())),...);}
			(bond::antiseek_s<N_data - 1>{});
			
			return self();
		}


		///\
		Multiplication by linear convolution, truncated by `N_data`. \

	//	XTAL_DEF_(inline)
		XTAL_LET operator *=(T const &t)
		XTAL_0EX -> T &
		{
			auto &s = self();
			
			if constexpr (_op::alignment::value < N_data) {
				for (auto i = N_data; ~--i;) {let(i) *= get<0>(t);
				for (auto j = i; j-- ;) {let(i) += t.let(j)*let(i - j);}}
			}
			else {
				bond::seek_backward_f<N_data, 0>([&, this] (auto I) XTAL_0FN {get<I>(s) *= get<0>(t);
				bond::seek_backward_f<     I, 1>([&, this] (auto J) XTAL_0FN {get<I>(s) += get<J>(t)*get<I - J>(s);});});
			}
			return s;
		}

	//	Vector addition:

		XTAL_DEF_(inline)
		XTAL_LET operator +=(T const &t)
		XTAL_0EX -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u += v;}>(XTAL_REF_(t));
		}
		XTAL_DEF_(inline)
		XTAL_LET operator -=(T const &t)
		XTAL_0EX -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u -= v;}>(XTAL_REF_(t));
		}

		XTAL_DEF_(inline)
		XTAL_LET operator +=(subarray_q<N_data> auto const &t)
		XTAL_0EX -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u += v;}>(XTAL_REF_(t));
		}
		XTAL_DEF_(inline)
		XTAL_LET operator -=(subarray_q<N_data> auto const &t)
		XTAL_0EX -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u -= v;}>(XTAL_REF_(t));
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
