#pragma once
#include "./any.hh"
#include "../serial.hh"
#include "../series.hh"




XTAL_ENV_(push)
namespace xtal::algebra::differential
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class   ..._s>	XTAL_TYP linear;
template <class   ..._s>	XTAL_USE linear_t = typename linear<_s...>::type;
template <class   ...Ts>	XTAL_REQ linear_q = bond::head_tag_p<linear_t, Ts...>;
template <class  V=void>
XTAL_DEF_(return,inline)
XTAL_LET linear_f(auto &&...oo)
XTAL_0EX {return _detail::initialize<linear_t>::template via<V>(XTAL_REF_(oo)...);}


////////////////////////////////////////////////////////////////////////////////
///\
Extends `serial` with succession. \

template <column_q A>
struct linear<A>
{
	using _op = bond::operate<A>;
	
	template <class T>
	using allotype = typename serial<A>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<linear_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		friend T;
		using  T_ = holotype<T>;
	
	protected:
		using          T_::N_data;
		using typename T_::U_data;

	public:// CONSTRUCT
		using T_::T_;

	public:// OPERATE
	//	using T_::get;
		using T_::let;
		using T_::self;
		using T_::twin;

		///\
		Produces the successor by pairwise addition from `begin()` to `end()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_DEF_(inline)
		XTAL_REF operator ++ (int)
		XTAL_0EX
		{
			auto t = twin(); operator++(); return t;
		}
		XTAL_DEF_(inline)
		XTAL_REF operator ++ ()
		XTAL_0EX
		{
			auto &s = self();

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(s) += get<I + 1>(s)),...);}
			(bond::seek_s<N_data - 1>{});
			return self();
		}

		///\
		Produces the predecessor by pairwise subtraction from `end()` to `begin()`, \
		assuming the entries of `this` are finite differences/derivatives. \

		XTAL_DEF_(inline)
		XTAL_REF operator -- (int)
		XTAL_0EX
		{
			auto t = twin(); operator--(); return t;
		}
		XTAL_DEF_(inline)
		XTAL_REF operator -- ()
		XTAL_0EX
		{
			auto &s = self();

			[&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(s) -= get<I + 1>(s)),...);}
			(bond::antiseek_s<N_data - 1>{});
			return self();
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
