#ifdef __INTELLISENSE__// stub...
#include "../any.hpp"
using namespace xtal;
namespace _retail
{	template <typename ...As> struct any {template <typename S> class subtype {};};
}
#endif


//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//\
This *internal* header creates higher-level decorators based on `[dr]efine` and/or `[dr]efer`, \
and is intended to be `#include`d within a namespace in which these decorators are provided \
(see `xtal/processor/any.hpp` for example). \

using namespace common;


////////////////////////////////////////////////////////////////////////////////

///<\
Defines a _decorator_ tagged with the inheritance chain `...As`. \

template <typename ...As>
struct any: _retail::any<As..., any<>>
{
};
template <typename ...As>
using any_t = typename any<As...>::template subtype<unit_t>;
///<\
Defines `any` class, inheriting from the base `unit_t`. \

template <typename T, typename ...As>
concept any_q = xtal::if_q<any_t<As...>, T>;
///<\
Identifies `any` class `T`. \


template <template <typename...> typename ...As_>
using any_of_t = any_t<xtal::of_t<As_>...>;
///<\
Uses the supplied templates `As_` to tag `any` class. \

template <template <typename...> typename A_, typename ...Ts>
concept any_of_q = xtal::if_q<any_of_t<A_>, Ts...>;
///<\
Identifies `any` class tagged with the given template. \


////////////////////////////////////////////////////////////////////////////////

template <typename U> struct defer;
///<\
Decorates `subtype` with the core implementation to proxy `U`, assuming the `supertype` is `define`d. \
NOTE: Implemented by the target. \

template <typename U> struct refer;
///<\
Decorates `subtype` with the default implementation to proxy `U`. \
NOTE: Implemented by the target. \


///\
Combines `defer` and `refer` to define a proxy of `U`, sandwiching the decorators `...As`. \

template <typename U, typename ...As>
struct confer
:	compose<refer<U>, As..., defer<U>>
{};


////////////////////////////////////////////////////////////////////////////////

template <typename T> struct define;
///<\
Decorates `subtype` with the core implementation of `T`, \
using the curiously recurring template pattern (CRTP). \
\
NOTE: Implemented by the target. \

template <typename T> struct refine;
///<\
Decorates `subtype` with the default implementation of `T`, \
using the curiously recurring template pattern (CRTP). \
\
NOTE: Implemented by the target. \


///\
Combines `define` and `refine` to define `T`, sandwiching the decorators `...As`. \

template <typename T, typename ...As>
struct confine
:	compose<refine<T>, As..., define<T>>
{
};
template <typename T, typename ...As>
using confine_t = compose_s<any_t<>, confine<T, As...>>;
///<\
Defines the `confine`d class `T` with decorators `...As`, \
inheriting from the base `any_t<>`. \


///\
Creates the `confine`d _decorator_ with `...As`. \

template <typename ...As>
struct confined
{
	template <typename T>
	using homotype = confine<T, As...>;

	template <any_q S>
	class subtype: public compose_s<S, homotype<subtype<S>>>
	{
		using co = compose_s<S, homotype<subtype<S>>>;
	public:
		using co::co;

	};
};
template <typename ...As>
using confined_t = compose_s<any_t<>, confined<As...>>;
///<\
Creates the `confine`d _class_ decorated by `...As`, inheriting from the base `any_t<>`. \


////////////////////////////////////////////////////////////////////////////////
///\
Creates a _decorator_ that proxies `U` with `...As`. \

template <typename U, typename ...As> using lift   = confined  <confer<U, As...>>;
template <typename U, typename ...As> using lift_t = confined_t<confer<U, As...>>;
///<\
Resolves `lift<U>::type`. \

template <typename U> XTAL_FN2 lift_f(U &&u) XTAL_0RN_(lift_t<U>(XTAL_FWD_(U) (u)))
///<\
\returns a `lift`ed proxy of `u`. \


////////////////////////////////////////////////////////////////////////////////
///\
Defines `type` by `W`, or `lift_t<W>` if `any_q<W>`. \

template <typename W> struct let    {using type = lift_t<W>;};
template <any_q    W> struct let<W> {using type =        W ;};
template <typename W> using  let_t = typename let<W>::type;
///<\
Resolves `let<W>::type`. \

template <typename W> XTAL_FN2 let_f(W &&w) XTAL_0RN_(lift_t<W>(XTAL_FWD_(W) (w)))
template <any_q    W> XTAL_FN2 let_f(W &&w) XTAL_0RN_(         (XTAL_FWD_(W) (w)))
///<\
\returns `w` if `any_q<decltype(w)>`, otherwise proxies `w` using `lift_t`. \


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
