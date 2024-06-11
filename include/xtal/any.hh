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
#include <simde/arm/neon.h>


#include "./etc.hh"

XTAL_ENV_(push)
namespace std
{///////////////////////////////////////////////////////////////////////////////

#if XTAL_STD < 26
template <size_t N, class U> constexpr U       & get(complex<U>        &t) {return           reinterpret_cast<U(&)[2]>(t)[N&1] ;};
template <size_t N, class U> constexpr U const & get(complex<U> const  &t) {return           reinterpret_cast<U(&)[2]>(t)[N&1] ;};
template <size_t N, class U> constexpr U      && get(complex<U>       &&t) {return XTAL_MOV_(reinterpret_cast<U(&)[2]>(t)[N&1]);};
template <size_t N, class U> constexpr U const&& get(complex<U> const &&t) {return XTAL_MOV_(reinterpret_cast<U(&)[2]>(t)[N&1]);};
template <size_t N, class U> struct tuple_element<N, complex<U>> {using type = U;};
template <          class U> struct tuple_size<complex<U>> : integral_constant<size_t, 2> {};
#endif


}/////////////////////////////////////////////////////////////////////////////
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _std = ::std;
namespace _xtd
{
//	using namespace ::std::experimental;

#if __cpp_lib_bit_cast
	using _std::bit_cast;
#else
	template <class T, class S>
	XTAL_DEF_(inline,static)
	XTAL_REF bit_cast(S const &s)
	XTAL_0FN
	{
		static_assert(is_trivially_copyable_v<T>);
		static_assert(is_trivially_copyable_v<S>);
		static_assert(sizeof(T) == sizeof(S));
		return __builtin_bit_cast(T, s);
	};
#endif

}
namespace _xtd::ranges
{
	using namespace ::ranges;

}
namespace _xtd::ranges::views
{
	using namespace ::ranges::views;

	XTAL_DEF_(inline,static)
	XTAL_REF zip_transform(auto &&...oo)
	XTAL_0EX
	{
		return zip_with(XTAL_REF_(oo)...);
	};

}


#include "./_entail.ii"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Standard...

XTAL_USE null_t = _entail:: null_t;
XTAL_USE unit_t = _entail:: unit_t;
XTAL_USE sign_t = _entail:: sign_t;
XTAL_USE byte_t = _entail:: byte_t;
XTAL_USE size_t = _entail:: size_t;
XTAL_USE size_s = _entail:: size_s;
XTAL_USE real_s = _entail:: real_s;

static constexpr size_t size_0 = _entail:: size_0;
static constexpr size_t size_1 = _entail:: size_1;


template <auto    N, auto  ...Ms>	XTAL_ASK      exclusive_q = _entail::exclusive_q<N, Ms... >;
template <auto    N, auto  ...Ms>	XTAL_ASK      inclusive_q = _entail::inclusive_q<N, Ms... >;
template <auto    N, auto  N_0=0>	XTAL_ASK           sign_p = _entail::     sign_p<N, N_0>;
template <auto    N, auto  N_0=0>	XTAL_LET           sign_n = _entail::     sign_n<N, N_0>;

template <class            ...Ts>	XTAL_ASK           some_q = _entail::     some_q<Ts...>;
template <auto             ...Ns>	XTAL_ASK           some_n = _entail::     some_n<Ns...>;
template <class            ...Ts>	XTAL_ASK           none_q = _entail::     none_q<Ts...>;
template <auto             ...Ns>	XTAL_ASK           none_n = _entail::     none_n<Ns...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural...

template <class            ...Ts>	XTAL_ASK           void_q =	(...and  _entail::       void_q<Ts   >);
template <class            ...Ts>	XTAL_ASK     incomplete_q =	(...and  _entail:: incomplete_q<Ts   >);
template <class            ...Ts>	XTAL_ASK       complete_q =	(...and  _entail::   complete_q<Ts   >);
template <class            ...Ts>	XTAL_USE       complete_t =	typename _entail::   complete_t<Ts...>;

template <class            ...Ts>	XTAL_ASK         common_q =	some_q<Ts...> and _entail:: common_q<Ts...>;//< `Ts...` share an ancestor.
template <class            ...Ts>	XTAL_USE         common_t =	                  _entail:: common_t<Ts...>;


////////////////////////////////////////////////////////////////////////////////

template <           class ...Ts>	XTAL_USE      isotropic_t =	               _entail::  isotropic<Ts...>;
template <           class ...Ts>	XTAL_USE      epitropic_t =	               _entail::  epitropic<Ts...>;
template <           class ...Ts>	XTAL_USE    anisotropic_t =	_std::negation<_entail::  isotropic<Ts...>>;
template <           class ...Ts>	XTAL_USE    anepitropic_t =	_std::negation<_entail::  epitropic<Ts...>>;

template <           class ...Ts>	XTAL_USE     isomorphic_t =	               _entail:: isomorphic<Ts...>;
template <           class ...Ts>	XTAL_USE     epimorphic_t =	               _entail:: epimorphic<Ts...>;
template <           class ...Ts>	XTAL_USE   anisomorphic_t =	_std::negation<_entail:: isomorphic<Ts...>>;
template <           class ...Ts>	XTAL_USE   anepimorphic_t =	_std::negation<_entail:: epimorphic<Ts...>>;

template <           class ...Ts>	XTAL_ASK      isotropic_q =	        _entail::  isotropic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK      epitropic_q =	        _entail::  epitropic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK    anisotropic_q =	    not _entail::  isotropic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK    anepitropic_q =	    not _entail::  epitropic<Ts...>::value;

template <           class ...Ts>	XTAL_ASK     isomorphic_q =	        _entail:: isomorphic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK     epimorphic_q =	        _entail:: epimorphic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK   anisomorphic_q =	    not _entail:: isomorphic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK   anepimorphic_q =	    not _entail:: epimorphic<Ts...>::value;

template <           class ...Ts>	XTAL_ASK             id_q =	        _entail:: identical<Ts...>::value;//< `Ts...` are identical.
template <           class ...Ts>	XTAL_ASK             is_q =	        _entail:: isotropic<Ts...>::value;//< `Ts...` are identical modulo qualifiers.
template <           class ...Ts>	XTAL_ASK             as_q =	        _entail:: epitropic<Ts...>::value;//< `Ts...` are constructible from `Ts[0]`.
template <class   T, class ...Ts>	XTAL_ASK             as_p =	        _entail:: as_p<T, Ts...>;

template <           class ...Ts>	XTAL_TYP       fungible             : _std::false_type                               {};
template <class   T, class ...Ts>	XTAL_TYP       fungible<T, Ts...>   : _std::conjunction<_entail::fungible<T, Ts>...> {};
template <           class ...Ts>	XTAL_ASK       fungible_q =	        fungible  <Ts...>::value; //< `T` and `Ts...` are   related by inheritance.
template <           class ...Ts>	XTAL_ASK     infungible_q =	    not fungible_q<Ts...>;        //< `T` and `Ts...` are unrelated by inheritance.

template <class   X, class ...Fs>	XTAL_ASK     idempotent_p =	(...and _entail:: idempotent_p<X, Fs>);//< `X` is unchanged by `Fs...`.
template <class   F, class    X >	XTAL_ASK     idempotent_q =	idempotent_p<X, F>;


////////////////////////////////////////////////////////////////////////////////

template <auto       N >	XTAL_USE      Nominal_t = typename _entail::     Nominal_t<N >;
template <auto       N >	XTAL_USE      Logical_t = typename _entail::     Logical_t<N >;
template <auto       N >	XTAL_USE      Ordinal_t = typename _entail::     Ordinal_t<N >;
template <auto       N >	XTAL_USE     Cardinal_t = typename _entail::    Cardinal_t<N >;
template <auto       N >	XTAL_USE     Integral_t = typename _entail::    Integral_t<N >;

template <class   ...Ts>	XTAL_ASK      Nominal_q = (...and  _entail::     Nominal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      Ordinal_q = (...and  _entail::     Ordinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      Logical_q = (...and  _entail::     Logical_q<Ts>);
template <class   ...Ts>	XTAL_ASK     Integral_q = (...and  _entail::    Integral_q<Ts>);
template <class   ...Ts>	XTAL_ASK     Cardinal_q = (...and  _entail::    Cardinal_q<Ts>);

template <class   ...Ts>	XTAL_ASK      logical_q = (...and  _entail::     logical_q<Ts>);
template <class   ...Ts>	XTAL_ASK      ordinal_q = (...and  _entail::     ordinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK     cardinal_q = (...and  _entail::    cardinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK     integral_q = (...and  _entail::    integral_q<Ts>);

template <class   ...Ts>	XTAL_ASK     Terminal_q = (...and  _entail::    Terminal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      Liminal_q = (...and  _entail::     Liminal_q<Ts>);
template <Liminal_q  T >	XTAL_USE   Subliminal_s = typename _entail::  Subliminal_s<T >;
template <Liminal_q  T >	XTAL_USE  Semiliminal_s = typename _entail:: Semiliminal_s<T >;

template <size_t     N >	XTAL_LET    factorial_n =          _entail::   Factorial  <N    >::value;
template <int        N >	XTAL_LET   bisordinal_n =          _entail::  Bisordinal  <N    >::value;
template <int     ...Ns>	XTAL_LET   fractional_n =          _entail::  Fractional  <Ns...>::value;

XTAL_USE  Logical_0 = _entail::  Logical_t<0>;
XTAL_USE  Logical_1 = _entail::  Logical_t<1>;
XTAL_USE  Ordinal_0 = _entail::  Ordinal_t<0>;
XTAL_USE  Ordinal_1 = _entail::  Ordinal_t<1>;
XTAL_USE Cardinal_0 = _entail:: Cardinal_t<0>;
XTAL_USE Cardinal_1 = _entail:: Cardinal_t<1>;


template <class      T >	XTAL_USE        based_t =          _entail::   based_t<T>;
template <class   ...Ts>	XTAL_ASK        based_q = (...and  _entail::   based_q<Ts>);
template <class   ...Ts>	XTAL_ASK      unbased_q = (...and  _entail:: unbased_q<Ts>);

template <class      T >	XTAL_USE      rebased_t = typename _entail:: rebased<T>::type;
template <class      T >	XTAL_USE      debased_t = typename _entail:: debased<T>::type;
template <class      T >	XTAL_ASK      rebased_p =   (bool) _entail:: rebased<T>::value;
template <class      T >	XTAL_ASK      debased_p =   (bool) _entail:: debased<T>::value;
template <class   ...Ts>	XTAL_ASK      rebased_q = (...and  _entail:: rebased_q<Ts>);
template <class   ...Ts>	XTAL_ASK      debased_q = (...and  _entail:: debased_q<Ts>);


template <           class ...Ts>	XTAL_ASK     invalued_q = (...and  _entail:: invalued_q<Ts>);
template <           class ...Ts>	XTAL_USE     invalued_t = common_t<_entail:: invalued_t<Ts>...>;

template <           class ...Ts>	XTAL_ASK     unvalued_q = (...and  _entail:: unvalued_q<Ts>);
template <           class ...Ts>	XTAL_USE     unvalued_t = common_t<_entail:: unvalued_t<Ts>...>;

template <           class ...Ts>	XTAL_ASK     devalued_q = (...and  _entail:: devalued_q<Ts>);
template <           class ...Ts>	XTAL_USE     devalued_t = common_t<_entail:: devalued_t<Ts>...>;
template <class   T             >	XTAL_LET     devalued_n = _entail:: devalued_n<T>;

template <class   T, int   ...Ns>	XTAL_USE     devolved   =	_entail:: devolved  <T, Ns...>;
//mplate <           int   ...Ns>	XTAL_USE     devolved_x =	_entail:: devolved_x<   Ns...>;
//mplate <class   T, class ..._s>	XTAL_USE     devolved_s =	_entail:: devolved_s<T, _s...>;
template <           class ...Ts>	XTAL_USE     devolved_t = common_t<_entail:: devolved_t<Ts>...>;
template <class   T             >	XTAL_LET     devolved_n = _entail:: devolved_n<T>;

template <class   T, class ...Ts>	XTAL_ASK     devalued_p = (...and (devalued_n<T> < devalued_n<Ts>));
template <class   T, class ...Ts>	XTAL_ASK     devolved_p = (...and (devolved_n<T> < devolved_n<Ts>));


////////////////////////////////////////////////////////////////////////////////

template <           class ...Ts>	XTAL_ASK    column_q =  (...and _entail:: column_q<Ts>);
template <class T,   int   N=-1 >	XTAL_ASK     array_q =          _entail::  array_q<T> and N <  0   or devalued_n<T> == N;
template <class T,   int   N=-1 >	XTAL_ASK  subarray_q =          _entail::  array_q<T> and 0 <= N  and devalued_n<T> <= N;
template <           class ...Ts>	XTAL_ASK  disarray_q =        not (...and  array_q<Ts>);

template <class            ...Ts>	XTAL_ASK  accessed_q = (... and _entail:: accessed_q<Ts>);
template <class            ...Ts>	XTAL_ASK   pointer_q = (... and _entail::  pointer_q<Ts>);
template <class               T >	XTAL_USE  accessed_t =          _entail:: accessed_t<T >;
template <class               T >	XTAL_USE   pointer_t =          _entail::  pointer_t<T >;
template <class               T >	XTAL_USE   pointee_t =          _entail::  pointee_t<T >;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Ranged...

template <class      ...Ts>	XTAL_ASK        sizeable_q =	    (...and  _entail::   sizeable_q<based_t<Ts>>);
template <class      ...Ts>	XTAL_ASK      resizeable_q =	    (...and  _entail:: resizeable_q<based_t<Ts>>);

template <class      ...Ts>	XTAL_ASK       reembrace_q =	    (...and  _entail::  reembrace_q<Ts>);
template <class         T >	XTAL_USE       reembrace_t =	             _entail::  reembrace_t<T >;
template <class         T >	XTAL_USE         embrace_t =	             _entail::    embrace_t<T >;

template <class         T >	XTAL_USE        interval_t =	             _entail::   interval_t<T >;
template <class         T >	XTAL_USE        iterated_t =	    typename _entail::   iterated  <T >::type;
template <class         T >	XTAL_USE        iterator_t =	    typename _entail::   iterator  <T >::type;
template <class         T >	XTAL_USE        iteratee_t =	    typename _entail::   iteratee  <T >::type;
template <class         T >	XTAL_USE        distance_t =	             _entail::   distance_t<T >;
template <class   T=size_s>	XTAL_USE         counted_t =	    typename _entail::    counted  <T >::type;
template <class   T=size_s>	XTAL_USE         counter_t =	    typename _entail::    counter  <T >::type;

template <class      ...Ts>	XTAL_ASK        interval_q =	    (...and  _entail::   interval_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iteratee_q =	    (...and  _entail::   iteratee_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterable_q =	    (...and  _entail::   iterable_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterated_q =	    (...and  _entail::   iterated_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterator_q =	    (...and  _entail::   iterator_q<Ts>);
template <class      ...Ts>	XTAL_ASK        sentinel_q =	    (...and  _entail::   sentinel_q<Ts>);
template <class      ...Ts>	XTAL_ASK        distance_q =	    (...and  _entail::   distance_q<Ts>);
template <class      ...Ts>	XTAL_ASK         counted_q =	    (...and  _entail::    counted_q<Ts>);
template <class      ...Ts>	XTAL_ASK         counter_q =	    (...and  _entail::    counter_q<Ts>);

template <class      ...Ts>	XTAL_ASK     uniteratee_q =	not (...and  _entail::   iteratee_q<Ts>);
template <class      ...Ts>	XTAL_ASK     uniterable_q =	not (...and  _entail::   iterable_q<Ts>);
template <class      ...Ts>	XTAL_ASK     uniterated_q =	not (...and  _entail::   iterated_q<Ts>);
template <class      ...Ts>	XTAL_ASK     uniterator_q =	not (...and  _entail::   iterator_q<Ts>);
template <class      ...Ts>	XTAL_ASK      uncounted_q =	not (...and  _entail::    counted_q<Ts>);
template <class      ...Ts>	XTAL_ASK      uncounter_q =	not (...and  _entail::    counter_q<Ts>);

template <class         T >	XTAL_USE      reiterated_t =	             _entail:: reiterated_t<T >;
template <class         T >	XTAL_USE      initerated_t =	             _entail:: initerated_t<T >;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Arithmetic...

template <class   ...Ts>	XTAL_ASK            number_q =	    (...and  _entail::          number_q<Ts>);
template <class   ...Ts>	XTAL_ASK       real_number_q =	    (...and  _entail::     real_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK    complex_number_q =	    (...and  _entail::  complex_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK   integral_number_q =	    (...and  _entail:: integral_number_q<Ts>);


template <size_t N, class T, class U=T>	XTAL_ASK multiplicative_group_p = _entail:: multiplicative_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       additive_group_p = _entail::       additive_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       discrete_group_p = _entail::       discrete_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       quotient_group_p = _entail::       quotient_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       integral_group_p = _entail::       integral_group_p<N, T, U>;

template <size_t N, class T, class U=T>	XTAL_ASK     contiguous_group_p = _entail::     contiguous_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK     contiguous_field_p = _entail::     contiguous_field_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK     continuous_field_p = _entail::     continuous_field_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK        complex_field_p = _entail::        complex_field_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK        simplex_field_p = _entail::        simplex_field_p<N, T, U>;

template <size_t N, class T, class U=T>	XTAL_ASK      boolean_lattice_p = _entail::      boolean_lattice_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       binary_lattice_p = _entail::       binary_lattice_p<N, T, U>;

template <size_t N, class T, class U=T>	XTAL_ASK           inequality_p = _entail::           inequality_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK             equality_p = _entail::             equality_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK              quality_p = _entail::              quality_p<N, T, U>;


template <class   ...Ts>	XTAL_ASK multiplicative_group_q = (...and multiplicative_group_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK       additive_group_q = (...and       additive_group_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK       discrete_group_q = (...and       discrete_group_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK       quotient_group_q = (...and       quotient_group_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK       integral_group_q = (...and       integral_group_p<0, Ts>);

template <class   ...Ts>	XTAL_ASK     contiguous_group_q = (...and     contiguous_group_p<0, Ts>);
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

template <auto    ...Ns>	XTAL_USE   lateral_t = typename _entail::lateral<common_t<XTAL_TYP_(Ns)...>, Ns...>::type;
template <auto    ...Ns>	XTAL_LET   lateral_n =          _entail::lateral<common_t<XTAL_TYP_(Ns)...>, Ns...>::type::value;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./any.ii"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
