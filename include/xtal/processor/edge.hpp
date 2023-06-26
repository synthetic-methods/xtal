#pragma once
#include "./any.hpp"
#include "../message/sequel.hpp"





XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename, typename ...>
struct edge;

using edge_s = any_t<of_t<edge>>;

template <typename U, typename ...As>
using edge_t = typename confined<edge<U, As...>>::template subtype<edge_s>;

template <typename... Ts>
concept edge_q = if_q<edge_s, Ts...>;

template <typename ...As>
XTAL_FZ2 edge_f(XTAL_DEF u)
{
	return edge_t<decltype(u), As...>(XTAL_REF_(u));
}


////////////////////////////////////////////////////////////////////////////////

template <typename U, typename ...As>
struct edge
{
	using subkind = confer<U, link<As...>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>; using T = typename co::self_t;
	
	public:
		using co::co;
		using co::self;

		template <typename ...Xs>
		struct bond
		{
			using rebound = typename co::template bond<Xs...>;
			using subkind = compose<concord::confer<typename rebound::result_t>, rebound>;

			template <typename R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;

			public:
				XTAL_CN4_(subtype);
				XTAL_CN2_(subtype);
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

				XTAL_RN2_(XTAL_FN1 solve(XTAL_DEF... oo), co::head(XTAL_REF_(oo)...))

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return solve();
				}

			public:
				using co::efflux;

				XTAL_FNX efflux(XTAL_DEF_(message::sequel_q) sequel_o)
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
