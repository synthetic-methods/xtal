#pragma once
#include "./any.hh"

#include "./slot.hh"




XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Ties `Xs...` to unify flux branching, etc. \

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
		
	public:// *FLUX
	//	using S_::influx;
	//	using S_::efflux;

		///\returns the result of `influx`ing `self` then  (if `& 1`) `slots`. \

		XTAL_DEF_(short)
		XTAL_LET influx(auto &&...oo)
		noexcept -> signed
		{
			return [this, oo...] XTAL_XFN_(1,&,self().influx_push(oo...)) (S_::influx(XTAL_REF_(oo)...));
		}

		///\returns the result of `efflux`ing `slots` then (if `& 1`) `self`. \

		XTAL_DEF_(short)
		XTAL_LET efflux(auto &&...oo)
		noexcept -> signed
		{
			return [this, oo...] XTAL_XFN_(1,&,S_::efflux(oo...)) (self().efflux_pull(XTAL_REF_(oo)...));
		}

		///\returns the result of `*flux`ing with the supplied routing. \
		If prefixed by a positive `slot_q`, forwards to the `slot` specified. \
		If prefixed by a negative `slot_q` , forwards to all `slots`. \

		XTAL_DEF_(short)
		XTAL_LET influx(flux::slot_q auto i, auto &&...oo)
		noexcept -> signed
		{
			XTAL_IF0
			XTAL_0IF (0 <= i) {return slot<i>().influx     (XTAL_REF_(oo)...);}
			XTAL_0IF (i <  0) {return self   ().influx_push(XTAL_REF_(oo)...);}
		}
		XTAL_DEF_(short)
		XTAL_LET efflux(flux::slot_q auto i, auto &&...oo)
		noexcept -> signed
		{
			XTAL_IF0
			XTAL_0IF (0 <= i) {return slot<i>().efflux     (XTAL_REF_(oo)...);}
			XTAL_0IF (i <  0) {return self   ().efflux_push(XTAL_REF_(oo)...);}
		}

		///\
		Forwards to all `slots`, bypassing `self`. \

		///\note\
		If `0 <= N_slot` provided, \
		forwards `o, oo...` to the slot specified, then `oo...` to the remainder. \

		XTAL_DEF_(short)
		XTAL_LET influx_push(auto &&...oo)
		noexcept -> signed
		{
			return slots().apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
				XTAL_0FN_(XTAL_REF_(xs).influx(oo...) &...& -1)
			);
		}
		XTAL_DEF_(short)
		XTAL_LET efflux_pull(auto &&...oo)
		noexcept -> signed
		{
			return slots().apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
				XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) &...& -1)
			);
		}
		
		template <int N_slot>
		XTAL_DEF_(long)
		XTAL_LET influx_push(auto &&o, auto &&...oo)
		noexcept -> signed
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
		XTAL_DEF_(long)
		XTAL_LET efflux_pull(auto &&o, auto &&...oo)
		noexcept -> signed
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
