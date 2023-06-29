#pragma once
#include "../concord/any.hpp"// `_retail`






XTAL_ENV_(push)
namespace xtal::conflux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::concord;
#include "../concord/any.hxx"


////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct define
{
	using subkind = _retail::define<T>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		friend T;
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using co::self;

		///\
		Influx operator: resolves the message for `this` before any dependencies, \
		used for e.g. `message::resize`. \

		XTAL_OP1 <<=(XTAL_DEF o)
		XTAL_0EX
		{
			(void) self().influx(XTAL_REF_(o));
			return self();
		}
		XTAL_OP1 <<=(XTAL_DEF_(bundle_q) o)
		XTAL_0EX
		{
			(void) _std::apply([this](XTAL_DEF ...oo)
				XTAL_0FN_(self().influx(XTAL_REF_(oo)...)),
				XTAL_REF_(o)
			);
			return self();
		}
		///\
		Influx handler: resolves the message for `this` before any dependencies. \
		
		///\returns the result of `infuse` applied to the first argument \
		`&` `influx` applied to the remaining arguments. \

		XTAL_FNX influx(XTAL_DEF o, XTAL_DEF ...oo)
		XTAL_0EX
		{
			return XTAL_FLX_(self().influx(oo...)) (self().infuse(XTAL_REF_(o)));
		}
		XTAL_FNX influx(null_t, XTAL_DEF ...oo)
		XTAL_0EX
		{
		//	return self().influx(XTAL_REF_(oo)...);
			return influx();
		}
		XTAL_FNX influx()
		XTAL_0EX
		{
			return -1;
		}


		///\
		Efflux operator: resolves the message for any dependencies before `this`, \
		used for e.g. `message::respan` and `message::sequel`. \

		XTAL_OP1 >>=(XTAL_DEF o)
		XTAL_0EX
		{
			(void) self().efflux(XTAL_REF_(o));
			return self();
		}
		XTAL_OP1 >>=(XTAL_DEF_(bundle_q) o)
		XTAL_0EX
		{
			(void) _std::apply([this](XTAL_DEF ...oo)
				XTAL_0FN_(self().efflux(XTAL_REF_(oo)...)),
				XTAL_REF_(o)
			);
			return self();
		}
		///\
		Efflux handler: resolves the message for any dependencies before `this`. \
		
		///\returns the result of `effuse` applied to the first argument \
		`&` `efflux` applied to the remaining arguments. \

		XTAL_FNX efflux(XTAL_DEF o, XTAL_DEF ...oo)
		XTAL_0EX
		{
			return XTAL_FLX_(self().efflux(oo...)) (self().effuse(XTAL_REF_(o)));
		}
		XTAL_FNX efflux(null_t, XTAL_DEF ...oo)
		XTAL_0EX
		{
		//	return self().efflux(XTAL_REF_(oo)...);
			return efflux();
		}
		XTAL_FNX efflux()
		XTAL_0EX
		{
			return -1;
		}


		///\
		Defuse handler: resolves the individual components of the message. \
		
		///\returns a ternary integer indicating that the state has changed (`0`), \
		remains unchanged (`1`), or that the message was unrecognized (`-1`). \
		
		///\note\
		The return values are accumulated using `&`, with a default of `-1` and limit of `0`, \
		and truncating propagation when the aggregated result is `1`. \

		XTAL_FNX defuse(XTAL_DEF o)
		XTAL_0EX
		{
			return -1;
		}
		XTAL_FNX effuse(XTAL_DEF o) XTAL_0EX {return self().defuse(XTAL_REF_(o));}
		///\< \see `defuse`. \

		XTAL_FNX infuse(XTAL_DEF o) XTAL_0EX {return self().defuse(XTAL_REF_(o));}
		///\< \see `defuse`. \
		

	};
};
template <typename T>
struct refine
:	_retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////

template <typename U>
struct defer
{
	using subkind = _retail::defer<U>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;
		using co::self;
		using co::head;

		///\note\
		Influxes `this`, then the proxied value if supported.

		XTAL_FNX influx(XTAL_DEF ...oo)
		XTAL_0EX
		XTAL_IF1 any_p<U>
		{
			return XTAL_FLX_(head().influx(oo...)) (co::influx(XTAL_REF_(oo)...));
		}
		XTAL_FNX influx(XTAL_DEF ...oo)
		XTAL_0EX
		{
			return co::influx(XTAL_REF_(oo)...);
		}

		///\note\
		Effluxes the proxied value if supported, then `this`.

		XTAL_FNX efflux(XTAL_DEF ...oo)
		XTAL_0EX
		XTAL_IF1 any_p<U>
		{
			return XTAL_FLX_(co::efflux(oo...)) (head().efflux(XTAL_REF_(oo)...));
		}
		XTAL_FNX efflux(XTAL_DEF ...oo)
		XTAL_0EX
		{
			return co::efflux(XTAL_REF_(oo)...);
		}

		///\note\
		Assigns the given value `u` if it matches the proxied type `U`. \

		XTAL_FNX defuse(U u)
		XTAL_0EX
		{
			return co::has(u) or (co::head(u), 0);
		}
		XTAL_FNX defuse(XTAL_DEF w)
		XTAL_0EX
		{
			return co::defuse(XTAL_REF_(w));
		}

	};
};
template <typename U>
struct refer
:	_retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
