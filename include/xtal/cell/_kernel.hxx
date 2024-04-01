









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


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///\
Combines `defer` and `refer` to lift `U`, sandwiching the decorators `As...`. \

template <class U, typename ...As>	struct  confer      : bond::compose<refer<U>, As..., defer<U>> {};
template <class U, typename ...As>	using   conferred   = confined<confer<U, As...>>;
template <class U, typename ...As>	using   conferred_t = typename conferred<U, As...>::type;


////////////////////////////////////////////////////////////////////////////////
///\
Lifts `A` with `defer`/`any` depending on whether `complete_q<U>`/`incomplete_q<U>`. \

///\note\
Will use `A` directly if it appears to be decorator w.r.t. `infers<As...>`.

template <                          class ...As> struct infers              : bond::compose<                                       > {};
template <                          class ...As> struct infers<void, As...> : bond::compose<                          infers<As...>> {};
template <incomplete_q A, size_t N, class ...As> struct infers<A[N], As...> : bond::compose<any<A>, defer<unit_t[N]>, infers<As...>> {};
template <incomplete_q A          , class ...As> struct infers<A   , As...> : bond::compose<any<A>,                   infers<As...>> {};
template <class        A          , class ...As> struct infers<A   , As...> : bond::compose<        defer<A>,         infers<As...>> {};
template <class        A          , class ...As>
XTAL_REQ_(typename A::template subtype<defined_t<infers<As...>>>)
struct infers<A, As...>
:	bond::compose<A, infers<As...>>
{};

///\
Creates a `confined` type from `infers<As...>`, delegating to the outermost `complete_q<head_t<>>`. \

template <typename ...As>
struct inferrer
{
	using subkind = infers<As...>;

	template <class S>
	class subtype: public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;

	};
	template <class S>
	using paratype = typename bond::compose_s<S, subkind>::template head_t<>;

	template <class S> requires complete_q<paratype<S>>
	class subtype<S>: public bond::compose_s<S, subkind, refer<paratype<S>>>
	{
		using S_ = bond::compose_s<S, subkind, refer<paratype<S>>>;
	
	public:
		using S_::S_;

	};
	
};
template <class   ...As>	using inferred   = confined<inferrer<As...>>;
template <class   ...As>	using inferred_t = typename inferred<As...>::type;


////////////////////////////////////////////////////////////////////////////////
///\
Creates a unique tuple `inferred` from `...As`. \

template <class   ...As>	struct  packed   : inferred<As..., bond::tag<packed>> {};
template <class   ...As>	using   packed_t = typename packed<As...>::type;
template <class   ...As>	concept packed_q = any_p<class packed_a, As...>;


///\
Defines `type` by `T` if `any_q<T>`, otherwise `conferred_t<T>`. \

template <class      T >	struct  let        {using type = conferred_t<T>;};
template <any_q      T >	struct  let<T>     {using type =             T ;};
template <class      T >	using   let_t    = typename let<T>::type;

template <class W> XTAL_TN2 let_f(W &&w) XTAL_0EX {return conferred_t<W>(XTAL_REF_(w));}
template <any_q W> XTAL_TN2 let_f(W &&w) XTAL_0EX {return               (XTAL_REF_(w));}
///<\
\returns `w` if `any_q<decltype(w)>`, otherwise proxies `w` using `conferred_t`. \


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
