#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Ties `Xs...` to unify flow branching, etc. \

///\note\
Deified as a `process`'s `closure`, binding the provided arguments. \

template <class ...Xs> struct   bundle;
template <class ...Xs> using    bundle_t = confined_t<bundle<Xs...>>;
template <class ..._s> concept  bundle_q = bond::tag_p<bundle, _s...>;


//////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct bundle
{
	using superkind = bond::compose<bond::tag<bundle>
	,	cell::defer<flow::packed_t<Xs...>>
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
		Initialize `arguments` using those provided. \

		XTAL_NEW_(explicit) subtype(Xs &&...xs)
		noexcept
		:	S_(H_{XTAL_REF_(xs)...})
		{}

	public:// ACCESS
		using S_::self;
		using S_::head;

		//\note\
		Contingent override of `node` allows unextended `bundle`s to be destructured. \
		Use `arguments` for unmitigated access. \

		using node_type = typename S_::head_type;

		XTAL_FX4_(alias) (XTAL_DEF_(return,inline,get)      node(), head())
		XTAL_FX4_(alias) (XTAL_DEF_(return,inline,get) arguments(), head())
		
		XTAL_FX2_(do) (template <size_type ...Is>
		XTAL_DEF_(return,inline,let)
		argument(),
		noexcept -> decltype(auto)
		{
			return bond::pack_item_f<Is...>(head());
		})
		
	public:// FLOW

		///\returns the result of influxing `self` then  (if `& 1`) `arguments`. \
		///\returns the result of effluxing `arguments` then (if `& 1`) `self`. \

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux(auto &&...oo)
		noexcept -> signed
		{
			XTAL_IF0
			XTAL_0IF (N_ion == +1) {
				return [this, oo...]
					XTAL_0FN_(and) (self().template flux_arguments<N_ion>(oo...))
						(S_::template flux<N_ion>(XTAL_REF_(oo)...));
			}
			XTAL_0IF (N_ion == -1) {
				return [this, oo...]
					XTAL_0FN_(and) (S_::template flux<N_ion>(oo...))
						(self().template flux_arguments<N_ion>(XTAL_REF_(oo)...));
			}
		}

		///\returns the result of `*flow`ing with the supplied routing. \
		If prefixed by a positive `constant_q`, forwards to the `argument` specified. \
		If prefixed by a negative `constant_q` , forwards to all `arguments`. \

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux(constant_q auto &&o, auto &&...oo)
		noexcept -> signed
		{
			extent_type constexpr i = XTAL_ALL_(o){};
			XTAL_IF0
			XTAL_0IF (0 <= i) {return argument<i>().template flux          <N_ion>(XTAL_REF_(oo)...);}
			XTAL_0IF (i <  0) {return self       ().template flux_arguments<N_ion>(XTAL_REF_(oo)...);}
		}

		///\
		Forwards `oo...` to all `arguments`, bypassing `self`. \

		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux_arguments(auto &&...oo)
		noexcept -> signed
		{
			return arguments().apply([...oo=XTAL_REF_(oo)] (auto &&...xs)
				XTAL_0FN_(return) (XTAL_REF_(xs).template flux<N_ion>(oo...) &...& -1)
			);
		}
		///\
		Forwards `oo...` to all `arguments`, bypassing `self`. \
		If `0 <= N_dex`, the message is prefixed by `o` for the `argument` specified. \

		template <signed N_ion, int N_dex>
		XTAL_DEF_(return,inline,let)
		flux_arguments_(auto &&o, auto &&...oo)
		noexcept -> signed
		{
			XTAL_IF0
			XTAL_0IF (N_dex <  0) {
				return flux_arguments<N_ion>(XTAL_REF_(oo)...);
			}
			XTAL_0IF (0 <= N_dex) {
				return [this, o=XTAL_REF_(o), ...oo=XTAL_REF_(oo)]
				<auto ...I>(bond::seek_t<I...>)
					XTAL_0FN_(return) (
						argument<N_dex>().template flux<N_ion>(o, oo...) &...& argument<(N_dex <= I) + I>().template flux<N_ion>(oo...)
					)
				(bond::seek_s<sizeof...(Xs) - 1> {});
			}
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
