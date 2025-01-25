#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Governs access to the arguments of `flow::bundle`. \

//\
template <  int N             >	using          argument_t = bond::compose_s<any_s<constant_t<N>>, confined<>>;
template <  int N             >	using          argument_t = any_s<constant_t<N>>  ;
template <  int N             >	auto constexpr argument_n = any_s<constant_t<N>>{};
template <  int N, class ...Ts>	concept        argument_p = constant_q<Ts...> and (1 <= sizeof...(Ts) and not un_n<N, Ts::value...>);
template <class T,   int ...Ns>	concept        argument_q = constant_q<T    > and (0 == sizeof...(Ns) or      in_n<T::value, Ns...>);

static_assert(    argument_p<3, argument_t<3>, argument_t<3>, argument_t<3>>);
static_assert(not argument_p<3, argument_t<3>, argument_t<3>, argument_t<2>>);

static_assert(argument_q<argument_t<3>>);
static_assert(argument_q<argument_t<3>, 3>);
static_assert(argument_q<argument_t<3>, 3, 2, 1>);

static_assert(any_q<flow::argument_t<0>>);


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
