#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <int        ...Ns>	XTAL_LET seek_n =                 _std::array     {Ns...};
template <int        ...Ns>	using    seek_t = _std::     integer_sequence<int, Ns...>;
template <int           N >	using    seek_s = _std::make_integer_sequence<int, N    >;


}///////////////////////////////////////////////////////////////////////////////

template <int        ...Ns>	                 XTAL_LET      seek_n = _detail::seek_n<Ns...>;
template <int        ...Ns>	                 using         seek_t = _detail::seek_t<Ns...>;
template <auto       ...  >	XTAL_DEF_(short) XTAL_LET      seek_i(auto &&o     ) noexcept -> decltype(auto) {return XTAL_REF_(o);}
template <constant_q ...Ns>	XTAL_DEF_(short) XTAL_LET      seek_f(       Ns... ) noexcept -> seek_t<(                         Ns{})...> {return {};}
template <int        ...Ns>	XTAL_DEF_(short) XTAL_LET      seek_f(seek_t<Ns...>) noexcept -> seek_t<(                         Ns  )...> {return {};}
template <constant_q ...Ns>	XTAL_DEF_(short) XTAL_LET  antiseek_f(       Ns... ) noexcept -> seek_t<(sizeof...(Ns) - size_1 - Ns{})...> {return {};}
template <int        ...Ns>	XTAL_DEF_(short) XTAL_LET  antiseek_f(seek_t<Ns...>) noexcept -> seek_t<(sizeof...(Ns) - size_1 - Ns  )...> {return {};}

template <int           N >	                 struct   superseek    {using type = decltype(    seek_f(_detail::seek_s<+N>{}));};
template <int           N >	requires (N < 0) struct   superseek<N> {using type = decltype(antiseek_f(_detail::seek_s<-N>{}));};
template <int           N >	                 using    superseek_t = typename superseek<N>::type;
template <int           N >	                 using         seek_s = superseek_t<+N>;
template <int           N >	                 using     antiseek_s = superseek_t<-N>;


////////////////////////////////////////////////////////////////////////////////

///\
Invokes the function `f` with each index `Ns...`. \

template <auto ...Ns>
XTAL_DEF_(inline)
XTAL_LET seek_access_f(auto const &f)
noexcept -> decltype(auto)
{
	return [&] <int ...I>(seek_t<I...>)
		XTAL_0FN_(..., f(constant_t<I>{})) (seek_t<Ns...> {});
}

template <int N_count=0, auto N_onset=0>
XTAL_DEF_(inline)
XTAL_LET seek_forward_f(auto const &f)
noexcept -> decltype(auto)
{
	return [&] <int ...I>(seek_t<I...>)
		XTAL_0FN_(..., f(constant_t<N_onset + I>{})) (seek_s<N_count> {});
}
template <int N_count=0, auto N_onset=0>
XTAL_DEF_(inline)
XTAL_LET seek_backward_f(auto const &f)
noexcept -> decltype(auto)
{
	return [&] <int ...I>(seek_t<I...>)
		XTAL_0FN_(..., f(constant_t<N_onset + I>{})) (antiseek_s<N_count> {});
}


////////////////////////////////////////////////////////////////////////////////

template <         class ...Ts>  struct   seek_front;
template <class T, class ...Ts>  struct   seek_front<T, Ts...>       {using type = T;};
template <         class ...Ts>  using    seek_front_t = typename seek_front<Ts...>::type;

template <         class ...Ts>  struct   seek_back;
template <class T             >  struct   seek_back <T       >       {using type = T;};
template <class T, class ...Ts>  struct   seek_back <T, Ts...>  : seek_back <Ts...> {};
template <         class ...Ts>  using    seek_back_t  = typename seek_back <Ts...>::type;


////////////////////////////////////////////////////////////////////////////////

template <              class ...Ts>  struct   seek_constant                    {using type = void;};
template <constant_q T, class ...Ts>  struct   seek_constant<T, Ts...> :                        T {};
template <class T,      class ...Ts>  struct   seek_constant<T, Ts...> :  seek_constant<Ts...>    {};
template <              class ...Ts>  using    seek_constant_t = typename seek_constant<Ts...>::type;
template <              class ...Ts>  concept  seek_constant_q = complete_q<seek_constant_t<Ts...>>;
template <              class ...Ts>  XTAL_LET seek_constant_n =          seek_constant<Ts...>::value;


////////////////////////////////////////////////////////////////////////////////

template <int I=0, bool ...Ns> struct   seek_truth;
template <int I              > struct   seek_truth<I              > : constant_t<-1> {};
template <int I,   bool ...Ns> struct   seek_truth<I,  true, Ns...> : constant_t< I> {};
template <int I,   bool ...Ns> struct   seek_truth<I, false, Ns...> : seek_truth<I + 1, Ns...> {};
template <         bool ...Ns> XTAL_LET seek_truth_n = seek_truth<0, Ns...>::value;
template <auto A,  auto ...As> XTAL_LET seek_index_n = seek_truth_n<(A == As)...>;

static_assert(seek_truth_n<                   > == -1);
static_assert(seek_truth_n<               true> ==  0);
static_assert(seek_truth_n<       false,  true> ==  1);
static_assert(seek_truth_n<false, false,  true> ==  2);
static_assert(seek_truth_n<false, false, false> == -1);


////////////////////////////////////////////////////////////////////////////////

template <auto F,                   auto ...Ns>                      struct   seek_ordered;
template <auto F, auto N0                     >                      struct   seek_ordered<F, N0           > : constant_t<N0> {};
template <auto F, auto N0, auto N1, auto ...Ns> requires (F(N0, N1)) struct   seek_ordered<F, N0, N1, Ns...> : seek_ordered<F, N0, Ns...> {};
template <auto F, auto N0, auto N1, auto ...Ns>                      struct   seek_ordered<F, N0, N1, Ns...> : seek_ordered<F, N1, Ns...> {};
template <auto F,                   auto ...Ns>                      XTAL_LET seek_ordered_n = seek_ordered<F, Ns...>::value;

template <int ...Ns>	XTAL_LET seek_maximum_n = seek_ordered_n<[] (auto i, auto j) XTAL_0FN_(i > j), Ns...>;
template <int ...Ns>	XTAL_LET seek_minimum_n = seek_ordered_n<[] (auto i, auto j) XTAL_0FN_(i < j), Ns...>;


////////////////////////////////////////////////////////////////////////////////

template <int ...Ns>
XTAL_LET unseek_n = []<auto ...I> (bond::seek_t<I...>)
	XTAL_0FN_(_std::array{bond::seek_index_n<I, Ns...>...})
(bond::seek_s<1U << _std::bit_width((unsigned) seek_maximum_n<Ns...>)>{});

template <constant_q ...Ns>	XTAL_DEF unseek_f(       Ns... ) noexcept {return unseek_n<Ns{}...>;}
template <int        ...Ns>	XTAL_DEF unseek_f(seek_t<Ns...>) noexcept {return unseek_n<Ns  ...>;}


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
