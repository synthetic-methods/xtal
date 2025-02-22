#pragma once
#include "../bond.hh"
#include "../cell/any.hh"// `_retail`





XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::cell;
#include "./_entail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Extends `cell::define` with event routing via `flux|fuse`.
*/
template <class T>
struct define
{
	using _fit = bond::fit<>;

	using superkind = _retail::define<T>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

		using U_delay = signed;

	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;

	public:// FLOW

		XTAL_DEF_(return,inline,let) influx(auto &&...oo) noexcept -> signed {return self().template flux<+1>(XTAL_REF_(oo)...);}
		XTAL_DEF_(return,inline,let) efflux(auto &&...oo) noexcept -> signed {return self().template flux<-1>(XTAL_REF_(oo)...);}
		XTAL_DEF_(return,inline,let) effuse(auto &&    o) noexcept -> signed {return self().template fuse<-1>(XTAL_REF_(o)    );}
		XTAL_DEF_(return,inline,let) infuse(auto &&    o) noexcept -> signed {return self().template fuse<+1>(XTAL_REF_(o)    );}
		/*!
		\brief  	Flux handler: resolves the given message,
		resorting to `fuse` each comoponent separately if unmatched.

		\details	The return values are accumulated using `&`, with a default of `-1` and limit of `0`,
		and truncating propagation when the aggregated result is `1`.

		\tparam  N_ion
		A ternary integer indicating the direction of flow,
		where `influx` `+1` resolves the current instance before any dependencies,
		and   `efflux` `-1` resolves the any dependencies before current instance.

		\returns	A ternary integer indicating that the state has changed `0`,
		remains unchanged `+1`, or was unrecognized `-1`.
		*/
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
				XTAL_1FN_(and) (flux<N_ion>(oo...))
					(self().template fuse<N_ion>(XTAL_REF_(o)));
		}

		/*!
		\brief  	Fuse handler: resolves the individual components.
		\brief  	A ternary integer (\see `flux`).
		*/
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		{
			if constexpr (N_ion == 0) {
				return -1;
			}
			else {
				return self().template fuse<0>(XTAL_REF_(o));
			}
		}
		template <signed N_ion> requires in_n<N_ion, 0>
		XTAL_DEF_(return,inline,let)
		fuse(same_q<T> auto &&o)
		noexcept -> signed
		{
			return equivalent_f(o, self()) || ((void) self(XTAL_REF_(o)), 0);
		}

	public:// SCHEDULE

		XTAL_DEF_(return,inline,let) delay()         noexcept -> auto {return bond::fit<signed>::delta_f(count_f(self()));}
		XTAL_DEF_(mutate,inline,let) belay()         noexcept -> auto {return        delay();}
		XTAL_DEF_(mutate,inline,let) relay(auto &&i) noexcept -> auto {return self().delay();}
	//	XTAL_DEF_(return,inline,let) relay(auto &&i) noexcept -> auto {return _std::min<signed>({0x80, self().delay()});}// Force chunking somehow?
		/*!
		\brief  	Relays all spooled events while invoking the supplied callback for each intermediate segment.
		\details	The callback parameters are the `counted_t` indicies and the segment index.
		*/
		XTAL_DEF_(return,inline,let) pump(auto const &f            ) noexcept -> signed {return pump(f, 0);}
		XTAL_DEF_(return,inline,let) pump(auto const &f, signed &&n) noexcept -> signed {return pump(f, n);}
		XTAL_DEF_(return,let)
		pump(auto const &f, signed &n)
		noexcept -> signed
		{
			auto &s = self();
			signed x = -1;
			for (auto j = s.delay(), i = j^j; j != i; j = s.relay(i = j)) {
				x &= f(counted_f(i, j), n++);
			}
			--n; s.belay();
			return n;
		}

	};
};
/*!
\brief   Extends `cell::refine` with event routing endpoints/operators.
*/
template <class T>
struct refine
{
	using superkind = _retail::refine<T>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;

	public:// OPERATE
		/*!
		\returns	`self()` after `influx`ing the given message,
		resolving `this` before any dependencies.
		*/
		XTAL_DEF_(inline,let)
		operator <<=(auto &&o)
		noexcept -> decltype(auto)
		{
			(void) flux<+1>(XTAL_REF_(o));
			return self();
		}
		/*!
		\returns	`self()` after `efflux`ing the given message,
		resolving any dependencies before `this`.
		*/
		XTAL_DEF_(inline,let)
		operator >>=(auto &&o)
		noexcept -> decltype(auto)
		{
			(void) flux<-1>(XTAL_REF_(o));
			return self();
		}

	public:// FLOW

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		refuse(bond::tupack_q auto &&o)
		noexcept -> signed
		{
			return _std::apply([this] XTAL_1FN_(call) (flux<N_ion>), XTAL_REF_(o));
		}

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux(auto &&...oo)
		noexcept -> signed
		{
			if constexpr (0 == sizeof...(oo)) {
				return -1;
			}
			else {
				return S_::template flux<N_ion>(XTAL_REF_(oo)...);
			}
		}
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		{
			return S_::template fuse<N_ion>(XTAL_REF_(o));
		}

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux(auto &&o, auto &&...oo)
		noexcept -> signed
		requires requires {refuse<N_ion>(XTAL_REF_(o));}
		{
			return [this, ...oo=XTAL_REF_(oo)]
				XTAL_1FN_(and) (flux<N_ion>(oo...)) (refuse<N_ion>(XTAL_REF_(o)));
		}
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		requires XTAL_TRY_(to)
			(refuse<N_ion>(XTAL_REF_(o)))

	};
};


////////////////////////////////////////////////////////////////////////////////

/*!
\brief   Extends `cell::defer` with event handling for the supplied `U`.
*/
template <class U>
struct defer
{
	using superkind = _retail::defer<U>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
		using U_ = typename S_::head_type;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;
		using S_::head;

	public:// FLOW
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux_this(auto &&...oo)
		noexcept -> signed
		{
			using X = bond::seek_front_t<decltype(oo)...>;
			XTAL_IF0
			XTAL_0IF                                (sizeof...(oo) == 0) {return -1;}
			XTAL_0IF (different_q<T_, X> and in_q<T_, decltype(oo)... >) {return -1;}
			XTAL_0IF_(else) {
				return S_::template flux<N_ion>(XTAL_REF_(oo)...);
			}
		}
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux_head(auto &&...oo)
		noexcept -> signed
		{
			if constexpr (un_q<U_, decltype(oo)...> and any_q<U_>) {
				return head().template flux<N_ion>(XTAL_REF_(oo)...);
			}
			else {
				return -1;
			}
		}

		/*!
		\note   	When `N_ion == +1`, influxes via the proxied value if supported, then via `this`.
		When `N_ion == -1`, effluxes via `this`, then via the proxied value if supported.
		*/
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux(auto &&...oo)
		noexcept -> signed
		{
			XTAL_IF0
			XTAL_0IF (N_ion < 0) {return [this, oo...] XTAL_1FN_(and) (flux_head<N_ion>(oo...)) (flux_this<N_ion>(XTAL_REF_(oo)...));}
			XTAL_0IF (0 < N_ion) {return [this, oo...] XTAL_1FN_(and) (flux_this<N_ion>(oo...)) (flux_head<N_ion>(XTAL_REF_(oo)...));}
		}

		/*!
		\note   	Assigns the given value `O` if it matches the proxied type `U`.
		*/
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		{
			return S_::template fuse<N_ion>(XTAL_REF_(o));
		}
		template <signed N_ion> requires in_n<N_ion, 0>
		XTAL_DEF_(return,inline,let)
		fuse(same_q<U> auto &&o)
		noexcept -> signed
		{
			return equivalent_f(o, head()) || ((void) head(XTAL_REF_(o)), 0);
		}

	};
};
/*!
\brief   Aliases `cell::refer`.
*/
template <class U>
struct refer
:	_retail::refer<U>
{
};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
