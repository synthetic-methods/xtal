#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <size_t ...I> using seek_t = _std::index_sequence<I...>;
template <size_t    N> using seek_f = _std::make_index_sequence<N>;

template <size_t N=0, int I_offset=0>
XTAL_CN1 seeker_f(auto const &f)
XTAL_0EX
{
	return [&] <auto ...I>(seek_t<I...>)
		XTAL_0FN_(..., f(constant_t<I + I_offset>())) (seek_f<N> {});
}
template <size_t N=0, int I_offset=0>
XTAL_CN1 antiseeker_f(auto const &f)
XTAL_0EX
{
	size_t constexpr N_offset = N - 1 + I_offset;
	return [&] <auto ...I>(seek_t<I...>)
		XTAL_0FN_(..., f(constant_t<N_offset - I>())) (seek_f<N> {});
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
