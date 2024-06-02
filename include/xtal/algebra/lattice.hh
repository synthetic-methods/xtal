#pragma once
#include "./any.hh"
#include "../atom/block.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP lattice;
template <class   ..._s>	XTAL_USE lattice_t = typename lattice<_s...>::type;
template <class   ..._s>	XTAL_ASK lattice_q = bond::head_tag_p<lattice, _s...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_FN1 lattice_f(auto &&...oo)
XTAL_0EX {return _detail::build<lattice_t>::template via<V>(XTAL_REF_(oo)...);}

template <class  T, class  L=T  >	XTAL_ASK lettuce_q = bond::pack_q<T> and not lattice_q<T> and bond::pack_size_n<T> == bond::pack_size_n<L>;
template <class  L, class ...Ts >	XTAL_ASK lettuce_p = (...and lettuce_q<Ts, L>);


////////////////////////////////////////////////////////////////////////////////
///\
Extends `block` with point-wise comparison, \
and lifts all other operators. \

template <class U, size_t N, size_t ...Ns>
struct lattice<U[N][Ns]...> : lattice<lattice_t<U[N]>[Ns]...>
{};
template <class U_data, size_t N_data>
struct lattice<U_data[N_data]>
{
	using Op = bond::operate<U_data>;
	
	template <class T>
	using allotype = typename atom::block<U_data[N_data]>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<lattice>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
		using  I_ = typename T_::difference_type;

	public:
		using T_::T_;
		using T_::self;
		using T_::twin;
		using T_::size;
		using T_::get;
		using T_::let;

	public:// OPERATION
	//	Vector comparison (performed point-wise):
		XTAL_OP2 <=> (homotype const &t)
		XTAL_0FX
		{
			homotype const &s = *this;
			return\
				s <  t? _std::strong_ordering::      less:
			   s == t? _std::strong_ordering::     equal:
			   s  > t? _std::strong_ordering::   greater:
			           _std::strong_ordering::equivalent;
		}
		XTAL_OP2_(bool) == (homotype   const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) == t.get(I))) (bond::seek_s<N_data> {});}
		XTAL_OP2_(bool) <= (homotype   const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) <= t.get(I))) (bond::seek_s<N_data> {});}
		XTAL_OP2_(bool) >= (homotype   const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) >= t.get(I))) (bond::seek_s<N_data> {});}
		XTAL_OP2_(bool) <  (homotype   const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) <  t.get(I))) (bond::seek_s<N_data> {});}
		XTAL_OP2_(bool) >  (homotype   const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) >  t.get(I))) (bond::seek_s<N_data> {});}

	//	Scalar assignment (performed point-wide):
		XTAL_OP1_(T &) <<= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I) <<= u;}); return self();}
		XTAL_OP1_(T &) >>= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I) >>= u;}); return self();}
		XTAL_OP1_(T &)  &= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I)  &= u;}); return self();}
		XTAL_OP1_(T &)  ^= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I)  ^= u;}); return self();}
		XTAL_OP1_(T &)  *= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I)  *= u;}); return self();}
		XTAL_OP1_(T &)  %= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([        &, this] (auto I) XTAL_0FN {let(I)  %= u;}); return self();}
		XTAL_OP1_(T &)  /= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([n = 1.0/u, this] (auto I) XTAL_0FN {let(I)  *= n;}); return self();}

	//	Vector assignment (via `std::initializer_list`):
		XTAL_OP1_(T &) <<= (embrace_t<U_data> w) XTAL_0EX {return self() <<= T(w);}
		XTAL_OP1_(T &) >>= (embrace_t<U_data> w) XTAL_0EX {return self() >>= T(w);}
		XTAL_OP1_(T &)  &= (embrace_t<U_data> w) XTAL_0EX {return self()  &= T(w);}
		XTAL_OP1_(T &)  ^= (embrace_t<U_data> w) XTAL_0EX {return self()  ^= T(w);}
		XTAL_OP1_(T &)  |= (embrace_t<U_data> w) XTAL_0EX {return self()  |= T(w);}
		XTAL_OP1_(T &)  *= (embrace_t<U_data> w) XTAL_0EX {return self()  *= T(w);}
		XTAL_OP1_(T &)  %= (embrace_t<U_data> w) XTAL_0EX {return self()  %= T(w);}
		XTAL_OP1_(T &)  /= (embrace_t<U_data> w) XTAL_0EX {return self()  /= T(w);}
		XTAL_OP1_(T &)  += (embrace_t<U_data> w) XTAL_0EX {return self()  += T(w);}
		XTAL_OP1_(T &)  -= (embrace_t<U_data> w) XTAL_0EX {return self()  -= T(w);}

	//	Generic operation (via assignment):
		XTAL_OP2_(T)   <<  (auto const &w)       XTAL_0FX {return twin() <<=   w ;}
		XTAL_OP2_(T)   >>  (auto const &w)       XTAL_0FX {return twin() >>=   w ;}
		XTAL_OP2_(T)    &  (auto const &w)       XTAL_0FX {return twin()  &=   w ;}
		XTAL_OP2_(T)    ^  (auto const &w)       XTAL_0FX {return twin()  ^=   w ;}
		XTAL_OP2_(T)    |  (auto const &w)       XTAL_0FX {return twin()  |=   w ;}
		XTAL_OP2_(T)    *  (auto const &w)       XTAL_0FX {return twin()  *=   w ;}
		XTAL_OP2_(T)    %  (auto const &w)       XTAL_0FX {return twin()  %=   w ;}
		XTAL_OP2_(T)    /  (auto const &w)       XTAL_0FX {return twin()  /=   w ;}
		XTAL_OP2_(T)    +  (auto const &w)       XTAL_0FX {return twin()  +=   w ;}
		XTAL_OP2_(T)    -  (auto const &w)       XTAL_0FX {return twin()  -=   w ;}

		XTAL_OP3        *  (devolved_q<T> auto const &w, T const &t) XTAL_0EX {return t * w;}
		XTAL_OP3        +  (devolved_q<T> auto const &w, T const &t) XTAL_0EX {return t + w;}

		///\
		Component-wise field-adjustment by an equal-sized non-`lattice`. \
		
		XTAL_OP3 * (T const &t, lettuce_q auto const &w)
		XTAL_0EX
		{
			using _std::get;

			return [&]<XTAL_NDX ...i> (bond::seek_t<i...>)
				XTAL_0FN_(bond::pack_f(get<i>(t) * get<i>(w)...))
			(bond::seek_s<N_data>{});
		}
		XTAL_OP3 / (T const &t, lettuce_q auto const &w)
		XTAL_0EX
		{
			using _std::get;

			return [&]<XTAL_NDX ...i> (bond::seek_t<i...>)
				XTAL_0FN_(bond::pack_f(get<i>(t) / get<i>(w)...))
			(bond::seek_s<N_data>{});
		}
		XTAL_OP3 + (T const &t, lettuce_q auto const &w)
		XTAL_0EX
		{
			using _std::get;

			return [&]<XTAL_NDX ...i> (bond::seek_t<i...>)
				XTAL_0FN_(bond::pack_f(get<i>(t) + get<i>(w)...))
			(bond::seek_s<N_data>{});
		}
		XTAL_OP3 - (T const &t, lettuce_q auto const &w)
		XTAL_0EX
		{
			using _std::get;

			return [&]<XTAL_NDX ...i> (bond::seek_t<i...>)
				XTAL_0FN_(bond::pack_f(get<i>(t) - get<i>(w)...))
			(bond::seek_s<N_data>{});
		}


	};
	using type = bond::isotype<homotype>;

};
static_assert(not counted_q<lattice_t<   int[2]>>);
static_assert(not counted_q<lattice_t<size_s[2]>>);
static_assert(not counted_q<lattice_t<size_t[2]>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
