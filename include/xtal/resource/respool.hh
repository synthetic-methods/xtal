#pragma once
#include "./any.hh"
#include "../atom/spool.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  respool {};
template <class ...Ts> concept respool_q = bond::tag_p<respool, Ts...>;


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
template <constant_q A>
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
:	respool<constant_t<~0U>>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
