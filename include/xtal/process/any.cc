#pragma once
#include "../any.cc"
#include "./any.hh"// testing...

#include "../flow/all.hh"
#include "../occur/all.hh"


XTAL_ENV_(push)
namespace xtal::process::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::_test;


////////////////////////////////////////////////////////////////////////////////
/**/
struct subtract
{
	template <process::any_q S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	public:
		using S_::S_;

		template <auto ...>
		XTAL_DEF_(return,inline,let)
		method(auto &&x, auto &&y) const
		noexcept -> auto
		{
			return XTAL_REF_(x) - XTAL_REF_(y);
		}

	};
};
using subtract_t = process::confined_t<subtract>;
/***/
struct square_root
{
	template <process::any_q S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	public:
		using S_::S_;

		template <auto ...>
		XTAL_DEF_(return,inline,set)
		method_f(auto &&o)
		noexcept -> auto
		{
			return _std::sqrt(o);
		}

	};
};
using square_root_t = confined_t<square_root>;

struct halve
{
	template <process::any_q S>
	class subtype : public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	public:
		using S_::S_;

		template <auto ...>
		XTAL_DEF_(return,inline,set)
		method_f(auto &&o)
		noexcept -> auto
		{
			return o*0.5L;
		}

	};
};
using halve_t = confined_t<halve>;


////////////////////////////////////////////////////////////////////////////////
/**/
TAG_("process", "attach")
{
	using _fit = bond::fit<>;
	using T_sigma = typename _fit::sigma_type;
	using T_delta = typename _fit::delta_type;
	using T_alpha = typename _fit::alpha_type;

	using L01 = process::confined_t<typename Ox_level::template poll<0b01>>;
	using L10 = process::confined_t<typename Ox_level::template poll<0b10>>;

	TRY_("messaging")
	{
		subtract_t::bind_t<L01, L10> op{};

		op <<= flow::mark_s<Ox_level>(0b01, Ox_level{9});
		op <<= flow::mark_s<Ox_level>(0b10, Ox_level{1});
		TRUE_(8 == op());

		op <<= bond::pack_f(ordinal_constant_t<0>{}, _std::array<int, 0>{});
		op <<= bond::pack_f(ordinal_constant_t<0>{}, Ox_level{6});
		op <<= bond::pack_f(ordinal_constant_t<1>{}, Ox_level{3});
		TRUE_(3 == op());

	}
}

/***/
////////////////////////////////////////////////////////////////////////////////

TAG_("process", "construct")
{
	using _fit = bond::fit<>;
	using T_sigma = typename _fit::sigma_type;
	using T_delta = typename _fit::delta_type;
	using T_alpha = typename _fit::alpha_type;

	TRY_("lifting")
	{
		auto const f = process::let_f([] (auto &&...xs) XTAL_0FN_(to) (XTAL_REF_(xs) +...+ 0));
		TRUE_(10 == f.method(1, 2, 3, 4));
		TRUE_(10 == f(1, 2, 3, 4));
		TRUE_(10 == f.reify() (1, 2, 3, 4));

	}
	TRY_("chaining")
	{
		using halve_square_root_t = reinferred_t<halve_t, square_root_t>;
		using square_root_halve_t = reinferred_t<square_root_t, halve_t>;
		
		TRUE_(2. == halve_square_root_t::method_f(16.));
		TRUE_(3. == square_root_halve_t::method_f(18.));

		TRUE_(2. == halve_square_root_t{}.method(16.));
		TRUE_(3. == square_root_halve_t{}.method(18.));

	}
}


////////////////////////////////////////////////////////////////////////////////

void process_access__get(auto z)
{
	auto &o = z.template head<Ox_onset>();
	TRUE_(00.0 == (float) o);
	TRUE_(10.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
TAG_("process", "access")
{
	TRY_("get (dynamic)") {process_access__get(Px_dynamic_onset_mix());}
	TRY_("get (static)")  {process_access__get( Px_static_onset_mix());}

}

/***/
////////////////////////////////////////////////////////////////////////////////
/**/
void process_provision__influx_operator(auto z)
{
	auto &o = z.template head<Ox_onset>();
	z <<= Ox_onset(0.0); TRUE_(0.0 == (float) o);
	z <<= Ox_onset(1.0); TRUE_(1.0 == (float) o);
	z <<= Ox_onset(2.0); TRUE_(2.0 == (float) o);
	z <<= Ox_onset(3.0); TRUE_(3.0 == (float) o);
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
void process_provision__efflux_operator(auto z)
{
	auto &o = z.template head<Ox_onset>();
	z >>= Ox_onset(0.0); TRUE_(0.0 == (float) o);
	z >>= Ox_onset(1.0); TRUE_(1.0 == (float) o);
	z >>= Ox_onset(2.0); TRUE_(2.0 == (float) o);
	z >>= Ox_onset(3.0); TRUE_(3.0 == (float) o);
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
void process_provision__influx_method(auto z)
{
	using U_start = occur::reinferred_t<class start_a, constant_t<0>>;

	auto &o = z.template head<Ox_onset>();
	TRUE_(-1 == z.influx(U_start()));                            // unrecognized
	TRUE_( 1 == z.influx(Ox_onset(0.0))); TRUE_(0.0 == (float) o);// unchanged
	TRUE_( 0 == z.influx(Ox_onset(1.0))); TRUE_(1.0 == (float) o);// changed
	TRUE_( 0 == z.influx(Ox_onset(2.0))); TRUE_(2.0 == (float) o);// changed
	TRUE_( 0 == z.influx(Ox_onset(3.0))); TRUE_(3.0 == (float) o);// changed
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));
}
void process_provision__efflux_method(auto z)
{
	using U_start = occur::reinferred_t<class start_a, constant_t<0>>;

	auto &o = z.template head<Ox_onset>();
	TRUE_(-1 == z.efflux(U_start()));                            // unrecognized
	TRUE_( 1 == z.efflux(Ox_onset(0.0))); TRUE_(0.0 == (float) o);// unchanged
	TRUE_( 0 == z.efflux(Ox_onset(1.0))); TRUE_(1.0 == (float) o);// changed
	TRUE_( 0 == z.efflux(Ox_onset(2.0))); TRUE_(2.0 == (float) o);// changed
	TRUE_( 0 == z.efflux(Ox_onset(3.0))); TRUE_(3.0 == (float) o);// changed
	TRUE_(13.0 == (float) z(1.0, 2.0, 3.0, 4.0));

}
TAG_("process", "occur")
{
	TRY_("influx operator (dynamic)") {process_provision__influx_operator(Px_dynamic_onset_mix());}
	TRY_("efflux operator (dynamic)") {process_provision__efflux_operator(Px_dynamic_onset_mix());}

	TRY_("influx operator (static)")  {process_provision__influx_operator( Px_static_onset_mix());}
	TRY_("efflux operator (static)")  {process_provision__efflux_operator( Px_static_onset_mix());}

	TRY_("influx method (dynamic)") {process_provision__influx_method(Px_dynamic_onset_mix());}
	TRY_("efflux method (dynamic)") {process_provision__efflux_method(Px_dynamic_onset_mix());}

	TRY_("influx method (static)")  {process_provision__influx_method( Px_static_onset_mix());}
	TRY_("efflux method (static)")  {process_provision__efflux_method( Px_static_onset_mix());}

}

/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
