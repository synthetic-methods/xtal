#pragma once
#include "./any.hh"
#include "./seek.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class        ...Us> XTAL_TYP pack         {using type = _std::tuple<Us...>;};
template <class U0, class U1> XTAL_TYP pack<U0, U1> {using type = _std::pair<U0, U1>;};
template <class        ...Us> XTAL_USE pack_t = typename pack<Us...>::type;

XTAL_DEF_(inline)
XTAL_LET pack_f(auto &&...us)
XTAL_0EX
{
	return pack_t<_xtd::decay_rconst_t<decltype(us)>...>(XTAL_REF_(us)...);
};
template <size_type N>
XTAL_DEF_(inline)
XTAL_LET pack_f(auto &&f)
XTAL_0EX
{
	return [f = XTAL_REF_(f)]<auto ...I> (seek_t<I...>)
		XTAL_0FN_(pack_f(f(nominal_t<I>{})...))
	(bond::seek_s<N>{});
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class         T >	XTAL_REQ     _extent_q   =	complete_q<_std::    extent<based_t<T>>> and 0 < _std::extent_v<based_t<T>>;
template <class         T >	XTAL_REQ _tuple_size_q   =	complete_q<_std::tuple_size<based_t<T>>>;
template <class         T >	XTAL_TYP   pack_size;
template <class         U >	XTAL_TYP   pack_size<_std::complex<U>>  :	nominal_t<size_2> {};
template <    _extent_q T >	XTAL_TYP   pack_size<T>                 :	      _std::    extent<based_t<T>> {};
template <_tuple_size_q T >	XTAL_TYP   pack_size<T>                 :	      _std::tuple_size<based_t<T>> {};
template <class      ...Ts>	XTAL_LET   pack_size_n                  =	    (0 +...+ pack_size<based_t<Ts>>::value);
template <class      ...Ts>	XTAL_REQ   pack_size_q                  =	  complete_q<pack_size<based_t<Ts>>...>;
template <class      ...Ts>	XTAL_USE   pack_size_t                  =	 nominal_t<pack_size_n<based_t<Ts>...>>;

static_assert(pack_size_n<_std::tuple<            >> == 0);
static_assert(pack_size_n<_std::array<null_type, 0>> == 0);

static_assert(pack_size_q<_std::tuple<            >>);
static_assert(pack_size_q<_std::array<null_type, 0>>);

template <class T, size_type N> XTAL_REQ    pack_sized_q = N == pack_size_n<T>;
template <class T, size_type N> XTAL_REQ subpack_sized_q = N <  pack_size_n<T>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <size_type N,         class T> XTAL_TYP pack_item;
template <size_type N,         class U> XTAL_TYP pack_item<N, _std::complex<U> const &&> {using type = U const   ;};//&&
template <size_type N,         class U> XTAL_TYP pack_item<N, _std::complex<U> const  &> {using type = U const  &;};
template <size_type N,         class U> XTAL_TYP pack_item<N, _std::complex<U>       &&> {using type = U         ;};//&&
template <size_type N,         class U> XTAL_TYP pack_item<N, _std::complex<U>        &> {using type = U        &;};
template <size_type N, _tuple_size_q T> XTAL_TYP pack_item<N, T        > {using type = _std::tuple_element_t<N, based_t<T>>        ;};
template <size_type N, _tuple_size_q T> XTAL_TYP pack_item<N, T       &> {using type = _std::tuple_element_t<N, based_t<T>>       &;};
template <size_type N, _tuple_size_q T> XTAL_TYP pack_item<N, T const &> {using type = _std::tuple_element_t<N, based_t<T>> const &;};
template <size_type N,     _extent_q T> XTAL_TYP pack_item<N, T        > {using type = _std::           remove_extent_t<T>         ;};
template <size_type N,     _extent_q T> XTAL_TYP pack_item<N, T       &> {using type = _std::           remove_extent_t<T>        &;};
template <size_type N,     _extent_q T> XTAL_TYP pack_item<N, T const &> {using type = _std::           remove_extent_t<T>  const &;};
template <size_type N, class T> XTAL_USE pack_item_t = typename pack_item<N, T>::type;

template <size_type N, class T> XTAL_REQ pack_item_p = N <  pack_size_n<T> and requires(T t) {{get<N>(t)} -> as_q<pack_item_t<N, T>>;};
template <             class T> XTAL_REQ pack_list_q = 0 == pack_size_n<T> or [] <size_type ...Ns>
	(seek_t<Ns...>) XTAL_0FN_(...and pack_item_p<Ns, T>)
	(seek_s<pack_size_n<T>> {})
;

XTAL_DEF_(return,inline)
XTAL_LET pack_item_f(auto &&t)
XTAL_0EX -> decltype(auto)
{
	return XTAL_REF_(t);
}
template <size_type N>
XTAL_DEF_(return,inline)
XTAL_LET pack_item_f(auto &&t)
XTAL_0EX -> decltype(auto)
{
	/*/
	return get<N>(XTAL_REF_(t));
	/*/
	if constexpr (complex_field_q<decltype(t)>) {
		return involved_f(XTAL_REF_(t))[N];
	}
	else {
		return get<N>(XTAL_REF_(t));
	}
	/***/
}
template <size_type N, size_type ...Ns> requires some_n<Ns...>
XTAL_DEF_(return,inline)
XTAL_LET pack_item_f(auto &&t, auto &&...ts)
XTAL_0EX -> decltype(auto)
{
	XTAL_LET N_t = pack_size_n<decltype(t)>;
	XTAL_IF0
	XTAL_0IF (N >= N_t) {
		return pack_item_f<N - N_t, Ns...>(XTAL_REF_(ts)...);
	}
	XTAL_0IF (N <  N_t) {
		return pack_item_f<Ns...>(pack_item_f<N>(XTAL_REF_(t)));
	}
}
template <size_type ...Ns>
XTAL_DEF_(return,inline)
XTAL_LET pack_item_f(seek_t<Ns...>, auto &&...ts)
XTAL_0EX -> decltype(auto)
{
	return pack_item_f<Ns...>(XTAL_REF_(ts)...);
}


////////////////////////////////////////////////////////////////////////////////

template <size_type I,                       class  ...Ts> XTAL_TYP interpack_item;
template <size_type I,              class T, class  ...Ts> XTAL_TYP interpack_item<I, T, Ts...> : interpack_item<I - pack_size_n<T>, Ts...> {};
template <size_type I, subpack_sized_q<I> T, class  ...Ts> XTAL_TYP interpack_item<I, T, Ts...> :      pack_item<I, T>                      {};
template <size_type I,                       class  ...Ts> XTAL_USE interpack_item_t = typename interpack_item<I, Ts...>::type;

template <class T,                        size_type ...Ns> XTAL_TYP intrapack_item;
template <class T,           size_type N, size_type ...Ns> XTAL_TYP intrapack_item<T, N, Ns...> : intrapack_item<pack_item_t<N, T>, Ns...> {};
template <class T,           size_type N                 > XTAL_TYP intrapack_item<T, N       > :                pack_item  <N, T>         {};
template <class T                                        > XTAL_TYP intrapack_item<T          > {using type = T;};
template <class T,                       size_type... Ns > XTAL_USE intrapack_item_t = typename intrapack_item<T, Ns...>::type;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <pack_size_q ...Ts>
XTAL_TYP repack
{
	template <size_type  ...Ns>
	XTAL_DEF_(static)
	XTAL_LET make(seek_t<Ns...>) -> pack_t<interpack_item_t<Ns, Ts...>...>;

	using type = decltype(make(seek_s<pack_size_n<Ts...>>()));

};
template <pack_size_q ...Ts>
XTAL_USE repack_t = typename repack<Ts...>::type;


template <template <class ...> class F=pack_t>
XTAL_DEF_(inline)
XTAL_LET repack_f(auto &&...ts)
XTAL_0EX
{
	return [&]<auto ...Ns> (bond::seek_t<Ns...>)
		XTAL_0FN_(F<interpack_item_t<Ns, decltype(ts)...>...>{pack_item_f<Ns>(ts...)...})
	(bond::seek_s<pack_size_n<decltype(ts)...>>{});
};
template <template <class ...> class F=pack_t>
XTAL_USE repack_y = decltype([] XTAL_1FN_(repack_f<F>));


template <size_type N, class U=void>
XTAL_DEF_(return,inline)
XTAL_LET pack_rowwise_f(size_type const &m, accessed_q auto &&w)
XTAL_0EX
{
	using _std::span;
	using _xtd::ranges::views::zip;

	return [&]<size_type ...Ns> (bond::seek_t<Ns...>)
	XTAL_0FN {
		if constexpr (void_q<U>) {
			return zip(span(point_f(w[Ns]), m)...);
		}
		else {
			return iterative_f<U>(span(point_f(w[Ns]), m)...);
		}
	}
	(bond::seek_s<N>{});
}
template <size_type N, class U=void>
XTAL_DEF_(return,inline)
XTAL_LET pack_rowwise_f(size_type n)
XTAL_0EX
{
	return [=] (auto &&w) XTAL_0FN_(pack_rowwise_f<N, U>(n, XTAL_REF_(w)));
}
template <size_type N, class U>
XTAL_USE pack_rowwise_t = XTAL_ALL_(pack_rowwise_f<N, U>(0x1000, XTAL_ANY_(debraced_t<U> **)));

template <class U> XTAL_LET repack_rowwise_f = [] XTAL_1FN_(  pack_rowwise_f<devalued_n<U>, U>);
template <class U> XTAL_USE repack_rowwise_t =    XTAL_ALL_(repack_rowwise_f<U>(0x1000, XTAL_ANY_(debraced_t<U> **)));


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class ...Ts> concept       pack_q = pack_size_q<Ts...> and (...and pack_list_q<Ts>);
template <class ...Ts> concept     dipack_q = pack_q<Ts...> and (...and (2 == pack_size_n<Ts>));
template <class ...Ts> concept   idiopack_q = (...and is_q<Ts, repack_t<Ts>>);
template <class ...Ts> concept   homopack_q = pack_q<Ts...> and     iterable_q<Ts...> and idiopack_q<Ts...>;
template <class ...Ts> concept heteropack_q = pack_q<Ts...> and not iterable_q<Ts...> and idiopack_q<Ts...>;


////////////////////////////////////////////////////////////////////////////////

template <pack_q X, pack_q Y>
XTAL_DEF_(return,inline)
XTAL_LET pack_dot_f(X const &x, Y const &y)
{
	XTAL_LET M = pack_size_n<X>;
	XTAL_LET N = pack_size_n<Y>;
	static_assert(M == N);
	return [&]<size_type ...I>(bond::seek_t<I...>)
		XTAL_0FN_((get<0>(x)*get<0>(y)) +...+ (get<1 + I>(x)*get<1 + I>(y)))
	(bond::seek_s<N - 1> {});
}


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
