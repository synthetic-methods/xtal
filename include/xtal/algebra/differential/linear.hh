#pragma once
#include "./any.hh"
#include "../serial.hh"





XTAL_ENV_(push)
namespace xtal::algebra::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  linear;
template <class ..._s> using   linear_t = typename linear<_s...>::type;
template <class ...Ts> concept linear_q = bond::tag_p<linear, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Extends `serial` with succession. \

template <class U, int N>
struct linear<U[N]>
{
	using re = bond::realize<U>;
	
	template <class T>
	using demitype = typename serial<U[N]>::template homotype<T>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<linear>>;

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

		///\
		Produces the successor by pairwise addition from `begin()` to `end()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_OP1 ++ (int)
		XTAL_0EX
		{
			auto t = twin(); operator++(); return t;
		}
		XTAL_OP1 ++ ()
		XTAL_0EX
		{
			bond::seek_forward_f<N - 1>([this] (auto i) XTAL_0FN_(let(i) += get(i + 1)));
			return self();
		}

		///\
		Produces the predecessor by pairwise subtraction from `end()` to `begin()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_OP1 -- (int)
		XTAL_0EX
		{
			auto t = twin(); operator--(); return t;
		}
		XTAL_OP1 -- ()
		XTAL_0EX
		{
			bond::seek_backward_f<N - 1>([this] (auto i) XTAL_0FN_(let(i) -= get(i + 1)));
			return self();
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
