#pragma once
#include "./any.hh"
#include "../atom/block.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_TYP lattice;
template <class ..._s> XTAL_USE lattice_t = typename lattice<_s...>::type;
template <class ..._s> XTAL_ASK lattice_q = bond::tag_p<lattice, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `block` with point-wise comparison, \
and lifts all other operators. \

template <class U, size_t N, int Ns>
struct lattice<U[N][Ns]> : lattice<lattice_t<U[N]>[Ns]>
{};
template <class U_data, size_t N_data>
struct lattice<U_data[N_data]>
{
	using re = bond::realize<U_data>;
	
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
		XTAL_TN2 apply(auto &&f)
		XTAL_0EX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(f(_std::get<I>(*this)...)) (bond::seek_s<N_data> {});}
		
		template <class F>
		XTAL_TN2 make()
		XTAL_0EX {return apply([] XTAL_1FN_(F));}

		using pact_t = bond::pact_made_t<T_>;
		XTAL_OP0_(implicit) pact_t() XTAL_0EX {return make<pact_t>();}


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
		XTAL_OP1_(T &) <<= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([                &, this] (auto i) XTAL_0FN {let(i) <<= u;}); return self();}
		XTAL_OP1_(T &) >>= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([                &, this] (auto i) XTAL_0FN {let(i) >>= u;}); return self();}
		XTAL_OP1_(T &)  &= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([                &, this] (auto i) XTAL_0FN {let(i)  &= u;}); return self();}
		XTAL_OP1_(T &)  ^= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([                &, this] (auto i) XTAL_0FN {let(i)  ^= u;}); return self();}
		XTAL_OP1_(T &)  *= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([                &, this] (auto i) XTAL_0FN {let(i)  *= u;}); return self();}
		XTAL_OP1_(T &)  %= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([                &, this] (auto i) XTAL_0FN {let(i)  %= u;}); return self();}
		XTAL_OP1_(T &)  /= (U_data     const &u) XTAL_0EX {bond::seek_forward_f<N_data>([n = re::alpha_1/u, this] (auto i) XTAL_0FN {let(i)  *= n;}); return self();}

	//	Vector assignment (via `std::initializer_list`):
		XTAL_OP1_(T &) <<= (embrace_t<U_data> w) XTAL_0EX {return   self() <<=         T(w);}
		XTAL_OP1_(T &) >>= (embrace_t<U_data> w) XTAL_0EX {return   self() >>=         T(w);}
		XTAL_OP1_(T &)  &= (embrace_t<U_data> w) XTAL_0EX {return   self()  &=         T(w);}
		XTAL_OP1_(T &)  ^= (embrace_t<U_data> w) XTAL_0EX {return   self()  ^=         T(w);}
		XTAL_OP1_(T &)  |= (embrace_t<U_data> w) XTAL_0EX {return   self()  |=         T(w);}
		XTAL_OP1_(T &)  *= (embrace_t<U_data> w) XTAL_0EX {return   self()  *=         T(w);}
		XTAL_OP1_(T &)  %= (embrace_t<U_data> w) XTAL_0EX {return   self()  %=         T(w);}
		XTAL_OP1_(T &)  /= (embrace_t<U_data> w) XTAL_0EX {return   self()  /=         T(w);}
		XTAL_OP1_(T &)  += (embrace_t<U_data> w) XTAL_0EX {return   self()  +=         T(w);}
		XTAL_OP1_(T &)  -= (embrace_t<U_data> w) XTAL_0EX {return   self()  -=         T(w);}

	//	Generic operation (via assignment):
		XTAL_OP2_(T)   <<  (auto            &&w) XTAL_0FX {return   twin() <<= XTAL_REF_(w);}
		XTAL_OP2_(T)   >>  (auto            &&w) XTAL_0FX {return   twin() >>= XTAL_REF_(w);}
		XTAL_OP2_(T)    &  (auto            &&w) XTAL_0FX {return   twin()  &= XTAL_REF_(w);}
		XTAL_OP2_(T)    ^  (auto            &&w) XTAL_0FX {return   twin()  ^= XTAL_REF_(w);}
		XTAL_OP2_(T)    |  (auto            &&w) XTAL_0FX {return   twin()  |= XTAL_REF_(w);}
		XTAL_OP2_(T)    *  (auto            &&w) XTAL_0FX {return   twin()  *= XTAL_REF_(w);}
		XTAL_OP2_(T)    %  (auto            &&w) XTAL_0FX {return   twin()  %= XTAL_REF_(w);}
		XTAL_OP2_(T)    /  (auto            &&w) XTAL_0FX {return   twin()  /= XTAL_REF_(w);}
		XTAL_OP2_(T)    +  (auto            &&w) XTAL_0FX {return   twin()  += XTAL_REF_(w);}
		XTAL_OP2_(T)    -  (auto            &&w) XTAL_0FX {return   twin()  -= XTAL_REF_(w);}

		XTAL_OP3_(T)    * (devolved_q<T> auto &&w, T const &t) XTAL_0EX {return t * XTAL_REF_(w);}
		XTAL_OP3_(T)    + (devolved_q<T> auto &&w, T const &t) XTAL_0EX {return t + XTAL_REF_(w);}
		template <template <class> class K> XTAL_OP3_(T)    * (devolved_q<T> auto &&w, K<T> const &t) XTAL_0EX {return t * XTAL_REF_(w);}
		template <template <class> class K> XTAL_OP3_(T)    + (devolved_q<T> auto &&w, K<T> const &t) XTAL_0EX {return t + XTAL_REF_(w);}

	};
	using type = bond::isotype<homotype>;

};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
