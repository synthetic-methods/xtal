#pragma once
#include "./any.hh"

#include "../cell/header.hh"




XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Insulated `cell::header` used to prefix `assessment`. \

template <class ..._s>	struct  assess;
template <class ..._s>	using   assess_s = bond::compose_s<let_t< _s...>, assess<>>;
template <class ..._s>	concept assess_q = bond::tagged_p<assess_s, _s...>;
template <           >	struct  assess<> : cell::header<bond::tag<assess_s>> {};


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) assess_f = []<class ...Us> (Us &&...us)
XTAL_0FN_(to) (assess_s<based_t<Us>...>(XTAL_REF_(us)...));

template <class U, class T>
concept assessing_p = assess_q<T> and
	requires {requires fungible_q<U, typename based_t<T>::tail_type>;};

template <class T, class ...Us>
concept assessing_q = (...and assessing_p<Us, T>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
