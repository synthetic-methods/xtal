#pragma once

#ifdef  NDEBUG
#define XTAL_LOG 0//release
#else
#define XTAL_LOG 1//debug
#endif

#if XTAL_LOG
#include <iostream>
#endif

#include <cstdint>
#include <variant>


///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#define XTAL_(NYM) XTAL_##NYM


////////////////////////////////////////////////////////////////////////////////
//\
TODO: Allow command-line/[c]?make configuration?

#define XTAL_STD_(NYM) XTAL_STD_##NYM
#define XTAL_STD ((__cplusplus/100)%100)
#define XTAL_STD_IEC 60559

#define XTAL_STD_null_t ::std::nullptr_t
#define XTAL_STD_unit_t ::std::monostate
#define XTAL_STD_byte_t ::std::byte
#define XTAL_STD_sign_t ::std::int_fast8_t
#define XTAL_STD_size_t ::std::size_t
#define XTAL_STD_size_s ::std::ptrdiff_t


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

#define XTAL_V00_(MAJ, MIN) (100*MAJ + MIN)
#define XTAL_V00 XTAL_V00_(1, 0)
#if     defined(_MSC_VER)
#define XTAL_V00_MSVC _MSC_VER
#define XTAL_V00_LLVM 0
#define XTAL_V00_GNUC 0

#elif   defined(__clang__)
#define XTAL_V00_LLVM XTAL_V00_(__clang_major__, __clang_minor__)
#define XTAL_V00_GNUC 0
#define XTAL_V00_MSVC 0

#elif   defined(__GNUC__)
#define XTAL_V00_GNUC XTAL_V00_(__GNUC__, __GNUC_MINOR__)
#define XTAL_V00_MSVC 0
#define XTAL_V00_LLVM 0

#else
#define XTAL_V00_MSVC 0
#define XTAL_V00_LLVM 0
#define XTAL_V00_GNUC 0

#endif


#if     XTAL_V00_MSVC
static_assert(1933 <= XTAL_V00_MSVC);

#elif   XTAL_V00_LLVM
static_assert(1400 <= XTAL_V00_LLVM);

#elif   XTAL_V00_GNUC
//static_assert(1200 <= XTAL_V00_GNUC);  

#endif


////////////////////////////////////////////////////////////////////////////////

#define XTAL_ENV_(NYM) XTAL_ENV_##NYM

#if     XTAL_V00_MSVC
#define XTAL_ENV_pop  _Pragma("warning(pop)")
#define XTAL_ENV_push _Pragma("warning(push)")\
                      _Pragma("warning(disable:4010)")\

#elif   XTAL_V00_LLVM
#define XTAL_ENV_pop  _Pragma("clang diagnostic pop")
#define XTAL_ENV_push _Pragma("clang diagnostic push")\
                      _Pragma("clang diagnostic ignored \"-Wcomment\"")\
                      _Pragma("clang diagnostic ignored \"-Wdocumentation\"")\
                      _Pragma("clang diagnostic ignored \"-Wconstant-conversion\"")\
                      _Pragma("clang diagnostic ignored \"-Wlogical-op-parentheses\"")\

#elif   XTAL_V00_GNUC
#define XTAL_ENV_pop  _Pragma("GCC diagnostic pop")
#define XTAL_ENV_push _Pragma("GCC diagnostic push")\
                      _Pragma("GCC diagnostic ignored \"-Wsubobject-linkage\"")\
//                    _Pragma("GCC diagnostic ignored \"-Winterference-size\"")\

#endif


////////////////////////////////////////////////////////////////////////////////

#define XTAL_TYP                             decltype(auto)
#define XTAL_TYP_(...) ::std::remove_cvref_t<decltype(__VA_ARGS__)>
#define XTAL_VAL_(...)                ::std::declval <__VA_ARGS__>()
#define XTAL_MOV_(...)                    ::std::move(__VA_ARGS__)
#define XTAL_REF_(...)           static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#define XTAL_DEF_(...)                                __VA_ARGS__ auto &&
#define XTAL_DEF                                                  auto &&
#define XTAL_NYM                        struct
#define XTAL_USE                         using
#define XTAL_ASK                       concept
#define XTAL_REQ                      requires
#define XTAL_REQ_(...)                requires requires { __VA_ARGS__ ;}

#define XTAL_CON                     constexpr       
#define XTAL_CXN                     constexpr explicit

#define XTAL_OP0_(SYM) XTAL_OP0_##SYM
#define XTAL_OP0_explicit            constexpr explicit              operator
#define XTAL_OP0_implicit            constexpr                       operator
#define XTAL_OP1                     constexpr        decltype(auto) operator
#define XTAL_OP2       [[nodiscard]] constexpr        decltype(auto) operator
#define XTAL_TN0                                               void
#define XTAL_TN1                     constexpr        decltype(auto)
#define XTAL_TN2       [[nodiscard]] constexpr        decltype(auto)
#define XTAL_FN0                               static          void
#define XTAL_FN1                     constexpr static decltype(auto)
#define XTAL_FN2       [[nodiscard]] constexpr static decltype(auto)
#define XTAL_LET                     constexpr static          auto

#define XTAL_OP1_(...)               constexpr        __VA_ARGS__ operator
#define XTAL_OP2_(...) [[nodiscard]] constexpr        __VA_ARGS__ operator
#define XTAL_TN1_(...)               constexpr        __VA_ARGS__
#define XTAL_TN2_(...) [[nodiscard]] constexpr        __VA_ARGS__
#define XTAL_FN1_(...)               constexpr static __VA_ARGS__
#define XTAL_FN2_(...) [[nodiscard]] constexpr static __VA_ARGS__
#define XTAL_LET_(...)               constexpr static __VA_ARGS__

#define XTAL_0EX                               noexcept
#define XTAL_0FX                     const     noexcept
#define XTAL_0EX_(REF)                     REF noexcept
#define XTAL_0FX_(REF)               const REF noexcept

#define XTAL_0FN                     constexpr noexcept
#define XTAL_0FM             mutable constexpr noexcept
#define XTAL_0FN_(...)               constexpr noexcept {return (__VA_ARGS__);}
#define XTAL_0FM_(...)       mutable constexpr noexcept {return (__VA_ARGS__);}
#define XTAL_0EZ_(...)                         noexcept {return (__VA_ARGS__);}

#define XTAL_TO2_(SIG, ...)      SIG const     noexcept {return (__VA_ARGS__);}\
                                 SIG           noexcept {return (__VA_ARGS__);};
#define XTAL_TO4_(SIG, ...)      SIG const   & noexcept {return (__VA_ARGS__);}\
                                 SIG         & noexcept {return (__VA_ARGS__);}\
                                 SIG const  && noexcept {return (__VA_ARGS__);}\
                                 SIG        && noexcept {return (__VA_ARGS__);};

#define XTAL_DO2_(SIG, ...)      SIG const     noexcept          __VA_ARGS__   \
                                 SIG           noexcept          __VA_ARGS__   ;
#define XTAL_DO4_(SIG, ...)      SIG const   & noexcept          __VA_ARGS__   \
                                 SIG         & noexcept          __VA_ARGS__   \
                                 SIG const  && noexcept          __VA_ARGS__   \
                                 SIG        && noexcept          __VA_ARGS__   ;

#define XTAL_CO0_(TYP)                         TYP()                          noexcept = default;\
                                              ~TYP()                          noexcept = default;;
#define XTAL_CO4_(TYP)               constexpr TYP & operator = (TYP const &) noexcept = default;\
                                     constexpr TYP              (TYP const &) noexcept = default;\
                                     constexpr TYP & operator = (TYP      &&) noexcept = default;\
                                     constexpr TYP              (TYP      &&) noexcept = default;;


////////////////////////////////////////////////////////////////////////////////

#define XTAL_FNX    [[nodiscard]] XTAL_STD_(sign_t)
#define XTAL_FLX                  XTAL_STD_(sign_t)
#define XTAL_FLX_(...) [=, this] (XTAL_STD_(sign_t) o) XTAL_0FN_(1 == o? o: o&(__VA_ARGS__))

#define XTAL_1FN_(...) (XTAL_DEF ...oo) XTAL_0FN_(__VA_ARGS__(XTAL_REF_(oo)...))


////////////////////////////////////////////////////////////////////////////////

#define XTAL_E0 ()
#define XTAL_F0() XTAL_F2_
#define XTAL_F1_(F_,     ...)        __VA_OPT__(XTAL_X2_(XTAL_F2_(F_, __VA_ARGS__)))///< Map.
#define XTAL_F2_(F_, A0, ...) F_(A0) __VA_OPT__(XTAL_F0  XTAL_E0 (F_, __VA_ARGS__))

#define XTAL_X0_(...) __VA_ARGS__
#define XTAL_X1_(...) XTAL_X0_(XTAL_X0_(XTAL_X0_(XTAL_X0_(__VA_ARGS__))))
#define XTAL_X2_(...) XTAL_X1_(XTAL_X1_(XTAL_X1_(XTAL_X1_(__VA_ARGS__))))///< Repeat.

#define XTAL_S0_(SYM) #SYM
#define XTAL_S1_(SYM) XTAL_S0_(SYM)///< Stringify.


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
