#pragma once
#include "./any.hh"
#include "../arrange/store.hh"

#include "../occur/review.hh"



XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP stated;
template <typename ..._s> XTAL_USE stated_t = confined_t<stated<_s...>>;
template <typename ..._s> XTAL_REQ stated_q = bond::any_tag_p<stated, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `arrange::store`. \

template <bond::compose_q A>
struct stated<A>
{
	using subkind = bond::tag<stated>;
	
	template <compound::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <iterated_q U>
		using state_t = typename A::template subtype<U>;

	};
};
template <>
struct stated<>
{
	using subkind = bond::tag<stated>;
	
	template <compound::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
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
