#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U=iota_t>
struct recount
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
	public:
		using co::co;
		
		XTAL_RE4_(XTAL_FN1 count(XTAL_DEF... oo), co::head(XTAL_REF_(oo)...))

	};
};
template <typename U=iota_t>
using recount_t = confined_t<recount<U>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
