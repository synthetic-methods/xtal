#pragma once
#include "../cell/any.hh"// `_retail`






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::cell;
#include "./_entail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	using _fix = bond::fixture<>;

	using superkind = _retail::define<T>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;
		using S_::self;

		XTAL_DEF_(inline,let) delay()         noexcept -> auto {return static_cast<signed>(count_f(self()));}
		XTAL_DEF_(inline,let) relay(auto &&i) noexcept -> auto {return self().delay();}
	//	XTAL_DEF_(inline,let) relay(auto &&i) noexcept -> auto {return _std::min<signed>({0x80, self().delay()});}// Force chunking somehow?
		
		///\
		Relays all queued events while invoking the supplied callback for each intermediate segment. \
		The callback parameters are the `ranges::slice` indicies and the segment index. \

		XTAL_DEF_(return,inline,let) reflux(auto const &f)             noexcept -> signed {return reflux(f, 0);}
		XTAL_DEF_(return,inline,let) reflux(auto const &f, signed &&n) noexcept -> signed {return reflux(f, n);}
		XTAL_DEF_(return,let)
		reflux(auto const &f, signed &n)
		noexcept
		{
			signed x = -1;
			for (auto j = self().delay(), i = decltype(j) {}; j != i; j = self().relay(i = j)) {
				x &= f(counted_f(i, j), n++);
			}
			--n;
			return x;
		}

	//	XTAL_DEF_(return,inline,let) defuse(auto &&    o) noexcept -> signed {return self().template fuse< 0>(XTAL_REF_(o)    );}
	//	XTAL_DEF_(return,inline,let) deflux(auto &&...oo) noexcept -> signed {return self().template flux< 0>(XTAL_REF_(oo)...);}
		XTAL_DEF_(return,inline,let) effuse(auto &&    o) noexcept -> signed {return self().template fuse<-1>(XTAL_REF_(o)    );}
		XTAL_DEF_(return,inline,let) efflux(auto &&...oo) noexcept -> signed {return self().template flux<-1>(XTAL_REF_(oo)...);}
		XTAL_DEF_(return,inline,let) infuse(auto &&    o) noexcept -> signed {return self().template fuse<+1>(XTAL_REF_(o)    );}
		XTAL_DEF_(return,inline,let) influx(auto &&...oo) noexcept -> signed {return self().template flux<+1>(XTAL_REF_(oo)...);}

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux(auto &&...oo)
		noexcept -> signed
		{
			return -1;
		}
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux(variable_q auto &&o, auto &&...oo)
		noexcept -> signed
		{
			return [this, ...oo=XTAL_REF_(oo)]
				XTAL_0FN_(and) (flux<N_ion>(oo...))
					(self().template fuse<N_ion>(XTAL_REF_(o)));
		}

		///\
		Defuse handler: resolves the individual components. \
		
		///\returns a ternary integer indicating that the state has changed (`0`), \
		remains unchanged (`1`), or was unrecognized (`-1`). \
		
		///\note\
		The return values are accumulated using `&`, with a default of `-1` and limit of `0`, \
		and truncating propagation when the aggregated result is `1`. \

		template <signed N_ion> requires in_n<N_ion,  0>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		{
			if constexpr (same_q<T, decltype(o)>) {
				return equivalent_f(o, self()) || ((void) self(XTAL_REF_(o)), 0);
			}
			else {
				return -1;
			}
		}
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		{
			return self().template fuse< 0>(XTAL_REF_(o));
		}

		///\
		Efflux operator: resolves any dependencies before `this`, \
		used for e.g. `occur::review` and `occur::render`. \

		XTAL_DEF_(inline,let)
		operator >>=(auto &&o)
		noexcept -> decltype(auto)
		{
			(void) efflux(XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline,let)
		operator >>=(bond::heteropack_q auto &&o)
		noexcept -> decltype(auto)
		{
			(void) _std::apply([this] (auto &&...oo)
				XTAL_0FN_(return) (efflux(XTAL_REF_(oo)...))
			,	XTAL_REF_(o)
			);
			return self();
		}

		///\
		Influx operator: resolves `this` before any dependencies, \
		used for e.g. `occur::resize`. \

		XTAL_DEF_(inline,let)
		operator <<=(auto &&o)
		noexcept -> decltype(auto)
		{
			(void) influx(XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline,let)
		operator <<=(bond::heteropack_q auto &&o)
		noexcept -> decltype(auto)
		{
			(void) _std::apply([this] (auto &&...oo)
				XTAL_0FN_(return) (influx(XTAL_REF_(oo)...))
			,	XTAL_REF_(o)
			);
			return self();
		}

	};
};
template <class T>
struct refine
:	_retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer
{
	using superkind = _retail::defer<U>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux(auto &&...oo)
		noexcept -> signed
		{
			return S_::template flux<N_ion>(XTAL_REF_(oo)...);
		}
		///\note\
		Influxes via the proxied value if supported, then via `this`.

		template <signed N_ion> requires in_n<N_ion, +1>
		XTAL_DEF_(return,inline,let)
		flux(auto &&...oo)
		noexcept -> signed
		requires any_q<U> and different_q<U, bond::seek_front_t<decltype(oo)...>>
		{
			return [this, oo...]
				XTAL_0FN_(and) (S_::template flux<N_ion>(oo...))
					(head().template flux<N_ion>(XTAL_REF_(oo)...));
		}
		///\note\
		Effluxes via `this`, then via the proxied value if supported.

		template <signed N_ion> requires in_n<N_ion, -1>
		XTAL_DEF_(return,inline,let)
		flux(auto &&...oo)
		noexcept -> signed
		requires any_q<U> and different_q<U, bond::seek_front_t<decltype(oo)...>>
		{
			return [this, oo...]
				XTAL_0FN_(and) (head().template flux<N_ion>(oo...))
					(S_::template flux<N_ion>(XTAL_REF_(oo)...));
		}

		///\note\
		Assigns the given value `O` if it matches the proxied type `U`. \

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		{
			return S_::template fuse<N_ion>(XTAL_REF_(o));
		}
		template <signed N_ion> requires in_n<N_ion,  0>
		XTAL_DEF_(return,inline,let)
		fuse(same_q<U> auto &&o)
		noexcept -> signed
		{
			return equivalent_f(o, head()) || ((void) head(XTAL_REF_(o)), 0);
		}

	};
};
template <class U>
struct refer
:	_retail::refer<U>
{
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
