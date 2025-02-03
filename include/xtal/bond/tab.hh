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
template <class   T                              >                                                  struct tabbed<T, logical_constant_t<1>> : logical_constant_t<1> {using type =    T;};
template <class   T                              >                                                  struct tabbed<T, logical_constant_t<0>> : logical_constant_t<0> {using type = void;};
template <class   T,                  class ...Is>                                                  struct tabbed<T,                Is...> : tabbed<T, logical_constant_t<same_q<T, Is...>>> {};
template <taboo_q T,                  class ...Is>                                                  struct tabbed<T,    taboo_u<T>, Is...> : tabbed<taboo_s<T>,                  Is...>   {};
template <class   T, intercedent_q I, class ...Is>                                                  struct tabbed<T,            I , Is...> : tabbed<taboo_s<T>, precedent_s<I>,  Is...>   {};
template <class   T,  antecedent_q I, class ...Is>                                                  struct tabbed<T,            I , Is...> : tabbed<        T ,                  Is...>   {};
template <taboo_q T,    identity_q I, class ...Is> requires      same_q<taboo_u<T>, identity_u<I>>  struct tabbed<T,            I , Is...> : tabbed<taboo_s<T>,                  Is...>   {};
template <taboo_q T,    identity_q I, class ...Is> requires un_n<same_q<taboo_u<T>, identity_u<I>>> struct tabbed<T,            I , Is...> : tabbed<taboo_s<T>,              I,  Is...>   {};


template <           class ..._s> concept       tabbed_q =          tabbed<based_t<_s>...>{}();

template <class   T, class ...Is> concept       tab_q = (...and tabbed_q<T , identity_t<Is>> );
template <class   I, class ...Ts> concept       tab_p = (...and tabbed_q<Ts, identity_t<I >> );

template <class   T, class ...Is> concept  some_tab_q = (...or  tabbed_q<T , identity_t<Is>> );
template <class   I, class ...Ts> concept  some_tab_p = (...or  tabbed_q<Ts, identity_t<I >> );

template <class   T, class ...Is> concept array_tab_q = some_tab_q<T, Is...> and (...and (array_shaped_q<T > or tab_q<T , Is>));
template <class   I, class ...Ts> concept array_tab_p = some_tab_p<I, Ts...> and (...and (array_shaped_q<Ts> or tab_q<Ts, I >));

template <           class ...Ts> struct        tab_compatible;
template <           class ...Ts> concept       tab_compatible_q      = tab_compatible<based_t<Ts>...>{}();
template <           class ...Ts> concept       tab_convertible_q     = tab_compatible_q<Ts...> and different_q<Ts...>;

template <           class ...Ts> struct        tab_compatible        : logical_constant_t<same_q<        Ts... >                                     > {};
template <         taboo_q ...Ts> struct        tab_compatible<Ts...> : logical_constant_t<same_q<taboo_u<Ts>...> and tab_compatible_q<taboo_s<Ts>...>> {};



///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
