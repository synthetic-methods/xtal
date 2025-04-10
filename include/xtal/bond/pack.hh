#pragma once
#include "./any.hh"
#include "./seek.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <         class ...Ts>	struct         pack_size;
template <fixed_shaped_q    T >	struct         pack_size<T> : cardinal_constant_t<fixed_shaped<T>::extent()> {};
template <         class ...Ts>	auto constexpr pack_size_n = pack_size<based_t<Ts>...>{}();
template <         class ...Ts>	concept        pack_size_q = complete_q<pack_size<based_t<Ts>>...>;

template <class T, class ...Ts>	requires some_q<Ts...> and pack_size_q<T, Ts...>
struct pack_size<T, Ts...>
:	cardinal_constant_t<(pack_size_n<T> +...+ pack_size_n<Ts>)>
{
};
template <         class ...Ts>
XTAL_DEF_(return,inline,let)
pack_size_f(Ts &&...)
noexcept -> decltype(auto)
{
	return pack_size_n<Ts...>;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*!
\brief  	Determines the element-type indexed by `Is...` nested within `T`.
*/
template <class T, size_type ...Is> struct   pack_item;
template <class T, size_type ...Is> using    pack_item_t = typename pack_item<T, Is...>::     type;
template <class T, size_type ...Is> using    pack_item_s = typename pack_item<T, Is...>::supertype;
template <class T                 >	struct   pack_item<T>    {using supertype = T; using type = T;};

template <class T, size_type I, size_type ...Is>
struct   pack_item<T, I, Is...> : pack_item<pack_item_t<T, I>, Is...> {};

template <fixed_valued_q T, size_type I> requires un_n<tuple_shaped_q<T>> struct pack_item<T        , I> {using supertype = T; using type =                   fixed_valued_u<T>         ;};
template <tuple_shaped_q T, size_type I>                                  struct pack_item<T        , I> {using supertype = T; using type = _std::tuple_element_t<I, based_t<T>>        ;};
template <tuple_shaped_q T, size_type I>                                  struct pack_item<T       &, I> {using supertype = T; using type = _std::tuple_element_t<I, based_t<T>>       &;};
template <tuple_shaped_q T, size_type I>                                  struct pack_item<T const &, I> {using supertype = T; using type = _std::tuple_element_t<I, based_t<T>> const &;};

/*!
\brief  	Determines the element-value indexed by `Is...` nested within and across the concatenated `t, ts...`.
*/
XTAL_DEF_(return,inline,let)
pack_item_f(auto &&t)
noexcept -> decltype(auto)
{
	return XTAL_REF_(t);
}
template <auto I>
XTAL_DEF_(return,inline,let)
pack_item_f(auto &&t)
noexcept -> decltype(auto)
{
	auto constexpr N = pack_size_n<decltype(t)>;
	auto constexpr K = modulo_v<N, I>;
	XTAL_IF0
	XTAL_0IF_(to) (get<K>(XTAL_REF_(t)))
	XTAL_0IF_(else) return destruct_f(XTAL_REF_(t))[K];
}
template <auto I, auto ...Is>// requires some_n<Is...>
XTAL_DEF_(return,inline,let)
pack_item_f(auto &&t, auto &&...ts)
noexcept -> decltype(auto)
{
	auto constexpr N = pack_size_n<decltype(t)>;
	XTAL_IF0
	XTAL_0IF (I >= N) {
		return pack_item_f<I - N, Is...>(XTAL_REF_(ts)...);
	}
	XTAL_0IF (I <  N) {
		return pack_item_f<Is...>(pack_item_f<I>(XTAL_REF_(t)));
	}
}
template <auto ...Is>
XTAL_DEF_(return,inline,let)
pack_item_f(seek_t<Is...>, auto &&...ts)
noexcept -> decltype(auto)
{
	return pack_item_f<Is...>(XTAL_REF_(ts)...);
}


template <class T, size_type ...Is>
concept  pack_item_q = requires(T t) {{pack_item_f<Is...>(t)} -> make_q<pack_item_t<T, Is...>>;};

template <class T>
concept  pack_list_q = 0 == pack_size_n<T> or
	[] <auto ...Is> (seek_t<Is...>) XTAL_0FN_(to) (...and pack_item_q<T, Is>) (seek_s<pack_size_n<T>> {});


////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Determines the element-type indexed by `I` across the concatenation of tuples `...Ts`.
*/
template <auto I,          class  ...Ts>                              struct   interpack_item;
template <auto I, class T, class  ...Ts>                              struct   interpack_item<I, T, Ts...> : interpack_item<I - pack_size_n<T>, Ts...> {};
template <auto I, class T, class  ...Ts> requires(I < pack_size_n<T>) struct   interpack_item<I, T, Ts...> :      pack_item<T, I>                      {};
template <auto I,          class  ...Ts>                              using    interpack_item_t = typename interpack_item<I, Ts...>::type;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class        ...Us> struct   pack         {using type = _std::tuple<pack_item_t<Us>...>;};
template <class U0, class U1> struct   pack<U0, U1> {using type = _std::pair <pack_item_t<U0>, pack_item_t<U1>>;};
template <class        ...Us> using    pack_t   = typename pack<Us...>::type;

/*!
\returns
A reference-preserving tuple with elements `_s...`.
*/
XTAL_DEF_(let) pack_f = []<class ...Us> (Us &&...us)
XTAL_0FN_(to) (pack_t<Us...>(static_cast<Us &&> (us)...));

/*!
\returns
A tuple with length `N`,
generated by the function `f` applied to each index.
*/
template <int N>
XTAL_DEF_(let)
pack_out_f = [] (auto const &f)
	XTAL_0FN_(to) ([&] <int ...I>(seek_t<I...>)
		XTAL_0FN_(to) (pack_f(f(constant_t<I>{})...))
			(seek_s<N>{}));


////////////////////////////////////////////////////////////////////////////////

template <pack_size_q ...Ts>
struct   repack
{
	template <auto  ...Is>
	XTAL_DEF_(return,inline,set)
	make(seek_t<Is...>) -> pack_t<interpack_item_t<Is, Ts...>...>;

	using type = decltype(make(seek_s<pack_size_n<Ts...>>()));

};
template <pack_size_q ...Ts>
using    repack_t = typename repack<Ts...>::type;

template <class ...Ts>
concept  repack_q = same_q<repack_t<Ts>...>;

template <template <class ...> class F=pack_t>
XTAL_DEF_(return,inline,let)
repack_f(pack_size_q auto &&...ts)
noexcept -> decltype(auto)
{
	return [&]<auto ...Is> (bond::seek_t<Is...>)
		XTAL_0FN_(to) (F<interpack_item_t<Is, decltype(ts)...>...>{pack_item_f<Is>(ts...)...})
	(bond::seek_s<pack_size_n<decltype(ts)...>>{});
};


////////////////////////////////////////////////////////////////////////////////

template <class U>
XTAL_DEF_(return,inline,let)
transpack_f(size_type i, size_type m, indexed_q auto &&w)
noexcept -> auto
{
	if constexpr (same_q<decltype(**w), U>) {
		return _std::span(point_f(XTAL_REF_(w)[i]), m);
	}
	else {
		return [&]<auto ...Is> (bond::seek_t<Is...>)
			XTAL_0FN_(to) (iterative_f<U>(_std::span(point_f(XTAL_REF_(w)[Is], i), m)...))
			(bond::seek_s<fluid_shaped<U>::extent()>{});
	}
}
template <class U>
XTAL_DEF_(return,inline,let)
transpack_f(size_type m, indexed_q auto &&w)
noexcept -> decltype(auto)
{
	return transpack_f<U>(0U, m, XTAL_REF_(w));
}
template <class U>
XTAL_DEF_(return,inline,let)
transpack_f(integral_q auto const &...ns)
noexcept -> decltype(auto)
{
	return [=] (auto &&w) XTAL_0FN_(to) (transpack_f<U>(ns..., XTAL_REF_(w)));
}
template <class U>
using    transpack_t = XTAL_ALL_(transpack_f<U>(0x1000U, XTAL_ANY_(initializer_t<U> **)));


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class ...Ts> concept   pack_q = pack_size_q<Ts...> and (...and          pack_list_q<Ts>);
template <class ...Ts> concept tupack_q = pack_q     <Ts...> and (...and same_q<repack_t<Ts>, Ts>);


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
