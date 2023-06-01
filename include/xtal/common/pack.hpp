#pragma once
#include "../any.hpp"
#include "./seek.hpp"





XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename T          > using    pack_size    = _std::tuple_size<_std::remove_reference_t<T>>;
template <typename T          > using    pack_size_t  = typename pack_size<T>::type;
template <typename T          > XTAL_LET pack_size_v  = pack_size<T>::value;
template <typename T          > concept  pack_size_p  = constant_p<pack_size_t<T>>;

template <typename T, size_t N> using    pack_part    = _std::tuple_element<N, _std::remove_reference_t<T>>;
template <typename T, size_t N> using    pack_part_t  = typename pack_part<T, N>::type;
template <typename T, size_t N> concept  pack_part_p  = requires(T a) {{_std::get<N>(a)} -> is_q<pack_part_t<T, N>>;};
template <typename T          > concept  pack_part_ps = [] <size_t ...Ns>
	(seek_t<Ns...>) XTAL_0FN_(every_q<pack_part_p<T, Ns>...>)
	(seek_v<pack_size_v<T>>)
;

static_assert(pack_size_v<_std::tuple<         >> == 0);
static_assert(pack_size_v<_std::array<null_t, 0>> == 0);

static_assert(pack_size_p<_std::tuple<         >>);
static_assert(pack_size_p<_std::array<null_t, 0>>);


////////////////////////////////////////////////////////////////////////////////

template <typename ...Xs>
struct pack
{
	using type = _std::remove_reference_t<_std::tuple<rebased_t<Xs>...>>;

	XTAL_LET make = [](XTAL_DEF...xs) XTAL_0FN_(type(XTAL_REF_(xs)...));

	using    size   = pack_size  <type>;
	using    size_t = pack_size_t<type>;
	XTAL_LET size_v = pack_size_v<type>;
	
	template <size_t N> using part   = pack_part  <type, N>;
	template <size_t N> using part_t = pack_part_t<type, N>;

	template <typename F> using invoke   = _std::invoke_result  <F, rebased_t<Xs>...>;
	template <typename F> using invoke_t = _std::invoke_result_t<F, rebased_t<Xs>...>;

};
template <typename ...Xs>
using    pack_t = typename pack<Xs...>::type;
XTAL_LET pack_f = [] <typename ...Xs> (Xs &&...xs)
XTAL_0FN_(_std::make_tuple(XTAL_FWD_(Xs) (xs)...));

XTAL_LET pack_fwd = [] <typename ...Xs> (Xs &&...xs)
XTAL_0FN_(_std::forward_as_tuple<Xs...>(XTAL_FWD_(Xs) (xs)...));

template <typename    T > concept pack_p = pack_size_p<T> and pack_part_ps<T>;
template <typename ...Ts> concept pack_q = every_q<pack_p<Ts>...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
