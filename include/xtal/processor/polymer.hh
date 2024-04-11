#pragma once
#include "./any.hh"
#include "./monomer.hh"
#include "../cell/key.hh"




XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename ..._s> struct  polymer;
template <typename ..._s> using   polymer_t = confined_t<polymer< _s...>>;
template <typename ..._s> concept polymer_q = bond::tag_p<polymer, _s...>;
template <typename ..._s>
XTAL_FN2  polymer_f(auto &&u)
XTAL_0EZ_(polymer_t<XTAL_TYP_(u), _s...>(XTAL_REF_(u)))


////////////////////////////////////////////////////////////////////////////////
///\
Polyphonic voice allocator. Functionally similar to `monomer`, \
but expands/contracts the voice buffer according to `occur::stage` requests/responses. \

///\note\
The attached `buffer` and `spool` determine the sample buffer and voice spool respectively. \

template <class U, typename ...As>
struct polymer<U, As...>
{
	using subkind = monomer<U, As...>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;
		using Y_ = monomer_t<based_t<U>>;
		
		template <class ...Xs>
		using S__binding = typename S_::template binding<Xs...>;

		template <class ...Xs>
		using R__binding = bond::compose<void// `As...` included by `monomer`...
		,	S__binding<Xs...>
		,	bond::tag<polymer>
		>;

	public:
		using S_::S_;
		using S_::self;

		template <class ...Xs> requires resource::respool_q<S_> and resource::restore_q<S_>
		struct binding : S__binding<Xs...>
		{
			using Y_return = typename S__binding<Xs...>::Y_return;

			using V_event = occur::stage_t<>;
			using U_event = cell::key_s<V_event>;
			
			using V_voice = typename Y_::template binding_t<Xs...>;
			using U_voice = cell::key_s<V_voice>;
			
			using U_ensemble = typename S_::template spool_t<U_voice>;

			using subkind = bond::compose<bond::tag<polymer>, defer<V_voice>, R__binding<Xs...>>;

			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
				
				U_ensemble u_ensemble{};

			public:
				using R_::R_;
				using R_::self;
				using R_::head;
				using R_::serve;
				using R_::store;
				
				XTAL_TO2_(XTAL_TN2 ensemble(), u_ensemble)

				using R_::influx;
				
				///\
				Forwards the `cell::key`ed occur to the associated instance. \
				Messages associated with a `occur/stage.ii` designate events, \
				and govern the allocation/deallocation of keyed instances. \
				
				///\note\
				If an incoming event is active `(0)`, \
				the top-most associated instance is cut `(-1)` \
				before a new instance is allocated from the prototype `head`. \

				XTAL_TNX influx(cell::key_q auto io, auto &&...oo)
				XTAL_0EX
				{
					auto const i = io.head();
					auto const o = io.then();
					return influx(cell::key_s<>(i), o, XTAL_REF_(oo)...);
				}
				XTAL_TNX influx(cell::key_s<> i, auto &&...oo)
				XTAL_0EX
				{
					auto h = i.head();
					auto w = u_ensemble.scan(h);
					assert(u_ensemble and h == w->head());
					return w->influx(XTAL_REF_(oo)...);
				}
				XTAL_TNX influx(cell::key_s<> i, V_event o, auto &&...oo)
				XTAL_0EX
				{
					auto h = i.head();
					auto w = u_ensemble.scan(h);
				//	Detect and allocate incoming note-on, terminating if it already exists:
					if (0 == o) {
						if (u_ensemble and h == w->head()) {
							(void) w->influx(occur::stage_f(-1), oo...);
						}
						auto y = head();
						w = u_ensemble.poke(w, h, y);
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
					bool constexpr rend = occur::influx_render_q<decltype(oo)...>;
					return _v3::ranges::accumulate(u_ensemble
					,	rend? -1: head().influx(oo...)
					,	[=] (XTAL_FLX flx, auto &&v) XTAL_0FN_(flx & XTAL_REF_(v).influx(oo...))
					);
				}
				XTAL_TNX efflux_pull(auto &&...oo)
				XTAL_0EX
				{
					bool constexpr rend = occur::efflux_render_q<decltype(oo)...>;
					return _v3::ranges::accumulate(u_ensemble
					,	 rend? -1: head().efflux(oo...)
					,	[=] (XTAL_FLX flx, auto &&v) XTAL_0FN_(flx & XTAL_REF_(v).efflux(oo...))
					);
				}

				///\
				Renders the buffer slice designated by `review_o` and `render_o` \
				after liberating any voices that have reached the final `occur::stage_f(-1)`. \
				
				template <occur::review_q Rv, occur::render_q Rn>
				XTAL_TNX efflux_pull_slice(Rv review_o, Rn render_o, auto &&...oo)
				XTAL_0EX
				{
					u_ensemble.cull([] (auto &&e)
						XTAL_0FN_(1 == XTAL_REF_(e).efflux(occur::stage_f(-1)))
					);
					for (auto &vox:u_ensemble) {
						if (1 == vox.efflux(render_o, XTAL_REF_(oo)...)) {
							return 1;
						}
					}
					for (auto &vox:u_ensemble) {
						for (auto && [i, u]:_v3::views::enumerate(vox()|recount_f(review_o))) {
							review_o[XTAL_REF_(i)] += XTAL_REF_(u);
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