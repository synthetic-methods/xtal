#pragma once
#include "../cell/any.hh"// `_retail`






XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_retail.ii"
#include "./_detail.ii"

using type = sign_type;


////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	using _op = bond::operating;
	using T_iota = typename _op::iota_type;

	using superkind = _retail::define<T>;

	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		friend T;
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;
		using S_::self;

		XTAL_DEF_(inline) XTAL_LET delay()         noexcept -> auto {return static_cast<T_iota>(count_f(self()));}
		XTAL_DEF_(inline) XTAL_LET relay(auto &&i) noexcept -> auto {return self().delay();}
	//	XTAL_DEF_(inline) XTAL_LET relay(auto &&i) noexcept -> auto {return _std::min<T_iota>({0x80, self().delay()});}// Force chunking somehow?
		
		///\
		Relays all queued events while invoking the supplied callback for each intermediate segment. \
		The callback parameters are the `ranges::slice` indicies and the segment index. \

		XTAL_DEF_(return,inline) XTAL_LET reflux(auto const &f)             noexcept -> sign_type {return reflux(f, 0);}
		XTAL_DEF_(return,inline) XTAL_LET reflux(auto const &f, T_iota &&n) noexcept -> sign_type {return reflux(f, n);}
		XTAL_DEF_(return)
		XTAL_LET reflux(auto const &f, T_iota  &n)
		noexcept
		{
			auto x = influx();
			auto &s = self();
			for (auto j = s.delay(), i = decltype(j) {}; j != i; j = s.relay(i = j)) {
				x &= f(counted_f(i, j), n++);
			}
			--n;
			return x;
		}


		///\
		Efflux operator: resolves any dependencies before `this`, \
		used for e.g. `occur::review` and `occur::render`. \

		XTAL_DEF_(inline)
		XTAL_LET operator >>=(auto &&o)
		noexcept -> decltype(auto)
		{
			(void) self().efflux(XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator >>=(bond::heteropack_q auto &&o)
		noexcept -> decltype(auto)
		{
			(void) efflux_apply(XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(return,inline)
		XTAL_LET efflux_apply(bond::heteropack_q auto &&o)
		noexcept -> sign_type
		{
			return _std::apply([this] XTAL_1FN_(self().efflux), XTAL_REF_(o));
		}
		XTAL_DEF_(return,inline)
		XTAL_LET efflux_batch(bond::heteropack_q auto &&o)
		noexcept -> sign_type
		{
			return _std::apply([this] (auto &&...oo)
				XTAL_0FN_(-1 &...& self().efflux(XTAL_REF_(oo)))
			,	XTAL_REF_(o));
		}

		///\
		Efflux handler: resolves any dependencies before `this`. \
		
		///\returns the result of `effuse` applied to the first argument \
		`&` `efflux` applied to the remaining arguments if successful. \

		XTAL_DEF_(return,inline) XTAL_LET efflux(                    auto &&...oo) noexcept -> sign_type {return efflux_fuse(XTAL_REF_(oo)...);}
		XTAL_DEF_(return,inline) XTAL_LET efflux(unnatural_q auto I, auto &&...oo) noexcept -> sign_type {return -1;}
		XTAL_DEF_(return,inline) XTAL_LET efflux(                                ) noexcept -> sign_type {return -1;}
		XTAL_DEF_(return,inline) XTAL_LET efflux_fuse(                           ) noexcept -> sign_type {return -1;}
		XTAL_DEF_(return,inline) XTAL_LET efflux_fuse(     auto &&o, auto &&...oo) noexcept -> sign_type
		{
			return [this, ...oo=XTAL_REF_(oo)] XTAL_XFN_(efflux_fuse(oo...)) (self().effuse(XTAL_REF_(o)));
		}


		///\
		Influx operator: resolves `this` before any dependencies, \
		used for e.g. `occur::resize`. \

		XTAL_DEF_(inline)
		XTAL_LET operator <<=(auto &&o)
		noexcept -> decltype(auto)
		{
			(void) self().influx(XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator <<=(bond::heteropack_q auto &&o)
		noexcept -> decltype(auto)
		{
			(void) influx_apply(XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(return,inline)
		XTAL_LET influx_apply(bond::heteropack_q auto &&o)
		noexcept -> sign_type
		{
			return _std::apply([this] XTAL_1FN_(self().influx), XTAL_REF_(o));
		}
		XTAL_DEF_(return,inline)
		XTAL_LET influx_batch(bond::heteropack_q auto &&o)
		noexcept -> sign_type
		{
			return _std::apply([this] (auto &&...oo)
				XTAL_0FN_(-1 &...& self().influx(XTAL_REF_(oo)))
			,	XTAL_REF_(o));
		}

		///\
		Influx handler: resolves `this` before any dependencies. \
		
		///\returns the result of `infuse` applied to the each argument. \

		XTAL_DEF_(return,inline) XTAL_LET influx(                    auto &&...oo) noexcept -> sign_type {return influx_fuse(XTAL_REF_(oo)...);}
		XTAL_DEF_(return,inline) XTAL_LET influx(unnatural_q auto I, auto &&...oo) noexcept -> sign_type {return -1;}
		XTAL_DEF_(return,inline) XTAL_LET influx(                                ) noexcept -> sign_type {return -1;}
		XTAL_DEF_(return,inline) XTAL_LET influx_fuse(                           ) noexcept -> sign_type {return -1;}
		XTAL_DEF_(return,inline) XTAL_LET influx_fuse(     auto &&o, auto &&...oo) noexcept -> sign_type
		{
			return [this, ...oo=XTAL_REF_(oo)] XTAL_XFN_(influx_fuse(oo...)) (self().infuse(XTAL_REF_(o)));
		}


		///\
		Defuse handler: resolves the individual components. \
		
		///\returns a ternary integer indicating that the state has changed (`0`), \
		remains unchanged (`1`), or was unrecognized (`-1`). \
		
		///\note\
		The return values are accumulated using `&`, with a default of `-1` and limit of `0`, \
		and truncating propagation when the aggregated result is `1`. \

		XTAL_DEF_(return,inline)
		XTAL_LET defuse(XTAL_ARG_(T) &&o)
		noexcept -> sign_type
		{
			return equivalent_f(o, self()) || ((void) self(XTAL_REF_(o)), 0);
		}
		XTAL_DEF_(return,inline) XTAL_LET defuse(auto &&o) noexcept -> sign_type {return -1;}
		XTAL_DEF_(return,inline) XTAL_LET effuse(auto &&o) noexcept -> sign_type {return self().defuse(XTAL_REF_(o));}///\< \see `defuse`.
		XTAL_DEF_(return,inline) XTAL_LET infuse(auto &&o) noexcept -> sign_type {return self().defuse(XTAL_REF_(o));}///\< \see `defuse`.


		///\
		Provides a `defer`red instance of `T` on `subtype`, \
		labelled with the given `As...`. \

		template <typename ...As>
		struct afflux
		{
			using superkind = bond::compose<any<As>..., defer<T>>;

			template <flux::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
			
			public:// CONSTRUCT
			//	using R_::R_;
				using R_::self;

				XTAL_CO0_(subtype);
				XTAL_CO1_(subtype);
				XTAL_CO4_(subtype);

				///\
				Constructs the `attach`ed `occur` using its default, \
				before `forward`ing the arguments to `this`. \

				XTAL_NEW_(explicit) subtype(auto &&...xs)
				noexcept
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
	using superkind = _retail::defer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::head;

		///\note\
		Influxes via the proxied value if supported, then via `this`.

		XTAL_DEF_(return,inline)
		XTAL_LET influx(auto &&...oo)
		noexcept -> sign_type
		{
			return S_::influx(XTAL_REF_(oo)...);
		}
		XTAL_DEF_(return,inline)
		XTAL_LET influx(auto &&...oo)
		noexcept -> sign_type
		requires any_q<U> and (not is_q<U, bond::seek_front_t<decltype(oo)...>>)
		{
			return [this, oo...] XTAL_XFN_(S_::influx(oo...)) (head().influx(XTAL_REF_(oo)...));
		}

		///\note\
		Effluxes via `this`, then via the proxied value if supported.

		XTAL_DEF_(return,inline)
		XTAL_LET efflux(auto &&...oo)
		noexcept -> sign_type
		{
			return S_::efflux(XTAL_REF_(oo)...);
		}
		XTAL_DEF_(return,inline)
		XTAL_LET efflux(auto &&...oo)
		noexcept -> sign_type
		requires any_q<U> and (not is_q<U, bond::seek_front_t<decltype(oo)...>>)
		{
			return [this, oo...] XTAL_XFN_(head().efflux(oo...)) (S_::efflux(XTAL_REF_(oo)...));
		}

		///\note\
		Assigns the given value `O` if it matches the proxied type `U`. \

		XTAL_DEF_(return,inline)
		XTAL_LET defuse(XTAL_ARG_(U) &&o)
		noexcept -> sign_type
		{
			return equivalent_f(o, head()) || ((void) head(XTAL_REF_(o)), 0);
		}
		XTAL_DEF_(return,inline)
		XTAL_LET defuse(auto &&o)
		noexcept -> sign_type
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
