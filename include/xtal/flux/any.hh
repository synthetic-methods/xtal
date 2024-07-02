#pragma once
#include "../compound/any.hh"// `_retail`






XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_retail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	using _op = bond::operating;
	using T_iota = typename _op::iota_type;

	using subkind = _retail::define<T>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		friend T;
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;

		XTAL_DEF_(inline) XTAL_LET delay()         XTAL_0EX {return static_cast<T_iota>(count_f(self()));}
		XTAL_DEF_(inline) XTAL_LET relay(auto &&i) XTAL_0EX {return self().delay();}
		
		///\
		Relays all queued events while invoking the supplied callback for each intermediate segment. \
		The callback parameters are the `ranges::slice` indicies and the segment index. \

		XTAL_TNX reflux(auto const &f)             XTAL_0EX {return reflux(f, 0);}
		XTAL_TNX reflux(auto const &f, T_iota &&n) XTAL_0EX {return reflux(f, n);}
		XTAL_TNX reflux(auto const &f, T_iota  &n)
		XTAL_0EX
		{
			XTAL_FLX flx = -1;
			auto &s = self();
			for (auto j = s.delay(), i = decltype(j) {}; j != i; j = s.relay(i = j)) {
				flx &= f(counted_f(i, j), n++);
			}
			--n;
			return flx;
		}


		///\
		Efflux operator: resolves any dependencies before `this`, \
		used for e.g. `occur::review` and `occur::render`. \

		XTAL_DEF_(inline)
		XTAL_LET operator >>=(auto &&o)
		XTAL_0EX -> decltype(auto)
		{
			(void) self().efflux(XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator >>=(bond::heteropack_q auto &&oo)
		XTAL_0EX -> decltype(auto)
		{
			(void) _std::apply([this] XTAL_1FN_(self().efflux), XTAL_REF_(oo));
			return self();
		}
		///\
		Efflux handler: resolves any dependencies before `this`. \
		
		///\returns the result of `effuse` applied to the first argument \
		`&` `efflux` applied to the remaining arguments if successful. \

		XTAL_TNX efflux(                    auto &&...oo) XTAL_0EX {return efflux_fuse(XTAL_REF_(oo)...);}
		XTAL_TNX efflux(unnatural_q auto I, auto &&...oo) XTAL_0EX {return -1;}
		XTAL_TNX efflux(                                ) XTAL_0EX {return -1;}
		XTAL_TNX efflux_fuse(                           ) XTAL_0EX {return -1;}
		XTAL_TNX efflux_fuse(     auto &&o, auto &&...oo)
		XTAL_0EX
		{
			return XTAL_FNX_(efflux_fuse(oo...)) (self().effuse(XTAL_REF_(o)));
		}

		///\
		Influx operator: resolves `this` before any dependencies, \
		used for e.g. `occur::resize`. \

		XTAL_DEF_(inline)
		XTAL_LET operator <<=(auto &&o)
		XTAL_0EX -> decltype(auto)
		{
			(void) self().influx(XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator <<=(bond::heteropack_q auto &&oo)
		XTAL_0EX -> decltype(auto)
		{
			(void) _std::apply([this] XTAL_1FN_(self().influx), XTAL_REF_(oo));
			return self();
		}
		///\
		Influx handler: resolves `this` before any dependencies. \
		
		///\returns the result of `infuse` applied to the each argument. \

		XTAL_TNX influx(                    auto &&...oo) XTAL_0EX {return influx_fuse(XTAL_REF_(oo)...);}
		XTAL_TNX influx(unnatural_q auto I, auto &&...oo) XTAL_0EX {return -1;}
		XTAL_TNX influx(                                ) XTAL_0EX {return -1;}
		XTAL_TNX influx_fuse(                           ) XTAL_0EX {return -1;}
		XTAL_TNX influx_fuse(     auto &&o, auto &&...oo)
		XTAL_0EX
		{
			return XTAL_FNX_(influx_fuse(oo...)) (self().infuse(XTAL_REF_(o)));
		}


		///\
		Defuse handler: resolves the individual components. \
		
		///\returns a ternary integer indicating that the state has changed (`0`), \
		remains unchanged (`1`), or was unrecognized (`-1`). \
		
		///\note\
		The return values are accumulated using `&`, with a default of `-1` and limit of `0`, \
		and truncating propagation when the aggregated result is `1`. \

		XTAL_TNX defuse(is_q<T> auto &&o)
		XTAL_0EX
		{
			return equivalent_f(o, self()) || ((void) self(XTAL_REF_(o)), 0);
		}
		XTAL_TNX defuse(auto &&o) XTAL_0EX {return -1;}
		XTAL_TNX effuse(auto &&o) XTAL_0EX {return self().defuse(XTAL_REF_(o));}///\< \see `defuse`.
		XTAL_TNX infuse(auto &&o) XTAL_0EX {return self().defuse(XTAL_REF_(o));}///\< \see `defuse`.


		///\
		Provides a `defer`red instance of `T` on `subtype`, \
		labelled with the given `As...`. \

		template <typename ...As>
		struct afflux
		{
			using subkind = bond::compose<any<As>..., defer<T>>;

			template <flux::any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
			
			public:
			//	using R_::R_;
				using R_::self;

				XTAL_CO0_(subtype);
				XTAL_CO1_(subtype);
				XTAL_CO4_(subtype);

				///\
				Constructs the `attach`ed `occur` using its default, \
				before `forward`ing the arguments to `this`. \

				XTAL_CON_(explicit) subtype(auto &&...xs)
				XTAL_0EX
				:	R_(T{}, XTAL_REF_(xs)...)
				{}

			};
		};
		template <typename ...As>
		using  afflux_t = confined_t<afflux<As...>>;

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
	using subkind = _retail::defer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		///\note\
		Influxes via the proxied value if supported, then via `this`.

		XTAL_TNX influx(auto &&...oo)
		XTAL_0EX
		{
			return S_::influx(XTAL_REF_(oo)...);
		}
		XTAL_TNX influx(auto &&...oo)
		XTAL_0EX requires any_q<U> and (not is_q<U, bond::seek_front_t<decltype(oo)...>>)
		{
			return XTAL_FNX_(S_::influx(oo...)) (head().influx(XTAL_REF_(oo)...));
		}

		///\note\
		Effluxes via `this`, then via the proxied value if supported.

		XTAL_TNX efflux(auto &&...oo)
		XTAL_0EX
		{
			return S_::efflux(XTAL_REF_(oo)...);
		}
		XTAL_TNX efflux(auto &&...oo)
		XTAL_0EX requires any_q<U> and (not is_q<U, bond::seek_front_t<decltype(oo)...>>)
		{
			return XTAL_FNX_(head().efflux(oo...)) (S_::efflux(XTAL_REF_(oo)...));
		}

		///\note\
		Assigns the given value `O` if it matches the proxied type `U`. \

		XTAL_TNX defuse(is_q<U> auto &&o)
		XTAL_0EX
		{
			return equivalent_f(o, head()) || ((void) head(XTAL_REF_(o)), 0);
		}
		XTAL_TNX defuse(auto &&o)
		XTAL_0EX
		{
			return S_::defuse(XTAL_REF_(o));
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
