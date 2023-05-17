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

			template <context::any_q _S>
			class subtype: public compose_s<_S, subkind>
			{
				using co = compose_s<_S, subkind>;
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

			//	TODO: Specialize a `process`'s `suspender` to `suspend` `T` automatically when lifted to a `processor`. \

			};
		};
		///\
		Attaches `T` as a member of `this`, appending it to the arguments used by `reify`. \

		template <delta_t N=2>
		struct dispatch
		{
			static_assert(0 < N);

			using subkind = attach;

			template <context::any_q _S>
			class subtype: public compose_s<_S, subkind>
			{
				using co = compose_s<_S, subkind>;
			public:
				using co::co;
				using co::self;
				using co::head;

				XTAL_NEW subtype(XTAL_DEF_(as_q<delta_t>) n)
			//	:	co(XTAL_REF_(n))
				:	co(n)
				{
					assert(0 <= n and n < N);
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
				dynamically indexed by message-value/subtype `T` and statically-generated with `N` entries. \

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
						XTAL_LET method_m = method_f(seek_v<N>);
					
					};

					template <auto... Ms>
					XTAL_LET method = resolve<Ms...>::method_m;
				
				};

			};
		};

		///\
		Provides a queue for this message-type `T` on the target object. \
		Messages `influx`ed with an integer prefix will be delayed by the given amount. \
		\
		NOTE: Only currently supported when supplied as a decorator to `processor::vectorize`. \
		\
		NOTE: Use deep introspection to automatically `suspend` viable sources/targets.. \
		\
		TODO: Use `message::serial` to convert absolute delays to relative delays? \
		\
		TODO: Allow for scheduling beyond the current window by offsetting all future events? \
		\
		TODO: Investigate whether recursively `influx`ing the `tail` is a viable approach to \
		managing collections of `messages` (e.g. presets). \
		\
		TODO: Define a `message::bundle` that `std::tuple`s the provided types. \
		The implementation of `suspend` in that case might be able to use `std::variant`. \

		template <iota_t N=-1>
		struct suspend
		{
			template <context::any_q _S>
			class subtype: public compose_s<_S>
			{
				using co = compose_s<_S>;

				using event_t = compose_s<T, content::confer<iota_t>>;
				using funnel_t = buffer_funnel_t<N, event_t>;

				funnel_t funnel_m;

			public:

				XTAL_FN2 next_tail()
				XTAL_0EX
				{
					return funnel_m.top().tail();
				}
				XTAL_FN2 next_head()
				XTAL_0EX
				{
					return funnel_m.top().head();
				}
				XTAL_FN2 nearest_head()
				XTAL_0EX
				{
					return funnel_m.empty()? _std::numeric_limits<iota_t>::max(): next_head();
				}
				XTAL_FN2 nearest_head(iota_t i)
				XTAL_0EX
				{
				//	NOTE: The curly braces here mitigate reference weirdness for `release` builds. \

					return _std::min<iota_t>({nearest_head(), i});
				}

			public:
				using co::co;
				using co::self;

				///\
				Enqueues the given event (2nd argument) at the supplied `delay` (1st argument). \
				\
				\returns the `influx` result if the `delay == 0`, `-1` otherwise. \

				XTAL_FN2_(iota_t) influx(iota_t i, XTAL_DEF_(is_q<T>) t)
				XTAL_0EX
				{
					assert(0 <= i);
					if (0 < i)
					{
						funnel_m.emplace(XTAL_REF_(i), XTAL_REF_(t));
						return -1;
					}
					else
					{
						return co::influx(XTAL_REF_(t));
					}
				}
				///\
				Invokes `influx` on the super-instance. \

				XTAL_FN2_(iota_t) influx(XTAL_DEF... ws)
				XTAL_0EX
				{
					return co::influx(XTAL_REF_(ws)...);
				}

		//	protected:

				///\
				Relays all queued events while invoking the supplied callback for each intermediate section. \

				XTAL_FN1_(void) redux(auto const &f)
				XTAL_0EX
				XTAL_IF2 (iota_t i, iota_t j) {f(i, j);}
				{
					iota_t i = 0, j = delay();
					for (; i != j; j = relay(i = j))
					{
						f(i, j);
					}
					assert(i == self().size());
				}
				///\
				Relays all queued events without processing. \

				XTAL_FN1_(void) redux()
				{
					redux([] (iota_t m, iota_t n) XTAL_0FN_(void()));
				}

				///\
				Invokes `influx` for all events up-to the supplied `delay`. \
				\returns the `delay()` until the next event. \

				XTAL_FN1_(iota_t) relay(iota_t i)
				XTAL_0EX
				{
				//	if constexpr (requires {{co::relay()} -> iota_q;})
					if constexpr (0 < N)
					{
						co::relay(i);
						while (funnel_m.size() and next_head() <= i)
						{
							auto const _ = co::influx(next_tail()); funnel_m.pop();
						}
					}
					return delay();
				}

				///\
				\returns the minimum delay across all queues bound to `this`. \

				XTAL_FN2_(iota_t) delay()
				XTAL_0EX
				{
				//	if constexpr (requires {{co::delay()} -> iota_q;})
					if constexpr (0 < N)
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
