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
//	using namespace ::std::experimental;

}
namespace _xtd::ranges
{
	using namespace ::ranges;

}
namespace _xtd::ranges::views
{
	using namespace ::ranges::views;

	XTAL_DEF_(inline)
	XTAL_FN1 zip_transform(auto &&...oo)
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

XTAL_LET size_0 = _entail:: size_0;
XTAL_LET size_1 = _entail:: size_1;


template <auto    N, auto  ...Ms>	XTAL_ASK      exclusive_p = _entail::exclusive_p<N, Ms... >;
template <auto    N, auto  ...Ms>	XTAL_ASK      inclusive_p = _entail::inclusive_p<N, Ms... >;
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

template <class   T, class ...Ts>	XTAL_ASK       fungible_q =	some_q<Ts...> and (...and _entail::   fungible_q<T, Ts>);//< `T` and `Ts...` are   related by inheritance.
template <class   T, class ...Ts>	XTAL_ASK     infungible_q =	some_q<Ts...> and (...and _entail:: infungible_q<T, Ts>);//< `T` and `Ts...` are unrelated by inheritance.

template <class   X, class ...Fs>	XTAL_ASK     idempotent_p =	(...and _entail:: idempotent_p<X, Fs>);//< `X` is unchanged by `Fs...`.
template <class   F, class    X >	XTAL_ASK     idempotent_q =	idempotent_p<X, F>;


////////////////////////////////////////////////////////////////////////////////

XTAL_USE cardinal_0 = _entail:: cardinal<0>::type;
XTAL_USE cardinal_1 = _entail:: cardinal<1>::type;
XTAL_USE  ordinal_0 = _entail::  ordinal<0>::type;
XTAL_USE  ordinal_1 = _entail::  ordinal<1>::type;
XTAL_USE  logical_0 = _entail::  ordinal<0>::type;
XTAL_USE  logical_1 = _entail::  ordinal<1>::type;

template <auto       N >	XTAL_USE     constant_t = typename _entail:: constant<N>::type;
template <auto       N >	XTAL_USE     cardinal_t = typename _entail:: cardinal<N>::type;
template <auto       N >	XTAL_USE      ordinal_t = typename _entail::  ordinal<N>::type;
template <auto       N >	XTAL_USE      logical_t = typename _entail::  logical<N>::type;

template <class   ...Ts>	XTAL_ASK     constant_q = (...and  _entail::    constant_q<Ts>);
template <class   ...Ts>	XTAL_ASK   cointegral_q = (...and  _entail::  cointegral_q<Ts>);
template <class   ...Ts>	XTAL_ASK   cocardinal_q = (...and  _entail::  cocardinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK    coordinal_q = (...and  _entail::   coordinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK    cological_q = (...and  _entail::   cological_q<Ts>);

template <class   ...Ts>	XTAL_ASK     integral_q = (...and  _entail::    integral_q<Ts>);
template <class   ...Ts>	XTAL_ASK     cardinal_q = (...and  _entail::    cardinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      ordinal_q = (...and  _entail::     ordinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      logical_q = (...and  _entail::     logical_q<Ts>);

template <class   ...Ts>	XTAL_ASK     terminal_q = (...and  _entail::    terminal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      liminal_q = (...and  _entail::     liminal_q<Ts>);
template <liminal_q  T >	XTAL_USE   subliminal_s = typename _entail::  subliminal<T>::type;
template <liminal_q  T >	XTAL_USE  semiliminal_s = typename _entail:: semiliminal<T>::type;

template <int        N >	XTAL_USE   bisordinal_t = typename _entail:: bisordinal<N    >::type;
template <int     ...Ns>	XTAL_USE   fractional_t = typename _entail:: fractional<Ns...>::type;
template <int     ...Ns>	XTAL_LET   fractional_n =          _entail:: fractional<Ns...>::value;


template <class      T >	XTAL_USE        based_t =          _entail::   based_t<T>;
template <class   ...Ts>	XTAL_ASK        based_q = (...and  _entail::   based_q<Ts>);
template <class   ...Ts>	XTAL_ASK      unbased_q = (...and  _entail:: unbased_q<Ts>);

template <class      T >	XTAL_USE      rebased_t = typename _entail:: rebased<T>::type;
template <class      T >	XTAL_USE      debased_t = typename _entail:: debased<T>::type;
template <class      T >	XTAL_ASK      rebased_p =   (bool) _entail:: rebased<T>::value;
template <class      T >	XTAL_ASK      debased_p =   (bool) _entail:: debased<T>::value;
template <class   ...Ts>	XTAL_ASK      rebased_q = (...and  _entail:: rebased_q<Ts>);
template <class   ...Ts>	XTAL_ASK      debased_q = (...and  _entail:: debased_q<Ts>);


template <           class ...Ts>	XTAL_ASK      invalue_q = (...and  _entail:: invalue_q<Ts>);
template <           class ...Ts>	XTAL_USE      invalue_t = common_t<_entail:: invalue_t<Ts>...>;

template <           class ...Ts>	XTAL_ASK      unvalue_q = (...and  _entail:: unvalue_q<Ts>);
template <           class ...Ts>	XTAL_USE      unvalue_t = common_t<_entail:: unvalue_t<Ts>...>;

template <           class ...Ts>	XTAL_ASK      devalue_q = (...and  _entail:: devalue_q<Ts>);
template <           class ...Ts>	XTAL_USE      devalue_t = common_t<_entail:: devalue_t<Ts>...>;
template <class   T             >	XTAL_LET      devalue_n = _entail:: devalue_n<T>;

//mplate <           int   ...Ns>	XTAL_USE      devolve_x =	_entail:: devolve_x<   Ns...>;
//mplate <class   T, class ..._s>	XTAL_USE      devolve_s =	_entail:: devolve_s<T, _s...>;
template <class   T             >	XTAL_USE      devolve_a =	_entail:: devolve_a<T       >;
template <           class ...Ts>	XTAL_USE      devolve_t = common_t<_entail:: devolve_t<Ts>...>;
template <class   T             >	XTAL_LET      devolve_n = _entail:: devolve_n<T>;

template <class   T, class ...Ts>	XTAL_ASK     devalued_q = (...and (devalue_n<T> < devalue_n<Ts>));
template <class   T, class ...Ts>	XTAL_ASK     devalued_p = (...and (devalue_n<T> > devalue_n<Ts>));
template <class   T, class ...Ts>	XTAL_ASK     devolved_q = (...and (devolve_n<T> < devolve_n<Ts>));
template <class   T, class ...Ts>	XTAL_ASK     devolved_p = (...and (devolve_n<T> > devolve_n<Ts>));


////////////////////////////////////////////////////////////////////////////////

template <class T,   int   N=-1 >	XTAL_ASK     array_q =             _entail:: array_q<T> and N <  0   or devalue_n<T> == N;
template <class T,   int   N=-1 >	XTAL_ASK  subarray_q =             _entail:: array_q<T> and 0 <= N  and devalue_n<T> <= N;
template <           class ...Ts>	XTAL_ASK  disarray_q =        not (...and    array_q<Ts>);

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

template <class      ...Ts>	XTAL_ASK         bounded_q =	    (...and  _entail::    bounded_q<Ts>);
template <class      ...Ts>	XTAL_ASK       unbounded_q =	    (...and  _entail::  unbounded_q<Ts>);
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
