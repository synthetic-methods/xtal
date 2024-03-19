#pragma once
#include "./any.cc"
#include "./mark.ii"// testing...





XTAL_ENV_(push)
namespace xtal::cell::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("mark")
{
	TRY_("construct")
	{
		using U_source = cell::conferred_t<counted_t<>>;
		using U_target = mark_s<U_source>;
		using V_target = mark_s<>;

		V_target t0(99);
		U_target t1(99, U_source(counted_t<>(11, 22)));

		TRUE_(99 == t0.template head<0>());
		TRUE_(99 == t1.template head<0>());
		TRUE_(equal_f(counted_t<>(11, 22), t1.then()));

		TRUE_(is_q<XTAL_TYP_(XTAL_VAL_(U_target).head()), typename V_target::template head_t<>>);
		TRUE_(is_q<XTAL_TYP_(XTAL_VAL_(U_target).then()), U_source>);

	}
	auto constexpr maybe = [] (mark_s<> g)
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
		  TRUE_(maybe(mark_s<>(1)));
		UNTRUE_(maybe(mark_s<>(0)));
		UNTRUE_(maybe(mark_s<>( )));

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
