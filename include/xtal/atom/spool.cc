#pragma once
#include "./any.cc"
#include "./spool.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <int N>
void spool__operation()
{
	using U_event = bond::compose_s<onset_t, cell::conferred<int>>;
	using U_queue = spool_t<U_event[N]>;
	U_queue q {(U_event) _std::numeric_limits<int>::max()};

	auto e1 = U_event(1, onset_t(-1.0));
	auto e2 = U_event(2, onset_t(-2.0));
	TRUE_(e1 < e2);
	TRUE_(2 == e2.head());
	TRUE_(1 == e1.head());
	
	TRUE_(0 == q.size());
	q.push(e1); TRUE_(1 == q.size());
	q.push(e2); TRUE_(2 == q.size());
	TRUE_(-1.0 == q.begin()->then()); q.advance(1); TRUE_(1 == q.size());
	TRUE_(-2.0 == q.begin()->then()); q.advance(1); TRUE_(0 == q.size());

}
TAG_("spool")
{
	TRY_("operation fluid") {spool__operation<00>();}
	TRY_("operation fixed") {spool__operation<64>();}

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
