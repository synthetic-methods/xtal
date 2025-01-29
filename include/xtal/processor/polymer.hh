#pragma once
#include "./any.hh"
#include "./monomer.hh"
#include "../flow/key.hh"
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
XTAL_DEF_(return,inline,let)
polymer_f(auto &&u)
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
		using S_voice = typename S_::template voice<>;

	public:
		using S_::S_;

		template <class ...Xs> requires provision::spooled_q<S_>
		struct closure
		{
			//\
			using V_voice = typename monomer_t<U, provision::voiced<S_voice>>::template bind_t<Xs...>;
			using V_voice = typename monomer_t<U, S_voice>::template bind_t<Xs...>;
			using V_event = occur::stage_t<>;
			
			using U_voice = flow::key_s<V_voice>;
			using U_event = flow::key_s<V_event>;
			using U_ensemble = typename S_::template spool_t<U_voice>;

			using superkind = bond::compose<bond::tag<polymer>// `As...` included by `monomer`...
			,	defer<V_voice>
			,	typename S_::template closure<Xs...>
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

				XTAL_FX2_(alias) (XTAL_DEF_(return,inline,get) ensemble(), u_ensemble)
				XTAL_FX2_(alias) (XTAL_DEF_(return,inline,get) ensemble(integral_q auto i), u_ensemble[i])
				XTAL_FX2_(alias) (XTAL_DEF_(return,inline,get) ensemble(occur::stage_q auto &&o)
				,	u_ensemble|_xtd::ranges::views::filter([o=XTAL_REF_(o)] (auto &&e) XTAL_0FN_(return) (0 != e.template flux<-1>(o)))
				)

				//\
				XTAL_FX2_(alias) (XTAL_DEF_(return,inline,get) lead(), ensemble().front())
				XTAL_FX2_(alias) (XTAL_DEF_(return,inline,get) lead(), R_::template head<V_voice>())

			public:// FLOW
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				///\
				Forwards to the associated instance. \
				Messages associated with `occur::stage` designate events, \
				and govern the allocation/deallocation of keyed instances. \
				
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(flow::key_q auto io, auto &&...oo)
				noexcept -> signed
				{
					return flux<N_ion>(flow::key_s<>(io), io.tail(), XTAL_REF_(oo)...);
				}
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(flow::key_s<> i_, auto &&...oo)
				noexcept -> signed
				{
					auto   u_ = ensemble().scan(i_.head());
					assert(u_ < ensemble().end() and i_.head() == u_->head());
					return u_->template flux<N_ion>(XTAL_REF_(oo)...);
				}

				///\
				Forwards to all active instances including the sentinel (except when rendering). \

				template <signed N_ion>
				XTAL_DEF_(return,let)
				flux_arguments(auto &&...oo)
				noexcept -> signed
				{
					using _xtd::ranges::accumulate;

					auto constexpr active = occur::stage_f(0);
					auto const     reduce = [=] (auto x, auto &&e) XTAL_0FN_(return) (x & XTAL_REF_(e).template flux<N_ion>(oo...));
					auto           result = N_ion < 0? -1: lead().template flux<N_ion>(XTAL_REF_(oo)...);

					if constexpr (in_n<1, occur::stage_q<decltype(oo)>...>) {
						return accumulate(ensemble(), result, XTAL_MOV_(reduce));
					}
					else {
						/*/
						return accumulate(ensemble(active), result, XTAL_MOV_(reduce));// Fails `copy_assign`?
						/*/
						for (auto &&e: ensemble()) {
							if (e.template flux<-1>(active)) {
								result = reduce(XTAL_MOV_(result), XTAL_REF_(e));
							}
						}
						return result;
						/***/
					}
				}

				///\note\
				If an incoming event is active `(0)`, \
				the top-most associated instance is cut `(-1)` \
				before a new instance is allocated from the prototype `head`. \

				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(return,let)
				flux(flow::key_s<> i, V_event o, auto &&...oo)
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
							auto x = u_->template flux<N_ion>(occur::stage_f(-1), oo...);
							assert(x != -1);
							u_ = ensemble().poke(u_, h, XTAL_MOV_(u));
						}
						else {
						//	Allocate a new voice using the `lead()`:
							u_ = ensemble().poke(u_, h, lead());
						}
					}
					assert(u_->head() == h);
					return u_->template flux<N_ion>(o, XTAL_REF_(oo)...);
				}

				///\
				Renders the `store` slice designated by `review_o` and `render_o`, \
				after freeing any voices that have reached the final `occur::stage_f(-1)`. \
				
				///\note\
				The `ensemble` is only mixed into `this` if `provision::stored_q`, \
				otherwise the multichannel data is just rendered locally on each voice. \
				
				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(return,let)
				subview_flux(occur::review_q auto &&review_o, occur::render_q auto &&render_o)
				noexcept -> signed
				{
					ensemble().template free<[] (auto &&e)
						XTAL_0FN_(return) (XTAL_REF_(e).template flux<N_ion>(occur::stage_f(-1)))
					>();
					for (auto &e:ensemble()) {
						if (1 == e.template flux<N_ion>(XTAL_REF_(render_o))) {
							return 1;
						}
					}
					if constexpr (provision::stored_q<S_>) {
						size_type i{count_f(ensemble())};

						auto y0 = point_f(review_o);
						auto yN = count_f(review_o);

						auto const mix_f = [&] (constant_q auto N) XTAL_0FN {
							[&]<auto ...I> (bond::seek_t<I...>) XTAL_0FN {
								i -= N; _detail::mix_to(review_o, ensemble(i + I)()...);// TODO: Normalize interface for `mix_to`...
							}	(bond::seek_s<N>{});
						};

						if (i) {
							i -= 1; _detail::move_to(y0, point_f(ensemble(i)()), yN);
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
