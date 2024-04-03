









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


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///\
Combines `defer` and `refer` to lift `U`, sandwiching the decorators `As...`. \

template <class U, typename ...As> struct  confer      : bond::compose<refer<U>, As..., defer<U>> {};
template <class U, typename ...As> using   conferred   = confined<confer<U, As...>>;
template <class U, typename ...As> using   conferred_t = typename conferred<U, As...>::type;


////////////////////////////////////////////////////////////////////////////////
///\
Applies `refer` to the outermost `head_t` iff `1 == arity()`. \

struct referree
{
	struct subkind
	{
		template <any_q S>
		using subtype = bond::compose_s<S, refer<typename S::template head_t<>>>;

	};
	template <any_q S>
	class subtype: public S
	{
		using S_ = S;
	
	public:
		using S_::S_;

	};
	template <any_q S> requires (1 == _std::tuple_size<S> {})
	class subtype<S>: public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;

	};
	
};
///\
Unless `A` is already a decorator, \
provides `defer<A>` or `any<A>` depending on whether `complete_q<A>`. \

template <class           A          > struct  infer      :             defer<A>                    {};
template <bond::compose_q A          > struct  infer<A   >:                   A                     {};
template <incomplete_q    A          > struct  infer<A   >:               any<A>                    {};
template <incomplete_q    A, size_t N> struct  infer<A[N]>: bond::compose<any<A>, defer<unit_t[N]>> {};
template <                           > struct  infer<void>: bond::compose<                        > {};

template <class ...As>
using infers = bond::compose<infer<As>...>; 

///\
Creates a `confined` `infers<As...>`, delegating to the outermost `complete_q<head_t<>>`. \

template <class   ...As>	using inferred   = confined<referree, infers<As...>>;
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
