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

template <incomplete_q A, typename ...As>
struct polymer<A, As...>
:	polymer<As...>
{
};
template <bond::compose_q A, typename ...As>
struct polymer<A, As...>
:	bond::compose<A, polymer<As...>>
{
};
template <class U, typename ...As>
struct polymer<U, As...>
{
	using U_resize = occur::resize_t<>;
	using U_cursor = occur::cursor_t<>;

	using superkind = monomer<U, As...>;
	//\
	Base `monomer` used to derive the return-type, \
	and to drive the `chunk`-renderer `flux_chunk`. \

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
		using T_voice = monomer_t<U, typename S_::template voice<>>;

	public:
		using S_::S_;

		template <class ...Xs> requires provision::spooled_q<S_>
		struct binding
		{
			using V_voice = typename T_voice::template bind_t<Xs...>;
			using U_stage = occur::stage_t<>;
			
			using U_voice = flow::key_s<V_voice>;
			using U_event = flow::key_s<U_stage>;
			using U_key   = flow::key_s<>;
			using V_key   = typename U_key::head_type;
			using U_ensemble = typename S_::template spool_t<U_voice>;

			using superkind = bond::compose<bond::tag<polymer>// `As...` included by `monomer`...
			,	typename S_::template binding<Xs...>
			>;
			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(any_q<R>);
				using R_ = bond::compose_s<R, superkind>;
				
				U_ensemble u_ensemble{_std::numeric_limits<V_key>::min(), bond::seek_t<>{}};

			public:// CONSTRUCT
			//	using R_::R_;
				XTAL_NEW_(delete) (subtype, noexcept = default)
				XTAL_NEW_(create) (subtype, noexcept = default)
				XTAL_NEW_(move)   (subtype, noexcept = default)
				XTAL_NEW_(copy)   (subtype, noexcept = default)
				XTAL_NEW_(cast)   (subtype, noexcept)

				XTAL_NEW_(explicit)
				subtype(same_q<Xs> auto &&...xs)
				noexcept
				:	u_ensemble{
						U_voice(_std::numeric_limits<V_key>::min()
						,	XTAL_REF_(xs)...
						)
					,	bond::seek_t<>{}
					}
				{}

			public:// ACCESS
				using R_::self;
				using R_::head;

				XTAL_FX2_(to) (XTAL_DEF_(return,inline,get)     lead(), u_ensemble.peek(-1))
				XTAL_FX2_(to) (XTAL_DEF_(return,inline,get) ensemble(), u_ensemble)
				XTAL_FX2_(to) (XTAL_DEF_(return,inline,get) ensemble(integral_q auto i), u_ensemble[i])
				XTAL_FX2_(to) (XTAL_DEF_(return,inline,get) ensemble(occur::stage_q auto &&o)
				,	u_ensemble
				|	_xtd::ranges::views::filter([o=XTAL_REF_(o)] (auto &&e)
						XTAL_0FN_(to) (0 != XTAL_REF_(e).template flux<-1>(o)))
				)

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
					return flux<N_ion>(U_key(io), io.tail(), XTAL_REF_(oo)...);
				}
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(U_key i_, auto &&...oo)
				noexcept -> signed
				{
					auto u_ = ensemble().scan(i_.head());
					//\
					if (1 <= count_f(ensemble())) {
					if (1 <= count_f(ensemble()) and 1 != u_->efflux(occur::stage_f(-1))) {
						assert(u_ < ensemble().end() and i_.head() == u_->head());
						return u_->template flux<N_ion>(XTAL_REF_(oo)...);
					}
					else {
						return -1;
					}
				}
				///\note\
				If an incoming event is active `(0)`, \
				the top-most associated instance is cut `(-1)` \
				before a new instance is allocated from the prototype `head`. \

				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(return,let)
				flux(U_key i_, U_stage _o, auto &&...oo)
				noexcept -> signed
				{
					auto h  = i_.head();
					auto u_ = ensemble().scan(h);

				// If an onset-event is received...
					if (0 == _o.head()) {
					
					// If a voice already exists for this `key_s`...
						if (u_ < ensemble().end() and h == u_->head()) {

						//	Recycle/terminate the current voice:
							auto u = *u_;
							auto x =  u_->template flux<N_ion>(occur::stage_f(-1), oo...);
							assert(x != -1);
							u_ = ensemble().poke(u_, h, XTAL_MOV_(u));
						}
						else {
						//	Allocate a new voice using the `lead()`:
							u_ = ensemble().poke(u_, h, lead());

						//	Update to the current `cursor`:
							(void) u_->influx(lead().template head<U_cursor>());
						}
					}
					assert(u_->head() == h);
					return u_->template flux<N_ion>(XTAL_MOV_(_o), XTAL_REF_(oo)...);
				}

				///\
				Renders the indexed `store` slice designated by `rev` and `cur`, \
				after freeing any voices that have reached the final `occur::stage_f(-1)`. \
				
				///\note\
				The `ensemble` is only mixed into `this` if `provision::stored_q`, \
				otherwise the multichannel data is just rendered locally on each voice. \
				
				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(return,let)
				flux(occur::render_q auto &&, occur::review_q auto &&rev, occur::cursor_q auto &&cur)
				noexcept -> signed
				{
					ensemble().free([] XTAL_1FN_(method) (efflux(occur::stage_f(-1)) == 1));

					auto y0 = point_f(rev);
					auto sN = count_f(rev);
					_detail::fill_with(y0, sN, zero);

					signed x = -1;

					(void) lead().influx(cur);

					for (auto &&e: ensemble()) {
						x &= XTAL_REF_(e).efflux(cur);
					}
					if (0 == x and provision::stored_q<S_>) {
						for (auto &&e: ensemble()) {
							auto xs = e()|account_f(sN);
							auto x0 =       point_f(xs);
							_detail::move_to<_std::plus<void>{}>(y0, x0, sN);
						}
					}
					return x;
				}
				
				///\
				Forwards to all active instances including the sentinel (except when rendering). \

				///\todo\
				Filter parameter changes from `stage == -1` events? \

				/*/
				template <signed N_ion, unnatural_constant_q I>
				XTAL_DEF_(return,inline,let)
				flux(I &&, auto &&...oo)
				/*/
				template <signed N_ion>
				XTAL_DEF_(return,let)
				flux_rest(auto &&...oo)
				/***/
				noexcept -> signed
				{
					auto x = N_ion < 0? -1: lead().template flux<N_ion>(oo...);
					return _xtd::ranges::accumulate(ensemble(), x
					,	[=] (auto x, auto &&e) XTAL_0FN_(to) (x & XTAL_REF_(e).template flux<N_ion>(oo...))
					);
					return x;
				}

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
