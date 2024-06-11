#pragma once
#include "../any.cc"
#include "./any.hh"// testing...

#include "../occur/all.hh"



XTAL_ENV_(push)
namespace xtal::process::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::_test;


////////////////////////////////////////////////////////////////////////////////

struct square_root
{
	template <class S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	public:
		using S_::S_;

		template <auto ...>
		XTAL_DEF_(return,inline,static)
		XTAL_LET function(auto &&o)
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
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	public:
		using S_::S_;

		template <auto ...>
		XTAL_DEF_(return,inline,static)
		XTAL_LET function(auto &&o)
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
	using _op = bond::operating;
	using T_sigma = typename _op::sigma_t;
	using T_delta = typename _op::delta_t;
	using T_alpha = typename _op::alpha_t;

	TRY_("lifting")
	{
		auto const f = let_f([] (auto &&...xs) XTAL_0FN_(XTAL_REF_(xs) +...+ 0));
		TRUE_(10 == f.functor(1, 2, 3, 4));
		TRUE_(10 == f(1, 2, 3, 4));
		TRUE_(10 == f.refunctor() (1, 2, 3, 4));

	}
	TRY_("chaining")
	{
		using halve_square_root_t = reinferred_t<halve_t, square_root_t>;
		using square_root_halve_t = reinferred_t<square_root_t, halve_t>;
		
		TRUE_(2. == halve_square_root_t::function(16.));
		TRUE_(3. == square_root_halve_t::function(18.));

		TRUE_(2. == halve_square_root_t{}.functor(16.));
		TRUE_(3. == square_root_halve_t{}.functor(18.));

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
	using U_start = occur::reinferred_t<class start_a, Ordinal_t<0>>;

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
	using U_start = occur::reinferred_t<class start_a, Ordinal_t<0>>;

	auto &o = z.template head<onset_t>();
	TRUE_(-1 == (int) z.efflux(U_start()));                            // unrecognized
	TRUE_( 1 == (int) z.efflux(onset_t(0.0))); TRUE_(0.0 == (float) o);// unchanged
	TRUE_( 0 == (int) z.efflux(onset_t(1.0))); TRUE_(1.0 == (float) o);// changed
	TRUE_( 0 == (int) z.efflux(onset_t(2.0))); TRUE_(2.0 == (float) o);// changed
	TRUE_( 0 == (int) z.efflux(onset_t(3.0))); TRUE_(3.0 == (float) o);// changed
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));

}
TAG_("process", "occur")
{
	TRY_("influx operator (dynamic)") {process_provision__influx_operator(dynamic_onset_mix_t());}
	TRY_("efflux operator (dynamic)") {process_provision__efflux_operator(dynamic_onset_mix_t());}

	TRY_("influx operator (static)")  {process_provision__influx_operator( static_onset_mix_t());}
	TRY_("efflux operator (static)")  {process_provision__efflux_operator( static_onset_mix_t());}

	TRY_("influx functor (dynamic)") {process_provision__influx_method(dynamic_onset_mix_t());}
	TRY_("efflux functor (dynamic)") {process_provision__efflux_method(dynamic_onset_mix_t());}

	TRY_("influx functor (static)")  {process_provision__influx_method( static_onset_mix_t());}
	TRY_("efflux functor (static)")  {process_provision__efflux_method( static_onset_mix_t());}

}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
