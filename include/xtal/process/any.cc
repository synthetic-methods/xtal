#pragma once
#include "../any.cc"
#include "./any.ii"// testing...

#include "../message/all.ii"



XTAL_ENV_(push)
namespace xtal::process::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::_test;


////////////////////////////////////////////////////////////////////////////////

struct square_root
{
	template <class S>
	class subtype: public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	public:
		using S_::S_;

		template <auto ...>
		XTAL_FN2 function(auto &&o)
		XTAL_0EX
		{
			return _std::sqrt(o);
		}

	};
};
using square_root_t = confined_t<square_root>;

struct halve
{
	template <class S>
	class subtype: public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	public:
		using S_::S_;

		template <auto ...>
		XTAL_FN2 function(auto &&o)
		XTAL_0EX
		{
			return o*0.5L;
		}

	};
};
using halve_t = confined_t<halve>;


////////////////////////////////////////////////////////////////////////////////

TAG_("process", "construct")
{
	using re = bond::realized;
	using T_sigma = typename re::sigma_t;
	using T_delta = typename re::delta_t;
	using T_alpha = typename re::alpha_t;

	TRY_("lifting")
	{
		auto const f = let_f([] (auto &&...xs) XTAL_0FN_(XTAL_FWD_(xs) +...+ 0));
		TRUE_(10 == f.method(1, 2, 3, 4));
		TRUE_(10 == f(1, 2, 3, 4));
		TRUE_(10 == f.reify() (1, 2, 3, 4));

	}
	TRY_("chaining")
	{
		using halve_square_root_t = lifted_t<halve_t, square_root_t>;
		using square_root_halve_t = lifted_t<square_root_t, halve_t>;
		
		TRUE_(2L == halve_square_root_t::function(16L));
		TRUE_(3L == square_root_halve_t::function(18L));

		TRUE_(2L == halve_square_root_t {}.method(16L));
		TRUE_(3L == square_root_halve_t {}.method(18L));

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

void process_provision__influx_operator(auto z)
{
	auto &o = z.template head<onset_t>();
	z <<= onset_t(0.0); TRUE_(0.0 == (float) o);
	z <<= onset_t(1.0); TRUE_(1.0 == (float) o);
	z <<= onset_t(2.0); TRUE_(2.0 == (float) o);
	z <<= onset_t(3.0); TRUE_(3.0 == (float) o);
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
void process_provision__efflux_operator(auto z)
{
	auto &o = z.template head<onset_t>();
	z >>= onset_t(0.0); TRUE_(0.0 == (float) o);
	z >>= onset_t(1.0); TRUE_(1.0 == (float) o);
	z >>= onset_t(2.0); TRUE_(2.0 == (float) o);
	z >>= onset_t(3.0); TRUE_(3.0 == (float) o);
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
void process_provision__influx_method(auto z)
{
	using U_start = message::lifted_t<class start_a, ordinal_t<0>>;

	auto &o = z.template head<onset_t>();
	TRUE_(-1 == (int) z.influx(U_start()));                            // unrecognized
	TRUE_( 1 == (int) z.influx(onset_t(0.0))); TRUE_(0.0 == (float) o);// unchanged
	TRUE_( 0 == (int) z.influx(onset_t(1.0))); TRUE_(1.0 == (float) o);// changed
	TRUE_( 0 == (int) z.influx(onset_t(2.0))); TRUE_(2.0 == (float) o);// changed
	TRUE_( 0 == (int) z.influx(onset_t(3.0))); TRUE_(3.0 == (float) o);// changed
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
void process_provision__efflux_method(auto z)
{
	using U_start = message::lifted_t<class start_a, ordinal_t<0>>;

	auto &o = z.template head<onset_t>();
	TRUE_(-1 == (int) z.efflux(U_start()));                            // unrecognized
	TRUE_( 1 == (int) z.efflux(onset_t(0.0))); TRUE_(0.0 == (float) o);// unchanged
	TRUE_( 0 == (int) z.efflux(onset_t(1.0))); TRUE_(1.0 == (float) o);// changed
	TRUE_( 0 == (int) z.efflux(onset_t(2.0))); TRUE_(2.0 == (float) o);// changed
	TRUE_( 0 == (int) z.efflux(onset_t(3.0))); TRUE_(3.0 == (float) o);// changed
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));

}
TAG_("process", "message")
{
	TRY_("influx operator (dynamic)") {process_provision__influx_operator(dynamic_onset_mix_t());}
	TRY_("efflux operator (dynamic)") {process_provision__efflux_operator(dynamic_onset_mix_t());}

	TRY_("influx operator (static)")  {process_provision__influx_operator( static_onset_mix_t());}
	TRY_("efflux operator (static)")  {process_provision__efflux_operator( static_onset_mix_t());}

	TRY_("influx method (dynamic)") {process_provision__influx_method(dynamic_onset_mix_t());}
	TRY_("efflux method (dynamic)") {process_provision__efflux_method(dynamic_onset_mix_t());}

	TRY_("influx method (static)")  {process_provision__influx_method( static_onset_mix_t());}
	TRY_("efflux method (static)")  {process_provision__efflux_method( static_onset_mix_t());}

}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
