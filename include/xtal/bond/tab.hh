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

template <class   T                            >	using      taboo_s = typename based_t<T>::taboo::supertype;
template <class   T                            >	using      taboo_t = typename based_t<T>::taboo::     type;
template <                        class   ...Ts>	concept    taboo_d = (...and not requires {typename taboo_t<Ts>;});
template <                        class   ...Ts>	concept    taboo_q = (...and     requires {typename taboo_t<Ts>;});

template <class   T,              class   ...Ys>	struct     all_tab                         :           constant_t<false> {using type = void;};
template <class   T,              class   ...Ys>	struct     all_tab<T, constant_t<0>, Ys...> :           constant_t< true> {using type =    T;};
template <taboo_q T                            >	struct     all_tab<T,   taboo_t<T>       > :           constant_t< true> {using type =    T;};
template <taboo_q T,              class   ...Ys>	struct     all_tab<T,               Ys...> : all_tab<taboo_s<T>,                  Ys...> {};
template <taboo_q T,              class   ...Ys>	struct     all_tab<T,   taboo_t<T>, Ys...> : all_tab<taboo_s<T>,                  Ys...> {};
template <taboo_q T, liminal_q I, class   ...Ys>	struct     all_tab<T,           I , Ys...> : all_tab<taboo_s<T>, subliminal_s<I>, Ys...> {};
template <class   T,              class   ...Ys>	using      all_tab_t                       = typename all_tab<T, Ys...>:: type;
template <class   T,              class   ...Ys>	concept    all_tab_q                       =          all_tab<T, Ys...>::value;

template <class   Y,              class   ...Ts>	concept    any_tab_p = _std::conjunction_v<all_tab<based_t<Ts>, Y >...>;
template <class   T,              class   ...Ys>	concept    any_tab_q = _std::conjunction_v<all_tab<based_t<T >, Ys>...>;

template <                        class   ...Ts>	struct     self_tab        : _std::false_type {};
template <                        taboo_d ...Ts>	struct     self_tab<Ts...> : isotropic_t<Ts...> {};
template <                        taboo_q ...Ts>	struct     self_tab<Ts...> : _std::conjunction<self_tab<taboo_t<Ts>...>, self_tab<taboo_s<Ts>...>> {};
template <                        class   ...Ts>	concept    self_tab_q      = self_tab<based_t<Ts>...>::value;
template <                        class   ...Ts>	concept    twin_tab_q      = not isotropic_q<Ts...> and taboo_q<Ts...> and self_tab_q<Ts...>;

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
