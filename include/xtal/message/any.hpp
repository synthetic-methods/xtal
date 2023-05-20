#pragma once
#include "../control/any.hpp"//_detail






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _detail = xtal::control;
#include "../common/any.ipp"

////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that defines `T` with `As...::subtype` applied. \

template <typename T>
struct define
{
	using subkind = _detail::define<T>;

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
				Constructs the `attach`ed `message` using its default, \
				before `forward`ing the arguments to `this`. \

				XTAL_NEW_(explicit) subtype(XTAL_DEF... xs)
				XTAL_0EX
				:	co(T(), XTAL_REF_(xs)...)
				{
				}

			//	TODO: Specialize a `process`'s `interrupter` to `interrupt` `T` automatically when lifted to a `processor`. \

			};
		};
		///\
		Attaches `T` as a member of `this`, appending it to the arguments used by `reify`. \

		template <delta_t N_arity=2>
		struct dispatch
		{
			static_assert(0 < N_arity);

			using subkind = attach;

			template <context::any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;
			public:
				using co::co;
				using co::self;
				using co::head;

				XTAL_NEW subtype(XTAL_DEF_(as_q<delta_t>) n)
			//	:	co(XTAL_REF_(n))
				:	co(n)
				{
					assert(0 <= n and n < N_arity);
				}

				///\
				Alias of `method` that resolves the template-parameters using member-variables. \

				XTAL_OP2() (XTAL_DEF... xs)
				XTAL_0EX
				{
					auto const &def = deify<decltype(xs)...>();
					return (self().*def)(XTAL_REF_(xs)...);
				}

				///\
				Reifies `method` as a (potentially stateful) lambda function (e.g. for `_std::transform`), \
				resolving the template-parameters using member-variables. \

				template <typename... Xs>
				XTAL_FN2 reify()
				XTAL_0EX
				{
					auto const &def = deify<Xs...>();
					return [this, def] (XTAL_DEF... xs)
						XTAL_0FN_((self().*def)(XTAL_REF_(xs)...))
					;
				}

				///\
				Resolves the overloaded function-pointer for the given types, \
				indexing the _detail template-parameter with the corresponding message-value/subtype `T`. \

				template <typename... Xs>
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
				dynamically indexed by message-value/subtype `T` and statically-generated with `N_arity` entries. \

				template <typename... Xs>
				struct being
				{
					template <auto... Ms>
					struct resolve
					{
						template <sigma_t... Ns>
						XTAL_FZ2 method_f(seek_t<Ns...>)
						XTAL_0EX
						{
							using doing = typename co::template being<Xs...>;
							return _std::array{(doing::template method<Ms..., Ns>)...};
						}
						XTAL_LET method_m = method_f(seek_v<N_arity>);
					
					};

					template <auto... Ms>
					XTAL_LET method = resolve<Ms...>::method_m;
				
				};

			};
		};
		template <delta_t N_future=-1>
		struct hold
		{
			template <context::any_q R>
			class subtype: public compose_s<R>
			{
				using co = compose_s<R>;

				using index_t = iota_t;
				using event_t = compose_s<T, content::confer<index_t>>;
				using stack_t = buffer_vector_t<N_future, event_t>;
				using point_t = typename stack_t::iterator;
				using count_t = typename stack_t::difference_type;

				using current_t = event_t const &;

				stack_t stack_m;
				point_t point_m;
				index_t index_m;

			public:
				using co::co;
				using co::self;

				XTAL_NEW subtype()
				:	co()
				,	stack_m {event_t(_std::numeric_limits<index_t>::max())}
				,	point_m {stack_m.begin()}
				,	index_m {0}
				{
				}

			protected:
				XTAL_FN2_(point_t) ending()
				XTAL_0EX
				{
					return _std::next(stack_m.begin(), stack_m.size() - 1);
				}
				XTAL_FN2_(point_t) beginning()
				XTAL_0EX
				{
					return stack_m.begin();
				}

				XTAL_FN2_(count_t) suspended()
				XTAL_0EX
				{
					return ending() - point_m;
				}
				XTAL_FN2_(count_t) completed()
				XTAL_0EX
				{
					return point_m - beginning();
				}

				XTAL_FN2 next()
				XTAL_0EX
				{
					return peek(1);
				}
				XTAL_FN2 next_tail()
				XTAL_0EX
				{
					return next().tail();
				}
				XTAL_FN2 next_head()
				XTAL_0EX
				{
					return next().head();
				}

				XTAL_FN2_(current_t) peek(index_t idx)
				XTAL_0EX
				{
					return *(point_m + idx);
				}
				XTAL_FN1_(current_t) advance(bool proceed=true)
				XTAL_0EX
				{
					point_m += proceed;
					return *point_m;
				}
				XTAL_FN1_(current_t) abandon(bool proceed=true)
				XTAL_0EX
				{
					if (proceed)
					{
						stack_m.erase(beginning(), ending());
						point_m = beginning();
						index_m = 0;
					}
					return *point_m;
				}
				
				///\
				Delays `msg` with the supplied `idx`. \
				\
				NOTE: Duplicate indicies are overwritten (only `event_t::head`s are compared by `==` etc). \

				XTAL_FN1_(void) poke(index_t idx, XTAL_DEF_(is_q<T>) msg)
				XTAL_0EX
				{
					auto const ex = event_t(idx, XTAL_REF_(msg));
					auto e_ = _std::lower_bound(beginning(), ending(), ex);
					if (*e_ == ex) *e_ = ex; else stack_m.insert(e_, {ex});
				}

			public:
				///\
				Invokes `influx` on the super-instance. \

				XTAL_FN2_(iota_t) influx(XTAL_DEF... etc)
				XTAL_0EX
				{
					abandon(0 < completed() and 0 == suspended());
					return co::influx(XTAL_REF_(etc)...);
				}

				///\
				Delays `msg, etc...` with the supplied `idx`. \
				\
				\returns the `influx` result if the `idx == 0`, `-1` otherwise. \

				XTAL_FN2_(iota_t) influx(index_t idx, XTAL_DEF_(is_q<T>) msg, XTAL_DEF... etc)
				XTAL_0EX
				{
					poke(idx, XTAL_REF_(msg));
					return influx(idx, XTAL_REF_(etc)...);
				}
				XTAL_FN2_(iota_t) influx(index_t idx)
				XTAL_0EX
				{
					return -1;
				}

			public:
				template <auto...>
				XTAL_FN1_(T) method()
				XTAL_0EX
				{
					return advance(index_m++ == next_head()).tail();
				}
			//	TODO: Once the phasor-type is settled, \
				define `method` that updates only on reset. \

			};
		};
		///\
		Provides a queue for this message-type `T` on the target object. \
		Messages `influx`ed with an integer prefix will be delayed by the given amount. \
		\
		NOTE: Only supports decorating `processor::vectorize`. \
		\
		TODO: Use deep introspection to automatically `interrupt` viable sources/targets. \
		\
		TODO: Use `message::serial` to convert absolute delays to relative delays? \
		\
		TODO: Allow for scheduling beyond the current window by offsetting all future events? \
		\
		TODO: Investigate whether recursively `influx`ing the `tail` is a viable approach to \
		managing collections of `messages` (e.g. presets). \
		\
		TODO: Define a `message::bundle` that `std::tuple`s the provided types. \
		The implementation of `interrupt` in that case might be able to use `std::variant`. \

		template <delta_t N_future=-1>
		struct interrupt
		{
			template <context::any_q R>
			class subtype: public compose_s<R>
			{
				using co = compose_s<R>;

				using index_t = iota_t;
				using event_t = compose_s<T, content::confer<index_t>>;
				using queue_t = buffer_funnel_t<N_future, event_t>;
				using count_t = typename queue_t::size_type;

				using current_t = void;

				queue_t queue_m;

				XTAL_FN2_(count_t) suspended()
				XTAL_0EX
				{
					return queue_m.size();
				}
				XTAL_FN2_(count_t) completed()
				XTAL_0EX
				{
					return 0;
				}

				XTAL_FN2 next()
				XTAL_0EX
				{
					return queue_m.top();
				}
				XTAL_FN2 next_tail()
				XTAL_0EX
				{
					return next().tail();
				}
				XTAL_FN2 next_head()
				XTAL_0EX
				{
					return next().head();
				}
				XTAL_FN2 nearest_head()
				XTAL_0EX
				{
					return 0 < suspended()? next_head(): _std::numeric_limits<index_t>::max();
				}
				XTAL_FN2 nearest_head(index_t idx)
				XTAL_0EX
				{
					return _std::min<index_t>({nearest_head(), idx});
				//	return _std::min<index_t>(nearest_head(), idx);// NOTE: `min` weirds out in `RELEASE` (known issue).
				}

				XTAL_FN1_(current_t) advance(bool proceed=true)
				XTAL_0EX
				{
					if (proceed)
					{
						queue_m.pop();
					}
				}
				XTAL_FN1_(current_t) abandon(bool proceed=true)
				XTAL_0EX
				{
					if (proceed)
					{
						redux();
					}
				}
				XTAL_FN1_(void) poke(index_t idx, XTAL_DEF_(is_q<T>) msg)
				XTAL_0EX
				{
				//	TODO: Handle duplicates? \

					queue_m.emplace(idx, XTAL_REF_(msg));
				}

			public:
				using co::co;
				using co::self;

				///\
				Enqueues the given event (2nd argument) at the supplied `delay` (1st argument). \
				\
				\returns the `influx` result if the `delay == 0`, `-1` otherwise. \

				XTAL_FN2_(iota_t) influx(index_t idx, XTAL_DEF_(is_q<T>) msg, XTAL_DEF... etc)
				XTAL_0EX
				{
					if (0 == idx)
					{
						iota_t const _ = co::influx(XTAL_REF_(msg));
						return !_?0:_ & influx(idx, XTAL_REF_(etc)...);
					}
					else
					{
						assert(0 < idx);
						poke(XTAL_REF_(idx), XTAL_REF_(msg));
						return -1;
					}
				}
				XTAL_FN2_(iota_t) influx(index_t idx)
				XTAL_0EX
				{
					return -1;
				}
				///\
				Invokes `influx` on the super-instance. \

				XTAL_FN2_(iota_t) influx(XTAL_DEF... etc)
				XTAL_0EX
				{
					return co::influx(XTAL_REF_(etc)...);
				}

			protected:
				///\
				Relays all queued events while invoking the supplied callback for each intermediate section. \

				XTAL_FN1_(void) redux(auto const &dux)
				XTAL_0EX
				XTAL_IF2 (index_t i, index_t j) {dux(i, j);}
				{
					index_t i = 0, j = delay();
					for (; i != j; j = relay(i = j))
					{
						dux(i, j);
					}
					assert(i == self().size());
				}
				///\
				Relays all queued events without processing. \

				XTAL_FN1_(void) redux()
				{
					redux([] (index_t m, index_t n) XTAL_0FN_(void()));
				}

				///\
				Invokes `influx` for all events up-to the supplied `delay`. \
				\returns the `delay()` until the next event. \

				XTAL_FN1_(index_t) relay(index_t idx)
				XTAL_0EX
				{
				//	if constexpr (requires {{co::relay()} -> iota_q;})
					if constexpr (0 < N_future)
					{
						co::relay(idx);
						while (0 < suspended() and next_head() <= idx)
						{
							auto const flx = co::influx(next_tail());
							advance();
						}
					}
					return delay();
				}

				///\
				\returns the minimum delay across all queues bound to `this`. \

				XTAL_FN2_(index_t) delay()
				XTAL_0EX
				{
				//	if constexpr (requires {{co::delay()} -> iota_q;})
					if constexpr (0 < N_future)
					{
						return nearest_head(co::delay());
					}
					else
					{
						return nearest_head(self().size());
					}
				}

			};
		};

	};	
};
////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct refine
{
	using subkind = _detail::refine<T>;

	template <any_q S>
	using subtype = compose_s<S, subkind>;

};

////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that proxies `U`. \

template <typename U>
struct defer
{
	using subkind = _detail::defer<U>;

	template <any_q S>
	using subtype = compose_s<S, subkind>;

};
template <cased_q W>
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
////////////////////////////////////////////////////////////////////////////////
///\
Produces a decorator `subtype<S>` that lifts the operations of `U`. \

template <typename U>
struct refer
{
	using subkind = _detail::refer<U>;

	template <any_q S>
	using subtype = compose_s<S, subkind>;

};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
