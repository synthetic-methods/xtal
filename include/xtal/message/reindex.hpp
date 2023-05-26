#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U=iota_t>
struct reindex
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
	public:
		using co::co;

		XTAL_RE4_(XTAL_FN1 index(XTAL_DEF... oo), co::head(XTAL_REF_(oo)...))

	};
};
template <typename U=iota_t>
using reindex_t = confined_t<reindex<U>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
