#pragma once
#include "./any.hpp"
#include "../control/sequel.hpp"





XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename, typename ...>
struct bond;

using bond_s = any_t<of_t<bond>>;

template <typename U, typename ...As>
using bond_t = typename confined<bond<U, As...>>::template subtype<bond_s>;

template <typename... Ts>
concept bond_q = if_q<bond_s, Ts...>;

template <typename ...As>
XTAL_FZ2 bond_f(XTAL_DEF u)
{
	return bond_t<decltype(u), As...>(XTAL_REF_(u));
}

////////////////////////////////////////////////////////////////////////////////

template <typename U, typename ...As>
struct bond
{
	using subkind = confer<U, link<As...>>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>; using T = typename co::self_t;
	public:
		using co::co;

		template <typename ...Xs>
		struct bind
		{
			using rebound = typename co::template bind<Xs...>;
			using subkind = common::compose<content::confer<typename rebound::result_t>, rebound>;

			template <typename R>
			class subtype: public common::compose_s<R, subkind>
			{
				using co = common::compose_s<R, subkind>;

			public:
				XTAL_CO4_(subtype);
				XTAL_CO2_(subtype);
			//	using co::co;

				XTAL_NEW_(explicit) subtype(XTAL_DEF ...xs)
				XTAL_0EX
				:	co(co::method(XTAL_REF_(xs)...), XTAL_REF_(xs)...)
				{
				}
				XTAL_NEW_(explicit) subtype(XTAL_DEF_(is_q<T>) t, XTAL_DEF ...xs)
				XTAL_0EX
				:	co(co::method(XTAL_REF_(xs)...), XTAL_REF_(t), XTAL_REF_(xs)...)
				{
				}

				XTAL_RE2_(XTAL_FN1 solve(XTAL_DEF... oo), co::head(XTAL_REF_(oo)...))

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return solve();
				}

			public:
				using co::efflux;

				XTAL_FNX efflux(XTAL_DEF_(control::sequel_q) sequel_o)
				XTAL_0EX
				{
					return XTAL_FLX_((void) solve(co::method()), (sign_t) 1) (co::efflux(XTAL_REF_(sequel_o)));
				}

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
