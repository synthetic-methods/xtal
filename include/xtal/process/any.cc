#pragma once
#include "../any.cc"
#include "./any.ii"// testing...

#include "../message/all.ii"



XTAL_ENV_(push)
namespace xtal::process::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__test;


////////////////////////////////////////////////////////////////////////////////

TAG_("process", "construct")
{
	TRY_("lifting")
	{
		auto const f = let_f([] (XTAL_DEF... xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
		TRUE_(10 == f.method(1, 2, 3, 4));
		TRUE_(10 == f(1, 2, 3, 4));
		TRUE_(10 == f.reify() (1, 2, 3, 4));

	}
}


////////////////////////////////////////////////////////////////////////////////

void process_access__get(auto z)
{
	auto &o = z.template head<onset_t>();
	TRUE_(00.0 == (float) o);
	TRUE_(10.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TAG_("process", "access")
{
	TRY_("get (dynamic)") {process_access__get(dynamic_onset_mix_t());}
	TRY_("get (static)")  {process_access__get( static_onset_mix_t());}

}


////////////////////////////////////////////////////////////////////////////////

void process_control__influx_operator(auto z)
{
	auto &o = z.template head<onset_t>();
	z <<= onset_t(0.0); TRUE_(0.0 == (float) o);
	z <<= onset_t(1.0); TRUE_(1.0 == (float) o);
	z <<= onset_t(2.0); TRUE_(2.0 == (float) o);
	z <<= onset_t(3.0); TRUE_(3.0 == (float) o);
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
void process_control__efflux_operator(auto z)
{
	auto &o = z.template head<onset_t>();
	z >>= onset_t(0.0); TRUE_(0.0 == (float) o);
	z >>= onset_t(1.0); TRUE_(1.0 == (float) o);
	z >>= onset_t(2.0); TRUE_(2.0 == (float) o);
	z >>= onset_t(3.0); TRUE_(3.0 == (float) o);
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
void process_control__influx_method(auto z)
{
	using start_t = message::label_t<ordinal_t<0>, struct T_start>;

	auto &o = z.template head<onset_t>();
	TRUE_(-1 == (int) z.influx(start_t()));                            // unrecognized
	TRUE_( 1 == (int) z.influx(onset_t(0.0))); TRUE_(0.0 == (float) o);// unchanged
	TRUE_( 0 == (int) z.influx(onset_t(1.0))); TRUE_(1.0 == (float) o);// changed
	TRUE_( 0 == (int) z.influx(onset_t(2.0))); TRUE_(2.0 == (float) o);// changed
	TRUE_( 0 == (int) z.influx(onset_t(3.0))); TRUE_(3.0 == (float) o);// changed
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
void process_control__efflux_method(auto z)
{
	using start_t = message::label_t<ordinal_t<0>, struct T_start>;

	auto &o = z.template head<onset_t>();
	TRUE_(-1 == (int) z.efflux(start_t()));                            // unrecognized
	TRUE_( 1 == (int) z.efflux(onset_t(0.0))); TRUE_(0.0 == (float) o);// unchanged
	TRUE_( 0 == (int) z.efflux(onset_t(1.0))); TRUE_(1.0 == (float) o);// changed
	TRUE_( 0 == (int) z.efflux(onset_t(2.0))); TRUE_(2.0 == (float) o);// changed
	TRUE_( 0 == (int) z.efflux(onset_t(3.0))); TRUE_(3.0 == (float) o);// changed
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));

}
TAG_("process", "message")
{
	TRY_("influx operator (dynamic)") {process_control__influx_operator(dynamic_onset_mix_t());}
	TRY_("efflux operator (dynamic)") {process_control__efflux_operator(dynamic_onset_mix_t());}

	TRY_("influx operator (static)")  {process_control__influx_operator( static_onset_mix_t());}
	TRY_("efflux operator (static)")  {process_control__efflux_operator( static_onset_mix_t());}

	TRY_("influx method (dynamic)") {process_control__influx_method(dynamic_onset_mix_t());}
	TRY_("efflux method (dynamic)") {process_control__efflux_method(dynamic_onset_mix_t());}

	TRY_("influx method (static)")  {process_control__influx_method( static_onset_mix_t());}
	TRY_("efflux method (static)")  {process_control__efflux_method( static_onset_mix_t());}

}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
