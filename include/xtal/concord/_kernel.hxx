#include "../_.hxx"

using namespace common;
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//\
This naked header is intended for inclusion within a `namespace` providing the decorators: \

template <class U> struct defer;///<   Proxies `U`.
template <class U> struct refer;///< Delegates `U`.

template <class T> struct define;///< Initializes `T`.
template <class T> struct refine;///<   Finalizes `T`.


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///\
Tags `subtype` with this namespace and the supplied types. \

template <typename ...As> struct any   : _retail::any<As...> {};
template <typename ...As> using  any_t = typename any<As...>::type;
///\
Matches any `T` that inherits from `any_t<As...>`. \

template <class T, typename ...As>
concept any_p = _detail::identity_p<any_t<As...>, T>;

template <class ...Ts>
concept any_q = of_p<any_t<>, Ts...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///\
Composes `Us...`, mapping each element with `defer` (or `any`, if incomplete). \

template <class ...Us> struct infer: compose<infer<Us>...> {};
template <vacant_q U > struct infer<U>:        any<U> {};
template <class    U > struct infer<U>:      defer<U> {};
template <class ...Us>  using infer_t = typename infer<Us...>::type;

///\
Combines `defer` and `refer` to define a proxy of `U`, sandwiching the decorators `...As`. \

template <class U, typename ...As>
struct confer: compose<refer<U>, As..., defer<U>> {};

///\
Combines `define` and `refine` to define `T`, sandwiching the decorators `...As`. \

template <class T, typename ...As>
struct confine//: compose<refine<T>, As..., define<T>> {};
{
	using subkind = compose<refine<T>, As..., define<T>>;

	template <class S>
	using subtype = compose_s<S, subkind>;
	using    type = T;
	
};
template <class T, typename ...As>
using confine_t = typename confine<T, As...>::template subtype<any_t<>>;

///\
Creates the `confine`d _decorator_ with `...As`. \

template <typename ...As>
struct confined
{
	template <class T>
	using homokind = confine<T, As...>;

	template <class S>
	class subtype: public compose_s<S, homokind<subtype<S>>>
	{
		using S_ = compose_s<S, homokind<subtype<S>>>;
	
	public:
		using S_::S_;

	};
	using type = subtype<any_t<>>;
	
};
template <typename ...As>
using confined_t = typename confined<As...>::type;


///\
Creates the `confine`d and `confer`red _decorator_ with `...As`. \

template <class U, typename ...As> using conferred   = confined<confer<U, As...>>;
template <class U, typename ...As> using conferred_t = typename conferred<U, As...>::type;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///\
Proxies and delegegates `U`, with `subtype` extending `any<As...>`. \

template <class U, typename ...As> using label   = conferred<U, any<As>...>;
template <class U, typename ...As> using label_t = typename label<U, As...>::type;

///\
Defines `type` by `W` if `any_q<W>`, otherwise `conferred_t<W>`. \

template <class ...Ws> struct let;
template <class    W > struct let<W> {using type = conferred_t<W>;};
template <any_q    W > struct let<W> {using type =             W ;};
template <class ...Ws>  using let_t = typename let<Ws...>::type;

template <class W> XTAL_FN2 let_f(W &&w) XTAL_0EX {return conferred_t<W>(XTAL_REF_(w));}
template <any_q W> XTAL_FN2 let_f(W &&w) XTAL_0EX {return               (XTAL_REF_(w));}
///<\
\returns `w` if `any_q<decltype(w)>`, otherwise proxies `w` using `conferred_t`. \


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
