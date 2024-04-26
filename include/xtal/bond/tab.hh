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

template <class   T> XTAL_ASK taboo_q = requires {typename T::taboo;};
template <class   T> XTAL_USE taboo_o =           typename T::taboo::pseudotype;
template <class   T> XTAL_USE taboo_s =           typename T::taboo:: supertype;

template <class   T,              class ...Ys> XTAL_TYP tab_rest                        :               logical_t<0> {using type = void;};
template <class   T,              class ...Ys> XTAL_TYP tab_rest<T, cardinal_0 , Ys...> :               logical_t<1> {using type =    T;};
template <taboo_q T                          > XTAL_TYP tab_rest<T,  taboo_o<T>       > :               logical_t<1> {using type =    T;};
template <taboo_q T,              class ...Ys> XTAL_TYP tab_rest<T,              Ys...> : tab_rest<taboo_s<T>,                  Ys...> {};
template <taboo_q T,              class ...Ys> XTAL_TYP tab_rest<T,  taboo_o<T>, Ys...> : tab_rest<taboo_s<T>,                  Ys...> {};
template <taboo_q T, liminal_q I, class ...Ys> XTAL_TYP tab_rest<T,          I , Ys...> : tab_rest<taboo_s<T>, subliminal_s<I>, Ys...> {};
template <class   T,              class ...Ys> XTAL_USE tab_rest_t                      = typename tab_rest<T, Ys...>:: type;
template <class   T,              class ...Ys> XTAL_ASK tab_rest_q                      =          tab_rest<T, Ys...>::value;

template <class Y, class ...Ts> XTAL_ASK tab_p = _std::conjunction_v<tab_rest<based_t<Ts>, Y >...>;
template <class T, class ...Ys> XTAL_ASK tab_q = _std::conjunction_v<tab_rest<based_t<T >, Ys>...>;

template <class Y>
struct tab
{
	template <class S>
	class subtype : public S
	{
	public:
		using S::S;
		
		struct taboo
		{
			using  supertype = S;
			using pseudotype = Y;

		};

	};
};



///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
