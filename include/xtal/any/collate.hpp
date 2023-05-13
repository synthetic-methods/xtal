#pragma once
#include "./any.hpp"
#include "./collect.hpp"// next





XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename... Xs>
struct collate
:	collect<Xs...>
{};

template <typename... Xs>
XTAL_IF1 is_q<Xs...>
struct collate<Xs...>
{
	using type = _std::array<_std::common_type_t<Xs...>, sizeof...(Xs)>;
};
template <typename... Xs>
using     collate_t = typename collate<Xs...>::type;
XTAL_LET  collate_f = [] <typename... Xs> (Xs&&... xs)
XTAL_0FN_(collate_t<Xs...>(XTAL_FWD_(Xs) (xs)...));

template <typename T, auto N> using   collatee   = _std::tuple_element<N, _std::remove_reference_t<T>>;
template <typename T, auto N> using   collatee_t = typename collatee<T, N>::type;
template <typename T, auto N> concept collatee_b = requires(T a) {{_std::get<N>(a)} -> is_q<collatee_t<T, N>>;};

template <typename T> using    collatees   = _std::tuple_size<_std::remove_reference_t<T>>;
template <typename T> using    collatees_t = typename collatees<T>::type;
template <typename T> XTAL_LET collatees_v = collatees<T>::value;
template <typename T> XTAL_LET collatees_w = [] <auto... Ns>
	(seek_t<Ns...>) XTAL_0FN_(unfalse_q<collatee_b<T, Ns>...>)
	(seek_v<collatees_v<T>>)
;

template <typename T>
concept collated_b = requires
{
	typename collatees_t<T>;
	requires collatees_w<T>;
};
template <typename... Ts>
concept collated_q = unfalse_q<collated_b<Ts>...>;

template <typename    T >         concept    arrayed_b   = iterated_b<T> and collated_b<T>;
template <typename... Ts>         concept    arrayed_q   = unfalse_q<arrayed_b<Ts>...>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
