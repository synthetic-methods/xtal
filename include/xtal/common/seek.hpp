#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <size_t ...I> using seek_t = _std::index_sequence<I...>;
template <size_t    N> using seek_f = _std::make_index_sequence<N>;
template <size_x K=0, auto I_offset=0>
XTAL_CN1 seek_e(auto const &f)
XTAL_0EX
{
	if constexpr (not K) {
	}
	else if constexpr (0 < K) {
		return [&] <auto ...I>(seek_t<I...>)
			XTAL_0FN_(..., f(constant_t<I_offset + I>())) (seek_f<+K>{});
	}
	else if constexpr (K < 0) {
		size_t constexpr N_offset = I_offset - K - 1;
		return [&] <auto ...I>(seek_t<I...>)
			XTAL_0FN_(..., f(constant_t<N_offset - I>())) (seek_f<-K>{});
	}
}


////////////////////////////////////////////////////////////////////////////////

template <int I, bool ...Qs> struct seek_true_from;
template <int I            > struct seek_true_from<I              >: constant_t<-1> {};
template <int I, bool ...Qs> struct seek_true_from<I,  true, Qs...>: constant_t< I> {};
template <int I, bool ...Qs> struct seek_true_from<I, false, Qs...>: seek_true_from<I + 1, Qs...> {};

template <bool ...Qs> XTAL_LET_(int) seek_true_v = seek_true_from<0, Qs...>::value;

static_assert(seek_true_v<                   > == -1);
static_assert(seek_true_v<               true> ==  0);
static_assert(seek_true_v<       false,  true> ==  1);
static_assert(seek_true_v<false, false,  true> ==  2);
static_assert(seek_true_v<false, false, false> == -1);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
