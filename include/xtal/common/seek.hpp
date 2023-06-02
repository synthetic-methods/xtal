#pragma once
#include "../any.hpp"
#include "./seek.hpp"





XTAL_ENV_(push)
namespace xtal::common
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <size_t ...Ns > using    seek_t  = _std::     index_sequence<Ns...>;
template <size_t    N  > XTAL_LET seek_v  = _std::make_index_sequence<N>{};
template <size_t    N=0>
XTAL_FZ1 seek_f(auto const &f)
XTAL_0EX
{
	return [&] <auto ...Ns>(seek_t<Ns...>)
		XTAL_0FN_(..., f(Ns)) (seek_v<N>);
}
template <size_t N=0>
XTAL_FZ1 seek_f(auto const &f, XTAL_DEF w)
XTAL_0EX
{
	return [&] <auto ...Ns>(seek_t<Ns...>)
		XTAL_0FN_(f(Ns), ..., XTAL_REF_(w)) (seek_v<N>);
}


////////////////////////////////////////////////////////////////////////////////

template <int I, bool ...Ns> struct seek_true_from;
template <int I            > struct seek_true_from<I              >: constant<-1> {};
template <int I, bool ...Ns> struct seek_true_from<I,  true, Ns...>: constant< I> {};
template <int I, bool ...Ns> struct seek_true_from<I, false, Ns...>: seek_true_from<I + 1, Ns...> {};

template <bool ...Ns> XTAL_LET_(int) seek_true_v = seek_true_from<0, Ns...>::value;

static_assert(seek_true_v<                   > == -1);
static_assert(seek_true_v<               true> ==  0);
static_assert(seek_true_v<       false,  true> ==  1);
static_assert(seek_true_v<false, false,  true> ==  2);
static_assert(seek_true_v<false, false, false> == -1);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
