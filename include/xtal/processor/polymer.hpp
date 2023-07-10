#pragma once
#include "./any.hpp"
#include "../context/scope.hpp"
#include "../context/grain.hpp"
#include "../control/stasis.hpp"
#include "../processor/monomer.hpp"


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
		
		template <typename ...Xs>
		using F_ = typename S_::template bond<Xs...>;

	public:
		using S_::S_;
		using S_::self;

		template <any_p X> requires collect_q<S_>
		struct bond
		{
			using result_t = _std::invoke_result_t<X>;
			using return_t = based_t<iteratee_t<result_t>>;

			using stage_u = control::stasis_t<>;
			using event_u = context::grain_s<stage_u>;
			using voice_u = context::grain_s<based_t<X>>;
			using spool_u = typename collage_t<voice_u, N_voice{}>::spool_t;
			using store_u = typename S_::template fluid<return_t>::type;
			using serve_u = deranged_t<store_u>;
			using respan_u = control::respan_t<serve_u>;

			using subkind = compose<tag<polymer>
			,	concord::defer<voice_u>
			,	concord::refer<serve_u>
			,	context::scope<store_u>
		//	,	As...
			,	resize_u::attach
			,	sequel_u::attach
			>;
			template <any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;
				using Q_ = typename R_::template super_s<1>;
				
				spool_u spool_m;

			public:
				using R_::R_;
				using R_::self;
				using R_::serve;
				using R_::store;
				XTAL_TO2_(XTAL_FN2   spool(), spool_m)
				XTAL_TO2_(XTAL_FN2  method(), serve())
				XTAL_TO2_(XTAL_FN2 spindle(), R_::template super_t<Q_>())
				
				XTAL_FNX influx(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(self().influx_request(oo...)) (Q_::influx(XTAL_REF_(oo)...));
				}
				XTAL_FNX efflux(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return XTAL_FLX_(Q_::efflux(oo...)) (self().efflux_request(XTAL_REF_(oo)...));
				}
				///\
				Forwards to all instances including the sentinel. \

				XTAL_FNX influx_request(XTAL_DEF ...oo)
				XTAL_0EX
				{
					XTAL_FLX flx = R_::head().influx(oo...);
					for (XTAL_DEF v: spool_m) {
						flx &= XTAL_REF_(v).influx(oo...);
					}
					return flx;
				}
				XTAL_FNX efflux_request(XTAL_DEF ...oo)
				XTAL_0EX
				{
					XTAL_FLX flx = R_::head().efflux(oo...);
					for (XTAL_DEF v: spool_m) {
						flx &= XTAL_REF_(v).efflux(oo...);
					}
					return flx;
				}

			//	using R_::influx;
				///\
				Forwards the event to the associated instance. \
				If the incoming event is active `(0)`, the top-most associated instance is cut `(-1)`, \
				before a new instance is allocated from the sentinel.

				XTAL_FNX influx(event_u event_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto e_stage = event_o.core();
					auto e_index = event_o.head();
					auto v_      = spool_m.scan(e_index);
					auto v_index = v_->head();

				//	Detect incoming note-on:
					if (e_stage == 0) {
					//	Cut if it already exists:
						if (v_index == e_index) {
							(void) v_->influx(control::stasis_f(-1), oo...);
						}
					//	Allocate by duplicating sentinel:
						spool_m.poke(v_, R_::head());
						v_->head(v_index = e_index);
					}
				//	Forward to detected/allocated instance:
					assert(v_index == e_index);
					return v_->influx(e_stage, XTAL_REF_(oo)...);
				}
			//	using R_::infuse;
				///\
				Responds to `control::resize` by resizing the internal `store()`. \

				XTAL_FNX infuse(XTAL_DEF o)
				XTAL_0EX
				{
					if constexpr (is_q<resize_u, decltype(o)>) {
						return R_::infuse(o) or (store().resize(XTAL_REF_(o)), 0);
					}
					else {
						return R_::infuse(XTAL_REF_(o));
					}
				}


				///\
				Render the buffer designated by `sequel_o`. \
				
				///\note\
				If no target `respan_o` is provided, uses the internal `store`. \
				
				XTAL_FNX efflux(control::sequel_q auto sequel_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return efflux(respan_u(store()), sequel_o, XTAL_REF_(oo)...);
				}
				XTAL_FNX efflux(respan_u respan_o, control::sequel_q auto sequel_o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					using namespace _v3::ranges;
					XTAL_FLX flx = spool_m.empty() or R_::effuse(sequel_o);
					(void) serve(respan_o);
					
					auto &t  = serve();
					auto  t_ = serve().begin();
					auto  u_ = spool_m.begin();
					auto _u  = spool_m.  end();
					
					if (flx == 1) return 1;// else...
				//	Render each instance, while releasing any that have terminated:
					for (auto _v = _u; u_ <= --_v;) {
						if (_v->efflux(control::stasis_f(-1)) == 1) {
							spool_m.pop(_v);
						}
						else {
							flx &= _v->efflux(sequel_o, oo...);
						}
					}
					if (flx == 1) return 1;// else...
				//	Initialize `serve` with first instance, then accumulate remaining:
					copy(*_u, t_);
					for (auto _v = _u; u_ < --_v;) {
						move(_detail::mix_f(*_v, t), t_);
					}
					return 0;
				}
				
			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
