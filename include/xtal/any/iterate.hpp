#pragma once
#include "./any.hpp"
#include "./utilize.hpp"
#include "./realize.hpp"




XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename    T  >    using iterate_t  = _v3::ranges::view_interface<T>;


template <typename    T  >    using front_t    = XTAL_TYP_(*XTAL_VAL_(T).begin());
template <typename    T  >    using begin_t    = XTAL_TYP_( XTAL_VAL_(T).begin());

template <typename    T  >  concept front_p    = requires (T t) {t.front();};
template <typename    T  >  concept begin_p    = requires (T t) {t.begin();};


template <typename    T  >  concept iterable_p = begin_p<T> and not front_p<T>;
template <typename    T  >  concept iterated_p = begin_p<T> and     front_p<T>;
template <typename    T  >  concept iterator_p = requires (T t) {*++t;};
template <typename    T  >  concept integral_p = _std::integral<T>;

template <typename ...Ts >  concept iterable_q = every_q<iterable_p<Ts>...>;
template <typename ...Ts >  concept iterated_q = every_q<iterated_p<Ts>...>;//_v3::ranges::forward_range
template <typename ...Ts >  concept iterator_q = every_q<iterator_p<Ts>...>;//_v3::ranges::forward_iterator
template <typename ...Ts >  concept integral_q = every_q<integral_p<Ts>...>;

template <typename    T  >   struct iterated;
template <typename    T  >   struct iterator;
template <typename    T  >   struct iteratee;

template <typename    T  >    using iterated_t = typename iterated<T>::type;
template <typename    T  >    using iterator_t = typename iterator<T>::type;//_v3::ranges::iterator_t
template <typename    T  >    using iteratee_t = typename iteratee<T>::type;//_v3::ranges::range_reference_t, _v3::ranges::iter_reference_t

template <iterated_p  T  >   struct iterated<T>: constant_t<1> {using type =                  based_t<T> ;};
template <iterator_p  T  >   struct iterated<T>: constant_t<0> {using type =                   void      ;};
template <integral_p  T  >   struct iterated<T>: constant_t<0> {using type = _v3::ranges::iota_view<T, T>;};

template <iterated_p  T  >   struct iterator<T>: constant_t<0> {using type =                  begin_t<T> ;};
template <iterator_p  T  >   struct iterator<T>: constant_t<1> {using type =                  based_t<T> ;};
template <integral_p  T  >   struct iterator<T>: constant_t<0> {using type =    iterator_t<iterated_t<T>>;};

template <iterated_p  T  >   struct iteratee<T>: constant_t<0> {using type =                  front_t<T> ;};
template <iterator_p  T  >   struct iteratee<T>: constant_t<0> {using type =                pointed_t<T> ;};
template <integral_p  T  >   struct iteratee<T>: constant_t<1> {using type =                  based_t<T> ;};


template <typename    T  >    using sentinel_t = based_t<_v3::ranges::sentinel_t<T>>;
template <typename    T  >    using distance_t = XTAL_TYP_(_std::distance(XTAL_VAL_(iterator_t<T>), XTAL_VAL_(iterator_t<T>)));


template <typename    T  >  concept counted_p  = is_q<T, iterated_t<iteratee_t<T>>>;
template <typename    T  >  concept counter_p  = integral_q<T>;

template <typename ...Ts >  concept counted_q  = every_q<counted_p<Ts>...>;
template <typename ...Ts >  concept counter_q  = every_q<counter_p<Ts>...>;

template <typename    T  >   struct counted;
template <typename    T  >   struct counter;

template <counted_p   T  >   struct counted<T> : constant_t<1> {using type =    based_t<T>;};
template <counter_p   T  >   struct counted<T> : constant_t<0> {using type = iterated_t<T>;};

template <counted_p   T  >   struct counter<T> : constant_t<0> {using type = iteratee_t<T>;};
template <counter_p   T  >   struct counter<T> : constant_t<1> {using type =    based_t<T>;};

template <typename T=iota_t> using  counted_t  = typename counted<T>::type;
template <typename T=iota_t> using  counter_t  = typename counter<T>::type;


////////////////////////////////////////////////////////////////////////////////

XTAL_FZ2 iterate_forward_f(XTAL_DEF z)
XTAL_0EX
{
	using namespace _v3::ranges;
	using  Z = any_view<iteratee_t<XTAL_TYP_(z)>, category::forward>;
	return Z(XTAL_REF_(z));
}
XTAL_FZ2 iterate_forward_f(XTAL_DEF z)
XTAL_0EX
XTAL_IF2 {z.size();}
{
	using namespace _v3::ranges;
	using  Z = any_view<iteratee_t<XTAL_TYP_(z)>, category::forward|category::sized>;
	return Z(XTAL_REF_(z))|_v3::views::take(z.size());
}
XTAL_LET iterate_function_f = [](XTAL_DEF f)
XTAL_0FN_([g = XTAL_REF_(f)](XTAL_DEF ...xs)
XTAL_0FN
{
	using namespace _v3::views;
	if constexpr (0 == sizeof...(xs))
	{	return iota(0)|transform([=](auto &&) XTAL_0FN_(g(XTAL_REF_(xs)...)));
//	{	return generate(_std::move(g));// FIXME?
	}
	else
	if constexpr (1 == sizeof...(xs))
	{	return transform(XTAL_REF_(xs)..., g);
	}
	else
	{	return zip_with(g, XTAL_REF_(xs)...);
	}
});


////////////////////////////////////////////////////////////////////////////////

template <iterated_q ...Ys> struct isomorphic<Ys...>: isomeric<iterated_t<Ys>...> {};
template <iterator_q ...Ys> struct isomorphic<Ys...>: isomeric<iterated_t<Ys>...> {};


template <iterated_q X, iterated_q Y>
XTAL_FN2_(bool) arranged_eq(X const &x, Y const &y)
XTAL_0EX
{
	if constexpr (iso_q<X, Y>)
	{	return x.begin() == y.begin() and x.end() == y.end();
	}
	else
	{	return false;
	}
}

template <typename T>
using     deranged_t = _v3::ranges::subrange<iterator_t<T>, sentinel_t<T>>;
XTAL_LET  deranged_f = [](XTAL_DEF x)
XTAL_0FN_(deranged_t<decltype(x)>(XTAL_REF_(x)));

template <iterated_q X, iterated_q Y>
XTAL_FN2_(bool) deranged_eq(X const &x, Y const &y)
XTAL_0EX
{
	return arranged_eq(deranged_f(x), deranged_f(y));
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
