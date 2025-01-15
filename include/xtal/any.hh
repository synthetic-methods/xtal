#pragma once

#include <range/v3/all.hpp>
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

using extent_type =        _entail:: extent_type;
using   size_type =        _entail::   size_type;
using   sign_type =        _entail::   sign_type;
using   null_type =        _entail::   null_type;
class   void_type ;
//ing   unit_type =        _entail::   unit_type;
class   unit_type : public _entail::   unit_type
{
	using S_ = _entail::unit_type;

public:
	using S_::S_;

};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural...

template <         class ...Ts>	concept     isotropic_q	=          _entail::      isotropic<   Ts...>::value;
template <         class ...Ts>	concept     epitropic_q	=          _entail::      epitropic<   Ts...>::value;
template <         class ...Ts>	concept    isomorphic_q	=          _entail::     isomorphic<   Ts...>::value;
template <         class ...Ts>	concept    epimorphic_q	=          _entail::     epimorphic<   Ts...>::value;

template <         class ...Ts>	concept      fungible_q	=          _entail::     fungible_q<   Ts...>; //< `T` and `Ts...` are   related by inheritance.
template <         class ...Ts>	concept    infungible_q	=          _entail::   infungible_q<   Ts...>; //< `T` and `Ts...` are unrelated by inheritance.


template <class T             >	using           based_t	=          _entail::        based_t<T       > ;
template <         class ...Ts>	concept         based_q	=  (...and _entail::        based_q<   Ts   >);
template <         class ...Ts>	concept       unbased_q	=  (...and _entail::      unbased_q<   Ts   >);

template <         class ...Ts>	using          common_t	=          _entail::       common_t<   Ts...>;
template <         class ...Ts>	concept        common_q	=          _entail::       common_q<   Ts...>;


template <class T             >	using        identity_t	=          _entail::     identity_t<T       >;
template <class T             >	using        identity_u	=          _entail::     identity_u<T       >;
template <class T             >	XTAL_LET     identity_n	=          _entail::     identity_n<T       >;
template <class T             >	concept      identity_q	=          _entail::     identity_q<T       >;

template <         class ...Ts>	using        complete_t	= typename _entail::     complete_t<   Ts...> ;
template <         class ...Ts>	concept      complete_q	=  (...and _entail::     complete_q<   Ts   >);
template <         class ...Ts>	concept    incomplete_q	=  (...and _entail::   incomplete_q<   Ts   >);

template <         class ...Ts>	concept     molecular_q	=  (...and _entail::    molecular_q<   Ts   >);
template <         class ...Ts>	concept        atomic_q	=  (...and _entail::       atomic_q<   Ts   >);


template <         class ...Ts>	concept     different_q	=          _entail::    different_q<   Ts...>;//< `Ts...` are different modulo qualifiers.
template <         class ...Ts>	concept          same_q	=          _entail::         same_q<   Ts...>;//< `Ts...` are identical modulo qualifiers.
template <         class ...Ts>	concept          make_q	=          _entail::         make_q<   Ts...>;//< `Ts...` are constructible from `Ts[0]`.
template <class T, class ...Ts>	concept          make_p	=          _entail::         make_p<T, Ts...>;//< `T` is constructible from `Ts...`.

template <class F, class ...Xs>	using          return_t	=          _entail::       return_t<F, Xs...>;
template <class F, class ...Xs>	concept    applicable_p	=          _entail::   applicable_p<F, Xs...>;
template <class F, class ...Xs>	concept  inapplicable_p	=          _entail:: inapplicable_p<F, Xs...>;

template <class F, class ...Xs>	concept  automorphism_p	=  (...and _entail:: automorphism_p<F, Xs   >);//< `Xs` are unchanged by `F ...`.
template <class X, class ...Fs>	concept  automorphism_q	=  (...and _entail:: automorphism_q<X, Fs   >);//< `X `  is unchanged by `Fs...`.


///\
Resolves the given CRTP `template` as a type. \

template <template <class> class T_>
using derive_t	= typename _entail::derive<T_>::type;


///\
Defines a factory for the supplied type. \

template <class T>
XTAL_LET invoke_n = _entail::invoke_n<T>;

template <class T>
using    invoke_t = decltype(invoke_n<T>);

template <class T, class ...Xs>
concept  invoke_p = _std::invocable<invoke_t<T>, Xs...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Valued...

template <auto  N, auto   Z=0 >	XTAL_LET       sign_n	=          _entail::          sign_n<N, Z    >;
template <auto  M, auto     N >	XTAL_LET       modulo_m	=          _entail::          modulo_m<M, N    >;
template <auto  M, auto     N >	XTAL_LET        above_m	=          _entail::           above_m<M, N    >;
template <auto  M, auto     N >	XTAL_LET        below_m	=          _entail::           below_m<M, N    >;
template <auto  M, auto  ...Ns>	concept         above_p =          _entail::           above_p<M, Ns...>;
template <auto  M, auto  ...Ns>	concept         below_p =          _entail::           below_p<M, Ns...>;
template <auto  N, auto  ...Ms>	concept            in_n	=          _entail::              in_n<N, Ms...>;
template <auto  N, auto  ...Ms>	concept            un_n	=          _entail::              un_n<N, Ms...>;
template <class T, class ...Ts>	concept            in_q	=          _entail::              in_q<T, Ts...>;
template <class T, class ...Ts>	concept            un_q	=          _entail::              un_q<T, Ts...>;

template <auto   N=null_type{}>	using        constant_t	= typename _entail::     constant_t<N >;
template <class          ...Ts>	concept      constant_q	=  (...and _entail::     constant_q<XTAL_RAW_(Ts)>);
template <class          ...Ts>	concept      variable_q	=  (...and _entail::     variable_q<XTAL_RAW_(Ts)>);

template <class 	 ...Ts>  concept   integral_variable_q	=  (...and _entail:: integral_variable_q<   Ts   >);
template <class 	 ...Ts>  concept   cardinal_variable_q	=  (...and _entail:: cardinal_variable_q<   Ts   >);
template <class 	 ...Ts>  concept    ordinal_variable_q	=  (...and _entail::  ordinal_variable_q<   Ts   >);
template <class 	 ...Ts>  concept    logical_variable_q	=  (...and _entail::  logical_variable_q<   Ts   >);
template <class 	 ...Ts>  concept       real_variable_q	=  (...and _entail::     real_variable_q<   Ts   >);
template <class 	 ...Ts>  concept    complex_variable_q	=  (...and _entail::  complex_variable_q<   Ts   >);
template <class 	 ...Ts>  concept    simplex_variable_q	=  (...and _entail::  simplex_variable_q<   Ts   >);
template <class 	 ...Ts>  concept    anyplex_variable_q	=  (...and _entail::  anyplex_variable_q<   Ts   >);

template <class 	 ...Ts>  concept   integral_constant_q	=  (...and _entail:: integral_constant_q<   Ts   >);
template <class 	 ...Ts>  concept   cardinal_constant_q	=  (...and _entail:: cardinal_constant_q<   Ts   >);
template <class 	 ...Ts>  concept    ordinal_constant_q	=  (...and _entail::  ordinal_constant_q<   Ts   >);
template <class 	 ...Ts>  concept    logical_constant_q	=  (...and _entail::  logical_constant_q<   Ts   >);
template <class 	 ...Ts>  concept       real_constant_q	=  (...and _entail::     real_constant_q<   Ts   >);
template <class 	 ...Ts>  concept    complex_constant_q	=  (...and _entail::  complex_constant_q<   Ts   >);
template <class 	 ...Ts>  concept    simplex_constant_q	=  (...and _entail::  simplex_constant_q<   Ts   >);
template <class 	 ...Ts>  concept    anyplex_constant_q	=  (...and _entail::  anyplex_constant_q<   Ts   >);

template <class       ...Ts>	concept         integral_q	=  (...and _entail::     integral_q<Ts>);
template <class       ...Ts>	concept         cardinal_q	=  (...and _entail::     cardinal_q<Ts>);
template <class       ...Ts>	concept          ordinal_q	=  (...and _entail::      ordinal_q<Ts>);
template <class       ...Ts>	concept          logical_q	=  (...and _entail::      logical_q<Ts>);
template <class 	    ...Ts>  concept             real_q	=  (...and _entail::         real_q<Ts>);
template <class 	    ...Ts>  concept          complex_q	=  (...and _entail::      complex_q<Ts>);
template <class 	    ...Ts>  concept          simplex_q	=  (...and _entail::      simplex_q<Ts>);
template <class 	    ...Ts>  concept          anyplex_q	=  (...and _entail::      anyplex_q<Ts>);
template <class 	    ...Ts>  concept           number_q	=                         anyplex_variable_q<Ts...>;

template <class          ...Ts>	concept       liminal_q	=  (...and _entail::      liminal_q<XTAL_RAW_(Ts)>);
template <class          ...Ts>	concept      terminal_q	=  (...and _entail::     terminal_q<XTAL_RAW_(Ts)>);
template <liminal_q T         >	using      subliminal_s	= typename _entail::   subliminal_s<T >;
template <liminal_q T         >	using    superliminal_s	= typename _entail:: superliminal_s<T >;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Valued & Sized...

template <class T             >	using         pointee_t	=          _entail::      pointee_t<T >;
template <class T             >	using         pointed_u	=          _entail::      pointed_u<T >;
template <class          ...Ts>	concept       pointed_q	= (... and _entail::      pointed_q<Ts>);

template <class T             >	using         indexee_t	=          _entail::      indexee_t<T >;
template <class T             >	using         indexed_u	=          _entail::      indexed_u<T >;
template <class          ...Ts>	concept       indexed_q	= (... and _entail::      indexed_q<Ts>);

template <         class ...Ts>	using    array_valued_u	= common_t<_entail::   array_valued_u<Ts>...>;
template <         class ...Ts>	concept  array_valued_q	=  (...and _entail::   array_valued_q<Ts>);

template <         class ...Ts>	using    inner_valued_u	= common_t<_entail::   inner_valued_u<Ts>...>;
template <         class ...Ts>	concept  inner_valued_q	=  (...and _entail::   inner_valued_q<Ts>);

template <         class ...Ts>	using    under_valued_u	= common_t<_entail::   under_valued_u<Ts>...>;
template <         class ...Ts>	concept  under_valued_q	=  (...and _entail::   under_valued_q<Ts>);

template <         class ...Ts>	using    fixed_valued_u	= common_t<_entail::   fixed_valued_u<Ts>...>;
template <         class ...Ts>	concept  fixed_valued_q	=  (...and _entail::   fixed_valued_q<Ts>);

template <         class ...Ts>	using    fluid_valued_u	= common_t<_entail::   fluid_valued_u<Ts>...>;
template <         class ...Ts>	concept  fluid_valued_q	=  (...and _entail::   fluid_valued_q<Ts>);

template <         class ...Ts>	using          valued_u	= common_t<_entail::         valued_u<Ts>...>;
template <         class ...Ts>	concept        valued_q	=  (...and _entail::         valued_q<Ts>);


template <         auto  ...Ns>	using    assign_sized_t	= typename _entail::  assign_sized  <Ns...>;
template <         auto  ...Ns>	XTAL_LET assign_sized_n	=          _entail::  assign_sized_n<Ns...>;
template <         auto  ...Ns>	XTAL_LET assign_sized_r	=          _entail::  assign_sized_r<Ns...>;


template <class T             >	XTAL_LET  tuple_sized_n	=          _entail::   tuple_sized_n<T >;
template <         class ...Ts>	concept   tuple_sized_q	=  (...and _entail::   tuple_sized_q<Ts>);

template <class T             >	XTAL_LET  array_sized_n	=          _entail::   array_sized_n<T >;
template <         class ...Ts>	concept   array_sized_q	=  (...and _entail::   array_sized_q<Ts>);

template <class T             >	using     fixed_sized  	=          _entail::   fixed_sized  <T >;
template <class T             >	XTAL_LET  fixed_sized_n	=          _entail::   fixed_sized_n<T >;
template <         class ...Ts>	concept   fixed_sized_q	=  (...and _entail::   fixed_sized_q<Ts>);

template <class T             >	using     fluid_sized  	=          _entail::   fluid_sized  <T >;
template <class T             >	XTAL_LET  fluid_sized_n	=          _entail::   fluid_sized_n<T >;
template <         class ...Ts>	concept   fluid_sized_q	=  (...and _entail::   fluid_sized_q<Ts>);

template <class T             >	using           sized  	=          _entail::         sized  <T >;
template <class T             >	XTAL_LET        sized_n	=          _entail::         sized_n<T >;
template <         class ...Ts>	concept         sized_q	=  (...and _entail::         sized_q<Ts>);


template <class T             >	XTAL_LET        fixed_n	=          _entail::         fixed_n<T >;
template <         class ...Ts>	using           fixed_u	= common_t<_entail::         fixed_u<Ts>...>;
template <         class ...Ts>	concept         fixed_q	=  (...and _entail::         fixed_q<Ts>);

template <class T             >	XTAL_LET        fluid_n	=          _entail::         fluid_n<T >;
template <         class ...Ts>	using           fluid_u	= common_t<_entail::         fluid_u<Ts>...>;
template <         class ...Ts>	concept         fluid_q	=  (...and _entail::         fluid_q<Ts>);


template <class T             >	using        destruct_t	=          _entail::      destruct_t<T >;
template <class T             >	using        destruct_u	=          _entail::      destruct_u<T >;
template <class T             >	XTAL_LET     destruct_n	=          _entail::      destruct_n<T >;

template <class T, int   ...Ns>	using        dissolve  	=          _entail:: dissolve  <T, Ns...>;
//mplate <         int   ...Ns>	using        dissolve_x	=          _entail:: dissolve_x<   Ns...>;
//mplate <class T, class ..._s>	using        dissolve_s	=          _entail:: dissolve_s<T, _s...>;
template <class T             >	using        dissolve_t	=          _entail::      dissolve_t<T >;
template <class T             >	using        dissolve_u	=          _entail::      dissolve_u<T >;
template <class T             >	XTAL_LET     dissolve_n	=          _entail::      dissolve_n<T >;
template <class T             >	XTAL_LET     dissolve_r	=          _entail::      dissolve_r<T >;

template <class T             >	using         absolve_t	=          _entail::       absolve_t<T >;
template <         class ...Ts>	using         absolve_u	= common_t<_entail::       absolve_u<Ts>...>;
template <class T             >	XTAL_LET      absolve_n	=          _entail::       absolve_n<T >;
template <class T             >	XTAL_LET      absolve_r	=          _entail::       absolve_r<T >;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Ranged...

template <         class ...Ts>	concept        scalar_q	=  (...and _entail::       scalar_q<Ts>);
template <         class ...Ts>	concept        vector_q	=  (...and _entail::       vector_q<Ts>);
template <         class ...Ts>	concept        matrix_q	=  (...and _entail::       matrix_q<Ts>);
template <         class ...Ts>	concept        tensor_q	=  (...and _entail::       tensor_q<Ts>);
template <class T, int   N=-1 >	concept         array_q	=          _entail::        array_q<T > and N < 0 or destruct_n<T> == N;
template <class T, int   N=-1 >	concept      subarray_q	=          _entail::        array_q<T > and N < 0 or destruct_n<T> <= N;


template <class T             >	using       coindexed_u	=          _entail::    coindexed_u<T >;
template <class          ...Ts>	concept     coindexed_q	= (... and _entail::    coindexed_q<Ts>);
template <class          ...Ts>	concept      covalued_q	= (... and _entail::     covalued_q<Ts>);


template <class T             >	using        arranged_t	=          _entail::     arranged_t<T >;
template <class T             >	using      reiterated_t	=          _entail::   reiterated_t<T >;

template <class T             >	using     initializer_s	=          _entail::  initializer_s<T > ;
template <class T             >	using     initializer_t	=          _entail::  initializer_t<T > ;
template <class T             >	using     initializer_u	=          _entail::  initializer_u<T > ;
template <class          ...Ts>	concept   initializer_q	=  (...and _entail::  initializer_q<Ts>);

template <class T             >	using        iteratee_t	= typename _entail::     iteratee  <T >::type;
template <class T             >	using        iterated_u	= _std::remove_reference_t<iteratee_t<T>>;
template <class T             >	using        iterated_t	= typename _entail::     iterated  <T >::type;
template <class T             >	using        iterator_t	= typename _entail::     iterator  <T >::type;
template <class T             >	using        distance_t	=          _entail::     distance_t<T > ;
template <class T             >	using        interval_t	=          _entail::     interval_t<T > ;
template <class T=extent_type >	using         counted_t	= typename _entail::      counted  <T >::type;
template <class T=extent_type >	using         counter_t	= typename _entail::      counter  <T >::type;

template <class          ...Ts>	concept      iterable_q	=  (...and _entail::     iterable_q<Ts>);
template <class          ...Ts>	concept      iterated_q	=  (...and _entail::     iterated_q<Ts>);
template <class          ...Ts>	concept      iterator_q	=  (...and _entail::     iterator_q<Ts>);
template <class          ...Ts>	concept      sentinel_q	=  (...and _entail::     sentinel_q<Ts>);
template <class          ...Ts>	concept      distance_q	=  (...and _entail::     distance_q<Ts>);
template <class          ...Ts>	concept      interval_q	=  (...and _entail::     interval_q<Ts>);
template <class          ...Ts>	concept       counted_q	=  (...and _entail::      counted_q<Ts>);
template <class          ...Ts>	concept       counter_q	=  (...and _entail::      counter_q<Ts>);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Arithmetic...

template <int N, class T, class U=T>	concept  multiplicative_group_p	= _entail:: multiplicative_group_p<N, T, U>;
template <int N, class T, class U=T>	concept        additive_group_p	= _entail::       additive_group_p<N, T, U>;
template <int N, class T, class U=T>	concept        discrete_group_p	= _entail::       discrete_group_p<N, T, U>;
template <int N, class T, class U=T>	concept        quotient_group_p	= _entail::       quotient_group_p<N, T, U>;
template <int N, class T, class U=T>	concept        integral_group_p	= _entail::       integral_group_p<N, T, U>;

template <int N, class T, class U=T>	concept      contiguous_group_p	= _entail::     contiguous_group_p<N, T, U>;
template <int N, class T, class U=T>	concept      contiguous_field_p	= _entail::     contiguous_field_p<N, T, U>;
template <int N, class T, class U=T>	concept      continuous_field_p	= _entail::     continuous_field_p<N, T, U>;
template <int N, class T, class U=T>	concept         complex_field_p	= _entail::        complex_field_p<N, T, U>;
template <int N, class T, class U=T>	concept         simplex_field_p	= _entail::        simplex_field_p<N, T, U>;

template <int N, class T, class U=T>	concept         logical_group_p	= _entail::        logical_group_p<N, T, U>;
template <int N, class T, class U=T>	concept          binary_group_p	= _entail::         binary_group_p<N, T, U>;

template <int N, class T, class U=T>	concept            inequality_p	= _entail::           inequality_p<N, T, U>;
template <int N, class T, class U=T>	concept              equality_p	= _entail::             equality_p<N, T, U>;
template <int N, class T, class U=T>	concept               quality_p	= _entail::              quality_p<N, T, U>;


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

template <class   ...Ts>	concept          logical_group_q	= (...and        logical_group_p<0, Ts>);
template <class   ...Ts>	concept           binary_group_q	= (...and         binary_group_p<0, Ts>);

template <class   ...Ts>	concept             inequality_q	= (...and           inequality_p<2, Ts>);
template <class   ...Ts>	concept               equality_q	= (...and             equality_p<2, Ts>);
template <class   ...Ts>	concept                quality_q	= (...and              quality_p<2, Ts>);


////////////////////////////////////////////////////////////////////////////////

XTAL_LET zero   = constant_t<XTAL_VAL_(0   )>{};
XTAL_LET half   = constant_t<XTAL_VAL_(0.5F)>{};
XTAL_LET  one   = constant_t<XTAL_VAL_(1   )>{};
XTAL_LET  two   = constant_t<XTAL_VAL_(2   )>{};
XTAL_LET  three = constant_t<XTAL_VAL_(3   )>{};

template <auto  N> XTAL_LET half_n = constant_t<XTAL_VAL_(1.F/(one << N))>{};
template <auto  N> XTAL_LET  two_n = constant_t<XTAL_VAL_(1.F*(one << N))>{};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./any.ii"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
