#pragma once
#include "./any.hh"

#include "../atom/spool.hh"




XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Provides priority-queuing via `spool_t<value_type>` conforming to `atom::spool_t<>`.
*/
template <typename ..._s> struct   spooled;
template <typename ..._s> using    spooled_t = confined_t<spooled<_s...>>;
template <typename ..._s> concept  spooled_q = bond::tag_in_p<spooled, _s...>;


////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Provides a custom spool via `A::template subtype<value_type>`.
*/
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
/*!
\brief   Provides a resizable `atom::spool_t`.
*/
template <constant_q A>
struct spooled<A>
{
private:
	static auto constexpr M = XTAL_SYS_(extent, size_type);
	static auto constexpr N = M&A{}();

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
		
		/*!
		\brief  	Defines a resizable spool of predetermined-capacity with the given `value_type`.
		*/
		template <class U>
		using spool_t = atom::spool_t<U[N]>;

	};
	template <class S> requires (0 == N or  M == N)
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		/*!
		\brief  	Defines a resizable spool of  undetermined capacity with the given `value_type`.
		*/
		template <class U>
		using spool_t = atom::spool_t<U * >;

	};
};
template <auto N> struct spooled<null_type[N]> : spooled<extent_constant_t< N>> {};///< Provides a resizable `atom::spool_t` based on `atom::buffer_t`.
template <      > struct spooled<            > : spooled<extent_constant_t<-1>> {};///< Provides a resizable `atom::spool_t` based on `std::vector` (default).


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
