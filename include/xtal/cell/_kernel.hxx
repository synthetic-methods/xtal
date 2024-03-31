









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
Associates the internal `subtype` both with the current namespace, \
the parent namespace, and with the decorators `As...` if provided. \

template <            typename ...As> struct  any   : bond::compose<_retail::any<As...>, bond::tag<any>> {};
template <class    T, typename ...As> using   any_s = bond::compose_s<T, any<As...>>;
template <class    T, typename ...As> concept any_p = bond::tag_p<any, T> and complete_q<typename T::template self_s<As...>>;
template <class ...Ts               > concept any_q = bond::tag_p<any, Ts...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///\
Combines `define` and `refine` to materialize the curiously recursive type `T`, \
sandwiching the decorators `As...`. \

template <class T, typename ...As>
struct confine
{
	using subkind = bond::compose<refine<T>, As..., define<T>>;

	template <class S>
	using subtype = bond::compose_s<S, subkind>;
	using    type = T;
	
};
template <class T, typename ...As>
using confine_t = typename confine<T, As...>::template subtype<any_s<unit_t>>;

///\
Creates the `confine`d _decorator_ with `As...`. \

template <typename ...As>
struct confined
{
	template <class T>
	using homokind = bond::compose<refine<T>, As..., define<T>>;

	template <class S>
	using subtype = bond::compose_s<S, bond::isokind<homokind>>;
	using    type = subtype<any_s<unit_t>>;
	
};
template <typename ...As>
using confined_t = typename confined<As...>::type;


///\
Creates the `define`d _decorator_ with `As...`. \

template <typename ...As>
struct defined
{
	template <class T>
	using homokind = bond::compose<As..., define<T>>;

	template <class S>
	using subtype = bond::compose_s<S, bond::isokind<homokind>>;
	using    type = subtype<any_s<unit_t>>;
	
};
template <typename ...As>
using defined_t = typename defined<As...>::type;


///\experimental\
Determines whether `...As` can be used to decorate within the current namespace. \

template <typename ...As>
concept unconfined_q = (...and requires {typename As::template subtype<defined_t<>>;});


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///\
Lifts `A` with either `defer` or `any`, \
depending respectively on whether `U` is `complete_q<U>` or `incomplete_q<U>`. \

///\experimental\
Will attempt to use `A` directly if it appears to be 

template <  class      U          > struct infer       : defer<U> {};
template <unconfined_q U          > struct infer<U>    :       U  {};
template <incomplete_q U          > struct infer<U>    :   any<U> {};
template <incomplete_q U, size_t N> struct infer<U[N]> : bond::compose<any<U>, defer<unit_t[N]>> {};

template <class ...Us> using infers = bond::compose<infer<Us>...>;///< Chained `infer`rals.
template <class ...Us> using defers = bond::compose<defer<Us>...>;///< Chained `defer`rals.


///\
Delegates to the first `complete_q` provided, if any. \

template <                class ...Us> struct referring           : bond::compose<> {};
template <unconfined_q U, class ...Us> struct referring<U, Us...> : referring<Us...> {};
template <incomplete_q U, class ...Us> struct referring<U, Us...> : referring<Us...> {};
template <  complete_q U, class ...Us> struct referring<U, Us...> : refer<U> {};


////////////////////////////////////////////////////////////////////////////////

///\
Combines `defer` and `refer` to lift `U`, \
sandwiching the decorators `As...`. \

template <class U, typename ...As>
struct confer: bond::compose<refer<U>, As..., defer<U>> {};

///\
Creates a lifted form of `U`, _decorated_ with `As...`. \

template <class U, typename ...As> using conferred   = confined<confer<U, As...>>;
template <class U, typename ...As> using conferred_t = typename conferred<U, As...>::type;


///\
Creates a `contained` type from `defer<As>...`. \

template <class ...Us> using deferred   = confined<referring<Us...>, defers<Us...>>;
template <class ...Us> using deferred_t = typename deferred<Us...>::type;


///\
Creates a `contained` type from `infer<As>...`. \

template <class ...Us> using inferred   = confined<referring<Us...>, infers<Us...>>;
template <class ...Us> using inferred_t = typename inferred<Us...>::type;


///\
Creates a `std::tuple` analogue. \

template <class ...Us> using   tupled   = confined<infers<Us...>, any<class tupled_a>>;
template <class ...Us> using   tupled_t = typename tupled<Us...>::type;
template <class ...Ts> concept tupled_q = any_p<class tupled_a, Ts...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///\
Defines `type` by `W` if `any_q<W>`, otherwise `conferred_t<W>`. \

template <class ...Ws> struct let;
template <class    W > struct let<W> {using type = conferred_t<W>;};
template <any_q    W > struct let<W> {using type =             W ;};
template <class ...Ws>  using let_t = typename let<Ws...>::type;

template <class W> XTAL_TN2 let_f(W &&w) XTAL_0EX {return conferred_t<W>(XTAL_FWD_(w));}
template <any_q W> XTAL_TN2 let_f(W &&w) XTAL_0EX {return               (XTAL_FWD_(w));}
///<\
\returns `w` if `any_q<decltype(w)>`, otherwise proxies `w` using `conferred_t`. \


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
