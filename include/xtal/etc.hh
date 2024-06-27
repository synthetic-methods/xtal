#pragma once

#include <variant>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <concepts>


///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#define XTAL_(...) XTAL_##__VA_ARGS__


////////////////////////////////////////////////////////////////////////////////

#ifdef  NDEBUG
#define XTAL_LOG 1//release
#else
#define XTAL_LOG 1//debug
#endif

#if     XTAL_LOG
#include <iostream>
#endif

#define  _LIBCPP_DEBUG XTAL_LOG
#define _GLIBCXX_DEBUG XTAL_LOG


////////////////////////////////////////////////////////////////////////////////

#define XTAL_INT_(...) XTAL_INT_##__VA_ARGS__
#define XTAL_INT_0          char
#define XTAL_INT_1     short int
#define XTAL_INT_2           int
#define XTAL_INT_3      long int
#define XTAL_INT_4 long long int

#define XTAL_FLT_(...) XTAL_FLT_##__VA_ARGS__
#define XTAL_FLT_0          void
#define XTAL_FLT_1          void
#define XTAL_FLT_2         float
#define XTAL_FLT_3        double
#define XTAL_FLT_4   long double


#define XTAL_STD_(...) XTAL_STD_##__VA_ARGS__
#define XTAL_STD ((__cplusplus/100)%100)
#define XTAL_STD_IEC 60559

#define XTAL_STD_null_type ::std::nullptr_t
#define XTAL_STD_unit_type ::std::monostate
#define XTAL_STD_sign_type int
#define XTAL_STD_real_type float
#define XTAL_STD_size_type ::std::size_t
#define XTAL_STD_integral_type ::std::ptrdiff_t


#if     defined(__cacheline_aligned)
#define XTAL_STD_L1 __cacheline_aligned

#elif   defined(L1_CACHE_BYTES)
#define XTAL_STD_L1 L1_CACHE_BYTES

#elif   defined(L1_CACHE_SHIFT)
#define XTAL_STD_L1 L1_CACHE_SHIFT

#else
#define XTAL_STD_L1 0x40

#endif


////////////////////////////////////////////////////////////////////////////////

#define XTAL_V00_(...) XTAL_V00_##__VA_ARGS__

#if     defined(_MSC_VER)
#define XTAL_V00_MSVC (_MSC_VER)
#define XTAL_V00_LLVM 0
#define XTAL_V00_GNUC 0
//static_assert(1933 <= XTAL_V00_(MSVC));

#elif   defined(__clang__)
#define XTAL_V00_LLVM (100*__clang_major__ + __clang_minor__)
#define XTAL_V00_GNUC 0
#define XTAL_V00_MSVC 0
//static_assert(1400 <= XTAL_V00_(LLVM));

#elif   defined(__GNUC__)
#define XTAL_V00_GNUC (100*__GNUC__ + __GNUC_MINOR__)
#define XTAL_V00_MSVC 0
#define XTAL_V00_LLVM 0
//static_assert(1200 <= XTAL_V00_(GNUC));  

#else
#define XTAL_V00_MSVC 0
#define XTAL_V00_LLVM 0
#define XTAL_V00_GNUC 0

#endif
#define XTAL_V00_GCC XTAL_V00_GNUC


////////////////////////////////////////////////////////////////////////////////

#define XTAL_ENV_(...)  XTAL_ENV_##__VA_ARGS__

#if     XTAL_V00_(MSVC)
#define XTAL_ENV_pop    _Pragma("warning(pop)")
#define XTAL_ENV_push   _Pragma("warning(push)")\
                        _Pragma("warning(disable:4010)")\

#elif   XTAL_V00_(LLVM)
#define XTAL_ENV_pop    _Pragma("clang diagnostic pop")
#define XTAL_ENV_push   _Pragma("clang diagnostic push")\
                        _Pragma("clang diagnostic ignored \"-Wcomment\"")\
                        _Pragma("clang diagnostic ignored \"-Wdocumentation\"")\
                        _Pragma("clang diagnostic ignored \"-Wconstant-conversion\"")\
                        _Pragma("clang diagnostic ignored \"-Wunused-local-typedef\"")\
                        _Pragma("clang diagnostic ignored \"-Wshift-op-parentheses\"")\
                        _Pragma("clang diagnostic ignored \"-Wlogical-op-parentheses\"")\

#elif   XTAL_V00_(GNUC)
#define XTAL_ENV_pop    _Pragma("GCC diagnostic pop")
#define XTAL_ENV_push   _Pragma("GCC diagnostic push")\
                        _Pragma("GCC diagnostic ignored \"-Wsubobject-linkage\"")\
//                      _Pragma("GCC diagnostic ignored \"-Winterference-size\"")\

#endif


////////////////////////////////////////////////////////////////////////////////

#define XTAL_USE                                   using
#define XTAL_TYP                                   struct
#define XTAL_REQ                                   concept

template <class T0, class T1>
concept XTAL_ARG = ::std::same_as<::std::remove_cvref_t<T0>, ::std::remove_cvref_t<T1>>;
#define XTAL_ARG_(...)                                              XTAL_ARG<__VA_ARGS__> auto
#define XTAL_TMP_(...)                                             template <__VA_ARGS__>
#define XTAL_ANY_(...)                                       ::std::declval <__VA_ARGS__>()
#define XTAL_ALL_(...)                        ::std::remove_cvref_t<decltype(__VA_ARGS__)>

#define XTAL_MOV_(...)                                           ::std::move(__VA_ARGS__)
#define XTAL_REF_(...)                static_cast< decltype(__VA_ARGS__) &&>(__VA_ARGS__)
#define XTAL_RET                         constexpr decltype(auto)
#define XTAL_LET                         constexpr          auto
#define XTAL_SET                  static constexpr          auto

#define XTAL_CON_(...)                   XTAL_CON_##__VA_ARGS__
#define XTAL_CON_explicit                constexpr explicit
#define XTAL_CON_implicit                constexpr

#define XTAL_CVN_(...)                   XTAL_CVN_##__VA_ARGS__
#define XTAL_CVN_explicit                constexpr explicit       operator
#define XTAL_CVN_implicit                constexpr                operator

#define XTAL_1FN_(...)     (auto &&..._) constexpr noexcept {return (__VA_ARGS__(static_cast<decltype(_) &&>(_)...));}
#define XTAL_0FN                         constexpr noexcept
#define XTAL_0FM                 mutable constexpr noexcept
#define XTAL_0FN_(...)                   constexpr noexcept {return (__VA_ARGS__);}
#define XTAL_0FM_(...)           mutable constexpr noexcept {return (__VA_ARGS__);}

#define XTAL_IF0              if         constexpr (0);
#define XTAL_0IF         else if         constexpr
#define XTAL_0IF_(...)                   XTAL_0IF_##__VA_ARGS__
#define XTAL_0IF_default else
#if     XTAL_STD < 26
#define XTAL_0IF_dynamic else if    (not _std::is_constant_evaluated())
#define XTAL_0IF_static  else if    (    _std::is_constant_evaluated())
#else
#define XTAL_0IF_dynamic else if     not consteval
#define XTAL_0IF_static  else if         consteval
#endif

#define XTAL_0FX                 const             noexcept
#define XTAL_0EX                                   noexcept
#define XTAL_0FX_(...)           const __VA_ARGS__ noexcept
#define XTAL_0EX_(...)                 __VA_ARGS__ noexcept
#define XTAL_0FX_DO_(...)        const             noexcept {        __VA_ARGS__ ;}
#define XTAL_0EX_DO_(...)                          noexcept {        __VA_ARGS__ ;}
#define XTAL_0FX_TO_(...)        const             noexcept {return (__VA_ARGS__);}
#define XTAL_0EX_TO_(...)                          noexcept {return (__VA_ARGS__);}

#define XTAL_TRY_(...)          (requires { __VA_ARGS__ ;})
#define XTAL_TRY_DO_(...)       (requires { __VA_ARGS__ ;}) {        __VA_ARGS__ ;}
#define XTAL_TRY_TO_(...)       (requires {(__VA_ARGS__);}) {return (__VA_ARGS__);}

#define XTAL_DO0_(SIG, ...)      SIG               noexcept          __VA_ARGS__   ;
#define XTAL_DO1_(SIG, ...)      SIG     const     noexcept          __VA_ARGS__   ;
#define XTAL_DO2_(SIG, ...)      SIG     const     noexcept          __VA_ARGS__   \
                                 SIG               noexcept          __VA_ARGS__   ;
#define XTAL_DO4_(SIG, ...)      SIG     const  &  noexcept          __VA_ARGS__   \
                                 SIG            &  noexcept          __VA_ARGS__   \
                                 SIG     const  && noexcept          __VA_ARGS__   \
                                 SIG            && noexcept          __VA_ARGS__   ;

#define XTAL_TO2_(SIG, ...)      SIG     const     noexcept {return (__VA_ARGS__);}\
                                 SIG               noexcept {return (__VA_ARGS__);};
#define XTAL_TO4_(SIG, ...)      SIG     const  &  noexcept {return (__VA_ARGS__);}\
                                 SIG            &  noexcept {return (__VA_ARGS__);}\
                                 SIG     const  && noexcept {return (__VA_ARGS__);}\
                                 SIG            && noexcept {return (__VA_ARGS__);};

#define XTAL_CO0_(TYP)          ~TYP()                          noexcept = default;;
#define XTAL_CO1_(TYP)           TYP()                          noexcept = default;;
#define XTAL_CO4_(TYP) constexpr TYP & operator = (TYP const &) noexcept = default;\
                       constexpr TYP              (TYP const &) noexcept = default;\
                       constexpr TYP & operator = (TYP      &&) noexcept = default;\
                       constexpr TYP              (TYP      &&) noexcept = default;;


////////////////////////////////////////////////////////////////////////////////

#define XTAL_DEF_(...)           XTAL_F1_(XTAL_ATT_,__VA_ARGS__)

#define XTAL_ATT_(...)           XTAL_ATT_##__VA_ARGS__

#if     0
#elif   XTAL_V00_(MSVC)
#define XTAL_ATT_verbatim        //FIXME
#elif   XTAL_V00_(LLVM)
#define XTAL_ATT_verbatim        [[clang::optnone]] __attribute__((optnone))
#elif   XTAL_V00_(GNUC)
#define XTAL_ATT_verbatim        [[gnu::optimize(0)]] __attribute__((optimize(0)))
#endif

#if     XTAL_V00_(MSVC)
#define XTAL_ATT_inline          __forceinline
#else
#define XTAL_ATT_inline          inline __attribute__((always_inline))
#endif

#define XTAL_ATT_return          [[nodiscard]]
#define XTAL_ATT_static          static
#define XTAL_ATT_friend          friend
#define XTAL_ATT_constexpr       constexpr


////////////////////////////////////////////////////////////////////////////////

//efine XTAL_TNX   XTAL_DEF_(return,inline)  XTAL_STD_(sign_type)
#define XTAL_TNX   XTAL_DEF_(return)         XTAL_STD_(sign_type)
#define XTAL_FLX                             XTAL_STD_(sign_type)
#define XTAL_FNX_(...)            [=, this] (XTAL_STD_(sign_type) o) XTAL_0FN_(1 == o? o: o&(__VA_ARGS__))


////////////////////////////////////////////////////////////////////////////////

#define XTAL_E0 ()
#define XTAL_F0() XTAL_F2_
#define XTAL_F1_(F_,     ...)           __VA_OPT__(XTAL_X2_(XTAL_F2_(F_, __VA_ARGS__)))///< Map.
#define XTAL_F2_(F_, A0, ...)    F_(A0) __VA_OPT__(XTAL_F0  XTAL_E0 (F_, __VA_ARGS__))

#define XTAL_X0_(...)                   __VA_ARGS__
#define XTAL_X1_(...)            XTAL_X0_(XTAL_X0_(XTAL_X0_(XTAL_X0_(__VA_ARGS__))))
#define XTAL_X2_(...)            XTAL_X1_(XTAL_X1_(XTAL_X1_(XTAL_X1_(__VA_ARGS__))))///< Repeat.

#define XTAL_S0_(SYM)                    #SYM
#define XTAL_S1_(SYM)            XTAL_S0_(SYM)///< Stringify.


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
