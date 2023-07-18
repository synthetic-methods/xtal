#ifdef __INTELLISENSE__// stub...
#include "../any.hpp"
using namespace xtal;
namespace _retail
{
template <typename ...As>
struct any
{
	template <typename S>
	class subtype
	{};
};
}
#endif


//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace common;


////////////////////////////////////////////////////////////////////////////////
//\
This naked header is intended for inclusion within a `namespace` providing the decorators: \

template <typename T> struct define;///< Initializes `T`, e.g. defining core functionality.
template <typename T> struct refine;///< Finalizes   `T`, e.g. applying `ranges::view_interface`.

template <typename U> struct defer;///< Proxies   `U`, e.g. defining constructors/accessors.
template <typename U> struct refer;///< Delegates `U`, e.g. relaying operators/methods.

//\
In each case, the member `::template subtype<S>` extends `S` with the functionality required. \
See `concord/any.hpp` for core implementations, and `*/any.hpp` for extensions. \


////////////////////////////////////////////////////////////////////////////////
///\
Tags `subtype` with this namespace and the supplied types. \

template <typename ...As> struct any   : _retail::any<As..., any<>> {};
template <typename ...As> using  any_t = compose_s<unit_t, any<As...>>;
///\
Matches any `T` that inherits from `any_t<As...>`. \

template <typename T, typename ...As>
concept any_p = _std::derived_from<based_t<T>, any_t<As...>>;

template <typename ...Ts>
concept any_q = (... and any_p<Ts>);

template <typename ...Ts>
concept not_any_q = not (... or any_p<Ts>);


////////////////////////////////////////////////////////////////////////////////
///\
The base-type for this module. \

using base_t = any_t<>;


////////////////////////////////////////////////////////////////////////////////
///\
Combines `defer` and `refer` to define a proxy of `U`, sandwiching the decorators `...As`. \

template <typename U, typename ...As>
struct confer: compose<refer<U>, As..., defer<U>> {};


////////////////////////////////////////////////////////////////////////////////
///\
Combines `define` and `refine` to define `T`, sandwiching the decorators `...As`. \

template <typename T, typename ...As>
struct confine//: compose<refine<T>, As..., define<T>> {};
{
	using subkind = compose<refine<T>, As..., define<T>>;

	template <typename S>
	using subtype = compose_s<S, subkind>;

	using type = T;
	
};
template <typename T, typename ...As>
using confine_t = typename confine<T, As...>::template subtype<base_t>;

///\
Creates the `confine`d _decorator_ with `...As`. \

template <typename ...As>
struct confined
{
	template <typename T>
	using heterokind = confine<T, As...>;

	template <typename S>
	class subtype: public compose_s<S, heterokind<subtype<S>>>
	{
		using S_ = compose_s<S, heterokind<subtype<S>>>;
	
	public:
		using S_::S_;

	};
	using type = subtype<base_t>;
};
template <typename ...As>
using confined_t = typename confined<As...>::type;


////////////////////////////////////////////////////////////////////////////////
///\
Creates a _decorator_ that proxies `U`, with `subtype` extending `any<As...>`. \

template <typename U, typename ...As>
struct label
{
	template <typename T>
	using heterokind = compose<confine<T, confer<U>>, any<As>...>;

	template <typename S>
	class subtype: public compose_s<S, heterokind<subtype<S>>>
	{
		using S_ = compose_s<S, heterokind<subtype<S>>>;
	
	public:
		using S_::S_;

	};
	using type = subtype<base_t>;
};
template <typename U, typename ...As>
using label_t = typename label<U, As...>::type;
///<\
Resolves `label<U, As...>::type`. \


////////////////////////////////////////////////////////////////////////////////
///\
Creates a _decorator_ that proxies `U` with `...As`. \

template <typename U, typename ...As> using lift   = confined  <confer<U, As...>>;
template <typename U, typename ...As> using lift_t = confined_t<confer<U, As...>>;
///<\
Resolves `lift<U, As...>::type`. \

template <typename U> XTAL_FN2 lift_f(U &&u) XTAL_0EX {return lift_t<U>(XTAL_REF_(u));}
///<\
\returns a `lift`ed proxy of `u`. \


////////////////////////////////////////////////////////////////////////////////
///\
Defines `type` by `W` if `any_p<W>`, otherwise `lift_t<W>`. \

template <typename ...Ws> struct let;
template <typename    W > struct let<W> {using type =     lift_t<W>;};
template <any_p       W > struct let<W> {using type =            W ;};
template <              > struct let<>  {using type = confined_t< >;};
template <typename ...Ws> using  let_t = typename let<Ws...>::type;
///<\
Resolves `let<W>::type`. \

template <typename W> XTAL_FN2 let_f(W &&w) XTAL_0EX {return lift_t<W>(XTAL_REF_(w));}
template <any_p    W> XTAL_FN2 let_f(W &&w) XTAL_0EX {return          (XTAL_REF_(w));}
///<\
\returns `w` if `any_p<decltype(w)>`, otherwise proxies `w` using `lift_t`. \


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
