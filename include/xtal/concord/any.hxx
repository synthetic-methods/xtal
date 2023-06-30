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
	{
	};
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
template <typename T> struct refine;///<   Finalizes `T`, e.g. applying `ranges::view_interface`.

template <typename U> struct defer;///<   Proxies an instance of `U`, e.g. defining constructors/accessors.
template <typename U> struct refer;///< Delegates to the proxied `U`, e.g. relaying operators/methods.

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
concept any_q = conjunct_q<any_p<Ts>...>;


///\
Tags `subtype` with this namespace and the supplied templates. \

template <template <typename...> typename ...As> using only   = any  <comport_t<As>...>;
template <template <typename...> typename ...As> using only_t = any_t<comport_t<As>...>;

///\
Matches any `T` that inherits from `only_t<As...>`. \

template <typename T, template <typename...> typename A>
concept only_p = _std::derived_from<based_t<T>, only_t<A>>;


////////////////////////////////////////////////////////////////////////////////
///\
Combines `defer` and `refer` to define a proxy of `U`, sandwiching the decorators `...As`. \

template <typename U, typename ...As>
struct confer: compose<refer<U>, As..., defer<U>> {};


////////////////////////////////////////////////////////////////////////////////
///\
Combines `define` and `refine` to define `T`, sandwiching the decorators `...As`. \

template <typename T, typename ...As>
struct confine: compose<refine<T>, As..., define<T>> {};

template <typename T, typename ...As>
using confine_t = compose_s<any_t<>, confine<T, As...>>;

///\
Creates the `confine`d _decorator_ with `...As`. \

template <typename ...As>
struct confined
{
	template <typename T>
	using homotype = confine<T, As...>;

	template <any_p S>
	class subtype: public compose_s<S, homotype<subtype<S>>>
	{
		using S_ = compose_s<S, homotype<subtype<S>>>;
	
	public:
		using S_::S_;

	};
};
template <         typename ...As> using confined_t = compose_s<any_t<>, confined<As...>>;
template <any_p S, typename ...As> using confined_s = compose_s<S,       confined<As...>>;


template <typename ...As>
using confound = compose<confined<>, any<As>...>;

template <         typename ...As> using confound_t = compose_s<any_t<>, confound<As...>>;
template <any_p S, typename ...As> using confound_s = compose_s<S,       confound<As...>>;


////////////////////////////////////////////////////////////////////////////////
///\
Creates a _decorator_ that proxies `U` with `...As`. \

template <typename U, typename ...As> using lift   = confined  <confer<U, As...>>;
template <typename U, typename ...As> using lift_t = confined_t<confer<U, As...>>;
///<\
Resolves `lift<U, As...>::type`. \

template <typename U> XTAL_FN2 lift_f(U &&u) XTAL_0EX {return lift_t<U>(XTAL_FWD_(U) (u));}
///<\
\returns a `lift`ed proxy of `u`. \


////////////////////////////////////////////////////////////////////////////////
///\
Defines `type` by `W` if `any_p<W>`, otherwise `lift_t<W>`. \

template <typename W> struct let    {using type = lift_t<W>;};
template <any_p    W> struct let<W> {using type =        W ;};
template <typename W> using  let_t = typename let<W>::type;
///<\
Resolves `let<W>::type`. \

template <typename W> XTAL_FN2 let_f(W &&w) XTAL_0EX {return lift_t<W>(XTAL_FWD_(W) (w));}
template <any_p    W> XTAL_FN2 let_f(W &&w) XTAL_0EX {return          (XTAL_FWD_(W) (w));}
///<\
\returns `w` if `any_p<decltype(w)>`, otherwise proxies `w` using `lift_t`. \


////////////////////////////////////////////////////////////////////////////////
///\
Creates a _decorator_ that proxies `U` with `...any<As>`. \

template <typename U, typename ...As> using label   = compose<lift<U>, any<As...>>;
template <typename U, typename ...As> using label_t = compose_s<unit_t, label<U, As...>>;
///<\
Resolves `label<U, As...>::type`. \


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
