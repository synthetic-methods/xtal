#pragma once
#include "./any.hh"
#include "../arrange/all.hh"





XTAL_ENV_(push)
namespace xtal::resource
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP stored;
template <typename ..._s> XTAL_USE stored_t = confined_t<stored<_s...>>;
template <typename ..._s> XTAL_REQ stored_q = bond::any_tag_p<stored, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides a specialization of `arrange::store`. \

template <bond::compose_q A>
struct stored<A>
{
	using subkind = bond::tag<stored>;
	
	template <compound::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = typename A::template subtype<U>;

	};
};
template <size_type N>
struct stored<unit_type[N]>
{
	using subkind = bond::tag<stored>;
	
	template <compound::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = arrange::block_t<U[N]>;

	};
};
template <unsigned N>
struct stored<null_type[N]>
{
	using subkind = bond::tag<stored>;
	
	template <compound::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = arrange::store_t<U[(unsigned) N]>;

	};
};
template <nominal_q A>
struct stored<A>
{
	using subkind = bond::tag<stored>;
	
	template <compound::any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = arrange::store_t<U[(unsigned) A::value]>;

	};
};
//template <nominal_q U>
//struct stored<U>
//:	stored<null_type[(unsigned) U::value]>
//{
//};
template <>
struct stored<>
:	stored<nominal_t<-1>>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
