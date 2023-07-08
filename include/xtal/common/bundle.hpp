#pragma once
#include "./any.hpp"
#include "./seek.hpp"





XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename    T  >    using bundle_size   = _std::tuple_size<_std::remove_reference_t<T>>;
template <typename    T  >    using bundle_size_t =   typename bundle_size<T>::type;
template <typename    T  > XTAL_LET bundle_size_v =            bundle_size<T>{};
template <typename    T  >  concept bundle_size_p = constant_p<bundle_size_t<T>>;
template <typename ...Ts >  concept bundle_size_q = conjunct_q<bundle_size_p<Ts>...>;

template <typename T, size_t ...Ns >  struct bundle_part;
template <typename T, size_t... Ns >   using bundle_part_t = typename bundle_part<T, Ns...>::type;
template <typename T, size_t    N  > concept bundle_part_p = requires(T a) {{_std::get<N>(a)} -> is_q<bundle_part_t<T, N>>;};

template <typename T, size_t N, size_t ...Ns>
struct bundle_part<T, N, Ns...>
:	bundle_part<bundle_part_t<T, N>, Ns...>
{};
template <typename T, size_t N>
struct bundle_part<T, N>
:	_std::tuple_element<N, _std::remove_reference_t<T>>
{};
template <typename T>
struct bundle_part<T>
{
	using type = T;

};
template <typename T  >
concept bundle_parts_p = [] <size_t ...N>
	(seek_t<N...>) XTAL_0FN_(conjunct_q<bundle_part_p<T, N>...>)
	(seek_f<bundle_size_v<T>> {})
;
template <typename ...Ts >
concept bundle_parts_q = conjunct_q<bundle_parts_p<Ts>...>;


static_assert(bundle_size_v<_std::tuple<         >> == 0);
static_assert(bundle_size_v<_std::array<null_t, 0>> == 0);

static_assert(bundle_size_p<_std::tuple<         >>);
static_assert(bundle_size_p<_std::array<null_t, 0>>);


////////////////////////////////////////////////////////////////////////////////

template <typename ...Xs>
struct bundle
{
	using type = _std::tuple<rebased_t<Xs>...>;

	XTAL_LET make = [] XTAL_1FN_(type);

	using    size   = bundle_size  <type>;
	using    size_t = bundle_size_t<type>;
	XTAL_LET size_v = bundle_size_v<type>;
	
	template <size_t N> using part   = bundle_part  <type, N>;
	template <size_t N> using part_t = bundle_part_t<type, N>;

	template <typename F> using invoke   = _std::invoke_result  <F, rebased_t<Xs>...>;
	template <typename F> using invoke_t = _std::invoke_result_t<F, rebased_t<Xs>...>;

};
template <typename ...Xs>
using    bundle_t = typename bundle<Xs...>::type;
XTAL_LET bundle_f = [] <typename ...Xs>(Xs &&...xs)
XTAL_0FN_(_std::make_tuple(XTAL_REF_(xs)...));

XTAL_LET bundle_fwd = [] <typename ...Xs>(Xs &&...xs)
XTAL_0FN_(_std::forward_as_tuple<Xs...>(XTAL_REF_(xs)...));


template <typename    T  > concept bundle_p = bundle_size_p<T> and bundle_parts_p<T>;
template <typename ...Ts > concept bundle_q = conjunct_q<bundle_p<Ts>...>;

template <typename    T  > concept heterogeneous_bundle_p = bundle_p<T> and not iterated_q<T>;
template <typename    T  > concept   homogeneous_bundle_p = bundle_p<T> and     iterated_q<T>;

template <typename ...Ts > concept heterogeneous_bundle_q = conjunct_q<heterogeneous_bundle_p<Ts>...>;
template <typename ...Ts > concept   homogeneous_bundle_q = conjunct_q<  homogeneous_bundle_p<Ts>...>;


XTAL_CN2 bundle_part_f(XTAL_DEF_(bundle_p) t)
XTAL_0EX
{
	return XTAL_REF_(t);
}
template <size_t N, size_t ...Ns>
XTAL_CN2 bundle_part_f(XTAL_DEF_(bundle_p) t)
XTAL_0EX
{
	if constexpr (0 == sizeof...(Ns)) {
		return _std::get<N>(XTAL_REF_(t));
	}
	else {
		return bundle_part_f<Ns...>(_std::get<N>(XTAL_REF_(t)));
	}
}
template <constant_q ...Ts>
XTAL_CN2 bundle_part_f(XTAL_DEF_(bundle_p) t, _std::tuple<Ts...> const &)
XTAL_0EX
{
	return bundle_part_f<Ts::value...>(XTAL_REF_(t));
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
