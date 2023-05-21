#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U, typename... As>
struct virtualize
{
	using subkind = confer<U, As...>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		template <typename... Xs>
		struct bind
		{
			using subkind = typename co::template bind<Xs...>;

			template <typename R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;

				XTAL_FN2 source()
				XTAL_0EX
				{
					return co::template method<>();
				}

			protected:
				typename co::result_t result_m = source();

			private:
				using serial_u = message::serial_t<>;

			public:
				using co::co;

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return result_m;
				}

				XTAL_FN2 begin()
				XTAL_0EX
				{
					return result_m.begin();
				}

				XTAL_FN2 end()
				XTAL_0EX
				{
					return result_m.end();
				}

				XTAL_FN2_(iota_t) efflux(XTAL_DEF... ws)
				XTAL_0EX
				{
					return co::efflux(XTAL_REF_(ws)...);
				}
				template <is_q<serial_u> W>
				XTAL_FN2_(iota_t) efflux(W &&serial_w, XTAL_DEF... ws)
				XTAL_0EX
				{
					iota_t _ = co::efflux(XTAL_FWD_(W) (serial_w), XTAL_REF_(ws)...); if (_) result_m = source();
					return _;
				}

			};
		};

	};
};
template <typename U, typename... As>
using     virtualize_t = confined_t<virtualize<U, As...>>;
XTAL_LET  virtualize_f = [] (XTAL_DEF u)
XTAL_0FN_(virtualize_t<decltype(u)>(XTAL_REF_(u)));

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
