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

#include "./etc.hh"

XTAL_ENV_(push)

#include <range/v3/all.hpp>
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _std = ::std;
namespace _v3
{
	namespace ranges = ::ranges;
	namespace views  = ::ranges::views;

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Standard types...

using null_t = XTAL_STD_(null_t);
using unit_t = XTAL_STD_(unit_t);
using sign_t = XTAL_STD_(sign_t);
using byte_t = XTAL_STD_(byte_t);
using size_t = XTAL_STD_(size_t);
using size_s = XTAL_STD_(size_s);

template <auto N> XTAL_LET sign_v = (0 < N) - (N < 0);
template <auto N>  concept sign_p = _std::integral<decltype(N)> and -1 <= N and N <= 1;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Structural types...

template <class      T >   concept complete_p = requires {typename _std::void_t<decltype(sizeof(T))>;};
template <class   ...Ts>   concept complete_q = (...and complete_p<Ts>);
template <class      T >    struct complete    {class type  {};};
template <complete_q T >    struct complete<T> {using type = T;};
template <class      T >     using complete_t = typename complete<T>::type;


template <class    T >     concept constant_p = _std::derived_from<complete_t<T>, _std::integral_constant<typename complete_t<T>::value_type, complete_t<T>{}>>;
template <class    T >     concept  boolean_p = constant_p<T> and _std::convertible_to<typename T::value_type, bool>;
template <class    T >     concept  integer_p = constant_p<T> and _std::   is_signed_v<typename T::value_type>;
template <class    T >     concept  sequent_p = constant_p<T> and _std:: is_unsigned_v<typename T::value_type>;

template <class ...Ts>     concept constant_q = (...and constant_p<Ts>);
template <class ...Ts>     concept  boolean_q = (...and  boolean_p<Ts>);
template <class ...Ts>     concept  integer_q = (...and  integer_p<Ts>);
template <class ...Ts>     concept  sequent_q = (...and  sequent_p<Ts>);

template <auto     N >       using constant_t = _std::integral_constant<decltype(N), N>;
template <auto     N >       using  boolean_t = _std::integral_constant<bool,        N>;
template <auto     N >       using  integer_t = _std::integral_constant<int,         N>;
template <auto     N >       using  sequent_t = _std::integral_constant<size_t,      N>;

template <class    T >     using subsequent_s = sequent_t<T{} - 1>;
template <class    T >   concept subsequent_p = sequent_p<T> and 0 != T::value;
template <class ...Ts>   concept subsequent_q = (...and subsequent_p<Ts>);


template <class    T >       using   based_t  = _std::remove_cvref_t<complete_t<T>>;
template <class    T >     concept   based_p  = _std::is_trivially_copyable_v<T>;
template <class    T >     concept unbased_p  =     not   based_p<T>;
template <class ...Ts>     concept   based_q  = (...and   based_p<Ts>);
template <class ...Ts>     concept unbased_q  = (...and unbased_p<Ts>);

template <class    T >      struct rebased             : boolean_t<1> {using type = _std::remove_reference_t<T>;};
template <unbased_p T>      struct rebased<T        & >: boolean_t<0> {using type =       T&;};
template <unbased_p T>      struct rebased<T  const & >: boolean_t<0> {using type = const T&;};
template <class    T >       using rebased_t  = typename rebased<T>::type;
template <class    T >     concept rebased_p  =  (bool)  rebased<T> {};
template <class ...Ts>     concept rebased_q  =  (...and rebased_p<Ts>);

template <class    T >      struct debased             : boolean_t<0> {using type = _std::remove_reference_t<T>;};
template <unbased_p T>      struct debased<T        & >: boolean_t<1> {using type =       T*;};
template <unbased_p T>      struct debased<T  const & >: boolean_t<1> {using type = const T*;};
template <class    T >       using debased_t  = typename debased<T>::type;
template <class    T >     concept debased_p  =  (bool)  debased<T> {};
template <class ...Ts>     concept debased_q  =  (...and debased_p<Ts>);


template <class    T >       using valued_t   = typename based_t<T>::value_type;
template <class    T >     concept valued_p   = requires {typename valued_t<T>;};
template <class ...Ts>     concept valued_q   = (...and valued_p<Ts>);
template <class    T >    XTAL_LET valued_v   = based_t<T>::value;
template <class    V >    XTAL_FN2 valued_f(V &&v) {return valued_v<V>;}

template <class    T >     struct devalued     {using value_type = _std::remove_all_extents_t<based_t<T>>;};
template <valued_p T >     struct devalued<T> : based_t<T> {};
template <class    T >      using devalued_t  = valued_t<devalued<T>>;


template <class    T >     concept vacant_p   = not complete_p<T> or constant_p<T>;//0 == sizeof(T);
template <class ...Ts>     concept vacant_q   = (...and vacant_p<Ts>);

template <class    X >       struct argument    {using type = X &&;};
template <based_q  X >       struct argument<X> {using type = X const &;};
template <class    X >        using argument_t = typename argument<X>::type;


////////////////////////////////////////////////////////////////////////////////

template <          class ...Ts> struct identical;// `is_same`
template <          class ...Ts> struct isotropic;// `is_same` modulo qualifiers
template <          class ...Ts> struct epitropic;// `is_constructible`

template <class  T, class ...Ts> struct identical<T, Ts...>: _std::conjunction<_std::is_same<Ts, T>...> {};
template <class  T, class ...Ts> struct isotropic<T, Ts...>: _std::conjunction<_std::is_same<based_t<Ts>, based_t<T>>...> {};
template <class  T, class ...Ts> struct epitropic<T, Ts...>: _std::conjunction<_std::is_constructible<Ts, T>...> {};

template <class  T, class ...Ts> concept of_p = (...and _std::derived_from<based_t<Ts>, based_t<T>>);
template <class  T, class ...Ts> concept of_q = (...and _std::derived_from<based_t<T>, based_t<Ts>>);

template <class ...Ts>         using common_t = _std::common_type_t<Ts...>;
template <class ...Ts>       concept common_q = requires {typename common_t<Ts...>;};
template <class ...Ts>       concept id_q     = identical<Ts...>::value;
template <class ...Ts>       concept is_q     = isotropic<Ts...>::value;
template <class ...Ts>       concept to_q     = epitropic<Ts...>::value;
template <class    T >      XTAL_LET to_f     = [] XTAL_1FN_(T);


////////////////////////////////////////////////////////////////////////////////

template <class    M >      using member_t = debased_t<M>;
///< Converts `unbased` references to pointers. \

template <class ...Ws>  concept remember_q = (...and not debased_p<Ws>);
///< Governs access to the underlying member. \


///\
Equivalent to the soon-to-be deprecated `std::aligned_storage`. \

template <class T>
struct aligned
{
	class type {alignas(alignof(T)) byte_t data[sizeof(T)];};
	XTAL_LET value = sizeof(type);
};
template <class    T >      using aligned_t = typename aligned<T>::type;
template <class    T >   XTAL_LET aligned_v =          aligned<T>::value;

template <class    T >      using pointed_t =          XTAL_TYP_(*XTAL_VAL_(T));
template <class    T >      using pointer_t =          XTAL_TYP_(&XTAL_VAL_(T));
template <class ...Ts>    concept pointed_q = (... and requires {&XTAL_VAL_(Ts);});
template <class ...Ts>    concept pointer_q = (... and requires {*XTAL_VAL_(Ts);});

template <class T, class ...Ys> concept forcible_q = (...and (sizeof(T) == sizeof(Ys)));
template <class T, class ...Ys> concept fungible_q = (...and (of_p<T, Ys> or of_p<Ys, T>));


template <valued_q T >   XTAL_LET arity_v = sizeof(T)/aligned_v<devalued_t<T>>;
template <valued_q T >      using arity_t = constant_t<arity_v<T>>;
template <valued_q T >      using array_t = _std::array<valued_t<T>, arity_v<T>>;
template <class    T >    concept array_r = _std::is_array_v<T> or of_p<array_t<T>, T>;

template <class    T , int N=-1> concept    arity_q = N <  0      or arity_v<T> == N;
template <class    T , int N=-1> concept subarity_q = 0 <= N     and arity_v<T> <= N;
template <class    T , int N=-1> concept    array_q = array_r<T> and    arity_q<T, N>;
template <class    T , int N=-1> concept subarray_q = array_r<T> and subarity_q<T, N>;

template <int N=-1, class ...Ts> concept    arity_p = (...and    arity_q<Ts, N>);
template <int N=-1, class ...Ts> concept subarity_p = (...and subarity_q<Ts, N>);
template <int N=-1, class ...Ts> concept    array_p = (...and    array_q<Ts, N>);
template <int N=-1, class ...Ts> concept subarray_p = (...and subarray_q<Ts, N>);

template <          class ...Ts> concept disarray_q = (...and not array_r<Ts>);



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Arithmetic types...

template <class    T >   using unsigned_t = _std::make_unsigned_t<devalued_t<T>>;
template <class    T >   using   signed_t = _std::  make_signed_t<devalued_t<T>>;

template <class    T > concept unsigned_p = _std::  is_unsigned_v<devalued_t<T>>;
template <class    T > concept   signed_p = _std::    is_signed_v<devalued_t<T>>;

template <class ...Ts> concept unsigned_q = (...and unsigned_p<Ts>);
template <class ...Ts> concept   signed_q = (...and   signed_p<Ts>);


////////////////////////////////////////////////////////////////////////////////

template <class T>
concept equality_p = requires (T t, T u)
{
	{t == u} -> is_q<bool>;
	{t != u} -> is_q<bool>;
};
template <class T>
concept inequality_p = equality_p<T> and requires (T t, T u)
{
	{t <= u} -> is_q<bool>;
	{t <  u} -> is_q<bool>;
	{t >= u} -> is_q<bool>;
	{t >  u} -> is_q<bool>;
};
template <class T>
concept quality_p = equality_p<T> and inequality_p<T>;


template <class T, size_t N_arity=0>
concept boolean_logic_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{!u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t || u} -> is_q<T>;
		{t && u} -> is_q<T>;
	};
};
template <class T, size_t N_arity=0>
concept binary_logic_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{   ~  u} -> is_q<T>;
		{t  ^= u} -> is_q<T>;
		{t  |= u} -> is_q<T>;
		{t  &= u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t  ^  u} -> is_q<T>;
		{t  |  u} -> is_q<T>;
		{t  &  u} -> is_q<T>;
	};
};


template <class T, size_t N_arity=0>
concept multiplicative_group_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{t  *= u} -> is_q<T>;
		{t  /= u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t  *  u} -> is_q<T>;
		{t  /  u} -> is_q<T>;
	};
};
template <class T, size_t N_arity=0>
concept additive_group_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{t  += u} -> is_q<T>;
		{t  -= u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t  +  u} -> is_q<T>;
		{t  -  u} -> is_q<T>;
		{   -  u} -> is_q<T>;
	};
};
template <class T, size_t N_arity=0>
concept discrete_group_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{t  ++  } -> is_q<T>;
		{   ++ u} -> is_q<T>;
		{t  --  } -> is_q<T>;
		{   -- u} -> is_q<T>;
	};
};
template <class T, size_t N_arity=0>
concept quotient_group_p = requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{t  %= u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t  %  u} -> is_q<T>;
	};
};
template <class T, size_t N_arity=0>
concept integral_group_p = _std::integral<T> or discrete_group_p<T, N_arity> and quotient_group_p<T, N_arity>;


template <class T, size_t N_arity=0>
concept field_p = multiplicative_group_p<T, N_arity> and additive_group_p<T, N_arity>;

template <class T, size_t N_arity=0>
concept real_field_p = _std::floating_point<T> or
requires (T t)
{
	requires quality_p<T> and field_p<T, N_arity>;
	{_std::abs(t)} -> is_q<T>;
};

template <class T>
concept complex_field_p = of_q<T, _std::complex<devalued_t<T>>> or requires (T t)
{
	requires equality_p<T> and field_p<T, 2>;
	{_std::abs(t)} -> is_q<valued_t<T>>;
	{t.real()}     -> is_q<valued_t<T>>;
	{t.imag()}     -> is_q<valued_t<T>>;
};


template <class ...Ts> concept multiplicative_group_q = (...and multiplicative_group_p<based_t<Ts>>);
template <class ...Ts> concept       additive_group_q = (...and       additive_group_p<based_t<Ts>>);
template <class ...Ts> concept       discrete_group_q = (...and       discrete_group_p<based_t<Ts>>);
template <class ...Ts> concept       quotient_group_q = (...and       quotient_group_p<based_t<Ts>>);
template <class ...Ts> concept       integral_group_q = (...and       integral_group_p<based_t<Ts>>);

template <class ...Ts> concept        complex_field_q = (...and        complex_field_p<based_t<Ts>>);
template <class ...Ts> concept           real_field_q = (...and           real_field_p<based_t<Ts>>);
template <class ...Ts> concept                field_q = (...and                field_p<based_t<Ts>>);

template <class ...Ts> concept        boolean_logic_q = (...and        boolean_logic_p<based_t<Ts>>);
template <class ...Ts> concept         binary_logic_q = (...and         binary_logic_p<based_t<Ts>>);

template <class ...Ts> concept           inequality_q = (...and           inequality_p<based_t<Ts>>);
template <class ...Ts> concept             equality_q = (...and             equality_p<based_t<Ts>>);
template <class ...Ts> concept              quality_q = (...and              quality_p<based_t<Ts>>);


static_assert(                  real_field_q<float>);
static_assert(                       field_q<float>);
static_assert(          not quotient_group_q<float>);
static_assert(              quotient_group_q<  int>);
static_assert(complex_field_q<_std::complex<float>>);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//\
Range types...

template <class    T >       using begin_t    = decltype( XTAL_VAL_(T).begin());
template <class    T >       using   end_t    = decltype( XTAL_VAL_(T).  end());
template <class    T >     concept begin_p    = requires (T t) {*t.begin();};
template <class    T >     concept   end_p    = requires (T t) {*t.  end();};
template <class ...Ts>     concept begin_q    = (...and begin_p<Ts>);
template <class ...Ts>     concept   end_q    = (...and   end_p<Ts>);

template <class    W >       using bracket_t  = _std::initializer_list<W>;
template <class ...Ts>     concept bracket_q  = begin_q<Ts...> and end_q<Ts...>;

template <class    W >       using interval_t = _v3::ranges::iota_view<W, W>;
template <class    T >       using iterate_t  = _v3::ranges::view_interface<T>;


template <class    T >     concept iterable_p = begin_p<T> and not requires (T t) {t.front();};
template <class    T >     concept iterated_p = begin_p<T> and     requires (T t) {t.front();};
template <class    T >     concept iterator_p = requires (T t) {*++t;};
template <class    T >     concept integral_p = _std::integral<T>;

template <class ...Ts>     concept iterable_q = (...and iterable_p<Ts>);
template <class ...Ts>     concept iterated_q = (...and iterated_p<Ts>);//_v3::ranges::forward_range
template <class ...Ts>     concept iterator_q = (...and iterator_p<Ts>);//_v3::ranges::forward_iterator
template <class ...Ts>     concept integral_q = (...and integral_p<Ts>);

template <class ...Ts>   concept uniterable_q = (...and not iterable_p<Ts>);
template <class ...Ts>   concept uniterated_q = (...and not iterated_p<Ts>);
template <class ...Ts>   concept uniterator_q = (...and not iterator_p<Ts>);
template <class ...Ts>   concept unintegral_q = (...and not integral_p<Ts>);

template <class    T >      struct iterated;
template <class    T >      struct iterator;
template <class    T >      struct iteratee;

template <class    T >       using iterated_t = typename iterated<T>::type;
template <class    T >       using iterator_t = typename iterator<T>::type;//_v3::ranges::iterator_t
template <class    T >       using iteratee_t = typename iteratee<T>::type;//_v3::ranges::range_reference_t, _v3::ranges::iter_reference_t

template <iterated_p T>     struct iterated<T>: boolean_t<1> {using type =               based_t<T> ;};
template <iterator_p T>     struct iterated<T>: boolean_t<0> {using type =                     void ;};
template <integral_p T>     struct iterated<T>: boolean_t<0> {using type =            interval_t<T> ;};

template <iterable_p T>     struct iterator<T>: boolean_t<0> {using type =               begin_t<T> ;};
template <iterated_p T>     struct iterator<T>: boolean_t<0> {using type =               begin_t<T> ;};
template <iterator_p T>     struct iterator<T>: boolean_t<1> {using type =               based_t<T> ;};
template <integral_p T>     struct iterator<T>: boolean_t<0> {using type = iterator_t<interval_t<T>>;};

template <iterable_p T>     struct iteratee<T>: boolean_t<0> {using type =     pointed_t<begin_t<T>>;};
template <iterated_p T>     struct iteratee<T>: boolean_t<0> {using type =     pointed_t<begin_t<T>>;};
template <iterator_p T>     struct iteratee<T>: boolean_t<0> {using type =             pointed_t<T> ;};
template <integral_p T>     struct iteratee<T>: boolean_t<1> {using type =               based_t<T> ;};


template <class    T >       using sentinel_t = based_t<_v3::ranges::sentinel_t<T>>;
template <class    T >       using distance_t = XTAL_TYP_(_std::distance(XTAL_VAL_(iterator_t<T>), XTAL_VAL_(iterator_t<T>)));
template <class    T >       using deranged_t = _v3::ranges::subrange<iterator_t<T>, sentinel_t<T>>;


template <class    T >     concept counted_p  = iterated_q<T> and to_q<T, interval_t<iteratee_t<T>>>;
template <class    T >     concept counter_p  = integral_q<T>;

template <class ...Ts>     concept counted_q  = (...and counted_p<Ts>);
template <class ...Ts>     concept counter_q  = (...and counter_p<Ts>);

template <class    T >      struct counted;
template <class    T >      struct counter;

template <counted_p T>      struct counted<T> : boolean_t<1> {using type =    based_t<T>;};
template <counter_p T>      struct counted<T> : boolean_t<0> {using type = iterated_t<T>;};

template <counted_p T>      struct counter<T> : boolean_t<0> {using type = iteratee_t<T>;};
template <counter_p T>      struct counter<T> : boolean_t<1> {using type =    based_t<T>;};

template <class T=size_s>    using counted_t  = typename counted<T>::type;
template <class T=size_s>    using counter_t  = typename counter<T>::type;


template <class      ...Ts> concept  beginning_q     = begin_q<Ts...> and is_q<begin_t<Ts>...>;
template <class      ...Ts> concept bracketing_q     = beginning_q<Ts...> and end_q<Ts...>;

template <class      ...Ts>  struct isomorphic       : isotropic<Ts...> {};
template <iterated_q ...Ts>  struct isomorphic<Ts...>: isomorphic<iteratee_t<Ts>...> {};
template <iterator_q ...Ts>  struct isomorphic<Ts...>: isomorphic<iteratee_t<Ts>...> {};
template <class      ...Ts> concept isomorphic_p =     isomorphic<Ts...>::value;

template <class      ...Ts>  struct epimorphic       : epitropic<Ts...> {};
template <iterated_q ...Ts>  struct epimorphic<Ts...>: epimorphic<iteratee_t<Ts>...> {};
template <iterator_q ...Ts>  struct epimorphic<Ts...>: epimorphic<iteratee_t<Ts>...> {};
template <class      ...Ts> concept epimorphic_p =     epimorphic<Ts...>::value;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
namespace std
{////////////////////////////////////////////////////////////////////////////////

#if not __cpp_lib_bit_cast
template <class  T, class S>
static constexpr T bit_cast(S const& s)
noexcept
{
	static_assert(xtal::based_q<T, S> and sizeof(T) == sizeof(S));
	return __builtin_bit_cast(T, s);
}
#endif


}//////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
