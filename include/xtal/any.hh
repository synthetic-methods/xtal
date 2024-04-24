#pragma once

#if __has_include(<execution>)
#include <execution>
#endif
#include <concepts>
#include <cassert>
#include <cstring>
#include <complex>
#include <numbers>
#include <cmath>
#include <tuple>
#include <array>
#include <queue>
#include <new>
#include <bit>

#include <iostream>

#include <range/v3/all.hpp>
#include <simde/arm/neon.h>
//#if __has_include(<arm_neon.h>)
//#include <arm_neon.h>
//#endif





#include "./etc.hh"

XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _std
{
	using namespace ::std;

#if not __cpp_lib_bit_cast
	template <class T>
	XTAL_LET bit_cast = []<class S> (S const &s)
	XTAL_0FN
	{
		static_assert(is_trivially_copyable_v<T>);
		static_assert(is_trivially_copyable_v<S>);
		static_assert(sizeof(T) == sizeof(S));
		return __builtin_bit_cast(T, s);
	};
#endif

}
namespace _v3
{
	namespace ranges  = ::ranges;
	namespace views   = ::ranges::views;
	namespace actions = ::ranges::actions;

}

#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Standard...

XTAL_USE null_t = _detail:: null_t;
XTAL_USE unit_t = _detail:: unit_t;
XTAL_USE sign_t = _detail:: sign_t;
XTAL_USE byte_t = _detail:: byte_t;
XTAL_USE size_t = _detail:: size_t;
XTAL_USE size_s = _detail:: size_s;
XTAL_USE real_s = _detail:: real_s;

XTAL_LET size_0 = _detail:: size_0;
XTAL_LET size_1 = _detail:: size_1;

template <auto N, auto  ...Ms>	concept exclusive_p = _detail::exclusive_p<N, Ms... >;
template <auto N, auto  ...Ms>	concept inclusive_p = _detail::inclusive_p<N, Ms... >;
template <auto N, auto  N_0=0>	concept      sign_p = _detail::     sign_p<N, N_0>;
template <auto N, auto  N_0=0>	XTAL_LET     sign_n = _detail::     sign_n<N, N_0>;

template <class         ...Ts>	concept      some_q = _detail::     some_q<Ts...>;
template <auto          ...Ns>	concept      some_n = _detail::     some_n<Ns...>;
template <class         ...Ts>	concept      none_q = _detail::     none_q<Ts...>;
template <auto          ...Ns>	concept      none_n = _detail::     none_n<Ns...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural...

template <class   ...Ts>	concept incomplete_q	= (...and  _detail:: incomplete_q<Ts>);
template <class   ...Ts>	concept   complete_q	= (...and  _detail::   complete_q<Ts>);
template <class   ...Ts>	using     complete_t	= typename _detail::   complete_t<Ts...>;


using cardinal_0 = _detail:: cardinal<0>::type;
using cardinal_1 = _detail:: cardinal<1>::type;
using  ordinal_0 = _detail::  ordinal<0>::type;
using  ordinal_1 = _detail::  ordinal<1>::type;
using  logical_0 = _detail::  ordinal<0>::type;
using  logical_1 = _detail::  ordinal<1>::type;

template <auto       N >	using        constant_t	= typename _detail:: constant<N>::type;
template <auto       N >	using        cardinal_t	= typename _detail:: cardinal<N>::type;
template <auto       N >	using         ordinal_t	= typename _detail::  ordinal<N>::type;
template <auto       N >	using         logical_t	= typename _detail::  logical<N>::type;

template <class   ...Ts>	concept      constant_q	= (...and  _detail::  constant_q<Ts>);
template <class   ...Ts>	concept      integral_q	= (...and  _detail::  integral_q<Ts>);
template <class   ...Ts>	concept      cardinal_q	= (...and  _detail::  cardinal_q<Ts>);
template <class   ...Ts>	concept       ordinal_q	= (...and  _detail::   ordinal_q<Ts>);
template <class   ...Ts>	concept       logical_q	= (...and  _detail::   logical_q<Ts>);

template <class   ...Ts>	concept      integral_p	= (...and  _detail::  integral_p<Ts>);
template <class   ...Ts>	concept      cardinal_p	= (...and  _detail::  cardinal_p<Ts>);
template <class   ...Ts>	concept       ordinal_p	= (...and  _detail::   ordinal_p<Ts>);
template <class   ...Ts>	concept       logical_p	= (...and  _detail::   logical_p<Ts>);

template <class   ...Ts>	concept      terminal_q	= (...and  _detail::    terminal_q<Ts>);
template <class   ...Ts>	concept       liminal_q	= (...and  _detail::     liminal_q<Ts>);
template <liminal_q  T >	using      subliminal_s	= typename _detail::  subliminal<T>::type;
template <liminal_q  T >	using     semiliminal_s	= typename _detail:: semiliminal<T>::type;

template <int        N >	using      bisordinal_t	= typename _detail:: bisordinal<N    >::type;
template <int     ...Ns>	using      fractional_t	= typename _detail:: fractional<Ns...>::type;
template <int     ...Ns>	XTAL_LET   fractional_n	=          _detail:: fractional<Ns...>::value;

template <class      T >	using           based_t	=          _detail::   based_t<T>;
template <class   ...Ts>	concept         based_q	= (...and  _detail::   based_q<Ts>);
template <class   ...Ts>	concept       unbased_q	= (...and  _detail:: unbased_q<Ts>);

template <class      T >	using         rebased_t	= typename _detail:: rebased<T>::type;
template <class      T >	using         debased_t	= typename _detail:: debased<T>::type;
template <class      T >	concept       rebased_p	=   (bool) _detail:: rebased<T>::value;
template <class      T >	concept       debased_p	=   (bool) _detail:: debased<T>::value;
template <class   ...Ts>	concept       rebased_q	= (...and  _detail:: rebased_q<Ts>);
template <class   ...Ts>	concept       debased_q	= (...and  _detail:: debased_q<Ts>);


template <class   ...Ts>	concept       unvalue_q	= (...and  _detail:: unvalue_q<Ts>);
template <class   ...Ts>	concept       invalue_q	= (...and  _detail:: invalue_q<Ts>);
template <class   ...Ts>	concept       devalue_q	= (...and  _detail:: devalue_q<Ts>);
template <class      T >	using         unvalue_t	=          _detail:: unvalue_t<T>;
template <class      T >	using         invalue_t	=          _detail:: invalue_t<T>;
template <class      T >	using         devalue_t	=          _detail:: devalue_t<T>;
template <class      T >	using         devolve_t	=          _detail:: devolve_t<T>;
template <class      T >	XTAL_LET      devalue_n =          _detail:: devalue_n<T>;
template <class      T >	XTAL_LET      devolve_n =          _detail:: devolve_n<T>;
template <class T, class Y>	concept   devalued_q = devalue_n<T> < devalue_n<Y>;
template <class T, class Y>	concept   devalued_p = devalue_n<Y> < devalue_n<T>;
template <class T, class Y>	concept   devolved_q = devolve_n<T> < devolve_n<Y>;
template <class T, class Y>	concept   devolved_p = devolve_n<Y> < devolve_n<T>;


////////////////////////////////////////////////////////////////////////////////

template <class         ...Ts>	concept   isomorphic_q	=         _detail:: isomorphic<Ts...>::value;
template <class         ...Ts>	concept   epimorphic_q	=         _detail:: epimorphic<Ts...>::value;
template <class         ...Ts>	concept anisomorphic_q	=     not _detail:: isomorphic<Ts...>::value;
template <class         ...Ts>	concept anepimorphic_q	=     not _detail:: epimorphic<Ts...>::value;

template <class            ...Ts>	concept         id_q	=         _detail:: identical<Ts...>::value;//< `Ts...` are identical.
template <class            ...Ts>	concept         is_q	=         _detail:: isotropic<Ts...>::value;//< `Ts...` are identical modulo qualifiers.
template <class            ...Ts>	concept         as_q	=         _detail:: epitropic<Ts...>::value;//< `Ts...` are constructible from `Ts[0]`.
template <class  T , class ...Ys>	concept         as_p	=         _detail:: as_p<T, Ys...>;

template <class  T , class ...Ys>	concept   fungible_q	= some_q<Ys...> and (...and _detail::   fungible_q<T, Ys>);//< `T` and `Ys...` are   related by inheritance.
template <class  T , class ...Ys>	concept infungible_q	= some_q<Ys...> and (...and _detail:: infungible_q<T, Ys>);//< `T` and `Ys...` are unrelated by inheritance.

template <class            ...Ys>	concept     common_q	= some_q<Ys...> and _detail:: common_q<Ys...>;//< `Ys...` share an ancestor.
template <class            ...Ys>	using       common_t	=                   _detail:: common_t<Ys...>;
template <           class    X >	using     argument_t	=          typename _detail:: argument<X>::type;



////////////////////////////////////////////////////////////////////////////////

template <class T,      int N=-1>	concept      array_q =             _detail:: array_q<T> and N <  0   or devalue_n<T> == N;
template <class T,      int N=-1>	concept   subarray_q =             _detail:: array_q<T> and 0 <= N  and devalue_n<T> <= N;
template <           class ...Ts>	concept   disarray_q =        not (...and    array_q<Ts>);
template <int N=-1,  class ...Ts>	concept      array_p =            (...and    array_q<Ts, N>);
template <int N=-1,  class ...Ts>	concept   subarray_p =            (...and subarray_q<Ts, N>);

template <class            ...Ts>	concept   accessed_q = (... and _detail:: accessed_q<Ts>);
template <class            ...Ts>	concept    pointer_q = (... and _detail::  pointer_q<Ts>);
template <class               T >	using     accessed_t =          _detail:: accessed_t<T >;
template <class               T >	using      pointer_t =          _detail::  pointer_t<T >;
template <class               T >	using      pointee_t =          _detail::  pointee_t<T >;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Ranged...

template <class      ...Ts>	concept     bounded_q    = (...and  _detail::   bounded_q<Ts>);
template <class      ...Ts>	concept   unbounded_q    = (...and  _detail:: unbounded_q<Ts>);
template <class      ...Ts>	concept   reembrace_q    = (...and  _detail:: reembrace_q<Ts>);
template <class         T >	using     reembrace_t    =          _detail:: reembrace_t<T >;
template <class         T >	using       embrace_t    =          _detail::   embrace_t<T >;

template <class         T >	using      interval_t    =          _detail::  interval_t<T >;
template <class         T >	using      iterated_t    = typename _detail::  iterated  <T >::type;
template <class         T >	using      iterator_t    = typename _detail::  iterator  <T >::type;//_v3::ranges::iterator_t
template <class         T >	using      iteratee_t    = typename _detail::  iteratee  <T >::type;//_v3::ranges::range_reference_t, _v3::ranges::iter_reference_t
template <class         T >	using      distance_t    =          _detail::  distance_t<T >;

template <class      ...Ts>	concept    iteratee_q    = (...and  _detail::  iteratee_q<Ts>);
template <class      ...Ts>	concept    iterable_q    = (...and  _detail::  iterable_q<Ts>);
template <class      ...Ts>	concept    iterated_q    = (...and  _detail::  iterated_q<Ts>);
template <class      ...Ts>	concept    iterator_q    = (...and  _detail::  iterator_q<Ts>);
template <class      ...Ts>	concept    sentinel_q    = (...and  _detail::  sentinel_q<Ts>);
template <class      ...Ts>	concept    distance_q    = (...and  _detail::  distance_q<Ts>);

template <class T, class Y=iteratee_t<T>>	concept    iteratee_of_p = _detail::  iteratee_of_q<T, Y>;
template <class T, class Y=iteratee_t<T>>	concept    iterable_of_p = _detail::  iterable_of_q<T, Y>;
template <class T, class Y=iteratee_t<T>>	concept    iterated_of_p = _detail::  iterated_of_q<T, Y>;
template <class T, class Y=iteratee_t<T>>	concept    iterator_of_p = _detail::  iterator_of_q<T, Y>;
template <class T, class Y=iteratee_t<T>>	concept    sentinel_of_p = _detail::  sentinel_of_q<T, Y>;
//mplate <class T, class Y=iteratee_t<T>>	concept    distance_of_p = _detail::  distance_of_q<T, Y>;

template <class      ...Ts>	concept     counted_q    = (...and  _detail::   counted_q<Ts>);
template <class      ...Ts>	concept     counter_q    = (...and  _detail::   counter_q<Ts>);

template <class   T=size_s>	using       counted_t    = typename _detail::   counted  <T >::type;
template <class   T=size_s>	using       counter_t    = typename _detail::   counter  <T >::type;

template <class         T >	using    reiterated_t    =          _detail:: reiterated_t<T >;
template <class         T >	using    initerated_t    =          _detail:: initerated_t<T >;




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Arithmetic...

template <class      T >	using           numeric_t =          _detail::         numeric_t<T >;
template <class   ...Ts>	concept         numeric_q = (...and  _detail::         numeric_q<Ts>);
template <class   ...Ts>	concept          number_q = (...and  _detail::          number_q<Ts>);
template <class   ...Ts>	concept integral_number_q = (...and  _detail:: integral_number_q<Ts>);
template <class   ...Ts>	concept     real_number_q = (...and  _detail::     real_number_q<Ts>);
template <class   ...Ts>	concept  complex_number_q = (...and  _detail::  complex_number_q<Ts>);


template <size_t N, class T, class U=T>	concept multiplicative_group_p = _detail:: multiplicative_group_p<N, T, U>;
template <size_t N, class T, class U=T>	concept       additive_group_p = _detail::       additive_group_p<N, T, U>;
template <size_t N, class T, class U=T>	concept       discrete_group_p = _detail::       discrete_group_p<N, T, U>;
template <size_t N, class T, class U=T>	concept       quotient_group_p = _detail::       quotient_group_p<N, T, U>;
template <size_t N, class T, class U=T>	concept       integral_group_p = _detail::       integral_group_p<N, T, U>;

template <size_t N, class T, class U=T>	concept multiplicative_field_p = _detail:: multiplicative_field_p<N, T, U>;
template <size_t N, class T, class U=T>	concept           real_field_p = _detail::           real_field_p<N, T, U>;
template <size_t N, class T, class U=T>	concept        complex_field_p = _detail::        complex_field_p<N, T, U>;
template <size_t N, class T, class U=T>	concept        simplex_field_p = _detail::        simplex_field_p<N, T, U>;

template <size_t N, class T, class U=T>	concept        boolean_logic_p = _detail::        boolean_logic_p<N, T, U>;
template <size_t N, class T, class U=T>	concept         binary_logic_p = _detail::         binary_logic_p<N, T, U>;

template <size_t N, class T, class U=T>	concept           inequality_p = _detail::           inequality_p<N, T, U>;
template <size_t N, class T, class U=T>	concept             equality_p = _detail::             equality_p<N, T, U>;
template <size_t N, class T, class U=T>	concept              quality_p = _detail::              quality_p<N, T, U>;


template <class   ...Ts>	concept multiplicative_group_q = (...and multiplicative_group_p<0, Ts>);
template <class   ...Ts>	concept       additive_group_q = (...and       additive_group_p<0, Ts>);
template <class   ...Ts>	concept       discrete_group_q = (...and       discrete_group_p<0, Ts>);
template <class   ...Ts>	concept       quotient_group_q = (...and       quotient_group_p<0, Ts>);
template <class   ...Ts>	concept       integral_group_q = (...and       integral_group_p<0, Ts>);

template <class   ...Ts>	concept multiplicative_field_q = (...and multiplicative_field_p<0, Ts>);
template <class   ...Ts>	concept           real_field_q = (...and           real_field_p<0, Ts>);
template <class   ...Ts>	concept        complex_field_q = (...and        complex_field_p<0, Ts>);
template <class   ...Ts>	concept        simplex_field_q = (...and        simplex_field_p<0, Ts>);

template <class   ...Ts>	concept        boolean_logic_q = (...and        boolean_logic_p<0, Ts>);
template <class   ...Ts>	concept         binary_logic_q = (...and         binary_logic_p<0, Ts>);

template <class   ...Ts>	concept           inequality_q = (...and           inequality_p<2, Ts>);
template <class   ...Ts>	concept             equality_q = (...and             equality_p<2, Ts>);
template <class   ...Ts>	concept              quality_q = (...and              quality_p<2, Ts>);


static_assert(                  real_field_q<float>);
static_assert(        multiplicative_field_q<float>);
static_assert(          not  complex_field_q<float>);
static_assert(          not quotient_group_q<float>);
static_assert(              quotient_group_q<  int>);
static_assert(complex_field_q<_std::complex<float>>);


////////////////////////////////////////////////////////////////////////////////

template <auto    ...Ns>	using      lateral_t	= typename _detail::lateral<common_t<XTAL_TYP_(Ns)...>, Ns...>::type;
template <auto    ...Ns>	XTAL_LET   lateral_n	=          _detail::lateral<common_t<XTAL_TYP_(Ns)...>, Ns...>::type::value;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./_kernel.ii"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
