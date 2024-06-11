#pragma once
#include "./any.hh"
#include "../atom/spool.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP spooled;
template <typename ..._s> XTAL_USE spooled_t = confined_t<spooled<_s...>>;
template <typename ..._s> XTAL_ASK spooled_q = bond::head_tag_p<spooled, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `atom::spool`. \

template <bond::compose_q A>
struct spooled<A>
{
	using subkind = bond::tag<spooled>;
	
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
template <nominal_q A>
struct spooled<A>
{
	using subkind = bond::tag<spooled>;
	
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
struct spooled<>
:	spooled<nominal_t<-1>>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
