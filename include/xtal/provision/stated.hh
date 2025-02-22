#pragma once
#include "./any.hh"

//#include "../occur/review.hh"




XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Provides a random-access view via the member-type `state_t<store_type>`.
*/
template <typename ..._s> struct   stated;
template <typename ..._s> using    stated_t = confined_t<stated<_s...>>;
template <typename ..._s> concept  stated_q = bond::tag_in_p<stated, _s...>;


////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Provides a custom view via `A::template subtype<store_type>` conforming to `ranges::subrange`.
*/
template <bond::compose_q A>
struct stated<A>
{
	using superkind = bond::tag<stated>;
	
	template <cell::any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <iterated_q U>
		using state_t = typename A::template subtype<U>;

	};
};
/*!
\brief
Defines `state_t` via `reiterated_t` a.k.a. `ranges::subrange`.
*/
template <>
struct stated<>
{
	using superkind = bond::tag<stated>;
	
	template <cell::any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <iterated_q U>
		using state_t = reiterated_t<U>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
