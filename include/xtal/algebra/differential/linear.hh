#pragma once
#include "./any.hh"
#include "../serial.hh"
#include "../series.hh"




XTAL_ENV_(push)
namespace xtal::algebra::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_TYP linear;
template <class ..._s> XTAL_USE linear_t = typename linear<_s...>::type;
template <class ...Ts> XTAL_ASK linear_q = bond::head_tag_p<linear, Ts...>;

template <auto f, class ...Xs> requires common_q<Xs...>
XTAL_DEF_(return,inline)
XTAL_FN1 linear_f(Xs &&...xs)
XTAL_0EX
{
	XTAL_USE U = common_t<Xs...>;
	XTAL_SET N = sizeof...(xs);
	if constexpr (idempotent_p<U, decltype(f)>) {
		return linear_t<U[N]>{ (XTAL_REF_(xs))...};
	}
	else {
		return linear_t<U[N]>{f(XTAL_REF_(xs))...};
	}
}
template <class ...Xs>
XTAL_DEF_(return,inline)
XTAL_FN1 linear_f(Xs &&...xs)
XTAL_0EX
{
	return linear_f<[] XTAL_1FN_(objective_f)>(XTAL_REF_(xs)...);
}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `serial` with succession. \

template <class U_data> requires disarray_q<U_data>
struct linear<U_data> : linear<U_data[2]>
{};
template <class U_data, int N_data>
struct linear<U_data[N_data]>
{
	using Op = bond::operate<U_data>;
	
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

		XTAL_DEF_(inline)
		XTAL_OP1 ++ (int)
		XTAL_0EX
		{
			auto t = twin(); operator++(); return t;
		}
		XTAL_DEF_(inline)
		XTAL_OP1 ++ ()
		XTAL_0EX
		{
			bond::seek_forward_f<N_data - 1>([this] (auto I) XTAL_0FN_(let(I) += get(I + 1)));
			return self();
		}

		///\
		Produces the predecessor by pairwise subtraction from `end()` to `begin()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_DEF_(inline)
		XTAL_OP1 -- (int)
		XTAL_0EX
		{
			auto t = twin(); operator--(); return t;
		}
		XTAL_DEF_(inline)
		XTAL_OP1 -- ()
		XTAL_0EX
		{
			bond::seek_backward_f<N_data - 1>([this] (auto I) XTAL_0FN_(let(I) -= get(I + 1)));
			return self();
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
