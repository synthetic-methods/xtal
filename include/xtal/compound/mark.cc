#pragma once
#include "./any.cc"
#include "./mark.ii"// testing...





XTAL_ENV_(push)
namespace xtal::compound::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("mark")
{
	TRY_("construct")
	{
		using source_t = compound::conferred_t<counted_t<>>;
		using target_t = mark_s<source_t>;
		using target_u = mark_s<>;

		target_u t0(99);
		target_t t1(99, source_t(counted_t<>(11, 22)));

		TRUE_(99 == t0.template head<0>());
		TRUE_(99 == t1.template head<0>());
		TRUE_(equal_f(counted_t<>(11, 22), t1.core()));

		TRUE_(is_q<XTAL_TYP_(XTAL_VAL_(target_t).head()), typename target_u::head_u>);
		TRUE_(is_q<XTAL_TYP_(XTAL_VAL_(target_t).core()), source_t>);

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
