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

template <class   T                            >	XTAL_USE   taboo_s = typename based_t<T>::taboo::supertype;
template <class   T                            >	XTAL_USE   taboo_t = typename based_t<T>::taboo::     type;
template <                        class   ...Ts>	XTAL_REQ   taboo_d = (...and not requires {typename taboo_t<Ts>;});
template <                        class   ...Ts>	XTAL_REQ   taboo_q = (...and     requires {typename taboo_t<Ts>;});

template <class   T,              class   ...Ys>	XTAL_TYP   tail_tab                         :           nominal_t<false> {using type = void;};
template <class   T,              class   ...Ys>	XTAL_TYP   tail_tab<T, nominal_t<0>, Ys...> :           nominal_t< true> {using type =    T;};
template <taboo_q T                            >	XTAL_TYP   tail_tab<T,   taboo_t<T>       > :           nominal_t< true> {using type =    T;};
template <taboo_q T,              class   ...Ys>	XTAL_TYP   tail_tab<T,               Ys...> : tail_tab<taboo_s<T>,                  Ys...> {};
template <taboo_q T,              class   ...Ys>	XTAL_TYP   tail_tab<T,   taboo_t<T>, Ys...> : tail_tab<taboo_s<T>,                  Ys...> {};
template <taboo_q T, liminal_q I, class   ...Ys>	XTAL_TYP   tail_tab<T,           I , Ys...> : tail_tab<taboo_s<T>, subliminal_s<I>, Ys...> {};
template <class   T,              class   ...Ys>	XTAL_USE   tail_tab_t                       = typename tail_tab<T, Ys...>:: type;
template <class   T,              class   ...Ys>	XTAL_REQ   tail_tab_q                       =          tail_tab<T, Ys...>::value;

template <class   Y,              class   ...Ts>	XTAL_REQ   head_tab_p = _std::conjunction_v<tail_tab<based_t<Ts>, Y >...>;
template <class   T,              class   ...Ys>	XTAL_REQ   head_tab_q = _std::conjunction_v<tail_tab<based_t<T >, Ys>...>;

template <                        class   ...Ts>	XTAL_TYP   self_tab        : _std::false_type {};
template <                        taboo_d ...Ts>	XTAL_TYP   self_tab<Ts...> : isotropic_t<Ts...> {};
template <                        taboo_q ...Ts>	XTAL_TYP   self_tab<Ts...> : _std::conjunction<self_tab<taboo_t<Ts>...>, self_tab<taboo_s<Ts>...>> {};
template <                        class   ...Ts>	XTAL_REQ   self_tab_q      = self_tab<based_t<Ts>...>::value;
template <                        class   ...Ts>	XTAL_REQ   twin_tab_q      = not isotropic_q<Ts...> and taboo_q<Ts...> and self_tab_q<Ts...>;

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
