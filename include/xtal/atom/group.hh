#pragma once
#include "./any.hh"
#include "./point.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Extends `point` with point-wise addition or multiplication respectively \
when the given operator is `std::plus<void>` (default) or `std::multiplies<void>`. \

template <        class ..._s>	struct   group;
template <        class ..._s>	using    group_t = typename group<_s...>::type;
template <        class ..._s>	concept  group_q = bond::array_tag_p<group_t, _s...> and same_n<sized_n<_s>...>;

XTAL_FX0_(alias) (template <auto f=invoke_n<>>
XTAL_DEF_(return,inline,let) group_f(auto &&...oo),
	_detail::build<group_t>::template static_factory<f>(XTAL_REF_(oo)...))


////////////////////////////////////////////////////////////////////////////////

template <template <class> class F, class U, auto N> struct group<F<U>   [N]> : group<F<void>, U   [N]> {};
template <template <class> class F, class U, auto N> struct group<F<U>(&)[N]> : group<F<void>, U(&)[N]> {};

template <class ..._s>
struct group<_std::plus<void>, _s...>
{
	template <class T>
	using endotype = typename point<_s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<group_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using I_ = typename S_::initializer_list;
	
	protected:
		using          S_::N_data;
		using typename S_::T_data;
		using typename S_::U_data;
		using typename S_::V_data;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
	//	using S_::operator+=;
	//	using S_::operator-=;

		XTAL_DEF_(return,inline,let)  operator + (auto const &t)      const noexcept -> auto {return S_::twin() += t;}
		XTAL_DEF_(return,inline,let)  operator - (auto const &t)      const noexcept -> auto {return S_::twin() -= t;}

		XTAL_DEF_(inline,let) operator +=(                      T const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u += v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator -=(                      T const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u -= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator +=(subarray_q<N_data> auto const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u += v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator -=(subarray_q<N_data> auto const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u -= v;}>(XTAL_REF_(t));}

		XTAL_DEF_(inline,let) operator +=(I_ t) noexcept -> auto & requires vector_q<_s...> {return S_::self() += T(t);}
		XTAL_DEF_(inline,let) operator -=(I_ t) noexcept -> auto & requires vector_q<_s...> {return S_::self() -= T(t);}

	};
	using type = derive_t<homotype>;

};
template <class ..._s>
struct group<_std::multiplies<void>, _s...>
{
	template <class T>
	using endotype = typename point<_s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<group_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using I_ = typename S_::initializer_list;

	protected:
		using          S_::N_data;
		using typename S_::T_data;
		using typename S_::U_data;
		using typename S_::V_data;

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

		XTAL_DEF_(inline,let) operator *=(array_q<N_data> auto const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u *= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator /=(array_q<N_data> auto const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u /= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator %=(array_q<N_data> auto const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u %= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator *=(                   T const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u *= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator /=(                   T const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u /= v;}>(XTAL_REF_(t));}
		XTAL_DEF_(inline,let) operator %=(                   T const &t) noexcept -> auto & {return S_::template pointwise<[] (auto &u, auto const &v) XTAL_0FN {u %= v;}>(XTAL_REF_(t));}

		XTAL_DEF_(inline,let) operator *=(I_ t) noexcept -> auto & requires vector_q<_s...> {return S_::self() *= T(t);}
		XTAL_DEF_(inline,let) operator /=(I_ t) noexcept -> auto & requires vector_q<_s...> {return S_::self() /= T(t);}
		XTAL_DEF_(inline,let) operator %=(I_ t) noexcept -> auto & requires vector_q<_s...> {return S_::self() %= T(t);}

	};
	using type = derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
