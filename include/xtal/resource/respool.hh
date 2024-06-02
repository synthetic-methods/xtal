#pragma once
#include "./any.hh"
#include "../atom/spool.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP respool;
template <typename ..._s> XTAL_USE respool_t = confined_t<respool<_s...>>;
template <typename ..._s> XTAL_ASK respool_q = bond::head_tag_p<respool, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `atom::spool`. \

template <bond::compose_q A>
struct respool<A>
{
	using subkind = bond::tag<respool>;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using spool_t = typename A::template subtype<U>;

	};
};
template <Integral_q A>
struct respool<A>
{
	using subkind = bond::tag<respool>;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using spool_t = atom::spool_t<U[(unsigned) A{}]>;

	};
};
template <>
struct respool<>
:	respool<Integral_t<-1>>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
