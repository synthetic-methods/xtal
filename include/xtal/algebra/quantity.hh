#pragma once
#include "./any.hh"
#include "../arrange/block.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP quantity;
template <class   ..._s>	XTAL_USE quantity_t = typename quantity<_s...>::type;
template <class   ..._s>	XTAL_REQ quantity_q = bond::any_tag_p<quantity_t, _s...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_LET quantity_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<quantity_t>::template via<V>(XTAL_REF_(oo)...);}

template <class T, class S=T>
XTAL_REQ lettuce_q = bond::heteropack_q<T> and bond::pack_size_n<T> == bond::pack_size_n<S>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `block` with point-wise comparison, \
and lifts all other operators. \

template <class U, size_type N, size_type ...Ns>
struct quantity<U[N][Ns]...> : quantity<quantity_t<U[N]>[Ns]...>
{
};
template <column_q A>
struct quantity<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using endotype = typename arrange::block<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<quantity_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  S_ = holotype<T>;
		using  I_ = typename S_::difference_type;

	protected:
		using          S_::N_data;
		using typename S_::U_data;

	public:
		using S_::S_;
		using S_::self;
		using S_::twin;
		using S_::size;
		using S_::let;

	public:// OPERATE
	//	Vector comparison (performed point-wise):
		XTAL_DEF_(return,inline)
		XTAL_LET operator <=> (homotype const &t)
		XTAL_0FX -> decltype(auto)
		{
			homotype const &s = *this;
			return\
				s <  t? _std::strong_ordering::      less:
			   s == t? _std::strong_ordering::     equal:
			   s  > t? _std::strong_ordering::   greater:
			           _std::strong_ordering::equivalent;
		}
		XTAL_DEF_(return,inline) XTAL_LET operator ==  (homotype const &t) XTAL_0FX -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) == get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline) XTAL_LET operator <=  (homotype const &t) XTAL_0FX -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) <= get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline) XTAL_LET operator >=  (homotype const &t) XTAL_0FX -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) >= get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline) XTAL_LET operator <   (homotype const &t) XTAL_0FX -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) <  get<I>(t)));} (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline) XTAL_LET operator >   (homotype const &t) XTAL_0FX -> bool {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN {return (...and (get<I>(self()) >  get<I>(t)));} (bond::seek_s<N_data> {});}

	//	Scalar assignment (performed point-wide):
		XTAL_DEF_(inline)        XTAL_LET operator <<= (size_type const &u) XTAL_0EX -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self()) <<= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator >>= (size_type const &u) XTAL_0EX -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self()) >>= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  ^= (U_data    const &u) XTAL_0EX -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self())  ^= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  |= (U_data    const &u) XTAL_0EX -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self())  |= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  &= (U_data    const &u) XTAL_0EX -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self())  &= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  %= (U_data    const &u) XTAL_0EX -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self())  %= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  *= (U_data    const &u) XTAL_0EX -> T  & {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {get<I>(self())  *= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_LET operator  /= (U_data    const &u) XTAL_0EX -> T  & {bond::seek_forward_f<N_data>([n = 1.0/u, this] (auto I) XTAL_0FN {get<I>(self())  *= n;}); return self();}

		XTAL_DEF_(return,inline,friend) XTAL_LET operator * (devolved_p<T> auto const &s, T const &t) XTAL_0EX {return t * s;}
		XTAL_DEF_(return,inline,friend) XTAL_LET operator + (devolved_p<T> auto const &s, T const &t) XTAL_0EX {return t + s;}

		template <auto f, size_t I=N_data - 1>
		XTAL_DEF_(return,inline)
		XTAL_LET pointless()
		XTAL_0FX
		{
			XTAL_IF0
			XTAL_0IF (0 == I) {return   get<I>(self())                        ;}
			XTAL_0IF (1 <= I) {return f(get<I>(self()), pointless<f, I - 1>());}
		}
		template <auto f>
		XTAL_DEF_(inline)
		XTAL_LET pointwise(auto const &t)
		XTAL_0EX -> T &
		{
			size_type constexpr N = bond::pack_size_n<decltype(t)>;
			static_assert(N <= N_data);

			auto &s = self();

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {(f(get<I>(s), get<I>(t)),...);}
			(bond::seek_s<N>{});
			
			return s;
		}
		template <auto f>
		XTAL_DEF_(return,inline)
		XTAL_LET pointwise(auto const &s, auto const &t)
		XTAL_0EX
		{
			size_type constexpr N = bond::pack_size_n<decltype(t)>;
			static_assert(N <= N_data);
			
			using F = XTAL_ALL_(twin());
			return [&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(F(f(get<I>(s), get<I>(t))...))
			(bond::seek_s<N>{});
		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(based_q<quantity_t<float[2]>>);

static_assert(not counted_q<quantity_t<        int[2]>>);
static_assert(not counted_q<quantity_t<counter_t<>[2]>>);
static_assert(not counted_q<quantity_t<  size_type[2]>>);

static_assert(fungible_q<_std::span<float, 2>, quantity_t<float(&)[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
