#pragma once
#include "./any.hh"
#include "./seek.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ...Us>                               XTAL_TYP pack        {using type = _std::tuple<Us...>;};
template <class ...Us> requires (2 == sizeof...(Us)) XTAL_TYP pack<Us...> {using type = _std::pair <Us...>;};
template <class ...Us> using pack_t = typename pack<Us...>::type;

XTAL_LET pack_f = []<class ...Us> (Us &&...us)
XTAL_0FN
{	return pack_t<rebased_t<Us>...>(XTAL_REF_(us)...);
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class         T >	XTAL_ASK _tuple_size_q   =	complete_q<_std::tuple_size<based_t<T>>>;
template <class         T >	XTAL_ASK     _extent_q   =	complete_q<_std::    extent<based_t<T>>> and 0 < _std::extent_v<based_t<T>>;
template <class         T >	XTAL_TYP  pack_size;
template <_tuple_size_q T >	XTAL_TYP  pack_size<T>  :	_std::tuple_size<based_t<T>> {};
template <    _extent_q T >	XTAL_TYP  pack_size<T>  :	_std::    extent<based_t<T>> {};
template <class      ...Ts>	XTAL_ASK  pack_size_q   =	complete_q<pack_size<Ts>...>;
template <class      ...Ts>	XTAL_LET  pack_size_n   =	(0 +...+ pack_size<Ts>::value);
template <class      ...Ts>	XTAL_USE  pack_size_t   =	cardinal_t<pack_size_n<Ts...>>;

static_assert(pack_size_n<_std::tuple<         >> == 0);
static_assert(pack_size_n<_std::array<null_t, 0>> == 0);

static_assert(pack_size_q<_std::tuple<         >>);
static_assert(pack_size_q<_std::array<null_t, 0>>);

template <class T, size_t N> XTAL_ASK subpack_size_q = N < pack_size_n<T>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <size_t N,         class T> XTAL_TYP pack_item;
template <size_t N, _tuple_size_q T> XTAL_TYP pack_item<N, T        > {using type = _std::tuple_element_t<N, based_t<T>>        ;};
template <size_t N, _tuple_size_q T> XTAL_TYP pack_item<N, T       &> {using type = _std::tuple_element_t<N, based_t<T>>       &;};
template <size_t N, _tuple_size_q T> XTAL_TYP pack_item<N, T const &> {using type = _std::tuple_element_t<N, based_t<T>> const &;};
template <size_t N,     _extent_q T> XTAL_TYP pack_item<N, T        > {using type = _std::           remove_extent_t<T>         ;};
template <size_t N,     _extent_q T> XTAL_TYP pack_item<N, T       &> {using type = _std::           remove_extent_t<T>        &;};
template <size_t N,     _extent_q T> XTAL_TYP pack_item<N, T const &> {using type = _std::           remove_extent_t<T>  const &;};
template <size_t N, class T> XTAL_USE pack_item_t = typename pack_item<N, T>::type;

template <size_t N, class T> XTAL_ASK pack_item_p = N < pack_size_n<T> and requires(T t) {{get<N>(t)} -> as_q<pack_item_t<N, T>>;};
template <          class T> XTAL_ASK pack_list_q = [] <size_t ...Ns>
	(seek_t<Ns...>) XTAL_0FN_(...and pack_item_p<Ns, T>)
	(seek_s<pack_size_n<T>> {})
;

template <size_t ...Ns> requires none_n<Ns...>
XTAL_FN2 pack_item_f(auto &&t)
XTAL_0EX
{
	return XTAL_REF_(t);
}
template <size_t N, size_t ...Ns>
XTAL_FN2 pack_item_f(auto &&t, auto &&...ts)
XTAL_0EX
{
	XTAL_VAL N_t = pack_size_n<decltype(t)>;
	XTAL_IF0
	XTAL_0IF_(N <  N_t) {return pack_item_f<         Ns...>(get<N>(XTAL_REF_(t)));}
	XTAL_0IF_(N >= N_t) {return pack_item_f<N - N_t, Ns...>(XTAL_REF_(ts)...);}
}
template <size_t ...Ns>
XTAL_FN2 pack_item_f(seek_t<Ns...>, auto &&...ts)
XTAL_0EX
{
	return pack_item_f<Ns...>(XTAL_REF_(ts)...);
}


////////////////////////////////////////////////////////////////////////////////

template <size_t I,                      class  ...Ts> XTAL_TYP interpack_item;
template <size_t I,             class T, class  ...Ts> XTAL_TYP interpack_item<I, T, Ts...> : interpack_item<I - pack_size_n<T>, Ts...> {};
template <size_t I, subpack_size_q<I> T, class  ...Ts> XTAL_TYP interpack_item<I, T, Ts...> :      pack_item<I, T>                      {};
template <size_t I,                      class  ...Ts> XTAL_USE interpack_item_t = typename interpack_item<I, Ts...>::type;

template <class T,                       size_t ...Ns> XTAL_TYP intrapack_item;
template <class T,             size_t N, size_t ...Ns> XTAL_TYP intrapack_item<T, N, Ns...> : intrapack_item<pack_item_t<N, T>, Ns...> {};
template <class T,             size_t N              > XTAL_TYP intrapack_item<T, N       > :                pack_item  <N, T>         {};
template <class T                                    > XTAL_TYP intrapack_item<T          > {using type = T;};
template <class T,                      size_t... Ns > XTAL_USE intrapack_item_t = typename intrapack_item<T, Ns...>::type;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <pack_size_q ...Ts> XTAL_TYP pack_row;
template <pack_size_q ...Ts> XTAL_USE pack_row_t = typename pack_row<Ts...>::type;
template <pack_size_q ...Ts> XTAL_TYP pack_row
{
	template <class     > struct sequence;
	template <auto ...Is> struct sequence<bond::seek_t<Is...>>
	{	using type = pack_t<interpack_item_t<Is, Ts...>...>;
	};
	using type = typename sequence<bond::seek_s<pack_size_n<Ts...>>>::type;

};
XTAL_LET pack_row_f = []<class ...Ts> (Ts &&...ts)
XTAL_0FN
{
	return [&]<auto ...Is> (bond::seek_t<Is...>)
		XTAL_0FN_(pack_row_t<Ts...>(pack_item_f<Is>(ts...)...))
	(bond::seek_s<pack_size_n<Ts...>>{});
};

template <size_t N, accessed_q W>
XTAL_FN2 pack_table_f(W &&w, size_t const &n)
XTAL_0EX
{
	using _std::span;
	using _xtd::ranges::views::zip;

	return [&]<size_t ...Is> (bond::seek_t<Is...>)
		XTAL_0FN_(zip(span(point_f(w[Is]), n)...))
	(bond::seek_s<N>{});
}
template <size_t N, accessed_q W>
XTAL_FN2 pack_table_f(size_t const &n, W &&w)
XTAL_0EX
{
	return pack_table_f<N>(XTAL_REF_(w), n);
}
template <size_t N>
XTAL_FN2 pack_table_f(size_t n)
XTAL_0EX
{
	return [=] (auto &&w) XTAL_0FN_(pack_table_f<N>(n, XTAL_REF_(w)));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class ...Ts> concept       pack_q = pack_size_q<Ts...> and (...and pack_list_q<Ts>);
template <class ...Ts> concept   homopack_q = pack_q<Ts...> and     iterable_q<Ts...>;
template <class ...Ts> concept heteropack_q = pack_q<Ts...> and not iterable_q<Ts...>;


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
