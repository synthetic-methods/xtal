#pragma once

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
//                     _Pragma("GCC diagnostic ignored \"-Winterference-size\"")\

#else
#endif//XTAL_ENV
#define XTAL_ENV_GCC XTAL_ENV_GNUC
#define XTAL_ENV (XTAL_ENV_(MSVC) or XTAL_ENV_(LLVM) or XTAL_ENV_(GNUC))



XTAL_ENV_(push)
///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#define XTAL_STD_(ARG,...)                XTAL_STD_##ARG __VA_OPT__((__VA_ARGS__)) ///< C++ standard version (YYMM) and reference types.
#define XTAL_STD (__cplusplus%10000)                                               ///< C++ standard version (YYMM).

#define XTAL_STD_null_type         ::std::nullptr_t
#define XTAL_STD_unit_type         ::std::monostate
#define XTAL_STD_size_type         ::std::size_t
#define XTAL_STD_integer_type      ::std::ptrdiff_t

#define XTAL_STD_int(...)                 XTAL_STD_int_##__VA_ARGS__
#define XTAL_STD_int_0                    char
#define XTAL_STD_int_1              short int
#define XTAL_STD_int_2                    int
#define XTAL_STD_int_3               long int
#define XTAL_STD_int_4          long long int

#define XTAL_STD_float(...)               XTAL_STD_float_##__VA_ARGS__
#define XTAL_STD_float_0                  void
#define XTAL_STD_float_1                  void
#define XTAL_STD_float_2                  float
#define XTAL_STD_float_3                  double
#define XTAL_STD_float_4             long double


#define XTAL_SYS_(...)                    XTAL_SYS_##__VA_ARGS__                      ///< System reference values.

#ifdef  XTAL_SYS_IEC
#else
//\
#define XTAL_SYS_IEC                      0
#define XTAL_SYS_IEC                      60559
#endif

#ifdef  XTAL_SYS_L1
#elif   defined(__cacheline_aligned)
#define XTAL_SYS_L1 __cacheline_aligned
#elif   defined(L1_CACHE_BYTES)
#define XTAL_SYS_L1 L1_CACHE_BYTES
#elif   defined(L1_CACHE_SHIFT)
#define XTAL_SYS_L1 L1_CACHE_SHIFT
#else
#define XTAL_SYS_L1                       0x40
#endif//XTAL_STD_L1


#define XTAL_VER_MSVC               XTAL_ENV_MSVC and XTAL_ENV_MSVC
#define XTAL_VER_LLVM               XTAL_ENV_LLVM and XTAL_ENV_LLVM
#define XTAL_VER_GNUC               XTAL_ENV_GNUC and XTAL_ENV_GNUC
#define XTAL_VER_GCC                XTAL_VER_GNUC
#define XTAL_VER_STD                XTAL_STD
#define XTAL_VER_ranges             3

#define XTAL_VER_(...) (false XTAL_N_(XTAL_ver_,__VA_ARGS__))///< Version checking.
#define XTAL_ver_(...)     or XTAL_VER_##__VA_ARGS__


////////////////////////////////////////////////////////////////////////////////

#define XTAL_RAW_(...)           ::std::remove_cvref_t<__VA_ARGS__>   ///< Reveals the underlying-type.
#define XTAL_ALL_(...)              XTAL_RAW_(decltype(__VA_ARGS__))  ///< Reveals the underlying-type of a value.
#define XTAL_SYN_(...)              XTAL_SYN <         __VA_ARGS__ >  ///< Matches the underlying-type.
#define XTAL_SYM_(...)              XTAL_SYN <decltype(__VA_ARGS__)>  ///< Matches the underlying-type of a value.
template <class X, class Y> concept XTAL_SYN = ::std::same_as<XTAL_RAW_(X), XTAL_RAW_(Y)>;///< Matches underlying-types.

#define XTAL_REF_(...)  static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)   ///< Forwards a value.
#define XTAL_MOV_(...)                         ::std::   move(__VA_ARGS__)   ///< Moves    a value.
#define XTAL_ANY_(...)                         ::std::declval<__VA_ARGS__>() ///< Yields the existential value for a type.
#define XTAL_VAL_(...)                        [] () XTAL_0FN_(__VA_ARGS__)   ///< Yields a thunk returning a value.
#define XTAL_FUN_(...)                  decltype([] XTAL_1FN_(__VA_ARGS__))  ///< Yields a type-level alias of a function.


////////////////////////////////////////////////////////////////////////////////

#define XTAL_DEF_(...)              XTAL_N_(XTAL_KEY_,__VA_ARGS__)///< Leading `[[attributes]]` and `keywords`.
#define XTAL_KEY_(...)              XTAL_KEY_##__VA_ARGS__

#define XTAL_KEY_return             [[nodiscard]]
#define XTAL_KEY_static             static
#define XTAL_KEY_friend             friend

#if     XTAL_ENV_(MSVC)
#define XTAL_KEY_inline           __forceinline
#else
#define XTAL_KEY_inline             inline __attribute__((always_inline))
#endif//XTAL_KEY_inline

#if     XTAL_ENV_(MSVC)
#define XTAL_KEY_verbatim           /*FIXME*/
#elif   XTAL_ENV_(LLVM)
#define XTAL_KEY_verbatim           [[clang::optnone]]    __attribute__((optnone))
#elif   XTAL_ENV_(GNUC)
#define XTAL_KEY_verbatim           [[gnu::optimize(0)]]  __attribute__((optimize(0)))
#endif//XTAL_KEY_verbatim

#define XTAL_KEY_long               XTAL_KEY_return                         ///< Start abridged long  function (not inlined).
#define XTAL_KEY_short              XTAL_KEY_return XTAL_KEY_inline         ///< Start abridged short function     (inlined).

#define XTAL_KEY_explicit           XTAL_KEY_short constexpr explicit       ///< Start abridged short `explicit` function.
#define XTAL_KEY_implicit           XTAL_KEY_short constexpr                ///< Start abridged short `implicit` function.
#define XTAL_KEY_alias              XTAL_KEY_short constexpr decltype(auto) ///< Start abridged short `decltype(auto)` function.


#define XTAL_NEW_(ARG,...)          XTAL_NEW_##ARG __VA_OPT__((__VA_ARGS__)) ///< Start `(?:ex|im)plicit` constructor.
#define XTAL_NEW_explicit           constexpr explicit                       ///< Start        `explicit` constructor.
#define XTAL_NEW_implicit           constexpr                                ///< Start        `implicit` constructor.
#define XTAL_NEW_copy(TYP,...)      constexpr TYP              (TYP const &) __VA_ARGS__;\
                                    constexpr TYP & operator = (TYP const &) __VA_ARGS__;;///< Declare copy constructor/assignment for `TYP`, with suffix `...`.
#define XTAL_NEW_move(TYP,...)      constexpr TYP              (TYP      &&) __VA_ARGS__;\
                                    constexpr TYP & operator = (TYP      &&) __VA_ARGS__;;///< Declare move constructor/assignment for `TYP`, with suffix `...`.


#define XTAL_LET_(...)              constexpr __VA_ARGS__ ///< Start  member  definition with type `...`.
#define XTAL_LET                    constexpr      auto   ///< Start  member  definition with type `auto`.

#define XTAL_SET_(...)       static constexpr __VA_ARGS__ ///< Start `static` definition with type `...`.
#define XTAL_SET             static constexpr      auto   ///< Start `static` definition with type `auto`.


#if not XTAL_ENV
#define XTAL_0FN                                            constexpr noexcept///< Lambda declaration (after `[captures]`).
#elif   XTAL_VER_(GNUC)
#define XTAL_0FN                                            constexpr noexcept\
                             __attribute__((always_inline))
#elif   XTAL_VER_(LLVM)
#define XTAL_0FN             __attribute__((always_inline)) constexpr noexcept
#elif   XTAL_VER_(MSVC)
#define XTAL_0FN                      [[msvc::forceinline]] constexpr noexcept
#endif//XTAL_0FN

#define XTAL_0FN_(...)                 XTAL_0FN {return (__VA_ARGS__);}                   ///< Lambda expression (after `[captures]`).
#define XTAL_1FN_(...)  (auto &&...oo) XTAL_0FN {return (__VA_ARGS__(XTAL_REF_(oo)...));} ///< Lambda forwarding (after `[captures]`).
#define XTAL_XFN_(...)        (auto o) XTAL_0FN_(decltype(o){1} == o? o: o&(__VA_ARGS__)) ///< Lambda `signed` short-circuiting reducer (after `[captures]`).

#define XTAL_IMP_(ARG,...)                XTAL_IMP_##ARG __VA_OPT__((__VA_ARGS__)) ///< C++ standard version (YYMM) and reference types.

#if     XTAL_ENV_(MSVC == 0000)
#define XTAL_IMP_fma(Y, X, W)        __builtin_fma(Y, X, W)
#define XTAL_IMP_fam(W, X, Y)        __builtin_fma(Y, X, W)
#elif   XTAL_ENV_(MSVC >= 1700)
#define XTAL_IMP_fma(Y, X, W)           ::std::fma(Y, X, W)
#define XTAL_IMP_fam(W, X, Y)           ::std::fma(Y, X, W)
#elif   XTAL_ENV_(MSVC <  1700)
#define XTAL_IMP_fma(Y, X, W)                ((Y)*(X) + (W))
#define XTAL_IMP_fam(W, X, Y)                ((Y)*(X) + (W))
#endif


////////////////////////////////////////////////////////////////////////////////

#define XTAL_DO0_(SIG, ...)         SIG                           __VA_ARGS__   ;///< Define member function.
#define XTAL_DO1_(SIG, ...)         SIG const                     __VA_ARGS__   ;///< Define `const` member function.
#define XTAL_DO2_(SIG, ...)         SIG const                     __VA_ARGS__   \
                                    SIG                           __VA_ARGS__   ;///< Define `const?` member functions.
#define XTAL_DO4_(SIG, ...)         SIG const&                    __VA_ARGS__   \
                                    SIG      &                    __VA_ARGS__   \
                                    SIG const&&                   __VA_ARGS__   \
                                    SIG      &&                   __VA_ARGS__   ;///< Define `(const)? &&?` member functions.

#define XTAL_TO0_(SIG, ...)         SIG         noexcept {return (__VA_ARGS__);};///< Define `noexcept` member expression returning `...`.
#define XTAL_TO1_(SIG, ...)         SIG const   noexcept {return (__VA_ARGS__);};///< Define `noexcept` `const` member expression returning `...`.
#define XTAL_TO2_(SIG, ...)         SIG const   noexcept {return (__VA_ARGS__);}\
                                    SIG         noexcept {return (__VA_ARGS__);};///< Define `noexcept` `(const)?    ` member expressions returning `...`.
#define XTAL_TO4_(SIG, ...)         SIG const&  noexcept {return (__VA_ARGS__);}\
                                    SIG      &  noexcept {return (__VA_ARGS__);}\
                                    SIG const&& noexcept {return (__VA_ARGS__);}\
                                    SIG      && noexcept {return (__VA_ARGS__);};///< Define `noexcept` `(const)? &&?` member expressions returning `...`.


#define XTAL_TRY_(...)         (requires{ __VA_ARGS__ ;})                        ///< Check requirements.
#define XTAL_TRY_DO_(...)      (requires{ __VA_ARGS__ ;}) {       __VA_ARGS__ ;} ///< Check requirements, then invoke as block.
#define XTAL_TRY_TO_(...)      (requires{(__VA_ARGS__);}) {return(__VA_ARGS__);} ///< Check requirements, then return as expression.
#define XTAL_RET_TO_(...)                                 {return(__VA_ARGS__);} ///< Return as expression.


#define XTAL_IF0                    if constexpr (false);                        ///< Begin `else if constexpr` tree.
#define XTAL_0IF_(...)         XTAL_0IF_##__VA_ARGS__                            ///< Begin `else if constexpr` branch.
#define XTAL_0IF               else if constexpr
#define XTAL_0IF_else          else

#if     XTAL_VER_(MSVC)
#define XTAL_0IF_void          else {__assume(false);}                           ///< Begin forbidden branch.
#else
#define XTAL_0IF_void          else {__builtin_unreachable();}                   ///< Begin forbidden branch.
#endif//XTAL_0IF_void

#if     XTAL_VER_(STD >= 2600)
#define XTAL_0IF_consteval     else if consteval                                 ///< Begin constant-evaluated branch.
#else
#define XTAL_0IF_consteval     else if (::std::is_constant_evaluated())          ///< Begin constant-evaluated branch.
#endif//XTAL_0IF_consteval


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)



#if      XTAL_VER_(ranges == -1)
#include <ranges>
#endif
#if      XTAL_VER_(ranges ==  3)
#include <range/v3/all.hpp>
#endif
#include <variant>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <concepts>

////////////////////////////////////////////////////////////////////////////////

#define XTAL_LOG 1//NDEBUG
#if     XTAL_LOG
#define  _LIBCPP_DEBUG XTAL_LOG
#define _GLIBCXX_DEBUG XTAL_LOG
#include <iostream>
#endif
