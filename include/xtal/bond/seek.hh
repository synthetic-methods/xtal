#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <size_type  ...Ns>	XTAL_USE seek_t = _std::index_sequence<Ns...>;
template <size_type     N >	XTAL_USE seek_s = _std::make_index_sequence<N>;

template <auto ...>
XTAL_DEF_(inline)
XTAL_LET seek_i(auto &&o)
XTAL_0EX -> decltype(auto)
{
	return XTAL_REF_(o);
}

template <nominal_q  ...Ns>	XTAL_DEF_(inline) XTAL_LET     seek_f(       Ns... ) XTAL_0EX -> seek_t<(                         Ns{})...> {return {};}
template <nominal_q  ...Ns>	XTAL_DEF_(inline) XTAL_LET antiseek_f(       Ns... ) XTAL_0EX -> seek_t<(sizeof...(Ns) - size_1 - Ns{})...> {return {};}
template <size_type  ...Ns>	XTAL_DEF_(inline) XTAL_LET antiseek_f(seek_t<Ns...>) XTAL_0EX -> seek_t<(sizeof...(Ns) - size_1 - Ns  )...> {return {};}
template <size_type     N >	XTAL_USE                   antiseek_s = decltype(antiseek_f(seek_s<N>()));


////////////////////////////////////////////////////////////////////////////////

template <auto ...Ns>
XTAL_DEF_(inline)
XTAL_LET seek_each_f(auto const &f)
XTAL_0EX -> decltype(auto)
{
	return [&] <size_type ...I>(seek_t<I...>)
		XTAL_0FN_(..., f(nominal_t<I>{})) (seek_t<Ns...> {});
}
template <size_type N_count=0, auto N_onset=0>
XTAL_DEF_(inline)
XTAL_LET seek_forward_f(auto const &f)
XTAL_0EX -> decltype(auto)
{
	return [&] <size_type ...I>(seek_t<I...>)
		XTAL_0FN_(..., f(nominal_t<N_onset + I>{})) (seek_s<N_count> {});
}
template <size_type N_count=0, auto N_onset=0>
XTAL_DEF_(inline)
XTAL_LET seek_backward_f(auto const &f)
XTAL_0EX -> decltype(auto)
{
	return [&] <size_type ...I>(seek_t<I...>)
		XTAL_0FN_(..., f(nominal_t<N_onset + I>{})) (antiseek_s<N_count> {});
}


////////////////////////////////////////////////////////////////////////////////

template <         class ...Ts>  XTAL_TYP seek_front;
template <class T, class ...Ts>  XTAL_TYP seek_front<T, Ts...>       {using type = T;};
template <         class ...Ts>  XTAL_USE seek_front_t = typename seek_front<Ts...>::type;

template <         class ...Ts>  XTAL_TYP seek_back;
template <class T             >  XTAL_TYP seek_back <T       >       {using type = T;};
template <class T, class ...Ts>  XTAL_TYP seek_back <T, Ts...>  : seek_back <Ts...> {};
template <         class ...Ts>  XTAL_USE seek_back_t  = typename seek_back <Ts...>::type;


////////////////////////////////////////////////////////////////////////////////

template <             class ...Ts>  XTAL_TYP seek_constant                    {using type = void;};
template <nominal_q T, class ...Ts>  XTAL_TYP seek_constant<T, Ts...> :                        T {};
template <class     T, class ...Ts>  XTAL_TYP seek_constant<T, Ts...> :  seek_constant<Ts...>    {};
template <             class ...Ts>  XTAL_USE seek_constant_t = typename seek_constant<Ts...>::type;
template <             class ...Ts>  XTAL_LET seek_constant_n =          seek_constant<Ts...>::value;


////////////////////////////////////////////////////////////////////////////////

template <int I=0, bool ...Ns> XTAL_TYP seek_index;
template <int I              > XTAL_TYP seek_index<I              > : nominal_t<-1> {};
template <int I,   bool ...Ns> XTAL_TYP seek_index<I,  true, Ns...> : nominal_t< I> {};
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
