#pragma once
#include "./any.hh"
#include "../atom/all.hh"





XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct   stored;
template <typename ..._s> using    stored_t = confined_t<stored<_s...>>;
template <typename ..._s> concept  stored_q = bond::tagged_with_p<stored, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Provides random-access range-based storage via `store_t<value_type>`. \
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
template <constant_q A>
struct stored<A>
{
private:
	static auto constexpr M = XTAL_SYS_(extent, size_type);
	static auto constexpr N = M&A{}();

public:
	using superkind = bond::tag<stored>;
	
	template <class S>
	class subtype;

	template <class S> requires (0 != N and M != N) and cardinal_q<valued_u<A>>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = atom:: block_t<U[N]>;

	};
	template <class S> requires (0 != N and M != N) and  ordinal_q<valued_u<A>>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = atom::buffer_t<U[N]>;

	};
	template <class S> requires (0 == N or  M == N) and  ordinal_q<valued_u<A>>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		template <class U>
		using store_t = atom::buffer_t<U * >;

	};
};
template <auto N> struct stored<unit_type[N]> : stored<  size_constant_t< N>> {};///< Fixed-size using `atom:: block_t`.
template <auto N> struct stored<null_type[N]> : stored<extent_constant_t< N>> {};///< Fluid-size using `atom::buffer_t`.
template <      > struct stored<            > : stored<extent_constant_t<-1>> {};///< Fluid-size using `std::vector` (default).


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
