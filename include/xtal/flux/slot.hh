#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Governs access to the arguments of `flux::bundle`. \

//\
template <  int N             >	XTAL_USE slot_t = bond::compose_s<any_s<nominal_t<N>>, confined<>>;
template <  int N             >	XTAL_USE slot_t = any_s<nominal_t<N>>  ;
template <  int N             >	XTAL_LET slot_n = any_s<nominal_t<N>>{};
template <  int N, class ...Ts>	XTAL_REQ slot_p = nominal_q<Ts...> and (some_q<Ts...> and not un_n<N, Ts::value...>);
template <class T,   int ...Ns>	XTAL_REQ slot_q = nominal_q<T    > and (none_n<Ns...> or      in_n<T::value, Ns...>);

static_assert(    slot_p<3, slot_t<3>, slot_t<3>, slot_t<3>>);
static_assert(not slot_p<3, slot_t<3>, slot_t<3>, slot_t<2>>);

static_assert(slot_q<slot_t<3>>);
static_assert(slot_q<slot_t<3>, 3>);
static_assert(slot_q<slot_t<3>, 3, 2, 1>);

static_assert(any_q<flux::slot_t<0>>);


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
