#pragma once
#include "./any.hh"
#include "../atom/store.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP restate;
template <typename ..._s> XTAL_USE restate_t = confined_t<restate<_s...>>;
template <typename ..._s> XTAL_ASK restate_q = bond::tag_p<restate, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `atom::store`. \

template <bond::compose_q A>
struct restate<A>
{
	using subkind = bond::tag<restate>;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <iterated_q U>
		using serve_t = typename A::template subtype<U>;

	};
};
template <>
struct restate<>
{
	using subkind = bond::tag<restate>;
	
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
