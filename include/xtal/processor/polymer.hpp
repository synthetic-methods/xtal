#pragma once
#include "./anybody.hpp"
#include "../context/voice.hpp"
#include "../control/stasis.hpp"
#include "../processor/monomer.hpp"



XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_NYM polymer;
template <typename ..._s> XTAL_ASK polymer_q =      tag_p<polymer, _s...>;
template <typename ..._s> XTAL_USE polymer_t = confined_t<polymer< _s...>>;
template <typename ...As>
XTAL_CN2 polymer_f(XTAL_DEF u) {return polymer_t<XTAL_TYP_(u), As...>(XTAL_REF_(u));}


////////////////////////////////////////////////////////////////////////////////
///\
Polyphonic voice allocator. Functionally similar to `monomer`, \
but expands/contracts the voice pool according to `control::stasis` requests/responses. \

///\note\
The attached `collect` and `collate` determine the sample buffer and voice spool respectively. \

template <class U, typename ...As>
struct polymer<U, As...>
{
	using subkind = monomer<U, As...>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		using Mu = monomer_t<based_t<U>>;
		
		template <class ...Xs>
		using F_ = typename S_::template bond<Xs...>;

	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs> requires collate_q<S_> and collect_q<S_>
		struct bond: F_<Xs...>
		{
			using rebound = F_<Xs...>;
			
			using return_t = typename rebound::return_t;

			using stave_u = typename Mu::template bond_t<Xs...>;
			using stage_u = control::stasis_t<>;
			using event_u = context::voice_s<stage_u>;
			using voice_u = context::voice_s<stave_u>;
			using spool_u = typename S_::template spool_t<voice_u>;

			using subkind = compose<tag<polymer>
			,	typename control::confined_t<>::rend
			,	defer<stave_u>
			,	As...// NOTE: Necessary for `intermit`...
			,	rebound
			>;
			template <any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;
				
				spool_u spool_m;

			public:
				using R_::R_;
				using R_::self;
				using R_::serve;
				using R_::store;
				
				XTAL_TO2_(XTAL_FN2 spool(), spool_m)
				XTAL_TO2_(XTAL_FN2 spine(), R_::head())

				using R_::influx;
				
				XTAL_FNX influx(context::voice_q auto o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto o_core = o.core();
					auto o_head = o.head();
					auto v_     = spool_m.scan(o_head);
					assert(spool_m and o_head == v_->head());
					return v_->influx(o_core, XTAL_REF_(oo)...);
				}
				///\
				Forwards the event to the associated instance. \
				If the incoming event is active `(0)`, the top-most associated instance is cut `(-1)`, \
				before a new instance is allocated from the sentinel.

				XTAL_FNX influx(event_u o, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto o_core = o.core();
					auto o_head = o.head();
					auto v_     = spool_m.scan(o_head);
				//	Detect and allocate incoming note-on, terminating if it already exists:
					if (o_core == 0) {
						if (spool_m and o_head == v_->head()) {
							(void) v_->influx(control::stasis_f(-1), oo...);
						}
						v_ = spool_m.poke(v_, o_head, spine());
					}
				//	Forward to detected/allocated instance:
					assert(v_->head() == o_head);
					return v_->influx(o_core, XTAL_REF_(oo)...);
				}

				///\
				Forwards to all instances including the sentinel. \

				XTAL_FNX influx_push(XTAL_DEF ...oo)
				XTAL_0EX
				{
					bool constexpr impure = false;
					return _v3::ranges::accumulate(spool_m
					,	impure? -1: spine().influx(oo...)
					,	[=] (XTAL_FLX flx, XTAL_DEF v)
							XTAL_0FN_(flx & XTAL_REF_(v).influx(oo...))
					);
				}
				XTAL_FNX efflux_pull(XTAL_DEF ...oo)
				XTAL_0EX
				{
					bool constexpr impure = (...or control::sequel_q<decltype(oo)>);
					return _v3::ranges::accumulate(spool_m
					,	impure? -1: spine().efflux(oo...)
					,	[=] (XTAL_FLX flx, XTAL_DEF v)
							XTAL_0FN_(flx & XTAL_REF_(v).efflux(oo...))
					);
				}

				///\
				Renders the buffer slice designated by `respan_x` and `sequel_x`. \
				
				template <control::respan_q R_x, control::sequel_q S_x>
				XTAL_FNX efflux_pull_slice(R_x respan_x, S_x sequel_x, XTAL_DEF ...oo)
				XTAL_0EX
				{
					XTAL_FLX flx = -1;
				//	Render each instance, while releasing any that have terminated:
					for (auto _v = spool_m.end(); spool_m.begin() <= --_v;) {
						if (_v->efflux(control::stasis_f(-1)) == 1) {
							spool_m.pop(_v);
						}
						else {
							flx &= _v->efflux(sequel_x, oo...);
						}
					}
					if (1 == flx) return flx;// else...
				//	Initialize buffer with first instance, then progressively chunk/mix the rest:
					using namespace _v3;
					using namespace _detail;
					auto i = spool_m.begin(), iN = spool_m.end();
					tunnel_f(respan_x, i++);
					seek_e<-4>([&, this] (auto M)// 3, 2, 1, 0
					XTAL_0FN {
						size_t constexpr N = (size_t) 1 << M;// 8, 4, 2, 1
						for (; N <= _std::distance(i, iN); i += N) {
							tunnel_f<N>(respan_x, i);
						}
					});
					return flx;
				}
				
			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
