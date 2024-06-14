#pragma once
#include "./any.hh"

#include "../cell/mark.hh"




XTAL_ENV_(push)
namespace xtal::flux
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Thunkifies the underlying `T` by capturing the arguments `Xs...`. \

template <class ...Xs>
struct bracket;


//////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct bracket
{
	using Xs_packed = cell::packed_t<Xs...>;
	
	using subkind = cell::defer<Xs_packed>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;
		using S_::head;

		XTAL_TO4_(XTAL_DEF_(return,inline) XTAL_REF slots(), head())
		
		XTAL_TO2_(template <size_t ...Ns>
		XTAL_DEF_(return,inline)
		XTAL_REF slot(), bond::pack_item_f<Ns...>(slots()))

	public:// FLUXION
	//	using S_::influx;
	//	using S_::efflux;

		///\returns the result of `influx`ing `self` then  (if `& 1`) `slots`. \

		XTAL_TNX influx(auto &&...oo)
		XTAL_0EX_TO_(XTAL_FNX_(self().influx_push(oo...)) (S_::influx(XTAL_REF_(oo)...)))

		///\returns the result of `efflux`ing `slots` then (if `& 1`) `self`. \

		XTAL_TNX efflux(auto &&...oo)
		XTAL_0EX_TO_(XTAL_FNX_(S_::efflux(oo...)) (self().efflux_pull(XTAL_REF_(oo)...)))

		///\note\
		If prefixed by `null_t{}`, forwards the occur to all `slots`. \

		XTAL_TNX influx(null_t, auto &&...oo) XTAL_0EX_TO_(self().influx_push(XTAL_REF_(oo)...))
		XTAL_TNX efflux(null_t, auto &&...oo) XTAL_0EX_TO_(self().efflux_pull(XTAL_REF_(oo)...))

		///\note\
		If prefixed by `nominal_q`, forwards the occur to the `slot` specified. \

		XTAL_TNX influx(nominal_q auto I, auto &&...oo) XTAL_0EX_TO_(slot<I>().influx(XTAL_REF_(oo)...))
		XTAL_TNX efflux(nominal_q auto I, auto &&...oo) XTAL_0EX_TO_(slot<I>().efflux(XTAL_REF_(oo)...))

		///\
		Forwards the occur to all `slots`, bypassing `self`. \

		XTAL_TNX influx_push(auto &&...oo)
		XTAL_0EX
		{
			return slots().apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
				XTAL_0FN_(XTAL_REF_(xs).influx(oo...) &...& -1)
			);
		}
		XTAL_TNX efflux_pull(auto &&...oo)
		XTAL_0EX
		{
			return slots().apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
				XTAL_0FN_(XTAL_REF_(xs).efflux(oo...) &...& -1)
			);
		}
		///\
		Forwards the occur-tail to all `slots`, bypassing `self`. \
		If `~N_slot`, the slot at `N_slot` receives the full occur. \

		template <int N_slot=-1>
		XTAL_TNX influx_push_tail(auto &&o, auto &&...oo)
		XTAL_0EX
		{
			XTAL_IF0
			XTAL_0IF (N_slot <  0) {
				return influx_push(XTAL_REF_(oo)...);
			}
			XTAL_0IF_(default) {
				return [this, o=XTAL_REF_(o), ...oo=XTAL_REF_(oo)] <auto ...I>(bond::seek_t<I...>)
					XTAL_0FN_(slot<N_slot>().influx(o, oo...) &...& slot<(N_slot <= I) + I>().influx(oo...))
				(bond::seek_s<sizeof...(Xs) - 1> {});
			}
		}
		template <int N_slot=-1>
		XTAL_TNX efflux_pull_tail(auto &&o, auto &&...oo)
		XTAL_0EX
		{
			XTAL_IF0
			XTAL_0IF (N_slot <  0) {
				return efflux_pull(XTAL_REF_(oo)...);
			}
			XTAL_0IF_(default) {
				return [this, o=XTAL_REF_(o), ...oo=XTAL_REF_(oo)] <auto ...I>(bond::seek_t<I...>)
					XTAL_0FN_(slot<N_slot>().efflux(o, oo...) &...& slot<(N_slot <= I) + I>().efflux(oo...))
				(bond::seek_s<sizeof...(Xs) - 1> {});
			}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
