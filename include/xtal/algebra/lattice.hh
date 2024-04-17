#pragma once
#include "./any.hh"
#include "../atom/block.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  lattice;
template <class ..._s> using   lattice_t = typename lattice<_s...>::type;
template <class ..._s> concept lattice_q = bond::tag_p<lattice, _s...>;

template <class T, class U>	concept semilattice_q = lattice_q<T, U> and widen_q<typename T::value_type, typename U::value_type>;
template <class T, class U>	concept semilattice_p = lattice_q<U, T> and widen_q<typename U::value_type, typename T::value_type>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `block` with point-wise comparison, \
and lifts all other operators. \

template <class U, size_t N, int Ns>
struct lattice<U[N][Ns]> : lattice<lattice_t<U[N]>[Ns]>
{};
template <class U, size_t N>
struct lattice<U[N]>
{
	using re = bond::realize<U>;
	
	template <class T>
	using allotype = typename atom::block<U[N]>::template homotype<T>;

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
		XTAL_OP2_(bool) ==     (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) == t.get(I))) (bond::seek_f<N> {});}
		XTAL_OP2_(bool) <=     (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) <= t.get(I))) (bond::seek_f<N> {});}
		XTAL_OP2_(bool) >=     (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) >= t.get(I))) (bond::seek_f<N> {});}
		XTAL_OP2_(bool) <      (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) <  t.get(I))) (bond::seek_f<N> {});}
		XTAL_OP2_(bool) >      (homotype const &t) XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) >  t.get(I))) (bond::seek_f<N> {});}

	//	Scalar assignment (performed point-wide):
		XTAL_OP1_(T &) <<=            (U const &u) XTAL_0EX {bond::seek_forward_f<N>([                &, this] (auto i) XTAL_0FN {let(i) <<= u;}); return self();}
		XTAL_OP1_(T &) >>=            (U const &u) XTAL_0EX {bond::seek_forward_f<N>([                &, this] (auto i) XTAL_0FN {let(i) >>= u;}); return self();}
		XTAL_OP1_(T &)  &=            (U const &u) XTAL_0EX {bond::seek_forward_f<N>([                &, this] (auto i) XTAL_0FN {let(i)  &= u;}); return self();}
		XTAL_OP1_(T &)  ^=            (U const &u) XTAL_0EX {bond::seek_forward_f<N>([                &, this] (auto i) XTAL_0FN {let(i)  ^= u;}); return self();}
		XTAL_OP1_(T &)  *=            (U const &u) XTAL_0EX {bond::seek_forward_f<N>([                &, this] (auto i) XTAL_0FN {let(i)  *= u;}); return self();}
		XTAL_OP1_(T &)  %=            (U const &u) XTAL_0EX {bond::seek_forward_f<N>([                &, this] (auto i) XTAL_0FN {let(i)  %= u;}); return self();}
		XTAL_OP1_(T &)  /=            (U const &u) XTAL_0EX {bond::seek_forward_f<N>([n = re::alpha_1/u, this] (auto i) XTAL_0FN {let(i)  *= n;}); return self();}

	//	Vector assignment (via `std::initializer_list`):
		XTAL_OP1_(T &) <<=        (embrace_t<U> w) XTAL_0EX {return   self() <<=         T(w);}
		XTAL_OP1_(T &) >>=        (embrace_t<U> w) XTAL_0EX {return   self() >>=         T(w);}
		XTAL_OP1_(T &)  &=        (embrace_t<U> w) XTAL_0EX {return   self()  &=         T(w);}
		XTAL_OP1_(T &)  ^=        (embrace_t<U> w) XTAL_0EX {return   self()  ^=         T(w);}
		XTAL_OP1_(T &)  |=        (embrace_t<U> w) XTAL_0EX {return   self()  |=         T(w);}
		XTAL_OP1_(T &)  *=        (embrace_t<U> w) XTAL_0EX {return   self()  *=         T(w);}
		XTAL_OP1_(T &)  %=        (embrace_t<U> w) XTAL_0EX {return   self()  %=         T(w);}
		XTAL_OP1_(T &)  /=        (embrace_t<U> w) XTAL_0EX {return   self()  /=         T(w);}
		XTAL_OP1_(T &)  +=        (embrace_t<U> w) XTAL_0EX {return   self()  +=         T(w);}
		XTAL_OP1_(T &)  -=        (embrace_t<U> w) XTAL_0EX {return   self()  -=         T(w);}

	//	Generic operation (via assignment):
		XTAL_OP2_(T)   <<               (auto &&w) XTAL_0FX {return   twin() <<= XTAL_REF_(w);}
		XTAL_OP2_(T)   >>               (auto &&w) XTAL_0FX {return   twin() >>= XTAL_REF_(w);}
		XTAL_OP2_(T)    &               (auto &&w) XTAL_0FX {return   twin()  &= XTAL_REF_(w);}
		XTAL_OP2_(T)    ^               (auto &&w) XTAL_0FX {return   twin()  ^= XTAL_REF_(w);}
		XTAL_OP2_(T)    |               (auto &&w) XTAL_0FX {return   twin()  |= XTAL_REF_(w);}
		XTAL_OP2_(T)    *               (auto &&w) XTAL_0FX {return   twin()  *= XTAL_REF_(w);}
		XTAL_OP2_(T)    %               (auto &&w) XTAL_0FX {return   twin()  %= XTAL_REF_(w);}
		XTAL_OP2_(T)    /               (auto &&w) XTAL_0FX {return   twin()  /= XTAL_REF_(w);}
		XTAL_OP2_(T)    +               (auto &&w) XTAL_0FX {return   twin()  += XTAL_REF_(w);}
		XTAL_OP2_(T)    -               (auto &&w) XTAL_0FX {return   twin()  -= XTAL_REF_(w);}

		XTAL_OP3_(T)    * (devolved_q<T> auto &&w, T const &t) XTAL_0EX {return t.twin()  *= XTAL_REF_(w);}
		XTAL_OP3_(T)    + (devolved_q<T> auto &&w, T const &t) XTAL_0EX {return t.twin()  += XTAL_REF_(w);}

	};
	using type = bond::isotype<homotype>;

};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
