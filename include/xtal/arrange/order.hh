#pragma once
#include "./any.hh"
#include "./block.hh"





XTAL_ENV_(push)
namespace xtal::arrange
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	struct   order;
template <class   ..._s>	using    order_t = typename order<_s...>::type;
template <class   ..._s>	concept  order_q = bond::tag_p<order_t, _s...>;
template <class  V=void>
XTAL_DEF_(short)
XTAL_LET order_f(auto &&...oo)
noexcept -> auto
{
	return _detail::initialize<order_t>::template via<V>(XTAL_REF_(oo)...);
}

template <class T, class S=T>
concept  lettuce_q = bond::heteropack_q<T> and bond::pack_size_n<T> == bond::pack_size_n<S>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `block` with point-wise comparison, \
and lifts all other operators. \

template <class U, unsigned N, unsigned ...Ns> requires (1 <= sizeof...(Ns)) struct order<U   [N][Ns]...> : order<order_t<U[N]>   [Ns]...> {};
template <class U, unsigned N, unsigned ...Ns> requires (1 <= sizeof...(Ns)) struct order<U(&)[N][Ns]...> : order<order_t<U[N]>(&)[Ns]...> {};

template <vector_q A>
struct order<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using endotype = typename arrange::block<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<order_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using  S_ = holotype<T>;
		using  I_ = typename S_::difference_type;

	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:
		using S_::S_;

	public:// OPERATE
		using S_::self;
		using S_::twin;
		using S_::size;

	//	Vector comparison (performed point-wise):
		XTAL_DEF_(short)
		XTAL_LET operator <=> (homotype const &t) const
		noexcept -> decltype(auto)
		{
			homotype const &s = *this;
			return\
				s <  t? _std::strong_ordering::      less:
			   s == t? _std::strong_ordering::     equal:
			   s  > t? _std::strong_ordering::   greater:
			           _std::strong_ordering::equivalent;
		}
		XTAL_DEF_(short) XTAL_LET operator ==  (homotype const &t) const noexcept -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) == get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(short) XTAL_LET operator <=  (homotype const &t) const noexcept -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) <= get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(short) XTAL_LET operator >=  (homotype const &t) const noexcept -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) >= get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(short) XTAL_LET operator <   (homotype const &t) const noexcept -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) <  get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(short) XTAL_LET operator >   (homotype const &t) const noexcept -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) >  get<I>(t)));} (bond::seek_s<N_data> {});}

	//	Scalar assignment (performed point-wide):
		XTAL_DEF_(inline)        XTAL_LET operator <<= (size_type const &u) noexcept -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self()) <<= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator >>= (size_type const &u) noexcept -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self()) >>= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  ^= (U_data    const &u) noexcept -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self())  ^= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  |= (U_data    const &u) noexcept -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self())  |= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  &= (U_data    const &u) noexcept -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self())  &= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  %= (U_data    const &u) noexcept -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self())  %= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  *= (U_data    const &u) noexcept -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self())  *= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  /= (U_data    const &u) noexcept -> T  & {bond::seek_forward_f<N_data>([n = one/u, this] (auto I) XTAL_0FN {get<I>(self())  *= n;}); return self();}

		XTAL_DEF_(short,friend)
		XTAL_LET operator * (auto const &s, T const &t)
		noexcept -> auto
		requires (dissolve_r<decltype(s)> < dissolve_r<T>)
		{
			return t * s;
		}
		XTAL_DEF_(short,friend)
		XTAL_LET operator + (auto const &s, T const &t)
		noexcept -> auto
		requires (dissolve_r<decltype(s)> < dissolve_r<T>)
		{
			return t + s;
		}

//		XTAL_DEF_(short,friend)
//		XTAL_LET operator - (T const &s)
//		noexcept -> auto
//		{
//			return pointwise<[] (auto const &x) XTAL_0FN_(-x)>(s);
//		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(atomic_q<order_t<float[2]>>);

static_assert(not counted_q<order_t<        int[2]>>);
static_assert(not counted_q<order_t<counter_t<>[2]>>);
static_assert(not counted_q<order_t<  size_type[2]>>);

static_assert(fungible_q<_std::span<float, 2>, order_t<float(&)[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
