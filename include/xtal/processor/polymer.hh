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

///\note\
The `scan` method of `spool` must return the most recently activated voice for a given `key_s`. \
The default implementation uses `lower_bound` to this effect. \

template <typename ..._s> struct   polymer;
template <typename ..._s> using    polymer_t =  confined_t<polymer< _s...>>;
template <typename ..._s> concept  polymer_q = bond::tag_p<polymer, _s... >;
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
			using V_voice = typename monomer_t<U, provision::context<S_subtext>>::template bind_t<Xs...>;
			using V_voice = typename monomer_t<U, S_subtext>::template bind_t<Xs...>;
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

				XTAL_TO2_(XTAL_DEF_(let) ensemble(), u_ensemble)
				XTAL_TO2_(XTAL_DEF_(let) ensemble(integral_q auto i), u_ensemble[i])
				XTAL_TO2_(XTAL_DEF_(let) ensemble(occur::stage_q auto const &o)
				,	u_ensemble|_xtd::ranges::views::filter([&] (auto &&e) XTAL_0FN_(XTAL_REF_(e).efflux(o)))
				)
				//\
				XTAL_TO2_(XTAL_DEF_(let) lead(), ensemble().front())
				XTAL_TO2_(XTAL_DEF_(let) lead(), R_::template head<V_voice>())

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
					auto   u_ = ensemble().scan(i.head());
					assert(u_ < ensemble().end() and i.head() == u_->head());
					return u_->influx(XTAL_REF_(oo)...);
				}
				XTAL_DEF_(long)
				XTAL_LET efflux(flux::key_s<> i, auto &&...oo)
				noexcept -> signed
				{
					auto   u_ = ensemble().scan(i.head());
					assert(u_ < ensemble().end() and i.head() == u_->head());
					return u_->efflux(XTAL_REF_(oo)...);
				}
				///\
				Forwards to all active instances including the sentinel (except when rendering). \

				XTAL_DEF_(let) influx_pushed(auto &&...oo) noexcept {return occur::influx_render_q<decltype(oo)...>? -1: lead().influx(XTAL_REF_(oo)...);}
				XTAL_DEF_(let) efflux_pushed(auto &&...oo) noexcept {return occur::efflux_render_q<decltype(oo)...>? -1: lead().efflux(XTAL_REF_(oo)...);}

				XTAL_DEF_(let) influx_pusher(auto &&...oo) noexcept {return [...oo=XTAL_REF_(oo)] (signed x, auto &&e) XTAL_0FN_(x & XTAL_REF_(e).influx(XTAL_MOV_(oo)...));}
				XTAL_DEF_(let) efflux_pusher(auto &&...oo) noexcept {return [...oo=XTAL_REF_(oo)] (signed x, auto &&e) XTAL_0FN_(x & XTAL_REF_(e).efflux(XTAL_MOV_(oo)...));}

				XTAL_DEF_(short)
				XTAL_LET influx_push(auto &&...oo)
				noexcept -> signed
				{
					using _xtd::ranges::accumulate;
					auto const x = influx_pushed(          oo ...);
					auto const f = influx_pusher(XTAL_REF_(oo)...);
					if constexpr ((... or occur::stage_q<decltype(oo)>)) {
						return accumulate(ensemble(                 ), x, XTAL_MOV_(f));
					}
					else {
						return accumulate(ensemble(occur::stage_f(0)), x, XTAL_MOV_(f));
					}
				}
				XTAL_DEF_(short)
				XTAL_LET efflux_pull(auto &&...oo)
				noexcept -> signed
				{
					using _xtd::ranges::accumulate;
					auto const x = efflux_pushed(          oo ...);
					auto const f = efflux_pusher(XTAL_REF_(oo)...);
					if constexpr ((... or occur::stage_q<decltype(oo)>)) {
						return accumulate(ensemble(                 ), x, XTAL_MOV_(f));
					}
					else {
						return accumulate(ensemble(occur::stage_f(0)), x, XTAL_MOV_(f));
					}
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
					auto u_ = ensemble().scan(h);

				// If an onset-event is received...
					if (0 == o) {
					
					// If a voice already exists for this `key_s`...
						if (u_ < ensemble().end() and h == u_->head()) {

						//	Recycle/terminate the current voice:
							auto u = *u_;
							auto x = u_->influx(occur::stage_f(-1), oo...);
							assert(x != -1);
							u_ = ensemble().poke(u_, h, XTAL_MOV_(u));
						}
						else {
						//	Allocate a new voice using the `lead()`:
							u_ = ensemble().poke(u_, h, lead());
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
					ensemble().free([] (auto &&e) XTAL_0FN_(XTAL_REF_(e).efflux(occur::stage_f(-1))));
					
					for (auto &e:ensemble()) {
						if (1 == e.efflux(XTAL_REF_(render_o))) {
							return 1;
						}
					}
					if constexpr (provision::stored_q<S_>) {
						size_type i{count_f(ensemble())};

						auto const mix_f = [&] (constant_q auto N) XTAL_0FN {
							[&]<auto ...I> (bond::seek_t<I...>) XTAL_0FN {
								i -= N; _detail::mix_to(review_o, ensemble(i + I)()...);
							}	(bond::seek_s<N>{});
						};

						if (i) {
							i -= 1; _xtd::ranges::move(ensemble(i)()|account_f(review_o), point_f(review_o));
						}
						while (i) {switch (i) {
							case 1:          {mix_f(constant_t<1>{}); break;}
							case 2:          {mix_f(constant_t<2>{}); break;}
							case 3:          {mix_f(constant_t<3>{}); break;}
							case 4: default: {mix_f(constant_t<4>{}); break;}
						}}
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
