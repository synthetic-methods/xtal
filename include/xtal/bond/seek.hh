#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <size_t  ...I > XTAL_USE seek_t = _std::index_sequence<I...>;
template <size_t     N > XTAL_USE seek_s = _std::make_index_sequence<N>;
template <auto    ...  > XTAL_LET seek_i = [] (auto &&o) XTAL_0FN_(XTAL_REF_(o));


////////////////////////////////////////////////////////////////////////////////

template <size_t K=0, auto I_onset=0>
XTAL_FN1 seek_forward_f(auto const &f)
XTAL_0EX
{
	return [&] <size_t ...I>(seek_t<I...>)
		XTAL_0FN_(..., f(cardinal_t<I_onset  + I>{})) (seek_s<K> {});
}

template <size_t K=0, auto I_onset=0>
XTAL_FN1 seek_backward_f(auto const &f)
XTAL_0EX
{
	size_t constexpr I_offset = I_onset + K - 1;
	return [&] <size_t ...I>(seek_t<I...>)
		XTAL_0FN_(..., f(cardinal_t<I_offset - I>{})) (seek_s<K> {});
}


////////////////////////////////////////////////////////////////////////////////

template <         class ...Ts>  XTAL_TYP seek_front;
template <class T, class ...Ts>  XTAL_TYP seek_front<T, Ts...> {using type = T;};
template <         class ...Ts>  XTAL_USE seek_front_t = typename seek_front<Ts...>::type;

template <         class ...Ts>  XTAL_TYP seek_back;
template <class T, class ...Ts>  XTAL_TYP seek_back<T, Ts...> : seek_back<Ts...> {};
template <class T             >  XTAL_TYP seek_back<T       >                    {using type = T;};
template <         class ...Ts>  XTAL_USE seek_back_t = typename seek_back<Ts...>::type;


////////////////////////////////////////////////////////////////////////////////

template <              class ...Ts>  XTAL_TYP seek_constant           {using type = void;};
template <constant_q T, class ...Ts>  XTAL_TYP seek_constant<T, Ts...> {using type =    T;};
template <class      T, class ...Ts>  XTAL_TYP seek_constant<T, Ts...> :  seek_constant<Ts...>    {};
template <              class ...Ts>  XTAL_USE seek_constant_t = typename seek_constant<Ts...>::type;


////////////////////////////////////////////////////////////////////////////////

template <int I=0, bool ...Ns> XTAL_TYP seek_truth;
template <int I              > XTAL_TYP seek_truth<I              > : ordinal_t<-1> {};
template <int I,   bool ...Ns> XTAL_TYP seek_truth<I,  true, Ns...> : ordinal_t< I> {};
template <int I,   bool ...Ns> XTAL_TYP seek_truth<I, false, Ns...> : seek_truth<I + 1, Ns...> {};
template <         bool ...Ns> XTAL_LET seek_truth_n = seek_truth<0, Ns...>::value;

static_assert(seek_truth_n<                   > == -1);
static_assert(seek_truth_n<               true> ==  0);
static_assert(seek_truth_n<       false,  true> ==  1);
static_assert(seek_truth_n<false, false,  true> ==  2);
static_assert(seek_truth_n<false, false, false> == -1);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
