#pragma once
#include "./any.hh"
#include "./monomer.hh"
#include "../flow/key.hh"
#include "../flow/assess.hh"
#include "../provision/all.hh"


XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!\addtogroup XTAL_processor_polymer*/
/*!
\ingroup XTAL_processor_polymer
\brief   Polyphonic voice allocator.

Functionally similar to `monomer`,
but expands/contracts the voice spool according to `occur::stage` requests/responses.

The attached `store` and `spool` determine the sample store and voice spool respectively.
The `scan` method of `spool` must return the most recently activated voice for a given `key_s`.
The default implementation uses `lower_bound` to this effect.
*/
template <typename ...As>	struct  polymer;
template <typename ...As>	using   polymer_t      =       confined_t<polymer< As...>>;///<\ingroup XTAL_processor_polymer
template <typename ...Qs>	concept polymer_head_q = bond::tag_as_p<polymer, Qs... >;///<\ingroup XTAL_processor_polymer
template <typename ...Qs>	concept polymer_body_q = bond::tag_in_p<polymer, Qs... >;///<\ingroup XTAL_processor_polymer


////////////////////////////////////////////////////////////////////////////////
/*!
\brief   Creates a `polymer` by lifting the given function/`process`, and attaching `As...`.
*/
template <typename ...As>
XTAL_DEF_(let) polymer_f = []<class U> (U &&u)
XTAL_0FN_(to) (polymer_t<based_t<U>, As...>(XTAL_REF_(u)));


////////////////////////////////////////////////////////////////////////////////
/**/
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
	using superkind = monomer<U, As...>;
/*/
template <typename ...As>
struct polymer
{
private:
	using superkind = monomer<As...>;
/***/
public:
	/*!
	\brief  	Defines a `monomer`-derived type that aggregates the internally managed voices.
	\brief  	Uses `provision::voiced` to configure the collective `ensemble`.
	*/
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
		using U_ = typename S_::head_type;
		//\
		using M_voice = monomer_t<U_, typename S_::template voice<>>;
		using M_voice = monomer_t<U , typename S_::template voice<>>;

	public:
		using S_::S_;

		template <class ...Xs> requires provision::spooled_q<S_>
		struct binding
		{
		private:
			using V_voice = typename M_voice::template bind_t<Xs...>;
			using U_stage = occur::stage_t<>;
			
			using U_voice = flow::key_s<V_voice>;
			using U_event = flow::key_s<U_stage>;
			using U_key   = flow::key_s<>;
			using V_key   = typename U_key::head_type;
			using U_ensemble = typename S_::template spool_t<U_voice>;

			using superkind = bond::compose<bond::tag<polymer>// `As...` included by `monomer`...
			,	typename S_::template binding<Xs...>
			>;
			/*!
			\brief  	Manages the `ensemble` via `occur::stage` events indexed by `flow::key`.
			\details
			Both events and the voices comprising the `ensemble` are wrapped by `flow::key`,
			allowing the two to be compared directly.

			Due to the opaque nature of `flow::key`,
			the `ensemble` can be navigated as a collection of `signed` prefixes.
			*/
		public:
			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(any_q<R>);
				using R_ = bond::compose_s<R, superkind>;
				
				U_ensemble u_ensemble{_std::numeric_limits<V_key>::min(), bond::seek_t<>{}};

			public:// CONSTRUCT
			//	using R_::R_;
				XTAL_NEW_(delete) (subtype, noexcept=default)
				XTAL_NEW_(create) (subtype, noexcept=default)
				XTAL_NEW_(move)   (subtype, noexcept=default)
				XTAL_NEW_(copy)   (subtype, noexcept=default)
				XTAL_NEW_(then)   (subtype, noexcept:subtype)
			//	XTAL_NEW_(else)   (subtype, noexcept:S_)

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

				XTAL_FN2_(to) (XTAL_DEF_(return,inline,get)     lead(), u_ensemble.peek(-1))
				XTAL_FN2_(to) (XTAL_DEF_(return,inline,get) ensemble(), u_ensemble)
				XTAL_FN2_(to) (XTAL_DEF_(return,inline,get) ensemble(integral_q auto i), u_ensemble[i])
				XTAL_FN2_(to) (XTAL_DEF_(return,inline,get) ensemble(occur::stage_q auto &&o)
				,	u_ensemble
				|	_xtd::ranges::views::filter([o=XTAL_REF_(o)] (auto &&e)
						XTAL_0FN_(to) (0 != XTAL_REF_(e).template flux<-1>(o)))
				)

			public:// FLOW
				/*!
				\brief  	Forwards the message upstream.
				*/
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				/*!
				\brief  	Unpacks and handles the message.
				\brief  	Messages associated with `occur::stage` designate events,
				governing the allocation/deallocation of keyed instances.
				*/
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(flow::key_q auto io, auto &&...oo)
				noexcept -> signed
				{
					return flux<N_ion>(U_key(io), io.tail(), XTAL_REF_(oo)...);
				}
				/*!
				\brief  	Forwards the message to the associated voice.
				*/
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(U_key i_, auto &&...oo)
				noexcept -> signed
				{
					auto u_ = ensemble().scan(i_.head());
					//\
					if (1 <= count_f(ensemble()) and 1 != u_->influx(occur::stage_f(-1))) {
					if (1 <= count_f(ensemble()) and 1 != u_->influx(flow::assess_f(occur::stage_f(-1)))) {
						assert(u_ < ensemble().end() and i_.head() == u_->head());
						return u_->template flux<N_ion>(XTAL_REF_(oo)...);
					}
					else {
						return -1;
					}
				}
				/*!
				\brief  	Handles voice-allocation/termination using the provided `occur::stage`
				\details
				If the incoming event is in the initial stage `0`,
				the top-most associated instance is duplicated then terminated `-1`.

				If no voice exists for the given key,
				the new instance is duplicated from `lead`.
				*/
				template <signed N_ion> requires in_v<N_ion, -1>
				XTAL_DEF_(return,let)
				flux(U_key k_, U_stage o, auto &&...oo)
				noexcept -> signed
				{
					auto const k     = k_.head();
					auto       e_    = ensemble().scan(k);
					bool const onset =                           0 == o  .head(), offset = not onset;
					bool const reset = e_ < ensemble().end() and k == e_->head(), preset = not reset;
					if (onset) {
						e_ = ensemble().poke(e_, k, preset? lead(): [&] XTAL_1FN {
							auto   u = *e_; (void) e_->template flux<N_ion>(occur::stage_f(-1), oo...);
							return u;
						}	());
					}
					return offset and preset? -1:
						e_->template flux<N_ion>(XTAL_MOV_(o), XTAL_REF_(oo)...);
				}
				/*!
				\brief  	Renders the given slice of `ren` designated by `rev` and `cur`.
				\brief  	Frees any voices that have reached the final stage `-1`.

				Voices are rendered internally by invoking `flux<-1>` with the cursor only,
				before being mixed into `rev` if `provision::stored_q<self_type>`.

				Variadic expansion can be achieved by prefixing the render-tuple with `key_s`.
				*/
				template <signed N_ion> requires in_v<N_ion, -1>
				XTAL_DEF_(return,let)
				flux(occur::render_q auto &&ren, occur::review_q auto &&rev, occur::cursor_q auto &&cur)
				noexcept -> signed
				{
					ensemble().free([] XTAL_1FN_(dot) (influx(flow::assess_f(occur::stage_f(-1))) == 1));

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

			//\
			protected:// FLOW
			public:// FLOW
				/*!
				\brief  	Forwards the message to all active instances.
				\brief  	The `lead` is included when `N_ion == 1` in order to maintain state continuity.
				*/
				template <signed N_ion>
				XTAL_DEF_(return,let)
				flux_rest(auto &&...oo)
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
