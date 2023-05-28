#pragma once
#include "./any.hpp"
#include "../message/any.hpp"
#include "../message/serial.hpp"
#include "../message/nominal.hpp"



XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U, typename ...As>
struct resolve
{
	using subkind = confer<U, As...>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>; using T = typename co::self_t;
	public:
		using co::co;

		template <typename ...Xs>
		struct bind
		{
			using superbind = typename co::template bind<Xs...>;
			using signature = typename superbind::signature;
			using result_t  = typename superbind::result_t;
			using return_t  = typename superbind::return_t;

			using serial_n = typename superbind::serial_n;
			using serial_u = typename superbind::serial_u;
			using resize_u = typename superbind::resize_u;

			using subkind = common::compose<any<>
			,	content::confer<result_t>
			,	As...
			,	superbind
			>;

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

				using co::efflux;

				XTAL_FN2_(flux_t) efflux(XTAL_DEF_(message::serial_q) serial_o)
				XTAL_0EX
				{
					return co::efflux(serial_o) and ((void) solve(co::method()), 1);
				}

			};
		};

	};
};
template <typename U, typename ...As>
using     resolve_t = confined_t<resolve<U, As...>>;
XTAL_LET  resolve_f = [] (XTAL_DEF u)
XTAL_0FN_(resolve_t<decltype(u)>(XTAL_REF_(u)));

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
