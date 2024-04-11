#pragma once
#include "./any.hh"
#include "./sector.hh"





XTAL_ENV_(push)
namespace xtal::algebra
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  serial;
template <class ..._s> using   serial_t = typename serial<_s...>::type;
template <class ...Ts> concept serial_q = bond::tag_p<serial, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `sector` with multiplication defined by linear convolution. \

template <class U_data, int N_data>
struct serial<U_data[N_data]>
{
	using re = bond::realize<U_data>;
	
	template <class T>
	using demitype = typename sector<U_data[N_data]>::template homotype<T>;

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
		Multiplication by linear convolution, truncated by `N_data`. \

		XTAL_OP1_(T &) *= (T const &t)
		XTAL_0EX
		{
			if constexpr (re::alignment_n < N_data) {
				for (auto i = N_data; ~--i;) {let(i) *= t.get(0);
				for (auto j = i; j-- ;) {let(i) += t.get(j)*get(i - j);}}
			}
			else {
				bond::seek_backward_f<N_data, 0>([&, this] (auto I) XTAL_0FN {let(I) *= t.get(0);
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
