#pragma once
#include "./any.hh"
#include "./group.hh"





XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Extends `group` with component-wise addition and differential succession.
*/
template <class ...Us>	struct  grade;
template <class ...Us>	using   grade_t = typename grade<Us...>::type;
template <class ...Us>	concept grade_q = bond::tag_infixed_p<grade_t, Us...>;

XTAL_DEF_(let) grade_f = [] XTAL_1FN_(call) (_detail::fake_f<grade_t>);


////////////////////////////////////////////////////////////////////////////////

template <scalar_q ...Us> requires common_q<Us...>
struct grade<Us ...>
:	grade<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct grade
{
	template <class T>
	using endotype = typename group_addition<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<grade_t>>;

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
