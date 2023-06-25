#pragma once
#include "../conflux/any.hpp"//_retail
#include "../compound/delay.hpp"



#include "../common/all.hpp"

XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::conflux;
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
			using subkind = conflux::defer<T>;

			template <conflux::any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;
			public:
			//	using co::co;

				XTAL_CN2_(subtype);
				XTAL_CN4_(subtype);

				///\
				Constructs the `attach`ed `message` using its default, \
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

		template <size_t N_arity=2>
		struct dispatch
		{
			using subkind = attach;

			template <conflux::any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;
			
			public:
			//	using co::co;
				using co::self;

				XTAL_CN2_(subtype);
				XTAL_CN4_(subtype);

				XTAL_NEW_(explicit) subtype(size_t const &n)
				:	co(n)
				{
					assert(0 <= n and n < N_arity);
				}

				///\
				Alias of `method` that resolves the template-parameters using member-variables. \

				XTAL_OP2() (XTAL_DEF ...xs)
				XTAL_0EX
				{
					return (self().*deify<decltype(xs)...>()) (XTAL_REF_(xs)...);
				}

				///\
				Reifies `method` as a (potentially stateful) lambda function (e.g. for `_std::transform`), \
				resolving the template-parameters using member-variables. \

				XTAL_RN2_(template <typename ...Xs> XTAL_FN2 reify()
				,	_std::bind_front(deify<Xs...>(), &self())
				)

				///\
				Resolves the overloaded function-pointer for the given types, \
				indexing the _retail template-parameter with the corresponding message-value/subtype `T`. \

				template <typename ...Xs>
				XTAL_FN2 deify()
				XTAL_0FX
				{
					return deify(being<Xs...>::template method<>);
				}
				XTAL_FN2 deify(auto const &fs)
				XTAL_0FX
				{
					return co::deify(fs[co::head()]);
				}

				///\
				Defines the subtype-indexed function-pointer table, \
				dynamically indexed by message-value/subtype `T` and statically-generated with `N_arity` entries. \

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
							using doing = typename co::template being<Xs...>;
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

			template <conflux::any_q R> requires (T::tuple_size::value == 0)
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;
			public:
				using co::co;
				using co::defuse;

				XTAL_FNX defuse(XTAL_DEF_(is_q<T>) t)
				XTAL_0EX
				{
					return 1;
				}

			};
		};
		template <int N_future=-1>
		struct hold
		{
			template <conflux::any_q R>
			class subtype: public compose_s<R>
			{
				using co = compose_s<R>;

				using delay_t = compound::delay_t;
				using event_t = compound::delay_s<T>;
				using queue_t = typename compose_s<unit_t
				,	collect<N_future>
				,	collate<event_t>
				>::template siphon<1>::type;

				delay_t d_{0};
				queue_t q_;

			public:
				using co::co;
				using co::self;

				///\
				Invokes `influx` on the super-instance after clearing the schedule iff completed. \

				XTAL_FNX influx(XTAL_DEF ...oo)
				XTAL_0EX
				{
					q_.abandon(0 < q_.completed() and 0 == q_.remaining() and ((d_ = 0), 1));
					return co::influx(XTAL_REF_(oo)...);
				}

				///\
				\returns the aggregate `flux` of queuing the messages with the given delay.. \

				XTAL_FNX influx(compound::delay_s<> d_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return influx(compound::delay_s<XTAL_TYP_(oo)>(d_t.head(), XTAL_REF_(oo))...);
				}
				XTAL_FNX influx(compound::delay_s<T> dot, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(influx(XTAL_REF_(oo)...)) (q_.push(_std::move(dot)));
				}

				template <auto...>
				XTAL_FN1_(T) method()
				XTAL_0EX
				{
					return q_.advance(d_++ == q_.next().head()).tail();
				}
			//	TODO: Once the phasor-type is settled, define a `method` that updates only on reset. \

			};
		};
		///\
		Provides a queue for this message-type `T` on the target object. \
		Messages `influx`ed with an integer prefix will be delay by the given amount. \
		\
		NOTE: Only supports decorating `processor::atom`. \
		\
		TODO: Use deep introspection to automatically `interrupt` viable sources/targets. \
		\
		TODO: Use `message::sequel` to convert absolute delays to relative delays? \
		\
		TODO: Allow for scheduling beyond the current window by offsetting all future events? \
		\
		TODO: Investigate whether recursively `influx`ing the tail is a viable approach to \
		managing collections of `message`s (e.g. presets). \
		\
		TODO: Define a `message::bundle` that `std::tuple`s the provided types. \
		The implementation of `interrupt` in that case might be able to use `std::variant`. \

		template <int N_future=-1>
		struct interrupt
		{
			template <conflux::any_q R>
			class subtype: public compose_s<R>
			{
				using co = compose_s<R>;
			
				using delay_t = compound::delay_t;
				using event_t = compound::delay_s<T>;
				using queue_t = typename compose_s<unit_t
				,	collect<N_future>
				,	collate<event_t>
			//	>::sluice::type;
				>::template siphon<0>::type;

				queue_t q_;

				XTAL_FN2 next_tail() XTAL_0EX {return q_.next().template head<1>();}
				XTAL_FN2 next_head() XTAL_0EX {return q_.next().template head<0>();}
				
				XTAL_FN2_(delay_t) nearest_head(delay_t i)
				XTAL_0EX
				{
					return _std::min<delay_t>({nearest_head(), i});// NOTE: `initializer_list` required for `RELEASE`.
				}
				XTAL_FN2_(delay_t) nearest_head()
				XTAL_0EX
				{
					return 0 < q_.remaining()? next_head(): _std::numeric_limits<delay_t>::max();
				}

				XTAL_FN2_(delay_t) furthest_head()
				XTAL_0EX
				{
					return self().size();
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

				XTAL_FNX influx(compound::delay_s<> d_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return influx(compound::delay_s<XTAL_TYP_(oo)>(d_t.head(), XTAL_REF_(oo))...);
				}
				XTAL_FNX influx(compound::delay_s<T> dot, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return 0 == dot.head()? influx(dot.tail(), XTAL_REF_(oo)...):
						XTAL_FLX_(influx(XTAL_REF_(oo)...)) (q_.push(_std::move(dot)));
				}

			protected:
				///\
				Relays all queued events while invoking the supplied callback for each intermediate section. \

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
					for (delay_t i = 0, j = delay(); i != j; j = relay(i = j))
					{	f(i, j, n++);
					}
					--n;
				}

				///\
				Invokes `influx` for all events up-to the given delay `i`. \
				
				///\
				\returns the `delay()` until q_.next event. \

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
					i = delay(); if (i == furthest_head()) q_.abandon();
					return i;
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
					{	return nearest_head(furthest_head());
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
template <constant_q W> requires sigma_q<value_t<W>>
struct defer<W>
{
	using subkind = defer<value_t<W>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		using dispatch = typename co::template dispatch<value_v<W>>;

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
