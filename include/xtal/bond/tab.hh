#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class T             >	using          taboo_t = typename   based_t<T >::taboo;
template <class T             >	using          taboo_s = typename   taboo_t<T >::hypotype;
template <class T             >	using          taboo_u = typename   taboo_t<T >::peritype;
template <class T             >	auto constexpr taboo_n = typename   taboo_t<T >::perisize{};
template <         class ...Ts>	concept        taboo_q = complete_q<taboo_t<Ts>...>;
template <         class ...Ts>	concept      untaboo_q = not taboo_q<Ts...>;
template <class T, class S    >	concept     subtaboo_q = taboo_q<S, T> and taboo_n<S> < taboo_n<T>;
template <class S, class T    >	concept   supertaboo_q = taboo_q<S, T> and taboo_n<S> < taboo_n<T>;


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
			using perisize = cardinal_constant_t<0>;

		};

	};
	template <taboo_q S>
	class subtype<S> : public S
	{
	public:
		using S::S;

		struct taboo : taboo_t<S>
		{
			using hypotype = S;
			using peritype = I;
			using perisize = succedent_s<typename taboo_t<S>::perisize>;

		};

	};
};

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

template <class T, class ...Is>	concept    tabbed_q =         tabbed<based_t<T >, based_t<Is>...>{}() ;
template <class I, class ...Ts>	concept    tabbed_p = (...and tabbed<based_t<Ts>, based_t<I >   >{}());


template <class T, class ...Is>	concept       tab_q = (...and tabbed_q<T , identity_t<Is>> );
template <class I, class ...Ts>	concept       tab_p = (...and tabbed_q<Ts, identity_t<I >> );

template <class T, class ...Is>	concept  some_tab_q = (...or  tabbed_q<T , identity_t<Is>> );
template <class I, class ...Ts>	concept  some_tab_p = (...or  tabbed_q<Ts, identity_t<I >> );

template <class T, class ...Is>	concept array_tab_q = some_tab_q<T, Is...> and (...and (array_shaped_q<T > or tab_q<T , Is>));
template <class I, class ...Ts>	concept array_tab_p = some_tab_p<I, Ts...> and (...and (array_shaped_q<Ts> or tab_q<Ts, I >));


template <  class   ...Ts>	struct  tab_comparable;
template <  class   ...Ts>	struct  tab_compatible;
template <class   ...Ts>	concept tab_comparable_q      =  tab_comparable<based_t<Ts>...>{}();
template <class   ...Ts>	concept tab_compatible_q      =  tab_compatible<based_t<Ts>...>{}();

template <  class   ...Ts>	struct  tab_comparable        : _std::false_type {};
template <untaboo_q ...Ts>	struct  tab_comparable<Ts...> : _std:: true_type {};
template <  taboo_q ...Ts>	struct  tab_comparable<Ts...> :  isotropic_t<taboo_u<Ts>...> {};

template <  class   ...Ts>	struct  tab_compatible        : _std::false_type {};
template <untaboo_q ...Ts>	struct  tab_compatible<Ts...> : _std:: true_type {};
template <  taboo_q ...Ts>	struct  tab_compatible<Ts...> : _std::conjunction<tab_compatible<taboo_s<Ts>...>, tab_comparable<Ts...>> {};

template <class   T,      class      ...Ts>	struct  subtabbed           : _std::false_type {};
template <taboo_q T, supertaboo_q<T> ...Ts>	struct  subtabbed<T, Ts...> : _std::disjunction<tab_compatible<taboo_s<T>, Ts...>, subtabbed<taboo_s<T>, Ts...>> {};
template <class T,        class      ...Ts>	concept subtabbed_q         =  subtabbed<based_t<T>, based_t<Ts>...>{}();
template <class T,        class      ...Ts>	concept insubtabbed_q         =  not subtabbed_q<T, Ts...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
