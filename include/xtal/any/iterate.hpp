#pragma once
#include "./any.hpp"
#include "./realize.hpp"





XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename    T > using     iterate_t  = _v3::ranges::view_interface<T>;

template <typename    T > using    iterator_ts = _std::iterator_traits<T>;
template <typename    T > concept  iterable_b  = requires (T t) {t.begin();} and not requires (T t) {t.front();};
template <typename    T > concept  iterated_b  = _v3::ranges::forward_range<based_t<T>>;
template <typename    T > concept  iterator_b  =  pointer_b<T> or requires {typename iterator_ts<T>::iterator_category;};//_v3::ranges::forward_iterator<based_t<T>>;
template <typename    T > concept  iteratee_b  = iterated_b<T> or iterator_b<T>;

template <typename    T > struct   iterated                   {using type = void;};
template <typename    T > struct   iterator                   {using type = void;};
template <typename    T > struct   iteratee                   {using type = void;};
template <iterated_b  T > struct   iterated<T> : _std:: true_type {using type = based_t<T>;};
template <iterator_b  T > struct   iterator<T> : _std:: true_type {using type = based_t<T>;};
template <iterated_b  T > struct   iteratee<T> : _std:: true_type {using type = _v3::ranges::range_reference_t<T>;};
template <iterator_b  T > struct   iteratee<T> : _std:: true_type {using type = _v3::ranges:: iter_reference_t<T>;};
template <iterated_b  T > struct   iterator<T> : _std::false_type {using type = _v3::ranges::       iterator_t<T>;};


template <typename ...Ts> concept uniterable_q =   false_p<iterable_b<Ts>...>;
template <typename ...Ts> concept uniterated_q =   false_p<iterated_b<Ts>...>;
template <typename ...Ts> concept   iterable_q = unfalse_p<iterable_b<Ts>...>;
template <typename ...Ts> concept   iterated_q = unfalse_p<iterated_b<Ts>...>;
template <typename ...Ts> concept   iterator_q = unfalse_p<iterator_b<Ts>...>;
template <typename ...Ts> concept   iteratee_q = unfalse_p<iteratee_b<Ts>...>;
template <typename    T > using     iterated_t = typename iterated<T>::type;
template <typename    T > using     iterator_t = typename iterator<T>::type;
template <typename    T > using     iteratee_t = typename iteratee<T>::type;
template <typename    T > using     sentinel_t = _v3::ranges::sentinel_t<T>;
template <typename    V > using     repeated_t = _v3::ranges::repeat_view<V>;

template <typename    V > using     ioted_t    = _v3::ranges::iota_view<V, V>;
template <typename    V > using     iotor_t    = iterator_t<ioted_t<V>>;
template <typename    T > concept   ioted_b    = iterated_b<T> and to_q<T, ioted_t<iteratee_t<T>>>;
template <typename    T > concept   iotor_b    = iterator_b<T> and to_q<T, iotor_t<iteratee_t<T>>>;
template <typename ...Ts> concept   iotee_q    = bit_operators_q<Ts...>;

template <typename    T > struct    counted                       {using type = void;};
template <typename    T > struct    countor                       {using type = void;};
template <typename    T > struct    countee                       {using type = void;};

template <ioted_b     T > struct    counted<T> : _std:: true_type {using type =    based_t<T>;};
template <ioted_b     T > struct    countee<T> : _std::false_type {using type = iteratee_t<T>;};

template <iotor_b     T > struct    countor<T> : _std:: true_type {using type =    based_t<T>;};
template <iotor_b     T > struct    countee<T> : _std::false_type {using type = iteratee_t<T>;};

template <iotee_q     T > struct    countee<T> : _std:: true_type {using type = based_t<T>;};
template <iotee_q     T > struct    counted<T> : _std::false_type {using type = ioted_t<T>;};
template <iotee_q     T > struct    countor<T> : _std::false_type {using type = iotor_t<T>;};

template <typename ...Ts> concept   counted_q  = unfalse_p<counted<Ts>::value...>;
template <typename ...Ts> concept   countor_q  = unfalse_p<countor<Ts>::value...>;
template <typename ...Ts> concept   countee_q  = iotee_q<Ts...>;//unfalse_p<countee<Ts>::value...>;
template <typename T=iota_t> using  counted_t  = typename counted<T>::type;
template <typename T=iota_t> using  countor_t  = typename countor<T>::type;
template <typename T=iota_t> using  countee_t  = typename countee<T>::type;

template <typename T>
using     spanner_t = _v3::ranges::subrange<iterator_t<T>, sentinel_t<T>>;
XTAL_LET  spanner_f = [] (XTAL_DEF x)
XTAL_0FN_(spanner_t<decltype(x)>(XTAL_REF_(x)));

//\
TODO: Shim `std::views::repeat` by e.g. \
`std::views::iota(0)|std::views::transform([&] (auto&& _) {return value;})`? \

//\
TODO: Shim `std::views::generate` by e.g. \
`std::views::iota(0)|std::views::transform([&] (auto&& _) {return function();})`? \

////////////////////////////////////////////////////////////////////////////////

template <iteratee_q ...Ys>
struct isomorphic<Ys...>
:	isomeric<iteratee_t<Ys>...>
{};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

XTAL_FZ2 sequential_f(XTAL_DEF z)
XTAL_0EX
{
//	TODO: Apparently both `category::sized` and `views::take` must be applied \
	for `size` to be defined by `ranges::view_interface`, but maybe there's a better way? \

	auto const z_size = z.size();
	using namespace _v3::ranges;
	using  Z = any_view<range_value_t<XTAL_TYP_(z)>, category::forward|category::sized>;
	return Z(XTAL_REF_(z))|_v3::views::take(z_size);
}

template <typename F>
struct zap
{
	class type
	{
		F function_m;

	public:
		XTAL_NEW_(explicit) type(F&&f)
		XTAL_0EX
		:	function_m(XTAL_FWD_(F) (f))
		{
		}
		XTAL_OP2() () &&
		XTAL_0EX
		{
			return _v3::views::generate(_std::move(function_m));
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
using     zap_t = typename zap<F>::type;
XTAL_LET  zap_f = [] (XTAL_DEF f)
XTAL_0FN_(zap_t<decltype(f)>(XTAL_REF_(f)));


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
