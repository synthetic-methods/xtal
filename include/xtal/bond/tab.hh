#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

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
};
template <class   T             > using         taboo_s =            typename T ::taboo::hypotype;
template <class   T             > using         taboo_u =            typename T ::taboo::peritype;
template <           class ...Ts> concept       taboo_q = complete_q<typename Ts::taboo...>;


template <                            class ..._s>                                                  struct tabbed;
template <class   T                              >                                                  struct tabbed<T, _std:: true_type> : _std:: true_type {using type =    T;};
template <class   T                              >                                                  struct tabbed<T, _std::false_type> : _std::false_type {using type = void;};
template <class   T,                  class ...Is>                                                  struct tabbed<T,                Is...> : tabbed<T, logical_constant_t<same_q<T, Is...>>> {};
template <taboo_q T,                  class ...Is>                                                  struct tabbed<T,    taboo_u<T>, Is...> : tabbed<taboo_s<T>,                  Is...>   {};
template <class   T, intercedent_q I, class ...Is>                                                  struct tabbed<T,            I , Is...> : tabbed<taboo_s<T>, precedent_s<I>,  Is...>   {};
template <class   T,  antecedent_q I, class ...Is>                                                  struct tabbed<T,            I , Is...> : tabbed<        T ,                  Is...>   {};
template <taboo_q T,    identity_q I, class ...Is> requires      same_q<taboo_u<T>, identity_u<I>>  struct tabbed<T,            I , Is...> : tabbed<taboo_s<T>,                  Is...>   {};
template <taboo_q T,    identity_q I, class ...Is> requires un_n<same_q<taboo_u<T>, identity_u<I>>> struct tabbed<T,            I , Is...> : tabbed<taboo_s<T>,              I,  Is...>   {};


//\
TODO: Need to be able to check against the top-most `complete_q<peritype>`.

template <class   T, class ...Is> concept    tabbed_q =         tabbed<based_t<T >, based_t<Is>...>{}() ;
template <class   I, class ...Ts> concept    tabbed_p = (...and tabbed<based_t<Ts>, based_t<I >   >{}());

template <class   T, class ...Is> concept       tab_q = (...and tabbed_q<T , identity_t<Is>> );
template <class   I, class ...Ts> concept       tab_p = (...and tabbed_q<Ts, identity_t<I >> );

template <class   T, class ...Is> concept  some_tab_q = (...or  tabbed_q<T , identity_t<Is>> );
template <class   I, class ...Ts> concept  some_tab_p = (...or  tabbed_q<Ts, identity_t<I >> );

template <class   T, class ...Is> concept array_tab_q = some_tab_q<T, Is...> and (...and (array_shaped_q<T > or tab_q<T , Is>));
template <class   I, class ...Ts> concept array_tab_p = some_tab_p<I, Ts...> and (...and (array_shaped_q<Ts> or tab_q<Ts, I >));

template <           class ...Ts> struct        tab_comparable;
template <           class ...Ts> struct        tab_compatible;
template <           class ...Ts> concept       tab_comparable_q      = tab_comparable<based_t<Ts>...>{}();
template <           class ...Ts> concept       tab_compatible_q      = tab_compatible<based_t<Ts>...>{}();

template <           class ...Ts> struct        tab_comparable        : logical_constant_t<same_q<        Ts... >> {};
template <         taboo_q ...Ts> struct        tab_comparable<Ts...> : logical_constant_t<same_q<taboo_u<Ts>...>> {};

template <           class ...Ts> struct        tab_compatible        :                                                   tab_comparable<Ts...>  {};
template <         taboo_q ...Ts> struct        tab_compatible<Ts...> : _std::conjunction<tab_compatible<taboo_s<Ts>...>, tab_comparable<Ts...>> {};



///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
