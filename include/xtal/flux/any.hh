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

		XTAL_TN1_(V_delay) delay()         {return count_f(self());}
		XTAL_TN1_(V_delay) relay(auto &&i) {return self().delay();}
		
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
			for (int i{}, j = s.delay(); i != j; j = s.relay(i = j)) {
				flx &= f(counted_f(i, j), n++);
			}
			--n;
			return flx;
		}


		///\
		Efflux operator: resolves any dependencies before `this`, \
		used for e.g. `occur::revise` and `occur::render`. \

		XTAL_OP1 >>=(auto &&o)
		XTAL_0EX
		{
			(void) self().efflux(XTAL_REF_(o));
			return self();
		}
		XTAL_OP1 >>=(bond::heteropack_q auto &&oo)
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
			return XTAL_FLX_(self().efflux(oo...)) (self().effuse(XTAL_REF_(o)));
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

		XTAL_OP1 <<=(auto &&o)
		XTAL_0EX
		{
			(void) self().influx(XTAL_REF_(o));
			return self();
		}
		XTAL_OP1 <<=(bond::heteropack_q auto &&oo)
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
			return XTAL_FLX_(self().influx(oo...)) (self().infuse(XTAL_REF_(o)));
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

		XTAL_TNX defuse(auto &&o)
		XTAL_0EX
		{
			return -1;
		}
		/*/
		XTAL_TNX defuse(is_q<T> auto &&t)
		XTAL_0EX
		{
			if (self() != t) {
				//\
				self() = XTAL_REF_(t);
				self(XTAL_REF_(t));
				return 0;
			}
			else {
				return 1;
			}
		}
		/***/
		XTAL_TNX effuse(auto &&o) XTAL_0EX {return self().defuse(XTAL_REF_(o));}
		///\< \see `defuse`. \

		XTAL_TNX infuse(auto &&o) XTAL_0EX {return self().defuse(XTAL_REF_(o));}
		///\< \see `defuse`. \


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

				XTAL_CXN subtype(auto &&...xs)
				XTAL_0EX
				:	R_(T{}, XTAL_REF_(xs)...)
				{}

			};
		};

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
		Influxes the proxied value if supported, then `this`.

		XTAL_TNX influx(auto &&...oo)
		XTAL_0EX
		XTAL_REQ any_q<U>
		{
			return XTAL_FLX_(S_::influx(oo...)) (head().influx(XTAL_REF_(oo)...));
		}
		XTAL_TNX influx(auto &&...oo)
		XTAL_0EX
		{
			return S_::influx(XTAL_REF_(oo)...);
		}

		///\note\
		Effluxes `this`, then the proxied value if supported.

		XTAL_TNX efflux(auto &&...oo)
		XTAL_0EX
		XTAL_REQ any_q<U>
		{
			return XTAL_FLX_(head().efflux(oo...)) (S_::efflux(XTAL_REF_(oo)...));
		}
		XTAL_TNX efflux(auto &&...oo)
		XTAL_0EX
		{
			return S_::efflux(XTAL_REF_(oo)...);
		}

		///\note\
		Assigns the given value `u` if it matches the proxied type `U`. \

		template <class W>
		XTAL_TNX defuse(W &&w)
		XTAL_0EX
		{
			if constexpr (is_q<U, W>) {
				return S_::heading(w) || (S_::head(XTAL_REF_(w)), 0);
			}
			else {
				return S_::defuse(XTAL_REF_(w));
			}
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

template <any_q Y, class    X > XTAL_OP2 << (X &&x, Y &&y) XTAL_0EX {return bond::pack_f(XTAL_REF_(x), XTAL_REF_(y));}
template <any_q Y, class    X > XTAL_OP2 >> (X &&x, Y &&y) XTAL_0EX {return bond::pack_f(XTAL_REF_(y), XTAL_REF_(x));}

template <any_q Y, class ...Xs> XTAL_OP2 << (_std::tuple<Xs...> &&x, Y &&y) XTAL_0EX {return _std::tuple_cat(XTAL_REF_(x), bond::pack_f(XTAL_REF_(y)));}
template <any_q Y, class ...Xs> XTAL_OP2 << (_std:: pair<Xs...> &&x, Y &&y) XTAL_0EX {return _std::tuple_cat(XTAL_REF_(x), bond::pack_f(XTAL_REF_(y)));}
template <any_q Y, class ...Xs> XTAL_OP2 >> (_std::tuple<Xs...> &&x, Y &&y) XTAL_0EX {return _std::tuple_cat(bond::pack_f(XTAL_REF_(y)), XTAL_REF_(x));}
template <any_q Y, class ...Xs> XTAL_OP2 >> (_std:: pair<Xs...> &&x, Y &&y) XTAL_0EX {return _std::tuple_cat(bond::pack_f(XTAL_REF_(y)), XTAL_REF_(x));}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
