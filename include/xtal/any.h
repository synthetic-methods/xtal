#pragma once


#ifndef XTAL_DOC
////////////////////////////////////////////////////////////////////////////////

#if __has_include(<execution>)
#include <execution>
#endif
#include <concepts>
#include <variant>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <complex>
#include <numbers>
#include <limits>
#include <cmath>
#include <array>
#include <tuple>
#include <queue>
#include <new>
#include <bit>


////////////////////////////////////////////////////////////////////////////////
#endif

#define XTAL_K_(...) XTAL_k_(__VA_ARGS__,,,,,,,,,,,,,,,,,,,,,,,,,,)                 ///< Concatenate.
#define XTAL_k_(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, ...)\
                A##B##C##D##E##F##G##H##I##J##K##L##M##N##O##P##Q##R##S##T##U##V##W##X##Y##Z

#define XTAL_Q_(...)                                         XTAL_q_(__VA_ARGS__)   ///< Stringify.
#define XTAL_q_(...)                                                #__VA_ARGS__

#define XTAL_N_(F0,...)                __VA_OPT__(XTAL_X_(XTAL_M_(F0,__VA_ARGS__))) ///< Map.
#define XTAL_M_(F0,A1,...)       F0(A1)__VA_OPT__(XTAL_M  XTAL_X (F0,__VA_ARGS__))
#define XTAL_M() XTAL_M_

#define XTAL_X ()
#define XTAL_X_(...)                                        XTAL_X4_(__VA_ARGS__)   ///< Repeat.
#define XTAL_X4_(...)            XTAL_X3_(XTAL_X3_(XTAL_X3_(XTAL_X3_(__VA_ARGS__))))
#define XTAL_X3_(...)            XTAL_X2_(XTAL_X2_(XTAL_X2_(XTAL_X2_(__VA_ARGS__))))
#define XTAL_X2_(...)            XTAL_X1_(XTAL_X1_(XTAL_X1_(XTAL_X1_(__VA_ARGS__))))
#define XTAL_X1_(...)            XTAL_X0_(XTAL_X0_(XTAL_X0_(XTAL_X0_(__VA_ARGS__))))
#define XTAL_X0_(...)                                                __VA_ARGS__

#define XTAL_(...)                                    XTAL_K_(XTAL,_,__VA_ARGS__)   ///< Name.


////////////////////////////////////////////////////////////////////////////////

#define XTAL_ENV_(NAME,...) XTAL_ENV_##NAME __VA_ARGS__///< Compiler version (`100*${major}.${minor}`), and `_Pragma`s.
#if 00//XTAL_ENV

#ifdef  NDEBUG
#define XTAL_ENV_release 1
#define XTAL_ENV_debug   0
#else
#define XTAL_ENV_release 0
#define XTAL_ENV_debug   1
#endif


#elif   defined(_MSC_VER)
#define XTAL_ENV_MSVC   (_MSC_VER)
#define XTAL_ENV_LLVM   0
#define XTAL_ENV_GNUC   0
#define XTAL_ENV_pop   _Pragma("warning(pop)")
#define XTAL_ENV_push  _Pragma("warning(push)")\
                       _Pragma("warning(disable:4010)")\

#elif   defined(__clang__)
#define XTAL_ENV_LLVM   (100*__clang_major__ + __clang_minor__)
#define XTAL_ENV_GNUC   0
#define XTAL_ENV_MSVC   0
#define XTAL_ENV_pop   _Pragma("clang diagnostic pop")
#define XTAL_ENV_push  _Pragma("clang diagnostic push")\
                       _Pragma("clang diagnostic ignored \"-Wcomment\"")\
                       _Pragma("clang diagnostic ignored \"-Wdocumentation\"")\
                       _Pragma("clang diagnostic ignored \"-Wconstant-conversion\"")\
                       _Pragma("clang diagnostic ignored \"-Wunused-local-typedef\"")\
                       _Pragma("clang diagnostic ignored \"-Wshift-op-parentheses\"")\
                       _Pragma("clang diagnostic ignored \"-Wlogical-op-parentheses\"")\

#elif   defined(__GNUC__)
#define XTAL_ENV_GNUC   (100*__GNUC__ + __GNUC_MINOR__)
#define XTAL_ENV_MSVC   0
#define XTAL_ENV_LLVM   0
#define XTAL_ENV_pop   _Pragma("GCC diagnostic pop")
#define XTAL_ENV_push  _Pragma("GCC diagnostic push")\
                       _Pragma("GCC diagnostic ignored \"-Wsubobject-linkage\"")\

#else
#endif//XTAL_ENV
#define XTAL_ENV_GCC XTAL_ENV_(GNUC)
#define XTAL_ENV (XTAL_ENV_(MSVC) or XTAL_ENV_(LLVM) or XTAL_ENV_(GNUC))



XTAL_ENV_(push)
///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

#define XTAL_STD_(ARG,...)             XTAL_STD_##ARG __VA_OPT__((__VA_ARGS__)) ///< C++ standard version (YYMM) and reference types.
#ifdef  XTAL_STD
#elif   2000 >   (__cplusplus%10000)
#define XTAL_STD (2000)                                                         ///< C++ standard version minimum (YYMM).
#elif   2600 <   (__cplusplus%10000)
#define XTAL_STD (2600)                                                         ///< C++ standard version maximum (YYMM).
#else
#define XTAL_STD (__cplusplus%10000)                                            ///< C++ standard version         (YYMM).
#endif

#define XTAL_STD_null_type      ::std::nullptr_t
#define XTAL_STD_unit_type      ::std::monostate
#define XTAL_STD_size_type      ::std::size_t
#define XTAL_STD_extent_type    ::std::ptrdiff_t

#define XTAL_STD_flt(...)              XTAL_STD_flt_##__VA_ARGS__
#define XTAL_STD_flt_0                 void
#define XTAL_STD_flt_1                 void
#define XTAL_STD_flt_2                 float
#define XTAL_STD_flt_3                 double
#define XTAL_STD_flt_4            long double

#define XTAL_STD_int(...)              XTAL_STD_int_##__VA_ARGS__
#define XTAL_STD_int_0          ::std::int8_t
#define XTAL_STD_int_1          ::std::int16_t
#define XTAL_STD_int_2          ::std::int32_t
#define XTAL_STD_int_3          ::std::int64_t
#define XTAL_STD_int_4       long long int


////////////////////////////////////////////////////////////////////////////////

#define XTAL_SYS_(ARG,...)             XTAL_SYS_##ARG __VA_OPT__((__VA_ARGS__)) ///< System reference values.

#ifdef  XTAL_SYS_IEC
#else
//\
#define XTAL_SYS_IEC                   0
#define XTAL_SYS_IEC                   60559
#endif

#ifdef  XTAL_SYS_L1
#elif   defined(__cacheline_aligned)
#define XTAL_SYS_L1 __cacheline_aligned
#elif   defined(L1_CACHE_BYTES)
#define XTAL_SYS_L1 L1_CACHE_BYTES
#elif   defined(L1_CACHE_SHIFT)
#define XTAL_SYS_L1 L1_CACHE_SHIFT
#else
#define XTAL_SYS_L1                    0x40
#endif//XTAL_STD_L1

#define XTAL_SYS_size(...)            (0x80000000 __VA_OPT__(/sizeof(__VA_ARGS__))) ///< `sizeof([])` limit in `MSVC`.
#define XTAL_SYS_extent(...)          (XTAL_SYS_size(__VA_ARGS__) - 1)

// TODO: Find better way to check for `__builtin_\w+`?
#define XTAL_SYS_builtin (XTAL_VER_(GNUC >= 1000) or XTAL_VER_(LLVM >= 1000))

#if          defined(FP_FAST_FMA) and     defined(FP_FAST_FMAF)
#define XTAL_SYS_FMA 0b110
#elif        defined(FP_FAST_FMA) and not defined(FP_FAST_FMAF)
#define XTAL_SYS_FMA 0b100
#elif    not defined(FP_FAST_FMA) and     defined(FP_FAST_FMAF)
#define XTAL_SYS_FMA 0b010
#elif    not defined(FP_FAST_FMA) and not defined(FP_FAST_FMAF)
#define XTAL_SYS_FMA 0b000
#endif

#if defined(    __aarch64__)\
 or defined(     __x86_64  )\
 or defined(     __x86_64__)\
 or defined(       _M_X64  )\
 or defined(      __amd64  )\
 or defined(      __amd64__)\
 or defined(     _M_AMD64  )\
 or defined(        _IA64  )\
 or defined(       __ia64  )\
 or defined(       __ia64__)\
 or defined(       __IA64__)\
 or defined(      _M_IA64  )\
 or defined(  __powerpc64__)\
 or defined(      __ppc64__)\
 or defined(      __PPC64__)\
 or defined(  _ARCH_PPC64  )\

#define XTAL_SYS_CPU 64
#else
#define XTAL_SYS_CPU 32
#endif

//#define XTAL_DOC_(...)           XTAL_DOC_##__VA_ARGS__
//#define XTAL_DOC_hide    /*!    \if FALSE */
//#define XTAL_DOC_show    /*! \endif       */

#define XTAL_LOG 1//NDEBUG


////////////////////////////////////////////////////////////////////////////////

#define XTAL_VER_MSVC            XTAL_ENV_MSVC and XTAL_ENV_MSVC
#define XTAL_VER_LLVM            XTAL_ENV_LLVM and XTAL_ENV_LLVM
#define XTAL_VER_GNUC            XTAL_ENV_GNUC and XTAL_ENV_GNUC
#define XTAL_VER_GCC             XTAL_VER_GNUC
#define XTAL_VER_STD             XTAL_STD
#if     XTAL_VER_STD >= 2300 and XTAL_VER_GNUC >= 1400
//\
#define XTAL_VER_ranges            -1
#define XTAL_VER_ranges             3
#else
#define XTAL_VER_ranges             3
#endif

#define XTAL_VER_(...) (false XTAL_N_(XTAL_VER,  __VA_ARGS__))///< Version checking.
#define XTAL_VER(...)              or XTAL_VER_##__VA_ARGS__


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define XTAL_NOM_(...)                 ::std::remove_cvref_t<__VA_ARGS__>       ///< Reveals the underlying-type.
#define XTAL_ALL_(...)                    XTAL_NOM_(decltype(__VA_ARGS__))      ///< Reveals the underlying-type of a value.
#define XTAL_ANY_(...)                        ::std::declval<__VA_ARGS__>()     ///< Yields the existential value for a type.
#define XTAL_MOV_(...)                        ::std::   move(__VA_ARGS__)       ///< Moves    a value.
#define XTAL_REF_(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)       ///< Forwards a value.
#ifndef XTAL_DOC
template <class X, class Y> concept XTAL_(generalized) = ::std::derived_from<XTAL_NOM_(Y), XTAL_NOM_(X)> and not ::std::same_as<XTAL_NOM_(X), XTAL_NOM_(Y)>;
template <class X, class Y> concept XTAL_(specialized) = ::std::derived_from<XTAL_NOM_(X), XTAL_NOM_(Y)> and not ::std::same_as<XTAL_NOM_(Y), XTAL_NOM_(X)>;
template <class X, class Y> concept XTAL_(relativized) = XTAL_(generalized)<X, Y> or XTAL_(specialized)<X, Y>;
#endif


////////////////////////////////////////////////////////////////////////////////

#define XTAL_DEF_(...)           XTAL_N_(XTAL_DEF,__VA_ARGS__)///< Leading `[[attributes]]` and `keywords`.
#define XTAL_DEF(...)            XTAL_DEF_##__VA_ARGS__

#define XTAL_DEF_return          [[nodiscard]]
#define XTAL_DEF_static          static
#define XTAL_DEF_friend          friend
#define XTAL_DEF_mutate        //NOTE: Mutability is the default!

#ifdef  XTAL_DOC
#define XTAL_DEF_verbatim
#elif   XTAL_ENV_MSVC
#define XTAL_DEF_verbatim      //NOTE: Use `#pragma optimize("", {off,on})`~
#elif   XTAL_ENV_LLVM
#define XTAL_DEF_verbatim        [[clang::optnone]]    __attribute__((optnone))
#elif   XTAL_ENV_GNUC
#define XTAL_DEF_verbatim        [[gnu::optimize(0)]]  __attribute__((optimize(0)))
#endif//XTAL_DEF_verbatim

#ifdef  XTAL_DOC
#define XTAL_DEF_inline
#elif   XTAL_ENV_MSVC
#define XTAL_DEF_inline        __forceinline
#else
#define XTAL_DEF_inline        __attribute__((always_inline))
#endif//XTAL_DEF_inline

#define XTAL_DEF_explicit        constexpr explicit                             ///< Start `explicit` function.
#define XTAL_DEF_implicit        constexpr                                      ///< Start `implicit` function.
#define XTAL_DEF_get      inline constexpr decltype(auto)                       ///< Start `decltype(auto)` function.
#define XTAL_DEF_let      inline constexpr auto                                 ///< Start `auto` function.
#define XTAL_DEF_met      inline constexpr auto friend                          ///< Start `auto` function (friend).
#define XTAL_DEF_set      static constexpr auto                                 ///< Start `auto` function (static).

#define XTAL_NEW_(ARG,...)       XTAL_NEW_##ARG __VA_OPT__((__VA_ARGS__))       ///< Start `(?:ex|im)plicit` constructor.
#define XTAL_NEW_explicit        constexpr explicit                             ///< Start        `explicit` constructor.
#define XTAL_NEW_implicit        constexpr                                      ///< Start        `implicit` constructor.

#define XTAL_NEW_then(TYP,...)   template     <class ...XTAL_(As)>                      \
                                 constexpr explicit TYP(XTAL_(As) &&...XTAL_(as))       \
                               __VA_ARGS__ (static_cast<XTAL_(As) &&> (XTAL_(as))...) {};

#define XTAL_NEW_cast(TYP,...)   template <XTAL_(relativized)  <TYP>    XTAL_(That)>    \
                                 constexpr     TYP(XTAL_(That)      &&  XTAL_(this))    \
                               __VA_ARGS__     TYP(static_cast <TYP &&>(XTAL_(this))) {};

#define XTAL_NEW_copy(TYP,...)   constexpr     TYP             (TYP const &) __VA_ARGS__;\
                                 constexpr     TYP & operator= (TYP const &) __VA_ARGS__;;///< Declare copy constructor/assignment for `TYP`, with suffix `...`.
#define XTAL_NEW_move(TYP,...)   constexpr     TYP             (TYP      &&) __VA_ARGS__;\
                                 constexpr     TYP & operator= (TYP      &&) __VA_ARGS__;;///< Declare move constructor/assignment for `TYP`, with suffix `...`.

#define XTAL_NEW_create(TYP,...) constexpr     TYP()                         __VA_ARGS__;
#define XTAL_NEW_delete(TYP,...) constexpr    ~TYP()                         __VA_ARGS__;


////////////////////////////////////////////////////////////////////////////////

#define XTAL_FX4_(ARG,...)    XTAL_FX4_##ARG __VA_OPT__((__VA_ARGS__))
#define XTAL_FX2_(ARG,...)    XTAL_FX2_##ARG __VA_OPT__((__VA_ARGS__))
#define XTAL_FX1_(ARG,...)    XTAL_FX1_##ARG __VA_OPT__((__VA_ARGS__))
#define XTAL_FX0_(ARG,...)    XTAL_FX0_##ARG __VA_OPT__((__VA_ARGS__))

#define XTAL_FX4_do(SIG,...)  SIG const &                 __VA_ARGS__   \
                              SIG       &                 __VA_ARGS__   \
                              SIG const &&                __VA_ARGS__   \
                              SIG       &&                __VA_ARGS__   ;///< Define `(const)? &&?` member functions.
#define XTAL_FX2_do(SIG,...)  SIG const                   __VA_ARGS__   \
                              SIG                         __VA_ARGS__   ;///< Define `(const)?`     member functions.
#define XTAL_FX1_do(SIG,...)  SIG const                   __VA_ARGS__   ;///< Define `(const) `     member function.
#define XTAL_FX0_do(SIG,...)  SIG                         __VA_ARGS__   ;///< Define         static member function.

#define XTAL_FX4_to(SIG,...)  SIG const &  noexcept __VA_OPT__({return (__VA_ARGS__);});\
                              SIG       &  noexcept __VA_OPT__({return (__VA_ARGS__);});\
                              SIG const && noexcept __VA_OPT__({return (__VA_ARGS__);});\
                              SIG       && noexcept __VA_OPT__({return (__VA_ARGS__);});;///< Define returning `noexcept` `(const)? &&?` member expressions.
#define XTAL_FX2_to(SIG,...)  SIG const    noexcept __VA_OPT__({return (__VA_ARGS__);});\
                              SIG          noexcept __VA_OPT__({return (__VA_ARGS__);});;///< Define returning `noexcept` `(const)?    ` member expressions.
#define XTAL_FX1_to(SIG,...)  SIG const    noexcept __VA_OPT__({return (__VA_ARGS__);});;///< Define returning `noexcept` `(const)     ` member expression.
#define XTAL_FX0_to(SIG,...)  SIG          noexcept __VA_OPT__({return (__VA_ARGS__);});;///< Define returning `noexcept`         static member expression.


////////////////////////////////////////////////////////////////////////////////

//\
#if not XTAL_ENV
#ifdef  XTAL_DOC
#define XTAL_0FN                 constexpr   noexcept///< Lambda declaration after `[captures]` and `(arguments)`.
#elif   XTAL_VER_(MSVC)
//\
#define XTAL_0FN                 constexpr   noexcept          [[msvc::forceinline]]//NOTE: Fixed 2024-12-27!
#define XTAL_0FN                 constexpr   noexcept
#elif   XTAL_VER_(GNUC)
#define XTAL_0FN                 constexpr   noexcept __attribute__((always_inline))
#elif   XTAL_VER_(LLVM)
#define XTAL_0FN                                      __attribute__((always_inline))\
                                 constexpr   noexcept
#endif//XTAL_0FN
#define XTAL_1FN                          () XTAL_0FN
#define XTAL_0FN_(ARG,...)                   XTAL_0FN_##ARG __VA_OPT__((__VA_ARGS__))                    ///< Lambda after `[captures]` and `(arguments)`.
#define XTAL_1FN_(ARG,...)                   XTAL_1FN_##ARG __VA_OPT__((__VA_ARGS__))                    ///< Lambda after `[captures]`.

#define XTAL_0FN_if(...)                     XTAL_0FN requires requires {         (__VA_ARGS__);} {}     ///< Lambda perform statement after `[captures]` and `(arguments)`.
#define XTAL_0FN_do(...)                     XTAL_0FN                   {         (__VA_ARGS__);}        ///< Lambda perform statement after `[captures]` and `(arguments)`.
#define XTAL_0FN_to(...)                     XTAL_0FN                   {return   (__VA_ARGS__);}        ///< Lambda return expression after `[captures]` and `(arguments)`.

#define XTAL_1FN_to(...)           <class ...XTAL_(As)>\
                                            (XTAL_(As) \
                                        &&...XTAL_(as))\
   XTAL_0FN_(to)                                           (__VA_ARGS__)                                 ///< Lambda ignoring arguments after `[captures]`.

#define XTAL_1FN_dot(...)          <class    XTAL_(T )>\
                                            (XTAL_(T ) \
                                           &&XTAL_(t ))\
   XTAL_0FN_(to)                  (XTAL_REF_(XTAL_(t )).__VA_ARGS__)                                 ///< Lambda forwarding to `.`member after `[captures]`.

#define XTAL_1FN_call(...)         <class ...XTAL_(As)>\
                                            (XTAL_(As) \
                                        &&...XTAL_(as))\
   XTAL_0FN_(to)      (__VA_ARGS__(XTAL_REF_(XTAL_(as))...))                                         ///< Lambda forwarding to call`(...)` after `[captures]`.

#define XTAL_1FN_make(...)         <class ...XTAL_(As)>\
                                            (XTAL_(As) \
                                        &&...XTAL_(as))\
   XTAL_0FN_(to)      (__VA_ARGS__{XTAL_REF_(XTAL_(as))...})                                         ///< Lambda forwarding to make`{...}` after `[captures]`.

#define XTAL_1FN_else(ARG,SYM,...)  (auto _) XTAL_0FN_(to) (ARG == _? _: _ SYM (__VA_ARGS__))            ///< Lambda conditional     after `[captures]`.
#define XTAL_1FN_and(...)                    XTAL_1FN_else(1, &, __VA_ARGS__)                            ///< Lambda conditional `&` after `[captures]`.
#define XTAL_1FN_or(...)                     XTAL_1FN_else(0, |, __VA_ARGS__)                            ///< Lambda conditional `|` after `[captures]`.


////////////////////////////////////////////////////////////////////////////////

#define XTAL_TRY_(ARG,...)                    XTAL_TRY_##ARG __VA_OPT__((__VA_ARGS__))

#define XTAL_TRY_do(...)              (requires{ __VA_ARGS__ ;}) {      (__VA_ARGS__);} ///< Check requirements, then invoke as block.
#define XTAL_TRY_to(...)              (requires{(__VA_ARGS__);}) {return(__VA_ARGS__);} ///< Check requirements, then return as expression.
#define XTAL_TRY_unless(...)      (not requires{ __VA_ARGS__ ;})                        ///< Check requirements failure.


////////////////////////////////////////////////////////////////////////////////


#define XTAL_IF1_(ARG,...)             XTAL_IF1_##ARG __VA_OPT__((__VA_ARGS__))          ///< Begin `else if constexpr` branch.
#define XTAL_0IF_(ARG,...)             XTAL_0IF_##ARG __VA_OPT__((__VA_ARGS__))          ///< Begin `else if constexpr` branch.

#define XTAL_IF0                             if constexpr (false);                       ///< Begin `else if constexpr` tree.
#define XTAL_0IF                       else  if constexpr
#define XTAL_0IF_else                  else

#if     XTAL_VER_(MSVC)
#define XTAL_0IF_terminate             else {__assume(false);}                           ///< Begin forbidden branch.
#else
#define XTAL_0IF_terminate             else {__builtin_unreachable();}                   ///< Begin forbidden branch.
#endif//XTAL_0IF_terminate

#define XTAL_IF1_do(...)                     if constexpr XTAL_TRY_do(__VA_ARGS__)
#define XTAL_0IF_do(...)               else  if constexpr XTAL_TRY_do(__VA_ARGS__)
#define XTAL_IF1_to(...)                     if constexpr XTAL_TRY_to(__VA_ARGS__)
#define XTAL_0IF_to(...)               else  if constexpr XTAL_TRY_to(__VA_ARGS__)
#define XTAL_IF1_unless(...)                 if constexpr XTAL_TRY_unless(__VA_ARGS__)
#define XTAL_0IF_unless(...)           else  if constexpr XTAL_TRY_unless(__VA_ARGS__)

#if     XTAL_VER_(STD >= 2600)
#define XTAL_IF1_consteval                   if                consteval                  ///< Begin constant-evaluated branch.
#define XTAL_0IF_consteval             else  if                consteval                  ///< Begin constant-evaluated branch.
#define XTAL_IF1_eval                        if  not           consteval                  ///< Begin non constant-evaluated branch.
#define XTAL_0IF_eval                  else  if  not           consteval                  ///< Begin non constant-evaluated branch.
#else
#define XTAL_IF1_consteval                   if (    ::std::is_constant_evaluated())      ///< Begin constant-evaluated branch.
#define XTAL_0IF_consteval             else  if (    ::std::is_constant_evaluated())      ///< Begin constant-evaluated branch.
#define XTAL_IF1_eval                        if (not ::std::is_constant_evaluated())      ///< Begin non constant-evaluated branch.
#define XTAL_0IF_eval                  else  if (not ::std::is_constant_evaluated())      ///< Begin non constant-evaluated branch.
#endif


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)


#ifndef XTAL_DOC
////////////////////////////////////////////////////////////////////////////////

#include <range/v3/all.hpp>
#if     XTAL_VER_(ranges !=  3)
#include <ranges>
#endif

#if     XTAL_LOG
#define  _LIBCPP_DEBUG XTAL_LOG
#define _GLIBCXX_DEBUG XTAL_LOG
#include <iostream>
#endif


////////////////////////////////////////////////////////////////////////////////
#endif

