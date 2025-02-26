#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class T             >	using   intab_t = typename based_t<T>::taboo;
template <class T             >	using   intab_s = typename based_t<T>::taboo::hypotype;
template <class T             >	using   intab_u = typename based_t<T>::taboo::peritype;
template <         class ...Ts>	concept intab_q = requires {requires complete_q<intab_t<Ts>...>;};
template <         class ...Ts>	concept untab_q = not intab_q<Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Tags `subtype` while preserving Standard Layout. \
Avoids the `sizeof` inflation that can occur with multiple-inheritance \
(e.g. frustrated Empty Base Optimization). \

template <class K>
struct tab
{
	template <class S>
	class subtype : public S
	{
	public:
		using S::S;

		struct taboo
		{
			using hypotype = S;
			using peritype = K;

		};

	};
	template <intab_q S>
	class subtype<S> : public S
	{
	public:
		using S::S;

		struct taboo : intab_t<S>
		{
			using hypotype = S;
			using peritype = K;

		};

	};
};


////////////////////////////////////////////////////////////////////////////////

template <class T, class ...Ks>  struct  tabbed;
template <class K, class ...Ts>  struct  tabbed_with;

template <class T, class ...Ks>	concept tabbed_q      =         tabbed<based_t<T >,            based_t<Ks> ...>{}() ;///< Matches `T` with     consecutive `Ks...` in sequence.
template <class T, class ...Ks>	concept tabbed_with_q =         tabbed<based_t<T >, identity_t<based_t<Ks>>...>{}() ;///< Matches `T` with non-consecutive `Ks...` in sequence.

template <class K, class ...Ts>	concept tabbed_p      = (...and tabbed<based_t<Ts>,            based_t<K >    >{}());///< Matches all `Ts...` with       outer `K`.
template <class K, class ...Ts>	concept tabbed_with_p = (...and tabbed<based_t<Ts>, identity_t<based_t<K >>   >{}());///< Matches all `Ts...` with inner/outer `K`.

template <class T, class ...Ks>	concept fixed_tabbed_q      =  fixed_shaped_q<T    > and                       tabbed_q     <T , Ks...>  ;///< Matches both `fixed_shaped_q` and `tabbed_q`.
template <class T, class ...Ks>	concept fixed_tabbed_with_q =  fixed_shaped_q<T    > and                       tabbed_with_q<T , Ks...>  ;///< Matches both `fixed_shaped_q` and `tabbed_with_q`.
template <class K, class ...Ts>	concept fixed_tabbed_p      = (fixed_shaped_q<Ts...> and...and (array_q<Ts> or tabbed_q     <Ts, K    >));///< Matches both `fixed_shaped_q` and `tabbed_p`.
template <class K, class ...Ts>	concept fixed_tabbed_with_p = (fixed_shaped_q<Ts...> and...and (array_q<Ts> or tabbed_with_q<Ts, K    >));///< Matches both `fixed_shaped_q` and `tabbed_with_p`.
///<\note\
Array signatures are ignored by the `fixed_tabbed(?:_with)_p` checks \
to allow simultaneous `size` checking. \


template <class   T,                   class ...Ks> requires different_q<        T , Ks...        > struct tabbed<T,             Ks...> :         _std:: false_type {using type = void;};
template <class   T,                   class ...Ks> requires      same_q<        T , Ks...        > struct tabbed<T,             Ks...> :         _std::  true_type {using type =    T;};
template <class   T,   antecedent_q I, class ...Ks>                                                 struct tabbed<T,         I , Ks...> : tabbed<        T ,                 Ks...>   {};
template <class   T,  intercedent_q I, class ...Ks>                                                 struct tabbed<T,         I , Ks...> : tabbed<intab_s<T>, precedent_s<I>, Ks...>   {};
template <intab_q T,     identity_q K, class ...Ks> requires different_q<intab_u<T>, identity_u<K>> struct tabbed<T,         K , Ks...> : tabbed<intab_s<T>,             K,  Ks...>   {};
template <intab_q T,     identity_q K, class ...Ks> requires      same_q<intab_u<T>, identity_u<K>> struct tabbed<T,         K , Ks...> : tabbed<intab_s<T>,                 Ks...>   {};
template <intab_q T,                   class ...Ks>                                                 struct tabbed<T, intab_u<T>, Ks...> : tabbed<intab_s<T>,                 Ks...>   {};

template <class K,                     class ...Ts> struct tabbed_with              : _std:: false_type {using type = void;};
template <class K, tabbed_with_q<K> T, class ...Ts> struct tabbed_with<K, T, Ts...> : _std::  true_type {using type = T   ;};
template <class K, class            T, class ...Ts> struct tabbed_with<K, T, Ts...> : tabbed_with<K, Ts...> {};

template <class K,                     class ...Ts> using  tabbed_with_t = typename tabbed_with<K, Ts...>::type;
template <class T,                     class ...Ks> using  tabbed_t      = typename tabbed     <T, Ks...>::type;


////////////////////////////////////////////////////////////////////////////////

template <                      class   ..._s>	struct  tab_comparable              : _std::false_type {};
template <                      class   ..._s>	struct  tab_compatible              : _std::false_type {};
template <                      class   ..._s>	struct  tab_precedence              : _std::false_type {};

template <                      untab_q ..._s>	struct  tab_comparable<      _s...> : _std:: true_type {};
template <                      untab_q ..._s>	struct  tab_compatible<      _s...> : _std:: true_type {};
template <intab_q T, untab_q U               >	struct  tab_precedence<T, U       > : _std:: true_type {};

template <                      intab_q ..._s>	struct  tab_comparable<      _s...> :                                             isotropic_t<intab_u<_s>...>  {};// `T == _s...`           (shallow)
template <                      intab_q ..._s>	struct  tab_compatible<      _s...> : _std::conjunction<tab_comparable<_s...>, tab_compatible<intab_s<_s>...>> {};// `T == _s...`           (deep)
template <intab_q T, class   U               >	struct  tab_precedence<T, U       > : _std::disjunction<tab_compatible<T, U >, tab_precedence<intab_s<T>, U>>  {};// `T >= U`               (deep)
template <intab_q T, class   U, class   ..._s>	struct  tab_precedence<T, U, _s...> : _std::conjunction<tab_precedence<T, U >, tab_precedence<     U, _s ...>> {};// `T >= U`, `U >= _s...` (deep)

template <                      class   ..._s>	concept tab_comparable_q =  tab_comparable<based_t<_s>...>{}();
template <                      class   ..._s>	concept tab_compatible_q =  tab_compatible<based_t<_s>...>{}();
template <                      class   ..._s>	concept tab_precedence_p =  tab_precedence<based_t<_s>...>{}();
template <class   T,            class   ..._s>	concept tab_preference_p =  requires {requires tab_precedence_p<intab_s<T>, _s...>;};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
