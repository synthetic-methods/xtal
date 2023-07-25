#pragma once
#include "./anybody.hpp"






XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_NYM respan;
template <typename ..._s> XTAL_ASK respan_q = tag_p<respan, _s...>;
template <iterated_q   U> XTAL_USE respan_t = confined_t<refer<U>, respan<U>, tag<respan>>;

template <iterated_q U>
struct respan<U>
{
private:
	using V = distance_t<U>;

public:
	using subkind = defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
	//	using S_::S_;
		using S_::self;
		using S_::twin;
		using S_::head;
		
		using span_t = U;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);

		template <iterated_q W>
		XTAL_CXN subtype(W &&w, XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(deranged_t<W>(XTAL_REF_(w)), XTAL_REF_(oo)...)
		{}

		XTAL_TO4_(XTAL_FN2 span(XTAL_DEF... oo), head(XTAL_REF_(oo)...))
		XTAL_TO4_(XTAL_FN2 size(), head().size())

		XTAL_FN2 slice(XTAL_DEF_(counted_q) w)
		XTAL_0FX
		{
			auto i = w.front(), j = w.back() + 1;
			auto t = twin(); (void) t.span(t.span()|_v3::views::slice(i, j)); return t;
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
