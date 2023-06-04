#pragma once
#include "../context/any.hpp"//_retail
#include "../content/delay.hpp"



#include "../block/all.hpp"

XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::context;
#include "../common/all.hxx"
#include "../common/any.hxx"


////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that defines `T` with `As...::subtype` applied. \

template <typename T>
struct define
{
	using subkind = _retail::define<T>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		friend T;
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		///\
		Attaches `T` as a member of `this`. \

		struct attach
		{
			using control_t = T;
			using subkind = context::defer<T>;

			template <context::any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;
			public:
			//	using co::co;

				XTAL_CO2_(subtype);
				XTAL_CO4_(subtype);

				///\
				Constructs the `attach`ed `control` using its default, \
				before `forward`ing the arguments to `this`. \

				XTAL_NEW_(explicit) subtype(XTAL_DEF ...xs)
				XTAL_0EX
				:	co(T(), XTAL_REF_(xs)...)
				{
				}

			//	TODO: Specialize a `process`'s `interrupter` to `interrupt` `T` automatically when lifted to a `processor`. \

			};
		};
		///\
		Attaches `T` as a member of `this`, appending it to the arguments used by `reify`. \

		template <int N_arity=2> requires (0 < N_arity)
		struct dispatch
		{
			using control_t = T;
			using subkind = attach;

			template <context::any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;
			
			public:
			//	using co::co;
				using co::self;
				using co::head;

				XTAL_CO2_(subtype);
				XTAL_CO4_(subtype);

				XTAL_NEW_(explicit) subtype(int const &n)
			//	:	co(XTAL_REF_(n))
				:	co(n)
				{
					assert(0 <= n and n < N_arity);
				}

				///\
				Alias of `method` that resolves the template-parameters using member-variables. \

				XTAL_OP2() (XTAL_DEF ...xs)
				XTAL_0EX
				{
					auto const &def = deify<decltype(xs)...>();
					return (self().*def) (XTAL_REF_(xs)...);
				}

				///\
				Reifies `method` as a (potentially stateful) lambda function (e.g. for `_std::transform`), \
				resolving the template-parameters using member-variables. \

				template <typename ...Xs>
				XTAL_FN2 reify()
				XTAL_0EX
				{
					auto const &def = deify<Xs...>();
					return [this, def](XTAL_DEF ...xs)
						XTAL_0FN_((self().*def) (XTAL_REF_(xs)...))
					;
				}

				///\
				Resolves the overloaded function-pointer for the given types, \
				indexing the _retail template-parameter with the corresponding control-value/subtype `T`. \

				template <typename ...Xs>
				XTAL_FN2 deify()
				XTAL_0FX
				{
					return deify(being<Xs...>::template method<>);
				}
				
				XTAL_FN2 deify(auto const &fs)
				XTAL_0FX
				{
					return co::deify(fs[head()]);
				}

				///\
				Defines the subtype-indexed function-pointer table, \
				dynamically indexed by control-value/subtype `T` and statically-generated with `N_arity` entries. \

				template <typename ...Xs>
				struct being
				{
					template <auto ...Ms>
					struct atom
					{
						template <size_t ...Ns>
						XTAL_FZ2 method_f(seek_t<Ns...>)
						XTAL_0EX
						{
							using doing = typename co::template being<Xs...>;
							return _std::array{(doing::template method<Ms..., Ns>)...};
						}
						XTAL_LET method_m = method_f(seek_v<N_arity>);
					
					};

					template <auto ...Ms>
					XTAL_LET method = atom<Ms...>::method_m;
				
				};

			};
		};
		template <int N_future=-1>
		struct hold
		{
			template <context::any_q R>
			class subtype: public compose_s<R>
			{
				using co = compose_s<R>;

				using delay_t = content::delay_t;
				using event_t = content::delay_s<T>;
				using queue_t = block::sluice_t<N_future, event_t, 1>;

				queue_t q_;
				delay_t delay_m {0};

				XTAL_FN2 next     () XTAL_0EX {return q_.peek(1);}
				XTAL_FN2 next_tail() XTAL_0EX {return next().tail();}
				XTAL_FN2 next_head() XTAL_0EX {return next().head();}

			public:
				using co::co;
				using co::self;

				///\
				Invokes `influx` on the super-instance after clearing the schedule iff completed. \

				XTAL_FNX influx(XTAL_DEF ...oo)
				XTAL_0EX
				{
					q_.abandon(0 < q_.completed() and 0 == q_.remaining() and true_f(delay_m = 0));
					return co::influx(XTAL_REF_(oo)...);
				}

				///\
				\returns the aggregate `flux` of queuing the messages with the given delay.. \

				XTAL_FNX influx(content::delay_s<> d_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return influx(content::delay_s<XTAL_TYP_(oo)>(d_t.head(), XTAL_REF_(oo))...);
				}
				XTAL_FNX influx(content::delay_s<T> dot, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(influx(XTAL_REF_(oo)...)) (q_.poke(dot.head(), dot.tail()));
				}

				template <auto...>
				XTAL_FN1_(T) method()
				XTAL_0EX
				{
					return q_.advance(delay_m++ == next_head()).tail();
				}
			//	TODO: Once the phasor-type is settled, define a `method` that updates only on reset. \

			};
		};
		///\
		Provides a queue for this control-type `T` on the target object. \
		Messages `influx`ed with an integer prefix will be delay by the given amount. \
		\
		NOTE: Only supports decorating `processor::atom`. \
		\
		TODO: Use deep introspection to automatically `interrupt` viable sources/targets. \
		\
		TODO: Use `control::sequel` to convert absolute delays to relative delays? \
		\
		TODO: Allow for scheduling beyond the current window by offsetting all future events? \
		\
		TODO: Investigate whether recursively `influx`ing the tail is a viable approach to \
		managing collections of `control`s (e.g. presets). \
		\
		TODO: Define a `control::pack` that `std::tuple`s the provided types. \
		The implementation of `interrupt` in that case might be able to use `std::variant`. \

		template <int N_future=-1>
		struct interrupt
		{
			template <context::any_q R>
			class subtype: public compose_s<R>
			{
				using co = compose_s<R>;
			
			protected:
				using delay_t = content::delay_t;
				using event_t = content::delay_s<T>;
				using queue_t = block::siphon_t<N_future, event_t, 1>;

				queue_t q_;

				XTAL_FN2 next     () XTAL_0EX {return q_.top();}
				XTAL_FN2 next_tail() XTAL_0EX {return next().template head<1>();}
				XTAL_FN2 next_head() XTAL_0EX {return next().template head<0>();}
				
				XTAL_FN2 nearest_head()
				XTAL_0EX
				{
					return 0 < q_.remaining()? next_head(): _std::numeric_limits<delay_t>::max();
				}
				XTAL_FN2 nearest_head(delay_t i)
				XTAL_0EX
				{
					return _std::min<delay_t>({nearest_head(), i});// NOTE: `initializer_list` required for `RELEASE`.
				}

			public:
				using co::co;
				using co::self;
				using co::influx;
				///\
				Invokes `influx` if the given delay `i == 0`, \
				otherwise enqueues the events `o, o...` at the specified index. \
				\
				\returns the result of `influx` if `i == 0`, `-1` otherwise. \

				/*/
				XTAL_FNX influx(content::delay_s<> d_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return influx(content::delay_s<XTAL_TYP_(oo)>(d_t.head(), XTAL_REF_(oo))...);
				}
				XTAL_FNX influx(content::delay_s<T> dot, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return 0 == dot.head()? influx(XTAL_REF_(oo)...):
						XTAL_FLX_(influx(XTAL_REF_(oo)...)) (q_.poke(dot.head(), dot.tail()));
				}
				/*/
				XTAL_FNX infuse(XTAL_DEF o)
				XTAL_0EX
				{
					return co::infuse(XTAL_REF_(o));
				}
				XTAL_FNX infuse(content::delay_s<T> dot)
				XTAL_0EX
				{
					auto const i = dot.head();
					auto const t = dot.tail();
					return 0 == i? co::infuse(t): (q_.poke(i, t), -1);
				}
				XTAL_FNX influx(content::delay_s<> d_t, T t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto const i = d_t.head();
					return 0 == i? influx(t, XTAL_REF_(oo)...): infuse(content::delay_s<T>(i, t));
				}
				XTAL_FNX influx(content::delay_s<T> dot, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(influx(XTAL_REF_(oo)...)) (influx(content::delay_s<>(dot.head()), dot.tail()));
				}
				/***/

			protected:
				///\
				Relays all queued events while invoking the supplied callback for each intermediate section. \

				XTAL_FN0 redux(auto const &f)
				XTAL_0EX
				{
					for (delay_t i = 0, j = delay(); i != j; j = relay(i = j))
					{	f(i, j);
					}
				}
				XTAL_FN0 redux(auto const &f, auto &n)
				XTAL_0EX
				{
					for (delay_t i = 0, j = delay(); i != j; j = relay(i = j))
					{	f(i, j, n++);
					}
					--n;
				}

				///\
				Invokes `influx` for all events up-to the given delay `i`. \
				
				///\
				\returns the `delay()` until the next event. \

				XTAL_FN1_(delay_t) relay(delay_t i)
				XTAL_0EX
				{
					if constexpr (0 < N_future)
					{	co::relay(i);
						while (0 < q_.remaining() and next_head() <= i)
						{	(void) co::influx(next_tail());
							q_.advance();
						}
					}
					return delay();
				}

				///\
				\returns the minimum delay across all queues bound to `this`. \

				XTAL_FN2_(delay_t) delay()
				XTAL_0EX
				{
					if constexpr (0 < N_future)
					{	return nearest_head(co::delay());
					}
					else
					{	return nearest_head(self().size());
					}
				}

			};
		};

	};
};

template <typename T>
struct refine: _retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that proxies `U`. \

template <typename U>
struct defer
{
	using subkind = _retail::defer<U>;

	template <any_q S>
	using subtype = compose_s<S, subkind>;

};
template <constant_q W>
struct defer<W>
{
	using subkind = defer<typename W::value_type>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		using dispatch = typename co::template dispatch<W::value>;

	};
};

///\
Produces a decorator `subtype<S>` that lifts the operations of `U`. \

template <typename U>
struct refer: _retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
