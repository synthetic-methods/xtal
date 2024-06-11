#pragma once
#include "./any.hh"
#include "../atom/all.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP stored;
template <typename ..._s> XTAL_USE stored_t = confined_t<stored<_s...>>;
template <typename ..._s> XTAL_ASK stored_q = bond::head_tag_p<stored, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `atom::store`. \

template <bond::compose_q A>
struct stored<A>
{
	using subkind = bond::tag<stored>;
	
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
template <class A>
struct stored<A>
{
	static_assert(Integral_q<A>);
	using subkind = bond::tag<stored>;
	
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
template <class A> requires (0 <= A{} and A{} <= 0x1000)
struct stored<A>
{
	static_assert(Integral_q<A>);
	using subkind = bond::tag<stored>;
	
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
struct stored<>
:	stored<Integral_t<-1>>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
