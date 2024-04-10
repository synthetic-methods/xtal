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

using    null_t = _detail:: null_t;
using    unit_t = _detail:: unit_t;
using    sign_t = _detail:: sign_t;
using    byte_t = _detail:: byte_t;
using    size_t = _detail:: size_t;
using    size_s = _detail:: size_s;
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

template <auto       N >	using     constant_t	= typename _detail:: constant<N>::type;
template <auto       N >	using     cardinal_t	= typename _detail:: cardinal<N>::type;
template <auto       N >	using      ordinal_t	= typename _detail::  ordinal<N>::type;
template <auto       N >	using      logical_t	= typename _detail::  logical<N>::type;

template <class   ...Ts>	concept   constant_q	= (...and  _detail::  constant_q<Ts>);
template <class   ...Ts>	concept   integral_q	= (...and  _detail::  integral_q<Ts>);
template <class   ...Ts>	concept   cardinal_q	= (...and  _detail::  cardinal_q<Ts>);
template <class   ...Ts>	concept    ordinal_q	= (...and  _detail::   ordinal_q<Ts>);
template <class   ...Ts>	concept    logical_q	= (...and  _detail::   logical_q<Ts>);

template <class   ...Ts>	concept   integral_p	= (...and  _detail::  integral_p<Ts>);
template <class   ...Ts>	concept   cardinal_p	= (...and  _detail::  cardinal_p<Ts>);
template <class   ...Ts>	concept    ordinal_p	= (...and  _detail::   ordinal_p<Ts>);
template <class   ...Ts>	concept    logical_p	= (...and  _detail::   logical_p<Ts>);

template <class   ...Ts>	concept   terminal_q	= (...and  _detail::    terminal_q<Ts>);
template <class   ...Ts>	concept    liminal_q	= (...and  _detail::     liminal_q<Ts>);
template <liminal_q  T >	using   subliminal_s	= typename _detail::  subliminal<T>::type;
template <liminal_q  T >	using  semiliminal_s	= typename _detail:: semiliminal<T>::type;


template <class      T >	using        based_t	=          _detail::   based_t<T>;
template <class   ...Ts>	concept      based_q	= (...and  _detail::   based_q<Ts>);
template <class   ...Ts>	concept    unbased_q	= (...and  _detail:: unbased_q<Ts>);

template <class      T >	using      rebased_t	= typename _detail:: rebased<T>::type;
template <class      T >	using      debased_t	= typename _detail:: debased<T>::type;
template <class      T >	concept    rebased_p	=   (bool) _detail:: rebased<T>::value;
template <class      T >	concept    debased_p	=   (bool) _detail:: debased<T>::value;
template <class   ...Ts>	concept    rebased_q	= (...and  _detail:: rebased_q<Ts>);
template <class   ...Ts>	concept    debased_q	= (...and  _detail:: debased_q<Ts>);


template <class   ...Ts>	concept    devalue_q	= (...and  _detail::  devalue_q<Ts>);
template <class   ...Ts>	concept    revalue_q	= (...and  _detail::  revalue_q<Ts>);
template <class   ...Ts>	concept      value_q	= (...and  _detail::    value_q<Ts>);
template <class      T >	using      devalue_t	=          _detail::  devalue_t<T>;
template <class      T >	using      revalue_t	=          _detail::  revalue_t<T>;
template <class      T >	using        value_t	=          _detail::    value_t<T>;


////////////////////////////////////////////////////////////////////////////////

template <class         ...Ts>	concept    isomorphic_q	=     _detail:: isomorphic<Ts...>::value;
template <class         ...Ts>	concept  anisomorphic_q	= not _detail:: isomorphic<Ts...>::value;
template <class         ...Ts>	concept    epimorphic_q	=     _detail:: epimorphic<Ts...>::value;
template <class         ...Ts>	concept  anepimorphic_q	= not _detail:: epimorphic<Ts...>::value;

template <class            ...Ts>	concept         id_q	=     _detail:: identical<Ts...>::value;//< `Ts...` are identical.
template <class            ...Ts>	concept         is_q	=     _detail:: isotropic<Ts...>::value;//< `Ts...` are identical modulo qualifiers.
template <class            ...Ts>	concept       make_q	=     _detail:: epitropic<Ts...>::value;//< `Ts...` are constructible from `Ts[0]`.
template <class  T , class ...Ys>	concept       make_p	=     _detail:: make_p<T, Ys...>;

template <class  T , class ...Ys>	concept       made_p	= (...and _detail::made_p<T, Ys>);//< `Ys...` are `std::derived_from<T>`.
template <class  T , class ...Ys>	concept       made_q	= (...and _detail::made_q<T, Ys>);//< `T` is `std::derived_from<Ys>...`.

template <class  T , class ...Ys>	concept     unmade_p	= not made_p<T, Ys...>;
template <class  T , class ...Ys>	concept     unmade_q	= not made_q<T, Ys...>;

template <class  T , class ...Ys>	concept   fungible_q	= some_q<Ys...> and (...and _detail::   fungible_q<T, Ys>);//< `T` and `Ys...` are related by inheritance.
template <class  T , class ...Ys>	concept infungible_q	= some_q<Ys...> and (...and _detail:: infungible_q<T, Ys>);

template <class            ...Ys>	concept     common_q	= some_q<Ys...> and _detail:: common_q<Ys...>;//< `Ys...` share an ancestor.
template <class            ...Ys>	using       common_t	=                   _detail:: common_t<Ys...>;
template <           class    X >	using     argument_t	=          typename _detail:: argument<X>::type;

template <class  T , class ...Ys>	concept        not_q	= anisomorphic_q<T, Ys...> or infungible_q<T, Ys...>;


////////////////////////////////////////////////////////////////////////////////

template <class T               >	XTAL_LET     array_n =          _detail:: array_n<T>;
template <class T,      int N=-1>	concept      array_q =          _detail:: array_q<T> and N <  0   or array_n<T> == N;
template <class T,      int N=-1>	concept   subarray_q =          _detail:: array_q<T> and 0 <= N  and array_n<T> <= N;

template <int N=-1,  class ...Ts>	concept      array_p = (...and    array_q<Ts, N>);
template <int N=-1,  class ...Ts>	concept   subarray_p = (...and subarray_q<Ts, N>);

template <class               T >	using      pointed_t =          _detail:: pointed_t<T >;
template <class               T >	using      pointer_t =          _detail:: pointer_t<T >;
template <class            ...Ts>	concept    pointed_q = (... and _detail:: pointed_q<Ts>);
template <class            ...Ts>	concept    pointer_q = (... and _detail:: pointer_q<Ts>);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Ranged...

template <class   ...Ts>	concept   unbounded_q = (...and  _detail:: unbounded_q<Ts>);
template <class   ...Ts>	concept     bounded_q = (...and  _detail::   bounded_q<Ts>);
template <class   ...Ts>	concept      braced_q = (...and  _detail::    braced_q<Ts>);
template <class      T >	using        braced_t =          _detail::    braced_t<T >;
template <class      T >	using        braces_t =          _detail::    braces_t<T >;

template <class   ...Ts>	concept    iterable_q = (...and  _detail::  iterable_q<Ts>);
template <class   ...Ts>	concept    iterated_q = (...and  _detail::  iterated_q<Ts>);
template <class   ...Ts>	concept    iterator_q = (...and  _detail::  iterator_q<Ts>);

template <class      T >	using      interval_t =          _detail::  interval_t<T >;
template <class      T >	using      iterated_t = typename _detail::  iterated  <T >::type;
template <class      T >	using      iterator_t = typename _detail::  iterator  <T >::type;//_v3::ranges::iterator_t
template <class      T >	using      iteratee_t = typename _detail::  iteratee  <T >::type;//_v3::ranges::range_reference_t, _v3::ranges::iter_reference_t
template <class      T >	using      distance_t =          _detail::  distance_t<T >;

template <class   ...Ts>	concept     counted_q = (...and  _detail::   counted_q<Ts>);
template <class   ...Ts>	concept     counter_q = (...and  _detail::   counter_q<Ts>);

template <class   T=size_s>	using    counted_t = typename _detail::   counted  <T >::type;
template <class   T=size_s>	using    counter_t = typename _detail::   counter  <T >::type;

template <class      T >	using     reiterate_t =          _detail:: reiterate_t<T >;
template <class      T >	using     reiterant_t =          _detail:: reiterant_t<T >;




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

template <size_t N, class T, class U=T>	concept     arithmetic_field_p = _detail::     arithmetic_field_p<N, T, U>;
template <size_t N, class T, class U=T>	concept        complex_field_p = _detail::        complex_field_p<N, T, U>;
template <size_t N, class T, class U=T>	concept        simplex_field_p = _detail::        simplex_field_p<N, T, U>;
template <size_t N, class T, class U=T>	concept           real_field_p = _detail::           real_field_p<N, T, U>;

template <size_t N, class T, class U=T>	concept        boolean_logic_p = _detail::        boolean_logic_p<N, T, U>;
template <size_t N, class T, class U=T>	concept         binary_logic_p = _detail::         binary_logic_p<N, T, U>;

template <size_t N, class T, class U=T>	concept           inequality_p = _detail::           inequality_p<N, T, U>;
template <size_t N, class T, class U=T>	concept             equality_p = _detail::             equality_p<N, T, U>;
template <size_t N, class T, class U=T>	concept              quality_p = _detail::              quality_p<N, T, U>;


template <class   ...Ts>	concept multiplicative_group_q = (...and _detail:: multiplicative_group_p<0, Ts>);
template <class   ...Ts>	concept       additive_group_q = (...and _detail::       additive_group_p<0, Ts>);
template <class   ...Ts>	concept       discrete_group_q = (...and _detail::       discrete_group_p<0, Ts>);
template <class   ...Ts>	concept       quotient_group_q = (...and _detail::       quotient_group_p<0, Ts>);
template <class   ...Ts>	concept       integral_group_q = (...and _detail::       integral_group_p<0, Ts>);

template <class   ...Ts>	concept     arithmetic_field_q = (...and _detail::     arithmetic_field_p<0, Ts>);
template <class   ...Ts>	concept        complex_field_q = (...and _detail::        complex_field_p<0, Ts>);
template <class   ...Ts>	concept        simplex_field_q = (...and _detail::        simplex_field_p<0, Ts>);
template <class   ...Ts>	concept           real_field_q = (...and _detail::           real_field_p<0, Ts>);

template <class   ...Ts>	concept        boolean_logic_q = (...and _detail::        boolean_logic_p<0, Ts>);
template <class   ...Ts>	concept         binary_logic_q = (...and _detail::         binary_logic_p<0, Ts>);

template <class   ...Ts>	concept           inequality_q = (...and _detail::           inequality_p<2, Ts>);
template <class   ...Ts>	concept             equality_q = (...and _detail::             equality_p<2, Ts>);
template <class   ...Ts>	concept              quality_q = (...and _detail::              quality_p<2, Ts>);


static_assert(                  real_field_q<float>);
static_assert(            arithmetic_field_q<float>);
static_assert(          not quotient_group_q<float>);
static_assert(              quotient_group_q<  int>);
static_assert(complex_field_q<_std::complex<float>>);


////////////////////////////////////////////////////////////////////////////////

template <auto    ...Ns>	XTAL_USE   lateral_t	= typename _detail::lateral<common_t<XTAL_TYP_(Ns)...>, Ns...>::type;
template <auto    ...Ns>	XTAL_LET   lateral_n	=          _detail::lateral<common_t<XTAL_TYP_(Ns)...>, Ns...>::type::value;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./_kernel.ii"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
