#pragma once
#include "./any.cc"
#include "./argument.hh"// testing...





XTAL_ENV_(push)
namespace xtal::flow::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*/
TAG_("argument")
{
	TRY_("construct")
	{
		using U_source = conferred_t<counted_t<>>;
		using U_target = argument_s<U_source>;
		using V_target = argument_s<>;

		V_target t0(99);
		U_target t1(99, U_source(counted_t<>(11, 22)));

		TRUE_(99 == t0.template head<0>());
		TRUE_(99 == t1.template head<0>());
		TRUE_(equal_f(counted_t<>(11, 22), t1.tail()));

		TRUE_(same_q<decltype(XTAL_ANY_(U_target).head()), typename V_target::head_type>);
		TRUE_(same_q<decltype(XTAL_ANY_(U_target).tail()), U_source>);

	}
	auto constexpr maybe = [] (argument_s<> g)
	XTAL_0FN {
		if (g) {
			return true;
		}
		else {
			return false;
		}
	};
	
	TRY_("condition")
	{
		  TRUE_(maybe(argument_s<>(1)));
		UNTRUE_(maybe(argument_s<>(0)));
		UNTRUE_(maybe(argument_s<>( )));

	}
}

/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
