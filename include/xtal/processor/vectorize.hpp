#pragma once
#include "./any.hpp"
#include "../message/any.hpp"





XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U, typename... As>
struct vectorize
{
	using interrupt = typename message::contrived_t<>::interrupt<0>;
//	using subkind = confer<U, As..., interrupt, buffer<-1>>;
	using subkind = confer<U, buffer<-1>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		template <typename... Xs>
		struct bind
		{
		//	using subkind = typename co::template bind<Xs...>;
			using subkind = compose<As..., interrupt, typename co::template bind<Xs...>>;

			template <any_q R>
			class subtype: public compose_s<R, subkind>//, public iterate_t<subtype<R>>
			{
				using co = compose_s<R, subkind>;

			public:
				using result_t = typename co::result_t;
				using buffer_t = typename co::template vector_t<iteratee_t<result_t>>;
				using target_t = reified_t<buffer_t>;

				using render_t = message::render_t<target_t>;
				using resize_t = message::resize_t<>;
				using serial_t = message::serial_t<>;

			protected:
				buffer_t buffer_m;
				target_t target_m;

			//	XTAL_FN1_(void) handle(resize_t w)// &&
			//	XTAL_0EX
			//	XTAL_IF1 unimorphic_q<result_t, Xs...>
			//	{
			//		buffer_m.resize(XTAL_REF_(w));// TODO: Delete line, since `&&` should reuse the provided buffer.
			//	}
				XTAL_FN1_(void) handle(resize_t resize_o)// &
				XTAL_0EX
				{
					buffer_m.resize(XTAL_REF_(resize_o));
				}
				XTAL_FN1_(void) handle(render_t render_o)
				XTAL_0EX
				{
					target_m = render_o;
					co::redux([this] (iota_t i, iota_t j)
						XTAL_0FN_(_v3::ranges::copy(co::template method<>()|
							_v3::views::slice(i, j), _v3::ranges::next(target_m.begin(), i))
						)
					);
				}

			public:
				using co::co;
				using co::self;

			//	XTAL_CO2_(subtype);
				XTAL_CO4_(subtype);
				XTAL_RE2_(XTAL_FN2 buffer(), buffer_m)

				template <auto...>
				XTAL_FN2 method()
				XTAL_0EX
				{
					return target_m;
				}

				XTAL_FN2 begin()
				XTAL_0EX
				{
					return target_m.begin();
				}

				XTAL_FN2 end()
				XTAL_0EX
				{
					return target_m.end();
				}

				///\
				Message `deflux` handler: responds to the matched head `w`. \

				XTAL_FN2_(iota_t) deflux(auto o)
				XTAL_0EX
				{
					iota_t const _ = co::deflux(o);
					if constexpr (requires {handle(o);})
					{
						if (_) handle(o);
					}
					return _;
				}

				///\
				Message `efflux` handler: forwards the message to `arguments` then `this`. \
				\
				NOTE: The command to render comprises a `message::render` guarded by `message::serial`. \
				If no `message::render` is supplied, the `span` for the current `vector` is used instead. \
				If identical `serial` prefixes are received in succession, only the first will `render`. \

				XTAL_FN2_(iota_t) efflux(XTAL_DEF... oo)
				XTAL_0EX
				{
					return co::efflux(XTAL_REF_(oo)...);
				}

				XTAL_FN2_(iota_t) efflux(serial_t serial_o)
				XTAL_0EX
				{
					return efflux(serial_o, render_t(buffer_m));
				}

			//	XTAL_FN2_(iota_t) efflux(serial_t serial_o, render_t render_o)// &&
			//	XTAL_0EX
			//	XTAL_IF1 unimorphic_q<result_t, Xs...>
			//	{
			//		iota_t const _ = co::efflux(serial_o, render_o);   // render `co`   to `render_o`
			//		return !_?0: _ & efflux(render_o);                 // render `this` to `render_o`
			//	}
				XTAL_FN2_(iota_t) efflux(serial_t serial_o, render_t render_o)// &
				XTAL_0EX
				{
					iota_t const _ = co::efflux(serial_o);             // render `co`
					return !_?0: _ & efflux(render_o);                 // render `this` to `render_o`
				}

			};
		};

	};
};
template <typename U, typename... As>
using     vectorize_t = confined_t<vectorize<U, As...>>;
XTAL_LET  vectorize_f = [] (XTAL_DEF u)
XTAL_0FN_(vectorize_t<decltype(u)>(XTAL_REF_(u)));

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
