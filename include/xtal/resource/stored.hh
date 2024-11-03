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
	using superkind = bond::tag<stored>;
	
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = typename A::template subtype<U>;

	};
};
template <nominal_q A>
struct stored<A>
{
	XTAL_USE value_type =  typename  A::value_type;
	XTAL_SET value      = (unsigned) A{};

	using superkind = bond::tag<stored>;
	
	template <class S>
	class subtype;
	
	template <class S> requires _std::unsigned_integral<value_type>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = arrange::block_t<U[value]>;

	};
	template <class S> requires _std::  signed_integral<value_type>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = arrange::store_t<U[value]>;

	};
};
template <auto N>
struct stored<unit_type[N]>
:	stored<nominal_t<unsigned(N)>>
{
};
template <auto N>
struct stored<null_type[N]>
:	stored<nominal_t<  signed(N)>>
{
};
template <>
struct stored<>
:	stored<nominal_t<-1>>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
