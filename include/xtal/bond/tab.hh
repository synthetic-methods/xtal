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

template <class T>	XTAL_ASK taboo_q = requires {typename T::taboo;};
template <class T>	XTAL_USE taboo_s =           typename T::taboo::supertype;
template <class T>	XTAL_USE taboo_t =           typename T::taboo::     type;

template <class   T,              class   ...Ys>	XTAL_TYP tab_tail                        :               logical_t<0> {using type = void;};
template <class   T,              class   ...Ys>	XTAL_TYP tab_tail<T, cardinal_0 , Ys...> :               logical_t<1> {using type =    T;};
template <taboo_q T                            >	XTAL_TYP tab_tail<T,  taboo_t<T>       > :               logical_t<1> {using type =    T;};
template <taboo_q T,              class   ...Ys>	XTAL_TYP tab_tail<T,              Ys...> : tab_tail<taboo_s<T>,                  Ys...> {};
template <taboo_q T,              class   ...Ys>	XTAL_TYP tab_tail<T,  taboo_t<T>, Ys...> : tab_tail<taboo_s<T>,                  Ys...> {};
template <taboo_q T, liminal_q I, class   ...Ys>	XTAL_TYP tab_tail<T,          I , Ys...> : tab_tail<taboo_s<T>, subliminal_s<I>, Ys...> {};
template <class   T,              class   ...Ys>	XTAL_USE tab_tail_t                      = typename tab_tail<T, Ys...>:: type;
template <class   T,              class   ...Ys>	XTAL_ASK tab_tail_q                      =          tab_tail<T, Ys...>::value;

template <class   Y,              class   ...Ts>	XTAL_ASK tab_head_p = _std::conjunction_v<tab_tail<based_t<Ts>, Y >...>;
template <class   T,              class   ...Ys>	XTAL_ASK tab_head_q = _std::conjunction_v<tab_tail<based_t<T >, Ys>...>;

template <                        class   ...Ts>	XTAL_TYP tab_self        : isotropic_t<Ts...> {};
template <                        taboo_q ...Ts>	XTAL_TYP tab_self<Ts...> : _std::conjunction<tab_self<taboo_t<Ts>...>, tab_self<taboo_s<Ts>...>> {};
template <                        class   ...Ts>	XTAL_ASK tab_self_q      = tab_self<based_t<Ts>...>::value;
template <                        class   ...Ts>	XTAL_ASK tab_selfish_q = tab_self_q<Ts...> and not is_q<Ts...>;

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
			using supertype = S;
			using      type = Y;

		};

	};
};



///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
