#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::content
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <iterated_q U>
struct render
{
   using buffer_t = U;
   using target_t = spanned_t<U>;

	using subkind = compose<confer<target_t>, defer<buffer_t>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;

		XTAL_NEW_(explicit) subtype(buffer_t const &o, XTAL_DEF ...oo)
		XTAL_0EX
		:	co(target_t(o), o, XTAL_REF_(oo)...)
		{
		}
		XTAL_NEW_(explicit) subtype(buffer_t &&o, XTAL_DEF ...oo)
		XTAL_0EX
		:	co(target_t(o), _std::move(o), XTAL_REF_(oo)...)
		{
		}

	public:
	//	using co::co;

		XTAL_CO2_(subtype);
		XTAL_CO4_(subtype);

		XTAL_NEW_(explicit) subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	subtype(buffer_t(), XTAL_REF_(oo)...)
		{
		}

		XTAL_RE4_(XTAL_FN1 target(XTAL_DEF... oo), co::template head<0>(XTAL_REF_(oo)...))
		XTAL_RE4_(XTAL_FN1 buffer(XTAL_DEF... oo), co::template head<1>(XTAL_REF_(oo)...))

	};
};
template <iterated_q U>
using render_t = confined_t<render<U>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
