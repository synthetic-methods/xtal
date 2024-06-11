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

template <class 	                        ...Ts>	XTAL_ASK taboo_q = (...and requires {typename Ts::taboo;});
template <class   T                            >	XTAL_USE taboo_s = typename T ::taboo::supertype;
template <class   T                            >	XTAL_USE taboo_t = typename T ::taboo::     type;

template <class   T,              class   ...Ys>	XTAL_TYP tail_tab                        :               Logical_t<0> {using type = void;};
template <class   T,              class   ...Ys>	XTAL_TYP tail_tab<T, Cardinal_0 , Ys...> :               Logical_t<1> {using type =    T;};
template <taboo_q T                            >	XTAL_TYP tail_tab<T,  taboo_t<T>       > :               Logical_t<1> {using type =    T;};
template <taboo_q T,              class   ...Ys>	XTAL_TYP tail_tab<T,              Ys...> : tail_tab<taboo_s<T>,                  Ys...> {};
template <taboo_q T,              class   ...Ys>	XTAL_TYP tail_tab<T,  taboo_t<T>, Ys...> : tail_tab<taboo_s<T>,                  Ys...> {};
template <taboo_q T, Liminal_q I, class   ...Ys>	XTAL_TYP tail_tab<T,          I , Ys...> : tail_tab<taboo_s<T>, Subliminal_s<I>, Ys...> {};
template <class   T,              class   ...Ys>	XTAL_USE tail_tab_t                      = typename tail_tab<T, Ys...>:: type;
template <class   T,              class   ...Ys>	XTAL_ASK tail_tab_q                      =          tail_tab<T, Ys...>::value;

template <class   Y,              class   ...Ts>	XTAL_ASK head_tab_p = _std::conjunction_v<tail_tab<based_t<Ts>, Y >...>;
template <class   T,              class   ...Ys>	XTAL_ASK head_tab_q = _std::conjunction_v<tail_tab<based_t<T >, Ys>...>;

template <                        class   ...Ts>	XTAL_TYP self_tab        : isotropic_t<Ts...> {};
template <                        taboo_q ...Ts>	XTAL_TYP self_tab<Ts...> : _std::conjunction<self_tab<taboo_t<Ts>...>, self_tab<taboo_s<Ts>...>> {};
template <                        class   ...Ts>	XTAL_ASK self_tab_q      = self_tab<based_t<Ts>...>::value;
template <                        class   ...Ts>	XTAL_ASK twin_tab_q      = taboo_q<Ts...> and self_tab_q<Ts...> and infungible_q<Ts...>;

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
