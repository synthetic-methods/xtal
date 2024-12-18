#pragma once
#include "./any.hh"
#include "./monomer.hh"
#include "../flux/key.hh"
#include "../provision/all.hh"



XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Polyphonic voice allocator. Functionally similar to `monomer`, \
but expands/contracts the voice spool according to `occur::stage` requests/responses. \

///\note\
The attached `store` and `spool` determine the sample store and voice spool respectively. \

///\todo\
For `dimer`, clone-then-unstage the current voice. \
Either define `lead()` as the `front()` of the ensemble, \
or conditionally incorporate `lead()` into rendering and `key`ed event propagation. \

template <typename ..._s> struct   polymer;
template <typename ..._s> using    polymer_t = confined_t<polymer< _s...>>;
template <typename ..._s> concept  polymer_q = bond::tag_p<polymer, _s...>;
template <typename ..._s>
XTAL_DEF_(short)
XTAL_LET polymer_f(auto &&u)
noexcept -> auto
{
	return polymer_t<XTAL_ALL_(u), _s...>(XTAL_REF_(u));
}


////////////////////////////////////////////////////////////////////////////////

template <bond::compose_q A, typename ...As>
struct polymer<A, As...>
:	bond::compose<A, polymer<As...>>
{
};
template <class U, typename ...As>
struct polymer<U, As...>
{
	using superkind = monomer<U, As...>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using S_subtext = typename S_::template subtext<>;

	public:
		using S_::S_;

		template <class ...Xs> requires provision::spooled_q<S_>
		struct bracket
		{
			//\
			using V_voice = monomer_t<U, provision::context<S_subtext>>::template bind_t<Xs...>;
			using V_voice = monomer_t<U, S_subtext>::template bind_t<Xs...>;
			using V_event = occur::stage_t<>;
			
			using U_voice = flux::key_s<V_voice>;
			using U_event = flux::key_s<V_event>;
			using U_ensemble = typename S_::template spool_t<U_voice>;

			using superkind = bond::compose<bond::tag<polymer>// `As...` included by `monomer`...
			,	defer<V_voice>
			,	typename S_::template bracket<Xs...>
			>;
			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(any_q<R>);
				using R_ = bond::compose_s<R, superkind>;
				
				//\
				U_ensemble u_ensemble = U_ensemble(-1);
				U_ensemble u_ensemble{};

			public:// CONSTRUCT
				using R_::R_;

			public:// ACCESS
				using R_::self;
				using R_::head;

				XTAL_TO2_(XTAL_DEF ensemble(size_t i), u_ensemble[i])
				XTAL_TO2_(XTAL_DEF ensemble(        ), u_ensemble   )
				//\
				XTAL_TO2_(XTAL_DEF lead(), u_ensemble.front())
				XTAL_TO2_(XTAL_DEF lead(), R_::template head<V_voice>())

			public:// *FLUX
				using R_::influx;
				using R_::efflux;

				///\
				Forwards to the associated instance. \
				Messages associated with `occur::stage` designate events, \
				and govern the allocation/deallocation of keyed instances. \
				
				XTAL_DEF_(short)
				XTAL_LET influx(flux::key_q auto io, auto &&...oo)
				noexcept -> signed
				{
					return influx(flux::key_s<>(io), io.tail(), XTAL_REF_(oo)...);
				}

				XTAL_DEF_(short)
				XTAL_LET efflux(flux::key_q auto io, auto &&...oo)
				noexcept -> signed
				{
					return efflux(flux::key_s<>(io), io.tail(), XTAL_REF_(oo)...);
				}

				XTAL_DEF_(long)
				XTAL_LET influx(flux::key_s<> i, auto &&...oo)
				noexcept -> signed
				{
					auto   u_ = u_ensemble.scan(i.head());
					assert(u_ < u_ensemble.end() and i.head() == u_->head());
					return u_->influx(XTAL_REF_(oo)...);
				}
				XTAL_DEF_(long)
				XTAL_LET efflux(flux::key_s<> i, auto &&...oo)
				noexcept -> signed
				{
					auto   u_ = u_ensemble.scan(i.head());
					assert(u_ < u_ensemble.end() and i.head() == u_->head());
					return u_->efflux(XTAL_REF_(oo)...);
				}
				///\
				Forwards to all instances including the sentinel (except when rendering). \

				XTAL_DEF_(long)
				XTAL_LET influx_push(auto &&...oo)
				noexcept -> signed
				{
					using _xtd::ranges::accumulate;

					bool constexpr rend = occur::influx_render_q<decltype(oo)...>;
					return accumulate(u_ensemble, rend? -1: lead().influx(oo...)
					,	[...oo=XTAL_REF_(oo)] (signed x, auto &&vox) XTAL_0FN_(x & XTAL_REF_(vox).influx(oo...))
					);
				}
				XTAL_DEF_(long)
				XTAL_LET efflux_pull(auto &&...oo)
				noexcept -> signed
				{
					using _xtd::ranges::accumulate;

					bool constexpr rend = occur::efflux_render_q<decltype(oo)...>;
					return accumulate(u_ensemble, rend? -1: lead().efflux(oo...)
					,	[...oo=XTAL_REF_(oo)] (signed x, auto &&vox) XTAL_0FN_(x & XTAL_REF_(vox).efflux(oo...))
					);
				}

				///\note\
				If an incoming event is active `(0)`, \
				the top-most associated instance is cut `(-1)` \
				before a new instance is allocated from the prototype `head`. \

				XTAL_DEF_(long)
				XTAL_LET influx(flux::key_s<> i, V_event o, auto &&...oo)
				noexcept -> signed
				{
					auto h  = i.head();
					auto u_ = u_ensemble.scan(h);

				// If an onset-event is received...
					if (0 == o) {
					
					// If a voice already exists for this `key_s`...
						if (u_ < u_ensemble.end() and h == u_->head()) {

						//	Recycle/terminate the current voice:
							auto u = *u_;
							switch (u_->influx(occur::stage_f(-1), oo...)) {
							case  0: break;// Successful termination.
							case  1: break;// Already terminated?
							case -1:       // No response!
								_std::abort();
							}
							u_ = u_ensemble.poke(u_, h, XTAL_MOV_(u));
						}
						else {
						//	Allocate a new voice using the `lead()`:
							u_ = u_ensemble.poke(u_, h, lead());
						}
					}
					assert(u_->head() == h);
					return u_->influx(o, XTAL_REF_(oo)...);
				}

				///\
				Renders the `store` slice designated by `review_o` and `render_o`, \
				after freeing any voices that have reached the final `occur::stage_f(-1)`. \
				
				///\note\
				The `ensemble` is only mixed into `this` if `provision::stored_q`, \
				otherwise the multichannel data is just rendered locally on each voice. \
				
				template <occur::review_q Rev, occur::render_q Ren>
				XTAL_DEF_(long)
				XTAL_LET efflux_subview(Rev &&review_o, Ren &&render_o)
				noexcept -> signed
				{
					u_ensemble.free([] (auto &&e) XTAL_0FN_(XTAL_REF_(e).efflux(occur::stage_f(-1))));
					
					for (auto &vox:u_ensemble) {
						if (1 == vox.efflux(XTAL_REF_(render_o))) {
							return 1;
						}
					}
					///\todo\
					Either configure `vox` (e.g. with `stored`), \
					or reapply the base `monomer`. \

					if constexpr (provision::stored_q<S_>) {
						/**/
						size_type i{count_f(u_ensemble)};
						
						auto vox_f = [&]<class N> (N n) XTAL_0FN {
							i -= n;
							[&]<auto ...I> (bond::seek_t<I...>)
								XTAL_0FN {_detail::mix_to(review_o, u_ensemble[i + I]()...);}
							(bond::seek_s<n>{});
						};
						while (i) {switch (i) {
							case 1:          {vox_f(constant_t<1>{}); break;}
							case 2:          {vox_f(constant_t<2>{}); break;}
							case 3:          {vox_f(constant_t<3>{}); break;}
							case 4: default: {vox_f(constant_t<4>{}); break;}
						}}
						/*/
						for (auto &vox:u_ensemble) {
							_detail::mix_to(review_o, vox());
						}
						/***/
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
