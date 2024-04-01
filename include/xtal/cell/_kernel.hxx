









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
template <typename   ...As>	using       confined_t = typename confined<As...>::type;

template <typename   ...As>	concept   decorator_q = (...and requires {typename As::template subtype<confined_t<>>;});
template <typename   ...As>	concept undecorator_q =     not decorator_q<As...>;
///<\experimental\
Determines whether `...As` can be used to decorate within the current namespace. \


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///\
Combines `defer` and `refer` to lift `U`, sandwiching the decorators `As...`. \

template <class U, typename ...As>	struct  confer      : bond::compose<refer<U>, As..., defer<U>> {};
template <class U, typename ...As>	using   conferred   = confined<confer<U, As...>>;
template <class U, typename ...As>	using   conferred_t = typename conferred<U, As...>::type;


template <class   ...As>	concept   conferrable_q = complete_q<As...> and not decorator_q<As...>;
template <class   ...As>	concept unconferrable_q = not conferrable_q<As...>;


////////////////////////////////////////////////////////////////////////////////
///\
Lifts `A` with `defer`/`any` depending on whether `complete_q<U>`/`incomplete_q<U>`. \

///\experimental\
Will attempt to use `A` directly if it appears to be `decorator_q`.

template <class        A          > struct infer       : defer<A> {};
template <decorator_q A          > struct infer<A>    :       A  {};
template <incomplete_q A          > struct infer<A>    :   any<A> {};
template <incomplete_q A, size_t N> struct infer<A[N]> : bond::compose<any<A>, defer<unit_t[N]>> {};
template <                        > struct infer<void> : bond::compose<                        > {};

template <class   ...Us>	using infers = bond::compose<infer<Us>...>;///< Chained `infer`rals.
template <class   ...Us>	using defers = bond::compose<defer<Us>...>;///< Chained `defer`rals.

///\
Delegates to the first `conferrable_q` provided, if any. \

template <                   class ...Us> struct referred           : bond::compose<> {};
template <unconferrable_q U, class ...Us> struct referred<U, Us...> : referred<Us...> {};
template <  conferrable_q U, class ...Us> struct referred<U, Us...> : refer<U> {};


///\
Creates a `confined` type from `infers<As...>`. \

template <class   ...As>	using inferred   = confined<referred<As...>, infers<As...>>;
template <class   ...As>	using inferred_t = typename inferred<As...>::type;


////////////////////////////////////////////////////////////////////////////////
///\
Creates a unique tuple `inferred` from `...As`. \

template <class   ...As>	struct  packed   : inferred<As..., bond::tag<packed>> {};
template <class   ...As>	using   packed_t = typename packed<As...>::type;
template <class   ...As>	concept packed_q = any_p<class packed_a, As...>;


///\
Defines `type` by `T` if `any_q<T>`, otherwise `conferred_t<T>`. \

template <class    T > struct  let    {using type = conferred_t<T>;};
template <any_q    T > struct  let<T> {using type =             T ;};
template <class    T > using   let_t = typename let<T>::type;

template <class W> XTAL_TN2 let_f(W &&w) XTAL_0EX {return conferred_t<W>(XTAL_REF_(w));}
template <any_q W> XTAL_TN2 let_f(W &&w) XTAL_0EX {return               (XTAL_REF_(w));}
///<\
\returns `w` if `any_q<decltype(w)>`, otherwise proxies `w` using `conferred_t`. \


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
