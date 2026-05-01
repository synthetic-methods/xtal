#pragma once
#include "./any.hh"

#include "./operate.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class T             >	XTAL_TYP_(new) seek_is                                         : logical_constant_t<0> {};
template <class U, auto  ...Ns>	XTAL_TYP_(new) seek_is    <_std::integer_sequence<U  , Ns...>> : logical_constant_t<1> {};
template <         class ...Ts>	XTAL_TYP_(ask) seek_is_q =             (...and seek_is<Ts>{}());///<\brief Determines whether `Ts...` are `std::integer_sequence`s.
template <         int   ...Ns>	XTAL_TYP_(let) seek_in_t = _std::integer_sequence<int, Ns...>  ;///<\brief Defines                        `std::integer_sequence<int, Ns...>`.


///\brief   Reproduces `std::integer_sequence<int, Ns...>` from left-to-right.
template <int   ...Ns>
XTAL_DEF_(return,inline,let)
forward_seek_f(seek_in_t<Ns...>)
noexcept -> auto
{
	return seek_in_t<(Ns  )...>{};
}
///\brief   Reproduces `std::integer_sequence<int, Ns...>` from right-to-left.
template <int   ...Ns>
XTAL_DEF_(return,inline,let)
reverse_seek_f(seek_in_t<Ns...>)
noexcept -> auto
{
	return seek_in_t<(sizeof...(Ns) - 1 - Ns  )...>{};
}


///\brief   Produces `std::integer_sequence<int, Ns...>` from left-to-right.
template <constant_q ...Ns>
XTAL_DEF_(return,inline,let)
forward_seek_in_f(Ns...)
noexcept -> auto
{
	return forward_seek_f(seek_in_t<(Ns{})...>{});
}
///\brief   Produces `std::integer_sequence<int, Ns...>` from right-to-left.
template <constant_q ...Ns>
XTAL_DEF_(return,inline,let)
reverse_seek_in_f(Ns...)
noexcept -> auto
{
	return reverse_seek_f(seek_in_t<(Ns{})...>{});
}


///\brief   Generates `std::make_integer_sequence<int, N_count>` from lowest-to-highest.
template <constant_q N_count>
XTAL_DEF_(return,inline,let)
forward_seek_to_f(N_count)
noexcept -> auto
{
	static_assert(0 <= N_count{});
	return forward_seek_f(_std::make_integer_sequence<int, N_count{}>{});
}
///\brief   Generates `std::make_integer_sequence<int, N_count>` from highest-to-lowest.
template <constant_q N_count>
XTAL_DEF_(return,inline,let)
reverse_seek_to_f(N_count)
noexcept -> auto
{
	static_assert(0 <= N_count{});
	return reverse_seek_f(_std::make_integer_sequence<int, N_count{}>{});
}
///\brief   Generates `std::make_integer_sequence<int, abs(N_counter)>` in the direction of `sgn(N_counter)`.
template <constant_q N_counter>
XTAL_DEF_(return,inline,let)
seek_to_f(N_counter)
noexcept -> auto 
{
	XTAL_IF0
	XTAL_0IF (N_counter{} == 0) {return         seek_in_t                         {} ;}
	XTAL_0IF (N_counter{}  > 0) {return forward_seek_to_f(constant_t<+N_counter{}>{});}
	XTAL_0IF (N_counter{} <  0) {return reverse_seek_to_f(constant_t<-N_counter{}>{});}
}

template <int N_counter> requires (0 <= N_counter) XTAL_TYP_(let) forward_seek_to_t = decltype(forward_seek_to_f(constant_t<N_counter>{}));
template <int N_counter> requires (0 <= N_counter) XTAL_TYP_(let) reverse_seek_to_t = decltype(reverse_seek_to_f(constant_t<N_counter>{}));
template <int N_counter>                           XTAL_TYP_(let)         seek_to_t = decltype(        seek_to_f(constant_t<N_counter>{}));


////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <         class ...Ts>  XTAL_TYP_(new) seek_front           {using type = void;};
template <class T, class ...Ts>  XTAL_TYP_(new) seek_front<T, Ts...> {using type = T   ;};
#endif
template <         class ...Ts>  XTAL_TYP_(let) seek_front_t = typename seek_front  <           Ts ...>::type; ///<\brief Produces the first  type within `Ts...`.
template <         auto  ...Ns>  XTAL_DEF_(let) seek_front_v =          seek_front_t<constant_t<Ns>...>{}();   ///<\brief Produces the first value within `Ns...`.

///\brief   Produces the first argument of `ts...`.
XTAL_DEF_(let)
seek_front_f = []<class ...Ts> (Ts &&...ts)
	XTAL_0FN_(to) (get<0>(_std::tuple<Ts...>{XTAL_REF_(ts)...}));

#ifndef XTAL_DOC
template <         class ...Ts>  XTAL_TYP_(new) seek_back;
template <class T             >  XTAL_TYP_(new) seek_back <T       >       {using type = T;};
template <class T, class ...Ts>  XTAL_TYP_(new) seek_back <T, Ts...>  : seek_back <Ts...> {};
#endif
template <         class ...Ts>  XTAL_TYP_(let) seek_back_t = typename seek_back <Ts...>::type;            ///<\brief Produces the  last  type within `Ts...`.
template <         auto  ...Ns>  XTAL_DEF_(let) seek_back_v =          seek_back_t<constant_t<Ns>...>{}(); ///<\brief Produces the  last value within `Ns...`.

///\brief   Produces the  last argument of `ts...`.
XTAL_DEF_(let)
seek_back_f = []<class ...Ts> (Ts &&...ts)
	XTAL_0FN_(to) (get<sizeof...(Ts) - 1>(_std::tuple<Ts...>{XTAL_REF_(ts)...}));


////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <auto F,                   auto ...Ns>                      XTAL_TYP_(new) seek_extremum;
template <auto F, auto N0                     >                      XTAL_TYP_(new) seek_extremum<F, N0           > : constant_t<N0> {};
template <auto F, auto N0, auto N1, auto ...Ns> requires (F(N0, N1)) XTAL_TYP_(new) seek_extremum<F, N0, N1, Ns...> : seek_extremum<F, N0, Ns...> {};
template <auto F, auto N0, auto N1, auto ...Ns>                      XTAL_TYP_(new) seek_extremum<F, N0, N1, Ns...> : seek_extremum<F, N1, Ns...> {};
#endif

///\brief   Produces the lattice-join w.r.t. the binary-function `F`.
template <auto F, auto ...Ns> XTAL_DEF_(let) seek_extremum_v = seek_extremum<F, Ns...>{}();
template <        auto ...Ns>	XTAL_DEF_(let) seek_minimum_v  = seek_extremum_v<[] (auto i, auto j) XTAL_0FN_(to) (i < j), Ns...>;///<\brief Produces the lower-most element in `Ns...`.
template <        auto ...Ns>	XTAL_DEF_(let) seek_maximum_v  = seek_extremum_v<[] (auto i, auto j) XTAL_0FN_(to) (i > j), Ns...>;///<\brief Produces the upper-most element in `Ns...`.


////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <              class ...Ts>  XTAL_TYP_(new) seek_constant;
template <              class ...Ts>  XTAL_TYP_(new) seek_constant                    {using type = void;};
template <constant_q T, class ...Ts>  XTAL_TYP_(new) seek_constant<T, Ts...>          {using type = T   ;};
template <class T,      class ...Ts>  XTAL_TYP_(new) seek_constant<T, Ts...> :  seek_constant<Ts...>    {};
#endif
template <              class ...Ts>  XTAL_TYP_(let) seek_constant_t = typename seek_constant<Ts...>::type; ///<\brief Produces the `constant_q`  type within `Ts...`.
template <              class ...Ts>  XTAL_DEF_(let) seek_constant_v = seek_constant_t<Ts...>{}();          ///<\brief Produces the `constant_q` value within `Ts...`.
template <              class ...Ts>  XTAL_TYP_(ask) seek_constant_q = complete_q<seek_constant_t<Ts...>>;  ///<\brief Determines whether a `constant_q` exists within `Ts...`.


////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <int  I, bool ...Ns>	XTAL_TYP_(new) seek_truth;
template <int  I            >	XTAL_TYP_(new) seek_truth<I              > : constant_t<   -1       > {};
template <int  I, bool ...Ns>	XTAL_TYP_(new) seek_truth<I,  true, Ns...> : constant_t<    I       > {};
template <int  I, bool ...Ns>	XTAL_TYP_(new) seek_truth<I, false, Ns...> : seek_truth<1 + I, Ns...> {};
#endif

///\brief   Produces the index of `true` within `Ns...`.
template <        bool ...Ns>	XTAL_DEF_(let) seek_truth_v = seek_truth<0, Ns...>{}();


////////////////////////////////////////////////////////////////////////////////

///\brief   Produces the index of `T` within `Ts...`.
template <auto T, auto ...Ts>
XTAL_DEF_(let) seek_index_v = seek_truth_v<(T == Ts)...>;

#ifndef XTAL_DOC
template <auto ...Ns> requires some_v<Ns...>
struct seek_index
{
	static unsigned constexpr N_upper = seek_maximum_v<Ns...>;
	static unsigned constexpr N_lower = seek_minimum_v<Ns...>;
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
		:	supertype{[]<auto ...I> (bond::seek_in_t<I...>)
			XTAL_0FN_(to) (supertype{(seek_index_v<I + N_lower, Ns...>)...})
				(bond::seek_to_t<N_limit>{})}
		{};

	public:// OPERATE
		template <integral_q I>
		XTAL_DEF_(return,inline,let)
		operator[](I i) const
		noexcept -> decltype(auto)
		{
			auto const j = _xtd::make_signed_f<int>(i) - N_lower;
			auto const k = 0 <= j and j < N_limit; assert(k);
			return supertype::operator[](k? j: 0);
		}
		
	};

};
#endif

///\brief   Produces a map from the values of `Ns...` to their respective indicies.
template <auto ...Ns>
using    seek_index_t = typename seek_index<Ns...>::type;


////////////////////////////////////////////////////////////////////////////////
#ifndef XTAL_DOC
template <auto ...Ns> requires some_v<Ns...>
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
		:	supertype{[]<auto ...I> (bond::seek_in_t<I...>)
			XTAL_0FN_(to) (supertype{Ns...})
				(bond::seek_to_t<N_limit>{})}
		{};

	};

};
#endif

///\brief   Produces a map from the indicies of `Ns...` to their respective values.
template <auto ...Ns>
using    seek_value_t = typename seek_value<Ns...>::type;


////////////////////////////////////////////////////////////////////////////////

///\brief   Invokes the function `f` with each index `Ns...`.
template <integral_q auto ...Ns>
XTAL_DEF_(inline,let)
seek_in_e(auto const &f)
noexcept -> void
{
	[&] <int ...I>(seek_in_t<I...>)
	XTAL_0FN_(do) (..., f(constant_t<I>{}))
		(seek_in_t<Ns...> {});
}

///\brief   Invokes the function `f` with each index from `N_onset` to `N_onset + N_count`.
template <int N_counter=0, int N_onset=0>
XTAL_DEF_(inline,let)
seek_to_e(auto const &f)
noexcept -> void
{
	[&] <int ...I>(seek_in_t<I...>)
	XTAL_0FN_(do) (..., f(constant_t<I + N_onset>{}))
		(seek_to_t<N_counter> {});
}



///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////

XTAL_ENV_(pop)
