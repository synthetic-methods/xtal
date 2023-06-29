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
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;

		///\
		Attaches `T` as a member of `this`. \

		struct attach
		{
			using subkind = conflux::defer<T>;

			template <conflux::any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;
			
			public:
			//	using co::co;

				XTAL_CN2_(subtype);
				XTAL_CN4_(subtype);

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

		template <size_t N_arity=2>
		struct dispatch
		{
			using subkind = attach;

			template <conflux::any_p R>
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
					return co::deify(fs[co::head()]);
				}

				///\
				Defines the subtype-indexed function-pointer table, \
				dynamically indexed by control-value/subtype `T` and statically-generated with `N_arity` entries. \

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

			template <conflux::any_p R> requires (T::tuple_size::value == 0)
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
		template <int N_event=-1>
		struct hold
		{
			template <conflux::any_p R>
			class subtype: public compose_s<R>
			{
				using co = compose_s<R>;

				using event_t = context::delay_s<T>;
				using delay_t = typename event_t::head_t;
				using limit_t = _std::numeric_limits<delay_t>;
				using queue_t = typename collage_t<N_event, event_t>::siphon_t;

				delay_t d_{0};
				queue_t q_{(event_t) limit_t::min(), (event_t) limit_t::max()};

			public:
				using co::co;
				using co::self;


				using co::influx;
				///\returns the aggregate `flux` of queuing the controls with the given delay.. \

				XTAL_FNX influx(event_t dot, XTAL_DEF ...oo)
				XTAL_0EX
				{
					if (dot.head() < d_ and q_.empty())
					{	q_.abandon().head(d_ = 0);
					}
					q_.push(_std::move(dot));
					return co::influx(oo...);
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
					return q_.advance(d_++ == q_.top().head()).tail();
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
				using co = compose_s<R>;

				using event_t = context::delay_s<T>;
				using delay_t = typename event_t::head_t;
				using limit_t = _std::numeric_limits<delay_t>;
				using queue_t = typename collage_t<N_event, event_t>::siphon_t;

				queue_t q_{(event_t) limit_t::max()};

				XTAL_RN2_(XTAL_FN2 next_tail(), q_.top().template head<1>())
				XTAL_RN2_(XTAL_FN2 next_head(), q_.top().template head<0>())
				XTAL_FN2 last_head()
				XTAL_0FX
				{
					if constexpr (requires {{co::relay()} -> is_q<delay_t>;})
					{	return co::relay();
					}
					else
					{	return delay_t(self().size());
					}
				}

			protected:
				///\
				Invokes `influx` for all events up-to the supplied delay `i`. \
				
				///\returns the delay until the next event. \

				XTAL_FN1_(delay_t) relay(delay_t i)
				XTAL_0EX
				{
					if constexpr (requires {{co::relay(i)} -> is_q<delay_t>;})
					{	co::relay(i);
						for (; 0 < q_.size() and next_head() <= i; q_.pop())
						{	(void) co::influx(next_tail());
						}
					}
					return relay();
				}
				XTAL_FN1_(delay_t) relay()
				XTAL_0EX
				{
					return _std::min<delay_t>({next_head(), last_head()});
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
					for (delay_t i = 0, j = relay(); i != j; j = relay(i = j))
					{	f(i, j, n++);
					}
					--n;
				}

			public:
				using co::co;
				using co::self;
				using co::influx;
				///\
				Invokes `influx` if the given delay `i == 0`, \
				otherwise enqueues the events `o, o...` at the specified index. \
				
				XTAL_FNX influx(event_t dot, XTAL_DEF ...oo)
				XTAL_0EX
				{
					if (0 == dot.head())
					{	return influx(dot.tail(), XTAL_REF_(oo)...);
					}
					else
					{	q_.push(_std::move(dot));
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
				using co = compose_s<R>;

			protected:
				using relay_t = context::delay_t;
				XTAL_FN1_(relay_t) relay()          XTAL_0EX {return self().size();}
				XTAL_FN1_(relay_t) relay(relay_t i) XTAL_0EX {return self().size();}

				XTAL_FN0 redux(auto const &f)           XTAL_0EX {redux(f, 0);}
				XTAL_FN0 redux(auto const &f, auto &&n) XTAL_0EX {redux(f, n);}
				XTAL_FN0 redux(auto const &f, auto  &n) XTAL_0EX {f(0, relay(), n);}

			public:
				using co::co;
				using co::self;

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
		using co = compose_s<S, subkind>;
	
	public:
		using co::co;

		using dispatch = typename co::template dispatch<value_v<W>>;

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
