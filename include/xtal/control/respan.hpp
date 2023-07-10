#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <iterated_q U>
struct respan
{
private:
	using V = distance_t<U>;

public:
	using subkind = defer<U>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
	//	using S_::S_;
		using S_::self;
		using span_t = U;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);

		template <iterated_q W>
		XTAL_CXN subtype(W &&w, XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(deranged_t<W>(XTAL_REF_(w)), XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(XTAL_FN2 span(XTAL_DEF... oo), S_::head(XTAL_REF_(oo)...))
		XTAL_TO4_(XTAL_FN2 size(), S_::head().size())

		XTAL_FN2 slice(XTAL_DEF_(counted_q) w)
		XTAL_0FX
		{
			auto i = w.front(), j = w.back() + 1;
			auto t = self(); (void) t.span(t.span()|_v3::views::slice(i, j)); return t;
		}

	};
};
template <iterated_q U>
using respan_t = confined_t<respan<U>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
