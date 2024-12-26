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
			using paratype = S;
			using peritype = I;

		};

	};
};
template <class   T                           > using        taboo_s =            typename T ::taboo::paratype;
template <class   T                           > using        taboo_u =            typename T ::taboo::peritype;
template <                         class ...Ts> concept      taboo_q = complete_q<typename Ts::taboo...>;

template <                         class ...Ts> struct  same_tabs;
template <                         class ...Ts> concept same_tabs_q      = same_tabs<based_t<Ts>...>::value;

template <                         class ...Ts> struct  same_tabs        : constant_t<same_q<        Ts... >                                > {};
template <                       taboo_q ...Ts> struct  same_tabs<Ts...> : constant_t<same_q<taboo_u<Ts>...> and same_tabs_q<taboo_s<Ts>...>> {};

template <                         class ..._s> struct       tabbed   ;
template <                         class ..._s> using        tabbed_s = typename tabbed<based_t<_s>...>:: type;
template <                         class ..._s> concept      tabbed_q =          tabbed<based_t<_s>...>::value;

template <class   T                           >                                                  struct tabbed<T, logical_t<1>       > : logical_t<1> {using type =    T;};
template <class   T                           >                                                  struct tabbed<T, logical_t<0>       > : logical_t<0> {using type = void;};
template <class   T,               class ...Is>                                                  struct tabbed<T,               Is...> : tabbed<T,        constant_t<same_q<T, Is...>>> {};
template <taboo_q T,               class ...Is>                                                  struct tabbed<T,   taboo_u<T>, Is...> : tabbed<taboo_s<T>,                    Is...>   {};
template <class   T, constant_q I, class ...Is> requires                          liminal_q<I>   struct tabbed<T,           I , Is...> : tabbed<taboo_s<T>, subliminal_s<I>,   Is...>   {};
template <class   T, constant_q I, class ...Is> requires                         terminal_q<I>   struct tabbed<T,           I , Is...> : tabbed<        T ,                    Is...>   {};
template <taboo_q T, identity_q I, class ...Is> requires      same_q<taboo_u<T>, identity_u<I>>  struct tabbed<T,           I , Is...> : tabbed<taboo_s<T>,                    Is...>   {};
template <taboo_q T, identity_q I, class ...Is> requires un_q<same_q<taboo_u<T>, identity_u<I>>> struct tabbed<T,           I , Is...> : tabbed<taboo_s<T>,              I,    Is...>   {};


template <class   T,               class ...Is> concept      tab_q = (...and tabbed_q<T , identity_t<Is>>);
template <class   I,               class ...Ts> concept      tab_p = (...and tabbed_q<Ts, identity_t<I >>);



///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
