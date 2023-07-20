#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::conflux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct define
{
	using subkind = _retail::define<T>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		friend T;
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;

		XTAL_FN1_(size_x) delay()         {return count_f(self());}
		XTAL_FN1_(size_x) relay(size_x i) {return count_f(self());}
		
		///\
		Relays all queued events while invoking the supplied callback for each intermediate segment. \
		The callback parameters are the `ranges::slice` indicies and the segment index. \

		XTAL_FNX reflux(auto const &f)
		XTAL_0EX
		{
			return reflux(f, 0);
		}
		XTAL_FNX reflux(auto const &f, auto &&n)
		XTAL_0EX
		{
			return reflux(f, n);
		}
		XTAL_FNX reflux(auto const &f, auto &n)
		XTAL_0EX
		{
			auto flx = -1;
			auto  &s = self();
			for (size_x i = 0, j = s.delay(); i != j; j = s.relay(i = j)) {
				flx &= f(n++, counted_f(i, j));
			}
			--n;
			return flx;
		}

		///\
		Influx operator: resolves the message for `this` before any dependencies, \
		used for e.g. `control::resize`. \

		XTAL_OP1 <<(XTAL_DEF o)
		XTAL_0EX
		{
			(void) self().influx(XTAL_REF_(o));
			return self();
		}
		XTAL_OP1 <<(XTAL_DEF_(heterogeneous_bundle_q) oo)
		XTAL_0EX
		{
			(void) _std::apply([this] XTAL_1FN_(self().influx), XTAL_REF_(oo));
			return self();
		}
		///\
		Influx handler: resolves the message for `this` before any dependencies. \
		
		///\returns the result of `infuse` applied to the first argument \
		`&` `influx` applied to the remaining arguments if successful. \

		XTAL_FNX influx(XTAL_DEF o, XTAL_DEF ...oo)
		XTAL_0EX
		{
			return XTAL_FLX_(sizeof...(oo)? self().influx(oo...): -1) (self().infuse(XTAL_REF_(o)));
		}
		XTAL_FNX influx(null_t, XTAL_DEF ...oo)
		XTAL_0EX
		{
			return -1;
		}
		XTAL_FNX influx()
		XTAL_0EX
		{
			return -1;
		}


		///\
		Efflux operator: resolves the message for any dependencies before `this`, \
		used for e.g. `control::respan` and `control::sequel`. \

		XTAL_OP1 >>(XTAL_DEF o)
		XTAL_0EX
		{
			(void) self().efflux(XTAL_REF_(o));
			return self();
		}
		XTAL_OP1 >>(XTAL_DEF_(heterogeneous_bundle_q) oo)
		XTAL_0EX
		{
			(void) _std::apply([this] XTAL_1FN_(self().efflux), XTAL_REF_(oo));
			return self();
		}
		///\
		Efflux handler: resolves the message for any dependencies before `this`. \
		
		///\returns the result of `effuse` applied to the first argument \
		`&` `efflux` applied to the remaining arguments if successful. \

		XTAL_FNX efflux(XTAL_DEF o, XTAL_DEF ...oo)
		XTAL_0EX
		{
			return XTAL_FLX_(sizeof...(oo)? self().efflux(oo...): -1) (self().effuse(XTAL_REF_(o)));
		}
		XTAL_FNX efflux(null_t, XTAL_DEF ...oo)
		XTAL_0EX
		{
			return -1;
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
		
		
	protected:
		///\
		Effluxes each part independently. \

		XTAL_FNX efflux_apart(XTAL_DEF o, XTAL_DEF ...oo)
		XTAL_0EX
		{
			return self().efflux(XTAL_REF_(o)) & self().efflux_apart(XTAL_REF_(oo)...);
		}
		XTAL_FNX efflux_apart()
		XTAL_0EX
		{
			return -1;
		}

		///\
		Influxes each part independently. \

		XTAL_FNX influx_apart(XTAL_DEF o, XTAL_DEF ...oo)
		XTAL_0EX
		{
			return self().influx(XTAL_REF_(o)) & self().influx_apart(XTAL_REF_(oo)...);
		}
		XTAL_FNX influx_apart()
		XTAL_0EX
		{
			return -1;
		}

	};
};
template <typename T>
struct refine
:	_retail::refine<T>
{};


////////////////////////////////////////////////////////////////////////////////

template <typename U>
struct defer
{
	using subkind = _retail::defer<U>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		///\note\
		Influxes the proxied value if supported, then `this`.

		XTAL_FNX influx(XTAL_DEF ...oo)
		XTAL_0EX
		XTAL_REQ any_p<U>
		{
			return XTAL_FLX_(S_::influx(oo...)) (head().influx(XTAL_REF_(oo)...));
		}
		XTAL_FNX influx(XTAL_DEF ...oo)
		XTAL_0EX
		{
			return S_::influx(XTAL_REF_(oo)...);
		}

		///\note\
		Effluxes `this`, then the proxied value if supported.

		XTAL_FNX efflux(XTAL_DEF ...oo)
		XTAL_0EX
		XTAL_REQ any_p<U>
		{
			return XTAL_FLX_(head().efflux(oo...)) (S_::efflux(XTAL_REF_(oo)...));
		}
		XTAL_FNX efflux(XTAL_DEF ...oo)
		XTAL_0EX
		{
			return S_::efflux(XTAL_REF_(oo)...);
		}

		///\note\
		Assigns the given value `u` if it matches the proxied type `U`. \

		XTAL_FNX defuse(U u)
		XTAL_0EX
		{
			return S_::has(u) or (S_::head(u), 0);
		}
		XTAL_FNX defuse(XTAL_DEF w)
		XTAL_0EX
		{
			return S_::defuse(XTAL_REF_(w));
		}

	};
};
template <typename U>
struct refer
:	_retail::refer<U>
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
