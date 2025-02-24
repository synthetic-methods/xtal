#pragma once
#include "./any.hh"

#include "../atom/spool.hh"




XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   spooled;
template <typename ..._s> using    spooled_t = confined_t<spooled<_s...>>;
template <typename ..._s> concept  spooled_q = bond::any_tags_p<spooled, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides range-based priority-queuing via `spool_t<value_type>`, \
which conforms to the interface defined by `atom::spool_t<>`. \

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
private:
	static auto constexpr M = XTAL_SYS_(extent, size_type);
	static auto constexpr N = M&shaped<A>::extent();

public:
	using superkind = bond::tag<spooled>;
	
	template <class S>
	class subtype;

	template <class S> requires (0 != N and M != N)
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using spool_t = atom::spool_t<U[N]>;

	};
	template <class S> requires (0 == N or  M == N)
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using spool_t = atom::spool_t<U * >;

	};
};
template <auto N> struct spooled<null_type[N]> : spooled<extent_constant_t< N>> {};///< Fluid-size using `atom::buffer_t`.
template <      > struct spooled<            > : spooled<extent_constant_t<-1>> {};///< Fluid-size using `std::vector` (default).


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
