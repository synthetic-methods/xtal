#pragma once

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

#include <range/v3/all.hpp>
#include <simde/arm/neon.h>


#include "./etc.hh"

XTAL_ENV_(push)
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
	XTAL_DEF_(inline)
	XTAL_LET bit_cast(S const &s)
	noexcept -> decltype(auto)
	{
		static_assert(is_trivially_copyable_v<T>);
		static_assert(is_trivially_copyable_v<S>);
		static_assert(sizeof(T) == sizeof(S));
		return __builtin_bit_cast(T, s);
	};
#endif

	XTAL_DEF_(inline,static)
	XTAL_LET make_signed_f(auto const &u)
	noexcept -> auto
	{
		using U = XTAL_ALL_(u); static_assert(_std::is_integral_v<U>);
		using V = _std::make_signed_t<U>;
		
		if constexpr (_std::is_same_v<U, V>) {
			return u;
		}
		else {
			return _xtd::bit_cast<V>(u);
		}
	}
	XTAL_DEF_(inline,static)
	XTAL_LET make_unsigned_f(auto const &v)
	noexcept -> auto
	{
		using V = XTAL_ALL_(v); static_assert(_std::is_integral_v<V>);
		using U = _std::make_unsigned_t<V>;
		
		if constexpr (_std::is_same_v<U, V>) {
			return v;
		}
		else {
			return _xtd::bit_cast<U>(v);
		}
	}


	template <class T> XTAL_DEF_(inline) XTAL_LET decay_lvalue_f(T const  &t) noexcept -> T const    {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_lvalue_f(T        &t) noexcept -> T          {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_lvalue_f(T const &&t) noexcept -> T const && {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_lvalue_f(T       &&t) noexcept -> T       && {return XTAL_REF_(t);}

	template <class T> XTAL_DEF_(inline) XTAL_LET decay_rvalue_f(T const  &t) noexcept -> T const  & {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_rvalue_f(T        &t) noexcept -> T        & {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_rvalue_f(T const &&t) noexcept -> T const    {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_rvalue_f(T       &&t) noexcept -> T          {return XTAL_REF_(t);}

	template <class T> XTAL_DEF_(inline) XTAL_LET decay_lconst_f(T const  &t) noexcept -> T          {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_lconst_f(T        &t) noexcept -> T          {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_lconst_f(T const &&t) noexcept -> T const && {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_lconst_f(T       &&t) noexcept -> T       && {return XTAL_REF_(t);}

	template <class T> XTAL_DEF_(inline) XTAL_LET decay_rconst_f(T const  &t) noexcept -> T const  & {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_rconst_f(T        &t) noexcept -> T        & {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_rconst_f(T const &&t) noexcept -> T          {return XTAL_REF_(t);}
	template <class T> XTAL_DEF_(inline) XTAL_LET decay_rconst_f(T       &&t) noexcept -> T          {return XTAL_REF_(t);}

	template <class T>                   XTAL_USE decay_lvalue_t = decltype(decay_lvalue_f(XTAL_ANY_(T)));
	template <class T>                   XTAL_USE decay_rvalue_t = decltype(decay_rvalue_f(XTAL_ANY_(T)));
	template <class T>                   XTAL_USE decay_lconst_t = decltype(decay_lconst_f(XTAL_ANY_(T)));
	template <class T>                   XTAL_USE decay_rconst_t = decltype(decay_rconst_f(XTAL_ANY_(T)));

}
namespace _xtd::ranges
{
	using namespace ::ranges;

}
namespace _xtd::ranges::views
{
	using namespace ::ranges::views;

	XTAL_DEF_(inline)
	XTAL_LET zip_transform(auto &&...oo)
	noexcept -> decltype(auto)
	{
		return zip_with(XTAL_REF_(oo)...);
	};

}


#include "./_entail.ii"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Standard...

XTAL_USE      null_type = _entail::      null_type;
XTAL_USE      unit_type = _entail::      unit_type;
XTAL_USE      sign_type = _entail::      sign_type;
XTAL_USE      real_type = _entail::      real_type;
XTAL_USE      size_type = _entail::      size_type;
XTAL_USE  integral_type = _entail::  integral_type;

static constexpr size_type size_0{0};
static constexpr size_type size_1{1};
static constexpr size_type size_2{2};
static constexpr size_type size_3{3};


template <auto    N, auto  ...Ms>	XTAL_ASK             un_n = _entail::un_n<N, Ms... >;
template <auto    N, auto  ...Ms>	XTAL_ASK             in_n = _entail::in_n<N, Ms... >;
template <auto    N, auto N_0=0 >	XTAL_ASK           sign_p = _entail::     sign_p<N, N_0>;
template <auto    N, auto N_0=0 >	XTAL_LET           sign_n = _entail::     sign_n<N, N_0>;
template <auto    N, auto   M   >	XTAL_LET           stop_n = _entail::     stop_n<N, M  >;
template <auto    N, auto   M=0 >	XTAL_LET            top_n = _entail::      top_n<N, M  >;

template <class            ...Ts>	XTAL_ASK           some_q = _entail::     some_q<Ts...>;
template <auto             ...Ns>	XTAL_ASK           some_n = _entail::     some_n<Ns...>;
template <class            ...Ts>	XTAL_ASK           none_q = _entail::     none_q<Ts...>;
template <auto             ...Ns>	XTAL_ASK           none_n = _entail::     none_n<Ns...>;

template <class            ...Ts>	XTAL_ASK           unit_q =	(...and  _entail::       unit_q<Ts   >);
template <class            ...Ts>	XTAL_ASK           null_q =	(...and  _entail::       null_q<Ts   >);
template <class            ...Ts>	XTAL_ASK           void_q =	(...and  _entail::       void_q<Ts   >);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural...

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

template <auto       N >	XTAL_USE      constant_t = typename _entail::     constant_t<N >;
template <class   ...Ts>	XTAL_ASK      constant_q = (...and  _entail::     constant_q<Ts>);
template <class   ...Ts>	XTAL_ASK      logical_q = (...and  _entail::     logical_q<Ts>);
template <class   ...Ts>	XTAL_ASK      ordinal_q = (...and  _entail::     ordinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK     cardinal_q = (...and  _entail::    cardinal_q<Ts>);
template <class   ...Ts>	XTAL_ASK     integral_q = (...and  _entail::    integral_q<Ts>);

template <class   ...Ts>	XTAL_ASK    unnatural_q = (...and  _entail::   unnatural_q<Ts>);
template <class   ...Ts>	XTAL_ASK      natural_q = (...and  _entail::     natural_q<Ts>);
template <class   ...Ts>	XTAL_ASK     terminal_q = (...and  _entail::    terminal_q<Ts>);
template <class   ...Ts>	XTAL_ASK      liminal_q = (...and  _entail::     liminal_q<Ts>);
template <liminal_q  T >	XTAL_USE   subliminal_s = typename _entail::  subliminal_s<T >;
template <liminal_q  T >	XTAL_USE superliminal_s = typename _entail::superliminal_s<T >;

template <int     ...Ns>	XTAL_LET   fractional_n =          _entail::  fractional  <Ns...>::value;///< `FromContinuedFraction`
template <int        N >	XTAL_LET   bisordinal_n =          _entail::  bisordinal  <N    >::value;
template <int        N >	XTAL_LET    factorial_n =          _entail::   factorial  <N    >::value;


template <class      T >	XTAL_USE        based_t =          _entail::    based_t<T>;
template <class   ...Ts>	XTAL_ASK        based_q = (...and  _entail::    based_q<Ts>);
template <class   ...Ts>	XTAL_ASK      unbased_q = (...and  _entail::  unbased_q<Ts>);

template <class      T >	XTAL_USE      debased_t = typename _entail::  debased<T>::type;
template <class      T >	XTAL_USE      rebased_t = typename _entail::  rebased<T>::type;

template <class      T >	XTAL_ASK      debased_p =   (bool) _entail::  debased<T>::value;
template <class      T >	XTAL_ASK      rebased_p =   (bool) _entail::  rebased<T>::value;

template <class   ...Ts>	XTAL_ASK      debased_q = (...and  _entail::  debased_q<Ts>);
template <class   ...Ts>	XTAL_ASK      rebased_q = (...and  _entail::  rebased_q<Ts>);


template <class T               >	XTAL_LET tuple_sized_n    =          _entail::   tuple_sized_n<T >;
template <class T               >	XTAL_USE tuple_sized_t    =          _entail::   tuple_sized_t<T >;
template <           class ...Ts>	XTAL_ASK tuple_sized_q    = (...and  _entail::   tuple_sized_q<Ts>);

template <class T               >	XTAL_LET array_sized_n    =          _entail::   tuple_sized_n<T >;
template <class T               >	XTAL_USE array_sized_t    =          _entail::   tuple_sized_t<T >;
template <           class ...Ts>	XTAL_ASK array_sized_q    = (...and  _entail::   tuple_sized_q<Ts>);

template <class T               >	XTAL_USE       sized      =          _entail::         sized  <T >;
template <class T               >	XTAL_LET       sized_n    =          _entail::         sized_n<T >;
template <class T               >	XTAL_USE       sized_t    =          _entail::         sized_t<T >;
template <           class ...Ts>	XTAL_ASK       sized_q    = (...and  _entail::         sized_q<Ts>);


template <           class ...Ts>	XTAL_USE inner_valued_u   = common_t<_entail::   inner_valued_u<Ts>...>;
template <           class ...Ts>	XTAL_ASK inner_valued_q   = (...and  _entail::   inner_valued_q<Ts>);

template <           class ...Ts>	XTAL_USE array_valued_u   = common_t<_entail::   array_valued_u<Ts>...>;
template <           class ...Ts>	XTAL_ASK array_valued_q   = (...and  _entail::   array_valued_q<Ts>);

template <           class ...Ts>	XTAL_USE       valued_u   = common_t<_entail::   valued_u<Ts>...>;
template <           class ...Ts>	XTAL_ASK       valued_q   = (...and  _entail::   valued_q<Ts>);


template <           class ...Ts>	XTAL_ASK     devalued_q = (...and  _entail:: devalued_q<Ts>);
template <class T               >	XTAL_USE     devalued_t =          _entail:: devalued_t<T >;
template <           class ...Ts>	XTAL_USE     devalued_u = common_t<_entail:: devalued_u<Ts>...>;
template <class T               >	XTAL_LET     devalued_n = _entail:: devalued_n<T>;
template <class T,   class ...Ts>	XTAL_ASK     devalued_p = (...and (devalued_n<T> < devalued_n<Ts>));

template <class T,   int   ...Ns>	XTAL_USE     devolved   =	_entail:: devolved  <T, Ns...>;
//mplate <           int   ...Ns>	XTAL_USE     devolved_x =	_entail:: devolved_x<   Ns...>;
//mplate <class   T, class ..._s>	XTAL_USE     devolved_s =	_entail:: devolved_s<T, _s...>;
template <class T               >	XTAL_LET     devolved_n =  _entail:: devolved_n<T>;
template <           class ...Ts>	XTAL_USE     devolved_u = common_t<_entail:: devolved_u<Ts>...>;
template <class T               >	XTAL_USE     devolved_t =          _entail:: devolved_t<T >;
template <class T,   class ...Ts>	XTAL_ASK     devolved_p = (...and (devolved_n<T> < devolved_n<Ts>));


////////////////////////////////////////////////////////////////////////////////

template <class T               >	XTAL_USE   aligned_t =       typename _entail:: aligned<T >::type;
template <           class ...Ts>	XTAL_LET   aligned_n =  (size_0 +...+ _entail:: aligned<Ts>::size());
template <           class ...Ts>	XTAL_LET   aligned_m =  aligned_n<Ts...> - size_1;

template <           class ...Ts>	XTAL_ASK    column_q =  (...and _entail:: column_q<Ts>);
template <class T,   int   N=-1 >	XTAL_ASK     array_q =          _entail::  array_q<T> and N <  0   or devalued_n<T> == N;
template <class T,   int   N=-1 >	XTAL_ASK  subarray_q =          _entail::  array_q<T> and 0 <= N  and devalued_n<T> <= N;
template <           class ...Ts>	XTAL_ASK  disarray_q =        not (...and  array_q<Ts>);

template <class            ...Ts>	XTAL_ASK  accessed_q = (... and _entail:: accessed_q<Ts>);
template <class            ...Ts>	XTAL_ASK   pointer_q = (... and _entail::  pointer_q<Ts>);
template <class               T >	XTAL_USE  accessed_u =          _entail:: accessed_u<T >;
template <class               T >	XTAL_USE   pointer_t =          _entail::  pointer_t<T >;
template <class               T >	XTAL_USE   pointee_t =          _entail::  pointee_t<T >;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Ranged...

template <class      ...Ts>	XTAL_ASK           count_q =	    (...and  _entail::count_q<based_t<Ts>>);
template <class         T >	XTAL_USE           count_t =	             _entail::count_t<based_t<T >> ;

template <class         T >	XTAL_USE     initializer_u =	             _entail::  initializer_u<T > ;
template <class         T >	XTAL_USE     initializer_t =	             _entail::  initializer_t<T > ;
template <class         T >	XTAL_USE      reiteratee_t =	             _entail::   reiteratee_t<T > ;
template <class         T >	XTAL_USE        iteratee_t =	    typename _entail::     iteratee  <T >::type;
template <class         T >	XTAL_USE        iterated_t =	    typename _entail::     iterated  <T >::type;
template <class         T >	XTAL_USE        iterator_t =	    typename _entail::     iterator  <T >::type;
template <class         T >	XTAL_USE        distance_t =	             _entail::     distance_t<T > ;
template <class         T >	XTAL_USE        interval_t =	             _entail::     interval_t<T > ;
template <class T=integral_type>	XTAL_USE      counted_t =	    typename _entail::      counted  <T >::type;
template <class T=integral_type>	XTAL_USE      counter_t =	    typename _entail::      counter  <T >::type;

template <class      ...Ts>	XTAL_ASK     initializer_q =	    (...and  _entail::  initializer_q<Ts>);
template <class      ...Ts>	XTAL_ASK      reiteratee_q =	    (...and  _entail::   reiteratee_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iteratee_q =	    (...and  _entail::     iteratee_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterable_q =	    (...and  _entail::     iterable_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterated_q =	    (...and  _entail::     iterated_q<Ts>);
template <class      ...Ts>	XTAL_ASK        iterator_q =	    (...and  _entail::     iterator_q<Ts>);
template <class      ...Ts>	XTAL_ASK        sentinel_q =	    (...and  _entail::     sentinel_q<Ts>);
template <class      ...Ts>	XTAL_ASK        distance_q =	    (...and  _entail::     distance_q<Ts>);
template <class      ...Ts>	XTAL_ASK        interval_q =	    (...and  _entail::     interval_q<Ts>);
template <class      ...Ts>	XTAL_ASK         counted_q =	    (...and  _entail::      counted_q<Ts>);
template <class      ...Ts>	XTAL_ASK         counter_q =	    (...and  _entail::      counter_q<Ts>);

template <class      ...Ts>	XTAL_ASK       ordinated_q =	    (...and  _entail::    ordinated_q<Ts>);
template <class      ...Ts>	XTAL_ASK     coordinated_q =	    (...and  _entail::  coordinated_q<Ts>);
template <class      ...Ts>	XTAL_ASK   uncoordinated_q =	    (...and  _entail::uncoordinated_q<Ts>);

template <class         T >	XTAL_USE        deranged_t =	             _entail::     deranged_t<T >;
template <class         T >	XTAL_USE        arranged_t =	             _entail::     arranged_t<T >;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Arithmetic...

template <class   ...Ts>	XTAL_ASK            number_q =	    (...and  _entail::          number_q<Ts>);
template <class   ...Ts>	XTAL_ASK       real_number_q =	    (...and  _entail::     real_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK     unreal_number_q =	    (...and  _entail::   unreal_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK    complex_number_q =	    (...and  _entail::  complex_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK    simplex_number_q =	    (...and  _entail::  simplex_number_q<Ts>);
template <class   ...Ts>	XTAL_ASK   integral_number_q =	    (...and  _entail:: integral_number_q<Ts>);


template <size_type N, class T, class U=T>	XTAL_ASK multiplicative_group_p = _entail:: multiplicative_group_p<N, T, U>;
template <size_type N, class T, class U=T>	XTAL_ASK       additive_group_p = _entail::       additive_group_p<N, T, U>;
template <size_type N, class T, class U=T>	XTAL_ASK       discrete_group_p = _entail::       discrete_group_p<N, T, U>;
template <size_type N, class T, class U=T>	XTAL_ASK       quotient_group_p = _entail::       quotient_group_p<N, T, U>;
template <size_type N, class T, class U=T>	XTAL_ASK       integral_group_p = _entail::       integral_group_p<N, T, U>;

template <size_type N, class T, class U=T>	XTAL_ASK     contiguous_group_p = _entail::     contiguous_group_p<N, T, U>;
template <size_type N, class T, class U=T>	XTAL_ASK     contiguous_field_p = _entail::     contiguous_field_p<N, T, U>;
template <size_type N, class T, class U=T>	XTAL_ASK     continuous_field_p = _entail::     continuous_field_p<N, T, U>;
template <size_type N, class T, class U=T>	XTAL_ASK        complex_field_p = _entail::        complex_field_p<N, T, U>;
template <size_type N, class T, class U=T>	XTAL_ASK        simplex_field_p = _entail::        simplex_field_p<N, T, U>;

template <size_type N, class T, class U=T>	XTAL_ASK      boolean_quantity_p = _entail::      boolean_quantity_p<N, T, U>;
template <size_type N, class T, class U=T>	XTAL_ASK       binary_quantity_p = _entail::       binary_quantity_p<N, T, U>;

template <size_type N, class T, class U=T>	XTAL_ASK           inequality_p = _entail::           inequality_p<N, T, U>;
template <size_type N, class T, class U=T>	XTAL_ASK             equality_p = _entail::             equality_p<N, T, U>;
template <size_type N, class T, class U=T>	XTAL_ASK              quality_p = _entail::              quality_p<N, T, U>;


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

template <class   ...Ts>	XTAL_ASK      boolean_quantity_q = (...and      boolean_quantity_p<0, Ts>);
template <class   ...Ts>	XTAL_ASK       binary_quantity_q = (...and       binary_quantity_p<0, Ts>);

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

template <auto    ...Ns>	XTAL_USE   lateral_t = typename _entail::lateral<common_t<XTAL_ALL_(Ns)...>, Ns...>::type;
template <auto    ...Ns>	XTAL_LET   lateral_n =          _entail::lateral<common_t<XTAL_ALL_(Ns)...>, Ns...>::type::value;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./any.ii"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
