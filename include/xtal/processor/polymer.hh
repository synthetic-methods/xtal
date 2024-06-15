#pragma once
#include "./any.hh"
#include "./monomer.hh"
#include "../flux/key.hh"
#include "../resource/all.hh"



XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> XTAL_TYP polymer;
template <typename ..._s> XTAL_USE polymer_t = confined_t<polymer< _s...>>;
template <typename ..._s> XTAL_REQ polymer_q = bond::any_tag_p<polymer, _s...>;
template <typename ..._s>
XTAL_DEF_(return,inline)
XTAL_LET     polymer_f(auto &&u)
XTAL_0EX_TO_(polymer_t<XTAL_ALL_(u), _s...>(XTAL_REF_(u)))


////////////////////////////////////////////////////////////////////////////////
///\
Polyphonic voice allocator. Functionally similar to `monomer`, \
but expands/contracts the voice spool according to `occur::stage` requests/responses. \

///\note\
The attached `store` and `spool` determine the sample store and voice spool respectively. \

template <typename A, typename ...As> requires anything_q<confined_t<polymer<As...>>>
struct polymer<A, As...>
:	bond::compose<A, polymer<As...>>
{
};
template <class U, typename ...As>
struct polymer<U, As...>
{
	using subkind = monomer<U, As...>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		//\
		using Y_ = confined_t<subkind>;
		using Y_ = monomer_t<U>;
		
	public:
		using S_::S_;

		template <class ...Xs> requires resource::spooled_q<S_>
		struct bracket
		{
			using V_event = occur::stage_t<>;
			using U_event = flux::key_s<V_event>;
			
			using V_voice = typename Y_::template binding_t<Xs...>;
			using U_voice = flux::key_s<V_voice>;
			
			using U_ensemble = typename S_::template spool_t<U_voice>;

			using subkind = bond::compose<bond::tag<polymer>// `As...` included by `monomer`...
			,	defer<V_voice>
			,	typename S_::template bracket<Xs...>
			>;
			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
				
				U_ensemble u_ensemble{};

			public:
				using R_::R_;
				using R_::self;
				using R_::head;
				
				XTAL_TO2_(XTAL_DEF_(return,inline) XTAL_RET ensemble(), u_ensemble)

				using R_::influx;
				
				///\
				Forwards the `flux::key`ed occur to the associated instance. \
				Messages associated with a `occur/stage.ii` designate events, \
				and govern the allocation/deallocation of keyed instances. \
				
				///\note\
				If an incoming event is active `(0)`, \
				the top-most associated instance is cut `(-1)` \
				before a new instance is allocated from the prototype `head`. \

				XTAL_TNX influx(flux::key_q auto io, auto &&...oo)
				XTAL_0EX
				{
					auto const i = io.head();
					auto const o = io.tail();
					return influx(flux::key_s<>(i), o, XTAL_REF_(oo)...);
				}
				XTAL_TNX influx(flux::key_s<> i, auto &&...oo)
				XTAL_0EX
				{
					auto h = i.head();
					auto w = u_ensemble.scan(h);
					assert(u_ensemble and h == w->head());
					return w->influx(XTAL_REF_(oo)...);
				}
				XTAL_TNX influx(flux::key_s<> i, V_event o, auto &&...oo)
				XTAL_0EX
				{
					auto h = i.head();
					auto w = u_ensemble.scan(h);
				//	Detect and allocate incoming note-on, terminating if it already exists:
					if (0 == o) {
						if (u_ensemble and h == w->head()) {
							(void) w->influx(occur::stage_f(-1), oo...);
						}
						w = u_ensemble.poke(w, h, head());
					}
				//	Forward to detected/allocated instance:
					assert(w->head() == h);
					return w->influx(o, XTAL_REF_(oo)...);
				}

				///\
				Forwards to all instances including the sentinel (except when rendering). \

				XTAL_TNX influx_push(auto &&...oo)
				XTAL_0EX
				{
					using _xtd::ranges::accumulate;

					bool constexpr rend = occur::influx_render_q<decltype(oo)...>;
					return accumulate(u_ensemble, rend? -1: head().influx(oo...)
					,	[=] (XTAL_FLX flx, auto &&v) XTAL_0FN_(flx & XTAL_REF_(v).influx(oo...))
					);
				}
				XTAL_TNX efflux_pull(auto &&...oo)
				XTAL_0EX
				{
					using _xtd::ranges::accumulate;

					bool constexpr rend = occur::efflux_render_q<decltype(oo)...>;
					return accumulate(u_ensemble, rend? -1: head().efflux(oo...)
					,	[=] (XTAL_FLX flx, auto &&v) XTAL_0FN_(flx & XTAL_REF_(v).efflux(oo...))
					);
				}

				///\
				Renders the `store` slice designated by `review_o` and `render_o`, \
				after freeing any voices that have reached the final `occur::stage_f(-1)`. \
				
				///\note\
				The `ensemble` is only mixed into `this` if `resource::stored_q`, \
				otherwise the multichannel data is just rendered locally on each voice. \
				
				template <occur::review_q Rev, occur::render_q Ren>
				XTAL_TNX efflux_subview(Rev &&review_o, Ren &&render_o)
				XTAL_0EX
				{
					u_ensemble.cull([] (auto &&e)
						XTAL_0FN_(1 == XTAL_REF_(e).efflux(occur::stage_f(-1)))
					);
					for (auto &vox:u_ensemble) {
						if (1 == vox.efflux(XTAL_REF_(render_o))) {
							return 1;
						}
					}
					if constexpr (resource::stored_q<S_>) {
						for (auto &vox:u_ensemble) {
							auto result_o = vox();
							auto _j = point_f(result_o);
							auto _i = point_f(review_o);
							auto  n = count_f(review_o);
							
							for (size_type m = 0; m < n; ++m) {*_i++ += XTAL_MOV_(*_j++);}
						}
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
