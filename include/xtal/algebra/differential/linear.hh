#pragma once
#include "./any.hh"
#include "../serial.hh"





XTAL_ENV_(push)
namespace xtal::algebra::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_TYP linear;
template <class ..._s> XTAL_USE linear_t = typename linear<_s...>::type;
template <class ...Ts> XTAL_ASK linear_q = bond::tag_p<linear, Ts...>;

XTAL_LET  linear_f = []<class ...Xs> (Xs &&...xs)
XTAL_0FN_(linear_t<common_t<Xs...>[sizeof...(Xs)]>{XTAL_REF_(xs)...});


////////////////////////////////////////////////////////////////////////////////
///\
Extends `serial` with succession. \

template <class U_data> requires disarray_q<U_data>
struct linear<U_data> : linear<U_data[2]>
{};
template <class U_data, int N_data>
struct linear<U_data[N_data]>
{
	using re = bond::realize<U_data>;
	
	template <class T>
	using allotype = typename serial<U_data[N_data]>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<linear>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
	
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
			bond::seek_forward_f<N_data - 1>([this] (auto i) XTAL_0FN_(let(i) += get(i + 1)));
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
			bond::seek_backward_f<N_data - 1>([this] (auto i) XTAL_0FN_(let(i) -= get(i + 1)));
			return self();
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
