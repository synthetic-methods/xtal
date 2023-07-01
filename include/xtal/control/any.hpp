#pragma once
#include "../conflux/any.hpp"// `_retail`

#include "../context/delay.hpp"




XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::conflux;
#include "../concord/any.hxx"


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

		///\
		Attaches `T` as a member of `this`. \

		struct attach
		{
			using subkind = conflux::defer<T>;

			template <conflux::any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;
			
			public:
			//	using R_::R_;

				XTAL_CN2_(subtype);
				XTAL_CN4_(subtype);

				///\
				Constructs the `attach`ed `control` using its default, \
				before `forward`ing the arguments to `this`. \

				XTAL_NEW_(explicit) subtype(XTAL_DEF ...xs)
				XTAL_0EX
				:	R_(T(), XTAL_REF_(xs)...)
				{
				}

			//	TODO: Specialize a `process`'s `interrupter` to `interrupt` `T` automatically when lifted to a `processor`. \

			};
		};
		///\
		Attaches `T` as a member of `this`, appending it to the arguments used by `reify`. \

		template <size_t N_arity=2>
		struct dispatch
		{
			using subkind = attach;

			template <conflux::any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;
			
			public:
			//	using R_::R_;
				using R_::self;

				XTAL_CN2_(subtype);
				XTAL_CN4_(subtype);

				XTAL_NEW_(explicit) subtype(size_t const &n)
				:	R_(n)
				{
					assert(0 <= n and n < N_arity);
				}


				XTAL_RN4_(
				XTAL_OP2() (XTAL_DEF ...xs), (self().*deify<decltype(xs)...>()) (XTAL_REF_(xs)...)
				)

				XTAL_RN4_(template <typename ...Xs>
				XTAL_FN2 reify(), _std::bind_front(deify<Xs...>(), &self())
				)

				template <typename ...Xs>
				XTAL_FN2 deify()
				XTAL_0FX
				{
					return deify(being<Xs...>::template method<>);
				}
				XTAL_FN2 deify(auto const &fs)
				XTAL_0FX
				{
					return R_::deify(fs[R_::head()]);
				}

			protected:
				template <typename ...Xs>
				struct being
				{
					template <auto ...Ms>
					struct resolve
					{
						template <size_t ...I>
						XTAL_FZ2 method_f(seek_t<I...>)
						XTAL_0EX
						{
							using doing = typename R_::template being<Xs...>;
							return _std::array{(doing::template method<Ms..., I>)...};
						}
						XTAL_LET method_m = method_f(seek_v<N_arity>);
					
					};
					template <auto ...Ms>
					XTAL_LET method = resolve<Ms...>::method_m;
				
				};

			};
		};
		///\
		Attaches `T` as a namespace recognized by `this`. \

		struct guard
		{
			using subkind = attach;

			template <conflux::any_p R> requires (T::tuple_size::value == 0)
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;
			
			public:
				using R_::R_;
				using R_::defuse;

				XTAL_FNX defuse(XTAL_DEF_(is_q<T>) t)
				XTAL_0EX
				{
					return 1;
				}

			};
		};
		template <int N_event=-1>
		struct hold
		{
			template <conflux::any_p R>
			class subtype: public compose_s<R>
			{
				using R_ = compose_s<R>;

				using event_u = context::delay_s<T>;
				using delay_u = typename event_u::head_t;
				using spool_u = typename collage_t<event_u, N_event>::spool_t;

				delay_u d_{0};
				spool_u q_{event_u::template sentry<-1>(), event_u::template sentry<+1>()};

			public:
				using R_::R_;
				using R_::self;


				using R_::influx;
				///\returns the aggregate `flux` of queuing the controls with the given delay.. \

				XTAL_FNX influx(event_u dot, XTAL_DEF ...oo)
				XTAL_0EX
				{
					if (dot.head() < d_ and q_.empty())
					{	q_.abandon().head(d_ = 0);
					}
					q_.push(XTAL_MOV_(dot));
					return R_::influx(oo...);
				}
				XTAL_FNX influx(context::delay_s<> d_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return influx(context::delay_s<XTAL_TYP_(oo)>(d_t.head(), XTAL_REF_(oo))...);
				}


				template <auto...>
				XTAL_FN1_(T) method()
				XTAL_0EX
				{
					return q_.advance(d_++ == q_.top().head()).parent();
				}
			//	TODO: Once the phasor-type is settled, define a `method` that updates only on reset. \

			};
		};
		///\
		Provides a queue for this control-type `T` on the target object, \
		scheduled via `influx` and processed in segments via `redux`. \

		///\todo\
		Allow for scheduling beyond the current window, \
		possibly using `control::sequel` to convert between absolute and relative delays. \

		template <int N_event=-1>
		struct interrupt
		{
			template <conflux::any_p R>
			class subtype: public compose_s<R>
			{
				using R_ = compose_s<R>;

				using event_u = context::delay_s<T>;
				using delay_u = typename event_u::head_t;
				using spool_u = typename collage_t<event_u, N_event>::spool_t;

				spool_u q_{event_u::template sentry<1>()};

				XTAL_RN2_(XTAL_FN2 next_tail(), q_.top().parent())
				XTAL_RN2_(XTAL_FN2 next_head(), q_.top().head())
				XTAL_FN2 last_head()
				XTAL_0FX
				{
					if constexpr (requires {{R_::relay()} -> is_q<delay_u>;})
					{	return R_::relay();
					}
					else
					{	return delay_u(self().size());
					}
				}

			protected:
				///\
				Invokes `influx` for all events up-to the supplied delay `i`. \
				
				///\returns the delay until the next event. \

				XTAL_FN1_(delay_u) relay(delay_u i)
				XTAL_0EX
				{
					if constexpr (requires {{R_::relay(i)} -> is_q<delay_u>;})
					{	R_::relay(i);
						for (; 0 < q_.size() and next_head() <= i; q_.pop())
						{	(void) R_::influx(next_tail());
						}
					}
					return relay();
				}
				XTAL_FN1_(delay_u) relay()
				XTAL_0EX
				{
					return _std::min<delay_u>({next_head(), last_head()});
				//	NOTE: The initializer syntax voids segfaulting in `RELEASE`. \
				
				}

				///\
				Relays all queued events while invoking the supplied callback for each intermediate segment. \
				The callback parameters are the `ranges::slice` indicies and the segment index. \

				XTAL_FN0 redux(auto const &f)
				XTAL_0EX
				{
					redux(f, 0);
				}
				XTAL_FN0 redux(auto const &f, auto &&n)
				XTAL_0EX
				{
					redux(f, n);
				}
				XTAL_FN0 redux(auto const &f, auto &n)
				XTAL_0EX
				{
					for (delay_u i = 0, j = relay(); i != j; j = relay(i = j))
					{	f(i, j, n++);
					}
					--n;
				}

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
					if (0 == dot.head())
					{	return influx(dot.parent(), XTAL_REF_(oo)...);
					}
					else
					{	q_.push(XTAL_MOV_(dot));
						return influx(XTAL_REF_(oo)...);
					}
				}
				XTAL_FNX influx(context::delay_s<> d_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return influx(context::delay_s<XTAL_TYP_(oo)>(d_t.head(), XTAL_REF_(oo))...);
				}

			};
			///\note\
			When `N_event == 0`, scheduling is bypassed and `relay` is resolved w.r.t. `self`. \

			template <conflux::any_p R> requires (N_event == 0)
			class subtype<R>: public compose_s<R>
			{
				using R_ = compose_s<R>;

			protected:
				using relay_t = typename context::delay_s<>::head_t;
				XTAL_FN1_(relay_t) relay()          XTAL_0EX {return self().size();}
				XTAL_FN1_(relay_t) relay(relay_t i) XTAL_0EX {return self().size();}

				XTAL_FN0 redux(auto const &f)           XTAL_0EX {redux(f, 0);}
				XTAL_FN0 redux(auto const &f, auto &&n) XTAL_0EX {redux(f, n);}
				XTAL_FN0 redux(auto const &f, auto  &n) XTAL_0EX {f(0, relay(), n);}

			public:
				using R_::R_;
				using R_::self;

			};
		};

	};
};
template <typename T>
struct refine
:	_retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////

template <typename U>
struct defer
:	_retail::defer<U>
{
};
template <constant_q W> requires sigma_q<value_t<W>>
struct defer<W>
{
	using subkind = defer<value_t<W>>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

		using dispatch = typename S_::template dispatch<value_v<W>>;

	};
};
template <typename U>
struct refer
:	_retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
