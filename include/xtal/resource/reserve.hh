#pragma once
#include "./any.hh"
#include "../atom/store.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP reserve;
template <typename ..._s> XTAL_USE reserve_t = confined_t<reserve<_s...>>;
template <typename ..._s> XTAL_ASK reserve_q = bond::tag_p<reserve, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `atom::store`. \

template <bond::compose_q A>
struct reserve<A>
{
	using subkind = bond::tag<reserve>;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using serve_t = typename A::template subtype<U>;

	};
};
template <>
struct reserve<>
{
	using subkind = bond::tag<reserve>;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <iterated_q U>
		using serve_t = reiterated_t<U>;

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
