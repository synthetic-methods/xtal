#pragma once
#include "./any.cc"
#include "./assign.hh"// testing...





XTAL_ENV_(push)
namespace xtal::flow::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("assign")
{
	TRY_("construct")
	{
		using U_source = flow::conferred_t<counted_t<>>;
		using U_target = assign_s<U_source>;
		using V_target = assign_s<>;

		V_target v_target(99);
		U_target u_target(99, U_source(counted_t<>(11, 22)));

		TRUE_(99 == v_target.template head<0>());
		TRUE_(99 == u_target.template head<0>());
		TRUE_(equal_f(counted_t<>(11, 22), u_target.tail()));

		TRUE_(same_q<decltype(XTAL_ANY_(U_target).head()), typename V_target::head_type>);
		TRUE_(same_q<decltype(XTAL_ANY_(U_target).tail()), U_source>);

	}
}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
