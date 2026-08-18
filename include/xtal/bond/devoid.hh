#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Removes `incomplete_q<Us...>` before applying `Y`.
*/
template <template <class ...> class Y>
struct  devoid;

template <template <class ...> class Y, class ...Us>
using   devoid_s = typename devoid<Y>::template type<Us...>;


////////////////////////////////////////////////////////////////////////////////

template <template <class ...> class Y>
struct devoid
{
	template <                 class ...Us>
	struct endotype;

	template < incomplete_q U, class ...Us> requires in_v<complete_q<Us...>>
	struct endotype<U, Us...>
	:	           Y<   Us...>
	{
	};
	template < incomplete_q U, class ...Us> requires un_v<complete_q<Us...>>
	struct endotype<U, Us...>
	:	    endotype<   Us...>
	{
	};
	template <   complete_q U, class ...Us> requires in_v<complete_q<Us...>>
	struct endotype<U, Us...>
	:	           Y<U, Us...>
	{
	};
	template <   complete_q U, class ...Us> requires un_v<complete_q<Us...>>
	struct endotype<U, Us...>
	:	    endotype<Us..., U>
	{
	};
	template <class ...Us>
	using type = endotype<Us..., void>;

};



////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
