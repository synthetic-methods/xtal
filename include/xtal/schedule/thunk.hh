#pragma once
#include "./any.hh"
#include "../resource/spooled.hh"

#include "../algebra/differential/linear.hh"
#include "../flux/cue.hh"


XTAL_ENV_(push)
namespace xtal::schedule
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

///\
Provides an `in(flux )queue` for `X` on the target object, \
which produces a signal by successive calls to `method`. \

template <typename ...As>
struct thunk
{
	using subkind = bond::compose<As..., resource::spooled<nominal_t<-1>>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		static_assert(resource::spooled_q<S_>);

	public:
		using S_::S_;

		template <class ...Xs>
		struct inqueue
		{
			using subkind = typename S_::template inqueue<Xs...>;

			template <flux::any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
			
			protected:
				using typename R_::V_delay;
				using typename R_::V_event;
				using typename R_::U_event;

				XTAL_USE X_tip = typename U_event::cue_type;
				XTAL_SET K_tip =          U_event::cue_size::value;
				//\
				using V_shuttle = X_tip;
				using V_shuttle =      algebra::d_::linear_t<X_tip[K_tip]>;
				using U_shuttle =                   flux::cue_s<V_shuttle>;
				using U_spool   = typename S_::template spool_t<U_shuttle>;

			public:// CONSTRUCT
			//	using R_::R_;
				
				XTAL_CO0_(subtype)
				XTAL_CO1_(subtype)
				XTAL_CO4_(subtype)

			private:// ACCESS
				using L_delay = _std::numeric_limits<V_delay>;

				U_spool u_spool{
					(U_shuttle) L_delay::min(),
					(U_shuttle) L_delay::max()
				};
				U_shuttle u_shuttle{};

				XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET head_(), u_shuttle.head())
				XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET then_(), u_shuttle.tail())

				XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET head_(int i), u_spool.begin(i)->head())
				XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET then_(int i), u_spool.begin(i)->tail())

			public:// OPERATE
				using R_::self;

				template <auto ...>
				XTAL_LET method()
				XTAL_0EX
				{
					return u_spool.advance(head_()++ == head_(1))
					->	tail().apply([this] XTAL_1FN_(method));
				}
				template <auto ...>
				XTAL_DEF_(return,inline)
				XTAL_LET method(V_shuttle &x, auto &&...)
				XTAL_0EX
				{
					if constexpr (algebra::d_::linear_q<V_shuttle>) {
						return x++(0);
					}
					else {
						return x;
					}
				}

			public:// *FLUX

				XTAL_TNX efflux(auto &&...oo)
				XTAL_0EX
				{
					compact_();

					return R_::efflux(XTAL_REF_(oo)...);
				}
				XTAL_TNX influx(XTAL_ARG_(X_tip) &&o)
				XTAL_0EX
				{
					compact_();
					
					if constexpr (is_q<U_shuttle, decltype(o)>) {
						return then_(0).influx(XTAL_REF_(o));
					}
					else {
						return then_(0).influx(V_shuttle{XTAL_REF_(o)});
					}
				}
				using R_::influx;

			public:// *FUSE_
				
				XTAL_TNX infuse(auto &&o)
				XTAL_0EX
				{
					return R_::infuse(XTAL_REF_(o));
				}
				XTAL_TNX infuse(flux::cue_q auto &&o)
				XTAL_0EX
				{
					if constexpr (is_q<U_shuttle, decltype(o)>) {
						return shuttle_(XTAL_REF_(o));
					}
					else {
						return shuffle_(XTAL_REF_(o));
					}
				}
				
			private:
				//\
				Enqueues the given message. \

				XTAL_TNX shuttle_(XTAL_ARG_(U_shuttle) &&o)
				XTAL_0EX
				{
					compact_(o);
					u_spool.push(XTAL_REF_(o));
					return 0;
				}
				XTAL_TNX shuttle_(V_delay v, auto &&...oo)
				XTAL_0EX
				{
					return shuttle_(U_shuttle(v, V_shuttle{XTAL_REF_(oo)...}));
				}
				
			private:
				//\
				Unpacks the given message, \
				allowing for gradient calculation/requeueing. \
				
				XTAL_TNX shuffle_(flux::cue_q auto &&o, auto &&...oo)
				XTAL_0EX
				{
					return shuffle_(o.tail(), o.head(), XTAL_REF_(oo)...);
				}
				XTAL_TNX shuffle_(XTAL_ARG_(X_tip) &&x1, V_delay t1)
				XTAL_0EX
				{
					return shuttle_(t1, x1);
				}
				XTAL_TNX shuffle_(XTAL_ARG_(X_tip) &&x1, V_delay t1, V_delay t0)
				XTAL_0EX
				{
					if (t0 < t1) {
						//\
						auto const i0 = flux::cue_s<>(t0);
						auto const i0 = U_shuttle(t0);
						//\
						auto const x0 = V_shuttle(u_spool.scan(i0)->tail()) (0);
						auto const x0 = V_shuttle(_std::prev(u_spool.scan(i0))->tail()) (0);
						auto const x_ = x1 - x0;
						double const t_ = t1 - t0;
						(void) shuttle_(t0, x0, x_/t_);
					}
					return shuffle_(x1, t1);
				}
			
			private:
				//\
				Reset the play-head, \
				clearing all processed events, \
				bringing forward any future events. \

				XTAL_LET compact_()//TODO: Filter somehow?
				XTAL_0EX -> void
				{
					V_delay const v_delay = head_(); head_() = 0;
					(void) u_spool.abandon(u_spool.empty());
					for (auto &u : u_spool.span(-1)) {
						u -= v_delay;
					}
				}
				XTAL_LET compact_(V_delay const &v)
				XTAL_0EX -> void
				{
					if (v < u_shuttle.head()) {
						compact_();
					}
				}
				XTAL_LET compact_(flux::cue_q auto const &o)
				XTAL_0EX -> void
				{
					compact_(o.head());
				}

			};
		};

	};
};
template <class ...Xs>
using thunk_t = confined_t<thunk<Xs...>>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
