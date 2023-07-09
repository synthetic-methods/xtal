#pragma once
#include "../conflux/any.hpp"// `_retail`

#include "../context/cue.hpp"




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

				XTAL_CO0_(subtype);
				XTAL_CO4_(subtype);

				///\
				Constructs the `attach`ed `control` using its default, \
				before `forward`ing the arguments to `this`. \

				XTAL_CXN subtype(XTAL_DEF ...xs)
				XTAL_0EX
				:	R_(T(), XTAL_REF_(xs)...)
				{}

			//	TODO: Specialize a `process`'s `intermiter` to `intermit` `T` automatically when lifted to a `processor`. \

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

				XTAL_CO0_(subtype);
				XTAL_CO4_(subtype);

				XTAL_CXN subtype(size_t const &n)
				:	R_(n)
				{
					assert(0 <= n and n < N_arity);
				}


				XTAL_TO2_(
				XTAL_OP2() (XTAL_DEF ...xs), (self().*deify<decltype(xs)...>()) (XTAL_REF_(xs)...)
				)

				XTAL_TO4_(template <typename ...Xs>
				XTAL_FN2 reify(), _std::bind_front(deify<Xs...>(), &self())
				)

				template <typename ...Xs>
				XTAL_FN2 deify()
				XTAL_0FX
				{
					return deify(being<Xs...>::template method_m<>);
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
					template <auto ...Ks>
					struct resolve
					{
						template <size_t ...I>
						XTAL_CN2 method_f(seek_t<I...>)
						XTAL_0EX
						{
							using doing = typename R_::template being<Xs...>;
							return _std::array{(doing::template method_m<Ks..., I>)...};
						}
						XTAL_LET method_m = method_f(seek_f<N_arity> {});
					
					};
					template <auto ...Ks> XTAL_LET method_m = resolve<Ks...>::method_m;
					template <auto ...Ks> XTAL_USE method_t = decltype(method_m<Ks...>);
				
				};

			};
		};
		///\
		Attaches `T` as a namespace recognized by `this`. \

		struct prefix
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
		struct gauge
		{
			using subkind = attach;

			template <conflux::any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;
			
			public:
				using R_::R_;
				using R_::head;

				XTAL_FNX effuse(XTAL_DEF o)
				XTAL_0EX
				{
					if constexpr (is_q<T, XTAL_TYP_(o)>) {
						return o == head();
					}
					else {
						return R_::effuse(XTAL_REF_(o));
					}
				}

			};
		};
		struct emit
		{
			using subkind = attach;

			template <conflux::any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;
			
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
		struct pend
		{
			template <conflux::any_p R>
			class subtype: public R
			{
			public:
				using R::R;
				using R::self;

				using R::influx;
				///\returns the aggregate `flux` of queuing the controls with the given delay.. \

				XTAL_FNX influx(context::cue_s<> d_t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return self().influx(context::cue_s<XTAL_TYP_(oo)>(d_t.head(), XTAL_REF_(oo))...);
				}

			};
		};
		template <int N_event=-1>
		struct hold
		{
			using event_u = context::cue_s<T>;
			using delay_u = typename event_u::head_t;
			using spool_u = typename collage_t<event_u, N_event>::spool_t;

			using subkind = pend;

			template <conflux::any_p R> requires (2 <= size_t(N_event))
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;
				
				delay_u d_{0};
				spool_u q_{event_u::template sentry<-1>(), event_u::template sentry<+1>()};

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
					return q_.advance(d_++ == q_.top().head()).parent();
				}
			//	TODO: Once the phasor-type is settled, define a `method` that updates only on reset. \

			};
		};
		///\
		Provides a queue for this control-type `T` on the target object, \
		scheduled via `influx` and processed in segments via `replay`. \

		///\todo\
		Allow for scheduling beyond the current window, \
		possibly using `control::sequel` to convert between absolute and relative delays. \

		template <int N_event=-1>
		struct intermit
		{
			using event_u = context::cue_s<T>;
			using delay_u = typename event_u::head_t;
			using spool_u = typename collage_t<event_u, N_event>::spool_t;

			using subkind = pend;

			template <conflux::any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

				spool_u q_{event_u::template sentry<1>()};

				XTAL_TO4_(XTAL_FN2 next_tail(), q_.top().parent())
				XTAL_TO4_(XTAL_FN2 next_head(), q_.top().head())

			protected:
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

				///\
				Relays all queued events while invoking the supplied callback for each intermediate segment. \
				The callback parameters are the `ranges::slice` indicies and the segment index. \

				XTAL_FN0 replay(auto const &f)
				XTAL_0EX
				{
					replay(f, 0);
				}
				XTAL_FN0 replay(auto const &f, auto &&n)
				XTAL_0EX
				{
					replay(f, n);
				}
				XTAL_FN0 replay(auto const &f, auto &n)
				XTAL_0EX
				{
					for (delay_u i = 0, j = delay(); i != j; j = relay(i = j)) {
						f(i, j, n++);
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
					if (0 == dot.head()) {
						return influx(dot.parent(), XTAL_REF_(oo)...);
					}
					else {
						q_.push(XTAL_MOV_(dot));
						return influx(XTAL_REF_(oo)...);
					}
				}

			};
			///\note\
			When `N_event == 0`, scheduling is bypassed and `relay` is resolved w.r.t. `self`. \

			template <conflux::any_p R> requires (N_event == 0)
			class subtype<R>: public R
			{
			protected:
				XTAL_FN1_(delay_u) delay()          XTAL_0EX {return self().size();}
				XTAL_FN1_(delay_u) relay(delay_u i) XTAL_0EX {return self().size();}

				XTAL_FN0 replay(auto const &f)           XTAL_0EX {replay(f, 0);}
				XTAL_FN0 replay(auto const &f, auto &&n) XTAL_0EX {replay(f, n);}
				XTAL_FN0 replay(auto const &f, auto  &n) XTAL_0EX {f(0, delay(), n);}

			public:
				using R::R;
				using R::self;

			};
		};

	};
};
template <typename T>
struct refine
:	_retail::refine<T>
{};


////////////////////////////////////////////////////////////////////////////////

template <typename U>
struct defer
:	_retail::defer<U>
{};
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
{};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
