#pragma once
#include "./any.hh"
#include "../atom/all.hh"





XTAL_ENV_(push)
namespace xtal::provision
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Provides random-access storage via the member-type `store_t<value_type>`.
*/
template <typename ..._s> struct   stored;
template <typename ..._s> using    stored_t = confined_t<stored<_s...>>;
template <typename ..._s> concept  stored_q = bond::tag_in_p<stored, _s...>;


////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Provides custom storage via `A::template subtype<value_type>`.
*/
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
		
		/*!
		\brief  	Defines a collection of unknown capacity with the given `value_type`.
		*/
		template <class U>
		using store_t = bond::compose_s<U, A>;

	};
};
/*!
\brief
Provides either `std::vector`-like or `std::array`-like storage,
depending on whether `A::value` is signed or unsigned, respectively.
*/
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

	template <class S> requires (0 != N and M != N) and cardinal_q<typename fluid<A>::value_type>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		/*!
		\brief  	Defines a non-resizable collection of predetermined-capacity with the given `value_type`.
		*/
		template <class U>
		using store_t = atom:: block_t<U[N]>;

	};
	template <class S> requires (0 != N and M != N) and  ordinal_q<typename fluid<A>::value_type>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		/*!
		\brief  	Defines a     resizable collection of predetermined-capacity with the given `value_type`.
		*/
		template <class U>
		using store_t = atom::buffer_t<U[N]>;

	};
	template <class S> requires (0 == N or  M == N) and  ordinal_q<typename fluid<A>::value_type>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		
	public:
		using S_::S_;
		
		/*!
		\brief  	Defines a     resizable collection of  undetermined capacity with the given `value_type`.
		*/
		template <class U>
		using store_t = atom::buffer_t<U * >;

	};
};
template <auto N> struct stored<unit_type[N]> : stored<  size_constant_t< N>> {};///< Provides unresizable storage using `atom::block_t`.
template <auto N> struct stored<null_type[N]> : stored<extent_constant_t< N>> {};///< Provides   resizable storage using `atom::buffer_t`.
template <      > struct stored<            > : stored<extent_constant_t<-1>> {};///< Provides   resizable storage using `std::vector` (default).


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
