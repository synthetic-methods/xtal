#pragma once
#if __has_include(<execution>)
#include <execution>
#endif
#include <concepts>
#include <cassert>
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
template <typename T, typename S>
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


using size_t = XTAL_STD_(size_t);
using sign_t = XTAL_STD_(sign_t);
using null_t = XTAL_STD_(null_t);
using unit_t = XTAL_STD_(unit_t);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <auto     ...Ns >  concept conjunct_q = (bool(Ns) and...);
template <auto     ...Ns >  concept disjunct_q = (bool(Ns)  or...);
template <typename ...Ts >    using conjunct_t = _std::conjunction<Ts...>;
template <typename ...Ts >    using disjunct_t = _std::disjunction<Ts...>;

template <auto        N  >    using constant_t = _std::integral_constant<XTAL_TYP_(N), N>;
template <auto        N  > XTAL_CN2 constant_f() {using T = constant_t<N>; return T();};
template <typename    T  >  concept constant_p = _std::derived_from<T, _std::integral_constant<typename T::value_type, T::value>>;
template <typename ...Ts >  concept constant_q =     conjunct_q<constant_p<Ts>...>;
template <typename ...Ts >  concept variable_q = not disjunct_q<constant_p<Ts>...>;
template <constant_p  T  > XTAL_LET constant_v = T::value;



template <typename    T  >    using based_t    = _std::remove_cvref_t<T>;
template <typename    T  >  concept based_p    = _std::is_trivially_copyable_v<T>;
template <typename ...Ts >  concept based_q    = conjunct_q<based_p<Ts>...>;

template <typename    T  >  concept unbased_p  = not based_p<T>;
template <typename ...Ts >  concept unbased_q  = conjunct_q<unbased_p<Ts>...>;

template <typename    T  >   struct debased            : constant_t<0> {using type = based_t<T>;};
template <unbased_p   T  >   struct debased<T        &>: constant_t<1> {using type =         T*;};
template <unbased_p   T  >   struct debased<T  const &>: constant_t<1> {using type =   const T*;};
template <typename    T  >    using debased_t  =   typename debased<T>::type;
template <typename ...Ts >  concept debased_q  = conjunct_q<debased<Ts>::value...>;

template <typename    T  >   struct rebased            : constant_t<1> {using type = based_t<T>;};
template <unbased_p   T  >   struct rebased<T        &>: constant_t<0> {using type =         T&;};
template <unbased_p   T  >   struct rebased<T  const &>: constant_t<0> {using type =   const T&;};
template <typename    T  >    using rebased_t  =   typename rebased<T>::type;
template <typename ...Ts >  concept rebased_q  = conjunct_q<rebased<Ts>::value...>;


template <typename    T  >    using value_t    = typename based_t<T>::value_type;
template <typename    T  >  concept value_p    = requires {typename value_t<T>;};
template <typename ...Ts >  concept value_q    = conjunct_q<value_p<Ts>...>;
template <typename    T  > XTAL_LET value_v    = based_t<T>::value;

template <typename    T  >   struct revalue     {using value_type = based_t<T>;};
template <value_p     T  >   struct revalue<T> : based_t<T> {};
template <typename    T  >    using revalue_t  = value_t<revalue<T>>;


template <typename    T  >    using front_t    = decltype(*XTAL_VAL_(T).begin());
template <typename    T  >    using begin_t    = decltype( XTAL_VAL_(T).begin());
template <typename    T  >    using  back_t    = decltype(*XTAL_VAL_(T).  end());
template <typename    T  >    using   end_t    = decltype( XTAL_VAL_(T).  end());

template <typename    T  >  concept front_p    = requires (T t) { t.front();};
template <typename    T  >  concept begin_p    = requires (T t) {*t.begin();};
template <typename    T  >  concept  back_p    = requires (T t) { t. back();};
template <typename    T  >  concept   end_p    = requires (T t) {*t.  end();};

template <typename ...Ts >  concept front_q    = conjunct_q<front_p<Ts>...>;
template <typename ...Ts >  concept begin_q    = conjunct_q<begin_p<Ts>...>;
template <typename ...Ts >  concept  back_q    = conjunct_q< back_p<Ts>...>;
template <typename ...Ts >  concept   end_q    = conjunct_q<  end_p<Ts>...>;


template <typename    T  >
struct aligned
{
	class type {alignas(alignof(T)) _std::byte data[sizeof(T)];};
	XTAL_LET value = sizeof(type);

};
template <typename    T  >    using aligned_t  = typename aligned<T>::type;
template <typename    T  > XTAL_LET aligned_v  =          aligned<T>::value;
template <typename    I  >
XTAL_LET appointer_f = [] (XTAL_DEF i) XTAL_0FN_(_std::launder(reinterpret_cast<I>(XTAL_REF_(i))));
XTAL_LET   pointer_f = [] (XTAL_DEF o) XTAL_0FN_(_std::addressof(XTAL_REF_(o)));
XTAL_LET   pointer_e = [] (XTAL_DEF o, XTAL_DEF ...oo)
XTAL_0FN_((pointer_f(XTAL_REF_(o)) == pointer_f(XTAL_REF_(oo))) and ... and true);

template <typename    T  >    using pointed_t  = XTAL_TYP_(*XTAL_VAL_(T));
template <typename ...Ts >  concept pointer_q  = conjunct_q<_std::is_pointer_v<_std::decay_t<Ts>>...>;
template <typename ...Ts >  concept bracket_q  = conjunct_q<begin_p<Ts>..., end_p<Ts>...>;
template <typename    W  >    using bracket_t  = _std::initializer_list<W>;


template <typename             ...Ts> struct  identical;
template <typename             ...Ts> struct  isotropic;
template <typename             ...Ts> struct allotropic;

template <typename T, typename ...Ts> struct  identical<T, Ts...>: disjunct_t<_std::is_same<T, Ts>...> {};
template <typename T, typename ...Ts> struct  isotropic<T, Ts...>: disjunct_t<_std::is_same<based_t<T>, based_t<Ts>>...> {};
template <typename T, typename ...Ts> struct allotropic<T, Ts...>: conjunct_t<_std::is_constructible<T, Ts>...> {};

template <typename ...Ts>  concept id_q =  identical<Ts...>::value;
template <typename ...Ts>  concept is_q =  isotropic<Ts...>::value;
template <typename ...Ts>  concept to_q = allotropic<Ts...>::value;
template <typename    T > XTAL_LET to_f = [] XTAL_1FN_(based_t<T>);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename    T  > concept    iota_p = _std::         integral<based_t<T>>;
template <typename    T  > concept   delta_p = _std::  signed_integral<based_t<T>>;
template <typename    T  > concept   sigma_p = _std::unsigned_integral<based_t<T>>;
template <typename    T  > concept   alpha_p = _std::   floating_point<based_t<T>>;

template <typename ...Ts > concept    iota_q = conjunct_q< iota_p<Ts>...>;
template <typename ...Ts > concept   delta_q = conjunct_q<delta_p<Ts>...>;
template <typename ...Ts > concept   sigma_q = conjunct_q<sigma_p<Ts>...>;
template <typename ...Ts > concept   alpha_q = conjunct_q<alpha_p<Ts>...>;
template <typename ...Ts > concept numeric_q = iota_q<Ts...> or alpha_q<Ts...>;


///\returns `true` if `T` supports bitwise logical operations, `false` otherwise, \
with `0 < N_arity` differentiating between immutable (`2`) and mutable (`1`) operations. \

template <typename T, size_t N_arity=0>
concept binary_operators_p = iota_p<T> or requires (T t, T u)
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

template <typename T, size_t N_arity=0>
concept group_operators_p = iota_p<T> or requires (T t, T u)
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

template <typename T, size_t N_arity=0>
concept field_operators_p = alpha_p<T> or requires (T t, T u)
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
} and not binary_operators_p<T, N_arity>;


template <typename T>
concept inequality_p = requires (T t, T u)
{
	{t <= u} -> is_q<bool>;
	{t <  u} -> is_q<bool>;
	{t >= u} -> is_q<bool>;
	{t >  u} -> is_q<bool>;
};
template <typename T>
concept equality_p = requires (T t, T u)
{
	{t == u} -> is_q<bool>;
	{t != u} -> is_q<bool>;
};
template <typename T>
concept quality_p = equality_p<T> or inequality_p<T>;


template <typename T>
concept complex_p = value_p<T> and is_q<_std::complex<value_t<T>>> or requires (T t)
{
	requires equality_p<T>;
	requires field_operators_p<T, 2>;
	{t.real()} -> _std::same_as<value_t<T>>;
	{t.imag()} -> _std::same_as<value_t<T>>;
};


template <typename ...Ts > concept binary_operators_q = conjunct_q<binary_operators_p<based_t<Ts>>...>;
template <typename ...Ts > concept  field_operators_q = conjunct_q<field_operators_p<based_t<Ts>>...>;
template <typename ...Ts > concept  group_operators_q = conjunct_q<group_operators_p<based_t<Ts>>...>;
template <typename ...Ts > concept        operators_q = field_operators_q<Ts...> or group_operators_q<Ts...>;

template <typename ...Ts > concept       inequality_q = numeric_q<Ts...> and conjunct_q<inequality_p<based_t<Ts>>...>;
template <typename ...Ts > concept         equality_q = numeric_q<Ts...> and conjunct_q<  equality_p<based_t<Ts>>...>;
template <typename ...Ts > concept          quality_q = equality_q<Ts...> or inequality_q<Ts...>;

template <typename ...Ts>  concept          complex_q = conjunct_q<complex_p<Ts>...>;

static_assert(binary_operators_q<int>);
static_assert(group_operators_q<int>);
static_assert(field_operators_q<float>);
static_assert(field_operators_q<_std::complex<float>>);




template <typename T>
using unsigned_t = _std::make_unsigned_t<T>;

XTAL_CN2 unsigned_f(delta_q auto n)
XTAL_0EX
{
	using V = XTAL_TYP_(n);
	using U = unsigned_t<V>;
	U constexpr N = sizeof(n) << 3;
	U constexpr M = N - 1;
	V const m = n >> M;
	n += m;
	n ^= m;
	return (U) n;
}
static_assert(0 == unsigned_f( 0));
static_assert(1 == unsigned_f(+1));
static_assert(1 == unsigned_f(-1));
static_assert(2 == unsigned_f(+2));
static_assert(2 == unsigned_f(-2));


template <auto N>
concept sign_q = iota_q<decltype(N)> and -1 <= N and N <= 1;

template <sign_t N_zero=0>
XTAL_CN2 sign_f(delta_q auto n)
XTAL_0EX
{
	using V = XTAL_TYP_(n);
	using U = unsigned_t<V>;
	U constexpr N = sizeof(n) << 3;
	U constexpr M = N - 1;
	if constexpr (N_zero == 0) {
		return V((0 <  n) - (n <  0));
	}
	else if constexpr (N_zero == +1) {
		n >>= M;
		n  |= 1;
		return n;
	//	return V((0 <= n) - (n <  0));
	}
	else if constexpr (N_zero == -1) {
		return V((0 <  n) - (n <= 0));
	}
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename    T  >    using iterate_t  = _v3::ranges::view_interface<T>;


template <typename    T  >  concept iterable_p = begin_p<T> and not front_p<T>;
template <typename    T  >  concept iterated_p = begin_p<T> and     front_p<T>;
template <typename    T  >  concept iterator_p = requires (T t) {*++t;};
template <typename    T  >  concept integral_p = _std::integral<T>;

template <typename ...Ts >  concept iterable_q = conjunct_q<iterable_p<Ts>...>;
template <typename ...Ts >  concept iterated_q = conjunct_q<iterated_p<Ts>...>;//_v3::ranges::forward_range
template <typename ...Ts >  concept iterator_q = conjunct_q<iterator_p<Ts>...>;//_v3::ranges::forward_iterator
template <typename ...Ts >  concept integral_q = conjunct_q<integral_p<Ts>...>;

template <typename    T  >   struct iterated;
template <typename    T  >   struct iterator;
template <typename    T  >   struct iteratee;

template <typename    T  >    using iterated_t = typename iterated<T>::type;
template <typename    T  >    using iterator_t = typename iterator<T>::type;//_v3::ranges::iterator_t
template <typename    T  >    using iteratee_t = typename iteratee<T>::type;//_v3::ranges::range_reference_t, _v3::ranges::iter_reference_t

template <iterated_p  T  >   struct iterated<T>: constant_t<1> {using type =                  based_t<T> ;};
template <iterator_p  T  >   struct iterated<T>: constant_t<0> {using type =                   void      ;};
template <integral_p  T  >   struct iterated<T>: constant_t<0> {using type = _v3::ranges::iota_view<T, T>;};

template <iterable_p  T  >   struct iterator<T>: constant_t<0> {using type =                  begin_t<T> ;};
template <iterated_p  T  >   struct iterator<T>: constant_t<0> {using type =                  begin_t<T> ;};
template <iterator_p  T  >   struct iterator<T>: constant_t<1> {using type =                  based_t<T> ;};
template <integral_p  T  >   struct iterator<T>: constant_t<0> {using type =    iterator_t<iterated_t<T>>;};

template <iterable_p  T  >   struct iteratee<T>: constant_t<0> {using type =                  front_t<T> ;};
template <iterated_p  T  >   struct iteratee<T>: constant_t<0> {using type =                  front_t<T> ;};
template <iterator_p  T  >   struct iteratee<T>: constant_t<0> {using type =                pointed_t<T> ;};
template <integral_p  T  >   struct iteratee<T>: constant_t<1> {using type =                  based_t<T> ;};


template <typename    T  >    using sentinel_t = based_t<_v3::ranges::sentinel_t<T>>;
template <typename    T  >    using distance_t = XTAL_TYP_(_std::distance(XTAL_VAL_(iterator_t<T>), XTAL_VAL_(iterator_t<T>)));
template <typename    T  >    using deranged_t = _v3::ranges::subrange<iterator_t<T>, sentinel_t<T>>;
XTAL_LET  deranged_f = [] (XTAL_DEF t)
XTAL_0FN_(deranged_t<decltype(t)>(XTAL_REF_(t)));


using count_t = _std::make_unsigned_t<size_t>;

template <typename    T  >  concept counted_p  = iterated_q<T> and is_q<iterator_t<T>, iterator_t<iteratee_t<T>>>;//is_q<T, iterated_t<iteratee_t<T>>>;
template <typename    T  >  concept counter_p  = integral_q<T>;

template <typename ...Ts >  concept counted_q  = (counted_p<Ts> and ...);
template <typename ...Ts >  concept counter_q  = (counter_p<Ts> and ...);

template <typename    T  >   struct counted;
template <typename    T  >   struct counter;

template <counted_p   T  >   struct counted<T> : constant_t<1> {using type =    based_t<T>;};
template <counter_p   T  >   struct counted<T> : constant_t<0> {using type = iterated_t<T>;};

template <counted_p   T  >   struct counter<T> : constant_t<0> {using type = iteratee_t<T>;};
template <counter_p   T  >   struct counter<T> : constant_t<1> {using type =    based_t<T>;};

template <typename T=count_t> using counted_t  = typename counted<T>::type;
template <typename T=count_t> using counter_t  = typename counter<T>::type;
template <typename T>
XTAL_CN2 count_f(T &&t)
{
	if constexpr (counted_q<T>) {
		return 1 + t.back() - XTAL_REF_(t).front();
	}
	else if constexpr (bracket_q<T>) {
		return      t.end() - XTAL_REF_(t).begin();
	}
	else if constexpr (requires {t.size();}) {
		return XTAL_REF_(t).size();
	}
	else {
		return (distance_t<T>) -1;
	}
}
///<\returns the `size` of the given range. \

///<\note\
If provided with an `iota_view`, \
returns a `value_type` instead of `size_type` which is twice the width. \


template <typename   ...Ts>  struct isomorphic       : isotropic<Ts...> {};
template <iterated_q ...Ts>  struct isomorphic<Ts...>: isomorphic<iteratee_t<Ts>...> {};
template <iterator_q ...Ts>  struct isomorphic<Ts...>: isomorphic<iteratee_t<Ts>...> {};
template <typename   ...Ts> concept isomorphic_q =     isomorphic<Ts...>::value;

template <typename   ...Ts>  struct allomorphic       : allotropic<Ts...> {};
template <iterated_q ...Ts>  struct allomorphic<Ts...>: allomorphic<iteratee_t<Ts>...> {};
template <iterator_q ...Ts>  struct allomorphic<Ts...>: allomorphic<iteratee_t<Ts>...> {};
template <typename   ...Ts> concept allomorphic_q =     allomorphic<Ts...>::value;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "./any.hxx"


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
