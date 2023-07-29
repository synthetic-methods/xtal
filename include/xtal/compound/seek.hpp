#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::compound
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <size_t ...I> using seek_t = _std::index_sequence<I...>;
template <size_t    N> using seek_f = _std::make_index_sequence<N>;
template <size_s K=0, auto I_offset=0>
XTAL_CN1 seek_e(auto const &f)
XTAL_0EX
{
	if constexpr (not K) {
	}
	else if constexpr (0 < K) {
		return [&] <size_t ...I>(seek_t<I...>)
			XTAL_0FN_(..., f(sequent_t<I_offset + I>())) (seek_f<+K>{});
	}
	else if constexpr (K < 0) {
		size_t constexpr N_offset = I_offset - K - 1;
		return [&] <size_t ...I>(seek_t<I...>)
			XTAL_0FN_(..., f(sequent_t<N_offset - I>())) (seek_f<-K>{});
	}
}


////////////////////////////////////////////////////////////////////////////////

template <         class ...Ts>  struct seek_front;
template <class T, class ...Ts>  struct seek_front<T, Ts...> {using type = T;};
template <         class ...Ts>   using seek_front_t = typename seek_front<Ts...>::type;

template <         class ...Ts>  struct seek_back;
template <class T, class ...Ts>  struct seek_back<T, Ts...>: seek_back<Ts...> {};
template <class T             >  struct seek_back<T> {using type = T;};
template <         class ...Ts>   using seek_back_t = typename seek_back<Ts...>::type;


////////////////////////////////////////////////////////////////////////////////

template <int I=0, bool ...Ns>         struct seek_true;
template <int I              >         struct seek_true<I              >: integer_t<-1> {};
template <int I,   bool ...Ns>         struct seek_true<I,  true, Ns...>: integer_t< I> {};
template <int I,   bool ...Ns>         struct seek_true<I, false, Ns...>: seek_true<I + 1, Ns...> {};
template <         bool ...Ns> XTAL_LET_(int) seek_true_v = seek_true<0, Ns...>::value;

static_assert(seek_true_v<                   > == -1);
static_assert(seek_true_v<               true> ==  0);
static_assert(seek_true_v<       false,  true> ==  1);
static_assert(seek_true_v<false, false,  true> ==  2);
static_assert(seek_true_v<false, false, false> == -1);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
