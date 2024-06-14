#pragma once
#include "./any.hh"
#include "../atom/all.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP stored;
template <typename ..._s> XTAL_USE stored_t = confined_t<stored<_s...>>;
template <typename ..._s> XTAL_REQ stored_q = bond::head_tag_p<stored, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `atom::store`. \

template <bond::compose_q A>
struct stored<A>
{
	using subkind = bond::tag<stored>;
	
	template <cell::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = typename A::template subtype<U>;

	};
};
template <size_t N>
struct stored<unit_t[N]>
{
	using subkind = bond::tag<stored>;
	
	template <cell::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = atom::block_t<U[N]>;

	};
};
template <unsigned N>
struct stored<null_t[N]>
{
	using subkind = bond::tag<stored>;
	
	template <cell::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = atom::store_t<U[(unsigned) N]>;

	};
};
template <nominal_q A>
struct stored<A>
{
	using subkind = bond::tag<stored>;
	
	template <cell::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = atom::store_t<U[(unsigned) A::value]>;

	};
};
//template <nominal_q U>
//struct stored<U>
//:	stored<null_t[(unsigned) U::value]>
//{
//};
template <>
struct stored<>
:	stored<nominal_t<-1>>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
