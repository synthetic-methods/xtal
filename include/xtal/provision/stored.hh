#pragma once
#include "./any.hh"
#include "../atom/all.hh"





XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   stored;
template <typename ..._s> using    stored_t = confined_t<stored<_s...>>;
template <typename ..._s> concept  stored_q = bond::tag_p<stored, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides random-access range-based storage via the member-type `store_t<element_type>`. \
It may either be defined using the supplied decorator, \
or if `A` is an `unsigned` or `signed` constant, \
the store will be defined by `atom::block` or `atom::buffer`, respectively. \

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
	using superkind = bond::tag<stored>;
	
	template <class S>
	class subtype;

	template <class S> requires cardinal_q<valued_u<A>>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = atom:: block_t<U[(unsigned) shaped<A>::size()]>;

	};
	template <class S> requires  ordinal_q<valued_u<A>>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = atom::buffer_t<U[(unsigned) shaped<A>::size()]>;

	};
};
template <auto N> struct stored<unit_type[N]> : stored<constant_t<unsigned(N)>> {};///< Fixed-size, based on `block_t`.
template <auto N> struct stored<null_type[N]> : stored<constant_t<  signed(N)>> {};///< Fluid-size, based on `store_t`.
template <      > struct stored<            > : stored<constant_t<        -1 >> {};///< Fluid-size, based on `store_t` (default).


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
