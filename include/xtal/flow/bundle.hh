#pragma once
#include "./any.hh"

#include "../cell/bundle.hh"




XTAL_ENV_(push)
namespace xtal::flow
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Ties `Xs...` together to facilitate distributive flow.

\details
Internalized by `process` as `binding`,
allowing message distribution over bound arguments.
*/
template <class ...Xs> struct   bundle;
template <class ...Xs> using    bundle_t = confined_t<bundle<Xs...>>;
template <class ..._s> concept  bundle_q = bond::tag_in_p<bundle, _s...>;

//////////////////////////////////////////////////////////////////////////////////

XTAL_DEF_(let) bundle_f = []<class ...Xs> (Xs &&...xs)
XTAL_0FN {
	XTAL_IF0
	XTAL_0IF (un_v<0, objective_q<Xs>...>) {return bundle_t<objective_t<Xs>...>{            XTAL_REF_(xs) ...};}
	XTAL_0IF (in_v<0, objective_q<Xs>...>) {return bundle_t<objective_t<Xs>...>{objective_f(XTAL_REF_(xs))...};}
};


//////////////////////////////////////////////////////////////////////////////////

template <class ...Xs>
struct bundle
{
	using superkind = bond::compose<bond::tag<bundle>
	,	cell::bundle<Xs...>
	>;
	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;
		using S_::head;

		XTAL_FN2_(to) (template <size_type ...Is>
		XTAL_DEF_(return,inline,get)
		argument(), S_::template argument<Is...>())

	public:// FLOW

		/*!
		\returns	The aggregated result of `flux`ing `self` and `arguments`.
		\returns	If `N_ion == +1`, evaluates `arguments` if `self` evaluates succesfully.
		If `N_ion == -1`, evaluates `self` if `arguments` evaluate  succesfully.
		*/
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux(auto &&...oo)
		noexcept -> signed
		{
			XTAL_IF0
			XTAL_0IF (N_ion == +1) {
				return [this, oo...]
					XTAL_1FN_(and) (flux<N_ion>(constant_t<-1>{}, oo...))
						(S_::template flux<N_ion>(XTAL_REF_(oo)...));
			}
			XTAL_0IF (N_ion == -1) {
				return [this, oo...]
					XTAL_1FN_(and) (S_::template flux<N_ion>(oo...))
						(flux<N_ion>(constant_t<-1>{}, XTAL_REF_(oo)...));
			}
		}

		/*!
		\returns	The result of `flow`ing with the supplied routing.
		\returns	If prefixed by a positive `constant_q`, forwards to the `argument` specified.
		If prefixed by a negative `constant_q`, forwards to all `arguments`.
		*/
		template <signed N_ion,   natural_constant_q I_path>
		XTAL_DEF_(return,inline,let)
		flux(I_path, auto &&...oo)
		noexcept -> signed
		{
			return argument<I_path{}>().template flux<N_ion>(XTAL_REF_(oo)...);
		}
		template <signed N_ion, unnatural_constant_q I_path>
		XTAL_DEF_(return,inline,let)
		flux(I_path, auto &&...oo)
		noexcept -> signed
		{
			return self().template flux_rest<N_ion>(XTAL_REF_(oo)...);
		}

	//\
	protected:// FLOW
	public:// FLOW
		/*!
		\brief  	Forwards `oo...` to all `arguments`, bypassing `self`.
		*/
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		flux_rest(auto &&...oo)
		noexcept -> signed
		{
			return S_::arguments([...oo=XTAL_REF_(oo)] (auto &&...xs)
				XTAL_0FN_(to) (XTAL_REF_(xs).template flux<N_ion>(oo...) &...& -1)
			);
		}
		/*!
		\brief  	Forwards `oo...` to all `arguments`, bypassing `self`.
		If `0 <= N_dex`, the message is prefixed by `o` for the `argument` specified.
		*/
		template <signed N_ion, unnatural_constant_q I_head>
		XTAL_DEF_(return,inline,let)
		flux_unrest(I_head, auto &&o, auto &&...oo)
		noexcept -> signed
		{
			return flux_rest<N_ion>(XTAL_REF_(oo)...);
		}
		template <signed N_ion,   natural_constant_q I_head>
		XTAL_DEF_(return,inline,let)
		flux_unrest(I_head, auto &&o, auto &&...oo)
		noexcept -> signed
		{
			auto constexpr N_head = I_head{}();
			return [this, o=XTAL_REF_(o), ...oo=XTAL_REF_(oo)]
			<auto ...I>(bond::seek_t<I...>)
				XTAL_0FN_(to) (
					argument<N_head>().template flux<N_ion>(o, oo...)
						&...& argument<skip_v<N_head, I>>().template flux<N_ion>(oo...)
				)
			(bond::seek_s<sizeof...(Xs) - 1> {});
		}

	};
	using type = confined_t<bond::compose_t<subtype>>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
