#pragma once
#include "./any.hh"

#include "./operate.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <int   ...Ns>	using   seek_t = _std::     integer_sequence<int, Ns...>;
template <int      N >	using   seek_s = _std::make_integer_sequence<int, N    >;

template <class T    >	struct  seek                : logical_constant_t<0> {};
template <auto  ...Ns>	struct  seek<seek_t<Ns...>> : logical_constant_t<1> {};
template <class ...Ts>	concept seek_q = (...and seek<Ts>{}());


}///////////////////////////////////////////////////////////////////////////////

template <class ...Ts>	concept seek_q = _detail::seek_q<Ts...>;///<\brief Determines whether `Ts...` are `std::integer_sequence`s.
template <int   ...Ns>	using   seek_t = _detail::seek_t<Ns...>;///<\brief Defines `std::integer_sequence<int, Ns...>`.

/*!
\brief   Produces an         instance of `std::integer_sequence<int>` from the given sequence or lift of constants.
*/
XTAL_DEF_(let) seek_f = operate{
	[]<constant_q ...Ns> (       Ns... ) XTAL_0FN -> seek_t<(Ns{})...> {return {};}
,	[]<int        ...Ns> (seek_t<Ns...>) XTAL_0FN -> seek_t<(Ns  )...> {return {};}
};
/*!
\brief   Produces a reversed instance of `std::integer_sequence<int>` from the given sequence or lift of constants.
*/
XTAL_DEF_(let) seek_reverse_f = operate{
	[]<constant_q ...Ns> (       Ns... ) XTAL_0FN -> seek_t<(sizeof...(Ns) - 1 - Ns{})...> {return {};}
,	[]<int        ...Ns> (seek_t<Ns...>) XTAL_0FN -> seek_t<(sizeof...(Ns) - 1 - Ns  )...> {return {};}
};
template <int N>	                 struct XTAL_NYM_(seek)    {using type = decltype(seek_f        (_detail::seek_s<+N>{}));};
template <int N>	requires (N < 0) struct XTAL_NYM_(seek)<N> {using type = decltype(seek_reverse_f(_detail::seek_s<-N>{}));};
template <int N>	                 using  seek_s         = typename XTAL_NYM_(seek)<+N>::type;// Produces the         `std::integer_sequence<int>` from `0` to `N - 1`.
template <int N>	                 using  seek_reverse_s = typename XTAL_NYM_(seek)<-N>::type;// Produces the reverse `std::integer_sequence<int>` from `N - 1` to `0`.


////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Invokes the function `f` with each index `Ns...`.
*/
template <integral_q auto ...Ns>
XTAL_DEF_(inline,let)
seek_within_f(auto const &f)
noexcept -> void
{
	[&] <int ...I>(seek_t<I...>)
	XTAL_0FN_(do) (..., f(constant_t<I>{}))
		(seek_t<Ns...> {});
}

/*!
\brief   Invokes the function `f` with each index from `N_onset` to `N_onset + N_count`.
*/
template <int N_count=0, int N_onset=0>
XTAL_DEF_(inline,let)
seek_until_f(auto const &f)
noexcept -> void
{
	[&] <int ...I>(seek_t<I...>)
	XTAL_0FN_(do) (..., f(constant_t<I + N_onset>{}))
		(seek_s<N_count> {});
}


////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <         class ...Ts>  struct         seek_front           {using type = void;};
template <class T, class ...Ts>  struct         seek_front<T, Ts...> {using type = T   ;};
#endif
template <         class ...Ts>  using          seek_front_t = typename seek_front  <           Ts ...>::type; ///<\brief Produces the first  type within `Ts...`.
template <         auto  ...Ns>  auto constexpr seek_front_n =          seek_front_t<constant_t<Ns>...>{}();   ///<\brief Produces the first value within `Ns...`.

XTAL_DEF_(let)
seek_front_f = []<class ...Ts> (Ts &&...ts)
	XTAL_0FN_(to) (get<0>(_std::tuple<Ts...>{XTAL_REF_(ts)...}));
///<\brief Produces the first argument of `ts...`.

#ifndef XTAL_DOC
template <         class ...Ts>  struct         seek_back;
template <class T             >  struct         seek_back <T       >       {using type = T;};
template <class T, class ...Ts>  struct         seek_back <T, Ts...>  : seek_back <Ts...> {};
#endif
template <         class ...Ts>  using          seek_back_t = typename seek_back <Ts...>::type;            ///<\brief Produces the  last  type within `Ts...`.
template <         auto  ...Ns>  auto constexpr seek_back_n =          seek_back_t<constant_t<Ns>...>{}(); ///<\brief Produces the  last value within `Ns...`.

XTAL_DEF_(let)
seek_back_f = []<class ...Ts> (Ts &&...ts)
	XTAL_0FN_(to) (get<sizeof...(Ts) - 1>(_std::tuple<Ts...>{XTAL_REF_(ts)...}));
///<\brief Produces the  last argument of `ts...`.


////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <              class ...Ts>  struct         seek_constant;
template <              class ...Ts>  struct         seek_constant                    {using type = void;};
template <constant_q T, class ...Ts>  struct         seek_constant<T, Ts...>          {using type = T   ;};
template <class T,      class ...Ts>  struct         seek_constant<T, Ts...> :  seek_constant<Ts...>    {};
#endif
template <              class ...Ts>  using          seek_constant_t = typename seek_constant<Ts...>::type; ///<\brief Produces the `constant_q`  type within `Ts...`.
template <              class ...Ts>  auto constexpr seek_constant_n = seek_constant<Ts...>{}();            ///<\brief Produces the `constant_q` value within `Ts...`.
template <              class ...Ts>  concept        seek_constant_q = complete_q<seek_constant_t<Ts...>>;  ///<\brief Determines whether a `constant_q` exists within `Ts...`.


////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <auto F,                   auto ...Ns>                      struct         seek_order;
template <auto F, auto N0                     >                      struct         seek_order<F, N0           > : constant_t<N0> {};
template <auto F, auto N0, auto N1, auto ...Ns> requires (F(N0, N1)) struct         seek_order<F, N0, N1, Ns...> : seek_order<F, N0, Ns...> {};
template <auto F, auto N0, auto N1, auto ...Ns>                      struct         seek_order<F, N0, N1, Ns...> : seek_order<F, N1, Ns...> {};
#endif
template <auto F, auto ...Ns> auto constexpr seek_order_n = seek_order<F, Ns...>{}();
///<\brief   Produces the lattice-join w.r.t. the binary-function `F`.

template <auto  ...Ns>	auto constexpr seek_lower_n = seek_order_n<[] (auto i, auto j) XTAL_0FN_(to) (i < j), Ns...>;///<\brief Produces the lower-most element in `Ns...`.
template <auto  ...Ns>	auto constexpr seek_upper_n = seek_order_n<[] (auto i, auto j) XTAL_0FN_(to) (i > j), Ns...>;///<\brief Produces the upper-most element in `Ns...`.


////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <int  I, bool ...Ns>	struct         seek_truth;
template <int  I            >	struct         seek_truth<I              > : constant_t<   -1       > {};
template <int  I, bool ...Ns>	struct         seek_truth<I,  true, Ns...> : constant_t<    I       > {};
template <int  I, bool ...Ns>	struct         seek_truth<I, false, Ns...> : seek_truth<1 + I, Ns...> {};
#endif
template <        bool ...Ns>	auto constexpr seek_truth_n = seek_truth<0, Ns...>{}();
///<\brief Produces the index of `true` within `Ns...`.

static_assert(seek_truth_n<                   > == -1);
static_assert(seek_truth_n<               true> ==  0);
static_assert(seek_truth_n<       false,  true> ==  1);
static_assert(seek_truth_n<false, false,  true> ==  2);
static_assert(seek_truth_n<false, false, false> == -1);


////////////////////////////////////////////////////////////////////////////////

template <auto T, auto ...Ts>
XTAL_DEF_(let) seek_index_n = seek_truth_n<(T == Ts)...>;
///<\brief Produces the index of `T` within `Ts...`.

#ifndef XTAL_DOC
template <auto ...Ns> requires some_n<Ns...>
struct seek_index
{
	static unsigned constexpr N_upper = seek_upper_n<Ns...>;
	static unsigned constexpr N_lower = seek_lower_n<Ns...>;
	//\
	static unsigned constexpr N_limit = 1U + N_upper - N_lower;
	static unsigned constexpr N_limit = 1U << _std::bit_width(N_upper - N_lower);
	
	using  supertype = _std::array<int, N_limit>;
	class       type : public supertype
	{
	public:// CONSTRUCT
	//	using supertype::supertype;
		XTAL_NEW_(delete) (type, noexcept=default)
//		XTAL_NEW_(create) (type, noexcept=default)
		XTAL_NEW_(move)   (type, noexcept=default)
		XTAL_NEW_(copy)   (type, noexcept=default)

		XTAL_NEW_(implicit)
		type()
		noexcept
		:	supertype{[]<auto ...I> (bond::seek_t<I...>)
			XTAL_0FN_(to) (supertype{(seek_index_n<I + N_lower, Ns...>)...})
				(bond::seek_s<N_limit>{})}
		{};

	public:// OPERATE
		XTAL_FX4_(do) (template <integral_q I>
		XTAL_DEF_(return,inline,get)
		operator[](I i),
		{
			auto const j = _xtd::make_signed_f<int>(i) - N_lower;
			auto const k = 0 <= j and j < N_limit; assert(k);
			return supertype::operator[](k? j: 0);
		})
		
	};

};
#endif
template <auto ...Ns>
using    seek_index_t = typename seek_index<Ns...>::type;
///<\brief Produces a map from the values of `Ns...` to their respective indicies.


////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <auto ...Ns> requires some_n<Ns...>
struct seek_value
{
	//\
	static unsigned constexpr N_limit = sizeof...(Ns);
	static unsigned constexpr N_limit = 1U << _std::bit_width(sizeof...(Ns) - 1);
	
	using  supertype = _std::array<int, N_limit>;
	class       type : public supertype
	{
	public:// CONSTRUCT
		XTAL_NEW_(delete) (type, noexcept=default)
//		XTAL_NEW_(create) (type, noexcept=default)
		XTAL_NEW_(move)   (type, noexcept=default)
		XTAL_NEW_(copy)   (type, noexcept=default)

		XTAL_NEW_(implicit)
		type()
		noexcept
		:	supertype{[]<auto ...I> (bond::seek_t<I...>)
			XTAL_0FN_(to) (supertype{Ns...})
				(bond::seek_s<N_limit>{})}
		{};

	};

};
#endif

template <auto ...Ns>
using    seek_value_t = typename seek_value<Ns...>::type;
///<\brief Produces a map from the indicies of `Ns...` to their respective values.


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////

XTAL_ENV_(pop)
