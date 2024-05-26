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
#include <valarray>// For `static_assert`, only...
#include <array>
#include <tuple>
#include <queue>
#include <new>
#include <bit>

#include <iostream>

#include <range/v3/all.hpp>
#include <experimental/mdspan>

#include <simde/arm/neon.h>
//#if __has_include(<arm_neon.h>)
//#include <arm_neon.h>
//#endif


#if __has_include(<Eigen/Core>)
#include <Eigen/Core>
#endif


#include "./etc.hh"

XTAL_ENV_(push)
namespace std
{///////////////////////////////////////////////////////////////////////////////

#if XTAL_STD < 26
template <size_t N, class U> constexpr U       & get(complex<U>        &t) {return          (reinterpret_cast<U(&)[2]>(t)[N&1]);};
template <size_t N, class U> constexpr U const & get(complex<U> const  &t) {return          (reinterpret_cast<U(&)[2]>(t)[N&1]);};
template <size_t N, class U> constexpr U      && get(complex<U>       &&t) {return XTAL_MOV_(reinterpret_cast<U(&)[2]>(t)[N&1]);};
template <size_t N, class U> constexpr U const&& get(complex<U> const &&t) {return XTAL_MOV_(reinterpret_cast<U(&)[2]>(t)[N&1]);};
template <size_t N, class U> struct tuple_element<N, complex<U>> {using type = U;};
template <          class U> struct tuple_size<complex<U>> : integral_constant<size_t, 2> {};
#endif


}/////////////////////////////////////////////////////////////////////////////
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
namespace _xtd
{
	using namespace ::std::experimental;

}
namespace _xtd::ranges
{
	using namespace ::ranges;

}
namespace _xtd::ranges::views
{
	using namespace ::ranges::views;

	XTAL_DEF_(return,inline)
	XTAL_FN1 zip_transform(auto &&...oo)
	XTAL_0EX
	{
		return zip_with(XTAL_REF_(oo)...);
	};

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


template <auto    N, auto  ...Ms>	XTAL_ASK      exclusive_p = _detail::exclusive_p<N, Ms... >;
template <auto    N, auto  ...Ms>	XTAL_ASK      inclusive_p = _detail::inclusive_p<N, Ms... >;
template <auto    N, auto  N_0=0>	XTAL_ASK           sign_p = _detail::     sign_p<N, N_0>;
template <auto    N, auto  N_0=0>	XTAL_LET           sign_n = _detail::     sign_n<N, N_0>;

template <class            ...Ts>	XTAL_ASK           some_q = _detail::     some_q<Ts...>;
template <auto             ...Ns>	XTAL_ASK           some_n = _detail::     some_n<Ns...>;
template <class            ...Ts>	XTAL_ASK           none_q = _detail::     none_q<Ts...>;
template <auto             ...Ns>	XTAL_ASK           none_n = _detail::     none_n<Ns...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural...

template <class            ...Ts>	XTAL_ASK     incomplete_q =	(...and  _detail:: incomplete_q<Ts   >);
template <class            ...Ts>	XTAL_ASK       complete_q =	(...and  _detail::   complete_q<Ts   >);
template <class            ...Ts>	XTAL_USE       complete_t =	typename _detail::   complete_t<Ts...>;

template <class            ...Ts>	XTAL_ASK         common_q =	some_q<Ts...> and _detail:: common_q<Ts...>;//< `Ts...` share an ancestor.
template <class            ...Ts>	XTAL_USE         common_t =	                  _detail:: common_t<Ts...>;


////////////////////////////////////////////////////////////////////////////////

template <           class ...Ts>	XTAL_ASK      isotropic_q =	        _detail::  isotropic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK      epitropic_q =	        _detail::  epitropic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK    anisotropic_q =	    not _detail::  isotropic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK    anepitropic_q =	    not _detail::  epitropic<Ts...>::value;

template <           class ...Ts>	XTAL_ASK     isomorphic_q =	        _detail:: isomorphic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK     epimorphic_q =	        _detail:: epimorphic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK   anisomorphic_q =	    not _detail:: isomorphic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK   anepimorphic_q =	    not _detail:: epimorphic<Ts...>::value;

template <           class ...Ts>	XTAL_ASK             id_q =	        _detail:: identical<Ts...>::value;//< `Ts...` are identical.
template <           class ...Ts>	XTAL_ASK             is_q =	        _detail:: isotropic<Ts...>::value;//< `Ts...` are identical modulo qualifiers.
template <           class ...Ts>	XTAL_ASK             as_q =	        _detail:: epitropic<Ts...>::value;//< `Ts...` are constructible from `Ts[0]`.
template <class   T, class ...Ts>	XTAL_ASK             as_p =	        _detail:: as_p<T, Ts...>;

template <class   T, class ...Ts>	XTAL_ASK       fungible_q =	some_q<Ts...> and (...and _detail::   fungible_q<T, Ts>);//< `T` and `Ts...` are   related by inheritance.
template <class   T, class ...Ts>	XTAL_ASK     infungible_q =	some_q<Ts...> and (...and _detail:: infungible_q<T, Ts>);//< `T` and `Ts...` are unrelated by inheritance.


////////////////////////////////////////////////////////////////////////////////

XTAL_USE cardinal_0 = _detail:: cardinal<0>::type;
XTAL_USE cardinal_1 = _detail:: cardinal<1>::type;
XTAL_USE  ordinal_0 = _detail::  ordinal<0>::type;
XTAL_USE  ordinal_1 = _detail::  ordinal<1>::type;
XTAL_USE  logical_0 = _detail::  ordinal<0>::type;
XTAL_USE  logical_1 = _detail::  ordinal<1>::type;

template <auto       N >	XTAL_USE     constant_t = typename _detail:: constant<N>::type;
template <auto       N >	XTAL_USE     cardinal_t = typename _detail:: cardinal<N>::type;
template <auto       N >	XTAL_USE      ordinal_t = typename _detail::  ordinal<N>::type;
template <auto       N >	XTAL_USE      logical_t = typename _detail::  logical<N>::type;

template <class   ...Ts>	XTAL_ASK     constant_q = (...and  _detail::  constant_q<Ts>);
template <class   ...Ts>	XTAL_ASK     integral_q = (...and  _detail::  integral_q<Ts>);
template <class   ...Ts>	XTAL_ASK     cardinal_q = (...and  _detail::  cardinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      ordinal_q = (...and  _detail::   ordinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      logical_q = (...and  _detail::   logical_q<Ts>);

template <class   ...Ts>	XTAL_ASK     integral_p = (...and  _detail::  integral_p<Ts>);
template <class   ...Ts>	XTAL_ASK     cardinal_p = (...and  _detail::  cardinal_p<Ts>);
template <class   ...Ts>	XTAL_ASK      ordinal_p = (...and  _detail::   ordinal_p<Ts>);
template <class   ...Ts>	XTAL_ASK      logical_p = (...and  _detail::   logical_p<Ts>);

template <class   ...Ts>	XTAL_ASK     terminal_q = (...and  _detail::    terminal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      liminal_q = (...and  _detail::     liminal_q<Ts>);
template <liminal_q  T >	XTAL_USE   subliminal_s = typename _detail::  subliminal<T>::type;
template <liminal_q  T >	XTAL_USE  semiliminal_s = typename _detail:: semiliminal<T>::type;

template <int        N >	XTAL_USE   bisordinal_t = typename _detail:: bisordinal<N    >::type;
template <int     ...Ns>	XTAL_USE   fractional_t = typename _detail:: fractional<Ns...>::type;
template <int     ...Ns>	XTAL_LET   fractional_n =          _detail:: fractional<Ns...>::value;


template <class      T >	XTAL_USE        based_t =          _detail::   based_t<T>;
template <class   ...Ts>	XTAL_ASK        based_q = (...and  _detail::   based_q<Ts>);
template <class   ...Ts>	XTAL_ASK      unbased_q = (...and  _detail:: unbased_q<Ts>);

template <class      T >	XTAL_USE      rebased_t = typename _detail:: rebased<T>::type;
template <class      T >	XTAL_USE      debased_t = typename _detail:: debased<T>::type;
template <class      T >	XTAL_ASK      rebased_p =   (bool) _detail:: rebased<T>::value;
template <class      T >	XTAL_ASK      debased_p =   (bool) _detail:: debased<T>::value;
template <class   ...Ts>	XTAL_ASK      rebased_q = (...and  _detail:: rebased_q<Ts>);
template <class   ...Ts>	XTAL_ASK      debased_q = (...and  _detail:: debased_q<Ts>);


template <           class ...Ts>	XTAL_ASK   eigenclass_q = (...and  _detail:: eigenclass_q<Ts>);
template <           class ...Ts>	XTAL_USE   eigenclass_t = common_t<_detail:: eigenclass_t<Ts>...>;

template <           class ...Ts>	XTAL_ASK   eigenvalue_q = (...and  _detail:: eigenvalue_q<Ts>);
template <           class ...Ts>	XTAL_USE   eigenvalue_t = common_t<_detail:: eigenvalue_t<Ts>...>;

template <           class ...Ts>	XTAL_ASK      invalue_q = (...and  _detail:: invalue_q<Ts>);
template <           class ...Ts>	XTAL_USE      invalue_u = common_t<_detail:: invalue_u<Ts>...>;

template <           class ...Ts>	XTAL_ASK      unvalue_q = (...and  _detail:: unvalue_q<Ts>);
template <           class ...Ts>	XTAL_USE      unvalue_u = common_t<_detail:: unvalue_u<Ts>...>;

template <           class ...Ts>	XTAL_ASK      devalue_q = (...and  _detail:: devalue_q<Ts>);
template <           class ...Ts>	XTAL_USE      devalue_u = common_t<_detail:: devalue_u<Ts>...>;
template <class   T             >	XTAL_LET      devalue_n = _detail:: devalue_n<T>;

template <           int   ...Ns>	XTAL_USE      devolve_x =	_detail:: devolve_x<   Ns...>;
template <class   T, class ..._s>	XTAL_USE      devolve_s =	_detail:: devolve_s<T, _s...>;
template <class   T             >	XTAL_USE      devolve_t =	_detail:: devolve_t<T       >;
template <           class ...Ts>	XTAL_USE      devolve_u = common_t<_detail:: devolve_u<Ts>...>;
template <class   T             >	XTAL_LET      devolve_n = _detail:: devolve_n<T>;

template <class   T, class ...Ts>	XTAL_ASK     devalued_q = (...and (devalue_n<T> < devalue_n<Ts>));
template <class   T, class ...Ts>	XTAL_ASK     devalued_p = (...and (devalue_n<T> > devalue_n<Ts>));
template <class   T, class ...Ts>	XTAL_ASK     devolved_q = (...and (devolve_n<T> < devolve_n<Ts>));
template <class   T, class ...Ts>	XTAL_ASK     devolved_p = (...and (devolve_n<T> > devolve_n<Ts>));


////////////////////////////////////////////////////////////////////////////////

template <class T,   int   N=-1 >	XTAL_ASK     array_q =             _detail:: array_q<T> and N <  0   or devalue_n<T> == N;
template <class T,   int   N=-1 >	XTAL_ASK  subarray_q =             _detail:: array_q<T> and 0 <= N  and devalue_n<T> <= N;
template <           class ...Ts>	XTAL_ASK  disarray_q =        not (...and    array_q<Ts>);

template <class            ...Ts>	XTAL_ASK  accessed_q = (... and _detail:: accessed_q<Ts>);
template <class            ...Ts>	XTAL_ASK   pointer_q = (... and _detail::  pointer_q<Ts>);
template <class               T >	XTAL_USE  accessed_t =          _detail:: accessed_t<T >;
template <class               T >	XTAL_USE   pointer_t =          _detail::  pointer_t<T >;
template <class               T >	XTAL_USE   pointee_t =          _detail::  pointee_t<T >;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Ranged...

template <class      ...Ts>	XTAL_ASK         bounded_q = (...and  _detail::   bounded_q<Ts>);
template <class      ...Ts>	XTAL_ASK       unbounded_q = (...and  _detail:: unbounded_q<Ts>);
template <class      ...Ts>	XTAL_ASK       reembrace_q = (...and  _detail:: reembrace_q<Ts>);
template <class         T >	XTAL_USE       reembrace_t =          _detail:: reembrace_t<T >;
template <class         T >	XTAL_USE         embrace_t =          _detail::   embrace_t<T >;

template <auto         N=0>	XTAL_LET         induced_n =          _detail::   induced_n<N >;
template <class         T >	XTAL_USE         induced_t =          _detail::   induced_t<T >;
template <class         T >	XTAL_USE        interval_t =          _detail::  interval_t<T >;
template <class         T >	XTAL_USE        iterated_t = typename _detail::  iterated  <T >::type;
template <class         T >	XTAL_USE        iterator_t = typename _detail::  iterator  <T >::type;
template <class         T >	XTAL_USE        iteratee_t = typename _detail::  iteratee  <T >::type;
template <class         T >	XTAL_USE        distance_t =          _detail::  distance_t<T >;

template <class      ...Ts>	XTAL_ASK        iteratee_q = (...and  _detail::  iteratee_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterable_q = (...and  _detail::  iterable_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterated_q = (...and  _detail::  iterated_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterator_q = (...and  _detail::  iterator_q<Ts>);
template <class      ...Ts>	XTAL_ASK        sentinel_q = (...and  _detail::  sentinel_q<Ts>);
template <class      ...Ts>	XTAL_ASK        distance_q = (...and  _detail::  distance_q<Ts>);

template <class      ...Ts>	XTAL_ASK         counted_q = (...and  _detail::   counted_q<Ts>);
template <class      ...Ts>	XTAL_ASK         counter_q = (...and  _detail::   counter_q<Ts>);

template <class   T=size_s>	XTAL_USE         counted_t = typename _detail::   counted  <T >::type;
template <class   T=size_s>	XTAL_USE         counter_t = typename _detail::   counter  <T >::type;

template <class         T >	XTAL_USE       inflected_t = typename _detail:: inflected  <T >::type;

template <class      ...Ts>	XTAL_ASK      deiterated_q = not (...and  _detail:: reiterated_q<Ts>);
template <class      ...Ts>	XTAL_ASK      reiterated_q =     (...and  _detail:: reiterated_q<Ts>);
template <class         T >	XTAL_USE      reiterated_t =              _detail:: reiterated_t<T >;
template <class         T >	XTAL_USE      initerated_t =              _detail:: initerated_t<T >;

template <class      ...Ts>	XTAL_ASK       allocated_q =     (...and  _detail::    allocated_q<Ts>) and iterated_q<Ts...>;
template <class      ...Ts>	XTAL_ASK    materialized_q =     (...and  _detail:: materialized_q<Ts>) and iterated_q<Ts...>;
template <class      ...Ts>	XTAL_ASK  dematerialized_q = not (...and  _detail:: materialized_q<Ts>) and iterated_q<Ts...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Arithmetic...

template <class      T >	XTAL_USE            numeric_t =              _detail::         numeric_t<T >;
template <class   ...Ts>	XTAL_ASK            numeric_q =     (...and  _detail::         numeric_q<Ts>);
template <class   ...Ts>	XTAL_ASK             number_q =     (...and  _detail::          number_q<Ts>);
template <class   ...Ts>	XTAL_ASK        real_number_q =     (...and  _detail::     real_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK      unreal_number_q = not (...and  _detail::     real_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK     complex_number_q =     (...and  _detail::  complex_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK    integral_number_q =     (...and  _detail:: integral_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK disintegral_number_q = not (...and  _detail:: integral_number_q<Ts>);


template <size_t N, class T, class U=T>	XTAL_ASK multiplicative_group_p = _detail:: multiplicative_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       additive_group_p = _detail::       additive_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       discrete_group_p = _detail::       discrete_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       quotient_group_p = _detail::       quotient_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       integral_group_p = _detail::       integral_group_p<N, T, U>;

template <size_t N, class T, class U=T>	XTAL_ASK     contiguous_field_p = _detail::     contiguous_field_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK     continuous_field_p = _detail::     continuous_field_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK        complex_field_p = _detail::        complex_field_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK        simplex_field_p = _detail::        simplex_field_p<N, T, U>;

template <size_t N, class T, class U=T>	XTAL_ASK      boolean_lattice_p = _detail::      boolean_lattice_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       binary_lattice_p = _detail::       binary_lattice_p<N, T, U>;

template <size_t N, class T, class U=T>	XTAL_ASK           inequality_p = _detail::           inequality_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK             equality_p = _detail::             equality_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK              quality_p = _detail::              quality_p<N, T, U>;


template <class   ...Ts>	XTAL_ASK multiplicative_group_q = (...and multiplicative_group_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK       additive_group_q = (...and       additive_group_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK       discrete_group_q = (...and       discrete_group_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK       quotient_group_q = (...and       quotient_group_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK       integral_group_q = (...and       integral_group_p<0, Ts>);

template <class   ...Ts>	XTAL_ASK     contiguous_field_q = (...and     contiguous_field_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK     continuous_field_q = (...and     continuous_field_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK        complex_field_q = (...and        complex_field_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK        simplex_field_q = (...and        simplex_field_p<0, Ts>);

template <class   ...Ts>	XTAL_ASK      boolean_lattice_q = (...and      boolean_lattice_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK       binary_lattice_q = (...and       binary_lattice_p<0, Ts>);

template <class   ...Ts>	XTAL_ASK           inequality_q = (...and           inequality_p<2, Ts>);
template <class   ...Ts>	XTAL_ASK             equality_q = (...and             equality_p<2, Ts>);
template <class   ...Ts>	XTAL_ASK              quality_q = (...and              quality_p<2, Ts>);


static_assert(            contiguous_field_q<float>);
static_assert(               simplex_field_q<float>);
static_assert(          not  complex_field_q<float>);
static_assert(          not quotient_group_q<float>);
static_assert(              quotient_group_q<  int>);
static_assert(complex_field_q<_std::complex<float>>);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <auto    ...Ns>	XTAL_USE   lateral_t = typename _detail::lateral<common_t<XTAL_TYP_(Ns)...>, Ns...>::type;
template <auto    ...Ns>	XTAL_LET   lateral_n =          _detail::lateral<common_t<XTAL_TYP_(Ns)...>, Ns...>::type::value;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./_kernel.ii"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
