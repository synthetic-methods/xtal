#pragma once
#include "./any.cc"
#include "./equeue.hh"// testing...





XTAL_ENV_(push)
namespace xtal::atom::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <int N>
void equeue__operation()
{
	using U_event = bond::compose_s<onset_t, cell::conferred<int>>;
	using U_queue = equeue_t<U_event[N]>;
	U_queue q {(U_event) numeric_t<int>::max()};

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
TAG_("equeue")
{
	TRY_("operation fluid") {equeue__operation<00>();}
	TRY_("operation fixed") {equeue__operation<64>();}

}

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
