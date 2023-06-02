#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

using size_t = XTAL_STD_(size_t);
using sign_t = XTAL_STD_(sign_t);
using null_t = XTAL_STD_(null_t);
using unit_t = XTAL_STD_(unit_t);

template <auto        N  > concept      sign_q = _std::integral<decltype(N)> and -1 <= N and N <= 1;
template <auto     ...Ns > concept     every_q = (bool(Ns) and...);

template <typename    T  > using       based_t = _std::remove_cvref_t<T>;
template <typename    T  > concept     based_p = _std::is_trivially_copy_constructible_v<based_t<T>>;
template <typename ...Ts > concept     based_q = every_q<based_p<Ts>...>;

template <typename    T  > using       value_t = typename based_t<T>::value_type;
template <typename    T  > concept     value_p = requires {typename value_t<T>;};
template <typename ...Ts > concept     value_q = every_q<value_p<Ts>...>;
template <typename    T  > XTAL_LET    value_v = based_t<T>::value;

template <typename    T  > concept   unbased_p = not based_p<T>;
template <typename ...Ts > concept   unbased_q = every_q<unbased_p<Ts>...>;

template <typename    T  > struct    debased           : _std::false_type {using type = based_t<T>;};
template <unbased_p   T  > struct    debased<T       &>: _std:: true_type {using type =         T*;};
template <unbased_p   T  > struct    debased<T const &>: _std:: true_type {using type =   const T*;};
template <typename    T  > using     debased_t =  typename debased<T>::type;
template <typename    T  > concept   debased_p =           debased<T>::value;
template <typename ...Ts > concept   debased_q = every_q<debased_p<Ts>...>;

template <typename    T  > struct    rebased           : _std:: true_type {using type = based_t<T>;};
template <unbased_p   T  > struct    rebased<T       &>: _std::false_type {using type =         T&;};
template <unbased_p   T  > struct    rebased<T const &>: _std::false_type {using type =   const T&;};
template <typename    T  > using     rebased_t =  typename rebased<T>::type;
template <typename    T  > concept   rebased_p =           rebased<T>::value;
template <typename ...Ts > concept   rebased_q = every_q<rebased_p<Ts>...>;

template <typename    T  > struct    revalue    {using value_type = based_t<T>;};
template <value_p     T  > struct    revalue<T>: based_t<T> {};
template <typename    T  > using     revalue_t = value_t<revalue<T>>;

template <typename    T  > concept   pointer_p = _std::is_pointer_v<_std::decay_t<T>>;
template <typename ...Ts > concept   pointer_q = every_q<pointer_p<Ts>...>;

template <auto        N  > using    constant   = _std::integral_constant<XTAL_TYP_(N), N>;
template <typename    T  > concept  constant_p = _std::is_base_of_v<_std::integral_constant<typename T::value_type, T::value>, T>;
template <typename ...Ts > concept  constant_q = every_q<constant_p<Ts>...>;

XTAL_LET pointer_f  = [](XTAL_DEF o) XTAL_0FN_(_std::addressof(XTAL_REF_(o)));
XTAL_LET pointer_eq = [](XTAL_DEF o, XTAL_DEF ...oo)
XTAL_0FN_((pointer_f(XTAL_REF_(o)) == pointer_f(XTAL_REF_(oo))) and ... and true);


///////////////////////////////////////////////////////////////////////////////

template <typename             ...Ys> struct identical          : _std::false_type {};
template <typename T, typename ...Ys> struct identical<T, Ys...>: _std::disjunction<_std::is_same<T, Ys>...> {};
template <typename             ...Ys> struct isomeric           : identical<based_t<Ys>...> {};
template <typename             ...Ys> struct isomorphic         : isomeric<Ys...> {};

template <typename ...Ys>             concept  id_q = identical <Ys...>::value;
template <typename ...Ys>             concept  is_q = isomeric  <Ys...>::value;
template <typename ...Ys>             concept iso_q = isomorphic<Ys...>::value;

template <typename Y, typename    T > concept  if_p = _std::is_base_of_v<based_t<Y>, based_t<T>>;
template <typename Y, typename ...Ts> concept  if_q = every_q<if_p<Y, Ts>...>;

template <typename T, typename    Y > concept  to_p = requires (T t) {based_t<Y>(t);};// remove `based_t`?
template <typename T, typename ...Ys> concept  to_q = every_q<to_p<T, Ys>...>;

template <typename T> XTAL_LET to_f = [](XTAL_DEF ...oo) XTAL_0FN_(based_t<T>(XTAL_REF_(oo)...));

template <template <typename...> typename T_>                 struct  of_t {};
template <template <typename...> typename T_, typename ...Ts> concept of_q = if_q<of_t<T_>, Ts...>;


template <typename T> concept dismember_p = debased_p<T>;// determine whether `T` should be dereferenced
template <typename T> using      member_t = debased_t<T>;// convert references to pointers

template <typename T> XTAL_FZ2 member_f(XTAL_DEF w) XTAL_QEX dismember_p<T> {return &XTAL_REF_(w);}// obtain address
template <typename T> XTAL_FZ2 member_f(XTAL_DEF w) XTAL_0EX                {return to_f<T>(XTAL_REF_(w));}
template <typename T> XTAL_FZ2 member_f(XTAL_DEF ...ws) XTAL_0EX            {return to_f<T>(XTAL_REF_(ws)...);}

XTAL_FZ2 remember_y(XTAL_DEF w) XTAL_QEX requires {*w;} {return *XTAL_REF_(w);}// dereference address
XTAL_FZ2 remember_y(XTAL_DEF w) XTAL_0EX                {return  XTAL_REF_(w);}

XTAL_FZ2 remember_x(XTAL_DEF w) XTAL_QEX requires {*w;} {return *_std::move(XTAL_REF_(w));}// dereference address
XTAL_FZ2 remember_x(XTAL_DEF w) XTAL_0EX                {return  _std::move(XTAL_REF_(w));}

template <typename T> concept remember_p = not dismember_p<T>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
