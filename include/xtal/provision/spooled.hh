#pragma once
#include "./any.hh"
#include "../atom/all.hh"





XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   spooled;
template <typename ..._s> using    spooled_t = confined_t<spooled<_s...>>;
template <typename ..._s> concept  spooled_q = bond::tag_p<spooled, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides range-based priority-queuing. \

template <bond::compose_q A>
struct spooled<A>
{
	using superkind = bond::tag<spooled>;
	
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using spool_t = typename A::template subtype<U>;

	};
};
template <class A>
struct spooled<A>
{
	using superkind = bond::tag<spooled>;
	
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using spool_t = atom::queue_t<U[(unsigned) shaped<A>::size()]>;

	};
};
template <auto N> struct spooled<null_type[N]> : spooled<  size_constant_t< N>> {};///< Fluid-size, based on `store_t`.
template <auto N> struct spooled<unit_type[N]> : spooled<extent_constant_t< N>> {};///< Fixed-size, based on `block_t`.
template <      > struct spooled<            > : spooled<extent_constant_t<-1>> {};///< Fluid-size, based on `store_t` (default).


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
