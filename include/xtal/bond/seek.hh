#pragma once
#include "./any.hh"

#include "./tag.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <int        ...Ns>	using    seek_t = _std::     integer_sequence<int, Ns...>;
template <int           N >	using    seek_s = _std::make_integer_sequence<int, N    >;

template <class T         >	struct   seek                : logical_constant_t<0> {};
template <auto       ...Ns>	struct   seek<seek_t<Ns...>> : logical_constant_t<1> {};
template <class      ...Ts>	concept  seek_q = (...and seek<Ts>{}());


}///////////////////////////////////////////////////////////////////////////////

template <class      ...Ts>	                 concept       seek_q = _detail::seek_q<Ts...>;
template <int        ...Ns>	                 using         seek_t = _detail::seek_t<Ns...>;
template <constant_q ...Ns>	XTAL_DEF_(return,inline,let)           seek_f(       Ns... ) noexcept -> seek_t<(                      Ns{})...> {return {};}
template <int        ...Ns>	XTAL_DEF_(return,inline,let)           seek_f(seek_t<Ns...>) noexcept -> seek_t<(                      Ns  )...> {return {};}
template <constant_q ...Ns>	XTAL_DEF_(return,inline,let)       antiseek_f(       Ns... ) noexcept -> seek_t<(sizeof...(Ns) - one - Ns{})...> {return {};}
template <int        ...Ns>	XTAL_DEF_(return,inline,let)       antiseek_f(seek_t<Ns...>) noexcept -> seek_t<(sizeof...(Ns) - one - Ns  )...> {return {};}

template <int           N >	                 struct   superseek    {using type = decltype(    seek_f(_detail::seek_s<+N>{}));};
template <int           N >	requires (N < 0) struct   superseek<N> {using type = decltype(antiseek_f(_detail::seek_s<-N>{}));};
template <int           N >	                 using    superseek_t = typename superseek<N>::type;
template <int           N >	                 using         seek_s = superseek_t<+N>;
template <int           N >	                 using     antiseek_s = superseek_t<-N>;


////////////////////////////////////////////////////////////////////////////////

///\
Invokes the function `f` with each index `Ns...`. \

template <integral_q auto ...Ns>
XTAL_DEF_(return,inline,let)
seek_f(applicable_p<valued_u<decltype(Ns)...>> auto const &f)
noexcept -> decltype(auto)
{
	return [&] <int ...I>(seek_t<I...>)
		XTAL_0FN_(to) (..., f(constant_t<I>{})) (seek_t<Ns...> {});
}

template <int N_count=0, int N_onset=0>
XTAL_DEF_(inline,let)
seek_forward_f(auto const &f)
noexcept -> decltype(auto)
{
	return [&] <int ...I>(seek_t<I...>)
		XTAL_0FN_(to) (..., f(constant_t<N_onset + I>{})) (seek_s<N_count> {});
}
template <int N_count=0, int N_onset=0>
XTAL_DEF_(inline,let)
seek_backward_f(auto const &f)
noexcept -> decltype(auto)
{
	return [&] <int ...I>(seek_t<I...>)
		XTAL_0FN_(to) (..., f(constant_t<N_onset + I>{})) (antiseek_s<N_count> {});
}


////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(inline,let)
seek_front_f(auto &&o, auto &&...oo)
noexcept -> decltype(auto)
{
	return XTAL_REF_(o);
}
template <         class ...Ts>  struct         seek_front;
template <class T, class ...Ts>  struct         seek_front<T, Ts...>       {using type = T;};
template <         class ...Ts>  using          seek_front_t = typename seek_front  <           Ts ...>::type;
template <         auto  ...Ns>  auto constexpr seek_front_n =          seek_front_t<constant_t<Ns>...>{}();

XTAL_DEF_(inline,let)
seek_back_f(auto &&o, auto &&...oo)
noexcept -> decltype(auto)
{
	XTAL_IF0
	XTAL_0IF (0 == sizeof...(oo)) {return XTAL_REF_(o);}
	XTAL_0IF (1 <= sizeof...(oo)) {return seek_back_f(XTAL_REF_(oo)...);}
}
template <         class ...Ts>  struct   seek_back;
template <class T             >  struct   seek_back <T       >       {using type = T;};
template <class T, class ...Ts>  struct   seek_back <T, Ts...>  : seek_back <Ts...> {};
template <         class ...Ts>  using    seek_back_t  = typename seek_back <Ts...>::type;


////////////////////////////////////////////////////////////////////////////////

template <              class ...Ts>  struct         seek_constant                    {using type = void;};
template <constant_q T, class ...Ts>  struct         seek_constant<T, Ts...>          {using type = T   ;};
template <class T,      class ...Ts>  struct         seek_constant<T, Ts...> :  seek_constant<Ts...>    {};
template <              class ...Ts>  using          seek_constant_t = typename seek_constant<Ts...>::type;
template <              class ...Ts>  concept        seek_constant_q = complete_q<seek_constant_t<Ts...>>;
template <              class ...Ts>  auto constexpr seek_constant_n =          seek_constant<Ts...>{}();


////////////////////////////////////////////////////////////////////////////////

template <auto F,                   auto ...Ns>                      struct         seek_order;
template <auto F, auto N0                     >                      struct         seek_order<F, N0           > : constant_t<N0> {};
template <auto F, auto N0, auto N1, auto ...Ns> requires (F(N0, N1)) struct         seek_order<F, N0, N1, Ns...> : seek_order<F, N0, Ns...> {};
template <auto F, auto N0, auto N1, auto ...Ns>                      struct         seek_order<F, N0, N1, Ns...> : seek_order<F, N1, Ns...> {};
template <auto F,                   auto ...Ns>                      auto constexpr seek_order_n = seek_order<F, Ns...>{}();


////////////////////////////////////////////////////////////////////////////////

template <auto  ...Ns>	auto constexpr seek_upper_n = seek_order_n<[] (auto i, auto j) XTAL_0FN_(to) (i > j), Ns...>;
template <auto  ...Ns>	auto constexpr seek_lower_n = seek_order_n<[] (auto i, auto j) XTAL_0FN_(to) (i < j), Ns...>;


////////////////////////////////////////////////////////////////////////////////

template <int  I, bool ...Ns>	struct         seek_truth;
template <int  I            >	struct         seek_truth<I              > : constant_t<   -1       > {};
template <int  I, bool ...Ns>	struct         seek_truth<I,  true, Ns...> : constant_t<    I       > {};
template <int  I, bool ...Ns>	struct         seek_truth<I, false, Ns...> : seek_truth<1 + I, Ns...> {};
template <        bool ...Ns>	auto constexpr seek_truth_n = seek_truth<0, Ns...>{}();

static_assert(seek_truth_n<                   > == -1);
static_assert(seek_truth_n<               true> ==  0);
static_assert(seek_truth_n<       false,  true> ==  1);
static_assert(seek_truth_n<false, false,  true> ==  2);
static_assert(seek_truth_n<false, false, false> == -1);


////////////////////////////////////////////////////////////////////////////////

template <auto A, auto ...As>
auto constexpr seek_index_n = seek_truth_n<(A == As)...>;

template <auto ...Ns> requires (1 <= sizeof...(Ns))
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
		using S_ = supertype;

	public:// CONSTRUCT
	//	using S_::S_;

		XTAL_NEW_(delete) (type, noexcept = default)
//		XTAL_NEW_(create) (type, noexcept = default)
		XTAL_NEW_(move)   (type, noexcept = default)
		XTAL_NEW_(copy)   (type, noexcept = default)
	//	XTAL_NEW_(cast)   (type, noexcept)

		XTAL_NEW_(implicit)
		type()
		noexcept
		:	S_{[]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(to) (supertype{(seek_index_n<I + N_lower, Ns...>)...})
			(bond::seek_s<N_limit>{})}
		{
		};

	public:// OPERATE
		XTAL_FX4_(to) (template <integral_q I> XTAL_DEF_(return,inline,get) element(I i),
			S_::operator[](static_cast<int>(static_cast<_std::make_signed_t<I>>(i)) - N_lower))

		XTAL_FX4_(to) (template <integral_q I> XTAL_DEF_(return,inline,get) operator[](I i), element(i))
	//	XTAL_FX4_(to) (template <integral_q I> XTAL_DEF_(return,inline,get) operator()(I i), element(i))
		
	};

};
template <auto ...Ns>
using    seek_index_t = typename seek_index<Ns...>::type;


////////////////////////////////////////////////////////////////////////////////

template <auto ...Ns> requires (1 <= sizeof...(Ns))
struct seek_value
{
	//\
	static unsigned constexpr N_limit = sizeof...(Ns);
	static unsigned constexpr N_limit = 1U << _std::bit_width(sizeof...(Ns) - 1);
	
	using  supertype = _std::array<int, N_limit>;
	class       type : public supertype
	{
		using S_ = supertype;

	public:// CONSTRUCT
	//	using S_::S_;

		XTAL_NEW_(delete) (type, noexcept = default)
//		XTAL_NEW_(create) (type, noexcept = default)
		XTAL_NEW_(move)   (type, noexcept = default)
		XTAL_NEW_(copy)   (type, noexcept = default)
	//	XTAL_NEW_(cast)   (type, noexcept)

		XTAL_NEW_(implicit)
		type()
		noexcept
		:	S_{[]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(to) (supertype{Ns...})
			(bond::seek_s<N_limit>{})}
		{
		};

	};

};
template <auto ...Ns>
using    seek_value_t = typename seek_value<Ns...>::type;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////

XTAL_ENV_(pop)
