#pragma once
#include "./any.hpp"
#include "./realize.hpp"





XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename T        > using    bundle_size   = _std::tuple_size<_std::remove_reference_t<T>>;
template <typename T        > using    bundle_size_t = typename bundle_size<T>::type;
template <typename T        > XTAL_LET bundle_size_v = bundle_size<T>::value;
template <typename T        > concept  bundle_size_b = cased_b<bundle_size_t<T>>;

template <typename T, auto N> using    bundle_part   = _std::tuple_element<N, _std::remove_reference_t<T>>;
template <typename T, auto N> using    bundle_part_t = typename bundle_part<T, N>::type;
template <typename T, auto N> concept  bundle_part_b = requires(T a) {{_std::get<N>(a)} -> is_q<bundle_part_t<T, N>>;};
template <typename T        > concept  bundle_part_p = [] <auto... Ns>
	(seek_t<Ns...>) XTAL_0FN_(unfalse_q<bundle_part_b<T, Ns>...>)
	(seek_v<bundle_size_v<T>>)
;

static_assert(bundle_size_v<_std::tuple<       >> == 0);
static_assert(bundle_size_v<_std::array<void, 0>> == 0);

static_assert(bundle_size_b<_std::tuple<       >>);
static_assert(bundle_size_b<_std::array<void, 0>>);

static_assert(bundle_part_p<_std::tuple<       >>);
static_assert(bundle_part_p<_std::array<void, 0>>);

////////////////////////////////////////////////////////////////////////////////

template <typename... Xs>
struct bundle
{
	using type = _std::remove_reference_t<_std::tuple<rebased_t<Xs>...>>;

	template <typename F> using invoke   = _std::invoke_result  <F, rebased_t<Xs>...>;
	template <typename F> using invoke_t = _std::invoke_result_t<F, rebased_t<Xs>...>;

};
template <typename... Xs>
using    bundle_t = typename bundle<Xs...>::type;
XTAL_LET bundle_f = [] <typename... Xs> (Xs&&... xs)
XTAL_0FN_(_std::make_tuple(XTAL_FWD_(Xs) (xs)...));

XTAL_LET bundle_fwd = [] <typename... Xs> (Xs&&... xs)
XTAL_0FN_(_std::forward_as_tuple<Xs...>(XTAL_FWD_(Xs) (xs)...));

template <typename    T > concept  bundle_b = bundle_size_b<T> and bundle_part_p<T>;
template <typename... Ts> concept  bundle_q = unfalse_q<bundle_b<Ts>...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
