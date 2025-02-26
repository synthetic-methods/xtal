#pragma once
#include "./any.hh"

//#include "../occur/review.hh"




XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   stated;
template <typename ..._s> using    stated_t = confined_t<stated<_s...>>;
template <typename ..._s> concept  stated_q = bond::tagged_with_p<stated, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a range-based view of the `store` via `state_t<iterated_q>`, \
which conforms to `reiterated_t` a.k.a. `ranges::subrange`. \

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
		//\
		using state_t = occur::review_t<U>;
		using state_t = reiterated_t<U>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
