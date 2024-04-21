#pragma once
#include "./any.hh"
#include "./tag.hh"
#include "./seek.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

XTAL_LET pack_f = [] (auto &&...xs)
XTAL_0FN
{
	if constexpr (2 == sizeof...(xs)) {
		return _std::make_pair (XTAL_REF_(xs)...);
	}
	else {
		return _std::make_tuple(XTAL_REF_(xs)...);
	}
};
template <class ...Xs>
using pack_t = _std::invoke_result_t<decltype(pack_f), Xs...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class    T  > using    pack_size   = _std::tuple_size<_std::remove_reference_t<T>>;
template <class    T  > using    pack_size_t =   typename pack_size<T>::type;
template <class    T  > XTAL_LET pack_size_n =            pack_size<T> {};
template <class    T  > concept  pack_size_p = integral_q<pack_size_t<T>>;
template <class ...Ts > concept  pack_size_q =    (...and pack_size_p<Ts>);

static_assert(pack_size_n<_std::tuple<         >> == 0);
static_assert(pack_size_n<_std::array<null_t, 0>> == 0);

static_assert(pack_size_q<_std::tuple<         >>);
static_assert(pack_size_q<_std::array<null_t, 0>>);


////////////////////////////////////////////////////////////////////////////////

template <class T, size_t ...Ns > struct  pack_item;
template <class T, size_t... Ns > using   pack_item_t = typename pack_item<T, Ns...>::type;
template <class T, size_t    N  > concept pack_item_p = requires(T a) {{get<N>(a)} -> is_q<pack_item_t<T, N>>;};
template <class T>
concept pack_items_p = [] <size_t ...N>
	(seek_t<N...>) XTAL_0FN_(true and ... and pack_item_p<T, N>)
	(seek_f<pack_size_n<T>> {})
;
template <class ...Ts >
concept pack_items_q = (true and ... and pack_items_p<Ts>);


template <class T, size_t N, size_t ...Ns>
struct pack_item<T, N, Ns...>
:	pack_item<_std::tuple_element_t<N, _std::remove_reference_t<T>>, Ns...>
{
};
template <class T, size_t N>
struct pack_item<T, N>
:	_std::tuple_element<N, _std::remove_reference_t<T>>
{
};
template <class T>
struct pack_item<T>
{
	using type = T;

};
XTAL_FN2 pack_item_f(auto &&t)
XTAL_0EX
{
	return XTAL_REF_(t);
}
template <size_t N, size_t ...Ns>
XTAL_FN2 pack_item_f(auto &&t)
XTAL_0EX
{
	if constexpr (0 == sizeof...(Ns)) {
		return get<N>(XTAL_REF_(t));
	}
	else {
		return pack_item_f<Ns...>(get<N>(XTAL_REF_(t)));
	}
}
template <template <class ...> class L, integral_q ...Ts>
XTAL_FN2 pack_item_f(auto &&t, L<Ts...> const &)
XTAL_0EX
{
	return pack_item_f<Ts{}...>(XTAL_REF_(t));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct pack
{
	template <typename F>
	using invoke = _std::invoke_result<F, Xs...>;

	XTAL_LET make = pack_f;
	XTAL_USE type = pack_t<Xs...>;
	XTAL_USE size = pack_size<type>;

};
template <template <class ...> class Y, class ...Xs>
struct pack<Y<Xs...>> : pack<Xs...> {};


template <class ...Ts > concept       pack_q = pack_size_q<Ts...> and   pack_items_q<Ts...>;
template <class ...Ts > concept   homopack_q =      pack_q<Ts...> and     iterated_q<Ts...>;
template <class ...Ts > concept heteropack_q =      pack_q<Ts...> and not iterated_q<Ts...>;


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
