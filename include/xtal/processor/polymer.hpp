#pragma once
#include "./any.hpp"
#include "./monomer.hpp"
#include "../context/voice.hpp"
#include "../message/mute.hpp"
#include "../message/resize.hpp"
#include "../message/sequel.hpp"

XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...>
struct polymer;

template <typename ...Ts>
XTAL_ASK polymer_q = conjunct_q<only_p<Ts, polymer>...>;

template <typename ...As>
XTAL_USE polymer_t = compose_s<only_t<polymer>, polymer<As...>>;

template <typename ...As>
XTAL_FZ2 polymer_f(XTAL_DEF u) {return polymer_t<XTAL_TYP_(u), As...>(XTAL_REF_(u));}


////////////////////////////////////////////////////////////////////////////////

template <typename ...As>
struct polymer
{
	using subkind = compose<As..., context::voice<constant_t<-1>>>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		using T_ = typename S_::self_t;
	
	public:
		using S_::S_;
		using S_::self;

		template <any_p Y> requires collect_q<S_>
		struct bond
		{
			using voice_u  = context::voice_s<Y>;
			using spool_u  = typename collage<voice_u, S_::ensemble>::spool_t;
			using buffer_u = typename S_::template fluid<iteratee_t<Y>>::type;
			using debuff_u = deranged_t<buffer_u>;
			using respan_u = message::respan_t<debuff_u>;
			using resize_u = message::resize_t<>;

			using subkind = compose<void
			,	concord::confer<debuff_u>
			,	concord:: defer<buffer_u>
			>;
			template <typename R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

				XTAL_NEW_(explicit) subtype(buffer_u &&buffer_o, XTAL_DEF ...etc)
				XTAL_0EX
				:	R_((debuff_u) buffer_o, XTAL_MOV_(buffer_o), XTAL_REF_(etc)...)
				{
				}

			protected:
				spool_u q_{voice_u::template limit<1>()};

			public:
				XTAL_NEW_(explicit) subtype(XTAL_DEF ...etc)
				XTAL_0EX
				:	subtype(buffer_u(), XTAL_REF_(etc)...)
				{
				}

				XTAL_CN2_(subtype);
				XTAL_CN4_(subtype);
			//	using R_::R_;
				using R_::self;


				XTAL_RN4_(XTAL_FN1 store(XTAL_DEF... oo), R_::template head<1>(XTAL_REF_(oo)...))
				XTAL_RN4_(XTAL_FN1 serve(XTAL_DEF... oo), R_::template head<0>(XTAL_REF_(oo)...))


				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return serve();
				}

				///\
				Responds to `message::sequel` by rendering the internal `store()`. \
				A match for the following sequel will initiate the `respan` (returning `1`), \
				while a match for the current sequel will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion on `sequel`.) \

				XTAL_FNX efflux(message::sequel_q auto sequel_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return efflux(respan_u(store()), sequel_o, XTAL_REF_(oo)...);
				}
				///\
				Forwards `sequel`-prefixed messages to all voices, \
				then frees any that are `done`. \

				///\note\
				When accompanied by `message::respan`, the supplied visor will be used instead. \
				All `arguments` are rendered in-place unless a `visor`-compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				///\todo\
				Assess and improve performance w.r.t. buffer sharing and parallelization. \

				XTAL_FNX efflux(respan_u respan_o, message::sequel_q auto sequel_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					if (S_::effuse(sequel_o, oo...) == 1) return 1;
				//	else...
					using namespace _v3;

					serve(respan_o);
					
				//	Render each voice, and release any that have finished:
					for (auto* v_ = q_.end(); q_.begin() <= --v_;)
					{	(void) v_->efflux(sequel_o, oo...);
						if (v_->influx(message::mute_f(-1)) == 0)
						{	q_.pop(v_);
						}
					}
				//	Initialize target with first voice, then accumulate remaining:
					if (q_.size())
					{	ranges::copy(q_.front(), respan_o);
					}
					for (auto* v_ = q_.begin(1); v_ < q_.end(); ++v_)
					{	ranges::for_each(*v_|views::enumerate,
							[&, this](XTAL_DEF oi) XTAL_0FN_(respan_o[XTAL_REF_(oi[1])] += XTAL_REF_(oi[0]))
						);
					}
					return 0;
				}
				///\
				Forwards the event to the associated voice. \
				If the incoming event is active `(0)`, the top-most associated voice is cut `(-1)`, \
				before a new voice is allocated from the sentinel.

				XTAL_FNX influx(context::voice_s<message::mute_t<>> event_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto *v_ = q_.scan(event_o);

					auto m  = event_o.parent();
					auto i  = event_o.head();
					auto i_ =     v_->head();

				//	Detect incoming note-on:
					if (m == 0)
					//	Cut if it already exists:
					{	if (i == i_)
						{	(void) v_->influx(message::mute_f(-1), oo...);
						}
					//	Allocate by duplicating sentinel and assigning the correct index:
						q_.poke(v_, q_.end());
						v_->head(i_ = i);
					}
				//	Forward to detected/allocated voice:
					assert(i_ == i);
					return v_->influx(m, XTAL_REF_(oo)...);
				}

				
				XTAL_FNX efflux(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(S_::efflux(oo...)) (self().efflux_request(XTAL_REF_(oo)...));
				}
				XTAL_FNX influx(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(self().influx_request(oo...)) (S_::influx(XTAL_REF_(oo)...));
				}

				///\
				Forwards the message to all voices including the sentinel. \

				///\todo\
				Allow parameter crossfades (if wrapped by e.g. `control::any#fade`) \
				by duplicating the target voice. \

				XTAL_FNX efflux_request(XTAL_DEF ...oo)
				XTAL_0EX
				{
					XTAL_FLX flux = -1;
					for (auto* v_ = q_.begin(); v_ < q_.end(-1); ++v_)
					{	flux &= v_->efflux(oo...);
					}
					return flux;
				}
				XTAL_FNX influx_request(XTAL_DEF ...oo)
				XTAL_0EX
				{
					XTAL_FLX flux = -1;
					for (auto* v_ = q_.begin(); v_ < q_.end(-1); ++v_)
					{	flux &= v_->influx(oo...);
					}
					return flux;
				}

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
