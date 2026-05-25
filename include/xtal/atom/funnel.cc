#pragma once
#include "./any.cc"
#include "./funnel.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*/
template <int N>
void funnel__operation()
{
	using U_event = bond::compose_s<Ox_onset, cell::conferred<int>>;
	using U_funnel = funnel_t<U_event[N]>;
	U_funnel q {bond::seek_in_t<>{}
	,	(U_event) std::numeric_limits<int>::max()
	};

	auto e1 = U_event(1, Ox_onset(11));
	auto e2 = U_event(2, Ox_onset(22));
	
	TRUE_(1 == e1.head()); TRUE_(11 == e1.tail());
	TRUE_(2 == e2.head()); TRUE_(22 == e2.tail());
	TRUE_(e1 < e2);
	TRUE_(0 == q.size());

	q.push(e1); TRUE_(1 == q.size());
	q.push(e2); TRUE_(2 == q.size());

	TRUE_(11 == q.begin()->tail()); q.advance(1); TRUE_(1 == q.size());
	TRUE_(22 == q.begin()->tail()); q.advance(1); TRUE_(0 == q.size());

}
TAG_("funnel")
{
	TRY_("operation fluid") {funnel__operation<00>();}
	TRY_("operation fixed") {funnel__operation<64>();}

}
/***/

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
