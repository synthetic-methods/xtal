#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Metaclass to support external parameter definition, querying,
         and `attach`/`dispatch`.
*/
template <class ..._s> struct  codex   : bond::compose<codex<_s>...> {};
template <class ..._s> using   codex_t = cell::confined_t<codex<_s...>>;


////////////////////////////////////////////////////////////////////////////////

template <>
struct codex<>
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
struct codex<T> : codex<>
{
};
template <class ..._s>
struct codex<bond::compose<_s...>> : codex<_s...>
{
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
