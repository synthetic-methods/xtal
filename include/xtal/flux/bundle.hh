#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Ties `Xs...` to unify flux branching, etc. \

///\note\
Deified as a `process`'s `bracket`, binding the provided arguments. \

template <class ...Xs> XTAL_TYP bundle;
template <class ...Xs> XTAL_USE bundle_t = confined_t<bundle<Xs...>>;
template <class ..._s> XTAL_ASK bundle_q = bond::any_tag_p<bundle, _s...>;


//////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct bundle
{
	using superkind = bond::compose<bond::tag<bundle>
	,	cell::defer<cell::packed_t<Xs...>>
	>;
	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		using H_ = typename S_::head_type;

	public:// CONSTRUCT
		using S_::S_;

		///\
		Initialize `slots` using the arguments supplied. \

		XTAL_NEW_(explicit) subtype(Xs &&...xs)
		noexcept
		:	subtype(H_{XTAL_REF_(xs)...})
		{}

	public:// ACCESS
		using S_::self;
		using S_::head;

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_RET slots(), head())
		
		XTAL_DO2_(template <size_type ...Ns>
		XTAL_DEF_(return,inline)
		XTAL_LET slot(), -> decltype(auto)
		{
			return bond::pack_item_f<Ns...>(slots());
		})

	public:// *FLUX
	//	using S_::influx;
	//	using S_::efflux;

		///\returns the result of `influx`ing `self` then  (if `& 1`) `slots`. \

		XTAL_DEF_(return,inline)
		XTAL_LET influx(auto &&...oo)
		noexcept -> sign_type
		{
			return [this, oo...] XTAL_XFN_(self().influx_push(oo...)) (S_::influx(XTAL_REF_(oo)...));
		}

		///\returns the result of `efflux`ing `slots` then (if `& 1`) `self`. \

		XTAL_DEF_(return,inline)
		XTAL_LET efflux(auto &&...oo)
		noexcept -> sign_type
		{
			return [this, oo...] XTAL_XFN_(S_::efflux(oo...)) (self().efflux_pull(XTAL_REF_(oo)...));
		}

		///\note\
		If prefixed by `unnatural_q` a.k.a. `flux::slot_n<-1>`, forwards to all `slots`. \

		XTAL_DEF_(return,inline) XTAL_LET influx(unnatural_q auto, auto &&...oo) noexcept -> sign_type {return self().influx_push(XTAL_REF_(oo)...);}
		XTAL_DEF_(return,inline) XTAL_LET efflux(unnatural_q auto, auto &&...oo) noexcept -> sign_type {return self().efflux_push(XTAL_REF_(oo)...);}


		///\note\
		If prefixed by `natural_q`, forwards to the `slot` specified. \

		XTAL_DEF_(return,inline) XTAL_LET influx(natural_q auto I, auto &&...oo) noexcept -> sign_type {return slot<I>().influx(XTAL_REF_(oo)...);}
		XTAL_DEF_(return,inline) XTAL_LET efflux(natural_q auto I, auto &&...oo) noexcept -> sign_type {return slot<I>().efflux(XTAL_REF_(oo)...);}

		///\
		Forwards to all `slots`, bypassing `self`. \

		///\note\
		If `0 <= N_slot` provided, \
		forwards `o, oo...` to the slot specified, then `oo...` to the remainder. \

		XTAL_DEF_(return,inline)
		XTAL_LET influx_push(auto &&...oo)
		noexcept -> sign_type
		{
			return slots().apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
				XTAL_0FN_(XTAL_REF_(xs).influx(oo...) &...& -1)
			);
		}
		XTAL_DEF_(return,inline)
		XTAL_LET efflux_pull(auto &&...oo)
		noexcept -> sign_type
		{
			return slots().apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
				XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) &...& -1)
			);
		}
		
		template <int N_slot>
		XTAL_DEF_(return)
		XTAL_LET influx_push(auto &&o, auto &&...oo)
		noexcept -> sign_type
		{
			XTAL_IF0
			XTAL_0IF (N_slot <  0) {
				return influx_push(XTAL_REF_(oo)...);
			}
			XTAL_0IF (0 <= N_slot) {
				return [this, o=XTAL_REF_(o), ...oo=XTAL_REF_(oo)]
				<auto ...I>(bond::seek_t<I...>)
					XTAL_0FN_(
						slot<N_slot>().influx(o, oo...) &...& slot<(N_slot <= I) + I>().influx(oo...)
					)
				(bond::seek_s<sizeof...(Xs) - 1> {});
			}
		}
		template <int N_slot>
		XTAL_DEF_(return)
		XTAL_LET efflux_pull(auto &&o, auto &&...oo)
		noexcept -> sign_type
		{
			XTAL_IF0
			XTAL_0IF (N_slot <  0) {
				return efflux_pull(XTAL_REF_(oo)...);
			}
			XTAL_0IF (0 <= N_slot) {
				return [this, o=XTAL_REF_(o), ...oo=XTAL_REF_(oo)]
				<auto ...I>(bond::seek_t<I...>)
					XTAL_0FN_(
						slot<N_slot>().efflux(o, oo...) &...& slot<(N_slot <= I) + I>().efflux(oo...)
					)
				(bond::seek_s<sizeof...(Xs) - 1> {});
			}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
