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
template <typename    T  >  concept front_p    = requires (T t) {t.front();};
template <typename    T  >  concept begin_p    = requires (T t) {t.begin();};

template <typename    T  >  concept iterable_p = begin_p<T> and not front_p<T>;
template <typename    T  >  concept iterated_p = begin_p<T> and     front_p<T>;//_v3::ranges::range<based_t<T>>;
template <typename    T  >  concept iterator_p = requires {typename _std::iterator_traits<T>::iterator_category;};//_v3::ranges::contiguous_iterator<based_t<T>>;
template <typename    T  >  concept integral_p = _std::integral<T>;

template <typename ...Ts >  concept iterable_q = every_q<iterable_p<Ts>...>;
template <typename ...Ts >  concept iterated_q = every_q<iterated_p<Ts>...>;
template <typename ...Ts >  concept iterator_q = every_q<iterator_p<Ts>...>;
template <typename ...Ts >  concept integral_q = every_q<integral_p<Ts>...>;

template <typename    T  >   struct iterated;
template <typename    T  >   struct iterator;
template <typename    T  >   struct iteratee;

template <typename    T  >    using iterated_t = typename iterated<T>::type;
template <typename    T  >    using iterator_t = typename iterator<T>::type;
template <typename    T  >    using iteratee_t = typename iteratee<T>::type;

template <iterated_p  T  >   struct iterated<T>: constant_t< true> {using type = T;};
template <integral_p  T  >   struct iterated<T>: constant_t<false> {using type = _v3::ranges::iota_view<T, T>;};

template <iterator_p  T  >   struct iterator<T>: constant_t< true> {using type = T;};
template <iterated_p  T  >   struct iterator<T>: constant_t<false> {using type = _v3::ranges::iterator_t<T> ;};
template <integral_p  T  >   struct iterator<T>: constant_t<false> {using type =   iterator_t<iterated_t<T>>;};

template <iterated_p  T  >   struct iteratee<T>: constant_t<false> {using type = _v3::ranges::range_reference_t<T>;};
template <iterator_p  T  >   struct iteratee<T>: constant_t<false> {using type = _v3::ranges:: iter_reference_t<T>;};


template <typename    T  >    using sentinel_t = _v3::ranges::sentinel_t<T>;
template <typename    T  >    using distance_t = XTAL_TYP_(_std::distance(XTAL_VAL_(iterator_t<T>), XTAL_VAL_(iterator_t<T>)));


template <typename    T  >  concept counted_p  = is_q<T, iterated_t<iteratee_t<T>>, _v3::ranges::iota_view<iteratee_t<T>, sentinel_t<T>>>;
template <typename    T  >  concept counter_p  = integral_q<T>;

template <typename ...Ts >  concept counted_q  = every_q<counted_p<Ts>...>;
template <typename ...Ts >  concept counter_q  = every_q<counter_p<Ts>...>;

template <typename    T  >   struct counted;
template <typename    T  >   struct counter;

template <counted_p   T  >   struct counted<T> : constant_t< true> {using type =            T ;};
template <counter_p   T  >   struct counted<T> : constant_t<false> {using type = iterated_t<T>;};

template <counted_p   T  >   struct counter<T> : constant_t<false> {using type = iteratee_t<T>;};
template <counter_p   T  >   struct counter<T> : constant_t< true> {using type =            T ;};

template <typename T=iota_t>  using counted_t  = typename counted<T>::type;
template <typename T=iota_t>  using counter_t  = typename counter<T>::type;


template <iterated_q ...Ys>  struct isomorphic<Ys...>: isomeric<iteratee_t<Ys>...> {};
template <iterator_q ...Ys>  struct isomorphic<Ys...>: isomeric<iteratee_t<Ys>...> {};


////////////////////////////////////////////////////////////////////////////////

template <typename T>
using     deranged_t = _v3::ranges::subrange<iterator_t<T>, sentinel_t<T>>;
XTAL_LET  deranged_f = [](XTAL_DEF x)
XTAL_0FN_(deranged_t<decltype(x)>(XTAL_REF_(x)));

template <iterated_q X, iterated_q Y>
XTAL_FN2_(bool) deranged_b(X const &x, Y const &y)
XTAL_0EX
{
	auto const _x = deranged_f(x);
	auto const _y = deranged_f(y);
	return x.begin() == y.begin() and x.end() == y.end();
}


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

template <typename F>
struct iterate_map
{
	class type
	{
		F function_m;

	public:
		XTAL_NEW_(explicit) type(F &&f)
		XTAL_0EX
		:	function_m(XTAL_FWD_(F) (f))
		{
		}
		XTAL_OP2() () &&
		XTAL_0EX
		{
		//	return _v3::views::generate(_std::move(function_m));// FIXME
			return _v3::views::iota(0)|
				_v3::views::transform([f = _std::move(function_m)](auto &&) XTAL_0FN_(f()));
		}
		XTAL_OP2() (XTAL_DEF x) &&
		XTAL_0EX
		{
			return _v3::views::transform(XTAL_REF_(x), _std::move(function_m));
		}
		XTAL_OP2() (XTAL_DEF ...xs) &&
		XTAL_0EX
		{
			return _v3::views::zip_with(_std::move(function_m), XTAL_REF_(xs)...);
		}

	};
};
template <typename F>
using     iterate_map_t = typename iterate_map<F>::type;
XTAL_LET  iterate_map_f = [](XTAL_DEF f)
XTAL_0FN_(iterate_map_t<decltype(f)>(XTAL_REF_(f)));


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
