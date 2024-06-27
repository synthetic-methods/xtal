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

template <bond::compose_q A, typename ...As>
struct polymer<A, As...>
:	bond::compose<A, polymer<As...>>
{
};
template <class U, typename ...As>
struct polymer<U, As...>
{
	//\
	using subkind = monomer<monomer_t<U>, As...>;
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
		struct bundle
		{
			using V_event = occur::stage_t<>;
			using U_event = flux::key_s<V_event>;
			
			using V_voice = typename Y_::template binds_t<Xs...>;
			using U_voice = flux::key_s<V_voice>;
			
			using U_ensemble = typename S_::template spool_t<U_voice>;

			using subkind = bond::compose<bond::tag<polymer>// `As...` included by `monomer`...
			,	defer<V_voice>
			,	typename S_::template bundle<Xs...>
			>;
			template <any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
				
				U_ensemble u_ensemble{};

			public:// CONSTRUCT
				using R_::R_;

			public:// ACCESS
				using R_::self;
				using R_::head;

				XTAL_TO2_(XTAL_DEF_(return,inline) XTAL_RET ensemble(size_t i), u_ensemble[i])
				XTAL_TO2_(XTAL_DEF_(return,inline) XTAL_RET ensemble(), u_ensemble)
				XTAL_TO2_(XTAL_DEF_(return,inline) XTAL_RET lead(), R_::template head<V_voice>())

			public:// *FLUX
				using R_::influx;
				using R_::efflux;

				///\
				Forwards to the associated instance. \
				Messages associated with `occur::stage` designate events, \
				and govern the allocation/deallocation of keyed instances. \
				
				XTAL_TNX     influx(flux::key_q auto io, auto &&...oo)
				XTAL_0EX_TO_(influx(flux::key_s<>(io), io.tail(), XTAL_REF_(oo)...))

				XTAL_TNX     efflux(flux::key_q auto io, auto &&...oo)
				XTAL_0EX_TO_(efflux(flux::key_s<>(io), io.tail(), XTAL_REF_(oo)...))

				XTAL_TNX influx(flux::key_s<> i, auto &&...oo)
				XTAL_0EX
				{
					auto   u_ = u_ensemble.scan(i.head());
					assert(u_ < u_ensemble.end() and i.head() == u_->head());
					return u_->influx(XTAL_REF_(oo)...);
				}
				XTAL_TNX efflux(flux::key_s<> i, auto &&...oo)
				XTAL_0EX
				{
					auto   u_ = u_ensemble.scan(i.head());
					assert(u_ < u_ensemble.end() and i.head() == u_->head());
					return u_->efflux(XTAL_REF_(oo)...);
				}
				///\
				Forwards to all instances including the sentinel (except when rendering). \

				XTAL_TNX influx_push(auto &&...oo)
				XTAL_0EX
				{
					using _xtd::ranges::accumulate;

					bool constexpr rend = occur::influx_render_q<decltype(oo)...>;
					return accumulate(u_ensemble, rend? -1: lead().influx(oo...)
					,	[...oo=XTAL_REF_(oo)] (XTAL_FLX flx, auto &&vox) XTAL_0FN_(flx & XTAL_REF_(vox).influx(oo...))
					);
				}
				XTAL_TNX efflux_pull(auto &&...oo)
				XTAL_0EX
				{
					using _xtd::ranges::accumulate;

					bool constexpr rend = occur::efflux_render_q<decltype(oo)...>;
					return accumulate(u_ensemble, rend? -1: lead().efflux(oo...)
					,	[...oo=XTAL_REF_(oo)] (XTAL_FLX flx, auto &&vox) XTAL_0FN_(flx & XTAL_REF_(vox).efflux(oo...))
					);
				}

				///\note\
				If an incoming event is active `(0)`, \
				the top-most associated instance is cut `(-1)` \
				before a new instance is allocated from the prototype `head`. \

				XTAL_TNX influx(flux::key_s<> i, V_event o, auto &&...oo)
				XTAL_0EX
				{
					auto h  = i.head();
					auto u_ = u_ensemble.scan(h);
				//	When a voice is initiated...
					if (0 == o) {
					//	...terminate the previous entry, if it exists:
						if (u_ < u_ensemble.end() and h == u_->head()) {
						//	...assuming that it hasn't been terminated already:
							assert(1 != u_->efflux(occur::stage_f(-1)));
							(void) u_->influx(occur::stage_f(-1), oo...);
						}
					//	...then allocate a new instance:
						u_ = u_ensemble.poke(u_, h, lead());
					}
					assert(u_->head() == h);
					return u_->influx(o, XTAL_REF_(oo)...);
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
					///\todo\
					Either configure `vox` (e.g. with `stored`), \
					or reapply the base `monomer`. \

					///\todo\
					Examine the possibility of forwarding an accumulating view. \

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
