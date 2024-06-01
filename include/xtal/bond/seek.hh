#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <XTAL_NDX ...Ns> XTAL_USE seek_t = _std::index_sequence<Ns...>;
template <XTAL_NDX    N > XTAL_USE seek_s = _std::make_index_sequence<N>;
template <auto     ...  > XTAL_LET seek_i = [] (auto &&o) XTAL_0FN_(XTAL_REF_(o));

XTAL_LET seek_f = []<cointegral_q ...Ns> (Ns ...ns)
XTAL_0FN -> seek_t<Ns{}...> {return {};};

template <XTAL_NDX  ...Ns> XTAL_LET antiseek_f(seek_t<Ns...>) -> seek_t<(sizeof...(Ns) - Ns - 1)...>;
template <XTAL_NDX     N > XTAL_USE antiseek_s = decltype(antiseek_f(seek_s<N>()));


////////////////////////////////////////////////////////////////////////////////

template <XTAL_NDX N_count=0, auto N_onset=0>
XTAL_DEF_(inline)
XTAL_FN1 seek_forward_f(auto const &f)
XTAL_0EX
{
	return [&] <XTAL_NDX ...Ns>(seek_t<Ns...>)
		XTAL_0FN_(..., f(cardinal_t<N_onset + Ns>{})) (seek_s<N_count> {});
}
template <XTAL_NDX N_count=0, auto N_onset=0>
XTAL_DEF_(inline)
XTAL_FN1 seek_backward_f(auto const &f)
XTAL_0EX
{
	return [&] <XTAL_NDX ...Ns>(seek_t<Ns...>)
		XTAL_0FN_(..., f(cardinal_t<N_onset + Ns>{})) (antiseek_s<N_count> {});
}


////////////////////////////////////////////////////////////////////////////////

template <              class ...Ts>  XTAL_TYP seek_constant           {using type = void;};
template <constant_q T, class ...Ts>  XTAL_TYP seek_constant<T, Ts...> {using type =    T;};
template <class      T, class ...Ts>  XTAL_TYP seek_constant<T, Ts...> :  seek_constant<Ts...>    {};
template <              class ...Ts>  XTAL_USE seek_constant_t = typename seek_constant<Ts...>::type;


////////////////////////////////////////////////////////////////////////////////

template <int I=0, bool ...Ns> XTAL_TYP seek_index;
template <int I              > XTAL_TYP seek_index<I              > : ordinal_t<-1> {};
template <int I,   bool ...Ns> XTAL_TYP seek_index<I,  true, Ns...> : ordinal_t< I> {};
template <int I,   bool ...Ns> XTAL_TYP seek_index<I, false, Ns...> : seek_index<I + 1, Ns...> {};
template <         bool ...Ns> XTAL_LET seek_index_n = seek_index<0, Ns...>::value;

static_assert(seek_index_n<                   > == -1);
static_assert(seek_index_n<               true> ==  0);
static_assert(seek_index_n<       false,  true> ==  1);
static_assert(seek_index_n<false, false,  true> ==  2);
static_assert(seek_index_n<false, false, false> == -1);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
