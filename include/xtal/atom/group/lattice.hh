#pragma once
#include "./any.hh"
#include "../block.hh"





XTAL_ENV_(push)
namespace xtal::atom::group
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  lattice;
template <class ..._s> using   lattice_t = typename lattice<_s...>::type;
template <class ..._s> concept lattice_q = bond::tag_p<lattice, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `block` with point-wise comparison and generic operators. \

template <class U_type, size_t N, int Ns>
struct lattice<U_type[N][Ns]> : lattice<lattice_t<U_type[N]>[Ns]>
{};
template <class U_type, size_t N_size>
struct lattice<U_type[N_size]>
{
	using re = bond::realize<U_type>;
	
	template <class T>
	using demitype = typename block<U_type[N_size]>::template homotype<T>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<lattice>>;

	template <class T>
	class homotype : public hemitype<T>
	{
		friend T;
		using  T_ = hemitype<T>;
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
		XTAL_OP2_(bool) == (homotype const &t)          XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) == t.get(I))) (bond::seek_f<N_size> {});}
		XTAL_OP2_(bool) <= (homotype const &t)          XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) <= t.get(I))) (bond::seek_f<N_size> {});}
		XTAL_OP2_(bool) >= (homotype const &t)          XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) >= t.get(I))) (bond::seek_f<N_size> {});}
		XTAL_OP2_(bool) <  (homotype const &t)          XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) <  t.get(I))) (bond::seek_f<N_size> {});}
		XTAL_OP2_(bool) >  (homotype const &t)          XTAL_0FX {return [&, this]<auto ...I>(bond::seek_t<I...>) XTAL_0FN_(...and (get(I) >  t.get(I))) (bond::seek_f<N_size> {});}

	//	Vector assignment (via lifted `std::initializer_list`):
		XTAL_OP1_(T &) <<= (braces_t<U_type> w)         XTAL_0EX {return              self() <<=         T(w);}
		XTAL_OP1_(T &) >>= (braces_t<U_type> w)         XTAL_0EX {return              self() >>=         T(w);}

		XTAL_OP1_(T &)  &= (braces_t<U_type> w)         XTAL_0EX {return              self()  &=         T(w);}
		XTAL_OP1_(T &)  ^= (braces_t<U_type> w)         XTAL_0EX {return              self()  ^=         T(w);}
		XTAL_OP1_(T &)  |= (braces_t<U_type> w)         XTAL_0EX {return              self()  |=         T(w);}
		XTAL_OP1_(T &)  *= (braces_t<U_type> w)         XTAL_0EX {return              self()  *=         T(w);}
		XTAL_OP1_(T &)  /= (braces_t<U_type> w)         XTAL_0EX {return              self()  /=         T(w);}
		XTAL_OP1_(T &)  += (braces_t<U_type> w)         XTAL_0EX {return              self()  +=         T(w);}
		XTAL_OP1_(T &)  -= (braces_t<U_type> w)         XTAL_0EX {return              self()  -=         T(w);}

	//	Generic operation (adapted from assignment):
		XTAL_OP2_(T)   <<  (auto &&u)                   XTAL_0FX {return              twin() <<= XTAL_REF_(u);}
		XTAL_OP2_(T)   >>  (auto &&u)                   XTAL_0FX {return              twin() >>= XTAL_REF_(u);}

		XTAL_OP2_(T)    &  (auto &&u)                   XTAL_0FX {return              twin()  &= XTAL_REF_(u);}
		XTAL_OP2_(T)    ^  (auto &&u)                   XTAL_0FX {return              twin()  ^= XTAL_REF_(u);}
		XTAL_OP2_(T)    |  (auto &&u)                   XTAL_0FX {return              twin()  |= XTAL_REF_(u);}
		XTAL_OP2_(T)    *  (auto &&u)                   XTAL_0FX {return              twin()  *= XTAL_REF_(u);}
		XTAL_OP2_(T)    /  (auto &&u)                   XTAL_0FX {return              twin()  /= XTAL_REF_(u);}
		XTAL_OP2_(T)    +  (auto &&u)                   XTAL_0FX {return              twin()  += XTAL_REF_(u);}
		XTAL_OP2_(T)    -  (auto &&u)                   XTAL_0FX {return              twin()  -= XTAL_REF_(u);}

		XTAL_OP3_(T)    &  (bogey_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  &= XTAL_REF_(u);}
		XTAL_OP3_(T)    ^  (bogey_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  ^= XTAL_REF_(u);}
		XTAL_OP3_(T)    |  (bogey_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  |= XTAL_REF_(u);}
		XTAL_OP3_(T)    *  (bogey_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  *= XTAL_REF_(u);}
		XTAL_OP3_(T)    /  (bogey_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  /= XTAL_REF_(u);}
		XTAL_OP3_(T)    +  (bogey_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  += XTAL_REF_(u);}
		XTAL_OP3_(T)    -  (bogey_q<T> auto &&u, T &&t) XTAL_0EX {return XTAL_REF_(t).twin()  -= XTAL_REF_(u);}

	//	Scalar multiplication (performed point-wide):
		XTAL_OP1_(T &) <<= (bogey_q<T> auto &&u) XTAL_0EX {bond::seek_forward_f<N_size>([u =             XTAL_REF_(u), this] (auto i) XTAL_0FN {let(i) <<= u;}); return self();}
		XTAL_OP1_(T &) >>= (bogey_q<T> auto &&u) XTAL_0EX {bond::seek_forward_f<N_size>([u =             XTAL_REF_(u), this] (auto i) XTAL_0FN {let(i) >>= u;}); return self();}

		XTAL_OP1_(T &)  *= (bogey_q<T> auto &&u) XTAL_0EX {bond::seek_forward_f<N_size>([u =             XTAL_REF_(u), this] (auto i) XTAL_0FN {let(i)  *= u;}); return self();}
		XTAL_OP1_(T &)  /= (bogey_q<T> auto &&u) XTAL_0EX {bond::seek_forward_f<N_size>([n = re::alpha_1/XTAL_REF_(u), this] (auto i) XTAL_0FN {let(i)  *= n;}); return self();}

	};
	using type = bond::isotype<homotype>;

};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
