#pragma once

#include <range/v3/all.hpp>
#include <simde/arm/neon.h>
#if __has_include(<execution>)
#include <execution>
#endif
#include <complex>
#include <numbers>
#include <cmath>
#include <array>
#include <tuple>
#include <queue>
#include <new>
#include <bit>


#include "./etc.hh"


XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_entail.ii"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Standard...

using    null_type	= _entail::   null_type;
using    unit_type	= _entail::   unit_type;
using    size_type	= _entail::   size_type;
using  signum_type	= _entail:: signum_type;
using integer_type	= _entail::integer_type;

XTAL_LET_(size_type) size_0{0};
XTAL_LET_(size_type) size_1{1};
XTAL_LET_(size_type) size_2{2};
XTAL_LET_(size_type) size_3{3};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural...

template <auto  N, auto  ...Ms>	concept            in_n	=          _entail::     in_n<N, Ms...>;
template <auto  N, auto  ...Ms>	concept            un_n	=          _entail::     un_n<N, Ms...>;
template <auto  N, auto   Z=0 >	concept        signum_p	=          _entail:: signum_p<N, Z>;
template <auto  N, auto   Z=0 >	XTAL_LET       signum_n	=          _entail:: signum_n<N, Z>;
template <auto  N, auto   M   >	XTAL_LET          end_n	=          _entail::    end_n<N, M>;
template <auto  N, auto   M=0 >	XTAL_LET          top_n	=          _entail::    top_n<N, M>;

template <class          ...Ts>	concept          some_q	=          _entail:: some_q<Ts...>;
template <auto           ...Ns>	concept          some_n	=          _entail:: some_n<Ns...>;
template <class          ...Ts>	concept          none_q	=          _entail:: none_q<Ts...>;
template <auto           ...Ns>	concept          none_n	=          _entail:: none_n<Ns...>;

template <class          ...Ts>	concept    incomplete_q	= (...and  _entail:: incomplete_q<Ts   >);
template <class          ...Ts>	concept      complete_q	= (...and  _entail::   complete_q<Ts   >);
template <class          ...Ts>	using        complete_t	= typename _entail::   complete_t<Ts...>;

template <class          ...Ts>	concept        common_q	=          _entail::    common_q<Ts...>;//< `Ts...` share an ancestor.
template <class          ...Ts>	using          common_t	=          _entail::    common_t<Ts...>;


////////////////////////////////////////////////////////////////////////////////

template <         class ...Ts>	using       isotropic_t	= _entail::    isotropic <Ts...>;
template <         class ...Ts>	using       epitropic_t	= _entail::    epitropic <Ts...>;
template <         class ...Ts>	using     anisotropic_t	= _entail::  anisotropic <Ts...>;
template <         class ...Ts>	using     anepitropic_t	= _entail::  anepitropic <Ts...>;

template <         class ...Ts>	concept     isotropic_q	= _entail::    isotropic_q<Ts...>;
template <         class ...Ts>	concept     epitropic_q	= _entail::    epitropic_q<Ts...>;
template <         class ...Ts>	concept   anisotropic_q	= _entail::  anisotropic_q<Ts...>;
template <         class ...Ts>	concept   anepitropic_q	= _entail::  anepitropic_q<Ts...>;

template <         class ...Ts>	using      isomorphic_t	= _entail::   isomorphic <Ts...>;
template <         class ...Ts>	using      epimorphic_t	= _entail::   epimorphic <Ts...>;
template <         class ...Ts>	using    anisomorphic_t	= _entail:: anisomorphic <Ts...>;
template <         class ...Ts>	using    anepimorphic_t	= _entail:: anepimorphic <Ts...>;

template <         class ...Ts>	concept    isomorphic_q	= _entail::   isomorphic_q<Ts...>;
template <         class ...Ts>	concept    epimorphic_q	= _entail::   epimorphic_q<Ts...>;
template <         class ...Ts>	concept  anisomorphic_q	= _entail:: anisomorphic_q<Ts...>;
template <         class ...Ts>	concept  anepimorphic_q	= _entail:: anepimorphic_q<Ts...>;

template <         class ...Ts>	concept            id_q	= _entail:: id_q<   Ts...>;//< `Ts...` are identical.
template <         class ...Ts>	concept            is_q	= _entail:: is_q<   Ts...>;//< `Ts...` are identical modulo qualifiers.
template <         class ...Ts>	concept            as_q	= _entail:: as_q<   Ts...>;//< `Ts...` are constructible from `Ts[0]`.
template <class T, class ...Ts>	concept            as_p	= _entail:: as_p<T, Ts...>;

template <         class ...Ts>	concept      fungible_q	= _entail::   fungible_q<Ts...>; //< `T` and `Ts...` are   related by inheritance.
template <         class ...Ts>	concept    infungible_q	= _entail:: infungible_q<Ts...>; //< `T` and `Ts...` are unrelated by inheritance.

template <class X, class ...Fs>	concept    idempotent_p	=  (...and _entail:: idempotent_p<X, Fs>);//< `X` is unchanged by `Fs...`.
template <class F, class    X >	concept    idempotent_q	=  idempotent_p<X, F>;


////////////////////////////////////////////////////////////////////////////////

template <auto N              >	using        constant_t	= typename _entail::     constant_t<N >;
template <class          ...Ts>	concept      constant_q	= (...and  _entail::     constant_q<XTAL_RAW_(Ts)>);

template <         class ...Ts>	concept       logical_q	= (...and  _entail::      logical_q<XTAL_RAW_(Ts)>);
template <         class ...Ts>	concept       ordinal_q	= (...and  _entail::      ordinal_q<XTAL_RAW_(Ts)>);
template <         class ...Ts>	concept      cardinal_q	= (...and  _entail::     cardinal_q<XTAL_RAW_(Ts)>);
template <         class ...Ts>	concept      integral_q	= (...and  _entail::     integral_q<XTAL_RAW_(Ts)>);

template <class T, class ...Xs>	concept       logical_p	=          _entail::      logical_p<T, Xs...>;
template <class T, class ...Xs>	concept       ordinal_p	=          _entail::      ordinal_p<T, Xs...>;
template <class T, class ...Xs>	concept      cardinal_p	=          _entail::     cardinal_p<T, Xs...>;
template <class T, class ...Xs>	concept      integral_p	=          _entail::     integral_p<T, Xs...>;

template <class          ...Ts>	concept     unnatural_q	= (...and  _entail::    unnatural_q<XTAL_RAW_(Ts)>);
template <class          ...Ts>	concept       natural_q	= (...and  _entail::      natural_q<XTAL_RAW_(Ts)>);
template <class          ...Ts>	concept      terminal_q	= (...and  _entail::     terminal_q<XTAL_RAW_(Ts)>);
template <class          ...Ts>	concept       liminal_q	= (...and  _entail::      liminal_q<XTAL_RAW_(Ts)>);
template <liminal_q T         >	using      subliminal_s	= typename _entail::   subliminal_s<T >;
template <liminal_q T         >	using    superliminal_s	= typename _entail:: superliminal_s<T >;


template <class T             >	using           based_t	=          _entail::    based_t<T>;
template <class          ...Ts>	concept         based_q	= (...and  _entail::    based_q<Ts>);
template <class          ...Ts>	concept       unbased_q	= (...and  _entail::  unbased_q<Ts>);


template <class T             >	XTAL_LET  tuple_sized_n	=          _entail::   tuple_sized_n<T >;
template <class T             >	using     tuple_sized_t	=          _entail::   tuple_sized_t<T >;
template <         class ...Ts>	concept   tuple_sized_q	= (...and  _entail::   tuple_sized_q<Ts>);

template <class T             >	XTAL_LET  array_sized_n	=          _entail::   tuple_sized_n<T >;
template <class T             >	using     array_sized_t	=          _entail::   tuple_sized_t<T >;
template <         class ...Ts>	concept   array_sized_q	= (...and  _entail::   tuple_sized_q<Ts>);

template <class T             >	using           sized  	=          _entail::         sized  <T >;
template <class T             >	XTAL_LET        sized_n	=          _entail::         sized_n<T >;
template <class T             >	using           sized_t	=          _entail::         sized_t<T >;
template <         class ...Ts>	concept         sized_q	= (...and  _entail::         sized_q<Ts>);


template <         class ...Ts>	using    inner_valued_u	= common_t<_entail::   inner_valued_u<Ts>...>;
template <         class ...Ts>	concept  inner_valued_q	= (...and  _entail::   inner_valued_q<Ts>);

template <         class ...Ts>	using    array_valued_u	= common_t<_entail::   array_valued_u<Ts>...>;
template <         class ...Ts>	concept  array_valued_q	= (...and  _entail::   array_valued_q<Ts>);

template <         class ...Ts>	using          valued_u	= common_t<_entail::   valued_u<Ts>...>;
template <         class ...Ts>	concept        valued_q	= (...and  _entail::   valued_q<Ts>);


template <         class ...Ts>	concept      apart_q	= (...and  _entail:: apart_q<Ts>);
template <class T             >	using        apart_t	=          _entail:: apart_t<T >;
template <         class ...Ts>	using        apart_u	= common_t<_entail:: apart_u<Ts>...>;
template <class T             >	XTAL_LET     apart_n	= _entail:: apart_n<T>;
template <class T, class ...Ts>	concept      apart_p	= (...and (apart_n<T> < apart_n<Ts>));

template <class T, int   ...Ns>	using        devolved  	= _entail:: devolved  <T, Ns...>;
//mplate <         int   ...Ns>	using        devolved_x	= _entail:: devolved_x<   Ns...>;
//mplate <class T, class ..._s>	using        devolved_s	= _entail:: devolved_s<T, _s...>;
template <class T             >	XTAL_LET     devolved_n	= _entail:: devolved_n<T>;
template <         class ...Ts>	using        devolved_u	= common_t<_entail:: devolved_u<Ts>...>;
template <class T             >	using        devolved_t	=          _entail:: devolved_t<T >;
template <class T, class ...Ts>	concept      devolved_p	= (...and (devolved_n<T> < devolved_n<Ts>));


////////////////////////////////////////////////////////////////////////////////

template <         class ...Ts>	concept        column_q	=  (...and _entail:: column_q<Ts>);
template <class T, int   N=-1 >	concept         array_q	=          _entail::  array_q<T> and N <  0   or apart_n<T> == N;
template <class T, int   N=-1 >	concept      subarray_q	=          _entail::  array_q<T> and 0 <= N  and apart_n<T> <= N;
template <         class ...Ts>	concept      disarray_q	=        not (...and  array_q<Ts>);

template <class          ...Ts>	concept       indexed_q	= (... and _entail:: indexed_q<Ts>);
template <class          ...Ts>	concept       pointed_q	= (... and _entail:: pointed_q<Ts>);
template <class             T >	using         indexed_u	=          _entail:: indexed_u<T >;
template <class             T >	using         pointed_u	=          _entail:: pointed_u<T >;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Ranged...

template <class T             >	using         pointed_u	=          _entail:: pointed_u<T >;
template <class T             >	using        arranged_t	=               _entail::     arranged_t<T >;
template <class T             >	using      reiterated_t	=               _entail::     reiterated_t<T >;

template <class T             >	using     initializer_u	=               _entail::  initializer_u<T > ;
template <class T             >	using     initializer_t	=               _entail::  initializer_t<T > ;
template <class T             >	using        iteratee_t	=      typename _entail::     iteratee  <T >::type;
template <class T             >	using        iterated_t	=      typename _entail::     iterated  <T >::type;
template <class T             >	using        iterator_t	=      typename _entail::     iterator  <T >::type;
template <class T             >	using        distance_t	=               _entail::     distance_t<T > ;
template <class T             >	using        interval_t	=               _entail::     interval_t<T > ;
template <class T=integer_type>	using         counted_t	=      typename _entail::      counted  <T >::type;
template <class T=integer_type>	using         counter_t	=      typename _entail::      counter  <T >::type;

template <class          ...Ts>	concept   initializer_q	=      (...and  _entail::  initializer_q<Ts>);
template <class          ...Ts>	concept      iteratee_q	=      (...and  _entail::     iteratee_q<Ts>);
template <class          ...Ts>	concept      iterable_q	=      (...and  _entail::     iterable_q<Ts>);
template <class          ...Ts>	concept      iterated_q	=      (...and  _entail::     iterated_q<Ts>);
template <class          ...Ts>	concept      iterator_q	=      (...and  _entail::     iterator_q<Ts>);
template <class          ...Ts>	concept      sentinel_q	=      (...and  _entail::     sentinel_q<Ts>);
template <class          ...Ts>	concept      distance_q	=      (...and  _entail::     distance_q<Ts>);
template <class          ...Ts>	concept      interval_q	=      (...and  _entail::     interval_q<Ts>);
template <class          ...Ts>	concept       counted_q	=      (...and  _entail::      counted_q<Ts>);
template <class          ...Ts>	concept       counter_q	=      (...and  _entail::      counter_q<Ts>);

template <class          ...Ts>	concept      collated_q	=      (...and  _entail::    collated_q<Ts>);
template <class          ...Ts>	concept    correlated_q	=      (...and  _entail::  correlated_q<Ts>);
template <class          ...Ts>	concept  uncorrelated_q	=      (...and  _entail::uncorrelated_q<Ts>);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Arithmetic...

template <class ...Ts>	concept           number_q	= (...and  _entail::          number_q<Ts>);
template <class ...Ts>	concept      real_number_q	= (...and  _entail::     real_number_q<Ts>);
template <class ...Ts>	concept   complex_number_q	= (...and  _entail::  complex_number_q<Ts>);
template <class ...Ts>	concept   simplex_number_q	= (...and  _entail::  simplex_number_q<Ts>);
template <class ...Ts>	concept          integer_q	= (...and  _entail::         integer_q<Ts>);
template <class ...Ts>	concept          boolean_q	= (...and  _entail::         boolean_q<Ts>);


template <size_type N, class T, class U=T>	concept  multiplicative_group_p	= _entail:: multiplicative_group_p<N, T, U>;
template <size_type N, class T, class U=T>	concept        additive_group_p	= _entail::       additive_group_p<N, T, U>;
template <size_type N, class T, class U=T>	concept        discrete_group_p	= _entail::       discrete_group_p<N, T, U>;
template <size_type N, class T, class U=T>	concept        quotient_group_p	= _entail::       quotient_group_p<N, T, U>;
template <size_type N, class T, class U=T>	concept        integral_group_p	= _entail::       integral_group_p<N, T, U>;

template <size_type N, class T, class U=T>	concept      contiguous_group_p	= _entail::     contiguous_group_p<N, T, U>;
template <size_type N, class T, class U=T>	concept      contiguous_field_p	= _entail::     contiguous_field_p<N, T, U>;
template <size_type N, class T, class U=T>	concept      continuous_field_p	= _entail::     continuous_field_p<N, T, U>;
template <size_type N, class T, class U=T>	concept         complex_field_p	= _entail::        complex_field_p<N, T, U>;
template <size_type N, class T, class U=T>	concept         simplex_field_p	= _entail::        simplex_field_p<N, T, U>;

template <size_type N, class T, class U=T>	concept       boolean_quantity_p	= _entail::      boolean_quantity_p<N, T, U>;
template <size_type N, class T, class U=T>	concept        binary_quantity_p	= _entail::       binary_quantity_p<N, T, U>;

template <size_type N, class T, class U=T>	concept            inequality_p	= _entail::           inequality_p<N, T, U>;
template <size_type N, class T, class U=T>	concept              equality_p	= _entail::             equality_p<N, T, U>;
template <size_type N, class T, class U=T>	concept               quality_p	= _entail::              quality_p<N, T, U>;


template <class   ...Ts>	concept   multiplicative_group_q	= (...and multiplicative_group_p<0, Ts>);
template <class   ...Ts>	concept         additive_group_q	= (...and       additive_group_p<0, Ts>);
template <class   ...Ts>	concept         discrete_group_q	= (...and       discrete_group_p<0, Ts>);
template <class   ...Ts>	concept         quotient_group_q	= (...and       quotient_group_p<0, Ts>);
template <class   ...Ts>	concept         integral_group_q	= (...and       integral_group_p<0, Ts>);

template <class   ...Ts>	concept       contiguous_group_q	= (...and     contiguous_group_p<0, Ts>);
template <class   ...Ts>	concept       contiguous_field_q	= (...and     contiguous_field_p<0, Ts>);
template <class   ...Ts>	concept       continuous_field_q	= (...and     continuous_field_p<0, Ts>);
template <class   ...Ts>	concept          complex_field_q	= (...and        complex_field_p<0, Ts>);
template <class   ...Ts>	concept          simplex_field_q	= (...and        simplex_field_p<0, Ts>);

template <class   ...Ts>	concept       boolean_quantity_q	= (...and      boolean_quantity_p<0, Ts>);
template <class   ...Ts>	concept        binary_quantity_q	= (...and       binary_quantity_p<0, Ts>);

template <class   ...Ts>	concept             inequality_q	= (...and           inequality_p<2, Ts>);
template <class   ...Ts>	concept               equality_q	= (...and             equality_p<2, Ts>);
template <class   ...Ts>	concept                quality_q	= (...and              quality_p<2, Ts>);


static_assert(            contiguous_field_q<float>);
static_assert(               simplex_field_q<float>);
static_assert(          not  complex_field_q<float>);
static_assert(          not quotient_group_q<float>);
static_assert(              quotient_group_q<  int>);
static_assert(complex_field_q<_std::complex<float>>);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <auto    ...Ns>	using      lateral_t	= typename _entail::lateral<common_t<XTAL_ALL_(Ns)...>, Ns...>::type;
template <auto    ...Ns>	XTAL_LET   lateral_n	=          _entail::lateral<common_t<XTAL_ALL_(Ns)...>, Ns...>::type::value;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./any.ii"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
