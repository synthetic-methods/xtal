#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  traits   : bond::compose<traits<_s>...> {};
template <class ..._s> using   traits_t = cell::confined_t<traits<_s...>>;


////////////////////////////////////////////////////////////////////////////////

template <>
struct traits<>
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
struct traits<T> : traits<>
{
};
template <class ..._s>
struct traits<bond::compose<_s...>> : traits<_s...>
{
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
