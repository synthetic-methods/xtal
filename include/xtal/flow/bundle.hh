#pragma once
#include "./any.hh"

#include "./slot.hh"




XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Ties `Xs...` to unify flow branching, etc. \

///\note\
Deified as a `process`'s `bracket`, binding the provided arguments. \

template <class ...Xs> struct   bundle;
template <class ...Xs> using    bundle_t = confined_t<bundle<Xs...>>;
template <class ..._s> concept  bundle_q = bond::tag_p<bundle, _s...>;


//////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct bundle
{
	using superkind = bond::compose<bond::tag<bundle>
	,	cell::defer<cell::packed_t<Xs...>>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using H_ = typename S_::head_type;

	public:// CONSTRUCT
		using S_::S_;

		///\
		Initialize `slots` using the arguments supplied. \

		XTAL_NEW_(explicit) subtype(Xs &&...xs)
		noexcept
		:	S_(H_{XTAL_REF_(xs)...})
		{}

	public:// ACCESS
		using S_::self;
		using S_::head;

		//\note\
		Contingent override of `node` allows unextended `bundle`s to be destructured. \
		Use `slots` for unmitigated access. \

		using node_type = typename S_::head_type;

		XTAL_TO4_(XTAL_DEF_(let)  node(), head())
		XTAL_TO4_(XTAL_DEF_(let) slots(), head())
		
		XTAL_DO2_(template <size_type ...Is>
		XTAL_DEF_(short)
		XTAL_LET slot(),
		noexcept -> decltype(auto)
		{
			return bond::pack_item_f<Is...>(head());
		})
		
	public:// FLOW

		///\returns the result of influxing `self` then  (if `& 1`) `slots`. \
		///\returns the result of effluxing `slots` then (if `& 1`) `self`. \

		template <signed N_ion>
		XTAL_DEF_(short)
		XTAL_LET flux(auto &&...oo)
		noexcept -> signed
		{
			XTAL_IF0
			XTAL_0IF (N_ion == +1) {
				return [this, oo...]
					XTAL_XFN_(1, &, self().template flux_slots<N_ion>(oo...))
						(S_::template flux<N_ion>(XTAL_REF_(oo)...));
			}
			XTAL_0IF (N_ion == -1) {
				return [this, oo...]
					XTAL_XFN_(1, &, S_::template flux<N_ion>(oo...))
						(self().template flux_slots<N_ion>(XTAL_REF_(oo)...));
			}
		}

		///\returns the result of `*flow`ing with the supplied routing. \
		If prefixed by a positive `slot_q`, forwards to the `slot` specified. \
		If prefixed by a negative `slot_q` , forwards to all `slots`. \

		template <signed N_ion>
		XTAL_DEF_(short)
		XTAL_LET flux(flow::slot_q auto i, auto &&...oo)
		noexcept -> signed
		{
			XTAL_IF0
			XTAL_0IF (0 <= i) {return slot<i>().template flux      <N_ion>(XTAL_REF_(oo)...);}
			XTAL_0IF (i <  0) {return self   ().template flux_slots<N_ion>(XTAL_REF_(oo)...);}
		}

		///\
		Forwards to all `slots`, bypassing `self`. \

		///\note\
		If `0 <= N_dex` provided, \
		forwards `o, oo...` to the slot specified, then `oo...` to the remainder. \

		template <signed N_ion>
		XTAL_DEF_(short)
		XTAL_LET flux_slots(auto &&...oo)
		noexcept -> signed
		{
			return slots().apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
				XTAL_0FN_(XTAL_REF_(xs).template flux<N_ion>(oo...) &...& -1)
			);
		}
		template <signed N_ion, int N_dex>
		XTAL_DEF_(short)
		XTAL_LET flux_slotted(auto &&o, auto &&...oo)
		noexcept -> signed
		{
			XTAL_IF0
			XTAL_0IF (N_dex <  0) {
				return flux_slots<N_ion>(XTAL_REF_(oo)...);
			}
			XTAL_0IF (0 <= N_dex) {
				return [this, o=XTAL_REF_(o), ...oo=XTAL_REF_(oo)]
				<auto ...I>(bond::seek_t<I...>)
					XTAL_0FN_(
						slot<N_dex>().template flux<N_ion>(o, oo...) &...& slot<(N_dex <= I) + I>().template flux<N_ion>(oo...)
					)
				(bond::seek_s<sizeof...(Xs) - 1> {});
			}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
