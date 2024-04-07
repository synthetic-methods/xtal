#pragma once
#include "./any.hh"
#include "./sector.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_NEW serial;
template <class ..._s> XTAL_USE serial_t = typename serial<_s...>::type;
template <class ...Ts> XTAL_ASK serial_q = bond::tag_p<serial, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `sector` with multiplication defined by linear convolution. \

template <class U, int N>
struct serial<U[N]>
{
	using re = bond::realize<U>;
	
	template <class T>
	using demitype = typename sector<U[N]>::template homotype<T>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<serial>>;

	template <class T>
	class homotype : public hemitype<T>
	{
		friend T;
		using  T_ = hemitype<T>;
	
	public:// CONSTRUCTION
		using T_::T_;


	public:// OPERATION
		using T_::get;
		using T_::let;
		using T_::self;
		using T_::twin;
		using T_::operator*=;

		///\
		Multiplication by linear convolution, truncated by `N`. \

		XTAL_OP1_(T &) *= (T const &t)
		XTAL_0EX
		{
			if constexpr (re::alignment_n < N) {
				for (auto i = N; ~--i;) {let(i) *= t.get(0);
				for (auto j = i; j-- ;) {let(i) += t.get(j)*get(i - j);}}
			}
			else {
				bond::seek_backward_f<N, 0>([&, this] (auto I) XTAL_0FN {let(I) *= t.get(0);
				bond::seek_backward_f<I, 1>([&, this] (auto J) XTAL_0FN {let(I) += t.get(J)*get(I - J);});});
			}
			return self();
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
