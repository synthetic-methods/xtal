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


#include "./_retail.ii"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Standard...

XTAL_USE null_t = _retail:: null_t;
XTAL_USE unit_t = _retail:: unit_t;
XTAL_USE sign_t = _retail:: sign_t;
XTAL_USE byte_t = _retail:: byte_t;
XTAL_USE size_t = _retail:: size_t;
XTAL_USE size_s = _retail:: size_s;
XTAL_USE real_s = _retail:: real_s;

XTAL_LET size_0 = _retail:: size_0;
XTAL_LET size_1 = _retail:: size_1;


template <auto    N, auto  ...Ms>	XTAL_ASK      exclusive_p = _retail::exclusive_p<N, Ms... >;
template <auto    N, auto  ...Ms>	XTAL_ASK      inclusive_p = _retail::inclusive_p<N, Ms... >;
template <auto    N, auto  N_0=0>	XTAL_ASK           sign_p = _retail::     sign_p<N, N_0>;
template <auto    N, auto  N_0=0>	XTAL_LET           sign_n = _retail::     sign_n<N, N_0>;

template <class            ...Ts>	XTAL_ASK           some_q = _retail::     some_q<Ts...>;
template <auto             ...Ns>	XTAL_ASK           some_n = _retail::     some_n<Ns...>;
template <class            ...Ts>	XTAL_ASK           none_q = _retail::     none_q<Ts...>;
template <auto             ...Ns>	XTAL_ASK           none_n = _retail::     none_n<Ns...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural...

template <class            ...Ts>	XTAL_ASK     incomplete_q =	(...and  _retail:: incomplete_q<Ts   >);
template <class            ...Ts>	XTAL_ASK       complete_q =	(...and  _retail::   complete_q<Ts   >);
template <class            ...Ts>	XTAL_USE       complete_t =	typename _retail::   complete_t<Ts...>;

template <class            ...Ts>	XTAL_ASK         common_q =	some_q<Ts...> and _retail:: common_q<Ts...>;//< `Ts...` share an ancestor.
template <class            ...Ts>	XTAL_USE         common_t =	                  _retail:: common_t<Ts...>;


////////////////////////////////////////////////////////////////////////////////

template <           class ...Ts>	XTAL_ASK      isotropic_q =	        _retail::  isotropic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK      epitropic_q =	        _retail::  epitropic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK    anisotropic_q =	    not _retail::  isotropic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK    anepitropic_q =	    not _retail::  epitropic<Ts...>::value;

template <           class ...Ts>	XTAL_ASK     isomorphic_q =	        _retail:: isomorphic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK     epimorphic_q =	        _retail:: epimorphic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK   anisomorphic_q =	    not _retail:: isomorphic<Ts...>::value;
template <           class ...Ts>	XTAL_ASK   anepimorphic_q =	    not _retail:: epimorphic<Ts...>::value;

template <           class ...Ts>	XTAL_ASK             id_q =	        _retail:: identical<Ts...>::value;//< `Ts...` are identical.
template <           class ...Ts>	XTAL_ASK             is_q =	        _retail:: isotropic<Ts...>::value;//< `Ts...` are identical modulo qualifiers.
template <           class ...Ts>	XTAL_ASK             as_q =	        _retail:: epitropic<Ts...>::value;//< `Ts...` are constructible from `Ts[0]`.
template <class   T, class ...Ts>	XTAL_ASK             as_p =	        _retail:: as_p<T, Ts...>;

template <class   T, class ...Ts>	XTAL_ASK       fungible_q =	some_q<Ts...> and (...and _retail::   fungible_q<T, Ts>);//< `T` and `Ts...` are   related by inheritance.
template <class   T, class ...Ts>	XTAL_ASK     infungible_q =	some_q<Ts...> and (...and _retail:: infungible_q<T, Ts>);//< `T` and `Ts...` are unrelated by inheritance.


////////////////////////////////////////////////////////////////////////////////

XTAL_USE cardinal_0 = _retail:: cardinal<0>::type;
XTAL_USE cardinal_1 = _retail:: cardinal<1>::type;
XTAL_USE  ordinal_0 = _retail::  ordinal<0>::type;
XTAL_USE  ordinal_1 = _retail::  ordinal<1>::type;
XTAL_USE  logical_0 = _retail::  ordinal<0>::type;
XTAL_USE  logical_1 = _retail::  ordinal<1>::type;

template <auto       N >	XTAL_USE     constant_t = typename _retail:: constant<N>::type;
template <auto       N >	XTAL_USE     cardinal_t = typename _retail:: cardinal<N>::type;
template <auto       N >	XTAL_USE      ordinal_t = typename _retail::  ordinal<N>::type;
template <auto       N >	XTAL_USE      logical_t = typename _retail::  logical<N>::type;

template <class   ...Ts>	XTAL_ASK     constant_q = (...and  _retail::  constant_q<Ts>);
template <class   ...Ts>	XTAL_ASK     integral_q = (...and  _retail::  integral_q<Ts>);
template <class   ...Ts>	XTAL_ASK     cardinal_q = (...and  _retail::  cardinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      ordinal_q = (...and  _retail::   ordinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      logical_q = (...and  _retail::   logical_q<Ts>);

template <class   ...Ts>	XTAL_ASK     integral_p = (...and  _retail::  integral_p<Ts>);
template <class   ...Ts>	XTAL_ASK     cardinal_p = (...and  _retail::  cardinal_p<Ts>);
template <class   ...Ts>	XTAL_ASK      ordinal_p = (...and  _retail::   ordinal_p<Ts>);
template <class   ...Ts>	XTAL_ASK      logical_p = (...and  _retail::   logical_p<Ts>);

template <class   ...Ts>	XTAL_ASK     terminal_q = (...and  _retail::    terminal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      liminal_q = (...and  _retail::     liminal_q<Ts>);
template <liminal_q  T >	XTAL_USE   subliminal_s = typename _retail::  subliminal<T>::type;
template <liminal_q  T >	XTAL_USE  semiliminal_s = typename _retail:: semiliminal<T>::type;

template <int        N >	XTAL_USE   bisordinal_t = typename _retail:: bisordinal<N    >::type;
template <int     ...Ns>	XTAL_USE   fractional_t = typename _retail:: fractional<Ns...>::type;
template <int     ...Ns>	XTAL_LET   fractional_n =          _retail:: fractional<Ns...>::value;


template <class      T >	XTAL_USE        based_t =          _retail::   based_t<T>;
template <class   ...Ts>	XTAL_ASK        based_q = (...and  _retail::   based_q<Ts>);
template <class   ...Ts>	XTAL_ASK      unbased_q = (...and  _retail:: unbased_q<Ts>);

template <class      T >	XTAL_USE      rebased_t = typename _retail:: rebased<T>::type;
template <class      T >	XTAL_USE      debased_t = typename _retail:: debased<T>::type;
template <class      T >	XTAL_ASK      rebased_p =   (bool) _retail:: rebased<T>::value;
template <class      T >	XTAL_ASK      debased_p =   (bool) _retail:: debased<T>::value;
template <class   ...Ts>	XTAL_ASK      rebased_q = (...and  _retail:: rebased_q<Ts>);
template <class   ...Ts>	XTAL_ASK      debased_q = (...and  _retail:: debased_q<Ts>);


template <           class ...Ts>	XTAL_ASK      invalue_q = (...and  _retail:: invalue_q<Ts>);
template <           class ...Ts>	XTAL_USE      invalue_u = common_t<_retail:: invalue_u<Ts>...>;

template <           class ...Ts>	XTAL_ASK      unvalue_q = (...and  _retail:: unvalue_q<Ts>);
template <           class ...Ts>	XTAL_USE      unvalue_u = common_t<_retail:: unvalue_u<Ts>...>;

template <           class ...Ts>	XTAL_ASK      devalue_q = (...and  _retail:: devalue_q<Ts>);
template <           class ...Ts>	XTAL_USE      devalue_u = common_t<_retail:: devalue_u<Ts>...>;
template <class   T             >	XTAL_LET      devalue_n = _retail:: devalue_n<T>;

//mplate <           int   ...Ns>	XTAL_USE      devolve_x =	_retail:: devolve_x<   Ns...>;
//mplate <class   T, class ..._s>	XTAL_USE      devolve_s =	_retail:: devolve_s<T, _s...>;
template <class   T             >	XTAL_USE      devolve_t =	_retail:: devolve_t<T       >;
template <           class ...Ts>	XTAL_USE      devolve_u = common_t<_retail:: devolve_u<Ts>...>;
template <class   T             >	XTAL_LET      devolve_n = _retail:: devolve_n<T>;

template <class   T, class ...Ts>	XTAL_ASK     devalued_q = (...and (devalue_n<T> < devalue_n<Ts>));
template <class   T, class ...Ts>	XTAL_ASK     devalued_p = (...and (devalue_n<T> > devalue_n<Ts>));
template <class   T, class ...Ts>	XTAL_ASK     devolved_q = (...and (devolve_n<T> < devolve_n<Ts>));
template <class   T, class ...Ts>	XTAL_ASK     devolved_p = (...and (devolve_n<T> > devolve_n<Ts>));


////////////////////////////////////////////////////////////////////////////////

template <class T,   int   N=-1 >	XTAL_ASK     array_q =             _retail:: array_q<T> and N <  0   or devalue_n<T> == N;
template <class T,   int   N=-1 >	XTAL_ASK  subarray_q =             _retail:: array_q<T> and 0 <= N  and devalue_n<T> <= N;
template <           class ...Ts>	XTAL_ASK  disarray_q =        not (...and    array_q<Ts>);

template <class            ...Ts>	XTAL_ASK  accessed_q = (... and _retail:: accessed_q<Ts>);
template <class            ...Ts>	XTAL_ASK   pointer_q = (... and _retail::  pointer_q<Ts>);
template <class               T >	XTAL_USE  accessed_t =          _retail:: accessed_t<T >;
template <class               T >	XTAL_USE   pointer_t =          _retail::  pointer_t<T >;
template <class               T >	XTAL_USE   pointee_t =          _retail::  pointee_t<T >;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Ranged...

template <class      ...Ts>	XTAL_ASK        sizeable_q = (...and  _retail::   sizeable_q<Ts>);
template <class      ...Ts>	XTAL_ASK      resizeable_q = (...and  _retail:: resizeable_q<Ts>);

template <class      ...Ts>	XTAL_ASK         bounded_q = (...and  _retail::    bounded_q<Ts>);
template <class      ...Ts>	XTAL_ASK       unbounded_q = (...and  _retail::  unbounded_q<Ts>);
template <class      ...Ts>	XTAL_ASK       reembrace_q = (...and  _retail::  reembrace_q<Ts>);
template <class         T >	XTAL_USE       reembrace_t =          _retail::  reembrace_t<T >;
template <class         T >	XTAL_USE         embrace_t =          _retail::    embrace_t<T >;

template <class         T >	XTAL_USE        interval_t =          _retail::   interval_t<T >;
template <class         T >	XTAL_USE        iterated_t = typename _retail::   iterated  <T >::type;
template <class         T >	XTAL_USE        iterator_t = typename _retail::   iterator  <T >::type;
template <class         T >	XTAL_USE        iteratee_t = typename _retail::   iteratee  <T >::type;
template <class         T >	XTAL_USE        distance_t =          _retail::   distance_t<T >;

template <class      ...Ts>	XTAL_ASK        iteratee_q = (...and  _retail::   iteratee_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterable_q = (...and  _retail::   iterable_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterated_q = (...and  _retail::   iterated_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterator_q = (...and  _retail::   iterator_q<Ts>);
template <class      ...Ts>	XTAL_ASK        sentinel_q = (...and  _retail::   sentinel_q<Ts>);
template <class      ...Ts>	XTAL_ASK        distance_q = (...and  _retail::   distance_q<Ts>);

template <class      ...Ts>	XTAL_ASK         counted_q = (...and  _retail::    counted_q<Ts>);
template <class      ...Ts>	XTAL_ASK         counter_q = (...and  _retail::    counter_q<Ts>);

template <class   T=size_s>	XTAL_USE         counted_t = typename _retail::    counted  <T >::type;
template <class   T=size_s>	XTAL_USE         counter_t = typename _retail::    counter  <T >::type;

template <class         T >	XTAL_USE      reiterated_t =          _retail:: reiterated_t<T >;
template <class         T >	XTAL_USE      initerated_t =          _retail:: initerated_t<T >;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Arithmetic...

template <class      T >	XTAL_USE            numeric_t =              _retail::         numeric_t<T >;
template <class   ...Ts>	XTAL_ASK            numeric_q =     (...and  _retail::         numeric_q<Ts>);
template <class   ...Ts>	XTAL_ASK             number_q =     (...and  _retail::          number_q<Ts>);
template <class   ...Ts>	XTAL_ASK        real_number_q =     (...and  _retail::     real_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK      unreal_number_q = not (...and  _retail::     real_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK     complex_number_q =     (...and  _retail::  complex_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK    integral_number_q =     (...and  _retail:: integral_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK disintegral_number_q = not (...and  _retail:: integral_number_q<Ts>);


template <size_t N, class T, class U=T>	XTAL_ASK multiplicative_group_p = _retail:: multiplicative_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       additive_group_p = _retail::       additive_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       discrete_group_p = _retail::       discrete_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       quotient_group_p = _retail::       quotient_group_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       integral_group_p = _retail::       integral_group_p<N, T, U>;

template <size_t N, class T, class U=T>	XTAL_ASK     contiguous_field_p = _retail::     contiguous_field_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK     continuous_field_p = _retail::     continuous_field_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK        complex_field_p = _retail::        complex_field_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK        simplex_field_p = _retail::        simplex_field_p<N, T, U>;

template <size_t N, class T, class U=T>	XTAL_ASK      boolean_lattice_p = _retail::      boolean_lattice_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK       binary_lattice_p = _retail::       binary_lattice_p<N, T, U>;

template <size_t N, class T, class U=T>	XTAL_ASK           inequality_p = _retail::           inequality_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK             equality_p = _retail::             equality_p<N, T, U>;
template <size_t N, class T, class U=T>	XTAL_ASK              quality_p = _retail::              quality_p<N, T, U>;


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

template <auto    ...Ns>	XTAL_USE   lateral_t = typename _retail::lateral<common_t<XTAL_TYP_(Ns)...>, Ns...>::type;
template <auto    ...Ns>	XTAL_LET   lateral_n =          _retail::lateral<common_t<XTAL_TYP_(Ns)...>, Ns...>::type::value;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./any.ii"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
