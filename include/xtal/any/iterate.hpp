#pragma once
#include "./any.hpp"
#include "./utilize.hpp"
#include "./realize.hpp"




XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename    T > using     iterate_t  = _v3::ranges::view_interface<T>;

template <typename    T > using    iterator_ts = _std::iterator_traits<T>;
template <typename    T > concept  iterable_p  = requires (T t) {t.begin();} and not requires (T t) {t.front();};
template <typename    T > concept  iterated_p  = _v3::ranges::forward_range<based_t<T>>;
template <typename    T > concept  iterator_p  =  pointer_p<T> or requires {typename iterator_ts<T>::iterator_category;};//_v3::ranges::forward_iterator<based_t<T>>;
template <typename    T > concept  iteratee_p  = iterated_p<T> or iterator_p<T>;

template <typename    T > struct   iterated;
template <iterated_p  T > struct   iterated<T> : _std:: true_type {using type = based_t<T>;};

template <typename    T > struct   iterator;
template <iterator_p  T > struct   iterator<T> : _std:: true_type {using type = based_t<T>;};
template <iterated_p  T > struct   iterator<T> : _std::false_type {using type = _v3::ranges::iterator_t<T>;};

template <typename    T > struct   iteratee;
template <iterated_p  T > struct   iteratee<T> : _std:: true_type {using type = _v3::ranges::range_reference_t<T>;};
template <iterator_p  T > struct   iteratee<T> : _std:: true_type {using type = _v3::ranges:: iter_reference_t<T>;};

template <typename ...Ts> concept   iterable_q = every_q<iterable_p<Ts>...>;
template <typename ...Ts> concept   iterated_q = every_q<iterated_p<Ts>...>;
template <typename ...Ts> concept   iterator_q = every_q<iterator_p<Ts>...>;
template <typename ...Ts> concept   iteratee_q = every_q<iteratee_p<Ts>...>;
template <typename    T > using     iterated_t = typename iterated<T>::type;
template <typename    T > using     iterator_t = typename iterator<T>::type;
template <typename    T > using     iteratee_t = typename iteratee<T>::type;
template <typename    T > using     sentinel_t = _v3::ranges::sentinel_t<T>;
template <typename    V > using     repeated_t = _v3::ranges::repeat_view<V>;

template <typename    V > using     ioted_t    = _v3::ranges::iota_view<V, V>;
template <typename    V > using     iotor_t    = iterator_t<ioted_t<V>>;
template <typename    T > concept   counted_p  = iterated_p<T> and to_q<T, ioted_t<iteratee_t<T>>>;
template <typename    T > concept   countor_p  = iterator_p<T> and to_q<T, iotor_t<iteratee_t<T>>>;
template <typename    T > concept   countee_p  = _std::integral<T>;

template <typename    T > struct    counted;
template <counted_p   T > struct    counted<T> : _std:: true_type {using type = based_t<T>;};
template <countee_p   T > struct    counted<T> : _std::false_type {using type = ioted_t<T>;};

template <typename    T > struct    countor;
template <countor_p   T > struct    countor<T> : _std:: true_type {using type = based_t<T>;};
template <countee_p   T > struct    countor<T> : _std::false_type {using type = iotor_t<T>;};

template <typename    T > struct    countee;
template <counted_p   T > struct    countee<T> : _std::false_type {using type = iteratee_t<T>;};
template <countor_p   T > struct    countee<T> : _std::false_type {using type = iteratee_t<T>;};
template <countee_p   T > struct    countee<T> : _std:: true_type {using type =    based_t<T>;};

template <typename ...Ts> concept   counted_q  = every_q<counted_p<Ts>...>;
template <typename ...Ts> concept   countor_q  = every_q<countor_p<Ts>...>;
template <typename ...Ts> concept   countee_q  = every_q<countee_p<Ts>...>;
template <typename T=iota_t> using  counted_t  = typename counted<T>::type;
template <typename T=iota_t> using  countor_t  = typename countor<T>::type;
template <typename T=iota_t> using  countee_t  = typename countee<T>::type;



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

////////////////////////////////////////////////////////////////////////////////

template <iterated_q ...Ys>
struct isomorphic<Ys...>
:	isomeric<iteratee_t<Ys>...>
{};

template <iterator_q ...Ys>
struct isomorphic<Ys...>
:	isomeric<iteratee_t<Ys>...>
{};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

XTAL_FZ2 iterate_forward_f(XTAL_DEF z)
XTAL_0EX
{
	using namespace _v3::ranges;
	using  Z = any_view<range_value_t<XTAL_TYP_(z)>, category::forward>;
	return Z(XTAL_REF_(z));
}
XTAL_FZ2 iterate_forward_f(XTAL_DEF z)
XTAL_QEX requires {z.size();}
{
	using namespace _v3::ranges;
	using  Z = any_view<range_value_t<XTAL_TYP_(z)>, category::forward|category::sized>;
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
