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
#include <random>
#include <cmath>
#include <array>
#include <tuple>
#include <queue>
#include <new>
#include <bit>


////////////////////////////////////////////////////////////////////////////////
#endif

#define XTAL_APP ()

#define XTAL_APP_(...)                                       XTAL_APP_x4(__VA_ARGS__)   ///< Repeat.
#define XTAL_APP_x4(...) XTAL_APP_x3(XTAL_APP_x3(XTAL_APP_x3(XTAL_APP_x3(__VA_ARGS__))))
#define XTAL_APP_x3(...) XTAL_APP_x2(XTAL_APP_x2(XTAL_APP_x2(XTAL_APP_x2(__VA_ARGS__))))
#define XTAL_APP_x2(...) XTAL_APP_x1(XTAL_APP_x1(XTAL_APP_x1(XTAL_APP_x1(__VA_ARGS__))))
#define XTAL_APP_x1(...) XTAL_APP_x0(XTAL_APP_x0(XTAL_APP_x0(XTAL_APP_x0(__VA_ARGS__))))
#define XTAL_APP_x0(...)                                                 __VA_ARGS__

#define XTAL_MAP_(F0,...)          __VA_OPT__(XTAL_APP_(XTAL_MAP_this(F0,__VA_ARGS__))) ///< Map.
#define XTAL_MAP_then()                                 XTAL_MAP_this
#define XTAL_MAP_this(F0,A1,...)       F0(A1)__VA_OPT__(XTAL_MAP_then XTAL_APP (F0,__VA_ARGS__))

#define XTAL_VAL_(V0,...)          __VA_OPT__(XTAL_APP_(XTAL_VAL_this(V0,__VA_ARGS__))) ///< Aliased assignment.
#define XTAL_VAL_then()                                 XTAL_VAL_this
#define XTAL_VAL_this(V0,K1,...)   K1 = V0 __VA_OPT__(, XTAL_VAL_then XTAL_APP (K1,__VA_ARGS__))

#define XTAL_TXT_(...)                                  XTAL_TXT_make(__VA_ARGS__)      ///< Stringify.
#define XTAL_TXT_make(...)                                           #__VA_ARGS__

#define XTAL_NYM_(...)                                  XTAL_SYM_(XTAL,_,__VA_ARGS__)   ///< Name.

#define XTAL_SYM_(...) XTAL_SYM_make(__VA_ARGS__,,,,,,,,,,,,,,,,,,,,,,,,,,)             ///< Concatenate.
#define XTAL_SYM_make(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, ...)\
                      A##B##C##D##E##F##G##H##I##J##K##L##M##N##O##P##Q##R##S##T##U##V##W##X##Y##Z


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
#if     XTAL_VER_STD >= 2300// and XTAL_VER_GNUC >= 1400
//\
#define XTAL_VER_ranges            -1
#define XTAL_VER_ranges             3
#else
#define XTAL_VER_ranges             3
#endif

#define XTAL_VER_(...) (false XTAL_MAP_(XTAL_VER,  __VA_ARGS__))///< Version checking.
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
template <class X, class Y> concept XTAL_NYM_(generalized) = ::std::derived_from<XTAL_NOM_(Y), XTAL_NOM_(X)> and not ::std::same_as<XTAL_NOM_(X), XTAL_NOM_(Y)>;
template <class X, class Y> concept XTAL_NYM_(specialized) = ::std::derived_from<XTAL_NOM_(X), XTAL_NOM_(Y)> and not ::std::same_as<XTAL_NOM_(Y), XTAL_NOM_(X)>;
template <class X, class Y> concept XTAL_NYM_(relativized) = XTAL_NYM_(generalized)<X, Y> or XTAL_NYM_(specialized)<X, Y>;
#endif


////////////////////////////////////////////////////////////////////////////////

#define XTAL_DEF_(...)           XTAL_MAP_(XTAL_DEF,__VA_ARGS__)///< Leading `[[attributes]]` and `keywords`.
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

#define XTAL_NEW_then(TYP,...)   template     <class ...XTAL_NYM_(As)>                          \
                                 constexpr explicit TYP(XTAL_NYM_(As) &&...XTAL_NYM_(as))       \
                               __VA_ARGS__ (static_cast<XTAL_NYM_(As) &&> (XTAL_NYM_(as))...) {};

#define XTAL_NEW_cast(TYP,...)   template <XTAL_NYM_(relativized)  <TYP>    XTAL_NYM_(That)>    \
                                 constexpr     TYP(XTAL_NYM_(That)      &&  XTAL_NYM_(this))    \
                               __VA_ARGS__     TYP(static_cast     <TYP &&>(XTAL_NYM_(this))) {};

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

#define XTAL_1FN_to(...)           <class ...XTAL_NYM_(As)>\
                                            (XTAL_NYM_(As) \
                                        &&...XTAL_NYM_(as))\
   XTAL_0FN_(to)                                           (__VA_ARGS__)                                 ///< Lambda ignoring arguments after `[captures]`.

#define XTAL_1FN_dot(...)          <class    XTAL_NYM_(T )>\
                                            (XTAL_NYM_(T ) \
                                           &&XTAL_NYM_(t ))\
   XTAL_0FN_(to)                  (XTAL_REF_(XTAL_NYM_(t )).__VA_ARGS__)                                 ///< Lambda forwarding to `.`member after `[captures]`.

#define XTAL_1FN_call(...)         <class ...XTAL_NYM_(As)>\
                                            (XTAL_NYM_(As) \
                                        &&...XTAL_NYM_(as))\
   XTAL_0FN_(to)      (__VA_ARGS__(XTAL_REF_(XTAL_NYM_(as))...))                                         ///< Lambda forwarding to call`(...)` after `[captures]`.

#define XTAL_1FN_make(...)         <class ...XTAL_NYM_(As)>\
                                            (XTAL_NYM_(As) \
                                        &&...XTAL_NYM_(as))\
   XTAL_0FN_(to)      (__VA_ARGS__{XTAL_REF_(XTAL_NYM_(as))...})                                         ///< Lambda forwarding to make`{...}` after `[captures]`.

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
///////////////////////////////////////////////////////////////////////////////

#define XTAL_OCT_(ARG,...)       XTAL_OCT_##ARG __VA_OPT__((__VA_ARGS__))

#define XTAL_OCT_prime(OCT)    ((XTAL_OCT_primer_##OCT + OCT << 1)|!!OCT)///< Prime numbers indexed by `0000...0177`.
#define XTAL_OCT_primer(OCT)     XTAL_OCT_primer_##OCT
#define XTAL_OCT_primer_0000 0001U//   2
#define XTAL_OCT_primer_0001 0000U//   3 = 2^2 - 1
#define XTAL_OCT_primer_0002 0000U//   5 = 2^2 + 1
#define XTAL_OCT_primer_0003 0000U//   7 = 2^3 - 1
#define XTAL_OCT_primer_0004 0001U//  11
#define XTAL_OCT_primer_0005 0001U//  13
#define XTAL_OCT_primer_0006 0002U//  17 = 2^4 + 1
#define XTAL_OCT_primer_0007 0002U//  19
#define XTAL_OCT_primer_0010 0003U//  23
#define XTAL_OCT_primer_0011 0005U//  29
#define XTAL_OCT_primer_0012 0005U//  31 = 2^5 - 1
#define XTAL_OCT_primer_0013 0007U//  37
#define XTAL_OCT_primer_0014 0010U//  41
#define XTAL_OCT_primer_0015 0010U//  43
#define XTAL_OCT_primer_0016 0011U//  47
#define XTAL_OCT_primer_0017 0013U//  53
#define XTAL_OCT_primer_0020 0015U//  59
#define XTAL_OCT_primer_0021 0015U//  61
#define XTAL_OCT_primer_0022 0017U//  67
#define XTAL_OCT_primer_0023 0020U//  71
#define XTAL_OCT_primer_0024 0020U//  73
#define XTAL_OCT_primer_0025 0022U//  79
#define XTAL_OCT_primer_0026 0023U//  83
#define XTAL_OCT_primer_0027 0025U//  89
#define XTAL_OCT_primer_0030 0030U//  97
#define XTAL_OCT_primer_0031 0031U// 101
#define XTAL_OCT_primer_0032 0031U// 103
#define XTAL_OCT_primer_0033 0032U// 107
#define XTAL_OCT_primer_0034 0032U// 109
#define XTAL_OCT_primer_0035 0033U// 113
#define XTAL_OCT_primer_0036 0041U// 127 = 2^7 - 1
#define XTAL_OCT_primer_0037 0042U// 131
#define XTAL_OCT_primer_0040 0044U// 137
#define XTAL_OCT_primer_0041 0044U// 139
#define XTAL_OCT_primer_0042 0050U// 149
#define XTAL_OCT_primer_0043 0050U// 151
#define XTAL_OCT_primer_0044 0052U// 157
#define XTAL_OCT_primer_0045 0054U// 163
#define XTAL_OCT_primer_0046 0055U// 167
#define XTAL_OCT_primer_0047 0057U// 173
#define XTAL_OCT_primer_0050 0061U// 179
#define XTAL_OCT_primer_0051 0061U// 181
#define XTAL_OCT_primer_0052 0065U// 191
#define XTAL_OCT_primer_0053 0065U// 193
#define XTAL_OCT_primer_0054 0066U// 197
#define XTAL_OCT_primer_0055 0066U// 199
#define XTAL_OCT_primer_0056 0073U// 211
#define XTAL_OCT_primer_0057 0100U// 223
#define XTAL_OCT_primer_0060 0101U// 227
#define XTAL_OCT_primer_0061 0101U// 229
#define XTAL_OCT_primer_0062 0102U// 233
#define XTAL_OCT_primer_0063 0104U// 239
#define XTAL_OCT_primer_0064 0104U// 241
#define XTAL_OCT_primer_0065 0110U// 251
#define XTAL_OCT_primer_0066 0112U// 257 = 2^8 + 1
#define XTAL_OCT_primer_0067 0114U// 263
#define XTAL_OCT_primer_0070 0116U// 269
#define XTAL_OCT_primer_0071 0116U// 271
#define XTAL_OCT_primer_0072 0120U// 277
#define XTAL_OCT_primer_0073 0121U// 281
#define XTAL_OCT_primer_0074 0121U// 283
#define XTAL_OCT_primer_0075 0125U// 293
#define XTAL_OCT_primer_0076 0133U// 307
#define XTAL_OCT_primer_0077 0134U// 311
#define XTAL_OCT_primer_0100 0134U// 313
#define XTAL_OCT_primer_0101 0135U// 317
#define XTAL_OCT_primer_0102 0143U// 331
#define XTAL_OCT_primer_0103 0145U// 337
#define XTAL_OCT_primer_0104 0151U// 347
#define XTAL_OCT_primer_0105 0151U// 349
#define XTAL_OCT_primer_0106 0152U// 353
#define XTAL_OCT_primer_0107 0154U// 359
#define XTAL_OCT_primer_0110 0157U// 367
#define XTAL_OCT_primer_0111 0161U// 373
#define XTAL_OCT_primer_0112 0163U// 379
#define XTAL_OCT_primer_0113 0164U// 383
#define XTAL_OCT_primer_0114 0166U// 389
#define XTAL_OCT_primer_0115 0171U// 397
#define XTAL_OCT_primer_0116 0172U// 401
#define XTAL_OCT_primer_0117 0175U// 409
#define XTAL_OCT_primer_0120 0201U// 419
#define XTAL_OCT_primer_0121 0201U// 421
#define XTAL_OCT_primer_0122 0205U// 431
#define XTAL_OCT_primer_0123 0205U// 433
#define XTAL_OCT_primer_0124 0207U// 439
#define XTAL_OCT_primer_0125 0210U// 443
#define XTAL_OCT_primer_0126 0212U// 449
#define XTAL_OCT_primer_0127 0215U// 457
#define XTAL_OCT_primer_0130 0216U// 461
#define XTAL_OCT_primer_0131 0216U// 463
#define XTAL_OCT_primer_0132 0217U// 467
#define XTAL_OCT_primer_0133 0224U// 479
#define XTAL_OCT_primer_0134 0227U// 487
#define XTAL_OCT_primer_0135 0230U// 491
#define XTAL_OCT_primer_0136 0233U// 499
#define XTAL_OCT_primer_0137 0234U// 503
#define XTAL_OCT_primer_0140 0236U// 509
#define XTAL_OCT_primer_0141 0243U// 521
#define XTAL_OCT_primer_0142 0243U// 523
#define XTAL_OCT_primer_0143 0253U// 541
#define XTAL_OCT_primer_0144 0255U// 547
#define XTAL_OCT_primer_0145 0261U// 557
#define XTAL_OCT_primer_0146 0263U// 563
#define XTAL_OCT_primer_0147 0265U// 569
#define XTAL_OCT_primer_0150 0265U// 571
#define XTAL_OCT_primer_0151 0267U// 577
#define XTAL_OCT_primer_0152 0273U// 587
#define XTAL_OCT_primer_0153 0275U// 593
#define XTAL_OCT_primer_0154 0277U// 599
#define XTAL_OCT_primer_0155 0277U// 601
#define XTAL_OCT_primer_0156 0301U// 607
#define XTAL_OCT_primer_0157 0303U// 613
#define XTAL_OCT_primer_0160 0304U// 617
#define XTAL_OCT_primer_0161 0304U// 619
#define XTAL_OCT_primer_0162 0311U// 631
#define XTAL_OCT_primer_0163 0315U// 641
#define XTAL_OCT_primer_0164 0315U// 643
#define XTAL_OCT_primer_0165 0316U// 647
#define XTAL_OCT_primer_0166 0320U// 653
#define XTAL_OCT_primer_0167 0322U// 659
#define XTAL_OCT_primer_0170 0322U// 661
#define XTAL_OCT_primer_0171 0327U// 673
#define XTAL_OCT_primer_0172 0330U// 677
#define XTAL_OCT_primer_0173 0332U// 683
#define XTAL_OCT_primer_0174 0335U// 691
#define XTAL_OCT_primer_0175 0341U// 701
#define XTAL_OCT_primer_0176 0344U// 709
#define XTAL_OCT_primer_0177 0350U// 719


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)


#ifndef XTAL_DOC
////////////////////////////////////////////////////////////////////////////////

//nclude <range/v3/all.hpp>
#include <range/v3/range/traits.hpp>
#include <range/v3/range/concepts.hpp>

#include <range/v3/iterator/concepts.hpp>
#include <range/v3/iterator/operations.hpp>
#include <range/v3/iterator/move_iterators.hpp>

#include <range/v3/view/iota.hpp>
#include <range/v3/view/interface.hpp>
#include <range/v3/view/drop_exactly.hpp> // C++20: `std::ranges::drop_view`
#include <range/v3/view/take_exactly.hpp> // C++20: `std::ranges::take_view`
#include <range/v3/view/subrange.hpp>
#include <range/v3/view/any_view.hpp>     // C++29: ?
#include <range/v3/view/filter.hpp>
#include <range/v3/view/repeat.hpp>       // C++23: `std::ranges::repeat_view`
#include <range/v3/view/generate.hpp>     // C++23: `std::generator`
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip_with.hpp>     // C++23: `std::ranges::zip_transform_view`
#include <range/v3/view/zip.hpp>          // C++23: `std::ranges::zip_view`

#include <range/v3/algorithm/copy_n.hpp>
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/algorithm/move.hpp>
#include <range/v3/algorithm/equal.hpp>
#include <range/v3/algorithm/rotate.hpp>
#include <range/v3/algorithm/max_element.hpp>
#include <range/v3/algorithm/min_element.hpp>
#include <range/v3/algorithm/minmax_element.hpp>
#include <range/v3/algorithm/transform.hpp>

#include <range/v3/numeric/accumulate.hpp>// C++23: `std::ranges::fold_left`

#if     XTAL_VER_(ranges != 3)
#include <ranges>
#if __has_include(<generator>)
#include <generator>
#endif
#endif

#if     XTAL_LOG
#define  _LIBCPP_DEBUG XTAL_LOG
#define _GLIBCXX_DEBUG XTAL_LOG
#include <iostream>
#endif


////////////////////////////////////////////////////////////////////////////////
#endif

