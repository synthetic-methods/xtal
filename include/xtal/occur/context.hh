#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  context   : bond::compose<context<_s>...> {};
template <class ..._s> using   context_t = cell::confined_t<context<_s...>>;


////////////////////////////////////////////////////////////////////////////////

template <>
struct context<>
{
	template <class S>
	class subtype : public S
	{
	public:// CONSTRUCT
		using S::S;

		template <extent_type N_mask=1> struct   attach : bond::compose<> {};
		template <extent_type N_mask=1> struct dispatch : bond::compose<> {};
		
	};
	template <class S>
	requires requires {
		typename S::template   attach<1>;
		typename S::template dispatch<1>;
	}
	class subtype<S> : public S
	{
	public:// CONSTRUCT
		using S::S;

	};
};
template <class T>
struct context<T> : context<>
{
};
template <class ..._s>
struct context<bond::compose<_s...>> : context<_s...>
{
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
