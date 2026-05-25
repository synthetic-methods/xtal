#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Metaclass to support external parameter definition, querying,
         and `attach`/`dispatch`.
*/
template <class ..._s> struct  occurrence   : bond::compose<occurrence<_s>...> {};
template <class ..._s> using   occurrence_t = cell::confined_t<occurrence<_s...>>;


////////////////////////////////////////////////////////////////////////////////

template <>
struct occurrence<>
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
struct occurrence<T> : occurrence<>
{
};
template <class ..._s>
struct occurrence<bond::compose<_s...>> : occurrence<_s...>
{
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
