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


XTAL_FX0_(alias) (template <auto f=invoke_n<>>
XTAL_DEF_(return,inline,let) order_f(auto &&...oo),
	_detail::build<order_t>::template static_factory<f>(XTAL_REF_(oo)...))


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
		using typename S_::T_data;
		using typename S_::U_data;
		using typename S_::V_data;

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


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
