#pragma once
#include "./any.hh"
#include "../arrange/all.hh"





XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   stored;
template <typename ..._s> using    stored_t = confined_t<stored<_s...>>;
template <typename ..._s> concept  stored_q = bond::any_tag_p<stored, _s...>;


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
template <class A>
struct stored<A>
{
	using    value_type = valued_u<A>;
	XTAL_SET value      =  sized_n<A>;

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
		using store_t = arrange::block_t<U[(unsigned) value]>;

	};
	template <class S> requires _std::  signed_integral<value_type>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = arrange::store_t<U[(unsigned) value]>;

	};
};
template <auto N>
struct stored<unit_type[N]>
:	stored<constant_t<unsigned(N)>>
{
};
template <auto N>
struct stored<null_type[N]>
:	stored<constant_t<  signed(N)>>
{
};
template <>
struct stored<>
:	stored<constant_t<-1>>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
