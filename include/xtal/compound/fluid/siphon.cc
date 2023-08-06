#pragma once
#include "./any.cc"
#include "./siphon.ii"// testing...





XTAL_ENV_(push)
namespace xtal::compound::fluid::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <int N>
void siphon__operation()
{
	using event_u = compose_s<onset_t, concord::conferred<int>>;
	using queue_u = fluid::siphon_t<event_u[N]>;
	queue_u q {(event_u) _std::numeric_limits<int>::max()};

	auto e1 = event_u(1, onset_t(-1.0));
	auto e2 = event_u(2, onset_t(-2.0));
	TRUE_(e1 < e2);
	TRUE_(2 == e2.valve());
	TRUE_(1 == e1.valve());
	
	TRUE_(0 == q.size());
	q.push(e1); TRUE_(1 == q.size());
	q.push(e2); TRUE_(2 == q.size());
	TRUE_(-1.0 == q.peek().core()); q.advance(1); TRUE_(1 == q.size());
	TRUE_(-2.0 == q.peek().core()); q.advance(1); TRUE_(0 == q.size());

}
TAG_("siphon")
{
	TRY_("operation fluid") {siphon__operation<00>();}
	TRY_("operation fixed") {siphon__operation<64>();}

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
