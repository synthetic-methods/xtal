#pragma once


#ifndef XTAL_DOC
////////////////////////////////////////////////////////////////////////////////

#if __has_include(<execution>)
#include <execution>
#endif
#include <concepts>
#include <variant>
#include <cassert>
#include <cstring>
#include  <string>
#include <cstdint>
#include <complex>
#include <numbers>
#include <limits>
#include <random>
#include <cmath>
#include <array>
#include <tuple>
#include <queue>
#include <bit>
#include <new>


////////////////////////////////////////////////////////////////////////////////
#endif

#define XTAL_APP ()
#define XTAL_APP_(ARG,...) XTAL_APP_##ARG __VA_OPT__((__VA_ARGS__))

/// Recursion.
#define XTAL_APP_N(...)                                     XTAL_APP_4(__VA_ARGS__)
#define XTAL_APP_4(...)    XTAL_APP_3(XTAL_APP_3(XTAL_APP_3(XTAL_APP_3(__VA_ARGS__))))
#define XTAL_APP_3(...)    XTAL_APP_2(XTAL_APP_2(XTAL_APP_2(XTAL_APP_2(__VA_ARGS__))))
#define XTAL_APP_2(...)    XTAL_APP_1(XTAL_APP_1(XTAL_APP_1(XTAL_APP_1(__VA_ARGS__))))
#define XTAL_APP_1(...)    XTAL_APP_0(XTAL_APP_0(XTAL_APP_0(XTAL_APP_0(__VA_ARGS__))))
#define XTAL_APP_0(...)                                                __VA_ARGS__

/// Recursive map.
#define XTAL_APP_map(F0,...)                     __VA_OPT__(XTAL_APP_N(XTAL_APP_map_then_(F0,__VA_ARGS__)))
#define XTAL_APP_map_then()                                            XTAL_APP_map_then_
#define XTAL_APP_map_then_(F0,A1,...)   F0(A1)   __VA_OPT__(           XTAL_APP_map_then XTAL_APP (F0,__VA_ARGS__))

///< Recursive assignment.
#define XTAL_APP_let(V0,...)                     __VA_OPT__(XTAL_APP_N(XTAL_APP_let_then_(V0,__VA_ARGS__)))
#define XTAL_APP_let_then()                                            XTAL_APP_let_then_
#define XTAL_APP_let_then_(V0,K1,...)   K1 = V0  __VA_OPT__(         , XTAL_APP_let_then XTAL_APP (K1,__VA_ARGS__))

/// Token concatenation.
#define XTAL_APP_cat(...)  XTAL_APP_cat_then_(__VA_ARGS__,,,,,,,,,,,,,,,,,,,,,,,,,,)
#define XTAL_APP_cat_then_(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, ...)\
                           A##B##C##D##E##F##G##H##I##J##K##L##M##N##O##P##Q##R##S##T##U##V##W##X##Y##Z

/// String generation.
#define XTAL_TXT_(...)     XTAL_TXT_then_(__VA_ARGS__)
#define XTAL_TXT_then_(...)              #__VA_ARGS__

/// Symbol generation.
#define XTAL_NYM_(...)     XTAL_APP_(cat) (XTAL,_,__VA_ARGS__)



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
                       _Pragma("STDC FP_CONTRACT ON")\

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

#define XTAL_VER_(...)    (false XTAL_APP_(map) (XTAL_VER_then_,__VA_ARGS__))      ///< Version checking.
#define XTAL_VER_then_(...)                       or XTAL_VER_##__VA_ARGS__


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define XTAL_NOM_(...)                    ::std::remove_cvref_t<__VA_ARGS__>       ///< Reveals the nominal type.
#define XTAL_ALL_(...)                       XTAL_NOM_(decltype(__VA_ARGS__))      ///< Reveals the nominal type of a value.
#define XTAL_ANY_(...)                           ::std::declval<__VA_ARGS__>()     ///< Yields the existential value for a type.
#define XTAL_MOV_(...)                           ::std::   move(__VA_ARGS__)       ///< Moves    a value.
#define XTAL_REF_(...)    static_cast<decltype (__VA_ARGS__)&&>(__VA_ARGS__)       ///< Forwards a value.
#define XTAL_VAL_(...)    static_cast<XTAL_ALL_(__VA_ARGS__)  >(__VA_ARGS__)       ///< Forwards a value.
#ifndef XTAL_DOC
template <class X, class Y> concept XTAL_NYM_(generalized) = ::std::derived_from<XTAL_NOM_(Y), XTAL_NOM_(X)> and not ::std::same_as<XTAL_NOM_(X), XTAL_NOM_(Y)>;
template <class X, class Y> concept XTAL_NYM_(specialized) = ::std::derived_from<XTAL_NOM_(X), XTAL_NOM_(Y)> and not ::std::same_as<XTAL_NOM_(Y), XTAL_NOM_(X)>;
template <class X, class Y> concept XTAL_NYM_(relativized) = XTAL_NYM_(generalized)<X, Y> or XTAL_NYM_(specialized)<X, Y>;
template <class X         > concept XTAL_NYM_(synthesized) = not ::std::same_as<void, X>;
#endif


////////////////////////////////////////////////////////////////////////////////

#define XTAL_DEF_(...)           XTAL_APP_(map) (XTAL_DEF_then_,__VA_ARGS__)       ///< Leading `[[attributes]]` and `keywords`.
#define XTAL_DEF_then_(...)                          XTAL_DEF_##__VA_ARGS__

#if     XTAL_VER_(STD < 23)
#define XTAL_DEF_export
#define XTAL_DEF_import// TODO?
#else
#define XTAL_DEF_export          export
#define XTAL_DEF_import          import
#endif
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

#define XTAL_NEW_else(TYP,...)   template     <class ...XTAL_NYM_(As)>                          \
                                 constexpr explicit TYP(XTAL_NYM_(As) &&...XTAL_NYM_(as))       \
                               __VA_ARGS__ {static_cast<XTAL_NYM_(As) &&> (XTAL_NYM_(as))...} {};

#define XTAL_NEW_then(TYP,...)   template <XTAL_NYM_(relativized)  <TYP>    XTAL_NYM_(That)>    \
                                 constexpr     TYP(XTAL_NYM_(That)      &&  XTAL_NYM_(this))    \
                               __VA_ARGS__        (static_cast     <TYP &&>(XTAL_NYM_(this))) {};

#define XTAL_NEW_copy(TYP,...)   constexpr     TYP             (TYP const &) __VA_ARGS__;\
                                 constexpr     TYP & operator= (TYP const &) __VA_ARGS__;;///< Declare copy constructor/assignment for `TYP`, with suffix `...`.
#define XTAL_NEW_move(TYP,...)   constexpr     TYP             (TYP      &&) __VA_ARGS__;\
                                 constexpr     TYP & operator= (TYP      &&) __VA_ARGS__;;///< Declare move constructor/assignment for `TYP`, with suffix `...`.

#define XTAL_NEW_create(TYP,...) constexpr     TYP()                         __VA_ARGS__;
#define XTAL_NEW_delete(TYP,...) constexpr    ~TYP()                         __VA_ARGS__;


#define XTAL_TYP_(ARG,...)       XTAL_TYP_##ARG __VA_OPT__((__VA_ARGS__))                ///< Type definition.

#define XTAL_TYP_ask             concept
#define XTAL_TYP_new             struct
#define XTAL_TYP_let             using
#define XTAL_TYP_set             using


////////////////////////////////////////////////////////////////////////////////

#define XTAL_FN0_(ARG,...)    XTAL_FN0_##ARG __VA_OPT__((__VA_ARGS__))
#define XTAL_FN1_(ARG,...)    XTAL_FN1_##ARG __VA_OPT__((__VA_ARGS__))
#define XTAL_FN2_(ARG,...)    XTAL_FN2_##ARG __VA_OPT__((__VA_ARGS__))

#define XTAL_FN0_go(SIG,...)\
   SIG()              const  & noexcept {return __VA_ARGS__(           (*this)                   );}\
   SIG()                     & noexcept {return __VA_ARGS__(           (*this)                   );}\
   SIG()              const && noexcept {return __VA_ARGS__(::std::move(*this)                   );}\
   SIG()                    && noexcept {return __VA_ARGS__(::std::move(*this)                   );}\
///< Define `(const)? &&?` member accessor aliases.

#define XTAL_FN1_go(SIG,...)\
   SIG(auto &&...etc) const  & noexcept {return __VA_ARGS__(           (*this), XTAL_REF_(etc)...);}\
   SIG(auto &&...etc)        & noexcept {return __VA_ARGS__(           (*this), XTAL_REF_(etc)...);}\
   SIG(auto &&...etc) const && noexcept {return __VA_ARGS__(::std::move(*this), XTAL_REF_(etc)...);}\
   SIG(auto &&...etc)       && noexcept {return __VA_ARGS__(::std::move(*this), XTAL_REF_(etc)...);}\
///< Define `(const)? &&?` member function aliases.


#define XTAL_FN2_do(SIG,...)  SIG const                   __VA_ARGS__   \
                              SIG                         __VA_ARGS__   ;///< Define `(const)?`     member functions.

#define XTAL_FN2_to(SIG,...)  SIG const    noexcept __VA_OPT__({return (__VA_ARGS__);});\
                              SIG          noexcept __VA_OPT__({return (__VA_ARGS__);});;///< Define returning `noexcept` `(const)?    ` member expressions.


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

#define XTAL_0FN_if(...)                     XTAL_0FN -> decltype(auto) requires requires {         (__VA_ARGS__);} {}     ///< Lambda perform statement after `[captures]` and `(arguments)`.
#define XTAL_0FN_to(...)                     XTAL_0FN -> decltype(auto)                   {return   (__VA_ARGS__);}        ///< Lambda return expression after `[captures]` and `(arguments)`.
#define XTAL_0FN_do(...)                     XTAL_0FN -> decltype(auto)                   {         (__VA_ARGS__);}        ///< Lambda perform statement after `[captures]` and `(arguments)`.

#define XTAL_1FN_do(...)           <class ...XTAL_NYM_(As)>\
                                            (XTAL_NYM_(As) \
                                        &&...XTAL_NYM_(as))\
   XTAL_0FN_(do)                                           (__VA_ARGS__)                                 ///< Lambda ignoring arguments after `[captures]`.

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

#define XTAL_TRY_do_unless(...)      (not XTAL_TRY_do_if(__VA_ARGS__))                               ///< Check requirements failure.
#define XTAL_TRY_to_unless(...)      (not XTAL_TRY_to_if(__VA_ARGS__))                               ///< Check requirements failure.
#define XTAL_TRY_do_if(...)                 (requires {{(__VA_ARGS__)}                          ;})  ///< Check requirements success.
#define XTAL_TRY_to_if(...)                 (requires {{(__VA_ARGS__)} -> XTAL_NYM_(synthesized);})  ///< Check requirements success.
#define XTAL_TRY_do(...)                  XTAL_TRY_do_if(__VA_ARGS__) {       (__VA_ARGS__);}        ///< Check requirements, then invoke as block.
#define XTAL_TRY_to(...)                  XTAL_TRY_to_if(__VA_ARGS__) {return (__VA_ARGS__);}        ///< Check requirements, then return as expression.


////////////////////////////////////////////////////////////////////////////////

#define XTAL_IF1_(ARG,...)             XTAL_IF1_##ARG __VA_OPT__((__VA_ARGS__))          ///< Begin `else if constexpr` branch.
#define XTAL_0IF_(ARG,...)             XTAL_0IF_##ARG __VA_OPT__((__VA_ARGS__))          ///< Begin `else if constexpr` branch.

#define XTAL_IF1_switch(...)           switch(__VA_ARGS__)                          ///< Switch longhand.

#if     XTAL_VER_(MSVC)
#define XTAL_IF1_assume(...)         __assume(__VA_ARGS__)                          ///< Assumption of   truth.
#elif   XTAL_VER_(LLVM)
#define XTAL_IF1_assume(...) __builtin_assume(__VA_ARGS__)                          ///< Assumption of   truth.
#else
#define XTAL_IF1_assume(...)         [[assume(__VA_ARGS__)]]                        ///< Assumption of   truth.
#endif//XTAL_IF1_assume(...)

#define XTAL_IF0_assume(...)  XTAL_IF1_assume(not (__VA_ARGS__))                    ///< Assumption of untruth.

#define XTAL_IF0                             if constexpr (false);                       ///< Begin `else if constexpr` tree.
#define XTAL_0IF                       else  if constexpr
#define XTAL_0IF_else                  else

#if     XTAL_VER_(MSVC)
#define XTAL_0IF_void             else {__assume(false);}                           ///< Begin forbidden branch.
#else
#define XTAL_0IF_void             else {__builtin_unreachable();}                   ///< Begin forbidden branch.
#endif//XTAL_0IF_void

#define XTAL_IF1_do(...)                     if constexpr XTAL_TRY_do(__VA_ARGS__)
#define XTAL_0IF_do(...)               else  if constexpr XTAL_TRY_do(__VA_ARGS__)
#define XTAL_IF1_to(...)                     if constexpr XTAL_TRY_to(__VA_ARGS__)
#define XTAL_0IF_to(...)               else  if constexpr XTAL_TRY_to(__VA_ARGS__)

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

