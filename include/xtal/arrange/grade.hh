#pragma once
#include "./any.hh"
#include "./order.hh"





XTAL_ENV_(push)
namespace xtal::arrange
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class              ..._s>	struct   grade;
template <class              ..._s>	using    grade_t = typename grade<_s...>::type;
template <class              ...Ts>	concept  grade_q = bond::tag_p<grade_t, Ts...>;
template <size_type N, class ...Ts>	concept  grade_p = grade_q<Ts...> and (...and (N == Ts::size()));
template <class  V=void>
XTAL_DEF_(short)
XTAL_LET grade_f(auto &&...oo)
noexcept -> auto
{
	return _detail::initialize<grade_t>::template via<V>(XTAL_REF_(oo)...);
}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `order` with point-wise addition and differential succession. \

template <vector_q A>
struct grade<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using endotype = typename arrange::order<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<grade_t>>;

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
	//	using S_::operator+=;
	//	using S_::operator-=;

		XTAL_DEF_(short)  XTAL_LET operator + (auto const &t)      const noexcept -> auto   {return twin() +=   t ;}
		XTAL_DEF_(short)  XTAL_LET operator - (auto const &t)      const noexcept -> auto   {return twin() -=   t ;}
		XTAL_DEF_(inline) XTAL_LET operator +=(initializer_s<U_data> t)  noexcept -> auto & {return self() += T(t);}
		XTAL_DEF_(inline) XTAL_LET operator -=(initializer_s<U_data> t)  noexcept -> auto & {return self() -= T(t);}
		XTAL_DEF_(inline) XTAL_LET operator ++(int)                      noexcept -> auto   {auto t = twin(); operator++(); return t;}
		XTAL_DEF_(inline) XTAL_LET operator --(int)                      noexcept -> auto   {auto t = twin(); operator--(); return t;}


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
	using type = derive_t<homotype>;

};
static_assert(atomic_q<grade_t<float[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
