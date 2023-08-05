#pragma once
#include "./any.ipp"
#include "./seek.ipp"





XTAL_ENV_(push)
namespace xtal::compound
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class    T  >    using pack_size   = _std::tuple_size<_std::remove_reference_t<T>>;
template <class    T  >    using pack_size_t =   typename pack_size<T>::type;
template <class    T  > XTAL_LET pack_size_v =            pack_size<T> {};
template <class    T  >  concept pack_size_p = constant_p<pack_size_t<T>>;
template <class ...Ts >  concept pack_size_q =   (...and pack_size_p<Ts>);

template <class T, size_t ...Ns >  struct pack_item;
template <class T, size_t... Ns >   using pack_item_t = typename pack_item<T, Ns...>::type;
template <class T, size_t    N  > concept pack_item_p = requires(T a) {{_std::get<N>(a)} -> is_q<pack_item_t<T, N>>;};

template <class T, size_t N, size_t ...Ns>
struct pack_item<T, N, Ns...>
:	pack_item<pack_item_t<T, N>, Ns...>
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
template <class T>
concept pack_items_p = [] <size_t ...N>
	(seek_t<N...>) XTAL_0FN_(true and ... and pack_item_p<T, N>)
	(seek_f<pack_size_v<T>> {})
;
template <class ...Ts >
concept pack_items_q = (true and ... and pack_items_p<Ts>);


static_assert(pack_size_v<_std::tuple<         >> == 0);
static_assert(pack_size_v<_std::array<null_t, 0>> == 0);

static_assert(pack_size_p<_std::tuple<         >>);
static_assert(pack_size_p<_std::array<null_t, 0>>);


////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct pack
{
	using type = _std::tuple<rebased_t<Xs>...>;

	XTAL_LET make = [] XTAL_1FN_(type);

	using    size   = pack_size  <type>;
	using    size_t = pack_size_t<type>;
	XTAL_LET size_v = pack_size_v<type>;
	
	template <size_t N> using part   = pack_item  <type, N>;
	template <size_t N> using part_t = pack_item_t<type, N>;

	template <typename F> using invoke   = _std::invoke_result  <F, rebased_t<Xs>...>;
	template <typename F> using invoke_t = _std::invoke_result_t<F, rebased_t<Xs>...>;

};
template <class ...Xs>
using    pack_t = typename pack<Xs...>::type;
XTAL_LET pack_f = [] <class ...Xs>(Xs &&...xs)
XTAL_0FN_(_std::make_tuple(XTAL_REF_(xs)...));

XTAL_LET pack_fwd = [] <class ...Xs>(Xs &&...xs)
XTAL_0FN_(_std::forward_as_tuple<Xs...>(XTAL_REF_(xs)...));


template <class    T  > concept pack_p = pack_size_p<T> and pack_items_p<T>;
template <class ...Ts > concept pack_q = (...and pack_p<Ts>);

template <class    T  > concept heteropack_p = pack_p<T> and not iterated_q<T>;
template <class    T  > concept   homopack_p = pack_p<T> and     iterated_q<T>;

template <class ...Ts > concept heteropack_q = (...and heteropack_p<Ts>);
template <class ...Ts > concept   homopack_q = (...and   homopack_p<Ts>);


XTAL_CN2 pack_item_f(XTAL_DEF_(pack_p) t)
XTAL_0EX
{
	return XTAL_REF_(t);
}
template <size_t N, size_t ...Ns>
XTAL_CN2 pack_item_f(XTAL_DEF_(pack_p) t)
XTAL_0EX
{
	if constexpr (0 == sizeof...(Ns)) {
		return _std::get<N>(XTAL_REF_(t));
	}
	else {
		return pack_item_f<Ns...>(_std::get<N>(XTAL_REF_(t)));
	}
}
template <constant_q ...Ts>
XTAL_CN2 pack_item_f(XTAL_DEF_(pack_p) t, _std::tuple<Ts...> const &)
XTAL_0EX
{
	return pack_item_f<Ts{}...>(XTAL_REF_(t));
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
