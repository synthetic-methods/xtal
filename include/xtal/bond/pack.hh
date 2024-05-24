#pragma once
#include "./any.hh"
#include "./seek.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

/**/
template <class ...Us>
XTAL_TYP pack
{	using type = _std::tuple<Us...>;
};
template <class ...Us> requires (2 == sizeof...(Us))
XTAL_TYP pack<Us...>
{	using type = _std::pair <Us...>;
};
template <class ...Us>
using pack_t = typename pack<Us...>::type;

XTAL_LET pack_f = []<class ...Us> (Us &&...us)
XTAL_0FN
{	return pack_t<rebased_t<Us>...>(XTAL_REF_(us)...);
};
/*/
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
/***/


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class   ...Ts>	XTAL_USE pack_size_t   =	cardinal_t<(0 +...+ _std::tuple_size<based_t<Ts>>::value)>;
template <class   ...Ts>	XTAL_ASK pack_size_q   =	complete_q<pack_size_t<Ts...>>;
template <class   ...Ts>	XTAL_LET pack_size_n   =	           pack_size_t<Ts...>::value;
template <class   ...Ts>	XTAL_FN2 pack_size_f(Ts &&...) XTAL_0EX {return pack_size_n<Ts...>;}

static_assert(pack_size_n<_std::tuple<         >> == 0);
static_assert(pack_size_n<_std::array<null_t, 0>> == 0);

static_assert(pack_size_q<_std::tuple<         >>);
static_assert(pack_size_q<_std::array<null_t, 0>>);


////////////////////////////////////////////////////////////////////////////////

template <class T,           size_t ...Ns> XTAL_TYP pack_item;
template <class T, size_t N, size_t ...Ns> XTAL_TYP pack_item<T, N, Ns...> : pack_item<_std::tuple_element_t<N, based_t<T>>, Ns...> {};
template <class T, size_t N              > XTAL_TYP pack_item<T, N       > :           _std::tuple_element  <N, based_t<T>>         {};
template <class T                        > XTAL_TYP pack_item<T          > {using type = T;};
template <class T,          size_t... Ns > XTAL_USE pack_item_t = typename pack_item<T, Ns...>::type;

template <size_t ...Ns>
XTAL_FN2 pack_item_f(seek_t<Ns...>, auto &&...ts)
XTAL_0EX
{
	return pack_item_f<Ns...>(XTAL_REF_(ts)...);
}
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
//\
template <class T, size_t ...Ns> XTAL_ASK _pack_item_q = requires(T t) {{pack_item_f<Ns...>(t)} -> is_q<pack_item_t<T, Ns...>>;};
template <class T, size_t    N > XTAL_ASK _pack_item_q = requires(T t) {{get<N>(t)} -> is_q<pack_item_t<T, N>>;};
template <class T              > XTAL_ASK _pack_list_q = [] <size_t ...N>
	(seek_t<N...>) XTAL_0FN_(...and _pack_item_q<T, N>)
	(seek_s<pack_size_n<T>> {})
;
template <class ...Ts >
XTAL_ASK pack_list_q = (...and _pack_list_q<Ts>);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <size_t I,          class  ...Ts>                               XTAL_TYP pack_cell;
template <size_t I, class T, class  ...Ts> requires (I < pack_size_n<T>) XTAL_TYP pack_cell<I, T        , Ts...> {using type = _std::tuple_element_t<I, T>        ;};
template <size_t I, class T, class  ...Ts> requires (I < pack_size_n<T>) XTAL_TYP pack_cell<I, T       &, Ts...> {using type = _std::tuple_element_t<I, T>       &;};
template <size_t I, class T, class  ...Ts> requires (I < pack_size_n<T>) XTAL_TYP pack_cell<I, T const &, Ts...> {using type = _std::tuple_element_t<I, T> const &;};
template <size_t I, class T, class  ...Ts>                               XTAL_TYP pack_cell<I, T, Ts...> : pack_cell<I - pack_size_n<T>, Ts...> {};
template <size_t I,          class  ...Ts>                               XTAL_USE pack_cell_t = typename pack_cell<I, _std::remove_reference_t<Ts>...>::type;

template <class ...Ts>
XTAL_TYP pack_row
{
	template <class     > struct build;
	template <auto ...Is> struct build<bond::seek_t<Is...>>
	{	using type = pack_t<pack_cell_t<Is, Ts...>...>;
	};
	using type = typename build<bond::seek_s<pack_size_n<Ts...>>>::type;

};
template <class ...Ts>
XTAL_USE pack_row_t = typename pack_row<Ts...>::type;
XTAL_LET pack_row_f = []<class ...Ts> (Ts &&...ts)
XTAL_0FN
{
	return [&]<auto ...Is> (bond::seek_t<Is...>)
		XTAL_0FN_(pack_row_t<Ts...>(pack_item_f<Is>(ts...)...))
	(bond::seek_s<pack_size_n<Ts...>>{});
};


////////////////////////////////////////////////////////////////////////////////

template <size_t N, accessed_q W>
XTAL_FN2 pack_zip_f(W &&w, size_t const &n)
XTAL_0EX
{
	using _std::span;
	using _v3::views::zip;

	return [&]<size_t ...Is> (bond::seek_t<Is...>)
		XTAL_0FN_(zip(span(point_f(w[Is]), n)...))
	(bond::seek_s<N>{});
}
template <size_t N, accessed_q W>
XTAL_FN2 pack_zip_f(size_t const &n, W &&w)
XTAL_0EX
{
	return pack_zip_f<N>(XTAL_REF_(w), n);
}
template <size_t N>
XTAL_FN2 pack_zip_f(size_t n)
XTAL_0EX
{
	return [=] (auto &&w) XTAL_0FN_(pack_zip_f<N>(n, XTAL_REF_(w)));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class ...Ts > concept       pack_q = pack_size_q<Ts...> and pack_list_q<Ts...>;
template <class ...Ts > concept   homopack_q = pack_q<Ts...> and     iterable_q<Ts...>;
template <class ...Ts > concept heteropack_q = pack_q<Ts...> and not iterable_q<Ts...>;


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
