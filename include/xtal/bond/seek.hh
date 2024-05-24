#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <size_t  ...Is> XTAL_USE seek_t = _std::index_sequence<Is...>;
template <size_t     N > XTAL_USE seek_s = _std::make_index_sequence<N>;
template <auto    ...  > XTAL_LET seek_i = [] (auto &&o) XTAL_0FN_(XTAL_REF_(o));

XTAL_LET seek_f = []<class ...Is> (Is ...is)
XTAL_0FN
{
	if constexpr (integral_q<Is...>) {
		return seek_t<is.value...> {};
	}
	else {
		return seek_t<> {};
	}
};


////////////////////////////////////////////////////////////////////////////////

template <size_t N_count=0, auto N_onset=0>
XTAL_FN1 seek_forward_f(auto const &f)
XTAL_0EX
{
	return [&] <size_t ...N>(seek_t<N...>)
		XTAL_0FN_(..., f(cardinal_t<N_onset  + N>{})) (seek_s<N_count> {});
}

template <size_t N_count=0, auto N_onset=0>
XTAL_FN1 seek_backward_f(auto const &f)
XTAL_0EX
{
	size_t constexpr N_offset = N_onset + N_count - 1;
	return [&] <size_t ...N>(seek_t<N...>)
		XTAL_0FN_(..., f(cardinal_t<N_offset - N>{})) (seek_s<N_count> {});
}


////////////////////////////////////////////////////////////////////////////////

template <         class ...Ts>  XTAL_TYP seek_front;
template <class T, class ...Ts>  XTAL_TYP seek_front<T, Ts...> {using type = T;};
template <         class ...Ts>  XTAL_USE seek_front_t = typename seek_front<Ts...>::type;
template <         auto  ...Ns>  XTAL_LET seek_front_n = seek_front_t<cardinal_t<Ns>...>::value;

template <         class ...Ts>  XTAL_TYP seek_back;
template <class T, class ...Ts>  XTAL_TYP seek_back<T, Ts...> : seek_back<Ts...> {};
template <class T             >  XTAL_TYP seek_back<T       >                    {using type = T;};
template <         class ...Ts>  XTAL_USE seek_back_t = typename seek_back<Ts...>::type;
template <         auto  ...Ns>  XTAL_LET seek_back_n = seek_back_t<cardinal_t<Ns>...>::value;


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
