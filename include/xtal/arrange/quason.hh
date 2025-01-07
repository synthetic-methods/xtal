#pragma once
#include "./any.hh"
#include "./order.hh"





XTAL_ENV_(push)
namespace xtal::arrange
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class              ..._s>	struct   quason;
template <class              ..._s>	using    quason_t = typename quason<_s...>::type;
template <class              ...Ts>	concept  quason_q = bond::tag_p<quason_t, Ts...>;
template <size_type N, class ...Ts>	concept  quason_p = quason_q<Ts...> and (...and (N == Ts::size()));
template <class  V=void>
XTAL_DEF_(short)
XTAL_LET quason_f(auto &&...oo)
noexcept -> auto
{
	return _detail::initialize<quason_t>::template via<V>(XTAL_REF_(oo)...);
}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `arrange::order` with point-wise addition, and multiplication defined by linear convolution. \

template <vector_q A>
struct quason<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using endotype = typename arrange::order<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<quason_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using  S_ = holotype<T>;
	
	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::element;
		using S_::self;
		using S_::twin;
	
	public:// OPERATE
		using S_::operator*=;
	//	using S_::operator+=;
	//	using S_::operator-=;

		XTAL_DEF_(short)  XTAL_LET operator  * (auto const &t)      const noexcept -> auto   {return twin() *=   t ;}
		XTAL_DEF_(short)  XTAL_LET operator  + (auto const &t)      const noexcept -> auto   {return twin() +=   t ;}
		XTAL_DEF_(short)  XTAL_LET operator  - (auto const &t)      const noexcept -> auto   {return twin() -=   t ;}
		XTAL_DEF_(inline) XTAL_LET operator  *=(initializer_s<U_data> t)  noexcept -> auto & {return self() *= T(t);}
		XTAL_DEF_(inline) XTAL_LET operator  +=(initializer_s<U_data> t)  noexcept -> auto & {return self() += T(t);}
		XTAL_DEF_(inline) XTAL_LET operator  -=(initializer_s<U_data> t)  noexcept -> auto & {return self() -= T(t);}
		XTAL_DEF_(inline) XTAL_LET operator ++ (int)                      noexcept -> auto   {auto t = twin(); operator++(); return t;}
		XTAL_DEF_(inline) XTAL_LET operator -- (int)                      noexcept -> auto   {auto t = twin(); operator--(); return t;}


		///\
		Produces the successor by pairwise addition from `begin()` to `end()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_DEF_(inline)
		XTAL_LET operator ++ ()
		noexcept -> T &
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
		noexcept -> T &
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
		noexcept -> T &
		{
			auto &s = self();
			
			if constexpr (_op::alignment::value < N_data) {
				for (auto i = N_data; ~--i;) {element(i) *= get<0>(t);
				for (auto j = i; j-- ;) {element(i) += t.element(j)*element(i - j);}}
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
		noexcept -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u += v;}>(XTAL_REF_(t));
		}
		XTAL_DEF_(inline)
		XTAL_LET operator -=(T const &t)
		noexcept -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u -= v;}>(XTAL_REF_(t));
		}

		XTAL_DEF_(inline)
		XTAL_LET operator +=(subarray_q<N_data> auto const &t)
		noexcept -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u += v;}>(XTAL_REF_(t));
		}
		XTAL_DEF_(inline)
		XTAL_LET operator -=(subarray_q<N_data> auto const &t)
		noexcept -> T &
		{
			return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u -= v;}>(XTAL_REF_(t));
		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(atomic_q<quason_t<float[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
