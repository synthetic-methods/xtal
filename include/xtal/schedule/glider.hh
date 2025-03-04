#pragma once
#include "./any.hh"
#include "../provision/spooled.hh"

#include "../atom/grade.hh"
#include "../flow/cue.hh"


XTAL_ENV_(push)
namespace xtal::schedule
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Provides an `in(flow )queue` for the value `Y` on the target object,
producing a signal by successive calls to `method`.
*/
template <typename ...As>
struct glider
{
	using superkind = bond::compose<As..., provision::spooled<extent_constant_t<-1>>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		static_assert(provision::spooled_q<S_>);

	public:
		using S_::S_;

		template <class ...Ys>
		struct accept
		{
			static_assert(single_q<Ys...>);
			using superkind = bond::compose<typename S_::template accept<Ys...>>;

			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(flow::any_q<R>);
				using R_ = bond::compose_s<R, superkind>;
			
			public:// CONSTRUCT
				using R_::R_;
				
				using typename R_::delay_type;
				using typename R_::event_type;

			private:// ACCESS
				using V_limits = _std::numeric_limits<delay_type>;
				using U_layout = typename R_::event_type::layout_type;
				using U_hold =      valued_u<U_layout>;
				using U_ramp = atom::grade_t<U_layout>;
				using E_hold = flow::  cue_s<U_hold>;
				using E_ramp = flow::  cue_s<U_ramp>;
				using E_pipe = typename S_::template spool_t<E_ramp>;
				//\
				delay_type u_drip{};//FIXME: Confuses GCC/Ubuntu on CI...
				E_ramp u_drip{};
				E_pipe u_pipe{bond::seek_t<>{}, V_limits::min(), V_limits::max()};

				//\
				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) _drip(), u_drip)
				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) _drip(), u_drip.head())
				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)  head_(int i), u_pipe.begin(i)->head())
				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get)  tail_(int i), u_pipe.begin(i)->tail())

			public:// OPERATE
				using R_::self;

				/*!
				\brief   Advances the current position/ramp.
				\returns The next (interpolated) value.
				*/
				template <auto ...>
				XTAL_DEF_(return,inline,let)
				method()
				noexcept -> decltype(auto)
				{
					return u_pipe.advance(_drip()++ == head_(1))->
						tail().apply([this] (U_ramp &u_) XTAL_0FN_(to) (u_++(0)));
				}

			public:// FLOW

				/*!
				\brief   Forwards the message upstream.
				*/
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				fuse(auto &&o)
				noexcept -> signed
				{
					return R_::template fuse<N_ion>(XTAL_REF_(o));
				}
				/*!
				\brief   Enqueues the given event.
				\returns `0`.
				*/
				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(return,inline,let)
				fuse(in_q<E_hold, E_ramp, event_type> auto &&o)
				noexcept -> signed
				{
					enqueue(XTAL_REF_(o));
					return 0;
				}

				/*!
				\brief   Forwards the message upstream.
				*/
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					compact(0 <= N_ion);
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				/*!
				\brief   Updates the head of the signal.
				*/
				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(return,inline,let)
				flux(same_q<U_hold> auto &&o, auto &&...oo)
				noexcept -> signed
				{
					compact(0 <= N_ion);
					return [this, oo...] XTAL_1FN_(and) (R_::template flux<N_ion>(XTAL_REF_(oo)...))
						(tail_(0).template flux<N_ion>(U_ramp{XTAL_REF_(o)}));
				}
				
			protected:
				/*!
				\brief   Enqueues the given gradient event.
				*/
				XTAL_DEF_(mutate,inline,let)
				enqueue(same_q<E_ramp> auto &&o)
				noexcept -> void
				{
					compact(o);
					u_pipe.push(XTAL_REF_(o));
				}
				/*!
				\brief   Constructs and enqueues the given event.
				*/
				XTAL_DEF_(mutate,inline,let)
				enqueue(delay_type v, auto &&...oo)
				noexcept -> void
				{
					enqueue(E_ramp(v, U_ramp{XTAL_REF_(oo)...}));
				}
				
				/*!
				\brief   Deconstructs and enqueues the given event.
				*/
				XTAL_DEF_(mutate,inline,let)
				enqueue(flow::cue_q auto &&o, auto &&...oo)
				noexcept -> void
				{
					enqueue(o.tail(), o.head(), XTAL_REF_(oo)...);
				}
				/*!
				\brief   Enqueues the value `x1` at `t1`.
				*/
				XTAL_DEF_(mutate,inline,let)
				enqueue(same_q<U_hold> auto &&x1, delay_type t1)
				noexcept -> void
				{
					enqueue(t1, XTAL_REF_(x1));
				}
				/*!
				\brief   Enqueues the value `x1` at `t1`, ramping from `t0` to `t1`.
				*/
				XTAL_DEF_(mutate,let)
				enqueue(same_q<U_hold> auto &&x1, delay_type t1, delay_type t0)
				noexcept -> void
				{
					if (t0 < t1) {
						//\
						auto const i0 = flow::cue_s<>(t0);
						auto const i0 = E_ramp(t0);
						//\
						auto const x0 = U_ramp(u_pipe.scan(i0)->tail()) (0);
						auto const x0 = U_ramp(_std::prev(u_pipe.scan(i0))->tail()) (0);
						auto const x_ = x1 - x0;
						auto const t_ = t1 - t0;
						enqueue(t0, x0, x_/XTAL_ALL_(x_){t_});
					}
					enqueue(t1, XTAL_REF_(x1));
				}
			
			protected:
				/*!
				\brief   Reset the play-head, clearing all processed events, bringing forward any future events.
				*/
				XTAL_DEF_(let)
				compact(bool proceed=true)
				noexcept -> void
				{
					if (proceed) {
						delay_type const v_delay = _drip(); _drip() = 0;
						(void) u_pipe.abandon(u_pipe.empty());
						for (auto &u : u_pipe.span(-1)) {
							u -= v_delay;
						}
					}
				}
				XTAL_DEF_(let)
				compact(delay_type const &v)
				noexcept -> void
				{
					if (v < u_drip.head()) {
						compact();
					}
				}
				XTAL_DEF_(let)
				compact(flow::cue_q auto const &o)
				noexcept -> void
				{
					compact(o.head());
				}

			};
		};

	};
};
template <class ...Ys>
using glider_t = confined_t<glider<Ys...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
