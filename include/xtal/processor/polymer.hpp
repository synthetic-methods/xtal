#pragma once
#include "./any.hpp"
#include "../context/grain.hpp"
#include "../control/resize.hpp"
#include "../control/respan.hpp"
#include "../control/sequel.hpp"
#include "../control/stasis.hpp"

XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ...>
struct polymer;

template <typename ...Ts>
XTAL_ASK polymer_q = tag_q<polymer, Ts...>;

template <int N, typename ...As>
XTAL_USE polymer_t = confined_t<polymer<constant_t<N>, As...>>;

template <int N, typename ...As>
XTAL_CN2 polymer_f(XTAL_DEF... xs) {return polymer_t<N, As...>::bond_f(XTAL_REF_(xs)...);}


////////////////////////////////////////////////////////////////////////////////
///\
Polyphonic `grain` allocator with capacity `N_voice::value`. \
The `processor` supplied to `bond` is used as the underlying `value_type`. \
If constructed with `bond_f`, the supplied value is used as the sentinel, \
meaning any upstream references will be preserved. \

///\note\
The use of `bond` as the lifting mechanism is intended both to mirror `monomer`, \
and to allow `collect<...>, As...` to establish the type of the underlying `store`. \

template <constant_q N_voice, typename ...As>
struct polymer<N_voice, As...>
{
	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;

	using subkind = compose<As...>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
		using S_::S_;
		using S_::self;

		template <any_p X> requires collect_q<S_>
		struct bond
		{
			using result_t = _std::invoke_result_t<X>;
			using return_t = iteratee_t<result_t>;
			XTAL_LET_(return_t) zero = 0;

			using stage_u = control::stasis_t<>;
			using event_u = context::grain_s<stage_u>;
			using voice_u = context::grain_s<X>;
			using spool_u = typename collage_t<voice_u, N_voice{}>::spool_t;
			using store_u = typename S_::template fluid<based_t<return_t>>::type;
			using serve_u = deranged_t<store_u>;
			using respan_u = control::respan_t<serve_u>;

			using subkind = compose<tag<polymer>
			,	concord::confer<serve_u>
			,	concord:: defer<store_u>
		//	,	As...
			,	resize_u::attach
			,	sequel_u::attach
			>;
			template <any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

				spool_u q_;
			//	spool_u q_{voice_u::template sentry<0>()};

				XTAL_CXN subtype(store_u &&store_o, X x, XTAL_DEF ...etc)
				XTAL_0EX
				:	R_((serve_u) store_o, XTAL_MOV_(store_o), XTAL_REF_(etc)...)
				,	q_{voice_u::template sentry<0>(XTAL_MOV_(x))}
				{}
				XTAL_CXN subtype(store_u &&store_o, XTAL_DEF ...etc)
				XTAL_0EX
				:	R_((serve_u) store_o, XTAL_MOV_(store_o), XTAL_REF_(etc)...)
				,	q_{voice_u::template sentry<0>()}
				{}

			public:
			//	using R_::R_;
				using R_::self;

				~subtype() = default;
			//	XTAL_CO0_(subtype);
				XTAL_CO4_(subtype);


				XTAL_CON subtype()
				XTAL_0EX
				:	subtype(store_u())
				{}
				XTAL_CXN subtype(XTAL_DEF ...etc)
				XTAL_0EX
				:	subtype(store_u(), XTAL_REF_(etc)...)
				{}

				XTAL_TO4_(XTAL_FN2 spool(), q_)
				XTAL_TO4_(XTAL_FN2 store(XTAL_DEF... oo), R_::template head<1>(XTAL_REF_(oo)...))
				XTAL_TO4_(XTAL_FN2 serve(XTAL_DEF... oo), R_::template head<0>(XTAL_REF_(oo)...))

				XTAL_FN2 method()
				XTAL_0EX
				{
					return serve();
				}

				///\
				Responds to `control::sequel` by rendering the internal `store()`. \
				A match for the following sequel will initiate the `respan` (returning `1`), \
				while a match for the current sequel will terminate (returning `0`). \
				(Deviant behaviour is enforced by `assert`ion on `sequel`.) \

				XTAL_FNX efflux(control::sequel_q auto sequel_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return efflux(respan_u(store()), sequel_o, XTAL_REF_(oo)...);
				}
				///\
				Forwards `sequel`-prefixed messages to all instances, \
				then frees any that are `done`. \

				///\note\
				When accompanied by `control::respan`, the supplied visor will be used instead. \
				All `arguments` are rendered in-place unless a `visor`-compatible `rvalue` is found, \
				in which case the visor will be reused for the intermediate result. \

				///\todo\
				Assess and improve performance w.r.t. buffer sharing and parallelization. \

				XTAL_FNX efflux(respan_u respan_o, control::sequel_q auto sequel_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					if (R_::effuse(sequel_o) == 1) return 1;
				//	else...
					using namespace _v3;

					(void) serve(respan_o);
					/**/
				//	Render each instance, and release any that have finished:
					for (auto* v_ = q_.end(); q_.begin() <= --v_;) {
						(void) v_->efflux(sequel_o, oo...);
						if (v_->efflux(control::stasis_f(-1)) == 1) {
							q_.pop(v_);
						}
					}
				//	Initialize target with first instance, then accumulate remaining:
					if (q_.size()) {
						auto* v_ = q_.begin();
						ranges::copy(v_->parent(), serve().begin());
						for (auto* v_ = q_.begin(1); v_ < q_.end(); ++v_) {
							ranges::move(_detail::mix_f(v_->parent(), serve()), serve().begin());
						}
					}
					/***/
					return 0;
				}
				///\
				Forwards the event to the associated instance. \
				If the incoming event is active `(0)`, the top-most associated instance is cut `(-1)`, \
				before a new instance is allocated from the sentinel.

				XTAL_FNX influx(event_u event_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto *v_ = q_.scan(event_o);

					auto event_stage = event_o.parent();
					auto event_index = event_o.head();
					auto voice_index =     v_->head();

				//	Detect incoming note-on:
					if (event_stage == 0) {
					//	Cut if it already exists:
						if (event_index == voice_index) {
							(void) v_->influx(control::stasis_f(-1), oo...);
						}
					//	Allocate by duplicating sentinel:
						q_.poke(v_, q_.end())->head(voice_index = event_index);
					}
				//	Forward to detected/allocated instance:
					assert(voice_index == event_index);
					return v_->influx(event_stage, XTAL_REF_(oo)...);
				}
				
				XTAL_FNX efflux(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(R_::efflux(oo...)) (self().efflux_request(XTAL_REF_(oo)...));
				}
				XTAL_FNX influx(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(self().influx_request(oo...)) (R_::influx(XTAL_REF_(oo)...));
				}

				///\
				Forwards the message to all instances including the sentinel. \

				///\todo\
				Allow parameter crossfades (if wrapped by e.g. `control::any#fade`) \
				by duplicating the target instance. \

				XTAL_FNX efflux_request(XTAL_DEF ...oo)
				XTAL_0EX
				{
					XTAL_FLX flx = -1;
					for (auto* v_ = q_.begin(); v_ < q_.end(-1); ++v_) {
						flx &= v_->efflux(oo...);
					}
					return flx;
				}
				XTAL_FNX influx_request(XTAL_DEF ...oo)
				XTAL_0EX
				{
					XTAL_FLX flx = -1;
					for (auto* v_ = q_.begin(); v_ < q_.end(-1); ++v_) {
						flx &= v_->influx(oo...);
					}
					return flx;
				}

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
