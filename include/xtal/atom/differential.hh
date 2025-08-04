#pragma once
#include "./any.hh"
#include "./wrap.hh"
#include "./group.hh"




XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Extends `group` with component-wise addition and differential succession.
*/
template <class ...Us>	struct  differential;
template <class ...Us>	using   differential_t = typename differential<Us...>::type;
template <class ...Us>	concept differential_q = bond::tag_infixed_p<differential_t, Us...>;

XTAL_DEF_(let) differential_f = [] XTAL_1FN_(call) (_detail::factory<differential_t>::make);


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ...Us> requires common_q<Us...>
struct differential<Us ...>
:	differential<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct differential
{
	template <class T>
	using endotype = typename group<wrap_s<Us, _std::plus>...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<differential_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::element;
		using S_::size;
		using S_::self;
		using S_::twin;
	
	public:// OPERATE
		XTAL_DEF_(inline,let) operator ++(int) noexcept -> auto {auto t = twin(); operator++(); return t;}
		XTAL_DEF_(inline,let) operator --(int) noexcept -> auto {auto t = twin(); operator--(); return t;}

		/*!
		\brief  	Produces the successor by pairwise addition from `begin()` to `end()`,
		assuming the entries of `this` are finite differences/derivatives.
		*/
		XTAL_DEF_(inline,let)
		operator ++ ()
		noexcept -> T &
		{
			[this]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(self()) += get<I + 1>(self())),...);}
			(bond::seek_s<size - 1>{});
			
			return self();
		}
		/*!
		\brief  	Produces the predecessor by pairwise subtraction from `end()` to `begin()`,
		assuming the entries of `this` are finite differences/derivatives.
		*/
		XTAL_DEF_(inline,let)
		operator -- ()
		noexcept -> T &
		{
			[this]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN {((get<I>(self()) -= get<I + 1>(self())),...);}
			(bond::seek_reverse_s<size - 1>{});
			
			return self();
		}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
