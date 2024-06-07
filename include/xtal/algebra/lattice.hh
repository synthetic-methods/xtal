#pragma once
#include "./any.hh"
#include "../atom/block.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP lattice;
template <class   ..._s>	XTAL_USE lattice_t = typename lattice<_s...>::type;
template <class   ..._s>	XTAL_ASK lattice_q = bond::head_tag_p<lattice_t, _s...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_FN1 lattice_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<lattice_t>::template via<V>(XTAL_REF_(oo)...);}

template <class T, class S=T>
XTAL_ASK lettuce_q = bond::heteropack_q<T> and bond::pack_size_n<T> == bond::pack_size_n<S>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `block` with point-wise comparison, \
and lifts all other operators. \

template <class U, size_t N, size_t ...Ns>
struct lattice<U[N][Ns]...> : lattice<lattice_t<U[N]>[Ns]...>
{
};
template <column_q A>
struct lattice<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using allotype = typename atom::block<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<lattice_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
		using  I_ = typename T_::difference_type;

	protected:
		using          T_::N_data;
		using typename T_::U_data;

	public:
		using T_::T_;
		using T_::self;
		using T_::twin;
		using T_::size;
		using T_::get;
		using T_::let;

	public:// OPERATE
	//	Vector comparison (performed point-wise):
		XTAL_DEF_(return,inline)
		XTAL_OP1 <=> (homotype const &t)
		XTAL_0FX
		{
			homotype const &s = *this;
			return\
				s <  t? _std::strong_ordering::      less:
			   s == t? _std::strong_ordering::     equal:
			   s  > t? _std::strong_ordering::   greater:
			           _std::strong_ordering::equivalent;
		}
		XTAL_DEF_(return,inline) XTAL_OP1_(bool) ==  (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) == t.get(I))) (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline) XTAL_OP1_(bool) <=  (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) <= t.get(I))) (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline) XTAL_OP1_(bool) >=  (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) >= t.get(I))) (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline) XTAL_OP1_(bool) <   (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) <  t.get(I))) (bond::seek_s<N_data> {});}
		XTAL_DEF_(return,inline) XTAL_OP1_(bool) >   (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) >  t.get(I))) (bond::seek_s<N_data> {});}

	//	Scalar assignment (performed point-wide):
		XTAL_DEF_(inline)        XTAL_OP1_(T  &) <<= (size_t   const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I) <<= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_OP1_(T  &) >>= (size_t   const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I) >>= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_OP1_(T  &)  ^= (U_data   const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I)  ^= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_OP1_(T  &)  |= (U_data   const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I)  |= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_OP1_(T  &)  &= (U_data   const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I)  &= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_OP1_(T  &)  %= (U_data   const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I)  %= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_OP1_(T  &)  *= (U_data   const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I)  *= u;}); return self();}
		XTAL_DEF_(inline)        XTAL_OP1_(T  &)  /= (U_data   const &u) XTAL_0EX {bond::seek_forward_f<N_data>([n = 1.0/u, this] (auto I) XTAL_0FN {let(I)  *= n;}); return self();}

		XTAL_DEF_(return,inline,friend) XTAL_OP1_(auto) * (devolved_p<T> auto const &s, T const &t) XTAL_0EX {return t * s;}
		XTAL_DEF_(return,inline,friend) XTAL_OP1_(auto) + (devolved_p<T> auto const &s, T const &t) XTAL_0EX {return t + s;}

		///\
		Component-wise field-adjustment by an equal-sized `heteropack`. \
		
		XTAL_DEF_(return,inline,friend)
		XTAL_OP1 * (T const &s, lettuce_q auto const &t)
		XTAL_0EX
		{
			using _std::get;

			return [&]<XTAL_NDX ...i> (bond::seek_t<i...>)
				XTAL_0FN_(bond::pack_f(get<i>(s) * get<i>(t)...))
			(bond::seek_s<N_data>{});
		}
		XTAL_DEF_(return,inline,friend)
		XTAL_OP1 / (T const &s, lettuce_q auto const &t)
		XTAL_0EX
		{
			using _std::get;

			return [&]<XTAL_NDX ...i> (bond::seek_t<i...>)
				XTAL_0FN_(bond::pack_f(get<i>(s) / get<i>(t)...))
			(bond::seek_s<N_data>{});
		}
		XTAL_DEF_(return,inline,friend)
		XTAL_OP1 + (T const &s, lettuce_q auto const &t)
		XTAL_0EX
		{
			using _std::get;

			return [&]<XTAL_NDX ...i> (bond::seek_t<i...>)
				XTAL_0FN_(bond::pack_f(get<i>(s) + get<i>(t)...))
			(bond::seek_s<N_data>{});
		}
		XTAL_DEF_(return,inline,friend)
		XTAL_OP1 - (T const &s, lettuce_q auto const &t)
		XTAL_0EX
		{
			using _std::get;

			return [&]<XTAL_NDX ...i> (bond::seek_t<i...>)
				XTAL_0FN_(bond::pack_f(get<i>(s) - get<i>(t)...))
			(bond::seek_s<N_data>{});
		}

	};
	using type = bond::isotype<homotype>;

};
static_assert(not counted_q<lattice_t<   int[2]>>);
static_assert(not counted_q<lattice_t<size_s[2]>>);
static_assert(not counted_q<lattice_t<size_t[2]>>);

static_assert(fungible_q<_std::span<float, 2>, lattice_t<float(&)[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
