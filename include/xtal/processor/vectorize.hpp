#pragma once
#include "./any.hpp"
#include "../message/anything.hpp"





XTAL_ENV_(push)
namespace xtal::processor
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <typename U, typename... As>
struct vectorize
{
	using interrupt = typename message::contrived_t<>::interrupt<0>;
	using subkind = confer<U, buffer<-1>>;
//	using subkind = confer<U, As..., interrupt, buffer<-1>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>;
	public:
		using co::co;

		template <typename... Xs>
		struct bind
		{
			using subkind = compose<As..., interrupt, typename co::template bind<Xs...>>;

			template <any_q _S>
			class subtype: public compose_s<_S, subkind>
			{
				using co = compose_s<_S, subkind>;

				XTAL_FN2 source()
				XTAL_0EX
				{
					return co::template method<>();
				}

			public:
				using result_t = typename co::result_t;
				using buffer_t = typename co::template vector_t<iteratee_t<result_t>>;
				using target_t = rendered_t<buffer_t>;

				using render_t = message::render_t<target_t>;
				using resize_t = message::resize_t<>;
				using serial_t = message::serial_t<>;

			protected:
				buffer_t buffer_m;
				target_t target_m;

			public:
				using co::co;
				using co::self;

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

				template <typename W>
				XTAL_FN2_(iota_t) deflux(W &&w)
				XTAL_0EX
				{
					auto const _ = co::deflux(w);
					if constexpr (is_q<resize_t, W>)
					{
						//\
						TODO: Proceed iff `this` is an `lvalue`, \
						which should be enough to ensure that `target_m` can be shared. \

						if (1 == _)
						{
							self().resize(XTAL_FWD_(W) (w));
						}
					}
					return _;
				}

				///\
				Message `efflux` handler: forwards the message to `arguments` then `this`. \
				\
				NOTE: The command to render comprises a `message::render` guarded by `message::serial`. \
				If no `message::render` is supplied, the `span` for the current `vector` is used instead. \
				If identical `serial` prefixes are received in succession, only the first will `render`. \

				XTAL_FN2_(iota_t) efflux(XTAL_DEF... ws)
				XTAL_0EX
				{
					return co::efflux(XTAL_REF_(ws)...);
				}
				template <is_q<serial_t> W>
				XTAL_FN2_(iota_t) efflux(W &&serial_w)
				XTAL_0EX
				{
					target_m = target_t(buffer_m);
					return efflux(XTAL_FWD_(W) (serial_w), render_t(target_m));
				}

				XTAL_FN2_(iota_t) efflux(render_t &&render_w)
				XTAL_0EX
				{
					target_m = target_t(render_w);
					auto const _ = co::efflux(_std::move(render_w));
					self().render();
					return _;
				}
				XTAL_FN2_(iota_t) efflux(render_t const &render_w)
				XTAL_0EX
				{
					target_m = target_t(buffer_m);
					auto const _ = co::efflux(render_w);
					self().render(render_w);
					return _;
				}

				XTAL_FN1_(void) resize()
				XTAL_0EX
				{
				}
				XTAL_FN1_(void) resize(resize_t const &resize_w)
				XTAL_0EX
				{
					buffer_m.resize(resize_w);
				}

				XTAL_FN1_(void) render()
				XTAL_0EX
				{
				//	TODO: Create an alternative to interrupted event handling for contiguous dynamic controls: \
					-	Store the differences in a (possibly sparse) array. \
					-	Apply the differences on access. \
					-	Zero the array element after access. \

				//	TODO: Incorporate `std::execution_policy` based on `co::disorder_v`. \

					co::redux([this] (iota_t i, iota_t j)
						XTAL_0FN_(_v3::ranges::copy(source()|_v3::views::slice(i, j), _v3::ranges::next(target_m.begin(), i)))
					);
				}
				XTAL_FN1_(void) render(render_t const &render_w)
				XTAL_0EX
				{
					self().render();
					_v3::ranges::copy(target_m, render_w.begin());
				}

			};
		};

	};
};
template <typename U, typename... As>
using vectorize_t = confined_t<vectorize<U, As...>>;

template <typename... As>
XTAL_LET  vectorize_f = [] <typename U>(U &&u)
XTAL_0FN_(vectorize_t<U, As...>(XTAL_FWD_(U) (u)));

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
