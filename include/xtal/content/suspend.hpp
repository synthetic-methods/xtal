#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::content
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U=iota_t>
struct suspend
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
	public:
		using co::co;
		using delay_t = U;

		XTAL_RE4_(XTAL_FN1 delay(XTAL_DEF... oo), co::head(XTAL_REF_(oo)...))

	};
};
template <typename U=iota_t>
using suspend_t = confined_t<suspend<U>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
