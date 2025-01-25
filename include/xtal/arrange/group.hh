#pragma once
#include "./any.hh"
#include "./order.hh"





XTAL_ENV_(push)
namespace xtal::arrange
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class              ..._s>	struct   group;
template <class              ..._s>	using    group_t = typename group<_s...>::type;
template <class              ...Ts>	concept  group_q = bond::tag_p<group_t, Ts...>;
template <size_type N, class ...Ts>	concept  group_p = group_q<Ts...> and (...and (N == Ts::size()));
template <class  V=void>
XTAL_DEF_(return,inline,let)
group_f(auto &&...oo)
noexcept -> auto
{
	return _detail::initialize<group_t>::template via<V>(XTAL_REF_(oo)...);
}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `order` with point-wise addition or multiplication respectively \
when the given operator is `std::plus<void>` (default) or `std::multiplies<void>`. \

template <vector_q A>
struct group<A>
:	group<A, _std::plus<void>>
{
};
template <vector_q A>
struct group<A, _std::plus<void>>
{
	using _fix = bond::fixture<A>;
	
	template <class T>
	using endotype = typename order<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<group_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using  S_ = holotype<T>;
	
	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
	//	using S_::operator+=;
	//	using S_::operator-=;

		XTAL_DEF_(return,inline,let)  operator + (auto const &t)              const noexcept -> auto   {return S_::twin() +=   t ;}
		XTAL_DEF_(return,inline,let)  operator - (auto const &t)              const noexcept -> auto   {return S_::twin() -=   t ;}
		XTAL_DEF_(inline,let) operator +=(_std::initializer_list<U_data> t) noexcept -> auto & {return S_::self() += T(t);}
		XTAL_DEF_(inline,let) operator -=(_std::initializer_list<U_data> t) noexcept -> auto & {return S_::self() -= T(t);}
		XTAL_DEF_(inline,let) operator +=(                      T const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u += v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator -=(                      T const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u -= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator +=(subarray_q<N_data> auto const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u += v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator -=(subarray_q<N_data> auto const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u -= v;}>(XTAL_REF_(t));}

	};
	using type = derive_t<homotype>;

};
template <vector_q A>
struct group<A, _std::multiplies<void>>
{
	using _fix = bond::fixture<A>;
	
	template <class T>
	using endotype = typename order<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<group_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using  S_ = holotype<T>;
	
	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
	//	using S_::operator* ;
	//	using S_::operator/ ;
	//	using S_::operator% ;
		using S_::operator*=;
		using S_::operator/=;
		using S_::operator%=;

		XTAL_DEF_(return,inline,friend,let) operator * (T const &s, auto const &t) noexcept -> auto {return S_::template pointwise<[] (auto const &u, auto const &v) XTAL_0FN_(return) (u * v)>(s, t);}
		XTAL_DEF_(return,inline,friend,let) operator / (T const &s, auto const &t) noexcept -> auto {return S_::template pointwise<[] (auto const &u, auto const &v) XTAL_0FN_(return) (u / v)>(s, t);}
		XTAL_DEF_(return,inline,friend,let) operator % (T const &s, auto const &t) noexcept -> auto {return S_::template pointwise<[] (auto const &u, auto const &v) XTAL_0FN_(return) (u % v)>(s, t);}

		XTAL_DEF_(inline,let) operator *=(_std::initializer_list<U_data> t) noexcept -> auto & {return S_::self() *= T(t);}
		XTAL_DEF_(inline,let) operator /=(_std::initializer_list<U_data> t) noexcept -> auto & {return S_::self() /= T(t);}
		XTAL_DEF_(inline,let) operator %=(_std::initializer_list<U_data> t) noexcept -> auto & {return S_::self() %= T(t);}
		XTAL_DEF_(inline,let) operator *=(array_q<N_data>    auto const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u *= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator /=(array_q<N_data>    auto const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u /= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator %=(array_q<N_data>    auto const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u %= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator *=(                      T const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u *= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator /=(                      T const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u /= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator %=(                      T const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u %= v;}>(XTAL_REF_(t));}

	};
	using type = derive_t<homotype>;

};
static_assert(atomic_q<group_t<float[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
