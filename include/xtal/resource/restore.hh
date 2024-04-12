#pragma once
#include "./any.hh"
#include "../atom/store.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  restore {};
template <class ...Ts> concept restore_q = bond::tag_p<restore, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `atom::store`. \

template <bond::compose_q A>
struct restore<A>
{
	using subkind = bond::tag<restore>;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = typename A::template subtype<U>;

	};
};
template <constant_q A>
struct restore<A>
{
	using subkind = bond::tag<restore>;
	
	template <_retail::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = atom::store_t<U[(unsigned) A{}]>;

	};
};
template <>
struct restore<>
:	restore<constant_t<~0U>>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
