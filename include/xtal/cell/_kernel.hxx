









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
concept any_p = bond::identity_p<any_t<As...>, T>;

template <class ...Ts>
//\
concept any_q = (...and any_p<Ts>);
concept any_q = of_p<any_t<>, Ts...>;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///\
Composes `Us...`, mapping each element with `defer` (or `any`, if incomplete). \

template <class        U> struct infer    : defer<U> {};
template <incomplete_q U> struct infer<U> :   any<U> {};
template <incomplete_q U, size_t N>
struct infer<U[N]>
:	bond::compose<any<U>, defer<unit_t[N]>>
{};

template <class ...Us>
struct reinfers
{
	template <class S>
	using subtype = S;

};
template <incomplete_q U, class ...Us>
struct reinfers<U, Us...>
:	reinfers<Us...>
{
};
template <complete_q U, class ...Us>
struct reinfers<U, Us...>
{
	using subkind = refer<U>;

	template <class S>
	class subtype: public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		
	};
};
template <class ...Us> using infers = bond::compose<infer<Us>...>;
template <class ...Us> using refers = bond::compose<refer<Us>...>;
template <class ...Us> using defers = bond::compose<defer<Us>...>;


////////////////////////////////////////////////////////////////////////////////

///\
Combines `defer` and `refer` to define a proxy of `U`, sandwiching the decorators `As...`. \

template <class U, typename ...As>
struct confer: bond::compose<refer<U>, As..., defer<U>> {};

///\
Combines `define` and `refine` to define `T`, sandwiching the decorators `As...`. \

template <class T, typename ...As>
struct confine//: bond::compose<refine<T>, As..., define<T>> {};
{
	using subkind = bond::compose<refine<T>, As..., define<T>>;

	template <class S>
	using subtype = bond::compose_s<S, subkind>;
	using    type = T;
	
};
template <class T, typename ...As>
using confine_t = typename confine<T, As...>::template subtype<any_t<>>;

///\
Creates the `confine`d _decorator_ with `As...`. \

template <typename ...As>
struct confined
{
	template <class T>
	using homokind = confine<T, As...>;

	template <class S>
	class subtype: public bond::compose_s<S, homokind<subtype<S>>>
	{
		using S_ = bond::compose_s<S, homokind<subtype<S>>>;
	
	public:
		using S_::S_;

	};
	using type = subtype<any_t<>>;
	
};
template <typename ...As>
using confined_t = typename confined<As...>::type;


///\
Creates a lifted form of `U`, _decorated_ with `As...`. \

template <class U, typename ...As> using conferred   = confined<confer<U, As...>>;
template <class U, typename ...As> using conferred_t = typename conferred<U, As...>::type;


///\
Creates a `contained` type from `infer<As>...`. \

template <class ...Us> using inferred   = confined<reinfers<Us...>, infers<Us...>>;
template <class ...Us> using inferred_t = typename inferred<Us...>::type;


///\
Creates a `std::tuple` analogue. \

template <class ...Us> using   tupled   = confined<infers<Us...>, any<class tupled__>>;
template <class ...Us> using   tupled_t = typename tupled<Us...>::type;
template <class ...Ts> concept tupled_q = any_p<class tupled__, Ts...>;


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
