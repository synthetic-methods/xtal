#pragma once
#include "./any.hh"
#include "./seek.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class        ...Us> struct   pack         {using type = _std::tuple<Us...>;};
template <class U0, class U1> struct   pack<U0, U1> {using type = _std::pair<U0, U1>;};
template <class        ...Us> using    pack_t = typename pack<Us...>::type;

XTAL_DEF_(inline)
XTAL_LET pack_f(auto &&...us)
noexcept -> auto
{
	return pack_t<valve_t<decltype(us)>...>(XTAL_REF_(us)...);
};
template <auto I>
XTAL_DEF_(inline)
XTAL_LET pack_f(auto &&f)
noexcept -> auto
{
	return [f = XTAL_REF_(f)]<auto ...K> (seek_t<K...>)
		XTAL_0FN_(pack_f(f(constant_t<K>{})...))
	(bond::seek_s<I>{});
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <         class ...Ts>	struct   pack_size;
template <sized_q T           >	struct   pack_size<T> : sized_t<T> {};
template <         class ...Ts>	XTAL_LET pack_size_n = pack_size<based_t<Ts>...>::value;
template <         class ...Ts>	concept  pack_size_q = complete_q<pack_size<based_t<Ts>>...>;

template <class T, class ...Ts>	requires some_q<Ts...> and pack_size_q<T, Ts...>
struct pack_size<T, Ts...> : constant_t<(pack_size_n<T> +...+ pack_size_n<Ts>)> {};


static_assert(pack_size_n<_std::tuple<            >> == 0);
static_assert(pack_size_n<_std::array<null_type, 0>> == 0);

static_assert(pack_size_q<_std::tuple<            >>);
static_assert(pack_size_q<_std::array<null_type, 0>>);

template <class T, auto I> concept     pack_sized_q = I == pack_size_n<T>;
template <class T, auto I> concept  subpack_sized_q = I <  pack_size_n<T>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//\brief\
Determines the element-type indexed by `Is...` nested within `T`. \

template <class T, size_type ...Is> struct   pack_item;
template <class T, size_type... Is> using    pack_item_t = typename pack_item<T, Is...>::type;

template <class T>
struct   pack_item<T> {using type = T;};

template <class T, size_type I, size_type ...Is>
struct   pack_item<T, I, Is...> : pack_item<pack_item_t<T, I>, Is...> {};

template <     valued_q T, size_type I> requires un_n<tuple_sized_q<T>> struct pack_item<T, I> {using type = valued_u<T>;};
template <tuple_sized_q T, size_type I>                                 struct pack_item<T        , I> {using type = _std::tuple_element_t<I, based_t<T>>        ;};
template <tuple_sized_q T, size_type I>                                 struct pack_item<T       &, I> {using type = _std::tuple_element_t<I, based_t<T>>       &;};
template <tuple_sized_q T, size_type I>                                 struct pack_item<T const &, I> {using type = _std::tuple_element_t<I, based_t<T>> const &;};

template <class T, size_type ...Is>
using    pack_item_t = typename pack_item<T, Is...>::type;

//\brief\
Determines the element-value indexed by `Is...` nested within and across the concatenated `t, ts...`. \

XTAL_DEF_(return,inline)
XTAL_LET pack_item_f(auto &&t)
noexcept -> decltype(auto)
{
	return XTAL_REF_(t);
}
template <auto I>
XTAL_DEF_(return,inline)
XTAL_LET pack_item_f(auto &&t)
noexcept -> decltype(auto)
{
	XTAL_IF0
	XTAL_0IF XTAL_TRY_TO_(get<I>(XTAL_REF_(t)))
	XTAL_0IF_(else) return part_f(XTAL_REF_(t))[I];
}
template <auto I, auto ...Is> requires some_n<Is...>
XTAL_DEF_(return,inline)
XTAL_LET pack_item_f(auto &&t, auto &&...ts)
noexcept -> decltype(auto)
{
	XTAL_LET N = pack_size_n<decltype(t)>;
	XTAL_IF0
	XTAL_0IF (I >= N) {
		return pack_item_f<I - N, Is...>(XTAL_REF_(ts)...);
	}
	XTAL_0IF (I <  N) {
		return pack_item_f<Is...>(pack_item_f<I>(XTAL_REF_(t)));
	}
}
template <auto ...Is>
XTAL_DEF_(return,inline)
XTAL_LET pack_item_f(seek_t<Is...>, auto &&...ts)
noexcept -> decltype(auto)
{
	return pack_item_f<Is...>(XTAL_REF_(ts)...);
}


template <class T, size_type I>
concept  pack_item_p = I <  pack_size_n<T> and requires(T t) {{get<I>(t)} -> as_q<pack_item_t<T, I>>;};

template <class T>
concept  pack_list_q = 0 == pack_size_n<T> or [] <auto ...Is>
	(seek_t<Is...>) XTAL_0FN_(...and pack_item_p<T, Is>)
	(seek_s<pack_size_n<T>> {})
;



////////////////////////////////////////////////////////////////////////////////

//\
Determines the element-type indexed by `I` across the concatenation of tuples `...Ts`. \

template <auto I,                       class  ...Ts> struct   interpack_item;
template <auto I,              class T, class  ...Ts> struct   interpack_item<I, T, Ts...> : interpack_item<I - pack_size_n<T>, Ts...> {};
template <auto I, subpack_sized_q<I> T, class  ...Ts> struct   interpack_item<I, T, Ts...> :      pack_item<T, I>                      {};
template <auto I,                       class  ...Ts> using    interpack_item_t = typename interpack_item<I, Ts...>::type;



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <pack_size_q ...Ts>
struct   repack
{
	template <auto  ...Is>
	XTAL_DEF_(static)
	XTAL_LET make(seek_t<Is...>) -> pack_t<interpack_item_t<Is, Ts...>...>;

	using type = decltype(make(seek_s<pack_size_n<Ts...>>()));

};
template <pack_size_q ...Ts>
using    repack_t = typename repack<Ts...>::type;


template <template <class ...> class F=pack_t>
XTAL_DEF_(inline)
XTAL_LET repack_f(pack_size_q auto &&...ts)
noexcept -> decltype(auto)
{
	return [&]<auto ...Is> (bond::seek_t<Is...>)
		XTAL_0FN_(F<interpack_item_t<Is, decltype(ts)...>...>{pack_item_f<Is>(ts...)...})
	(bond::seek_s<pack_size_n<decltype(ts)...>>{});
};
template <template <class ...> class F=pack_t>
using    repack_y = XTAL_FUN_(repack_f<F>);


template <auto I, class U=void>
XTAL_DEF_(return,inline)
XTAL_LET pack_rowwise_f(auto const &m, auto const &i, indexed_q auto &&w)
noexcept -> auto
{
	using _std::span;
	using _std::next;

	if constexpr (is_q<U, decltype(**w)>) {
		return span(next(*w, i), m);
	}
	else {
		return [&]<auto ...Is> (bond::seek_t<Is...>)
		XTAL_0FN {
			if constexpr (void_q<U>) {
				return _xtd::ranges::views::zip(span(next(point_f(w[Is]), i), m)...);
			}
			else {
				return iterative_f<U>(span(next(point_f(w[Is]), i), m)...);
			}
		}
		(bond::seek_s<I>{});
	}
}
template <auto I, class U=void>
XTAL_DEF_(return,inline)
XTAL_LET pack_rowwise_f(auto const &m, indexed_q auto &&w)
noexcept -> decltype(auto)
{
	return pack_rowwise_f<I, U>(XTAL_REF_(m), size_0, XTAL_REF_(w));
}
template <auto I, class U=void>
XTAL_DEF_(return,inline)
XTAL_LET pack_rowwise_f(integer_q auto ...ns)
noexcept -> decltype(auto)
{
	return [=] (auto &&w) XTAL_0FN_(pack_rowwise_f<I, U>(ns..., XTAL_REF_(w)));
}
template <auto I, class U>
using    pack_rowwise_t = XTAL_ALL_(pack_rowwise_f<I, U>(0x1000, XTAL_ANY_(initializer_u<U> **)));

template <class U> XTAL_LET repack_rowwise_f = [] XTAL_1FN_(  pack_rowwise_f<devalued_n<U>, U>);
template <class U> using    repack_rowwise_t =    XTAL_ALL_(repack_rowwise_f<U>(0x1000, XTAL_ANY_(initializer_u<U> **)));


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class ...Ts> concept       pack_q = pack_size_q<Ts...> and (...and pack_list_q<Ts>);
template <class ...Ts> concept     dipack_q = pack_q<Ts...> and (...and (2 == pack_size_n<Ts>));
template <class ...Ts> concept   idiopack_q = (...and is_q<Ts, repack_t<Ts>>);
template <class ...Ts> concept   homopack_q = pack_q<Ts...> and      iterable_q<Ts...>  and idiopack_q<Ts...>;
template <class ...Ts> concept heteropack_q = pack_q<Ts...> and un_n<iterable_q<Ts...>> and idiopack_q<Ts...>;


////////////////////////////////////////////////////////////////////////////////

template <pack_q X, pack_q Y>
XTAL_DEF_(return,inline)
XTAL_LET pack_dot_f(X const &x, Y const &y)
{
	XTAL_LET M = pack_size_n<X>;
	XTAL_LET I = pack_size_n<Y>;
	static_assert(M == I);
	return [&]<auto ...I>(bond::seek_t<I...>)
		XTAL_0FN_((get<0>(x)*get<0>(y)) +...+ (get<1 + I>(x)*get<1 + I>(y)))
	(bond::seek_s<I - 1> {});
}


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
