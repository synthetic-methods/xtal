#pragma once
#include "../cell/any.hh"// `_retail`

#include "../cell/cue.hh"




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
	using U_delay = cell::cue_s<>;
	using V_delay = typename U_delay::template head_t<>;
	
	using subkind = _retail::define<T>;

	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		friend T;
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;
		using S_::self;

		XTAL_DEF_(inline) XTAL_LET delay()         XTAL_0EX -> V_delay {return count_f(self());}
		XTAL_DEF_(inline) XTAL_LET relay(auto &&i) XTAL_0EX -> V_delay {return self().delay();}
		
		///\
		Relays all queued events while invoking the supplied callback for each intermediate segment. \
		The callback parameters are the `ranges::slice` indicies and the segment index. \

		XTAL_TNX reflux(auto const &f)          XTAL_0EX {return reflux(f, 0);}
		XTAL_TNX reflux(auto const &f, int &&n) XTAL_0EX {return reflux(f, n);}
		XTAL_TNX reflux(auto const &f, int  &n)
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
		XTAL_REF operator >>=(auto &&o)
		XTAL_0EX
		{
			(void) self().efflux(XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_REF operator >>=(bond::heteropack_q auto &&oo)
		XTAL_0EX
		{
			(void) _std::apply([this] XTAL_1FN_(self().efflux), XTAL_REF_(oo));
			return self();
		}
		///\
		Efflux handler: resolves any dependencies before `this`. \
		
		///\returns the result of `effuse` applied to the first argument \
		`&` `efflux` applied to the remaining arguments if successful. \

		XTAL_TNX efflux(auto &&o, auto &&...oo)
		XTAL_0EX
		{
			return XTAL_FNX_(self().efflux(oo...)) (self().effuse(XTAL_REF_(o)));
		}
		XTAL_TNX efflux(null_t, auto &&...oo)
		XTAL_0EX
		{
			return efflux();
		}
		XTAL_TNX efflux()
		XTAL_0EX
		{
			return -1;
		}


		///\
		Influx operator: resolves `this` before any dependencies, \
		used for e.g. `occur::resize`. \

		XTAL_DEF_(inline)
		XTAL_REF operator <<=(auto &&o)
		XTAL_0EX
		{
			(void) self().influx(XTAL_REF_(o));
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_REF operator <<=(bond::heteropack_q auto &&oo)
		XTAL_0EX
		{
			(void) _std::apply([this] XTAL_1FN_(self().influx), XTAL_REF_(oo));
			return self();
		}
		///\
		Influx handler: resolves `this` before any dependencies. \
		
		///\returns the result of `infuse` applied to the first argument \
		`&` `influx` applied to the remaining arguments if successful. \

		XTAL_TNX influx(auto &&o, auto &&...oo)
		XTAL_0EX
		{
			return XTAL_FNX_(self().influx(oo...)) (self().infuse(XTAL_REF_(o)));
		}
		XTAL_TNX influx(null_t, auto &&...oo)
		XTAL_0EX
		{
			return influx();
		}
		XTAL_TNX influx()
		XTAL_0EX
		{
			return -1;
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

	public:
		///\
		Thunkifies the underlying `T` by capturing the arguments `Xs...`. \

		template <class ...Xs>
		struct compound
		{
			using Xs_packed = cell::packed_t<Xs...>;
			
			using subkind = cell::defer<Xs_packed>;

			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;

			public:// CONSTRUCT
				using R_::R_;

			public:// ACCESS
				using R_::self;
				using R_::head;

				XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_REF slots(), head())
				
				XTAL_TO2_(template <size_t ...Ns>
				XTAL_DEF_(return,inline)
				XTAL_REF slot(), bond::pack_item_f<Ns...>(slots()))

			public:// FLUXION
			//	using R_::influx;
			//	using R_::efflux;

				///\returns the result of `influx`ing `self` then  (if `& 1`) `slots`. \

				XTAL_TNX influx(auto &&...oo)
				XTAL_0EX_TO_(XTAL_FNX_(self().influx_push(oo...)) (R_::influx(XTAL_REF_(oo)...)))

				///\returns the result of `efflux`ing `slots` then (if `& 1`) `self`. \

				XTAL_TNX efflux(auto &&...oo)
				XTAL_0EX_TO_(XTAL_FNX_(R_::efflux(oo...)) (self().efflux_pull(XTAL_REF_(oo)...)))

				///\note\
				If prefixed by `null_t()`, forwards the occur to all `slots`. \

				XTAL_TNX influx(null_t, auto &&...oo) XTAL_0EX_TO_(self().influx_push(XTAL_REF_(oo)...))
				XTAL_TNX efflux(null_t, auto &&...oo) XTAL_0EX_TO_(self().efflux_pull(XTAL_REF_(oo)...))

				///\note\
				If prefixed by `nominal_q`, forwards the occur to the `slot` specified. \

				XTAL_TNX influx(nominal_q auto I, auto &&...oo) XTAL_0EX_TO_(slot<I>().influx(XTAL_REF_(oo)...))
				XTAL_TNX efflux(nominal_q auto I, auto &&...oo) XTAL_0EX_TO_(slot<I>().efflux(XTAL_REF_(oo)...))

				///\
				Forwards the occur to all `slots`, bypassing `self`. \

				XTAL_TNX influx_push(auto &&...oo)
				XTAL_0EX
				{
					return slots().apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
						XTAL_0FN_(XTAL_REF_(xs).influx(oo...) &...& -1)
					);
				}
				XTAL_TNX efflux_pull(auto &&...oo)
				XTAL_0EX
				{
					return slots().apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
						XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) &...& -1)
					);
				}
				///\
				Forwards the occur-tail to all `slots`, bypassing `self`. \
				If `~N_slot`, the slot at `N_slot` receives the full occur. \

				template <int N_slot=-1>
				XTAL_TNX influx_push_tail(auto &&o, auto &&...oo)
				XTAL_0EX
				{
					XTAL_IF0
					XTAL_0IF (N_slot <  0) {
						return influx_push(XTAL_REF_(oo)...);
					}
					XTAL_0IF_(default) {
						return [this, o=XTAL_REF_(o), ...oo=XTAL_REF_(oo)] <auto ...I>(bond::seek_t<I...>)
							XTAL_0FN_(slot<N_slot>().influx(o, oo...) &...& slot<(N_slot <= I) + I>().influx(oo...))
						(bond::seek_s<sizeof...(Xs) - 1> {});
					}
				}
				template <int N_slot=-1>
				XTAL_TNX efflux_pull_tail(auto &&o, auto &&...oo)
				XTAL_0EX
				{
					XTAL_IF0
					XTAL_0IF (N_slot <  0) {
						return efflux_pull(XTAL_REF_(oo)...);
					}
					XTAL_0IF_(default) {
						return [this, o=XTAL_REF_(o), ...oo=XTAL_REF_(oo)] <auto ...I>(bond::seek_t<I...>)
							XTAL_0FN_(slot<N_slot>().efflux(o, oo...) &...& slot<(N_slot <= I) + I>().efflux(oo...))
						(bond::seek_s<sizeof...(Xs) - 1> {});
					}
				}

			};
		};

	};
};
template <class T>
struct refine
{
	using subkind = _retail::refine<T>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		using T_ = T;
	
		template <class ...Xs>
		using S_compound = typename S_::template compound<Xs...>;

	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;

	public:// FLUX
		/*/
		XTAL_TNX infuse(auto &&o)
		XTAL_0EX
		{
			if constexpr (bond::twin_tab_q<T_, decltype(o)>) {
				return S_::infuse(XTAL_REF_(o).apply(invoke_f<T_>));
			}
			else {
				return S_::infuse(XTAL_REF_(o));
			}
		}
		/***/

	public:// BIND

		template <class ...Xs>
		struct binding
		{
			using subkind = confined<S_compound<Xs...>>;

			template <class R>
			using subtype = bond::compose_s<R, subkind>;
			using    type = subtype<S_>;

		};
		template <class ...Xs>
		XTAL_USE binding_t = typename binding<Xs...>::type;
		/**/
		XTAL_DEF_(return,inline,static)
		XTAL_LET     binding_f(auto &&...xs)
		XTAL_0EX_TO_(binding_t<decltype(xs)...>(XTAL_REF_(xs)...))
		/*/
		XTAL_DEF_(return,inline,static)
		XTAL_LET binding_f(auto &&...xs)
		XTAL_0EX_TO_(binding_t<decltype(xs)...>(let_f(XTAL_REF_(xs))...))
		/***/

	};
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
////////////////////////////////////////////////////////////////////////////////

template <any_q Y, class    X > XTAL_DEF_(return,inline) XTAL_REF operator << (X &&x, Y &&y) XTAL_0EX {return bond::pack_f(XTAL_REF_(x), XTAL_REF_(y));}
template <any_q Y, class    X > XTAL_DEF_(return,inline) XTAL_REF operator >> (X &&x, Y &&y) XTAL_0EX {return bond::pack_f(XTAL_REF_(y), XTAL_REF_(x));}

template <any_q Y, class ...Xs> XTAL_DEF_(return,inline) XTAL_REF operator << (_std::tuple<Xs...> &&x, Y &&y) XTAL_0EX {return _std::tuple_cat(XTAL_REF_(x), bond::pack_f(XTAL_REF_(y)));}
template <any_q Y, class ...Xs> XTAL_DEF_(return,inline) XTAL_REF operator << (_std:: pair<Xs...> &&x, Y &&y) XTAL_0EX {return _std::tuple_cat(XTAL_REF_(x), bond::pack_f(XTAL_REF_(y)));}
template <any_q Y, class ...Xs> XTAL_DEF_(return,inline) XTAL_REF operator >> (_std::tuple<Xs...> &&x, Y &&y) XTAL_0EX {return _std::tuple_cat(bond::pack_f(XTAL_REF_(y)), XTAL_REF_(x));}
template <any_q Y, class ...Xs> XTAL_DEF_(return,inline) XTAL_REF operator >> (_std:: pair<Xs...> &&x, Y &&y) XTAL_0EX {return _std::tuple_cat(bond::pack_f(XTAL_REF_(y)), XTAL_REF_(x));}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
