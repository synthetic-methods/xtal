#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Applies the template to the `value_type` of the provided `subtype`.
*/
template <template <class> class T_>
struct wrap;

template <class U, template <class> class T_>
using wrap_s = bond::compose_s<U, wrap<T_>>;


////////////////////////////////////////////////////////////////////////////////

template <template <class> class T_>
struct wrap
{
	template <class U>
	class epitype
	{
	public:
		using type = T_<U>;

	};
	template <vector_q W>
	class epitype<W>
	{
		XTAL_DEF_(set) N = _xtd::       extent_v<W>;
		XTAL_TYP_(set) U = _xtd::remove_extent_t<W>;
		XTAL_TYP_(set) V = _std::remove_cvref_t<U>;
		XTAL_TYP_(set) T = _xtd::  qualify_cvref_t<W, T_<V>[N]>;

	public:
		using type = T;
	
	};

	template <class W>
	using subtype = typename epitype<W>::type;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
