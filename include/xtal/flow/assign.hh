#pragma once
#include "./any.hh"

#include "../cell/header.hh"




XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Insulated `cell::header` used to prefix `assignment`. \

template <class ..._s>	struct  assign;
template <class ..._s>	using   assign_s = bond::compose_s<let_t< _s...>, assign<>>;
template <class ..._s>	concept assign_q = bond::tagged_p<assign_s, _s...>;
template <           >	struct  assign<> : cell::header<bond::tag<assign_s>> {};


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) assign_f = []<class ...Us> (Us &&...us)
XTAL_0FN_(to) (assign_s<based_t<Us>...>(XTAL_REF_(us)...));

template <class U, class T>
concept assigning_p = assess_q<T> and
	requires {requires fungible_q<U, typename based_t<T>::tail_type>;};

template <class T, class ...Us>
concept assigning_q = (...and assigning_p<Us, T>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
