#pragma once
#include "../content/any.hpp"//_detail






XTAL_ENV_(push)
namespace xtal::context
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail = xtal::content;
#include "../common/any.ipp"

////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct define
{
	using subkind = _detail::define<T>;

	template <any_q S>
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

			return operator<<=(bundle_fwd(XTAL_REF_(o)));
		}
		XTAL_OP1 <<=(XTAL_DEF_(bundle_q) o)
		XTAL_0EX
		{
			(void) _std::apply([this] (XTAL_DEF ...oo) XTAL_0FN_(self().influx(XTAL_REF_(oo)...)), XTAL_REF_(o));
			return self();
		}
		///\
		Influx handler: resolves the message for `this` before any dependencies. \
		
		///\
		\returns the result of `infuse` applied to the first argument \
		`&` `influx` applied to the remaining arguments. \

		XTAL_FN2_(flux_t) influx(XTAL_DEF o, XTAL_DEF ...oo)
		XTAL_0EX
		{
			flux_t const _ = self().infuse(XTAL_REF_(o));
			return !_?0: _ & self().influx(XTAL_REF_(oo)...);
		}
		XTAL_FN2_(flux_t) influx(nothing_t, XTAL_DEF ...oo)
		XTAL_0EX
		{
		//	return self().influx(XTAL_REF_(oo)...);
			return influx();
		}
		XTAL_FN2_(flux_t) influx()
		XTAL_0EX
		{
			return -1;
		}


		///\
		Efflux operator: resolves the message for any dependencies before `this`, \
		used for e.g. `message::respan` and `message::serial`. \

		XTAL_OP1 >>=(XTAL_DEF o)
		XTAL_0EX
		{
			(void) self().efflux(XTAL_REF_(o));
			return self();
		}
		XTAL_OP1 >>=(XTAL_DEF_(bundle_q) o)
		XTAL_0EX
		{
			(void) _std::apply([this] (XTAL_DEF ...oo) XTAL_0FN_(self().efflux(XTAL_REF_(oo)...)), XTAL_REF_(o));
			return self();
		}
		///\
		Efflux handler: resolves the message for any dependencies before `this`. \
		
		///\
		\returns the result of `effuse` applied to the first argument \
		`&` `efflux` applied to the remaining arguments. \

		XTAL_FN2_(flux_t) efflux(XTAL_DEF o, XTAL_DEF ...oo)
		XTAL_0EX
		{
			flux_t const _ = self().effuse(XTAL_REF_(o));
			return !_?0: _ & self().efflux(XTAL_REF_(oo)...);
		}
		XTAL_FN2_(flux_t) efflux(nothing_t, XTAL_DEF ...oo)
		XTAL_0EX
		{
		//	return self().efflux(XTAL_REF_(oo)...);
			return efflux();
		}
		XTAL_FN2_(flux_t) efflux()
		XTAL_0EX
		{
			return -1;
		}


		///\
		Defuse handler: resolves the individual components of the message. \
		
		///\
		\returns a ternary integer indicating the change in state (`1` or `0`), \
		or that the message was unrecognized (`-1`). \
		
		///\
		\note The return value controls conditional execution using binary `&`, \
		truncating propagation when the aggregated result is zero (`0`).

		XTAL_FN2_(flux_t) defuse(XTAL_DEF o)
		XTAL_0EX
		{
			return -1;
		}

		XTAL_FN2_(flux_t) effuse(XTAL_DEF o) XTAL_0EX {return self().defuse(XTAL_REF_(o));}
		///\< \see `defuse`. \

		XTAL_FN2_(flux_t) infuse(XTAL_DEF o) XTAL_0EX {return self().defuse(XTAL_REF_(o));}
		///\< \see `defuse`. \
		

	};
};
////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct refine
{
	using subkind = _detail::refine<T>;

	template <any_q S>
	using subtype = compose_s<S, subkind>;

};

////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that proxies `U`. \

template <typename U>
struct defer
{
	using subkind = _detail::defer<U>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;
		using co::self;
		using co::head;

		///\
		\note Propagates to the proxied value if it has the required `context`.

		XTAL_FN2_(flux_t) influx(XTAL_DEF ...ws)
		XTAL_0EX
		requires any_q<U>
		{
			flux_t const _ = co::influx(ws...);
			return !_?0: _ & head().influx(XTAL_REF_(ws)...);
		}
		XTAL_FN2_(flux_t) influx(XTAL_DEF ...ws)
		XTAL_0EX
		{
			return co::influx(XTAL_REF_(ws)...);
		}

		///\
		\note Propagates to the proxied value if it has the required `context`.

		XTAL_FN2_(flux_t) efflux(XTAL_DEF ...ws)
		XTAL_0EX
		requires any_q<U>
		{
			flux_t const _ = head().efflux(ws...);
			return !_?0: _ & co::efflux(XTAL_REF_(ws)...);
		}
		XTAL_FN2_(flux_t) efflux(XTAL_DEF ...ws)
		XTAL_0EX
		{
			return co::efflux(XTAL_REF_(ws)...);
		}

		///\
		\note Assigns the given value `u` if it matches the proxied type `U`. \

		XTAL_FN2_(flux_t) defuse(U u)
		XTAL_0EX
		{
			return not co::has(u) and (co::head(u), 1);
		}
		XTAL_FN2_(flux_t) defuse(XTAL_DEF w)
		XTAL_0EX
		{
			return co::defuse(XTAL_REF_(w));
		}

	};
};
////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that lifts the operations of `U`. \

template <typename U>
struct refer
{
	using subkind = _detail::refer<U>;

	template <any_q S>
	using subtype = compose_s<S, subkind>;

};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
