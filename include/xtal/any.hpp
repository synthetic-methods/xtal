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
#if not __cpp_lib_bit_cast
namespace ::std
{////////////////////////////////////////////////////////////////////////////////
template <class  T, class S>
requires (sizeof(T) == sizeof(S) and is_trivially_copyable_v<T> and is_trivially_copyable_v<S>)
static constexpr T bit_cast(S const& s)
noexcept
{
	return __builtin_bit_cast(T, s);
}
}//////////////////////////////////////////////////////////////////////////////
#endif


#include <range/v3/all.hpp>
#include "./etc.hpp"

XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _std = ::std;
namespace _v3
{
namespace ranges = ::ranges;
namespace views  = ::ranges::views;
}


using null_t = XTAL_STD_(null_t);
using unit_t = XTAL_STD_(unit_t);
using sign_t = XTAL_STD_(sign_t);
using size_t = XTAL_STD_(size_t);
using size_x = XTAL_STD_(size_x);

template <typename ...>   class class_t {};
template <typename ...> concept class_q = true;

template <auto N> XTAL_LET sign_v = (0 < N) - (N < 0);
template <auto N>  concept sign_p = _std::integral<decltype(N)> and -1 <= N and N <= 1;

template <        auto N> XTAL_LET moeity_v = N&1;
template <auto M, auto N>  concept moeity_p = M == moeity_v<N>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <auto     N >       using constant_t = _std::integral_constant<decltype(N), N>;
template <class    T >       using substant_t = _std::integral_constant<typename T::value_type, T{} - sign_v<T{}>>;
template <class    T >     concept constant_p = _std::derived_from<T, _std::integral_constant<typename T::value_type, T{}>>;
template <class    T >     concept substant_p = constant_p<T> and T::value != 0;
template <class    T >     concept variable_p =     not constant_p<T>;
template <class ...Ts>     concept constant_q = (...and constant_p<Ts>);
template <class ...Ts>     concept substant_q = (...and substant_p<Ts>);
template <class ...Ts>     concept variable_q = (...and variable_p<Ts>);


template <class    T >       using   based_t  = _std::remove_cvref_t<T>;
template <class    T >     concept   based_p  = _std::is_trivially_copyable_v<T>;
template <class    T >     concept unbased_p  =     not   based_p<T>;
template <class ...Ts>     concept   based_q  = (...and   based_p<Ts>);
template <class ...Ts>     concept unbased_q  = (...and unbased_p<Ts>);

template <class    T >      struct debased            : constant_t<0> {using type = _std::remove_reference_t<T>;};
template <unbased_p T>      struct debased<T        &>: constant_t<1> {using type =       T*;};
template <unbased_p T>      struct debased<T  const &>: constant_t<1> {using type = const T*;};
template <class    T >       using debased_t  = typename debased<T>::type;
template <class    T >     concept debased_p  =  (bool)  debased<T>{};
template <class ...Ts>     concept debased_q  =  (...and debased_p<Ts>);

template <class    T >      struct rebased            : constant_t<1> {using type = _std::remove_reference_t<T>;};
template <unbased_p T>      struct rebased<T        &>: constant_t<0> {using type =       T&;};
template <unbased_p T>      struct rebased<T  const &>: constant_t<0> {using type = const T&;};
template <class    T >       using rebased_t  = typename rebased<T>::type;
template <class    T >     concept rebased_p  =  (bool)  rebased<T>{};
template <class ...Ts>     concept rebased_q  =  (...and rebased_p<Ts>);


template <class    T >       using value_t    = typename based_t<T>::value_type;
template <class    T >     concept value_p    = requires {typename value_t<T>;};
template <class ...Ts>     concept value_q    = (...and value_p<Ts>);
template <class    T >    XTAL_LET value_v    = based_t<T>::value;

template <class    T >      struct revalue     {using value_type = based_t<T>;};
template <value_p  T >      struct revalue<T> : based_t<T> {};
template <class    T >       using revalue_t  = value_t<revalue<T>>;


template <          class ...Ts> struct identical;// `is_same`
template <          class ...Ts> struct isotropic;// `is_same` modulo qualifiers
template <          class ...Ts> struct epitropic;// `is_constructible`

template <class  T, class ...Ts> struct identical<T, Ts...>: _std::conjunction<_std::is_same<Ts, T>...> {};
template <class  T, class ...Ts> struct isotropic<T, Ts...>: _std::conjunction<_std::is_same<based_t<Ts>, based_t<T>>...> {};
template <class  T, class ...Ts> struct epitropic<T, Ts...>: _std::conjunction<_std::is_constructible<Ts, T>...> {};

template <class ...Ts>         using common_t = _std::common_type_t<Ts...>;
template <class ...Ts>       concept common_q = requires {typename common_t<Ts...>;};
template <class ...Ts>       concept id_q     = identical<Ts...>::value;
template <class ...Ts>       concept is_q     = isotropic<Ts...>::value;
template <class ...Ts>       concept to_q     = epitropic<Ts...>::value;
template <class    T >      XTAL_LET to_f     = [] XTAL_1FN_(based_t<T>);

XTAL_LET identical_f = [] (XTAL_DEF o, XTAL_DEF ...oo)
XTAL_0FN_(...and (_std::addressof(XTAL_REF_(o)) == _std::addressof(XTAL_REF_(oo))));

template <class Y, class T>
concept fungible_q = _std::derived_from<T, Y> or _std::derived_from<Y, T>;

template <class Y>
XTAL_CN2 funge_f(XTAL_DEF t)
XTAL_0EX
{
	if constexpr (fungible_q<Y, decltype(t)>) {
		return      static_cast<Y>(XTAL_REF_(t));
	}
	else {
		return reinterpret_cast<Y>(XTAL_REF_(t));
	}
}


////////////////////////////////////////////////////////////////////////////////

template <auto   ...  >   XTAL_CN2 method_f(XTAL_DEF o) {return XTAL_REF_(o);}
///< Parameter-agnostic identity `method`. \

template <class    M >      using member_t = debased_t<M>;
template <class    M >   XTAL_CN2 member_f(XTAL_DEF w)     XTAL_0EX XTAL_REQ debased_q<M> {return &XTAL_REF_(w);}// obtain address
template <class    M >   XTAL_CN2 member_f(XTAL_DEF w)     XTAL_0EX {return to_f<M>(XTAL_REF_(w));}
template <class    M >   XTAL_CN2 member_f(XTAL_DEF ...ws) XTAL_0EX {return to_f<M>(XTAL_REF_(ws)...);}
///< Converts `unbased` references to pointers. \

template <class ...Ws>  concept remember_q = not (...or debased_p<Ws>);
template <class    W > XTAL_CN2 remember_f(W &&w) XTAL_0EX XTAL_REQ_(*w) {return *XTAL_REF_(w);}
template <class    W > XTAL_CN2 remember_f(W &&w) XTAL_0EX               {return  XTAL_REF_(w);}
///< Governs access to the underlying member `T`. \

template <class    T >      using pointed_t   = XTAL_TYP_(*XTAL_VAL_(T));
template <class    T >      using pointer_t   = XTAL_TYP_(&XTAL_VAL_(T));
template <class    I > XTAL_LET appointer_f   = [] (auto i) XTAL_0FN_(_std::launder(reinterpret_cast<I>(i)));
template <class    T >
struct aligned
{
	class type {alignas(alignof(T)) _std::byte data[sizeof(T)];};
	XTAL_LET value = sizeof(type);
};
template <class    T >       using aligned_t  = typename aligned<T>::type;
template <class    T >    XTAL_LET aligned_v  =          aligned<T>::value;

template <value_q  T >    XTAL_LET arity_v    = sizeof(T)/aligned_v<value_t<T>>;
template <value_q  T >       using arity_t    = constant_t<arity_v<T>>;
template <value_q  T >       using array_t    = _std::array<value_t<T>, arity_v<T>>;
template <int N=-1, class ...Ts>
concept array_p = requires ()
{
	requires (...and _std::derived_from<based_t<Ts>, array_t<Ts>>);
	requires (N == -1) or (...and (N == arity_v<Ts>));
};
template <class ...Ts>
concept array_q = array_p<-1, Ts...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class    T >   using unsigned_t = _std::make_unsigned_t<revalue_t<T>>;
template <class    T >   using   signed_t = _std::  make_signed_t<revalue_t<T>>;

template <class    T > concept unsigned_p = _std::  is_unsigned_v<revalue_t<T>>;
template <class    T > concept   signed_p = _std::    is_signed_v<revalue_t<T>>;

template <class ...Ts> concept unsigned_q = (...and unsigned_p<Ts>);
template <class ...Ts> concept   signed_q = (...and   signed_p<Ts>);

template <class ...Ts>
concept numeric_q = false
	or (...and _std::integral<based_t<Ts>>)
	or (...and _std::floating_point<based_t<Ts>>)
	or (...and is_q<Ts, _std::complex<value_t<Ts>>>)
;


////////////////////////////////////////////////////////////////////////////////

template <class T>
concept inequality_comparators_p = requires (T t, T u)
{
	{t <= u} -> is_q<bool>;
	{t <  u} -> is_q<bool>;
	{t >= u} -> is_q<bool>;
	{t >  u} -> is_q<bool>;
};
template <class T>
concept equality_comparators_p = requires (T t, T u)
{
	{t == u} -> is_q<bool>;
	{t != u} -> is_q<bool>;
};
template <class T>
concept comparators_p = equality_comparators_p<T> or inequality_comparators_p<T>;


///\returns `true` if `T` supports bitwise logical operations, `false` otherwise, \
with `0 < N_arity` differentiating between immutable (`2`) and mutable (`1`) operations. \

template <class T, size_t N_arity=0>
concept bitwise_operators_p = _std::integral<T> or requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{t  ^= u} -> is_q<T>;
		{t  |= u} -> is_q<T>;
		{t  &= u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t  ^  u} -> is_q<T>;
		{t  |  u} -> is_q<T>;
		{t  &  u} -> is_q<T>;
		{   ~  u} -> is_q<T>;
	};
};
///\returns `true` if `T` supports integer addition and subtraction, `false` otherwise. \

template <class T, size_t N_arity=0>
concept group_operators_p = _std::integral<T> or requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{t  %= u} -> is_q<T>;
		{t  += u} -> is_q<T>;
		{t  ++  } -> is_q<T>;
		{   ++ u} -> is_q<T>;
		{t  -= u} -> is_q<T>;
		{t  --  } -> is_q<T>;
		{   -- u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t  %  u} -> is_q<T>;
		{t  +  u} -> is_q<T>;
		{t  -  u} -> is_q<T>;
		{   -  u} -> is_q<T>;
	};
};
///\returns `true` if `T` supports arithmetic (but not logic) operations, `false` otherwise, \
with `0 < N_arity` differentiating between immutable (`2`) and mutable (`1`) operations. \

template <class T, size_t N_arity=0>
concept field_operators_p = _std::floating_point<T> or requires (T t, T u)
{
	requires N_arity == 2 or requires
	{
		{t  *= u} -> is_q<T>;
		{t  += u} -> is_q<T>;
		{t  /= u} -> is_q<T>;
		{t  -= u} -> is_q<T>;
	};
	requires N_arity == 1 or requires
	{
		{t  *  u} -> is_q<T>;
		{t  +  u} -> is_q<T>;
		{t  /  u} -> is_q<T>;
		{t  -  u} -> is_q<T>;
		{   -  u} -> is_q<T>;
	};
} and not bitwise_operators_p<T, N_arity>;


template <class T>
concept complex_operators_p = value_p<T> and is_q<T, _std::complex<value_t<T>>> or requires (T t)
{
	requires equality_comparators_p<T>;
	requires field_operators_p<T, 2>;
	{t.real()} -> _std::same_as<value_t<T>>;
	{t.imag()} -> _std::same_as<value_t<T>>;
};


template <class ...Ts> concept bitwise_operators_q = (...and bitwise_operators_p<based_t<Ts>>);
template <class ...Ts> concept complex_operators_q = (...and complex_operators_p<based_t<Ts>>);
template <class ...Ts> concept   field_operators_q = (...and   field_operators_p<based_t<Ts>>);
template <class ...Ts> concept   group_operators_q = (...and   group_operators_p<based_t<Ts>>);
template <class ...Ts> concept         operators_q = field_operators_q<Ts...> or group_operators_q<Ts...>;

template <class ...Ts> concept inequality_comparators_q = numeric_q<Ts...> and (...and inequality_comparators_p<based_t<Ts>>);
template <class ...Ts> concept   equality_comparators_q = numeric_q<Ts...> and (...and   equality_comparators_p<based_t<Ts>>);
template <class ...Ts> concept            comparators_q = equality_comparators_q<Ts...> and inequality_comparators_q<Ts...>;

static_assert(bitwise_operators_q<int>);
static_assert(  group_operators_q<int>);
static_assert(  field_operators_q<float>);
static_assert(  field_operators_q<_std::complex<float>>);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class    T >       using iterate_t  = _v3::ranges::view_interface<T>;

template <class    T >       using begin_t    = decltype(XTAL_VAL_(T).begin());
template <class    T >       using   end_t    = decltype(XTAL_VAL_(T).  end());
template <class    T >     concept begin_p    = requires (T t) {*t.begin();};
template <class    T >     concept   end_p    = requires (T t) {*t.  end();};
template <class ...Ts>     concept begin_q    = (...and begin_p<Ts>);
template <class ...Ts>     concept   end_q    = (...and   end_p<Ts>);

template <class ...Ts>     concept bracket_q  = begin_q<Ts...> and end_q<Ts...>;
template <class    W >       using bracket_t  = _std::initializer_list<W>;
template <class    W >       using interval_t = _v3::ranges::iota_view<W, W>;


template <class    T >     concept iterable_p = begin_p<T> and not requires (T t) {t.front();};
template <class    T >     concept iterated_p = begin_p<T> and     requires (T t) {t.front();};
template <class    T >     concept iterator_p = requires (T t) {*++t;};
template <class    T >     concept integral_p = _std::integral<T>;

template <class ...Ts>     concept iterable_q = (...and iterable_p<Ts>);
template <class ...Ts>     concept iterated_q = (...and iterated_p<Ts>);//_v3::ranges::forward_range
template <class ...Ts>     concept iterator_q = (...and iterator_p<Ts>);//_v3::ranges::forward_iterator
template <class ...Ts>     concept integral_q = (...and integral_p<Ts>);

template <class    T >      struct iterated;
template <class    T >      struct iterator;
template <class    T >      struct iteratee;

template <class    T >       using iterated_t = typename iterated<T>::type;
template <class    T >       using iterator_t = typename iterator<T>::type;//_v3::ranges::iterator_t
template <class    T >       using iteratee_t = typename iteratee<T>::type;//_v3::ranges::range_reference_t, _v3::ranges::iter_reference_t

template <iterated_p T>     struct iterated<T>: constant_t<1> {using type =               based_t<T> ;};
template <iterator_p T>     struct iterated<T>: constant_t<0> {using type =                     void ;};
template <integral_p T>     struct iterated<T>: constant_t<0> {using type =            interval_t<T> ;};

template <iterable_p T>     struct iterator<T>: constant_t<0> {using type =               begin_t<T> ;};
template <iterated_p T>     struct iterator<T>: constant_t<0> {using type =               begin_t<T> ;};
template <iterator_p T>     struct iterator<T>: constant_t<1> {using type =               based_t<T> ;};
template <integral_p T>     struct iterator<T>: constant_t<0> {using type = iterator_t<interval_t<T>>;};

template <iterable_p T>     struct iteratee<T>: constant_t<0> {using type =     pointed_t<begin_t<T>>;};
template <iterated_p T>     struct iteratee<T>: constant_t<0> {using type =     pointed_t<begin_t<T>>;};
template <iterator_p T>     struct iteratee<T>: constant_t<0> {using type =             pointed_t<T> ;};
template <integral_p T>     struct iteratee<T>: constant_t<1> {using type =               based_t<T> ;};

template <class ...Ts>   concept uniterable_q = not (...or iterable_p<Ts>);
template <class ...Ts>   concept uniterated_q = not (...or iterated_p<Ts>);
template <class ...Ts>   concept uniterator_q = not (...or iterator_p<Ts>);
template <class ...Ts>   concept unintegral_q = not (...or integral_p<Ts>);


template <class    T >       using sentinel_t = based_t<_v3::ranges::sentinel_t<T>>;
template <class    T >       using distance_t = XTAL_TYP_(_std::distance(XTAL_VAL_(iterator_t<T>), XTAL_VAL_(iterator_t<T>)));
template <class    T >       using deranged_t = _v3::ranges::subrange<iterator_t<T>, sentinel_t<T>>;
template <class    T >    XTAL_CN2 deranged_f(T &&t) XTAL_0EX {return deranged_t<T>(XTAL_REF_(t));}

template <iterator_q I>   XTAL_CN2 reverser_f(I   i) XTAL_0EX {return _std::make_reverse_iterator(i);}
template <iterator_q I>   XTAL_CN2    mover_f(I   i) XTAL_0EX {return _std::   make_move_iterator(i);}


template <class    T >     concept counted_p  = iterated_q<T> and to_q<T, interval_t<iteratee_t<T>>>;
template <class    T >     concept counter_p  = integral_q<T>;

template <class ...Ts>     concept counted_q  = (...and counted_p<Ts>);
template <class ...Ts>     concept counter_q  = (...and counter_p<Ts>);

template <class    T >      struct counted;
template <class    T >      struct counter;

template <counted_p T>      struct counted<T> : constant_t<1> {using type =    based_t<T>;};
template <counter_p T>      struct counted<T> : constant_t<0> {using type = iterated_t<T>;};

template <counted_p T>      struct counter<T> : constant_t<0> {using type = iteratee_t<T>;};
template <counter_p T>      struct counter<T> : constant_t<1> {using type =    based_t<T>;};

template <class T=size_x>    using counted_t  = typename counted<T>::type;
template <class T=size_x>    using counter_t  = typename counter<T>::type;

template <counter_p I>     XTAL_CN2 counted_f(I i0, I iN) {return counted_t<I>(i0, iN);}
template <class    T>      XTAL_CN2 counted_f(T &&t)      {return counted_t<T>(XTAL_REF_(t));}
template <class    T>      XTAL_CN2 counter_f(T &&t)      {return counter_t<T>(XTAL_REF_(t));}
template <class    T>
XTAL_CN2 count_f(T &&t)
XTAL_0EX
{
	if constexpr (counter_q<T>) {
		return XTAL_REF_(t);
	}
	else if constexpr (counted_q<T>) {
		return 1 + t.back() - XTAL_REF_(t).front();
	}
	else if constexpr (bracket_q<T>) {
		return      t.end() - XTAL_REF_(t).begin();
	}
	else if constexpr (requires {t.size();}) {
		return XTAL_REF_(t).size();
	}
	else {
		return (sign_t) 0;
	}
}
///<\returns the `size` of the given range. \

///<\note\
If provided with an `iota_view`, \
returns a `value_type` instead of `size_type` which is twice the width. \

template <class  T>
XTAL_CN2 recount_f(T &&t)
XTAL_0EX
{
	return _v3::views::take(count_f(XTAL_REF_(t)));
}


template <class      ...Ts> concept beginning_q      = begin_q<Ts...> and is_q<begin_t<Ts>...>;
template <class      ...Ts> concept bracketing_q     = beginning_q<Ts...> and end_q<Ts...>;

template <class      ...Ts>  struct isomorphic       : isotropic<Ts...> {};
template <iterated_q ...Ts>  struct isomorphic<Ts...>: isomorphic<iteratee_t<Ts>...> {};
template <iterator_q ...Ts>  struct isomorphic<Ts...>: isomorphic<iteratee_t<Ts>...> {};
template <class      ...Ts> concept isomorphic_p =     isomorphic<Ts...>::value;

template <class      ...Ts>  struct epimorphic       : epitropic<Ts...> {};
template <iterated_q ...Ts>  struct epimorphic<Ts...>: epimorphic<iteratee_t<Ts>...> {};
template <iterator_q ...Ts>  struct epimorphic<Ts...>: epimorphic<iteratee_t<Ts>...> {};
template <class      ...Ts> concept epimorphic_p =     epimorphic<Ts...>::value;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./any.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
