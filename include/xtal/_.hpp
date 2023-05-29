#pragma once

#ifdef  NDEBUG
#define XTAL_LOG 1//release
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
//\
TODO: Allow command-line/[c]?make configuration.

#define XTAL_STD_(NYM) XTAL_STD_##NYM

#define XTAL_STD_IEEE 0//754

#define XTAL_STD_size_t ::std::size_t
#define XTAL_STD_sign_t ::std::int_fast8_t
#define XTAL_STD_null_t ::std::nullptr_t;
#define XTAL_STD_unit_t ::std::monostate;


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

#elif   defined(__GNUC__) or defined(__GNUG__)
#define XTAL_V00_GNUC XTAL_V00_(__GNUC__, __GNUC_MINOR__)
#define XTAL_V00_MSVC 0
#define XTAL_V00_LLVM 0

#else
#define XTAL_V00_MSVC 0
#define XTAL_V00_LLVM 0
#define XTAL_V00_GNUC 0

#endif

#ifndef NDEBUG
#if     XTAL_V00_MSVC
static_assert(1932 <= XTAL_V00_MSVC);

#elif   XTAL_V00_LLVM
static_assert(1300 <= XTAL_V00_LLVM);

#elif   XTAL_V00_GNUC
static_assert(1101 <= XTAL_V00_GNUC);

#endif
#endif


////////////////////////////////////////////////////////////////////////////////

#define XTAL_ENV_(NYM) XTAL_ENV_##NYM

#if     XTAL_V00_MSVC
#define XTAL_ENV_pop  _Pragma("warning(pop)")
#define XTAL_ENV_push _Pragma("warning(push)")\
                      _Pragma("warning(disable:4010)")

#elif   XTAL_V00_LLVM
#define XTAL_ENV_pop  _Pragma("clang diagnostic pop")
#define XTAL_ENV_push _Pragma("clang diagnostic push")\
                      _Pragma("clang diagnostic ignored \"-Wcomment\"")

#elif   XTAL_V00_GNUC
#define XTAL_ENV_pop  _Pragma("GCC diagnostic pop")
#define XTAL_ENV_push _Pragma("GCC diagnostic push")

#endif


////////////////////////////////////////////////////////////////////////////////

#define XTAL_TYP                             decltype(auto)
#define XTAL_TYP_(...) ::std::remove_cvref_t<decltype(__VA_ARGS__)>
#define XTAL_VAL_(...)                ::std::declval <__VA_ARGS__>()
#define XTAL_FWD_(...)           static_cast<         __VA_ARGS__ &&>
#define XTAL_REF_(...)           static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#define XTAL_DEF                                                  auto &&
#define XTAL_DEF_(...)                                __VA_ARGS__ auto &&


#define XTAL_NEW                            constexpr            
#define XTAL_OP2       [[nodiscard]]        constexpr    decltype(auto) operator
#define XTAL_OP1                            constexpr    decltype(auto) operator
#define XTAL_FN2       [[nodiscard]]        constexpr    decltype(auto)
#define XTAL_FN1                            constexpr    decltype(auto)
#define XTAL_FN0                            constexpr             void
#define XTAL_FZ2       [[nodiscard]] static constexpr    decltype(auto)
#define XTAL_FZ1                     static constexpr    decltype(auto)
#define XTAL_FZ0                     static constexpr             void
#define XTAL_LET                     static constexpr             auto

#define XTAL_NEW_(...)                      constexpr __VA_ARGS__
#define XTAL_OP1_(...)                      constexpr __VA_ARGS__       operator
#define XTAL_OP2_(...) [[nodiscard]]        constexpr __VA_ARGS__       operator
#define XTAL_FN1_(...)                      constexpr __VA_ARGS__
#define XTAL_FN2_(...) [[nodiscard]]        constexpr __VA_ARGS__
#define XTAL_FZ1_(...)               static constexpr __VA_ARGS__
#define XTAL_FZ2_(...) [[nodiscard]] static constexpr __VA_ARGS__
#define XTAL_LET_(...)               static constexpr __VA_ARGS__

#define XTAL_0EX                                      noexcept
#define XTAL_0EX_(REF)                            REF noexcept
#define XTAL_0FX                            const     noexcept
#define XTAL_0FX_(REF)                      const REF noexcept
#define XTAL_0FN                            constexpr noexcept
#define XTAL_0FN_(...)                      constexpr noexcept {return (__VA_ARGS__);}
#define XTAL_RE2_(SIG, ...)             SIG         & noexcept {return (__VA_ARGS__);};\
                                        SIG const   & noexcept {return (__VA_ARGS__);};
#define XTAL_RE4_(SIG, ...)             SIG         & noexcept {return (__VA_ARGS__);};\
                                        SIG        && noexcept {return (__VA_ARGS__);};\
                                        SIG const   & noexcept {return (__VA_ARGS__);};\
                                        SIG const  && noexcept {return (__VA_ARGS__);};;
#define XTAL_CO4_(TYP)                      constexpr TYP &operator = (TYP const  &) noexcept = default;\
                                            constexpr TYP             (TYP const  &) noexcept = default;\
                                            constexpr TYP &operator =       (TYP &&) noexcept = default;\
                                            constexpr TYP                   (TYP &&) noexcept = default;;
#define XTAL_CO2_(TYP)                                TYP()                          noexcept = default;\
                                                     ~TYP()                          noexcept = default;;


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
