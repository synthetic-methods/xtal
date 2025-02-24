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

template <class I>
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
			using peritype = I;

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
			using peritype = I;

		};

	};
};

template <                            class ..._s>                                                 struct tabs;
template <class   T,                  class ...Is> requires different_q<        T , Is...        > struct tabs<T,             Is...> :         _std:: false_type {using type = void;};
template <class   T,                  class ...Is> requires      same_q<        T , Is...        > struct tabs<T,             Is...> :         _std::  true_type {using type =    T;};
template <intab_q T,    identity_q I, class ...Is> requires different_q<intab_u<T>, identity_u<I>> struct tabs<T,         I , Is...> : tabs<intab_s<T>,             I,  Is...>   {};
template <intab_q T,    identity_q I, class ...Is> requires      same_q<intab_u<T>, identity_u<I>> struct tabs<T,         I , Is...> : tabs<intab_s<T>,                 Is...>   {};
template <class   T, intercedent_q I, class ...Is>                                                 struct tabs<T,         I , Is...> : tabs<intab_s<T>, precedent_s<I>, Is...>   {};
template <class   T,  antecedent_q I, class ...Is>                                                 struct tabs<T,         I , Is...> : tabs<        T ,                 Is...>   {};
template <intab_q T,                  class ...Is>                                                 struct tabs<T, intab_u<T>, Is...> : tabs<intab_s<T>,                 Is...>   {};
//\
TODO: Need to be able to check against the top-most `complete_q<peritype>`.

template <class T, class ...Is>	concept          all_tabs_q =         tabs<based_t<T >, based_t<Is>...>{}() ;
template <class I, class ...Ts>	concept          all_tabs_p = (...and tabs<based_t<Ts>, based_t<I >   >{}());

template <class T, class ...Is>	concept          any_tabs_q = (...and (all_tabs_q<T ,    identity_t<Is>>));
template <class I, class ...Ts>	concept          any_tabs_p = (...and (all_tabs_q<Ts,    identity_t<I >>));

template <class T, class ...Is>	concept array_or_any_tabs_q = (...and (any_tabs_q<T , Is> or array_q<T >));
template <class I, class ...Ts>	concept array_or_any_tabs_p = (...and (any_tabs_q<Ts, I > or array_q<Ts>));


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
