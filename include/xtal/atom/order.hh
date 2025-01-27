#pragma once
#include "./any.hh"
#include "./point.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends `point` with comparison. \

template <        class ..._s>	struct   order;
template <        class ..._s>	using    order_t = typename order<_s...>::type;
template <        class ..._s>	concept  order_q = bond::array_tag_p<order_t, _s...> and same_n<sized_n<_s>...>;

template <class U, auto  N, auto  ..._s> struct   order<U   [N][_s]...> : order<order_t<U[_s]...>   [N]> {};
template <class U, auto  N, auto  ..._s> struct   order<U(&)[N][_s]...> : order<order_t<U[_s]...>(&)[N]> {};


template <auto f=null_type{}>
XTAL_DEF_(return,inline,let)
order_f(auto &&...oo)
noexcept -> auto
{
	return _detail::build<order_t>::template with<f>(XTAL_REF_(oo)...);
}


////////////////////////////////////////////////////////////////////////////////

template <class ..._s>
struct order
{
	template <class T>
	using endotype = typename atom::point<_s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<order_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

	protected:
		using          S_::N_data;
		using typename S_::U_data;
		using typename S_::V_data;
		using typename S_::W_data;

	public:
		using S_::S_;

	public:// OPERATE
		using S_::self;
		using S_::twin;
		using S_::size;

	//	Vector comparison (performed point-wise):
		XTAL_DEF_(return,inline,let)
		operator <=> (homotype const &t) const
		noexcept -> decltype(auto)
		{
			homotype const &s = *this;
			return\
				s <  t? _std::strong_ordering::      less:
			   s == t? _std::strong_ordering::     equal:
			   s  > t? _std::strong_ordering::   greater:
			           _std::strong_ordering::equivalent;
		}
		XTAL_DEF_(return,inline,let) operator == (homotype const &t) const noexcept -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) == get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline,let) operator <= (homotype const &t) const noexcept -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) <= get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline,let) operator >= (homotype const &t) const noexcept -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) >= get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline,let) operator <  (homotype const &t) const noexcept -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) <  get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline,let) operator >  (homotype const &t) const noexcept -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) >  get<I>(t)));} (bond::seek_s<N_data> {});}

	};
	using type = derive_t<homotype>;

};
static_assert(atomic_q<order_t<float[2]>>);

static_assert(not counted_q<order_t<        int[2]>>);
static_assert(not counted_q<order_t<counter_t<>[2]>>);
static_assert(not counted_q<order_t<  size_type[2]>>);

//static_assert(fungible_q<_std::span<float, 2>, order_t<float(&)[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
