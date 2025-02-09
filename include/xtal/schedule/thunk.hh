#pragma once
#include "./any.hh"
#include "../provision/spooled.hh"

#include "../atom/grade.hh"
#include "../flow/cue.hh"


XTAL_ENV_(push)
namespace xtal::schedule
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

///\
Provides an `in(flow )queue` for `X` on the target object, \
which produces a signal by successive calls to `method`. \

template <typename ...As>
struct thunk
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

		template <class ...Xs>
		struct inqueue
		{
			using superkind = typename S_::template inqueue<Xs...>;

			template <flow::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
			
			public:// CONSTRUCT
			//	using R_::R_;
				
				XTAL_NEW_(delete) (subtype, noexcept = default)
				XTAL_NEW_(create) (subtype, noexcept = default)
				XTAL_NEW_(move)   (subtype, noexcept = default)
				XTAL_NEW_(copy)   (subtype, noexcept = default)
				XTAL_NEW_(cast)   (subtype, noexcept)

				using typename R_::delay_type;
				using typename R_::event_type;

			private:// ACCESS
				using U_cued    = typename R_::event_type::cue_signature;
				using U_tailed  =      valued_u<U_cued   >;
				using V_shuttle = atom::grade_t<U_cued   >;
				using U_shuttle = flow::  cue_s<V_shuttle>;

				typename S_::template spool_t<U_shuttle>
				u_spool{bond::seek_t<>{}
				, 	_std::numeric_limits<delay_type>::min()
				,	_std::numeric_limits<delay_type>::max()
				};
				U_shuttle u_shuttle{};

				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) head_(), u_shuttle.head())
				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) then_(), u_shuttle.tail())

				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) head_(int i), u_spool.begin(i)->head())
				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) then_(int i), u_spool.begin(i)->tail())

			public:// OPERATE
				using R_::self;

				template <auto ...>
				XTAL_DEF_(return,inline,let)
				method(V_shuttle &x, auto &&...)
				noexcept -> auto
				{
					//\
					return x;
					return x++(0);
				}
				template <auto ...>
				XTAL_DEF_(return,inline,let)
				method()
				noexcept -> decltype(auto)
				{
					return u_spool.advance(head_()++ == head_(1))->
						tail().apply([this] XTAL_1FN_(function) (method));
				}

			public:// FLOW

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				fuse(auto &&o)
				noexcept -> signed
				{
					return R_::template fuse<N_ion>(XTAL_REF_(o));
				}
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					if constexpr (0 <= N_ion) {
						compact_();
					}
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}

				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(return,inline,let)
				flux(same_q<U_tailed> auto &&o)
				noexcept -> signed
				{
					compact_();
					
					if constexpr (same_q<U_shuttle, decltype(o)>) {
						return then_(0).template flux<N_ion>(XTAL_REF_(o));
					}
					else {
						return then_(0).template flux<N_ion>(V_shuttle{XTAL_REF_(o)});
					}
				}
				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(return,inline,let)
				fuse(flow::cue_q auto &&o)
				noexcept -> signed
				{
					if constexpr (same_q<U_shuttle, decltype(o)>) {
						return shuttle_(XTAL_REF_(o));
					}
					else {
						return shuffle_(XTAL_REF_(o));
					}
				}
				
			private:
				//\
				Enqueues the given message. \

				XTAL_DEF_(return,inline,let)
				shuttle_(same_q<U_shuttle> auto &&o)
				noexcept -> signed
				{
					compact_(o);
					u_spool.push(XTAL_REF_(o));
					return 0;
				}
				XTAL_DEF_(return,inline,let)
				shuttle_(delay_type v, auto &&...oo)
				noexcept -> signed
				{
					return shuttle_(U_shuttle(v, V_shuttle{XTAL_REF_(oo)...}));
				}
				
			private:
				//\
				Unpacks the given message, \
				allowing for gradient calculation/requeueing. \
				
				XTAL_DEF_(return,inline,let)
				shuffle_(flow::cue_q auto &&o, auto &&...oo)
				noexcept -> signed
				{
					return shuffle_(o.tail(), o.head(), XTAL_REF_(oo)...);
				}
				XTAL_DEF_(return,inline,let)
				shuffle_(same_q<U_tailed> auto &&x1, delay_type t1)
				noexcept -> signed
				{
					return shuttle_(t1, XTAL_REF_(x1));
				}
				XTAL_DEF_(return,let)
				shuffle_(same_q<U_tailed> auto &&x1, delay_type t1, delay_type t0)
				noexcept -> signed
				{
					if (t0 < t1) {
						//\
						auto const i0 = flow::cue_s<>(t0);
						auto const i0 = U_shuttle(t0);
						//\
						auto const x0 = V_shuttle(u_spool.scan(i0)->tail()) (0);
						auto const x0 = V_shuttle(_std::prev(u_spool.scan(i0))->tail()) (0);
						auto const x_ = x1 - x0;
						auto const t_ = t1 - t0;
						(void) shuttle_(t0, x0, x_/XTAL_ALL_(x_){t_});
					}
					return shuffle_(XTAL_REF_(x1), t1);
				}
			
			private:
				//\
				Reset the play-head, \
				clearing all processed events, \
				bringing forward any future events. \

				XTAL_DEF_(let)
				compact_()//TODO: Filter somehow?
				noexcept -> void
				{
					delay_type const v_delay = head_(); head_() = 0;
					(void) u_spool.abandon(u_spool.empty());
					for (auto &u : u_spool.span(-1)) {
						u -= v_delay;
					}
				}
				XTAL_DEF_(let)
				compact_(delay_type const &v)
				noexcept -> void
				{
					if (v < u_shuttle.head()) {
						compact_();
					}
				}
				XTAL_DEF_(let)
				compact_(flow::cue_q auto const &o)
				noexcept -> void
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
