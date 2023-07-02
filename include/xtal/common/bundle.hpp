#pragma once
#include "./any.hpp"
#include "./seek.hpp"





XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <typename T          >    using bundle_size    = _std::tuple_size<_std::remove_reference_t<T>>;
template <typename T          >    using bundle_size_t  = typename bundle_size<T>::type;
template <typename T          > XTAL_LET bundle_size_v  = bundle_size<T>::value;
template <typename T          >  concept bundle_size_p  = constant_p<bundle_size_t<T>>;

template <typename T, size_t N>    using bundle_part    = _std::tuple_element<N, _std::remove_reference_t<T>>;
template <typename T, size_t N>    using bundle_part_t  = typename bundle_part<T, N>::type;
template <typename T, size_t N>  concept bundle_part_p  = requires(T a) {{_std::get<N>(a)} -> is_q<bundle_part_t<T, N>>;};
template <typename T          >  concept bundle_part_ps = [] <size_t ...I>
	(seek_t<I...>) XTAL_0FN_(conjunct_q<bundle_part_p<T, I>...>)
	(seek_v<bundle_size_v<T>>)
;

static_assert(bundle_size_v<_std::tuple<         >> == 0);
static_assert(bundle_size_v<_std::array<null_t, 0>> == 0);

static_assert(bundle_size_p<_std::tuple<         >>);
static_assert(bundle_size_p<_std::array<null_t, 0>>);


}///////////////////////////////////////////////////////////////////////////////

template <typename ...Xs>
struct bundle
{
	using type = _std::remove_reference_t<_std::tuple<rebased_t<Xs>...>>;

	XTAL_LET make = [] XTAL_1FN_(type);

	using    size   = _detail::bundle_size  <type>;
	using    size_t = _detail::bundle_size_t<type>;
	XTAL_LET size_v = _detail::bundle_size_v<type>;
	
	template <size_t N> using part   = _detail::bundle_part  <type, N>;
	template <size_t N> using part_t = _detail::bundle_part_t<type, N>;

	template <typename F> using invoke   = _std::invoke_result  <F, rebased_t<Xs>...>;
	template <typename F> using invoke_t = _std::invoke_result_t<F, rebased_t<Xs>...>;

};
template <typename ...Xs>
using    bundle_t = typename bundle<Xs...>::type;
XTAL_LET bundle_f = [] <typename ...Xs>(Xs &&...xs)
XTAL_0FN_(_std::make_tuple(XTAL_REF_(xs)...));

XTAL_LET bundle_fwd = [] <typename ...Xs>(Xs &&...xs)
XTAL_0FN_(_std::forward_as_tuple<Xs...>(XTAL_REF_(xs)...));

template <typename    T > concept bundle_p = _detail::bundle_size_p<T> and _detail::bundle_part_ps<T>;
template <typename ...Ts> concept bundle_q = conjunct_q<bundle_p<Ts>...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
