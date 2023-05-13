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
		Message `influx` operator: resolves the message for `this` before any dependencies, \
		used for e.g. `message::resize`. \

		XTAL_OP1 <<=(XTAL_DEF w)
		XTAL_0EX
		{
			return operator<<=(collected_f(XTAL_REF_(w)));
		}
		XTAL_OP1 <<=(XTAL_DEF_(collated_q) w)
		XTAL_0EX
		{
			auto const &_ = _std::apply([this] (XTAL_DEF... vs)
				XTAL_0FN_(self().influx(XTAL_REF_(vs)...))
			,	XTAL_REF_(w)
			);
			return self();
		}

		///\
		Message `efflux` operator: resolves the message for any dependencies before `this`, \
		used for e.g. `message::render` and `message::serial`. \

		XTAL_OP1 >>=(XTAL_DEF w)
		XTAL_0EX
		{
			return operator>>=(collected_f(XTAL_REF_(w)));
		}
		XTAL_OP1 >>=(XTAL_DEF_(collated_q) w)
		XTAL_0EX
		{
			auto const &_ = _std::apply([this] (XTAL_DEF... vs)
				XTAL_0FN_(self().efflux(XTAL_REF_(vs)...))
			,	XTAL_REF_(w)
			);
			return self();
		}

		///\
		Message `deflux` handler: resolves the individual components of the message. \
		\returns `1` if the state has changed, `0` if the state remains unchanged, \
		or `-1` if the message wasn't handled. \
		\
		NOTE: The values returned by `deflux` are aggregated by `efflux` and `influx`, \
		and are used to truncate propagation.

		XTAL_FN2_(iota_t) deflux(XTAL_DEF w)
		XTAL_0EX
		{
			return -1;
		}

		///\
		Message `efflux` handler: resolves the message for any dependencies before `this`. \
		\returns the result of `deflux` applied to the first argument `and` \
		`efflux` applied to the remaining arguments. \

		XTAL_FN2_(iota_t) efflux()
		XTAL_0EX
		{
			return -1;
		}
		XTAL_FN2_(iota_t) efflux(XTAL_DEF w, XTAL_DEF... ws)
		XTAL_0EX
		{
			auto const &_ = self().deflux(XTAL_REF_(w));
			return !_?0:_ & self().efflux(XTAL_REF_(ws)...);
		}

		///\
		Message `influx` handler: resolves the message for `this` before any dependencies. \
		\returns the result of `deflux` applied to the first argument `and` \
		`influx` applied to the remaining arguments. \

		XTAL_FN2_(iota_t) influx()
		XTAL_0EX
		{
			return -1;
		}
		XTAL_FN2_(iota_t) influx(XTAL_DEF w, XTAL_DEF... ws)
		XTAL_0EX
		{
			auto const &_ = self().deflux(XTAL_REF_(w));
			return !_?0:_ & self().influx(XTAL_REF_(ws)...);
		}

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
		Attempts assignment: returns `1` if the value has changed, `0` otherwise. \

		XTAL_FN2_(iota_t) deflux(XTAL_DEF w)
		XTAL_0EX
		{
			return co::deflux(XTAL_REF_(w));
		}
		XTAL_FN2_(iota_t) deflux(XTAL_DEF_(is_q<U>) w)
		XTAL_0EX
		{
			if (co::has(w))
			{
				return 0;
			}
			else
			{
				co::template set<U>(w);
				return 1;
			}
		}

		///\
		Message `efflux` handler: resolves the arguments via `head` before `this`. \

		XTAL_FN2_(iota_t) efflux(XTAL_DEF... ws)
		XTAL_0EX
		{
			return co::efflux(XTAL_REF_(ws)...);
		}
		XTAL_FN2_(iota_t) efflux(XTAL_DEF... ws)
		XTAL_0EX
		XTAL_IF1 any_q<U>
		{
			auto const &_ = head().efflux(ws...);
			return !_?0:_ & co::efflux(XTAL_REF_(ws)...);
		}

		///\
		Message `influx` handler: resolves the arguments via `this` before `head`. \

		XTAL_FN2_(iota_t) influx(XTAL_DEF... ws)
		XTAL_0EX
		{
			return co::influx(XTAL_REF_(ws)...);
		}
		XTAL_FN2_(iota_t) influx(XTAL_DEF... ws)
		XTAL_0EX
		XTAL_IF1 any_q<U>
		{
			auto const &_ = co::influx(ws...);
			return !_?0:_ & head().influx(XTAL_REF_(ws)...);
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
