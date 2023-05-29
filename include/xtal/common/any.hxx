//\
This *internal* header creates higher-level decorators based on `[dr]efine` and/or `[dr]efer`, \
and is intended to be `#include`d within a namespace in which these decorators are provided \
(see `xtal/processor/any.hpp` for example). \
\
The decorators themselves are spanned templates of the form \
`struct {template <class supertype> class subtype;}` \
(see `xtal/any/common::compose.hpp` for details). \

#ifdef __INTELLISENSE__ // stub...
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

////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct any: _retail::any<As..., any<>> {};
///<\
Defines the decorator for the target with decorators `...As`. \

template <typename ...As>
using any_t = typename any<As...>::template subtype<unit_t>;
///<\
Defines the class for the target with decorators `...As`, \
inheriting from the base `unit_t`. \

template <typename T, typename ...As>
concept any_q = if_q<any_t<As...>, T>;
///<\
Identifies any instance of the target with decorators `...As`. \

template <template <typename...> typename T_>
using any_of_t = any_t<xtal::of_t<T_>>;

template <template <typename...> typename T_, typename ...Ts>
concept any_of_q = if_q<any_of_t<T_>, Ts...>;

////////////////////////////////////////////////////////////////////////////////

template <typename U> struct defer;
///<\
Decorates `subtype` with the core implementation to proxy `U`, \
assuming the `supertype` is `define`d. \
\
NOTE: Implemented by the target. \

template <typename U> struct refer;
///<\
Decorates `subtype` with the default implementation to proxy `U`. \
\
NOTE: Implemented by the target. \

template <typename U, typename ...As>
struct confer
:	common::compose<refer<U>, As..., defer<U>>
{};
///<\
Combines `defer` and `refer` to define a proxy of `U`, sandwiching the decorators `...As`. \

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

template <typename T, typename ...As>
struct confine
:	common::compose<refine<T>, As..., define<T>>
{};
///<\
Combines `define` and `refine` to define `T`, sandwiching the decorators `...As`. \

template <typename T, typename ...As>
using confine_t = common::compose_s<any_t<>, confine<T, As...>>;
///<\
Defines the `confine`d class `T` with decorators `...As`, \
inheriting from the base `any_t<>`. \

template <typename ...As>
struct confined
{
	template <typename T>
	using homotype = confine<T, As...>;

	template <any_q S>
	class subtype: public common::compose_s<S, homotype<subtype<S>>>
	{
		using co = common::compose_s<S, homotype<subtype<S>>>;
	public:
		using co::co;

	};
};
///<\
Creates the `confine`d decorator from `...As`. \

template <typename ...As>
using confined_t = common::compose_s<any_t<>, confined<As...>>;
///<\
Creates the `confine`d class from decorators `...As`, \
inheriting from the base `any_t<>`. \

////////////////////////////////////////////////////////////////////////////////

template <typename U, typename ...As> using contrive   = confined  <confer<U, As...>>;
///<\
Creates the `confined` proxy decorator for `U` with `...As`. \

template <typename U, typename ...As> using contrive_t = confined_t<confer<U, As...>>;
///<\
Creates the `confined` proxy class for `U`,with decorators `...As`. \

template <typename ...As> using contrived   = contrive  <any_t<>, As...>;
///<\
Creates the nullary `contrive`d decorator from `...As`. \

template <typename ...As> using contrived_t = contrive_t<any_t<>, As...>;
///<\
Creates the nullary `contrive`d class from decorators `...As`. \

////////////////////////////////////////////////////////////////////////////////

template <typename W> struct let    {using type = contrive_t<W>;};
template <any_q    W> struct let<W> {using type =            W ;};
///<\
Defines `type` by `W` if `any_q<W>`, \
otherwise creates the `contrive`d proxy class for `W`. \

template <typename W> using  let_t = typename let<W>::type;
///<\
Resolves `let<W>::type`. \

template <typename W> XTAL_FN2 let_f(W &&w) XTAL_0EX {return contrive_t<W>(XTAL_FWD_(W) (w));}
template <any_q    W> XTAL_FN2 let_f(W &&w) XTAL_0EX {return               XTAL_FWD_(W) (w) ;}
///<\
\returns `w` if `any_q<decltype(w)>`, otherwise proxies `w` using `contrive_t`. \

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
