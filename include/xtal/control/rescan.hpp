#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <counted_q U=counted_t<>>
struct rescan
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
	public:
		using co::co;
		
		XTAL_RE4_(XTAL_FN1 scan(XTAL_DEF... oo), co::head(XTAL_REF_(oo)...))

	};
};
template <typename U=counted_t<>>
using rescan_t = confined_t<rescan<U>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
