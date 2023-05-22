#pragma once
#include "./any.hpp"
#include "../message/any.hpp"
#include "../message/serial.hpp"




XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U, typename ...As>
struct sourced
{
	using subkind = confer<U, As...>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		template <typename ...Xs>
		struct bind
		{
			using superkind = typename co::template bind<Xs...>;
			using signature = typename superkind::signature;
			using result_t = typename superkind::result_t;
			using return_t = typename superkind::return_t;
			using subkind = compose<content::confer<result_t>, superkind>;

			template <typename R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;

			public:
				using co::co;

				XTAL_RE2_(XTAL_FN1 source(XTAL_DEF... oo), co::head(XTAL_REF_(oo)...))

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return source();
				}

				XTAL_NEW subtype(XTAL_DEF ...oo)
				XTAL_0EX
				:	co(XTAL_REF_(oo)...)
				{
				}
				XTAL_NEW subtype()
				XTAL_0EX
				:	co(co::template method<>())
				{
				}

				using co::defuse;

				XTAL_FN2_(flux_t) defuse(XTAL_DEF_(message::serial_q) serial_o)
				XTAL_0EX
				{
					return co::defuse(XTAL_REF_(serial_o)) and (source(co::template method<>()), 1);
				}

			};
		};

	};
};
template <typename U, typename ...As>
using     sourced_t = confined_t<sourced<U, As...>>;
XTAL_LET  sourced_f = [] (XTAL_DEF u)
XTAL_0FN_(sourced_t<decltype(u)>(XTAL_REF_(u)));

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
