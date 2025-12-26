#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <class T             >	using   tab_r = typename based_t<T>::taboo;
template <class T             >	using   tab_s = typename based_t<T>::taboo::hypotype;
template <class T             >	using   tab_t = typename based_t<T>::taboo::peritype;
template <         class ...Ts>	concept tab_q = requires {requires complete_q<tab_r<Ts>...>;};
#endif

////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Tags `subtype` while preserving Standard Layout.

\details
Avoids the `sizeof` inflation that can occur with multiple-inheritance
(e.g. frustrated Empty Base Optimization).
*/
template <class K>
struct tab
{
	template <class S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	public:
		using S_::S_;

		struct taboo
		{
			using hypotype = S;
			using peritype = K;

		};

	};
	template <tab_q S>
	class subtype<S> : public S
	{
		using S_ = S;
		
	public:
		using S_::S_;

		struct taboo : tab_r<S>
		{
			using hypotype = S;
			using peritype = K;

		};

	};
};


////////////////////////////////////////////////////////////////////////////////

#ifndef XTAL_DOC
template <class T, class ...Ks>  struct  tab_as;
template <class K, class ...Ts>  struct  tab_in;
#endif
template <class T, class ...Ks>	concept tab_as_q = tab_as<based_t<T >,            based_t<Ks> ...>{}() ;///< Matches `T` with     consecutive `Ks...` in sequence.
template <class T, class ...Ks>	concept tab_in_q = tab_as<based_t<T >, identity_t<based_t<Ks>>...>{}() ;///< Matches `T` with non-consecutive `Ks...` in sequence.

template <class K, class ...Ts>	concept tab_as_p = (...and tab_as_q<Ts, K>);///< Matches all `Ts...` with     consecutive `K`.
template <class K, class ...Ts>	concept tab_in_p = (...and tab_in_q<Ts, K>);///< Matches all `Ts...` with non-consecutive `K`.

template <class T, class ...Ks>	concept tab_affixed_q =  fixed_shaped_q<T    > and                              tab_as_q<T , Ks...>  ;///< Matches `fixed_shaped_q` and `array_shaped_q|tab_as_q`.
template <class T, class ...Ks>	concept tab_infixed_q =  fixed_shaped_q<T    > and                              tab_in_q<T , Ks...>  ;///< Matches `fixed_shaped_q` and `array_shaped_q|tab_in_q`.
template <class K, class ...Ts>	concept tab_affixed_p = (fixed_shaped_q<Ts...> and...and (array_shaped_q<Ts> or tab_as_q<Ts, K    >));///< Matches `fixed_shaped_q` and `array_shaped_q|tab_as_p`.
template <class K, class ...Ts>	concept tab_infixed_p = (fixed_shaped_q<Ts...> and...and (array_shaped_q<Ts> or tab_in_q<Ts, K    >));///< Matches `fixed_shaped_q` and `array_shaped_q|tab_in_p`.
#ifndef XTAL_DOC
template <class T,                  class ...Ks>                                                  struct tab_as                     : _std:: false_type {using type = void;};
template <class T,              same_q<T> ...Ks> requires same_q<T, Ks...>                        struct tab_as<T,           Ks...> : _std::  true_type {using type =    T;};
template <class T,  antecedent_q I, class ...Ks>                                                  struct tab_as<T,       I , Ks...> :  tab_as<        T ,               Ks...> {};
template <class T, intercedent_q I, class ...Ks>                                                  struct tab_as<T,       I , Ks...> :  tab_as<tab_s<T>, precedent_s<I>, Ks...> {};
template <tab_q T,    identity_q K, class ...Ks> requires different_q<tab_t<T>, typename K::type> struct tab_as<T,       K , Ks...> :  tab_as<tab_s<T>,             K,  Ks...> {};
template <tab_q T,    identity_q K, class ...Ks> requires      same_q<tab_t<T>, typename K::type> struct tab_as<T,       K , Ks...> :  tab_as<tab_s<T>,                 Ks...> {};
template <tab_q T,         different_q<T> ...Ks>                                                  struct tab_as<T, tab_t<T>, Ks...> :  tab_as<tab_s<T>,                 Ks...> {};

template <class K,                  class ...Ts>                                                  struct tab_in              : _std:: false_type {using type = void;};
template <class K,   tab_in_q<K> T, class ...Ts>                                                  struct tab_in<K, T, Ts...> : _std::  true_type {using type = T   ;};
template <class K,         class T, class ...Ts>                                                  struct tab_in<K, T, Ts...> : tab_in<K, Ts...> {};
#endif
template <class T,                  class ...Ks> using  tab_as_t = typename tab_as<T, Ks...>::type;///< Provides the type at the given path.
template <class K,                  class ...Ts> using  tab_in_t = typename tab_in<K, Ts...>::type;///< Provides the type at the given path fragment.


////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <                   class ..._s>	struct  tab_comparable;
template <                   class ..._s>	struct  tab_compatible;
template <                   class ..._s>	struct  tab_precedence;

template <                   class ..._s>	struct  tab_comparable              : _std::negation<_std::disjunction<logical_constant_t<tab_q<_s>>...>> {};
template <                   class ..._s>	struct  tab_compatible              : _std::negation<_std::disjunction<logical_constant_t<tab_q<_s>>...>> {};
template <class T,           class ..._s>	struct  tab_precedence<T, _s...>    : _std::negation<_std::disjunction<logical_constant_t<tab_q<_s>>...>> {};
template <                   tab_q ..._s>	struct  tab_comparable<      _s...> :                                             isotropic_t<tab_t<_s>...>  {};// `T == _s...`             (shallow)
template <                   tab_q ..._s>	struct  tab_compatible<      _s...> : _std::conjunction<tab_comparable<_s...>, tab_compatible<tab_s<_s>...>> {};// `T == _s...`             (deep)
template <tab_q T, class  U             >	struct  tab_precedence<T, U       > : _std::disjunction<tab_compatible<T, U >, tab_precedence<tab_s<T>, U>>  {};// `T >= U`                 (deep)
template <tab_q T, class  U, class ..._s>	struct  tab_precedence<T, U, _s...> : _std::conjunction<tab_precedence<T, U >, tab_precedence<     U, _s ...>> {};// `T >= U`, `U >= _s...` (deep)
#endif
template <                   class ..._s>	concept tab_comparable_q =  tab_comparable<based_t<_s>...>{}();///<\brief Determines whether `_s...` share the top-most tab.
template <                   class ..._s>	concept tab_compatible_q =  tab_compatible<based_t<_s>...>{}();///<\brief Determines whether `_s...` share the all tabs.
template <                   class ..._s>	concept tab_precedence_p =  tab_precedence<based_t<_s>...>{}();///<\brief Determines whether `_s...` is in decreasing tab-order.
template <class T,           class ..._s>	concept tab_preference_p =  requires {requires tab_precedence_p<tab_s<T>, _s...>;};///<\brief Determines whether `_s...` is in strictly-decreasing tab-order.


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
