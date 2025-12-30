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

template <scalar_q ...Us> requires same_q<Us...>
struct differential<Us ...>
:	differential<common_t<Us...>[sizeof...(Us)]>
{
};
template <class ...Us>
struct differential
{
	template <class T>
	//\
	using endotype = typename group<wrap_s<Us, _std::plus>...>::template homotype<T>;
	using endotype = typename group<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<differential_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
	
	public:// CONSTRUCT
		using S_::S_;

		using typename S_::value_type;
		using typename S_::scale_type;

		template <intercedent_q K, group_multiplication_q U>
		XTAL_NEW_(explicit)
		homotype(U &&u, K)
 		noexcept
		:	S_{XTAL_REF_(u), [=]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(to) ((I, u) *...* (u)) (bond::seek_s<K::value - 1>{})}
 		{}
		template <intercedent_q K, class                  U>
		XTAL_NEW_(explicit)
		homotype(U &&u, K)
 		noexcept
		:	S_{XTAL_REF_(u), [=]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(to) ((I, u) +...+ (u)) (bond::seek_s<K::value - 1>{})}
 		{}

	public:// ACCESS
		using S_::element;
		using S_::size;
		using S_::self;
		using S_::twin;
	
	public:// OPERATE
		
		XTAL_DEF_(inline,let) operator++(int)
		noexcept -> auto {auto t = twin(); operator++(); return t;}
		
		XTAL_DEF_(inline,let) operator--(int)
		noexcept -> auto {auto t = twin(); operator--(); return t;}

		/*!
		\brief  	Produces the successor by pairwise addition from `begin()` to `end()`,
		assuming the entries of `this` are finite differences/derivatives.
		*/
		XTAL_DEF_(inline,let)
		operator ++ ()
		noexcept -> T &
		{
			[this]<auto ...I> (bond::seek_t<I...>)
			XTAL_0FN {
				auto  &s = self();
				using T0 = XTAL_ALL_(get<0>(s));
				if constexpr (group_multiplication_q<T0>) {return ((get<I>(s) *= get<I + 1>(s)),...);}
				else                                      {return ((get<I>(s) += get<I + 1>(s)),...);}
			}	(bond::seek_s<size - 1>{});
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
			XTAL_0FN {
				auto  &s = self();
				using T0 = XTAL_ALL_(get<0>(s));
				if constexpr (group_multiplication_q<T0>) {return ((get<I>(s) /= get<I + 1>(s)),...);}
				else                                      {return ((get<I>(s) -= get<I + 1>(s)),...);}
			}	(bond::seek_reverse_s<size - 1>{});
			return self();
		}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
