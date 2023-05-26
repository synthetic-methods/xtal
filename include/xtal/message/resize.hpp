#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U=iota_t>
struct resize
{
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
	public:
		using co::co;

		XTAL_RE4_(XTAL_FN1 size(XTAL_DEF... oo), co::head(XTAL_REF_(oo)...))

	};
};
template <iterated_q U>
struct resize<U>
:	resize<_v3::ranges::size_type_t<U>>
{};
template <typename U=iota_t>
using resize_t = confined_t<resize<U>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
