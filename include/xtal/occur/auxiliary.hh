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
template <class ..._s> struct  auxiliary   : bond::compose<auxiliary<_s>...> {};
template <class ..._s> using   auxiliary_t = cell::confined_t<auxiliary<_s...>>;


////////////////////////////////////////////////////////////////////////////////

template <>
struct auxiliary<>
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
struct auxiliary<T> : auxiliary<>
{
};
template <class ..._s>
struct auxiliary<bond::compose<_s...>> : auxiliary<_s...>
{
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
