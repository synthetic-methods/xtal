#pragma once
#include "./any.hh"
#include "../atom/all.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP restore;
template <typename ..._s> XTAL_USE restore_t = confined_t<restore<_s...>>;
template <typename ..._s> XTAL_ASK restore_q = bond::head_tag_p<restore, _s...>;


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
template <Integral_q A>// requires (A{} <  0 or 0x1000 <  A{})
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
/*/
template <Integral_q A> requires (0 <= A{} and A{} <= 0x1000)
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
		using store_t = atom::block_t<U[(unsigned) A{}]>;

	};
};
/***/
template <>
struct restore<>
:	restore<Integral_t<-1>>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
