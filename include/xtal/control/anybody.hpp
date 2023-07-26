#pragma once
#include "./any.hpp"

#include "../context/all.hpp"
#include "../process/any.hpp"
#include "../processor/any.hpp"


XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	using subkind = _retail::define<T>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		friend T;
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

		struct attach
		{
			using subkind = conflux::defer<T>;

			template <conflux::any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;
			
			public:
			//	using R_::R_;

				XTAL_CO0_(subtype);
				XTAL_CO4_(subtype);

				///\
				Constructs the `attach`ed `control` using its default, \
				before `forward`ing the arguments to `this`. \

				XTAL_CXN subtype(XTAL_DEF ...xs)
				XTAL_0EX
				:	R_(T{}, XTAL_REF_(xs)...)
				{}

			};
		};
		///\
		Attaches `T` as a member of `this`, appending it to the arguments used to resolve `method<auto ...>`. \

		template <size_t N_arity=2>
		struct dispatch
		{
			template <process::any_q R>
			class subtype: public compose_s<R, attach>
			{
				using R_ = compose_s<R, attach>;
				using K_ = typename R_::head_t;
			
			public:
			//	using R_::R_;
				using R_::self;
				using R_::head;

				XTAL_CO0_(subtype);
				XTAL_CO4_(subtype);

				XTAL_CXN subtype(size_t const &n)
				:	R_(n)
				{
					assert(0 <= n and n < N_arity);
				}

				XTAL_TO2_(
				XTAL_OP2() (XTAL_DEF ...xs),
					(self().*deify<decltype(xs)...>()) (XTAL_REF_(xs)...)
				)

				XTAL_TO4_(template <class ...Xs>
				XTAL_FN2 reify(constant_q auto const ...ks),
					_std::bind_front(deify<Xs...>(ks...), &self())
				)

				template <class ...Xs>
				XTAL_FN2 deify(constant_q auto const ...ks)
				XTAL_0FX
				{
					return deify_(being<Xs...>::template method_m<value_f(ks)...>);
				}
				XTAL_FN2 deify_(array_q auto const &fs)
				XTAL_0FX
				{
					return R_::deify_(fs[head()]);
				}

			protected:
				template <class ...Xs>
				struct being
				{
					template <auto ...Ks>
					class resolve
					{
						template <size_t ...I>
						XTAL_CN2 method_f(seek_t<I...>)
						XTAL_0EX
						{
							using doing = typename R_::template being<Xs...>;
							return _std::array{(doing::template method_m<Ks..., I>)...};
						}
					
					public:
						XTAL_LET method_m = method_f(seek_f<N_arity> {});
					
					};
					template <auto ...Ks> XTAL_LET method_m = resolve<Ks...>::method_m;
					template <auto ...Ks> XTAL_USE method_t = decltype(method_m<Ks...>);
				
				};

			};
		};
		///\
		Attaches `T` as a namespace, \
		forwarding on `influx` only when prefixed by a matching type/instance. \

		struct guard
		{
			template <conflux::any_q R>
			class subtype: public compose_s<R, attach>
			{
				using R_ = compose_s<R, attach>;
			
			public:
				using R_::R_;

				XTAL_FNX infuse(XTAL_DEF o)
				XTAL_0EX
				{
					if constexpr (is_q<T, XTAL_TYP_(o)>) {
						return R_::heading(XTAL_REF_(o));
					}
					else {
						return R_::infuse(XTAL_REF_(o));
					}
				}

			};
		};
		///\
		Attaches `T`, allowing aggregated inspection via `efflux`. \
		
		struct gauge
		{
			template <conflux::any_q R>
			class subtype: public compose_s<R, attach>
			{
				using R_ = compose_s<R, attach>;
			
			public:
				using R_::R_;
				
				XTAL_FNX effuse(XTAL_DEF o)
				XTAL_0EX
				{
					if constexpr (is_q<T, XTAL_TYP_(o)>) {
						return R_::heading(XTAL_REF_(o));
					}
					else {
						return R_::effuse(XTAL_REF_(o));
					}
				}

			};
		};
		///\
		Uses the current `T` as the return value of `method`. \
		
		struct poll
		{
			template <process::any_q R>
			class subtype: public compose_s<R, attach>
			{
				using R_ = compose_s<R, attach>;
			
			public:
				using R_::R_;
				using R_::head;

				XTAL_FN2_(T) method()
				XTAL_0FX
				{
					return head();
				}

			};
		};
		///\
		Wraps all `influx`ed `control`s prefixed by a context-free `voice`. \

		///\note\
		Defined independently of `T`!

		struct rend
		{
			template <conflux::any_q R>
			class subtype: public compose_s<R>
			{
				using R_ = compose_s<R>;
				
			public:
				using R_::R_;
				using R_::self;
				using R_::influx;
				///\returns the aggregated result of queuing the `control`s with the given delay. \

				XTAL_FNX influx(context::voice_s<> io, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return self().influx_apart(context::voice_s<XTAL_TYP_(oo)>(io.head(), XTAL_REF_(oo))...);
				}

			};
		};
		///\
		Wraps all `influx`ed `control`s prefixed by a context-free `cue`. \

		///\note\
		Defined independently of `T`!

		struct pend
		{
			template <conflux::any_q R>
			class subtype: public compose_s<R, rend>
			{
				using R_ = compose_s<R, rend>;
				
			public:
				using R_::R_;
				using R_::self;
				using R_::influx;
				///\returns the aggregated result of influxing the given `control`s. \

				XTAL_FNX influx(context::cue_s<> io, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return self().influx_apart(context::cue_s<XTAL_TYP_(oo)>(io.head(), XTAL_REF_(oo))...);
				}

			};
		};
		///\
		Provides a queue for `T` on the target object, \
		which is converted to a signal by successive calls to `method`. \

		template <int N_event=-1>
		struct hold
		{
			using event_u = context::cue_s<T>;
			using delay_u = typename event_u::head_t;
			using spool_u = typename collate_t<N_event>::template spool_t<event_u>;

			template <int N>
			XTAL_LET sentry_v = event_u::template sentry<N>();

			template <process::any_q R> requires (2 <= size_t(N_event))
			class subtype: public compose_s<R, pend>
			{
				using R_ = compose_s<R, pend>;
				
				delay_u d_{0};
				spool_u q_{sentry_v<-1>, sentry_v<1>};

			public:
				using R_::R_;
				using R_::influx;

				XTAL_FNX influx(event_u dot, XTAL_DEF ...oo)
				XTAL_0EX
				{
					if (dot.head() < d_ and q_.empty()) {
						q_.abandon().head(d_ = 0);
					}
					q_.push(XTAL_MOV_(dot));
					return R_::influx(oo...);
				}

				XTAL_FN2_(T) method()
				XTAL_0EX
				{
					return q_.advance(d_++ == q_.peek(1).head()).core();
				}
			//	TODO: Once the phasor-type is settled, define a `method` that updates only on reset. \

			};
		};
		///\
		Provides a queue for `T` on the target object, \
		scheduled via `influx` and processed in segments via `reflux`. \

		///\todo\
		Allow for scheduling beyond the current window, \
		possibly using `control::sequel` to convert between absolute and relative delays. \

		template <int N_event=-1>
		struct intermit
		{
			using event_u = context::cue_s<T>;
			using delay_u = typename event_u::head_t;
			using spool_u = typename collate_t<N_event>::template spool_t<event_u>;

			template <int N>
			XTAL_LET sentry_v = event_u::template sentry<N>();

			template <processor::any_q R>
			class subtype: public compose_s<R, pend>
			{
				using R_ = compose_s<R, pend>;
				spool_u q_{sentry_v<1>};

				XTAL_TO4_(XTAL_FN2 next_tail(), q_.peek().core())
				XTAL_TO4_(XTAL_FN2 next_head(), q_.peek().head())

			public:
				using R_::R_;
				using R_::self;
				using R_::influx;
				///\
				Invokes `influx` if the given delay `i == 0`, \
				otherwise enqueues the events `o, o...` at the specified index. \
				
				XTAL_FNX influx(event_u dot, XTAL_DEF ...oo)
				XTAL_0EX
				{
					if (0 == dot.head()) {
						return influx(dot.core(), XTAL_REF_(oo)...);
					}
					else {
						q_.push(XTAL_MOV_(dot));
						return influx(XTAL_REF_(oo)...);
					}
				}

				///\returns The delay until the next event to be processed. \

				XTAL_FN1_(delay_u) delay()
				XTAL_0EX
				{
					return _std::min<delay_u>({R_::delay(), next_head()});
				//	NOTE: The `std::initializer_list` syntax voids segfaulting in `RELEASE`. \
				
				}
				///\
				Invokes `influx` for all events up-to the supplied delay `i`. \
				
				///\returns the delay until the next event. \

				XTAL_FN1_(delay_u) relay(delay_u i)
				XTAL_0EX
				{
					R_::relay(i);
					for (; 0 < q_.size() and next_head() <= i; q_.pop()) {
						(void) R_::influx(next_tail());
					}
					return delay();
				}

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
:	_retail::defer<U>
{
};
template <constant_q W> requires unsigned_q<value_t<W>>
struct defer<W>
{
	using subkind = defer<value_t<W>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

		using dispatch = typename S_::template dispatch<value_v<W>>;

	};
};
template <class U>
struct refer
:	_retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
